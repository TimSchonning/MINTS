#include "master.h"

extern SX1262 radio;

bool encode_payload(payload_t* payload, ps_result_t* ps_result, ns_result_t* ns_result) {
    if (!payload || !ps_result || !ns_result) return false;
    
    payload->type       = MSG_TYPE_PAYLOAD_UPLINK;
    payload->node_id    = node_id;
    payload->reading_id = boot_count;
    
    uint16_t index = buffering_counter * 4;
    
    payload->readings[index]     = ps_result->pm1;
    payload->readings[index + 1] = ps_result->pm25;
    payload->readings[index + 2] = (ns_result->noise_avg >> 8); 
    payload->readings[index + 3] = ns_result->noise_avg;
    
    add_to_nvs(boot_count, ps_result->pm1, ps_result->pm25, ns_result->noise_avg);

    return true;
}

bool transmit_payload(payload_t* payload) {
    int16_t state = radio.begin(FREQUENCY, BANDWIDTH, SPREADING_FACTOR, CODING_RATE, SYNC_WORD, POWER, PREAMBLE_LEN);
    if (error_handler(state, false, UNDEFINED_ERROR, "LoRa initialisation")) return false;

    for (uint8_t counter = 0; counter < MAX_TX_RETRIES; counter++) {
        // 1. Transmit the package. Abort upon fail.
        uint16_t payload_size = 3 + BUFFERING_THRESHOLD * 4;
        state = radio.transmit((uint8_t*)payload, payload_size);
        if (error_handler(state, false, UNDEFINED_ERROR, "LoRa payload transmission")) return false;
        
        DEBUG_PRINTLN("[INFO]     Payload sent. Awaiting ACK");

        // 2. Receive an ACK
        msg_ack_t payload_ack;
        state = radio.receive((uint8_t*)&payload_ack, sizeof(msg_ack_t));

        // 3. Verify the ACK
        if (state               == RADIOLIB_ERR_NONE &&
            payload_ack.type    == MSG_TYPE_ACK &&
            payload_ack.node_id == node_id &&
            payload_ack.ack_for == MSG_TYPE_PAYLOAD_UPLINK) {
                DEBUG_PRINTLN("[INFO]      ACK received.");
                return true;
        }

        DEBUG_PRINTLN("[WARNING]  ACK missing or invalid. Retrying.");
        random_tx_delay(5);
    }

    DEBUG_PRINTLN("[ERROR]    Max transmit payload retries reached. Transmission failed.");
    return false;
}