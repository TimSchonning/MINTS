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