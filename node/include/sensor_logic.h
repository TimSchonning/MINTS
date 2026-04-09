#ifndef SENSOR_LOGIC_H
#define SENSOR_LOGIC_H

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

/**
 * @brief Stores the running totals and timing state for PM averaging.
 */
typedef struct {
    uint16_t start_time, last_sample_time;
    uint16_t sample_count;
    bool is_active;

    uint8_t sum_pm10, sum_pm25;
} pm_avg_t;

/**
 * @brief Stores the final calculated averages.
 */
typedef struct {
    uint8_t pm10, pm25;
} pm_res_t;

/**
 * @brief Stores the running totals and timing state for noise averaging.
 */
typedef struct {
    uint16_t start_time, last_sample_time;
    uint16_t sample_count;
    bool is_active;

    uint16_t sum_ss;
} ss_avg_t;

/**
 * @brief Stores the final calculated averages.
 */
typedef struct {
    uint16_t noise;
} ss_res_t;

/* Resets the structs */
pm_avg_t particle_sensor_stats = {0};
ss_avg_t sound_sensor_stats = {0};

/**
 * @brief  Calculates the average PM concentration.
 * @param  state: the state/running totals.
 * @param  results: the accumulated totals.
 * @param  duration_ms: duration in ms the sampling runs for.
 * @param  target_samples: number of samples to take.
 * @return Success indicator
 */
bool get_all_pm_averages(pm_avg_t* state, pm_res_t* results, uint16_t duration_ms, uint16_t target_samples);

/**
 * @brief  Calculates the average PM concentration.
 * @param  state: the state/running totals.
 * @param  results: the accumulated totals.
 * @param  duration_ms: duration in ms the sampling runs for.
 * @param  target_samples: number of samples to take.
 * @return Success indicator
 */
bool get_all_ss_averages(pm_avg_t* state, pm_res_t* results, uint16_t duration_ms, uint16_t target_samples);

#endif