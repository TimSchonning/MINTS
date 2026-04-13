#include <sensor_logic.h>
#include <SPI.h>

void ps_log(uint8_t* sensor_buf, ps_state_t* state, ps_result_t* results, uint16_t duration_ms, uint16_t target_samples) {
    bool is_done = ps_parse(sensor_buf, state, results, duration_ms, target_samples);

    if (is_done) {
        Serial.println(__func__);
        Serial.println("Avg PM1 reading:   " + String(results->pm10));
        Serial.println("Avg PM2.5 reading: " + String(results->pm25));
        Serial.println("");
    }
}

void ns_log(int SENSOR_PIN, ns_state_t* state, ns_result_t* results, uint16_t duration_ms) {
    bool is_done = ns_parse(SENSOR_PIN, state, results, duration_ms);
    
    if (is_done) {
        Serial.println(__func__);
        Serial.println("Peak to peak:      " + String(results->noise_peak));
        Serial.println("");
    }
}