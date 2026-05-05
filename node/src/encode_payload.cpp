#include "config.h"
#include "debug_macros.h"
#include "encode_payload.h"
#include "sensor_logic.h"
#include "utils.h"

#include <stdint.h>
#include <sensor_logic.h>
#include <encode_payload.h>
#include <RadioLib.h>

extern SX1262 radio;

bool encode_payload(payload_t* payload, ps_result_t* ps_result, ns_result_t* ns_result) {
    if (!payload || !ps_result || !ns_result) return false;

    if (buffering_counter >= BUFFERING_THRESHOLD) return false;
    
    payload->type       = MSG_TYPE_PAYLOAD_UPLINK;
    payload->node_id    = node_id;
    payload->reading_id = boot_count;
    
    uint16_t index = buffering_counter * 4;
    
    payload->readings[index]     = ps_result->pm10;
    payload->readings[index + 1] = ps_result->pm25;
    payload->readings[index + 2] = (uint8_t)((ns_result->noise_peak >> 8) & 0xFF); 
    payload->readings[index + 3] = (uint8_t)(ns_result->noise_peak & 0xFF);
    
    add_to_nvs(boot_count, ps_result->pm10, ps_result->pm25, ns_result->noise_peak);

    buffering_counter++;

    return true;
}

bool transmit_payload(payload_t* payload) {
    DEBUG_PRINTLN("[START] LoRa transmission");

    int16_t state = radio.begin(FREQUENCY, BANDWIDTH, SPREADING_FACTOR, CODING_RATE, SYNC_WORD, POWER, PREAMBLE_LEN, GAIN);
    error_handler(state, "LoRa initialisation");

    uint8_t counter = 0;
    while (counter < MAX_TX_RETRIES) {
        state = radio.transmit((uint8_t*)payload, sizeof(payload_t));
        error_handler(state, "LoRa payload transmission");
        
        DEBUG_PRINTLN("[SUCCESS] Payload sent, waiting for ACK");

        msg_ack_t payload_ack;
        state = radio.receive((uint8_t*)&payload_ack, sizeof(msg_ack_t));

        if (state == RADIOLIB_ERR_NONE) {
            if (payload_ack.type    == MSG_TYPE_ACK &&
                payload_ack.node_id == node_id &&
                payload_ack.ack_for == MSG_TYPE_PAYLOAD_UPLINK) {
                    return true;
            }
        }
        counter++;
    }
    return false;
}