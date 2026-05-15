#ifndef CONFIG_H
#define CONFIG_H

#include <cstdint>
#include "esp_attr.h"

//// General config
inline const uint64_t S_TO_uS                  = 1000000;
inline const uint64_t S_TO_mS                  = 1000;
inline const uint32_t BAUD                     = 115200;
inline const uint64_t MAX_TX_DELAY_S           = 60;
inline RTC_DATA_ATTR uint8_t  CPU_FREQ_MHZ     = 10;
inline RTC_DATA_ATTR uint32_t TIME_TO_SLEEP_S  = 300;      //make lowercase, will be calc at runtime

inline RTC_DATA_ATTR uint32_t MEASUREMENT_WINDOW_S  = 300;

//// Particle config
// ps = particle sensor
// ns = noise sensor
inline RTC_DATA_ATTR uint8_t  PS_HEAT_UP_TIME_S = 35;  // set to 35 to "guarantee" sufficient heat-up
inline RTC_DATA_ATTR uint16_t PS_SAMPLE_TIME_mS = 10000;   // must be > 1
inline RTC_DATA_ATTR uint16_t PS_TARGET_SAMPLES = 10;

inline RTC_DATA_ATTR uint16_t NS_SAMPLE_WINDOW_mS  = 1000;   // must be > 1
inline RTC_DATA_ATTR uint8_t  NS_TARGET_SAMPLES    = 10;   // must be > 1
inline RTC_DATA_ATTR uint8_t  NS_SAMPLE_DELAY_ms   = 1000;   // must be > 1
inline const uint8_t NS_PIN                        = 1;

//// LoRa config
inline float    FREQUENCY        = 868.1;
inline float    BANDWIDTH        = 125.0;
inline uint8_t  SPREADING_FACTOR = 8;
inline uint8_t  CODING_RATE      = 8;
inline uint8_t  SYNC_WORD        = 0x12;
inline int8_t   POWER            = 14;
inline uint16_t PREAMBLE_LEN     = 8;

// LoRa pins (check datasheet)
inline const int PIN_NSS  = 21;
inline const int PIN_DIO0 = 5;
inline const int PIN_NRST = 7;
inline const int PIN_DIO1 = 6;

//// Initialisation config
inline const uint8_t MAX_ID_ATTEMPTS    = 0;

//// ESP specific
inline RTC_DATA_ATTR bool needs_initialisation = true;
inline RTC_DATA_ATTR uint8_t  boot_count           = 0;
inline RTC_DATA_ATTR uint8_t  node_id              = 33;
inline RTC_DATA_ATTR uint8_t  MAX_TX_RETRIES       = 5;
inline constexpr uint8_t  BUFFERING_THRESHOLD  = 12;
inline RTC_DATA_ATTR uint8_t  buffering_counter    = 0;

//// TX config specific
// uint8_t config_tx_buffer[255];
// uint8_t config_tx_cursor = 0;
inline uint8_t config_rx_buffer[255];
inline uint8_t config_rx_cursor = 0;
#endif