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

bool error_handler(int16_t state, bool inform_gateway, uint8_t error_code, const char* message) {
    // RADIOLIB_ERR_NONE is def. as 0;
    if (state != RADIOLIB_ERR_NONE) {
        DEBUG_PRINT("[ERROR] ");
        DEBUG_PRINT(message);
        DEBUG_PRINT(" Code: ");
        DEBUG_PRINTLN(state);
    
        if (inform_gateway) {
            int16_t state = radio.begin(FREQUENCY, BANDWIDTH, SPREADING_FACTOR, CODING_RATE, SYNC_WORD, POWER, PREAMBLE_LEN);

            if (state != RADIOLIB_ERR_NONE) {
                DEBUG_PRINTLN("[ERROR] (error_handler) Cannot transmit because radio init failed.");
                return true;
            }
            msg_error_t msg_error;
            msg_error.node_id  = node_id;
            msg_error.error_id = error_code;
            
            state = radio.transmit((uint8_t*)&msg_error, sizeof(msg_error_t));

            if (state != RADIOLIB_ERR_NONE) {
                DEBUG_PRINTLN("[ERROR] (error_handler) Cannot transmit because radio transmit failed.");
                return true;
            }
        }

        return true;
    } else {
        return false;
    }
}
