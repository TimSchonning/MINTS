#include <Seeed_HM330X.h>
#include <HM330X.h>

uint8_t pm_average(uint8_t count, uint16_t input) {
    uint16_t average_pm = input / count;
    if (average_pm > 255) {
        return 255;
    }
    
    return (uint8_t)average_pm;
}

bool get_all_pm_averages(pm_avg_t* state, pm_res_t* results, uint16_t duration_ms, uint16_t target_samples) {
    uint16_t sample_interval = duration_ms / target_samples;
    uint32_t now = millis();
    
    if (!state->is_active) {
        memset(state, 0, sizeof(pm_avg));
        state->start_time = now;
        state->is_active = true;
    }

    /* Sums the readings over the given time period */
    if (now - state->last_sample_time >= sample_interval && state->sample_count < target_samples) {
        if (sensor.read_sensor_value(sensor_buf, 29) == NO_ERROR) {

            /* 
             * @brief HM330X Sensor Data Buffer Mapping (29 Bytes)
                * * The sensor transmits a 29-byte packet via I2C. Data is sent as Big-Endian 
                * (High Byte followed by Low Byte) for each 16-bit measurement.
                * | Index | Name          | Description                                    |
                * | 10-11 | PM1.0 (ATM)   | PM1.0 Atmospheric environment (ug/m3)          |
                * | 12-13 | PM2.5 (ATM)   | PM2.5 Atmospheric environment (ug/m3)          |
                * | 14-15 | PM10  (ATM)   | PM10  Atmospheric environment (ug/m3)          |
            */
            
            state->sum_pm10  += ((uint16_t)sensor_buf[10] << 8) | sensor_buf[11];
            state->sum_pm25  += ((uint16_t)sensor_buf[12] << 8) | sensor_buf[13];

            state->sample_count++;
            state->last_sample_time = now;
        }
    }

    /* Calculates the averages */
    if (now - state->startTime >= duration_ms) {
        uint8_t n = state->sample_count;
        if (n > 0) {
            results->pm10  = pm_average(n, state->sum_pm10);
            results->pm25  = pm_average(n, state->sum_pm25);
        }
        state->is_active = false;
        return true;
    }
    
    return false;
}

bool get_all_ss_averages(ss_avg_t* state, ss_res_t* results, uint16_t duration_ms, uint16_t target_samples) {
    return true;
}