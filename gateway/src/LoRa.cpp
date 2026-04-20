/**
 * The code in this file is to be copy-and-pasted to the Arduino IDE.
 * Functions like Serial.print will not work without the Arduino IDE.
 * TODO: This file will later be merged with gatewayLogic.cpp, and modified to run C++ directly on the Raspberry PI gateway.
 */

#include <RadioLib.h>

/**
 * Struct defining what is transmitted.
 * @see DataPacket.h
 */
typedef struct
{
    uint32_t signature = 0xDEADBEEF;
    uint8_t nodeID;
    uint8_t pm10, pm25;
    uint16_t noise_peak;
} __attribute__((packed)) payload_t;

/**
 * Heltec V2 Pin Definitions
 * NSS: 18, DIO0: 26, RST: 14, DIO1: 35
 * LoRa Chip: SX1276
 * Edit to fit your configuration.
 */
SX1276 radio = new Module(18, 26, 14, 35);

float FREQ = 868.1; // Frequency
float BW = 125.0;   // Bandwidth
int SF = 7;         // Spreading Factor
int CR = 8;         // Coding Rate
int SYNC = 0x12;    // Sync word
int PWR = 10;       // Power
int PRE = 8;        // Preamble
int BAUD = 115200;  // Baud

/**
 * Initial setup of Arduino and LoRa module.
 */
void setup()
{
    Serial.begin(BAUD);

    int state = radio.begin(FREQ, BW, SF, CR, SYNC, PWR, PRE);

    /**
     * Returns error code if LoRa radio set up fails.
     * For error code definition, see: https://jgromes.github.io/RadioLib/group__status__codes.html
     */
    if (state != RADIOLIB_ERR_NONE)
    {
        Serial.print(F("LoRa failed, code "));
        Serial.println(state);
        while (true);
    }
}

/**
 * Main loop.
 */
void loop()
{
    payload_t payload;

    // If LoRa signal found, copy it to a place in memory.
    int state = radio.receive((uint8_t *)&payload, sizeof(payload_t));

    if (state == RADIOLIB_ERR_NONE)
    {
        // If packet is received correctly, write to COM.
        Serial.write((uint8_t *)&payload, sizeof(payload_t));
    }
    else if (state == RADIOLIB_ERR_RX_TIMEOUT)
    {
        // No packet received in this polling window.
    }
    else if (state == RADIOLIB_ERR_CRC_MISMATCH)
    {
        Serial.println("CRC error! (Corrupt packet)");
    }
    else
    {
        Serial.println("Unknown error.");
    }
}