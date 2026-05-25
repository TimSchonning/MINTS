#ifndef POWER_H
#define POWER_H

#include "cstdint"

/**
 * @brief Disables all wireless communication.
 */
void power_down_radios();

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
 * @brief Wakes the sensor.
 * @return success
 */
bool wake_particle_sensor();

/**
 * @brief Calculates the time needed to sleep till the next measurement window.
 * @return sleep time in us.
 * @note Defaults to 900 seconds in the case of integer underflow.
 */
uint32_t calculate_sleep_time();

#endif