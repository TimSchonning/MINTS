/**
 * Contains the logic for the gateway. Is called upon by the dataToFirebase script.
 * @see dataToFirebase.py
 * Currently receives data from the COM port, transforms it to CSV format, and forwards it to dataToFirebase.
 * TODO: This file will be modified to work with an on-board LoRa module, i.e. COM ports, baud rate, etc will not be neccessary.
 */

#include <iostream>
#include <windows.h>
#include <string>
#include "../include/DataPacket.h"

bool toPython = true; // Temporary variable. Decides if print from c++ or from a separate python file.

int main()
{
    /**
     * Open the COM port - Make sure COM5 matches your current setup.
     * If unsure, check which port Arduino IDE is talking through.
     */
    HANDLE hSerial = CreateFileW(L"\\\\.\\COM5", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    if (hSerial == INVALID_HANDLE_VALUE)
    {
        /**
         * If correct port is chosen and you get access denied, check so nothing else is reading from your port.
         * E.g. close serial monitor in Arduino IDE, wait for Arduino code upload to finish, etc.
         */
        std::cerr << "Error: could not open COM port." << std::endl;
        return 1;
    }

    /**
     * Configures the serial port (Windows only)
     * Enables communication with an Arduino over UART.
     */
    DCB dcbSerialParams = {0};
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    GetCommState(hSerial, &dcbSerialParams);
    dcbSerialParams.BaudRate = CBR_115200;
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity = NOPARITY;
    SetCommState(hSerial, &dcbSerialParams);

    payload_t packet;
    DWORD bytesRead;

    while (true)
    {
        uint8_t syncCheck = 0; // Use uint8_t for single byte reads

        if (ReadFile(hSerial, &syncCheck, 1, &bytesRead, NULL) && bytesRead > 0)
        {
            static uint32_t window = 0; // Sliding window
            window = (window << 8) | (syncCheck & 0xFF);

            // Checks for Big-Endian or Little-Endian
            if (window == 0xDEADBEEF || window == 0xEFBEADDE)
            {
                // Removes the signature from the packet
                uint8_t *remainingData = (uint8_t *)&packet + sizeof(uint32_t);
                size_t remainingSize = sizeof(packet) - sizeof(uint32_t);

                if (ReadFile(hSerial, remainingData, (DWORD)remainingSize, &bytesRead, NULL))
                {
                    if (toPython)
                    {
                        // Converts received message to CSV
                        std::cout << (int)packet.nodeID << ","
                                  << (int)packet.pm10 << ","
                                  << (int)packet.pm25 << ","
                                  << (int)packet.noise_peak << std::endl;
                        std::cout.flush();
                    }
                    else
                    {
                        // Prints values directly to the terminal (for debugging)
                        std::cout << "Node: " << (int)packet.nodeID
                                  << " | PM10: " << (int)packet.pm10
                                  << " | PM25: " << (int)packet.pm25
                                  << " | Peak Noise: " << (int)packet.noise_peak << std::endl;
                    }
                }
                // Reset window
                window = 0;
            }
        }
    }

    return 0;
}