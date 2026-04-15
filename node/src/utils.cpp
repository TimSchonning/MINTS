#include <cstdint>
#include <RadioLib>

#include "config.h"
#include "debug_macros.h"
#include "encode_payload.h"
#include "sensor_logic.h"
#include "utils.h"

bool error_handler(int16_t state, const char* message) {
    if (state != RADIOLIB_ERR_NONE) {
        DEBUG_PRINT("[ERROR] ");
        DEBUG_PRINT(message);
        DEBUG_PRINT(" Code: ");
        DEBUG_PRINTLN(state);
        #ifdef DEBUG_MODE
            while (1); 
        #endif
        return true;
    } else {
        return false;
    }
}

void power_down_radios() {
    WiFi.mode(WIFI_OFF);
    btStop();
    esp_wifi_stop();
    esp_bt_controller_disable();
}

void initialise_node() {
    int16_t state = radio.begin(FREQUENCY, BANDWIDTH, SPREADING_FACTOR, CODING_RATE, SYNC_WORD, POWER, PREAMBLE_LEN, GAIN);
    error_handler(state, "LoRa_init initialisation");

    uint8_t id_attempts = 0;

    while (needs_initialisation && id_attempts < MAX_ID_ATTEMPTS) {
        DEBUG_PRINTLN("Pinging gateway for ID");

        // Pings the gateway
        state = radio.transmit(&MSG_TYPE_PING, 1);
        id_attempts++;
        DEBUG_PRINT("Ping attempt nr.: ");
        DEBUG_PRINTLN(id_attempts);

        if (!error_handler(state, "LoRa_init failed to ping the gateway")) {
            // Receives the (return ping) ID from the gateway
            uint8_t received_id[1];
            state = radio.receive(received_id, 1);
    
            if (!error_handler(state, "LoRa_init failed to receive id from gateway")) {
                // Assigns the ID
                NODE_ID = received_id[0];
                DEBUG_PRINT("Assigned Node ID: ");
                DEBUG_PRINTLN(NODE_ID);

                // ACK to gateway
                uint8_t ack_payload[] = {MSG_TYPE_ACK, NODE_ID};
                radio.transmit(ack_payload, 2);
                
                needs_initialisation = false;
            }
        }
    }
}