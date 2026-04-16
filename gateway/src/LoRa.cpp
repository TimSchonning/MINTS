#include <RadioLib.h>

// Packet data format
typedef struct
{
    uint32_t signature = 0xDEADBEEF;
    uint8_t nodeID;
    uint8_t pm10, pm25;
    uint16_t noise_peak;
} __attribute__((packed)) payload_t;

// Heltec V2 Pin Definitions
// NSS: 18, DIO0: 26, RST: 14, DIO1: 35
SX1276 radio = new Module(18, 26, 14, 35);

float FREQ = 868.1; // Frequency
float BW = 125.0;   // Bandwidth
int SF = 7;         // Spreading Factor
int CR = 8;         // Coding Rate
int SYNC = 0x12;    // Sync word
int PWR = 10;       // Power
int PRE = 8;        // Preamble

void setup()
{
    Serial.begin(115200);

    int state = radio.begin(FREQ, BW, SF, CR, SYNC, PWR, PRE);

    if (state != RADIOLIB_ERR_NONE)
    {
        Serial.print(F("LoRa failed, code "));
        Serial.println(state);
        while (true)
            ;
    }
}

void loop()
{
    payload_t payload;
    int state = radio.receive((uint8_t *)&payload, sizeof(payload_t));

    if (state == RADIOLIB_ERR_NONE)
    {
        Serial.write((uint8_t *)&payload, sizeof(payload_t));
    }
    else if (state == RADIOLIB_ERR_RX_TIMEOUT)
    {
        // Normal: No packet received in this polling window
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