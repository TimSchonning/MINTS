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
    power_down_radios();
    setCpuFrequencyMhz(CPU_FREQ_MHZ);
    DEBUG_BEGIN(BAUD);
    
    if (particle_sensor.init()) error_handler(-1, "Particle sensor initialisation failed");
    boot_count++; // Count of how many times the device has booted/woken from sleep, stored in the ESP32s RTC

    //// Data collection
    sample_particle_sensor();
    delay(1 * mS_TO_S);
    sample_noise_sensor();
    
    //// TODO: Power down sensors
    //// send data
    transmit_payload();

    //// Sleep
    DEBUG_PRINTLN("[END]   Entering sleep");
    radio.sleep();
    esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP_S * uS_TO_S);
    esp_deep_sleep_start();
}

void loop() {
    // keep empty
}

void error_handler(int16_t state, const char* message) {
    if (state != RADIOLIB_ERR_NONE) {
        DEBUG_PRINT("[ERROR] ");
        DEBUG_PRINT(message);
        DEBUG_PRINT(" Code: ");
        DEBUG_PRINTLN(state);
        #ifdef DEBUG_MODE
            while (1); 
        #endif
    }
}

void power_down_radios() {
    WiFi.mode(WIFI_OFF);
    btStop();
    esp_wifi_stop();
    esp_bt_controller_disable();
}