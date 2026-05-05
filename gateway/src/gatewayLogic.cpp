/**
 * Contains the logic for the gateway. Is called upon by the dataToFirebase script.
 * @see dataToFirebase.py
 * Currently receives data from the COM port, transforms it to CSV format, and forwards it to dataToFirebase.
 * TODO: This file will be modified to work with an on-board LoRa module, i.e. COM ports, baud rate, etc will not be neccessary.
 */

#include <iostream>
#include <string>

#include "RadioLib.h"
#include "DataPacket.h"
#include "../include/protocol.h"
#include "../include/config.h"
#include "modules/SX126x/SX1262.h"
#include "hal/RPi/PiHal.h"

bool toPython = true; // Temporary variable. Decides if print from c++ or from a separate python file.

PiHal* hal = new PiHal(1, 2000000, 0);
Module *mod = new Module(hal, CS, DIO1, RST, BUSY);
SX1262 radio(mod);

void LoRaInit() {
    int state = radio.begin(FREQ, BW, SF, CR, SYNC, PWR, PRE);

    if (state != RADIOLIB_ERR_NONE) {
        std::cout << "Initialisation failed, error code: \n" 
                  << "For error codes, see: https://jgromes.github.io/RadioLib/group__status__codes.html"
                  << (int)state << std::endl; // Maybe add some error handling?
    }
}

void handleSensorReading(payload_t packet) {
    std::cout << (int)packet.node_id    << ","
              << (int)packet.readings[0]       << ","
              << (int)packet.readings[1]       << ","
              << (int)packet.readings[2] << std::endl; // TODO: Är inte noise peak i readings[2] och readings[3]?
    std::cout.flush();
}

void sendAck(uint8_t nodeID, uint8_t ackFor) {
    msg_ack_t msg_packet_ack;
    msg_packet_ack.node_id = nodeID;
    msg_packet_ack.ack_for = ackFor;

    radio.transmit((uint8_t*)&msg_packet_ack, sizeof(msg_ack_t));
}

void handlePacket(payload_t packet) {
    switch (packet.signature) {
        case MSG_TYPE_PAYLOAD_UPLINK:
            handleSensorReading(packet);
            sendAck(packet.node_id, MSG_TYPE_PAYLOAD_UPLINK);
            break;

        case MSG_TYPE_ACK:
            break;

        default:
            std::cout << "Unknown packet signature: " << (uint8_t)packet.signature << std::endl;
            break;
    }
}

int main() { // TODO: Clear gateway simulation and add (modified) main loop from LoRa.cpp
    LoRaInit();

    payload_t packet;

    std::cout << "Gateway started..." << std::endl;

    while (true) {
        int state = radio.receive((uint8_t *)&packet, sizeof(payload_t));

        switch (state) {
            case RADIOLIB_ERR_NONE:
                handlePacket(packet);
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