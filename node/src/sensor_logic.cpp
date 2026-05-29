#include <Seeed_HM330X.h>

#include "config.h"
#include "debug_macros.h"
#include "sensor_logic.h"
#include "utils.h"

extern HM330X particle_sensor;
extern uint8_t ps_sensor_buf[];
extern ps_state_t ps_state;
extern ps_result_t ps_result;

extern ns_state_t ns_state;
extern ns_result_t ns_result;

static uint8_t pm_average(uint8_t count, uint16_t input) {
    uint16_t average_pm = (input + (count / 2)) / count;
    if (average_pm > 255) {
        return 255;
    }
    
    return (uint8_t)average_pm;
}

bool ps_parse(uint8_t* sensor_buf, ps_state_t* state, ps_result_t* result, uint16_t duration_ms, uint16_t target_samples) {
    // uint16_t sample_interval = duration_ms / target_samples;
    uint32_t now = millis();
    
    if (!state->is_active) {
        memset(state, 0, sizeof(ps_state_t));
        state->start_time = now;
        state->is_active = true;
    }

    if (target_samples != 1) {
        DEBUG_PRINTLN("[WARNING] Target samples inside ps_parse != 1. Undefined behaviour.");
    }

   // debug_print_raw_ps_data();

    /* Sums the readings over the given time period */
    // if (state->sample_count < target_samples) {
    //     if (now - state->last_sample_time >= sample_interval) {
    //         if (particle_sensor.read_sensor_value(sensor_buf, 29) == NO_ERROR) {

    //             state->sum_pm1  += ((uint16_t)sensor_buf[10] << 8) | sensor_buf[11];
    //             state->sum_pm25  += ((uint16_t)sensor_buf[12] << 8) | sensor_buf[13];

    //             DEBUG_PRINTLN("PM1 SUM VALUE:  ");
    //             DEBUG_PRINT(state->sum_pm1);
    //             DEBUG_PRINTLN("PM25 SUM VALUE: ");
    //             DEBUG_PRINT(state->sum_pm25);

    //             state->sample_count++;
    //             state->last_sample_time = now;
    //         } else {
    //             DEBUG_PRINTLN("[ERROR] particle_sensor.read_sensor_value(sensor_buf, 29) returned an error");
    //         }
    //     }
    //     return false;
    // }

    // /* Calculates the averages */
    // result->pm1 = pm_average(state->sample_count, state->sum_pm1);
    // result->pm25 = pm_average(state->sample_count, state->sum_pm25);
    // state->is_active = false;

    uint16_t error_code = particle_sensor.read_sensor_value(sensor_buf, 29);

    if (error_code == NO_ERROR) {

        result->pm1  += ((uint16_t)sensor_buf[10] << 8) | sensor_buf[11];
        result->pm25  += ((uint16_t)sensor_buf[12] << 8) | sensor_buf[13];

        DEBUG_PRINT("PM1 SUM VALUE:  ");
        DEBUG_PRINTLN( result->pm1);
        DEBUG_PRINT("PM25 SUM VALUE: ");
        DEBUG_PRINTLN( result->pm25);

    } else {
        DEBUG_PRINT("[ERROR] particle_sensor.read_sensor_value(sensor_buf, 29) returned an error");
        DEBUG_PRINTLN(error_code);
        DEBUG_PRINTLN("Writing 255 to both PM values");
        result->pm1  += 255;
        result->pm25 += 255;
    }

    state->is_active = false;

    return true;
}

float db_from_peak_to_peak(int peak_to_peak) {
    // Converts the peak-to-peak value into dB using a function fitted using manual calibration. 
    // The functions and calibration data used for this can be found in experiments/results/sound_sensor_calibration
    // This works pretty well in between 30-70 dB, generally being +-5 dB.
    // The largest discrepancies are around 50 dB (see CalibrationPlot.png).
    float a = -13.838529669252635;
    float b = 10.849420757521935;
    float db_approx = a+b*log((float)peak_to_peak);
    return db_approx;
}

uint16_t sample_approximate_db_reading(int SENSOR_PIN) {
    unsigned long startMillis = millis();

    long signalMin = ANALOG_MAX;
    long signalMax = 0;

    while (millis() - startMillis < NS_SAMPLE_DURATION_mS) {


        int sample = analogRead(SENSOR_PIN);

        if (sample < signalMin) {
            signalMin = sample;
        }

        if (sample > signalMax) {
            signalMax = sample;
        }
    }

    int peakToPeak = signalMax - signalMin;
    uint16_t db_approx = round(db_from_peak_to_peak(peakToPeak));
    #ifdef DEBUG_MODE
        Serial.print("Sampled approximated dB: ");
        Serial.println(db_approx);
    #endif
  
    return db_approx;
}

bool ns_parse(int SENSOR_PIN, ns_state_t* state, ns_result_t* result, uint16_t duration_ms) {
    uint32_t now = millis();
    
    if (!state->is_active) {
        state->start_time = now;
        state->db_sample = 0;
        state->is_active  = true;
    }

    /* Sums the readings over the given time period */
    if (now - state->start_time < duration_ms) {
        uint16_t db_sample = sample_approximate_db_reading(SENSOR_PIN);
        state->db_sample = db_sample;

        return false;
    }

    state->total_noise_peak += state->db_sample;
    state->sample_count++;

    #ifdef DEBUG_MODE
        Serial.println(__func__);
        Serial.println("Total noise peak (dB):      " + String(state->total_noise_peak));
        Serial.println("");
    #endif

    // Calculates the total average
    if (state->sample_count >= NS_TARGET_SAMPLES) {
        result->noise_avg = state->total_noise_peak / NS_TARGET_SAMPLES;
        #ifdef DEBUG_MODE
            Serial.println("Average noise level (dB):      " + String(result->noise_avg));
            Serial.println("");
        #endif

        // resets the state
        state->total_noise_peak = 0;
        state->sample_count = 0;
    }

    state->is_active = false;

    return true;
}

void sample_particle_sensor() {
    DEBUG_PRINTLN("[START] Particle sensor sampling");
    DEBUG_PRINT("Heating particle sensor for (ms): ");
    DEBUG_PRINTLN(PS_HEAT_UP_TIME_S * S_TO_mS);

    wake_particle_sensor();

    delay(PS_HEAT_UP_TIME_S * S_TO_mS);

    while (!ps_parse(ps_sensor_buf, &ps_state, &ps_result, PS_SAMPLE_TIME_mS - 1, PS_TARGET_SAMPLES)) {
        // 1ms delay safe guard
        delay(1);
    }
}

void sample_noise_sensor() {
    DEBUG_PRINTLN("[START] Noise sensor sampling");

    // state safe guards
    ns_state.is_active = false; 
    ns_state.total_noise_peak = 0;
    ns_state.sample_count = 0;

    for (int i = 0; i < NS_TARGET_SAMPLES; i++) {
        while (!ns_parse(NS_PIN, &ns_state, &ns_result, NS_SAMPLE_WINDOW_mS)) {
            //delay(1) Might cause side effects if enabled
        }
        delay(NS_SAMPLE_DELAY_ms);
    }
}