#ifndef ENCODE_PAYLOAD_H
#define ENCODE_PAYLOAD_H

#include <stdint.h>
#include <encode_payload.h>


/**
 * @brief Stores the results as a sendable LoRa payload.
 */
typedef struct {
    uint8_t id;
    uint8_t pm10, pm25;
    uint16_t noise_peak;
} payload_t;

/**
 * @brief  Returns the encoded payload.
 * @param  payload: the payload.
 * @param  pm_results: PM results.
 * @param  ns_results: Sound sensor results.
 * @return Success indicator
 */
bool encode_payload(payload_t* payload, ps_result_t* pm_results, ns_result_t* ns_results);

#endif