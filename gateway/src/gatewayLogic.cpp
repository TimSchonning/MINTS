/**
 * Contains the logic for the gateway. Is called upon by the dataToFirebase script.
 * @see dataToFirebase.py
 * Currently receives data from the COM port, transforms it to CSV format, and forwards it to dataToFirebase.
 * TODO: This file will be modified to work with an on-board LoRa module, i.e. COM ports, baud rate, etc will not be neccessary.
 */

#include <iostream>
#include <string>
#include <stdint.h>
#include <chrono>

#include "RadioLib.h"
#include "../include/protocol.h"
#include "../include/config.h"
#include "modules/SX126x/SX1262.h"
#include "hal/RPi/PiHal.h"

bool toPython = true; // Temporary variable. Decides if print from c++ or from a separate python file.

uint8_t packetBuffer[256];

PiHal* hal = new PiHal(1, 2000000, 0);

Module *mod = new Module(hal, CS, DIO1, RST, BUSY);
SX1262 radio(mod);

void LoRaInit() {
    int state = radio.begin(FREQ, BW, SF, CR, SYNC, PWR, PRE);

    if (state == RADIOLIB_ERR_NONE) {
        state = radio.setDio2AsRfSwitch();
    }

    if (state != RADIOLIB_ERR_NONE) {
        std::cout << "Initialisation failed, error code: \n" 
                  << "For error codes, see: https://jgromes.github.io/RadioLib/group__status__codes.html"
                  << (int)state << std::endl; // Maybe add some error handling?
    }
}

/**
 * @brief Parses payload packets and outputs CSV data.
 * Extracts multiple sensor readings from a single payload packet and flushes
 * them to the console in the format: node_id, data1, data2, data3 and so on for each batched reading.
 * @param packet Pointer to the received payload structure.
 */
static void handleSensorReading(payload_t *packet, size_t payloadSize) {
    int payloadOverheadSize = 3;
    int paylaodReadingSize  = 4;
    int numberOfReadings = (payloadSize - payloadOverheadSize) / paylaodReadingSize;

    for (int i = 0; i < numberOfReadings; i++) {
        int set = i * 4;
        std::cout << (int)i                         << "," // is used to calculate the timestamps for each set
                  << (int)packet->node_id           << ","
                  << (int)packet->readings[set + 0] << ","
                  << (int)packet->readings[set + 1] << ","
                  << (uint16_t) ((packet->readings[set + 2] << 8) | packet->readings[set + 3]) << std::endl;
        std::cout.flush();
    }
}

/**
 * @brief Transmits an acknowledgement packet to a specific node.
 * @param nodeID The target node ID.
 * @param ackFor The message type signature being acknowledged.
 */
static void sendAck(uint8_t nodeID, uint8_t ackFor) {
    msg_ack_t msg_packet_ack;
    msg_packet_ack.node_id = nodeID;
    msg_packet_ack.ack_for = ackFor;

    radio.transmit((uint8_t *)&msg_packet_ack, sizeof(msg_ack_t));
}

/**
 * @brief Main packet handler.
 * Reads the packet signature from the global buffer and routes to the 
 * appropriate handler (Payload, Error, or ACK).
 */
static void handlePacket(size_t payloadSize) {
    uint8_t signature = packetBuffer[0];

    switch (signature) {
        case MSG_TYPE_PAYLOAD_UPLINK: {
            payload_t *packet = (payload_t *)packetBuffer;
            handleSensorReading(packet, payloadSize);
            sendAck(packet->node_id, MSG_TYPE_PAYLOAD_UPLINK);
            break;
        }

        case MSG_TYPE_ACK:
            break;

        case MSG_TYPE_ERROR: {
            msg_error_t *error_msg = (msg_error_t *)packetBuffer;
            std::cout << "[ERROR] Node-side node ID: " << (int)error_msg->node_id << " error code: " << (int)error_msg->error_code << std::endl;
            break;
        }

        default:
            std::cout << "Unknown packet signature: " << signature << std::endl;
            break;
    }
}

int main() {
    LoRaInit();

    auto lastValidPacketTime = std::chrono::steady_clock::now();
    
    const std::chrono::minutes MAX_GATEWAY_SILENCE(20); 

    while (true) {
        int state = radio.receive(packetBuffer, sizeof(packetBuffer), 5000);
        size_t payloadSize = radio.getPacketLength();

        switch (state) {
            case RADIOLIB_ERR_NONE:
                if (packetBuffer[0] == MSG_TYPE_PAYLOAD_UPLINK) {
                    lastValidPacketTime = std::chrono::steady_clock::now();
                }
                handlePacket(payloadSize);
                break;

            case RADIOLIB_ERR_RX_TIMEOUT:
                break;

            case RADIOLIB_ERR_CRC_MISMATCH:
                std::cout << "CRC Error!" << std::endl;
                break;

            default:
                std::cout << "Radio glitch or timeout state detected: " << (int)state << std::endl;
                break;
        }

        auto currentTime = std::chrono::steady_clock::now();
        if (currentTime - lastValidPacketTime > MAX_GATEWAY_SILENCE) {
            std::cout << "[WATCHDOG] Gateway silence timeout reached! Forcing SX1262 re-initialization..." << std::endl;
            
            radio.standby();
            hal->delay(100);
            
            LoRaInit();
            
            lastValidPacketTime = std::chrono::steady_clock::now();
        }
    }

    return 0;
}