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

    uint16_t sum_pm10, sum_pm25, sum_pm100;
} pm_avg;

/**
 * @brief Stores the final calculated averages.
 */
typedef struct {
    uint16_t pm10, pm25, pm100;
} pm_res;

/**
 * @brief Stores the running totals and timing state for noise averaging.
 */
typedef struct {
    uint16_t start_time, last_sample_time;
    uint16_t sample_count;
    bool is_active;

    uint16_t sum_ss10;
} ss_avg;

/**
 * @brief Stores the final calculated averages.
 */
typedef struct {
    uint16_t pm10;
} ss_res;

/* Resets the structs */
pm_avg particle_sensor_stats = {0};
ss_avg sound_sensor_stats = {0};

/**
 * @brief  Calculates the average PM concentration.
 * @param  state: the state/running totals.
 * @param  results: the accumulated totals.
 * @param  duration_ms: duration in ms the sampling runs for.
 * @param  target_samples: number of samples to take.
 * @return Success indicator
 */
bool get_all_pm_averages(pm_avg* state, pm_res* results, uint16_t duration_ms, uint16_t target_samples);

/**
 * @brief  Calculates the average PM concentration.
 * @param  state: the state/running totals.
 * @param  results: the accumulated totals.
 * @param  duration_ms: duration in ms the sampling runs for.
 * @param  target_samples: number of samples to take.
 * @return Success indicator
 */
bool get_all_ss_averages(ss_avg* state, ss_res* results, uint16_t duration_ms, uint16_t target_samples);


#endif