#include <Seeed_HM330X.h>
#include <HM330X.h>
#include <WiFi.h>
#include <esp_wifi.h>
#include <esp_bt.h>
#include <SPI.h>
#include <RadioLib.h>

#include "encode_payload.h"
#include "sensor_logic.h"

#define DEBUG_MODE // Comment this to disable debug mode

#ifdef DEBUG_MODE
  #define DEBUG_FPRINT(x) Serial.print(F(x))
  #define DEBUG_FPRINTLN(x) Serial.println(F(x))
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
        DEBUG_FPRINTLN("[ERROR] PS INIT FAILED");
        #ifdef DEBUG_MODE
            while (1);
        #endif
    }

    //// Data collection
    DEBUG_FPRINTLN("[START] Particle sensor sampling");
    DEBUG_FPRINT("Heating particle sensor for: ");
    DEBUG_FPRINTLN(PS_HEAT_UP_TIME * mS_TO_S);
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

    DEBUG_FPRINTLN("[END]   Particle sensor done");
    delay(1 * mS_TO_S);
    DEBUG_FPRINTLN("[START] Noise sensor sampling");

    is_done = false;
    while (!is_done) {
        is_done = ns_parse(
            NS_PIN,
            &ns_state,
            &ns_results,
            NS_SAMPLE_TIME_mS - 1
        )
        delay(1);
    }

    DEBUG_FPRINTLN("[END]   Noise sensor done");
    //// Power down sensors
    //// send data
    DEBUG_FPRINTLN("[START] LoRa transmission");
    encode_payload(&payload, &ps_results, &ns_results);

    int state = radio.begin(FREQUENCY, BANDWIDTH, SPREADING_FACTOR, CODING_RATE, SYNC_WORD, POWER, PREAMBLE_LEN, GAIN);
    if (state == RADIOLIB_ERR_NONE) {
        DEBUG_FPRINTLN("[SUCCESS] LoRa radiolib initialisation");
    } else {
        DEBUG_FPRINTLN("[ERROR] LoRa radiolib initialisation");
        DEBUG_FPRINTLN("[ERROR] Error code: ");
        DEBUG_FPRINT(state);
        #ifdef DEBUG_MODE
            while (1);
        #endif
    }
    radio.startTransmit(payload);
    DEBUG_FPRINTLN("[END]   LoRa transmission sent");

    //// Sleep
    DEBUG_FPRINTLN("[END]   Entering sleep");

}

void loop() {
    // keep empty
}