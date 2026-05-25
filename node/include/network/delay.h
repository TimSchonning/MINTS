#ifndef DELAY_H
#define DELAY_H

#include <cstdint>
#include "sensor_logic.h"
#include "protocol.h"

/**
 * @brief  Delays execution between 0 and max_delay seconds.
 * @param  max_delay: Max amount of delay.
 */
void random_tx_delay(uint16_t max_delay);

#endif