#include <cstdint>
#include <RadioLib.h>

#include "config.h"
#include "debug_macros.h"
#include "sensor_logic.h"
#include "protocol.h"

extern SX1262 radio;

bool error_handler(int16_t state, bool inform_gateway, uint8_t error_code, const char* message) {
    // RADIOLIB_ERR_NONE is def. as 0;
    if (state != RADIOLIB_ERR_NONE) {
        DEBUG_PRINT("[ERROR] ");
        DEBUG_PRINT(message);
        DEBUG_PRINT(" Code: ");
        DEBUG_PRINTLN(state);
        
        if (inform_gateway) {
            msg_error_t msg_error;
            msg_error.node_id = node_id;
            msg_error.error_id = error_code;
            
            state = radio.transmit((uint8_t*)&msg_error, sizeof(msg_ack_t));
        }

        #ifdef DEBUG_MODE
            while (1); 
        #endif
        return true;
    } else {
        return false;
    }
}