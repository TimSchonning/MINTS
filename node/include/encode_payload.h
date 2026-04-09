#ifndef ENCODE_PAYLOAD_H
#define ENCODE_PAYLOAD_H

#include <stdint.h>
#include <encode_payload.h>


/**
 * @brief Stores the results as a sendable LoRa payload.
 */
typedef struct {
    uint16_t sum_pm10, sum_pm25, sum_pm100;
    uint16_t noise;
} payload;

/**
 * @brief  Returns the encoded payload.
 * @param  payload: the payload.
 * @param  pm_results: PM results.
 * @param  ss_results: Sound sensor results.
 * @return Success indicator
 */
bool encode_payload(payload* payload, pm_res* pm_results, ss_res* ss_results);

#endif