#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <cstdint>

// Types of messages
const uint8_t MSG_TYPE_ACK            = 0xA0;
const uint8_t MSG_TYPE_PAYLOAD_UPLINK = 0xB0;
const uint8_t MSG_TYPE_JOIN_REQ       = 0xD0;
const uint8_t MSG_TYPE_CLEARANCE      = 0xD1;
const uint8_t MSG_TYPE_ERROR          = 0xE0;
const uint8_t MSG_TYPE_CONFIG         = 0xF0;

const uint8_t UNDEFINED_ERROR = 0x00;
const uint8_t PS_INIT_ERROR   = 0x01;
const uint8_t PS_SLEEP_ERROR  = 0x02;
const uint8_t NS_SLEEP_ERROR  = 0x03;
const uint8_t NVS_ERROR       = 0x04;

/**
 * @brief Structure for config updates
 * @note Is __attribute__((packed)
 * @note 
 */
typedef struct __attribute__((packed)) {
    uint8_t  type = MSG_TYPE_CONFIG;
} msg_config_t;

/**
 * @brief Stores the results as a sendable LoRa payload.
 * @note reading_id reflects the latest readings id.
 * @note Must adhere to LoRa payload size limits (255 bytes)
 * @note Is __attribute__((packed)
 */
typedef struct __attribute__((packed)) {
    uint8_t type;
    uint8_t node_id;
    uint8_t reading_id;
    uint8_t readings[252];
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
 * @brief Error message structure.
 * @note Is __attribute__((packed)
 */
typedef struct __attribute__((packed)) {
    uint8_t type = MSG_TYPE_ERROR;
    uint8_t node_id;
    uint8_t error_id;
} msg_error_t;

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