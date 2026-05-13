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

void power_down_radios() {
    WiFi.mode(WIFI_OFF);
    btStop();
    esp_wifi_stop();
    esp_bt_controller_disable();
}

bool standby_mode() {
    msg_clearance_t clearance;
    int16_t state = radio.receive((uint8_t*)&clearance, sizeof(clearance));

    uint32_t _ = millis();
    uint32_t gateway_time_stamp = clearance.time_stamp;
    uint8_t type = clearance.type;

    if (type == MSG_TYPE_CLEARANCE &&
        !error_handler(state, false, UNDEFINED_ERROR, "LoRa_init failed to receive standby clearance from gateway")) {

        // ACKs the standby clearance
        msg_ack_t msg_clearance_ack;
        msg_clearance_ack.node_id = node_id;
        msg_clearance_ack.ack_for = MSG_TYPE_CLEARANCE;

        state = radio.transmit((uint8_t*)&msg_clearance_ack, sizeof(msg_ack_t));
        
        if (!error_handler(state, false, UNDEFINED_ERROR, "Failed to ack standby clearance")) {
            radio.sleep();

            //// Initialises the boot count
            uint32_t offset                 = millis() - _;
            uint32_t now_ms                 = clearance.time_stamp + offset;
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
        }
    } else {
        return false;
    }
}

void initialise_node() {
    int16_t state = radio.begin(FREQUENCY, BANDWIDTH, SPREADING_FACTOR, CODING_RATE, SYNC_WORD, POWER, PREAMBLE_LEN);
    error_handler(state, false, UNDEFINED_ERROR, "[INIT] LoRa_init initialisation");

    uint8_t id_attempts = 0;

    while (needs_initialisation && id_attempts < MAX_ID_ATTEMPTS) {
        DEBUG_PRINTLN("[INIT] Sends join request to the gateway");

        //// Sends a join request to the gateway
        msg_req_t msg_join_req;
        msg_join_req.type    = MSG_TYPE_JOIN_REQ;
        msg_join_req.node_id = 0x00;

        state = radio.transmit((uint8_t*)&msg_join_req, sizeof(msg_join_req));

        id_attempts++;

        DEBUG_PRINT("[INIT] Join request attempt nr.: ");
        DEBUG_PRINTLN(id_attempts);

        if (!error_handler(state, false, UNDEFINED_ERROR, "[ERROR] LoRa_init failed to send join msg to the gateway")) {
            //// Waits the for the join ack from the gateway
            msg_ack_t msg_join_ack;
            state = radio.receive((uint8_t*)&msg_join_ack, sizeof(msg_join_ack));
    
            if (msg_join_ack.ack_for == MSG_TYPE_JOIN_REQ &&
                !error_handler(state, false, UNDEFINED_ERROR, "[ERROR] LoRa_init failed to receive join ack from the gateway")) {
                
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
    DEBUG_PRINTLN("[ERROR] Max amount of id attempts reached. Reboot node.");
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

void config_mode() {
    int16_t state = radio.begin(FREQUENCY, BANDWIDTH, SPREADING_FACTOR, CODING_RATE, SYNC_WORD, POWER, PREAMBLE_LEN);
    error_handler(state, false, UNDEFINED_ERROR, "[config] radio initialisation");

    state = radio.receive(config_rx_buffer, sizeof(config_rx_buffer));

    if (state == RADIOLIB_ERR_NONE) {
        if (config_rx_buffer[0] == MSG_TYPE_CONFIG) {
            size_t len = radio.getPacketLength();
            
            // handle_config_msg(len);
    
            // ACKs the gateway
            msg_ack_t msg_ack;
            msg_ack.node_id = node_id;
            msg_ack.ack_for = MSG_TYPE_CONFIG;
            state = radio.transmit((uint8_t*)&msg_ack, sizeof(payload_t));
        }
        radio.sleep();
    }
}

static void write_nvs(const char* key, uint8_t data_in) {
    prefs.begin("mints", false);
    if (!prefs.putUChar(key, data_in)) error_handler(-1, true, NVS_ERROR, "Failed to write to nvs");
    prefs.end();
}

static void write_nvs(const char* key, uint16_t data_in) {
    prefs.begin("mints", false);
    if (!prefs.putUShort(key, data_in)) error_handler(-1, true, NVS_ERROR, "Failed to write to nvs");
    prefs.end();
}

static void write_nvs(const char* key, uint32_t data_in) {
    prefs.begin("mints", false);
    if (!prefs.putULong(key, data_in)) error_handler(-1, true, NVS_ERROR, "Failed to write to nvs");
    prefs.end();
}

static void read_nvs(const char* key, uint8_t &data_out) {
    prefs.begin("mints", true);
    data_out = prefs.getUChar(key, 0);
    prefs.end();
}

static void read_nvs(const char* key, uint16_t &data_out) {
    prefs.begin("mints", true);
    data_out = prefs.getUShort(key, 0);
    prefs.end();
}

static void read_nvs(const char* key, uint32_t &data_out) {
    prefs.begin("mints", true);
    data_out = prefs.getULong(key, 0);
    prefs.end();
}

void add_to_nvs(uint8_t boot_count, uint8_t pm1, uint8_t pm25, uint16_t noise) {
    char key[16];
    
    snprintf(key, sizeof(key), "i_%u_p1", boot_count);
    write_nvs(key, pm1);
    
    snprintf(key, sizeof(key), "i_%u_p2", boot_count);
    write_nvs(key, pm25);
    
    snprintf(key, sizeof(key), "i_%u_n", boot_count);
    write_nvs(key, noise);
}
