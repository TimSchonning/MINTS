#include <stdint.h>
#include <sensor_logic.h>
#include <encode_payload.h>
#include <RadioLib.h>

#include "config.h"
#include "debug_macros.h"
#include "encode_payload.h"
#include "sensor_logic.h"
#include "utils.h"

bool encode_payload(payload_t* payload, ps_result_t* ps_result, ns_result_t* ns_result, uint8_t id) {
    if (!payload || !pm_results || !ss_results || !id) return false;

    payload->id  = id;

    payload->pm10  = pm_results->pm10;
    payload->pm25  = pm_results->pm25;

    payload->noise_peak = ns_result->noise_peak;
    return true;
}

void transmit_payload() {
    DEBUG_PRINTLN("[START] LoRa transmission");
    encode_payload(&payload, &ps_results, &ns_results);

    int16_t state = radio.begin(FREQUENCY, BANDWIDTH, SPREADING_FACTOR, CODING_RATE, SYNC_WORD, POWER, PREAMBLE_LEN, GAIN);
    error_handler(state, "LoRa initialisation");

    state = radio.transmit((uint8_t*)&payload, sizeof(payload_t));
    error_handler(state, "LoRa transmission");

    DEBUG_PRINTLN("[SUCCESS] LoRa transmission completed");
}