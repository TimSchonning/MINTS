#include <cstdint>
#include <RadioLib>
#include <math.h>

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

bool standby_mode() {
    clearance_msg clearance;
    state = radio.receive(clearance, 2);

    if (!error_handler(state, "LoRa_init failed to receive standby clearance from gateway")) {
        radio.sleep();
        
        //// Initialises the boot count
        uint32_t now_ms                 = clearance.time_stamp;
        uint32_t measurement_windows_ms = MEASUREMENT_WINDOW_S * S_TO_mS;
        uint32_t time_past_in_window_ms = now_ms % measurement_windows_ms;
        uint32_t time_to_sleep_ms       = measurement_windows_ms - time_past_in_window_ms;
        
        boot_count = floor(now_ms / meas_win_ms);
        DEBUG_PRINT("[STANDBY] Init boot_count set to: ");
        DEBUG_PRINTLN(boot_count);

        DEBUG_PRINT("[STANDBY] Will sleep for: ");
        DEBUG_PRINTLN(time_to_sleep_ms);

        //// Sleeps till the closest window
        esp_sleep_enable_timer_wakeup(sleep_time_ms);
        return true;
    } else {
        return false;
    }
}

void initialise_node() {
    int16_t state = radio.begin(FREQUENCY, BANDWIDTH, SPREADING_FACTOR, CODING_RATE, SYNC_WORD, POWER, PREAMBLE_LEN, GAIN);
    error_handler(state, "LoRa_init initialisation");

    uint8_t id_attempts = 0;

    while (needs_initialisation && id_attempts < MAX_ID_ATTEMPTS) {
        DEBUG_PRINTLN("Pinging gateway for ID");

        // Pings the gateway
        state = radio.transmit(&MSG_TYPE_ID_PING, 1);
        id_attempts++;
        DEBUG_PRINT("Ping attempt nr.: ");
        DEBUG_PRINTLN(id_attempts);

        if (!error_handler(state, "LoRa_init failed to ping the gateway")) {
            // Receives the (return ping) ID from the gateway
            uint8_t received_id[1];
            state = radio.receive(received_id, 1);
    
            if (!error_handler(state, "LoRa_init failed to receive id from gateway")) {
                // Assigns the ID
                node_id = received_id[0];
                DEBUG_PRINT("Assigned Node ID: ");
                DEBUG_PRINTLN(node_id);

                // ACK to gateway
                uint8_t ack_payload[] = {MSG_TYPE_ID_ACK, node_id};
                radio.transmit(ack_payload, 2);
                
                needs_initialisation = false;
                
                //// Enters standby mode
                while (!standby_mode());
                esp_deep_sleep_start();
            }
        }
    }
}