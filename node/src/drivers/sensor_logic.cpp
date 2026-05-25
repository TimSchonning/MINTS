#include "master.h"

extern HM330X      particle_sensor;
extern uint8_t     ps_sensor_buf[];
extern ps_state_t  ps_state;
extern ps_result_t ps_result;

extern ns_state_t  ns_state;
extern ns_result_t ns_result;

void ps_parse() {
    memset(result, 0, sizeof(ps_result_t));

    uint16_t error_code = particle_sensor.read_sensor_value(ps_sensor_buf, 29);

    if (error_code == NO_ERROR) {
        ps_result->pm1  = ((uint16_t)ps_sensor_buf[10] << 8) | ps_sensor_buf[11];
        ps_result->pm25 = ((uint16_t)ps_sensor_buf[12] << 8) | ps_sensor_buf[13];

        DEBUG_PRINT("Measured PM1  : "); DEBUG_PRINTLN(ps_result->pm1);
        DEBUG_PRINT("Measured PM2.5: "); DEBUG_PRINTLN(ps_result->pm25);

    } else {
        DEBUG_PRINT("[ERROR]    read_sensor_value(sensor_buf, 29) returned error: "); DEBUG_PRINTLN(error_code);
        DEBUG_PRINTLN("[INFO]    Writing 254 to both PM values");
        ps_result->pm1  = 254;
        ps_result->pm25 = 254;
    }
}

void sample_particle_sensor() {
    wake_particle_sensor();
    delay(PS_HEAT_UP_TIME_S * S_TO_mS);

    ps_parse();
}

bool ns_parse(int SENSOR_PIN, ns_state_t* state, ns_result_t* result, uint16_t duration_ms) {
    uint32_t now = millis();
    
    if (!state->is_active) {
        state->start_time = now;
        state->signal_max = 0;
        state->signal_min = 4096;
        state->is_active  = true;
    }

    // 1. Sums the readings over the given time period
    if (now - state->start_time < duration_ms) {
        uint16_t sample = analogRead(SENSOR_PIN);

        if (sample < 4096) {
            if (sample > state->signal_max) state->signal_max = sample;
            if (sample < state->signal_min) state->signal_min = sample;
        }

        return false;
    }

    // 2. Window finished
    // Adds the peak-to-peak value to the accumulator
    if (state->signal_max <= state->signal_min) {
        DEBUG_PRINTLN("[ERROR]    ns_parse call failed to detect any sound");
        // TODO: this requires some better handling
        state->total_noise_peak += 0;
    } else {
        uint16_t noise_peak = state->signal_max - state->signal_min
        DEBUG_PRINT("Measured noise peak: "); DEBUG_PRINTLN(noise_peak);
        state->total_noise_peak += noise_peak;
    }

    state->sample_count++;

    // 3. Calculates the total average
    if (state->sample_count >= NS_TARGET_SAMPLES) {
        result->noise_avg = state->total_noise_peak / NS_TARGET_SAMPLES;

        // resets the state
        state->total_noise_peak = 0;
        state->sample_count = 0;
    }

    state->is_active = false;

    return true;
}

void sample_noise_sensor() {
    DEBUG_PRINTLN("[START]    Noise sensor sampling");

    // state safe guards
    ns_state.is_active        = false; 
    ns_state.total_noise_peak = 0;
    ns_state.sample_count     = 0;

    for (int i = 0; i < NS_TARGET_SAMPLES; i++) {
        while (!ns_parse(NS_PIN, &ns_state, &ns_result, NS_SAMPLE_WINDOW_mS)) {
            //delay(1) Might cause side effects if enabled
        }
        delay(NS_SAMPLE_DELAY_ms);
    }
}