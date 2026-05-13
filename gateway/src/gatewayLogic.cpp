/**
 * Contains the logic for the gateway. Is called upon by the dataToFirebase script.
 * @see dataToFirebase.py
 * Currently receives data from the COM port, transforms it to CSV format, and forwards it to dataToFirebase.
 * TODO: This file will be modified to work with an on-board LoRa module, i.e. COM ports, baud rate, etc will not be neccessary.
 */

#include <iostream>
#include <string>
#include <stdint.h>

#include "RadioLib.h"
#include "DataPacket.h"
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
            std::cout << "[ERROR] Node-side node ID: " << error_msg->node_id << " error code: " << error_msg->error_code << std::endl;
            break;
        }

        default:
            std::cout << "Unknown packet signature: " << signature << std::endl;
            break;
    }
}

int main() { // TODO: Clear gateway simulation and add (modified) main loop from LoRa.cpp
    LoRaInit();

    while (true) {
        int state = radio.receive(packetBuffer, sizeof(packetBuffer));
        size_t payloadSize = radio.getPacketLength();

        switch (state) {
            case RADIOLIB_ERR_NONE:
                handlePacket(payloadSize);
                break;

            case RADIOLIB_ERR_RX_TIMEOUT:
                break;

            case RADIOLIB_ERR_CRC_MISMATCH:
                std::cout << "CRC Error!" << std::endl;
                break;

            default:
                std::cout << "Unknown error: " << (int)state << std::endl;
                break;
        }
    }

    return 0;
}

// bool IdAssignment() {
//     uint8_t id = 1;     //TODO: ID from db. 1 is placeholder.
//     // TODO: db error handling
    
//     msg_ack_t idReqACK;
//     idReqACK.node_id = id;  // The new ID!
//     idReqACK.ack_for = MSG_TYPE_JOIN_REQ;

//     int state = radio.transmit((uint8_t*)&idReqACK, sizeof(msg_ack_t));
//     //error_handler(state);  // TODO: error handling
//     return (state == RADIOLIB_ERR_NONE); // If succeeded return true
// }