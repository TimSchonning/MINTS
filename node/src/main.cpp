#include <Seeed_HM330X.h>
#include <HM330X.h>
#include <WiFi.h>
#include <esp_wifi.h>
#include <esp_bt.h>
#include <SPI.h>

// Config
// ps = particle sensor
// ns = noise sensor
const int NS_PIN =       A0;
const int CPU_FREQ_MHZ = 10;     // Not sure if this will be a const

const uint16_t PS_SAMPLE_TIME =    0;
const uint16_t PS_TARGET_COUNT =   0;
const uint16_t NS_SAMPLE_TIME =    0;

HM330X particle_sensor;
uint8_t ps_sensor_buf[30];     // particle sensor buffer

ps_state_t ps_state;
ps_result_t ps_results;

ns_state_t ns_state;
ns_result_t ns_results;

void setup() {
    Serial.begin(115200);

    setCpuFrequencyMhz(CPU_FREQ_MHZ);
    WiFi.mode(WIFI_OFF);
    btStop();
    esp_wifi_stop();
    esp_bt_controller_disable();

    Serial.println("Serial start");
    if (particle_sensor.init()) {
        Serial.println("PS INIT FAILED");
        while (1);
    }

}

void loop() {

    delay(5000);
}