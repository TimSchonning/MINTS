#ifndef DATAPACKET_H
#define DATAPACKET_H

#include <stdint.h>

/**
 * @brief Definition of how data is structured for communication between a node and a gateway.
 * 
 * This structure holds the signature and must be same for all files on all communicating devices.
 * Signature assures we are receiving the sought after message.
 * NodeID, pm10, pm25, noise_peak is the node's ID and collected data respectively.
 */

#pragma pack(push, 1)
struct payload_t {
    uint32_t signature = 0xDEADBEEF;
    uint8_t nodeID;
    uint8_t pm10;
    uint8_t pm25;
    uint16_t noise_peak;
};
#pragma pack(pop)

#endif