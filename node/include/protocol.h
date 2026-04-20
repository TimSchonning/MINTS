#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <stdint.h>

#include "config.h"
#include "debug_macros.h"
#include "encode_payload.h"
#include "protocol.h"
#include "sensor_logic.h"
#include "utils.h"

// Types of messages
const uint8_t MSG_TYPE_ACK              = 0xA;
const uint8_t MSG_TYPE_PAYLOAD_UPLINK   = 0xB;  // node -> gateway

const uint8_t MSG_TYPE_JOIN_REQ
const uint8_t MSG_TYPE_JOIN_REQ         = 0xD;
const uint8_t MSG_TYPE_START_DOWNLINK   = 0xF;



/**
 * @brief Stores the results as a sendable LoRa payload.
 * @note Is __attribute__((packed)
 */
typedef struct __attribute__((packed)) {
    uint8_t type;
    uint8_t node_id;
    uint8_t reading_id;     // locally unique
    uint8_t pm10, pm25;
    uint16_t noise_peak;
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