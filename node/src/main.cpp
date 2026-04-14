#include <Seeed_HM330X.h>
#include <HM330X.h>
#include <WiFi.h>
#include <esp_wifi.h>
#include <esp_bt.h>
#include <SPI.h>

#include "encode_payload.h"
#include "sensor_logic.h"

// Comment this to disable debug mode
#define DEBUG_MODE 

#ifdef DEBUG_MODE
  #define DEBUG_PRINT(x) Serial.print(x)
  #define DEBUG_PRINTLN(x) Serial.println(x)
  #define DEBUG_BEGIN(x) Serial.begin(x)
#else
  #define DEBUG_PRINT(x)
  #define DEBUG_PRINTLN(x)
  #define DEBUG_BEGIN(x)
#endif

// Config
// ps = particle sensor
// ns = noise sensor
const uint8_t NS_PIN =       0;
const int CPU_FREQ_MHZ =     10;     // Not sure if this will be a const

const uint32_t uS_TO_S =          1000000;
const uint16_t PS_SAMPLE_TIME_S = 0;
const uint16_t PS_TARGET_COUNT =  0;
const uint32_t BAUD =             115200;

const uint16_t NS_SAMPLE_TIME =    0;

HM330X particle_sensor;
uint8_t ps_sensor_buf[30];     // particle sensor buffer

ps_state_t  ps_state;
ps_result_t ps_results;

ns_state_t  ns_state;
ns_result_t ns_results;

void setup() {
    WiFi.mode(WIFI_OFF);
    btStop();
    esp_wifi_stop();
    esp_bt_controller_disable();
    
    setCpuFrequencyMhz(CPU_FREQ_MHZ);
    
    // Dont set the baud before the cpu frequency change
    Serial.begin(BAUD);
    Serial.println("Serial start");
    if (particle_sensor.init()) {
        Serial.println("PS INIT FAILED");
        while (1);
    }

    // 3. COLLECT DATA
    // readParticleSensor();
    // readNoiseSensor();

    // 4. POWER DOWN PERIPHERALS
    // If your sensors have an 'enable' pin, pull it LOW here
    
    // 5. SEND DATA
    // (Turn on WiFi briefly, send, then turn off)

    // 6. CONFIGURE & START SLEEP

}

void loop() {
    // keep empty
}