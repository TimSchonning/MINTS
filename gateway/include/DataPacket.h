#include <stdint.h>

#pragma pack(push, 1)
typedef struct
{
    uint32_t signature = 0xDEADBEEF;
    uint16_t nodeID;
    int pm10, pm25;
    int noise_peak;
} __attribute__((packed)) payload_t;
#pragma pack(pop)