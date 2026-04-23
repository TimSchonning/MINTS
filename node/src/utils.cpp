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

    uint32_t _ = millis();
    uint32_t gateway_time_stamp = clearance.time_stamp;
    uint8_t type = clearance.type;

    if (type == MSG_TYPE_CLEARANCE &&
        !error_handler(state, "LoRa_init failed to receive standby clearance from gateway")) {

        // ACKs the standby clearance
        msg_ack_t msg_clearance_ack;
        msg_clearance_ack.node_id = node_id;
        msg_clearance_ack.ack_for = MSG_TYPE_CLEARANCE;

        state = radio.transmit(msg_clearance_ack, sizeof(msg_ack_t));
        
        if (!error_handler(state, "Failed to ack standby clearance")) {
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

        DEBUG_PRINT("[INIT] Join request attempt nr.: ");
        DEBUG_PRINTLN(id_attempts);

        if (!error_handler(state, "[ERROR] LoRa_init failed to send join msg to the gateway")) {
            //// Waits the for the join ack from the gateway
            msg_ack_t msg_join_ack;
            state = radio.receive(&msg_join_ack, sizeof(msg_join_ack));
    
            if (msg_join_ack.ack_for == MSG_TYPE_JOIN_REQ &&
                !error_handler(state, "[ERROR] LoRa_init failed to receive join ack from the gateway")) {
                
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

// static void start_config_msg(uint32_t time_ms) {
//     msg_config_t header;
    
//     memcpy(config_tx_buffer, &header, sizeof(msg_config_t));
//     cursor = sizeof(msg_config_t);
// }

// static void add_tlv(ConfigTag tag, size_t val) {
//     tx_buffer[cursor++] = tag;
//     tx_buffer[cursor++] = sizeof(val);
//     memcpy(&tx_buffer[cursor], &val, sizeof(val));
//     cursor += sizeof(val);
// }

// static void add_tlv(ConfigTag tag, uint8_t val) {
//     tx_buffer[cursor++] = tag;
//     tx_buffer[cursor++] = sizeof(uint8_t);
//     tx_buffer[cursor++] = val;
// }

// void send_update() {
//     start_config_msg(millis());

//     // example
//     add_tlv(TAG_LORA_FREQ, 433.5f);
//     add_tlv(TAG_LORA_SF, (uint8_t)12);
//     add_tlv(TAG_NODE_ID, (uint8_t)0x05);

//     int state = radio.transmit(tx_buffer, cursor); 
// }

static void handle_config_msg(size_t len) {
    if (len < sizeof(msg_config_t)) return; 
    
    msg_config_t* header = (msg_config_t*)config_rx_buffer;

    size_t cursor = sizeof(msg_config_t);

    while (cursor < len) {
        uint8_t tag        = config_rx_buffer[cursor++];
        uint8_t length     = config_rx_buffer[cursor++];
        uint8_t* value_ptr = &config_rx_buffer[cursor];

        switch (tag) {
            case TAG_LORA_FREQ:
                memcpy(&FREQUENCY, value_ptr, sizeof(FREQUENCY));
                break;
            case TAG_LORA_BW:
                memcpy(&BANDWIDTH, value_ptr, sizeof(BANDWIDTH));
                break;
            case TAG_LORA_SF:
                memcpy(&SPREADING_FACTOR, value_ptr, sizeof(SPREADING_FACTOR));
                break;
            case TAG_LORA_CR:
                memcpy(&CODING_RATE, value_ptr, sizeof(CODING_RATE));
                break;
            case TAG_LORA_SYNC:
                memcpy(&SYNC_WORD, value_ptr, sizeof(SYNC_WORD));
                break;
            case TAG_LORA_PWR:
                memcpy(&POWER, value_ptr, sizeof(POWER));
                break;
            case TAG_LORA_PREAMBLE:
                memcpy(&PREAMBLE_LEN, value_ptr, sizeof(PREAMBLE_LEN));
                break;
            case TAG_LORA_GAIN:
                memcpy(&GAIN, value_ptr, sizeof(GAIN));
                break;

            case TAG_CPU_FREQ:
                memcpy(&CPU_FREQ_MHZ, value_ptr, sizeof(CPU_FREQ_MHZ));
                break;
            case TAG_SLEEP_TIME:
                memcpy(&TIME_TO_SLEEP_S, value_ptr, sizeof(TIME_TO_SLEEP_S));
                break;
            case TAG_MEASURE_WINDOW:
                memcpy(&MEASUREMENT_WINDOW_S, value_ptr, sizeof(MEASUREMENT_WINDOW_S));
                break;

            case TAG_PS_HEAT_UP:
                memcpy(&PS_HEAT_UP_TIME_S, value_ptr, sizeof(PS_HEAT_UP_TIME_S));
                break;
            case TAG_PS_SAMPLE_TIME:
                memcpy(&PS_SAMPLE_TIME_mS, value_ptr, sizeof(PS_SAMPLE_TIME_mS));
                break;
            case TAG_PS_TARGET:
                memcpy(&PS_TARGET_SAMPLES, value_ptr, sizeof(PS_TARGET_SAMPLES));
                break;
            case TAG_NS_SAMPLE_TIME:
                memcpy(&NS_SAMPLE_TIME_mS, value_ptr, sizeof(NS_SAMPLE_TIME_mS));
                break;

            case TAG_NODE_ID:
                memcpy(&node_id, value_ptr, sizeof(node_id));
                break;
            case TAG_MAX_RETRIES:
                memcpy(&MAX_TX_RETRIES, value_ptr, sizeof(MAX_TX_RETRIES));
                break;
            case TAG_BUFFER_THRESH:
                memcpy(&BUFFERING_THRESHOLD, value_ptr, sizeof(BUFFERING_THRESHOLD));
                break;

            default:
                DEBUG_PRINTLN("Unknown config tag")
                break;
        }
        cursor += length;
    }
}

void config_mode() {
    int16_t state = radio.begin(FREQUENCY, BANDWIDTH, SPREADING_FACTOR, CODING_RATE, SYNC_WORD, POWER, PREAMBLE_LEN, GAIN);
    error_handler(state, "[config] radio initialisation");

    state = radio.receive(config_rx_buffer, sizeof(config_rx_buffer));

    if (state == RADIOLIB_ERR_NONE) {
        if (config_rx_buffer[0] == MSG_TYPE_CONFIG) {
            size_t len = radio.getPacketLength();
            
            handle_config_msg(len);
    
            // ACKs the gateway
            msg_ack_t msg_ack;
            msg_ack.node_id = node_id;
            msg_ack.ack_for = MSG_TYPE_CONFIG;
            state = radio.transmit(&payload, sizeof(payload_t));
        }
        radio.sleep()
    }
}

static void add_nvs(const char* key, uint8_t data) {
    // add data to non-volatile storage
}

static void add_nvs(const char* key, uint16_t data) {
    // add data to non-volatile storage
}

static void add_nvs(const char* key, uint32_t data) {
    // add data to non-volatile storage
}
