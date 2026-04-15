// Denna kod är för tillfället gjord för en Arduino och går inte att köra här. Måste köras i Arduino IDE.
// Detta är endast temporärt för teständamål.
// När koden väl ska användas "på riktigt", ta bort DEBUG_PRINT och modifera koden lite så bör den gå att köra här.

#include <RadioLib.h>
#include "debug_macros.h"

// Packet data format
typedef struct // OBS! Byt inte ut, behåll som det är för tillfället.
{
    uint32_t signature = 0x12;
    uint16_t nodeID;
    int pm10, pm25;
    int noise_peak;
} __attribute__((packed)) payload_t;

// Heltec V2 Pin Definitions
// NSS: 18, DIO0: 26, RST: 14, DIO1: 35
SX1276 radio = new Module(18, 26, 14, 35);

float FREQ = 868.1; // Frequency
float BW   = 125.0; // Bandwidth
int   SF   = 7;     // Spreading Factor
int   CR   = 8;     // Coding Rate
int   SYNC = 0x12;  // Sync word
int   PWR  = 10;    // Power
int   PRE  = 8;     // Preamble

void setup()
{
    DEBUG_BEGIN(115200);

    DEBUG_PRINT(F("[SX1276] Initializing ... "));

    int state = radio.begin(FREQ, BW, SF, CR, SYNC, PWR, PRE);

    if (state == RADIOLIB_ERR_NONE)
    {
        DEBUG_PRINTLN(F("LoRa initiated."));
    }
    else
    {
        DEBUG_PRINT(F("LoRa failed, code "));
        DEBUG_PRINTLN(state);
        while (true);
    }
}

void loop()
{
    payload_t payload;
    int state = radio.receive((uint8_t *)&payload, sizeof(payload_t));

    if (state == RADIOLIB_ERR_NONE)
    {
        if (incoming.signature == 0xDEADBEEF) {
            Serial.write((uint8_t*)&payload, sizeof(payload_t));
            DEBUG_PRINTLN("Packet Received.");
            DEBUG_PRINT("RSSI: ");
            DEBUG_PRINT(radio.getRSSI());
            DEBUG_PRINTLN(" dBm");
        }
        
    }
    else if (state == RADIOLIB_ERR_RX_TIMEOUT)
    {
        // Normal: No packet received in this polling window
    }
    else if (state == RADIOLIB_ERR_CRC_MISMATCH)
    {
        DEBUG_PRINTLN("CRC error! (Corrupt packet)");
    }
    else
    {
        DEBUG_PRINTLN("Unknown error.");
    }
}