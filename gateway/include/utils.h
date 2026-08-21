#ifndef UTILS_H
#define UTILS_H

#include <cstdint>

/**
 * @brief Logic for handling error status codes.
 * @param state The error code.
 * @param message The error message to print if the state is not successful.
 * @return true if an error occurred, false if successful.
 */
bool error_handler(int16_t state, const char* message);

#endif