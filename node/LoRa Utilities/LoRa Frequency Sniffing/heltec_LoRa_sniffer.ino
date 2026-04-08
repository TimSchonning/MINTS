#include <SPI.h>
#include <LoRa.h>
#include <U8x8lib.h>

// Heltec V2 Pin Definitions
#define SCK 5
#define MISO 19
#define MOSI 27
#define SS 18
#define RST 14
#define DIO0 26
#define PRG_BTN 0  // Onboard PRG button

// Swedish Frequency List (EU868)
long freqs[] = {868100000, 868300000, 868500000, 867100000, 867400000};
int freqIndex = 0;
int maxFreqs = 5;

U8X8_SSD1306_128X64_NONAME_SW_I2C display(15, 4, 16);

void updateFrequency() {
  LoRa.setFrequency(freqs[freqIndex]);
  
  display.clearLine(2);
  display.setCursor(0, 2);
  display.print("Freq: ");
  display.print(freqs[freqIndex] / 1000000.0, 1);
  display.print("MHz");
  
  Serial.print("Tuned to: ");
  Serial.print(freqs[freqIndex] / 1000000.0);
  Serial.println(" MHz");
}

void setup() {
  Serial.begin(115200);
  pinMode(PRG_BTN, INPUT_PULLUP);
  
  display.begin();
  display.setFont(u8x8_font_chroma48medium8_r);
  display.drawString(0, 0, "Sniffer 3000");

  SPI.begin(SCK, MISO, MOSI, SS);
  LoRa.setPins(SS, RST, DIO0);

  if (!LoRa.begin(freqs[0])) { 
    display.drawString(0, 2, "LoRa Fail"); 
    while(1); 
  }
  
  updateFrequency();
  Serial.println("--- Redo att sniffa ---");
}

void loop() {
  if (digitalRead(PRG_BTN) == LOW) {
    freqIndex = (freqIndex + 1) % maxFreqs; // Cycle 0, 1, 2, 3, 4 -> 0
    updateFrequency();
    
    delay(300); // Simple debounce
    while(digitalRead(PRG_BTN) == LOW); // Wait for button release
  }

  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    Serial.println("Hittat!"); 
    
    Serial.print("RSSI: "); Serial.print(LoRa.packetRssi()); Serial.println(" dBm");
    Serial.print("SNR: "); Serial.println(LoRa.packetSnr());

    display.clearLine(4);
    display.drawString(0, 4, "Hittat!");
    display.clearLine(5);
    display.setCursor(0, 5); 
    display.print("RSSI: "); 
    display.print(LoRa.packetRssi());

    while (LoRa.available()) { LoRa.read(); } 
  }
}