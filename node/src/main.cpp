#include <Seeed_HM330X.h>
#include <HM330X.h>
#include <WiFi.h>
#include <esp_wifi.h>
#include <esp_bt.h>

/* Sound sensor */

/* HM330X sensor */
HM330X sensor;
uint8_t sensor_buf[30];
pm_avg ps_state;
pm_res ps_results;


void setup() {
    /* Remember to solder off the LED */
    setCpuFrequencyMhz(10);     /* Might be too low */
    WiFi.mode(WIFI_OFF);
    btStop();
    esp_wifi_stop();
    esp_bt_controller_disable();

}

void loop() {

    delay(5000);
}