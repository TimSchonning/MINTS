#include <sensor_logic.h>
#include <SPI.h>

void log_ps(uint8_t* sensor_buf, pm_avg_t* state, pm_res_t* results, uint16_t duration_ms, uint16_t target_samples) {
    bool is_done = get_all_pm_averages(sensor_buf, state, results, duration_ms, target_samples);

    if (is_done) {
        Serial.println(__func__);
        Serial.println("Avg PM1 reading:   " + String(results->pm10));
        Serial.println("Avg PM2.5 reading: " + String(results->pm25));
        Serial.println("");
    }
}

void log_ns(int SENSOR_PIN, ss_avg_t* state, ss_res_t* results, uint16_t duration_ms) {
    bool is_done = get_ss_averages(SENSOR_PIN, state, results, duration_ms);
    
    if (is_done) {
        Serial.println(__func__);
        Serial.println("Peak to peak:      " + String(results->noise_peak));
        Serial.println("");
    }
}