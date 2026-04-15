#ifndef SYSTEM_UTILS_H
#define SYSTEM_UTILS_H

#include <cstdint>

/**
 * @brief Logic for handling radio status codes.
 * @param state The return code from the radio library.
 * @param message The error message to print if the state is not successful.
 * @return true if an error occurred, false if successful.
 */
bool error_handler(int16_t state, const char* message);

/**
 * @brief Disables all wireless communication.
 */
void power_down_radios();

/**
 * @brief Initializes the LoRa radio and performs a handshake with the gateway
 * to receive a unique node ID.
 * @note Sets init_flag to false upon success.
 */
void initialise_node();

#endif