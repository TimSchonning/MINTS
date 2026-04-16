#ifndef SYSTEM_UTILS_H
#define SYSTEM_UTILS_H

#include <cstdint>

#include "config.h"
#include "debug_macros.h"
#include "encode_payload.h"
#include "sensor_logic.h"
#include "utils.h"

typedef struct {
    uint8_t msg_type;
    uint32_t time_stamp;
} clearance_msg;

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