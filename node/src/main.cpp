#include <Seeed_HM330X.h>
#include <HM330X.h>
#include <WiFi.h>
#include <esp_wifi.h>
#include <esp_bt.h>
#include <SPI.h>
#include <RadioLib.h>

#include "config.h"
#include "encode_payload.h"
#include "sensor_logic.h"

#define DEBUG_MODE // Comment this to disable debug mode

#ifdef DEBUG_MODE
  #define DEBUG_PRINT(x) Serial.print(x)
  #define DEBUG_PRINTLN(x) Serial.println(x)
  #define DEBUG_BEGIN(x) Serial.begin(x)
#else
  #define DEBUG_PRINT(x)
  #define DEBUG_PRINTLN(x)
  #define DEBUG_BEGIN(x)
#endif

HM330X particle_sensor;
uint8_t     ps_sensor_buf[30];
ps_state_t  ps_state;
ps_result_t ps_results;

ns_state_t  ns_state;
ns_result_t ns_results;

// LoRa config
payload_t payload;

SX1276 radio = new Module(PIN_NSS, PIN_DIO0, PIN_NRST, PIN_DIO1);

void setup() {
    WiFi.mode(WIFI_OFF);
    btStop();
    esp_wifi_stop();
    esp_bt_controller_disable();
    setCpuFrequencyMhz(CPU_FREQ_MHZ);
    
    DEBUG_BEGIN(BAUD); // Dont set the baud before the cpu frequency change
    if (particle_sensor.init()) {
        DEBUG_PRINTLN("[ERROR] PS INIT FAILED");
        #ifdef DEBUG_MODE
            while (1);
        #endif
    }

    // Count of how many times the device has booted, stored in the ESP32s RTC
    boot_count++;

    //// Data collection
    DEBUG_PRINTLN("[START] Particle sensor sampling");
    DEBUG_PRINT("Heating particle sensor for: ");
    DEBUG_PRINTLN(PS_HEAT_UP_TIME * mS_TO_S);
    delay(PS_HEAT_UP_TIME * mS_TO_S);
    
    bool is_done = false;
    while (!is_done) {
        is_done = ps_parse(
            ps_sensor_buf,
            &ps_state,
            &ps_results,
            PS_SAMPLE_TIME_mS - 1,
            PS_TARGET_SAMPLES
        );
        delay(1);
    }

    DEBUG_PRINTLN("[END]   Particle sensor done");
    delay(1 * mS_TO_S);
    DEBUG_PRINTLN("[START] Noise sensor sampling");

    is_done = false;
    while (!is_done) {
        is_done = ns_parse(
            NS_PIN,
            &ns_state,
            &ns_results,
            NS_SAMPLE_TIME_mS - 1
        );
        delay(1);
    }

    DEBUG_PRINTLN("[END]   Noise sensor done");
    //// Power down sensors
    //// send data
    DEBUG_PRINTLN("[START] LoRa transmission");
    encode_payload(&payload, &ps_results, &ns_results);

    int16_t state = radio.begin(FREQUENCY, BANDWIDTH, SPREADING_FACTOR, CODING_RATE, SYNC_WORD, POWER, PREAMBLE_LEN, GAIN);
    if (state == RADIOLIB_ERR_NONE) {
        DEBUG_PRINTLN("[SUCCESS] LoRa radiolib initialisation");
    } else {
        DEBUG_PRINTLN("[ERROR] LoRa radiolib initialisation");
        DEBUG_PRINTLN("[ERROR] Error code: ");
        DEBUG_PRINT(state);
        #ifdef DEBUG_MODE
            while (1);
        #endif
    }

    state = radio.transmit((uint8_t*)&payload, sizeof(payload_t));
    if (state == RADIOLIB_ERR_NONE) {
        DEBUG_PRINTLN("[SUCCESS] LoRa transmission sent");
    } else {
        DEBUG_PRINTLN("[ERROR] LoRa transmission NOT sent");
        DEBUG_PRINTLN("[ERROR] Error code: ");
        DEBUG_PRINT(state);
        #ifdef DEBUG_MODE
            while (1);
        #endif    
    }

    //// Sleep
    DEBUG_PRINTLN("[END]   Entering sleep");
    radio.sleep();
    esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP_S * uS_TO_S);
    esp_deep_sleep_start();
}

void loop() {
    // keep empty
}