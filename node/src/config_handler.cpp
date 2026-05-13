#include <cstdint>
#include <RadioLib.h>

#include "config.h"
#include "debug_macros.h"
#include "sensor_logic.h"
#include "protocol.h"

extern SX1262 radio;

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