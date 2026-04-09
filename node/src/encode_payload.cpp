#include <stdint.h>
#include <sensor_logic.h>
#include <encode_payload.h>

bool encode_payload(payload_t* payload, pm_res_t* pm_results, ss_res_t* ss_results, uint8_t id) {
    if (!payload || !pm_results || !ss_results || !id) return false;

    payload->id  = id;

    payload->sum_pm10  = pm_results->pm10;
    payload->sum_pm25  = pm_results->pm25;

    payload->noise = ss_results->noise;
    return true;
}