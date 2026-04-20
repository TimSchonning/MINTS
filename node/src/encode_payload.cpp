#include <stdint.h>
#include <sensor_logic.h>
#include <encode_payload.h>
#include <RadioLib.h>

#include "config.h"
#include "debug_macros.h"
#include "encode_payload.h"
#include "sensor_logic.h"
#include "utils.h"

bool encode_payload(payload_t* payload, ps_result_t* ps_result, ns_result_t* ns_result, uint8_t id) {
    if (!payload || !ps_result || !ns_result || !id) return false;

    payload->id  = id;

    payload->pm10  = ps_result->pm10;
    payload->pm25  = ps_result->pm25;

    payload->noise_peak = ns_result->noise_peak;
    return true;
}

bool transmit_payload() {
    DEBUG_PRINTLN("[START] LoRa transmission");

    int16_t state = radio.begin(FREQUENCY, BANDWIDTH, SPREADING_FACTOR, CODING_RATE, SYNC_WORD, POWER, PREAMBLE_LEN, GAIN);
    error_handler(state, "LoRa initialisation");

    uint8_t counter = 0;
    while (counter < MAX_TX_RETRIES) {
        state = radio.transmit((uint8_t*)payload, sizeof(payload_t));
        error_handler(state, "LoRa payload transmission");
        
        DEBUG_PRINTLN("[SUCCESS] Payload sent, waiting for ACK");

        msg_ack_t payload_ack;
        state = radio.receive(&payload_ack, sizeof(msg_ack_t));

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