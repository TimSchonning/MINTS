#include <cstdint>
#include <RadioLib.h>
#include <WiFi.h>
#include <esp_wifi.h>
#include <esp_bt.h>

#include "config.h"
#include "debug_macros.h"
#include "sensor_logic.h"
#include "protocol.h"

void power_down_radios() {
    WiFi.mode(WIFI_OFF);
    btStop();
    esp_wifi_stop();
    esp_bt_controller_disable();
}

bool sleep_particle_sensor() {
    // TODO: set the SET_PIN of the sensor to low.
    // TODO: return success/fail
    return true;
}

bool sleep_noise_sensor() {
    // TODO: set the SET_PIN of the sensor to low.
    // TODO: return success/fail
    return true;
}