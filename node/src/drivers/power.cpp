#include <cstdint>
#include <stdio.h>
#include <RadioLib.h>
#include <math.h>
#include <Preferences.h>
#include <WiFi.h>
#include <esp_wifi.h>
#include <esp_bt.h>

#include "config.h"
#include "debug_macros.h"
#include "sensor_logic.h"
#include "utils.h"
#include "protocol.h"

Preferences prefs;
extern SX1262 radio;

void power_down_radios() {
    WiFi.mode(WIFI_OFF);
    btStop();
    esp_wifi_stop();
    esp_bt_controller_disable();
}

bool sleep_particle_sensor() {
    digitalWrite(PS_SET_PIN, LOW); 
    return true;
}

bool wake_particle_sensor() {
    pinMode(PS_SET_PIN, OUTPUT);
    digitalWrite(PS_SET_PIN, HIGH);
    return true;
}

void calculate_sleep_time() {
    uint32_t time_awake      = millis() * 1000UL;
    uint32_t wakeup_interval = WAKEUP_INTERVAL_S * S_TO_uS;
    uint32_t sleep_time      = 900 * S_TO_uS;  // default value
    
    if (wakeup_interval > time_awake) {
        sleep_time = wakeup_interval - time_awake;
    } else {
        error_handler(-1, true, SLEEPTIME_ERROR, "wakeup interval too low (underflow). Defaulting the sleep time.");
    }
}
