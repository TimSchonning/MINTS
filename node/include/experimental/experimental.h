#ifndef EXPERIMENTAL_H
#define EXPERIMENTAL_H


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

#endif