#include <cstdint>
#ifndef HM330X_LOGIC_H
#define HM330X_LOGIC_H

typedef struct {
    uint16_t start_time, last_sample_time;
    uint16_t sample_count;
    bool is_active;

    uint16_t sum_pm10, sum_pm25, sum_pm100;
} pm_avg;

typedef struct {
    uint16_t pm10, pm25, pm100;
} pm_res;

typedef struct {
    uint16_t start_time, last_sample_time;
    uint16_t sample_count;
    bool is_active;

    uint16_t sum_ss10;
} ss_avg;

typedef struct {
    uint16_t pm10;
} ss_res;

pm_avg particle_sensor_stats = {0};
ss_avg sound_sensor_stats = {0};