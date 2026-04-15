#include <iostream>
#include <windows.h>
#include <string>
#include "../include/DataPacket.h"

bool toPython = false; // Temporary variable. Decides if print from c++ or from a separate python file.

int main() {
    // Open the COM port (remove when Raspberry is used)
    HANDLE hSerial = CreateFileW(L"\\\\.\\COM3", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    if (hSerial == INVALID_HANDLE_VALUE) {
        std::cerr << "Error: could not open COM port." << std::endl;
        return 1;
    }

    DCB dcbSerialParams = {0};
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    GetCommState(hSerial, &dcbSerialParams);
    dcbSerialParams.BaudRate = CBR_115200;
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity = NOPARITY;
    SetCommState(hSerial, &dcbSerialParams);

    char incomingData[sizeof(payload_t)]; // I exemplet var det 256 it sizeof...
    payload_t packet;
    DWORD bytesRead;

    std::cout << "Listening for LoRa packets..." << std::endl;

    while (true) {
        uint32_t syncCheck = 0;
        
        ReadFile(hSerial, &syncCheck, 1, &bytesRead, NULL);

        static uint32_t window = 0; // Sliding window
        window = (window << 8) | (syncCheck & 0xFF);

        if (window = 0xDEADBEEF) {
            uint8_t* remainingData = (uint8_t*)&packet + sizeof(uint32_t);
            size_t remainingSize = sizeof(packet) - sizeof(uint32_t);

            if (ReadFile(hSerial, remainingData, remainingSize, &bytesRead, NULL)) {

                if (!toPython) {
                    std::cout << "Node: " << packet.nodeID
                          << " | PM10: " << packet.pm10 
                          << " | PM5" << packet.pm25 
                          << " | Peak Noise: " << packet.noise_peak << std::endl;
                } else {
                    return; //TODO
                }
                
            }
        }
    }
    
    return 0;
}