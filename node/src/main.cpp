#include <Seeed_HM330X.h>
#include <WiFi.h>
#include <esp_wifi.h>
#include <esp_bt.h>
#include <SPI.h>
#include <RadioLib.h>

#include "config.h"
#include "debug_macros.h"
#include "encode_payload.h"
#include "sensor_logic.h"
#include "utils.h"

HM330X particle_sensor;
uint8_t     ps_sensor_buf[30];
ps_state_t  ps_state;
ps_result_t ps_result;

ns_state_t  ns_state;
ns_result_t ns_result;

payload_t payload;

SX1276 radio = new Module(PIN_NSS, PIN_DIO0, PIN_NRST, PIN_DIO1);

void setup() {
    power_down_radios();
    setCpuFrequencyMhz(CPU_FREQ_MHZ);
    DEBUG_BEGIN(BAUD);

    //// Node initialisation
    if (needs_initialisation) initialise_node();

    // Initialise sensors
    if (particle_sensor.init()) error_handler(-1, "Particle sensor initialisation failed");
    
    //// Data collection
    sample_noise_sensor();
    if (sleep_noise_sensor()) error_handler(-1, "Failed to put the noise sensor to sleep");

    sample_particle_sensor();
    if (sleep_particle_sensor()) error_handler(-1, "Failed to put the particle sensor to sleep");

    //// Update RTC
    boot_count++;
    
    //// TODO: Power down sensors
    //// updates the payload
    encode_payload(&payload, &ps_result, &ns_result, node_id);
    
    //// send data
    if (buffering_counter <= (BUFFERING_THRESHOLD - 1)) {
        buffering_counter++;
    } else {
        buffering_counter = 0;
        transmit_payload();
    }

    //// Sleep
    DEBUG_PRINTLN("[END]   Entering sleep");
    radio.sleep();
    // calculates the sleep time by subtracting the designated sleep time with the time it took to reach this line
    uint32_t sleep_time_us = (TIME_TO_SLEEP_S * S_TO_uS) - (millis() * 1000UL);
    esp_sleep_enable_timer_wakeup(sleep_time_us);
    esp_deep_sleep_start();
}

void loop() {
    // keep empty
}