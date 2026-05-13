#ifndef POWER_H
#define POWER_H

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

#endif