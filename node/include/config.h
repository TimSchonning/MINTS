#ifndef CONFIG_H
#define CONFIG_H

#include "config.h"
#include "debug_macros.h"
#include "encode_payload.h"
#include "protocol.h"
#include "sensor_logic.h"
#include "utils.h"

//// General config
const uint64_t S_TO_uS                  = 1000000;
const uint64_t S_TO_mS                  = 1000;
const uint32_t BAUD                     = 115200;
RTC_DATA_ATTR uint8_t  CPU_FREQ_MHZ     = 10;
RTC_DATA_ATTR uint32_t TIME_TO_SLEEP_S  = 524;      //make lowercase, will be calc at runtime

RTC_DATA_ATTR uint32_t MEASUREMENT_WINDOW_S  = 600;

//// Particle config
// ps = particle sensor
// ns = noise sensor
RTC_DATA_ATTR uint8_t  PS_HEAT_UP_TIME_S = 35;  // set to 35 to "guarantee" sufficient heat-up
RTC_DATA_ATTR uint16_t PS_SAMPLE_TIME_mS = 0;   // must be > 1
RTC_DATA_ATTR uint16_t PS_TARGET_SAMPLES = 0;

RTC_DATA_ATTR uint16_t NS_SAMPLE_TIME_mS = 0;   // must be > 1
const uint8_t  NS_PIN                    = 0;

//// LoRa config
RTC_DATA_ATTR float    FREQUENCY        = 868.1;
RTC_DATA_ATTR float    BANDWIDTH        = 62.5;
RTC_DATA_ATTR uint8_t  SPREADING_FACTOR = 12;
RTC_DATA_ATTR uint8_t  CODING_RATE      = 8;
RTC_DATA_ATTR uint8_t  SYNC_WORD        = 0x12;
RTC_DATA_ATTR int8_t   POWER            = 14;
RTC_DATA_ATTR uint16_t PREAMBLE_LEN     = 8;
RTC_DATA_ATTR uint8_t  GAIN             = 0;

// LoRa pins (check datasheet)
const int PIN_NSS  = 0;
const int PIN_DIO0 = 0;
const int PIN_NRST = 0;
const int PIN_DIO1 = 0;

//// Initialisation config
const uint8_t MAX_ID_ATTEMPTS    = 0;

//// ESP specific
RTC_DATA_ATTR bool needs_initialisation = true;
RTC_DATA_ATTR uint8_t  boot_count           = 0;
RTC_DATA_ATTR uint8_t  node_id              = 0;
RTC_DATA_ATTR uint8_t  MAX_TX_RETRIES       = 5;
RTC_DATA_ATTR uint8_t  BUFFERING_THRESHOLD  = 4;
RTC_DATA_ATTR uint8_t  buffering_counter    = 0;
#endif