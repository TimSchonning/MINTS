#include <RadioLib.h>
#include "PiHal.h"

// LoRa HAT Pins
const int NSS_PIN = 0;
const int DIO1_PIN = 0;
const int NRST_PIN = 0;
const int BUSY_PIN = 0;

// Create the hardware abstraction layer instance
PiHal* hal = new PiHal();

// Create the radio instance
SX1262 radio = new Module(hal, NSS_PIN, DIO1_PIN, NRST_PIN, BUSY_PIN);

int main() {
    // Carrier freq: 868.0 MHz, BW: 125.0 kHz, SF: 9, CR: 7, SyncWord: 0x12, Power: 10 dBm
    int state = radio.begin(868.0, 125.0, 9, 7, 0x12, 10);

    if (state == RADIOLIB_ERR_NONE) {
        std::cout << "success!" << std::endl;
    } else {
        std::cout << "failed: " << state << std::endl;
        return 1;
    }

    while (true) {
        std::cout << "Waiting for incoming transmission ... " << std::flush;

        std::string str;
        state = radio.receive(str);

        if (state == RADIOLIB_ERR_NONE) {
            // Packet received successfully
            std::cout << "success!" << std::endl;

            std::cout << "Data:\t\t" << str << std::endl;
            std::cout << "RSSI:\t\t" << radio.getRSSI() << " dBm" << std::endl;
            std::cout << "SNR:\t\t" << radio.getSNR() << " dB" << std::endl;

        } else if (state == RADIOLIB_ERR_RX_TIMEOUT) {
            std::cout << "timeout!" << std::endl;

        } else if (state == RADIOLIB_ERR_CRC_MISMATCH) {
            std::cout << "Packet corrupted!" << std::endl;

        } else {
            // Some other error
            std::cout << "failed, code " << state << std::endl;
        }
    }

    return 0;
}