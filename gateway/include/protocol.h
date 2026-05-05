#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <stdint.h>

// Types of messages
const uint8_t MSG_TYPE_ACK            = 0xA0;
const uint8_t MSG_TYPE_PAYLOAD_UPLINK = 0xB0;  // node -> gateway

const uint8_t MSG_TYPE_JOIN_REQ       = 0xD0;
const uint8_t MSG_TYPE_CLEARANCE      = 0xD1;

const uint8_t MSG_TYPE_CONFIG         = 0xF0;

/**
 * @brief Stores the results as a sendable LoRa payload.
 * @note reading_id reflects the latest readings id.
 * @note Is __attribute__((packed)
 */
typedef struct __attribute__((packed)) {
    uint8_t signature;
    uint8_t node_id;
    uint8_t reading_id;     // locally unique
    uint8_t readings[BUFFERING_THRESHOLD * 4]
    // uint8_t pm10, pm25;
    // uint16_t noise_peak;
} payload_t;

/**
 * @brief Ack message structure.
 * @note Is __attribute__((packed)
 */
typedef struct __attribute__((packed)) {
    uint8_t type = MSG_TYPE_ACK;
    uint8_t node_id;
    uint8_t ack_for;    //ie which type of msg is being ack:ed
} msg_ack_t;

/**
 * @brief Request message structure.
 * @note Is __attribute__((packed)
 */
typedef struct __attribute__((packed)) {
    uint8_t type;
    uint8_t node_id;
} msg_req_t;

/**
 * @brief Structure for gateway synchronization clearance
 * @note Will ever only be received from the gateway upon initialisation.
 * @note Is __attribute__((packed)
 */
typedef struct __attribute__((packed)) {
    uint8_t type;
    uint32_t time_stamp;
} msg_clearance_t;


#endif