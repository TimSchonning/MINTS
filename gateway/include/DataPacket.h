#ifndef DATAPACKET_H
#define DATAPACKET_H

#include <stdint.h>

#pragma pack(push, 1)
struct payload_t {
    uint8_t signature = 0xDEADBEEF;
    uint16_t nodeID;
    int8_t pm10;
    int8_t pm25;
    int8_t noise_peak;
};
#pragma pack(pop)

#endif