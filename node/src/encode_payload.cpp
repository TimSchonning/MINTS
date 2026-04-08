#include <stdint.h>
#include <sensor_logic.h>
#include <encode_payload.h>

bool encode_payload(payload* payload, pm_res* pm_results, ss_res* ss_results) {
    if (!payload || !pm_results || !ss_results) return false;

    payload->sum_pm10  = pm_results->pm10;
    payload->sum_pm25  = pm_results->pm25;
    payload->sum_pm100 = pm_results->pm100;

    payload->noise = ss_results->noise;
    return true;
}