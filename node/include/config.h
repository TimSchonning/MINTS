#ifndef CONFIG_H
#define CONFIG_H

//// General config
const uint64_t S_TO_uS          = 1000000;
const uint64_t S_TO_mS          = 1000;
const uint8_t  CPU_FREQ_MHZ     = 10;
const uint32_t BAUD             = 115200;
const uint64_t TIME_TO_SLEEP_S  = 524

//// Particle config
// ps = particle sensor
// ns = noise sensor
const uint8_t  PS_HEAT_UP_TIME_S = 35;  // set to 35 to "guarantee" sufficient heat-up
const uint16_t PS_SAMPLE_TIME_mS = 0;   // must be > 1
const uint16_t PS_TARGET_SAMPLES = 0;

const uint16_t NS_SAMPLE_TIME_mS = 0;   // must be > 1
const uint8_t  NS_PIN            = 0;

//// LoRa config
const float    FREQUENCY        = 868.1;
const float    BANDWIDTH        = 62.5;
const uint8_t  SPREADING_FACTOR = 12;
const uint8_t  CODING_RATE      = 8;
const uint8_t  SYNC_WORD        = 0x12;
const int8_t   POWER            = 14;
const uint16_t PREAMBLE_LEN     = 8;
const uint8_t  GAIN             = 0;

// LoRa pins
const int PIN_NSS  = 0;
const int PIN_DIO0 = 0;
const int PIN_NRST = 0;
const int PIN_DIO1 = 0;

//// ESP specific
RTC_DATA_ATTR int boot_count = 0;

#endif