#include <stdint.h>
#include <sensor_logic.h>
#include <encode_payload.h>

bool encode_payload(payload_t* payload, ps_result_t* pm_results, ns_result_t* ss_results, uint8_t id) {
    if (!payload || !pm_results || !ss_results || !id) return false;

    payload->id  = id;

    payload->pm10  = pm_results->pm10;
    payload->pm25  = pm_results->pm25;

    payload->noise_peak = ss_results->noise_peak;
    return true;
}