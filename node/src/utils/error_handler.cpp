#include <cstdint>
#include <RadioLib.h>

#include "config.h"
#include "debug_macros.h"
#include "sensor_logic.h"
#include "utils.h"
#include "protocol.h"

extern SX1262 radio;

bool error_handler(int16_t state, bool inform_gateway, uint8_t error_code, const char* message) {
    if (state != RADIOLIB_ERR_NONE) return false;

    DEBUG_PRINT("[ERROR] "); DEBUG_PRINT(message); DEBUG_PRINT(". Code: "); DEBUG_PRINTLN(state);
    
    if (inform_gateway) {

        if (radio.begin(FREQUENCY, BANDWIDTH, SPREADING_FACTOR, CODING_RATE, SYNC_WORD, POWER, PREAMBLE_LEN) != RADIOLIB_ERR_NONE) {
            DEBUG_PRINTLN("[ERROR] (error_handler) Cannot transmit because radio initialisation failed.");
            return true;
        }

        msg_error_t msg_error{.node_id = node_id, .error_id = error_code};

        if (radio.transmit((uint8_t*)&msg_error, sizeof(msg_error_t)) != RADIOLIB_ERR_NONE) {
            DEBUG_PRINTLN("[ERROR] (error_handler) Cannot transmit because radio transmit failed.");
        }
    }

    return true;
}
