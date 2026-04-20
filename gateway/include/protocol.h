/
/ Types of messages
const uint8_t MSG_TYPE_ACK              = 0xA;
const uint8_t MSG_TYPE_PAYLOAD_UPLINK   = 0xB;  // node -> gateway

const uint8_t MSG_TYPE_JOIN_REQ         = 0xD;
const uint8_t MSG_TYPE_START_DOWNLINK   = 0xF;

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