#include <Seeed_HM330X.h>
#include <HM330X.h>
#include <sensor_logic.h>

#include "debug_macros.h"
#include "utils.h"

uint8_t pm_average(uint8_t count, uint16_t input) {
    uint16_t average_pm = input / count;
    if (average_pm > 255) {
        return 255;
    }
    
    return (uint8_t)average_pm;
}

bool ps_parse(uint8_t* sensor_buf, ps_state_t* state, ps_result_t* results, uint16_t duration_ms, uint16_t target_samples) {
    uint16_t sample_interval = duration_ms / target_samples;
    uint32_t now = millis();
    
    if (!state->is_active) {
        memset(state, 0, sizeof(ps_state_t));
        state->start_time = now;
        state->is_active = true;
    }

    /* Sums the readings over the given time period */
    if (state->sample_count < target_samples) {
        if (now - state->last_sample_time >= sample_interval) {
            if (sensor.read_sensor_value(sensor_buf, 29) == NO_ERROR) {

                state->sum_pm10  += ((uint16_t)sensor_buf[10] << 8) | sensor_buf[11];
                state->sum_pm25  += ((uint16_t)sensor_buf[12] << 8) | sensor_buf[13];

                state->sample_count++;
                state->last_sample_time = now;
            }
        }
        return false;
    }

    /* Calculates the averages */
    results->pm10 = pm_average(state->sample_count, state->sum_pm10);
    results->pm25 = pm_average(state->sample_count, state->sum_pm25);
    state->is_active = false;

    #ifdef DEBUG_MODE
        Serial.println("Avg PM1 reading:   " + String(results->pm10));
        Serial.println("Avg PM2.5 reading: " + String(results->pm25));
        Serial.println("");
    #endif

    return true;
}

bool ns_parse(int SENSOR_PIN, ns_state_t* state, ns_result_t* results, uint16_t duration_ms) {
    uint32_t now = millis();
    
    if (!state->is_active) {
        memset(state, 0, sizeof(ns_state_t));
        state->start_time = now;
        state->is_active = true;
        state->signal_max = 0;
        state->signal_min = 1024;
    }

    /* Sums the readings over the given time period */
    if (now - state->start_time < duration_ms) {
        uint16_t sample = analogRead(SENSOR_PIN);

        if (sample < 1024) {
            if (sample > state->signal_max) state->signal_max = sample;
            if (sample < state->signal_min) state->signal_min = sample;
        }

        return false;
    }

    if (state->signal_max <= state->signal_min) {
        /* ie, no readings were made */
        results->noise_peak = 0;
    } else {
        results->noise_peak = state->signal_max - state->signal_min;
    }

    state->is_active = false;

    #ifdef DEBUG_MODE
        Serial.println(__func__);
        Serial.println("Peak to peak:      " + String(results->noise_peak));
        Serial.println("");
    #endif

    return true;
}

void sample_particle_sensor() {
    DEBUG_PRINTLN("[START] Particle sensor sampling");
    DEBUG_PRINT("Heating particle sensor for: ");
    DEBUG_PRINTLN(PS_HEAT_UP_TIME * mS_TO_S);

    delay(PS_HEAT_UP_TIME * mS_TO_S);
    bool is_done = false;
    while (!ps_parse(ps_sensor_buf, &ps_state, &ps_results, PS_SAMPLE_TIME_mS - 1, PS_TARGET_SAMPLES)) {
        delay(1);
    }
}

void sample_noise_sensor() {
    DEBUG_PRINTLN("[START] Noise sensor sampling");

    bool is_done = false;
    while (!ns_parse(NS_PIN, &ns_state, &ns_results, NS_SAMPLE_TIME_mS - 1)) {
        delay(1);
    }
}