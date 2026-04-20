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

static bool standby_mode() {
    msg_clearance_t clearance;
    int16_t state = radio.receive((uint8_t*)&clearance, sizeof(clearance));

    if (!error_handler(state, "[STANDBY] LoRa_init failed to receive standby clearance from gateway")) {
        uint8_t ack_payload[] = {MSG_TYPE_ID_ACK, node_id};

        // ACKs the standby clearance
        msg_std_t msg_standby_ack;
        msg_standby_ack.node_id = node_id;
        msg_standby_ack.payload = 0x00;

        radio.transmit(msg_standby_ack, sizeof(msg_standby_ack));
        radio.sleep();
        
        //// Initialises the boot count
        uint32_t now_ms                 = clearance.time_stamp;
        uint32_t measurement_windows_ms = MEASUREMENT_WINDOW_S * S_TO_mS;
        uint32_t time_past_in_window_ms = now_ms % measurement_windows_ms;
        uint32_t time_to_sleep_us       = (measurement_windows_ms - time_past_in_window_ms) * 1000ULL;
        
        boot_count = floor(now_ms / measurement_windows_ms);
        DEBUG_PRINT("[STANDBY] Init boot_count set to: ");
        DEBUG_PRINTLN(boot_count);

        DEBUG_PRINT("[STANDBY] Will sleep for (seconds): ");
        DEBUG_PRINTLN(time_to_sleep_us / S_TO_uS);

        //// Sleeps till the closest window
        esp_sleep_enable_timer_wakeup(time_to_sleep_us);
        esp_deep_sleep_start();
        // wont be reached
    } else {
        return false;
    }
}

void initialise_node() {
    int16_t state = radio.begin(FREQUENCY, BANDWIDTH, SPREADING_FACTOR, CODING_RATE, SYNC_WORD, POWER, PREAMBLE_LEN, GAIN);
    error_handler(state, "[INIT] LoRa_init initialisation");

    uint8_t id_attempts = 0;

    while (needs_initialisation && id_attempts < MAX_ID_ATTEMPTS) {
        DEBUG_PRINTLN("[INIT] Sends join request to the gateway");

        //// Sends a join request to the gateway
        msg_req_t msg_join_req;
        msg_join_req.type    = MSG_TYPE_JOIN_REQ;
        msg_join_req.node_id = 0x00;

        state = radio.transmit(&msg_join_req, sizeof(msg_join_req));

        id_attempts++;
+
        DEBUG_PRINT("[INIT] Join request attempt nr.: ");
        DEBUG_PRINTLN(id_attempts);

        if (!error_handler(state, "[INIT] LoRa_init failed to send join msg to the gateway")) {
            //// Waits the for the join ack from the gateway
            msg_ack_t msg_join_ack;
            state = radio.receive(msg_join_ack, sizeof(msg_join_ack));
    
            if (msg_join_ack.ack_for == MSG_TYPE_JOIN_REQ &&
                !error_handler(state, "[INIT] LoRa_init failed to receive join ack from the gateway")) {
                
                // Assigns the ID
                node_id = msg_join_ack.node_id;
                DEBUG_PRINT("[INIT] Assigned Node ID: ");
                DEBUG_PRINTLN(node_id);

                // ACK the gateway
                // msg_join_ack.node_id = node_id;
                // msg_join_ack.ack_for = MSG_TYPE_JOIN_REQ;
                // radio.transmit(msg_join_ack, sizeof(msg_join_ack));
                
                needs_initialisation = false;
                
                //// Enters standby mode
                standby_mode();
            }
        }
    }
}