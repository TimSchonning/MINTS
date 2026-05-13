#ifndef CONFIG_H
#define CONFIG_H

#include <cstdint>
#include "esp_attr.h"

namespace Mints::Config {

    //// HARDWARE CONSTANTS
    namespace Hardware {
        constexpr uint32_t SERIAL_BAUD = 115200;
        
        // LoRa Radio Pins
        constexpr int8_t PIN_LORA_NSS  = 21;
        constexpr int8_t PIN_LORA_DIO0 = 5;
        constexpr int8_t PIN_LORA_NRST = 7;
        constexpr int8_t PIN_LORA_DIO1 = 6;
        
        constexpr uint8_t PIN_NOISE_SENSOR = 1;
    }

    //// RADIO PARAMETERS
    namespace Radio {
        namespace Config {
            inline const uint64_t MAX_TX_DELAY_S = 60;
        }
        
        namespace LoRa {
            inline float    FREQUENCY        = 868.1f;
            inline float    BANDWIDTH        = 125.0f;
            inline uint8_t  SPREADING_FACTOR = 8;
            inline uint8_t  CODING_RATE      = 8;
            inline uint8_t  SYNC_WORD        = 0x12;
            inline int8_t   POWER            = 13;
            inline uint16_t PREAMBLE_LEN     = 8;
        }
    }

    //// SYSTEM STATE (RTC RAM)
    namespace State {
        inline RTC_DATA_ATTR uint8_t node_id        = 33;
        inline RTC_DATA_ATTR uint8_t boot_count     = 0;
        inline RTC_DATA_ATTR uint8_t max_tx_retries = 5;
        inline RTC_DATA_ATTR uint8_t max_id_retries = 5;

        namespace Buffering {
            inline RTC_DATA_ATTR uint8_t  buffering_threshold = 4;
            inline RTC_DATA_ATTR uint8_t  buffering_counter   = 0;
        }

        namespace Sleep {
            inline RTC_DATA_ATTR uint32_t wakeup_interval = 900;
        }

        namespace flags {
            inline RTC_DATA_ATTR bool needs_init = true;
        }
    }
    
    //// SENSOR PARAMETERS
    namespace Sensors {
        namespace Particle {
            inline RTC_DATA_ATTR uint8_t  heat_up_s      = 35;
            inline RTC_DATA_ATTR uint16_t sample_time_ms = 1000;
            inline RTC_DATA_ATTR uint16_t target_samples = 5;
        }
        
        namespace Noise {
            inline RTC_DATA_ATTR uint16_t window_ms      = 50;
            inline RTC_DATA_ATTR uint8_t  target_samples = 5;
            inline RTC_DATA_ATTR uint16_t sample_delay   = 500;
        }
    }

    //// TIME CONVERSIONS
    namespace Utils {
        constexpr uint64_t S_TO_US = 1000000ULL;
        constexpr uint64_t S_TO_MS = 1000ULL;
    }
}
