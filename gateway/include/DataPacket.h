#ifndef DATAPACKET_H
#define DATAPACKET_H

#include <stdint.h>

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