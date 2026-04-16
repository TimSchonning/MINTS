#include <iostream>
#include <windows.h>
#include <string>
#include "../include/DataPacket.h"

bool toPython = true; // Temporary variable. Decides if print from c++ or from a separate python file.

int main()
{
    // Open the COM port - Make sure COM5 matches your current setup!
    HANDLE hSerial = CreateFileW(L"\\\\.\\COM5", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    if (hSerial == INVALID_HANDLE_VALUE)
    {
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

    payload_t packet;
    DWORD bytesRead;

    while (true)
    {
        uint8_t syncCheck = 0; // Use uint8_t for single byte reads

        if (ReadFile(hSerial, &syncCheck, 1, &bytesRead, NULL) && bytesRead > 0)
        {
            static uint32_t window = 0; // Sliding window
            window = (window << 8) | (syncCheck & 0xFF);

            // FIX 1: Changed '=' to '==' so it actually checks the signature
            // Added Little-Endian check just in case
            if (window == 0xDEADBEEF || window == 0xEFBEADDE)
            {

                uint8_t *remainingData = (uint8_t *)&packet + sizeof(uint32_t);
                size_t remainingSize = sizeof(packet) - sizeof(uint32_t);

                if (ReadFile(hSerial, remainingData, (DWORD)remainingSize, &bytesRead, NULL))
                {

                    if (toPython)
                    {
                        // FIX 2: Added (int) casts to show numeric values
                        std::cout << (int)packet.nodeID << ","
                                  << (int)packet.pm10 << ","
                                  << (int)packet.pm25 << ","
                                  << (int)packet.noise_peak << std::endl;
                        std::cout.flush();
                    }
                    else
                    {
                        // FIX 3: Added (int) casts to stop symbols like 'r' and '╦'
                        std::cout << "Node: " << (int)packet.nodeID
                                  << " | PM10: " << (int)packet.pm10
                                  << " | PM25: " << (int)packet.pm25
                                  << " | Peak Noise: " << (int)packet.noise_peak << std::endl;
                    }
                }
                // FIX 4: Reset window so we don't find a signature inside the data
                window = 0;
            }
        }
    }

    return 0;
}