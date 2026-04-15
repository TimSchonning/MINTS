#include <RadioLib.h>
#include <U8x8lib.h>

// Structure to hold our sensor data
typedef struct
{
  int pm10, pm25;
  int noise_peak;
} __attribute__((packed)) payload_t;

// Heltec V2 Pin Definitions
// NSS: 18, DIO0: 26, RST: 14, DIO1: 35
SX1276 radio = new Module(18, 26, 14, 35);

#define PRG_BTN 0

// Swedish Frequency List
float freqs[] = {868.1, 868.3, 868.5, 867.1, 867.4};
int freqIndex = 0;
int maxFreqs = 5;

// Display Pins for Heltec V2 (SDA: 15, SCL: 4, RST: 16)
U8X8_SSD1306_128X64_NONAME_SW_I2C display(15, 4, 16);

void updateFrequency()
{
  int state = radio.setFrequency(freqs[freqIndex]);

  if (state == RADIOLIB_ERR_NONE)
  {
    display.clearLine(2);
    display.setCursor(0, 2);
    display.print("Freq: ");
    display.print(freqs[freqIndex], 1);
    display.print("MHz");

    Serial.print("\n>>> Tuned to: ");
    Serial.print(freqs[freqIndex]);
    Serial.println(" MHz <<<");
  }
  else
  {
    Serial.print("Freq set failed, code: ");
    Serial.println(state);
  }
}

void setup()
{
  Serial.begin(115200);
  pinMode(PRG_BTN, INPUT_PULLUP);

  display.begin();
  display.setFont(u8x8_font_chroma48medium8_r);
  display.drawString(0, 0, "LoRa Sniffer");

  Serial.print(F("[SX1276] Initializing ... "));

  // Initialize: Freq, BW, SF, CR, SyncWord, Power, Preamble
  int state = radio.begin(868.1, 125.0, 7, 8, 0x12, 10, 8);

  if (state == RADIOLIB_ERR_NONE)
  {
    Serial.println(F("success!"));
  }
  else
  {
    Serial.print(F("failed, code "));
    Serial.println(state);
    display.drawString(0, 2, "Init Failed!");
    while (true)
      ;
  }

  updateFrequency();
}

void loop()
{
  // 1. Handle Button Press to switch frequencies
  if (digitalRead(PRG_BTN) == LOW)
  {
    freqIndex = (freqIndex + 1) % maxFreqs;
    updateFrequency();
    delay(300); // Debounce
    while (digitalRead(PRG_BTN) == LOW)
      ; // Wait for release
  }

  // 2. Check for incoming packets
  payload_t payload;
  int state = radio.receive((uint8_t *)&payload, sizeof(payload_t));

  if (state == RADIOLIB_ERR_NONE)
  {
    // Serial Output for Debugging
    Serial.println("--- Packet Received ---");
    Serial.print("PM10: ");
    Serial.println(payload.pm10);
    Serial.print("PM2.5: ");
    Serial.println(payload.pm25);
    Serial.print("Noise: ");
    Serial.println(payload.noise_peak);
    Serial.print("RSSI: ");
    Serial.print(radio.getRSSI());
    Serial.println(" dBm");
    Serial.println("-----------------------");

    // Display Update
    display.clearLine(4);
    display.drawString(0, 4, "New Packet!");

    // Print PM10, PM2.5, and Noise on Row 5
    // Format: "10:XX 25:XX N:XX"
    char buffer[17];
    snprintf(buffer, sizeof(buffer), "10:%d 25:%d N:%d", payload.pm10, payload.pm25, payload.noise_peak);
    display.clearLine(5);
    display.drawString(0, 5, buffer);

    // Print RSSI and SNR on Row 6
    display.clearLine(6);
    display.setCursor(0, 6);
    display.print("R:");
    display.print((int)radio.getRSSI());
    display.print(" S:");
    display.print((int)radio.getSNR());
  }
  else if (state == RADIOLIB_ERR_RX_TIMEOUT)
  {
    // Normal: No packet received in this polling window
  }
  else if (state == RADIOLIB_ERR_CRC_MISMATCH)
  {
    Serial.println("CRC error! (Corrupt packet)");
  }
}