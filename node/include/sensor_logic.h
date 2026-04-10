#ifndef SENSOR_LOGIC_H
#define SENSOR_LOGIC_H

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

/**
 * @brief Stores the running totals and timing state for PM averaging.
 */
typedef struct {
    uint32_t start_time, last_sample_time;
    uint8_t sample_count;
    bool is_active;

    uint16_t sum_pm10, sum_pm25;
} ps_state_t;

/**
 * @brief Stores the final calculated averages.
 */
typedef struct {
    uint8_t pm10, pm25;
} ps_result_t;

/**
 * @brief Stores the running totals and timing state for noise averaging.
 */
typedef struct {
    uint32_t start_time;
    uint16_t signal_max, signal_min;

    bool is_active;
} ns_state_t;

/**
 * @brief Stores the final calculated peak to peak amplitude.
 */
typedef struct {
    uint16_t noise_peak;
} ns_result_t;

/* Resets the structs */
ps_state_t particle_sensor_stats = {0};
ns_state_t sound_sensor_stats = {0};

/**
 * @brief  Calculates the average PM concentration.
 * @param  sensor_buf: Buffer containing the readings of the sensor. (uint8_t sensor_buf[30];)
 * @param  state: the state/running totals.
 * @param  results: the accumulated totals.
 * @param  duration_ms: duration in ms the sampling runs for.
 * @param  target_samples: number of samples to take.
 * @return is done
 * 
 * @note Sensor needs to heat up for about 30s
 * @note
 * HM330X Sensor Data Buffer Mapping (29 Bytes).
 * The sensor transmits a 29-byte packet via I2C. Data is sent as Big-Endian 
 * (High Byte followed by Low Byte) for each 16-bit measurement.
 * @note| Index | Name          | Description                                    |
 * @note| 10-11 | PM1.0 (ATM)   | PM1.0 Atmospheric environment (ug/m3)          |
 * @note| 12-13 | PM2.5 (ATM)   | PM2.5 Atmospheric environment (ug/m3)          |
 * @note| 14-15 | PM10  (ATM)   | PM10  Atmospheric environment (ug/m3)          |
 */
bool ps_parse(uint8_t* sensor_buf, ps_state_t* state, ps_result_t* results, uint16_t duration_ms, uint16_t target_samples);

/**
 * @brief  Calculates the peak to peak sound amplitude
 * @param  SENSOR_PIN: Analog data output pin.
 * @param  state: the state.
 * @param  results: the result (peak volume).
 * @param  duration_ms: duration in ms the sampling runs for.
 * @return is done
 * 
 * @note Avoid any delay() when using this function since it depends heavily on being called at a high sample rate
 * @note Hard-coded to an ADC which returns a 10 bit value. Change if possible/needed
 */
bool ns_parse(int SENSOR_PIN, ns_state_t* state, ns_result_t* results, uint16_t duration_ms);

#endif