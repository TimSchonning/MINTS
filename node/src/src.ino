#include <Seeed_HM330X.h>
#include <WiFi.h>
#include <esp_wifi.h>
#include <esp_bt.h>
#include <SPI.h>
#include <RadioLib.h>
#include <cstdlib>

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

RTC_DATA_ATTR payload_t payload;

SX1262 radio = new Module(PIN_NSS, PIN_DIO0, PIN_NRST, PIN_DIO1);

void setup() {
    power_down_radios();
    delay(1000);
    
    DEBUG_BEGIN(BAUD);
    delay(1000);
    
    DEBUG_PRINTLN("[START]");
    
    if (particle_sensor.init())  error_handler(-1, true, PS_INIT_ERROR,  "Particle sensor initialisation failed");
    
    sample_noise_sensor();
    sample_particle_sensor();
    if (!sleep_particle_sensor()) error_handler(-1, true, PS_SLEEP_ERROR, "Failed to put the particle sensor to sleep");

    boot_count++;
    
    encode_payload(&payload, &ps_result, &ns_result);
    
    //// send data
    if (buffering_counter < (BUFFERING_THRESHOLD - 1)) {
        buffering_counter++;
    } else {
        srand((unsigned int)time(NULL) + node_id);
        delay((rand() % MAX_TX_DELAY_S) * S_TO_mS);

        DEBUG_PRINTLN("[TRANSMIT] Transmitting payload");
        transmit_payload(&payload);
        buffering_counter = 0;
        memset(&payload, 0, sizeof(payload_t));
    }

    radio.sleep();

    sleep_time_ms = calculate_sleep_time();
    DEBUG_PRINT  ("[END]      Entering sleep for: ");
    DEBUG_PRINT  (sleep_time_ms);
    DEBUG_PRINTLN(" ms");
    
    esp_sleep_enable_timer_wakeup(sleep_time_ms);
    esp_deep_sleep_start();
}

void loop() {
    // keep empty
}