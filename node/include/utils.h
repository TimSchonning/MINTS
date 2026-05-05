#ifndef UTILS_H
#define UTILS_H


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

/**
 * @brief Sets the node to config mode - where it can receive updates to state RTC variables.
 * @note Starts and sleeps the radio upon use.
 * @note Acks the gateway upon received config message
 */
void config_mode();

/**
 * @brief Saves a single set of sensor readings to flash using the boot count as the unique ID.
 * @note pm1   => i_%u_p1
 * @note pm2,5 => i_%u_p2
 * @note noise => i_%u_n
 */
void add_to_nvs(uint8_t boot_count, uint8_t pm10, uint8_t pm25, uint16_t noise);

#endif