#ifndef SYSTEM_UTILS_H
#define SYSTEM_UTILS_H

#include <cstdint>

void error_handler(int16_t state, const char* message);

void power_down_radios();

#endif