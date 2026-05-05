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

int main() // TODO: Clear gateway simulation and add (modified) main loop from LoRa.cpp
{
    LoRaInit();

    payload_t packet;

    std::cout << "Gateway started..." << std::endl;

    while (true)
    {
        int state = radio.receive((uint8_t *)&packet, sizeof(payload_t));

        if (state == RADIOLIB_ERR_NONE) {
            std::cout << packet.signature << std::endl; // Test print
            if (packet.signature == 0xDEADBEEF) {
                std::cout << (int)packet.nodeID << ","
                          << (int)packet.pm10 << ","
                          << (int)packet.pm25 << ","
                          << (int)packet.noise_peak << std::endl;
                std::cout.flush();                              
            }
        } else if (state == RADIOLIB_ERR_RX_TIMEOUT){
            // No packet received in this polling window, maybe add some kind of sleep?
            // Normal behaviour btw
        } else if (state == RADIOLIB_ERR_CRC_MISMATCH) {
            std::cout << "CRC Error!" << std::endl;
        } else {
            std::cout << "Unknown error: " << (int)state << std::endl;
        }
    }

    return 0;
}