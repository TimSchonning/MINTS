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
 * @brief Contains all configurable variables and time stamp,
 * @note is __attribute__((packed))
 */
enum __attribute__((packed)) config_tag_t : uint8_t {
    TAG_TIME_STAMP     = 0x00, // uint32_t

    // LoRa Settings
    TAG_LORA_FREQ      = 0x01, // float (4 bytes)
    TAG_LORA_BW        = 0x02, // float (4 bytes)
    TAG_LORA_SF        = 0x03, // uint8_t
    TAG_LORA_CR        = 0x04, // uint8_t
    TAG_LORA_SYNC      = 0x05, // uint8_t
    TAG_LORA_PWR       = 0x06, // int8_t
    TAG_LORA_PREAMBLE  = 0x07, // uint16_t
    TAG_LORA_GAIN      = 0x08, // uint8_t

    // General Config
    TAG_CPU_FREQ       = 0x09, // uint8_t
    TAG_SLEEP_TIME     = 0x0A, // uint32_t
    TAG_MEASURE_WINDOW = 0x0B, // uint8_t

    // Particle Config
    TAG_PS_HEAT_UP     = 0x0C, // uint8_t
    TAG_PS_SAMPLE_TIME = 0x0D, // uint16_t
    TAG_PS_TARGET      = 0x0E, // uint16_t
    TAG_NODE_ID        = 0x0F, // uint8_t
    TAG_TX_RETRIES     = 0x10, // uint8_t
    TAG_BUFFER_THRESH  = 0x11  // uint8_t
};

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
 * @note Is __attribute__((packed)
 */
typedef struct __attribute__((packed)) {
    uint8_t type;
    uint8_t node_id;
    uint8_t reading_id;     // locally unique
    uint8_t readings[1 * 4];
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