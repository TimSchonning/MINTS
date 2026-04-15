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
 * @param  ps_result: PM results.
 * @param  ns_result: Sound sensor results.
 * @return Success indicator
 */
bool encode_payload(payload_t* payload, ps_result_t* ps_result, ns_result_t* ns_result);

/**
 * @brief High-level function.
 * Initializes radio, encodes current data, and transmits via LoRa.
 */
void transmit_payload();

#endif