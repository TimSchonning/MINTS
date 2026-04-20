#ifndef UTILS_H
#define UTILS_H

#include <cstdint>

#include "config.h"
#include "debug_macros.h"
#include "encode_payload.h"
#include "protocol.h"
#include "sensor_logic.h"
#include "utils.h"

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
 * @note Is blocking.
 */
void initialise_node();

/**
 * @brief Synchronizes with the gateway and sets a Deep Sleep timer until the next window.
 * @return success
 * @note Is blocking.
 */
bool standby_mode();

/**
 * @brief Sleeps the sensor.
 * @return success
 */
bool sleep_particle_sensor();

/**
 * @brief Sleeps the sensor.
 * @return success
 */
bool sleep_noise_sensor();

#endif