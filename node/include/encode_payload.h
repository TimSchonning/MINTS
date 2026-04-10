#ifndef ENCODE_PAYLOAD_H
#define ENCODE_PAYLOAD_H

#include <stdint.h>
#include <encode_payload.h>


/**
 * @brief Stores the results as a sendable LoRa payload.
 */
typedef struct {
    uint8_t id;
    uint8_t sum_pm10, sum_pm25;
    uint16_t noise_peak;
} payload_t;

/**
 * @brief  Returns the encoded payload.
 * @param  payload: the payload.
 * @param  pm_results: PM results.
 * @param  ss_results: Sound sensor results.
 * @return Success indicator
 */
bool encode_payload(payload_t* payload, pm_res_t* pm_results, ss_res_t* ss_results);

#endif