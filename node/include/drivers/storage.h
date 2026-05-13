#ifndef STORAGE_H
#define STORAGE_H

#include <cstdint>

/**
 * @brief Saves a single set of sensor readings to flash using the boot count as the unique ID.
 * @note pm1   => i_%u_p1
 * @note pm2,5 => i_%u_p2
 * @note noise => i_%u_n
 */
void add_to_nvs(uint8_t boot_count, uint8_t pm1, uint8_t pm25, uint16_t noise);


#endif