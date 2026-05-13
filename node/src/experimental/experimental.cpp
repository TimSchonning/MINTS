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

static void start_config_msg(uint32_t time_ms) {
    msg_config_t header;
    
    memcpy(config_tx_buffer, &header, sizeof(msg_config_t));
    cursor = sizeof(msg_config_t);
}

static void add_tlv(ConfigTag tag, size_t val) {
    tx_buffer[cursor++] = tag;
    tx_buffer[cursor++] = sizeof(val);
    memcpy(&tx_buffer[cursor], &val, sizeof(val));
    cursor += sizeof(val);
}

static void add_tlv(ConfigTag tag, uint8_t val) {
    tx_buffer[cursor++] = tag;
    tx_buffer[cursor++] = sizeof(uint8_t);
    tx_buffer[cursor++] = val;
}

void send_update() {
    start_config_msg(millis());

    // example
    add_tlv(TAG_LORA_FREQ, 433.5f);
    add_tlv(TAG_LORA_SF, (uint8_t)12);
    add_tlv(TAG_NODE_ID, (uint8_t)0x05);

    int state = radio.transmit(tx_buffer, cursor); 
}

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

void init_nvs() {
    // Initialises the flash storage at FIRST startup to match ram

    // init preferences GLOBALLY
    // begin
    // end
}

void set_config_variables() {
    // Updates the system variables based on values in nvs
    // use case: node has initialised, and updated system variables, before and is now being repowered (not woken from sleep)

    // init preferences GLOBALLY
    // begin
    // end
}