#include <SPI.h>
#include <LoRa.h>
#include <U8x8lib.h> // För OLED-skärmen

// Heltec V2 Pin Definitions
#define SCK 5
#define MISO 19
#define MOSI 27
#define SS 18
#define RST 14
#define DIO0 26
#define PRG_BTN 0

long freqs[] = {868100000, 868300000, 868500000, 867100000, 867400000}; // Frequencies for Schweden (EU)
int set_frequency = freqs[0]; // Change between 0 to 4 for different frequencies.
char *user = "David"; // Change to the correct user
char *msg = "Hejsan!"; // Message to send
int mode = 0; // 0 is receiver mode, 1 is transmitter mode. Don't change.

U8X8_SSD1306_128X64_NONAME_SW_I2C display(15, 4, 16);

void transmitterMode() {
  Serial.println("Changing to transmitter mode.");
  display.drawString(0, 2, "LoRa Transmitter");
  display.drawString(0, 4, (String("Freq: ") + (set_frequency/1000000.0) + " MHz").c_str());

  delay(5000);

  display.clearLine(2);
  display.clearLine(4);

  display.drawString(0, 0, "Sending...");
  delay(5000);

  display.clearLine(4);
  display.drawString(0, 0, (String("Sent: ") + msg).c_str());

  LoRa.beginPacket();
  LoRa.print(msg);
  LoRa.print((String("Message sent by ") + user).c_str());
  LoRa.endPacket();
  delay(1000);
  display.clearLine(0);
}

void receiverMode() {
  Serial.println("Changing to receiver mode.");
  display.drawString(0, 2, "LoRa Receiver");
  display.drawString(0, 4, (String("Freq: ") + (set_frequency/1000000) + " MHz").c_str());
}

void setup() {
  Serial.begin(115200);
  while(!Serial);
  pinMode(PRG_BTN, INPUT_PULLUP);

  display.begin();
  display.setFont(u8x8_font_chroma48medium8_r);
  display.drawString(0, 0, "Init System");

  SPI.begin(SCK, MISO, MOSI, SS);
  LoRa.setPins(SS, RST, DIO0);

  delay(3000);
  display.clearLine(0);

  if(!LoRa.begin(set_frequency)) {
    display.drawString(0, 2, "LoRa FAILED :()");
    while(1);
  }

  Serial.println("System ready.");

  receiverMode();
}

void loop() {
  if (digitalRead(PRG_BTN) == LOW) { // Button press, change mode
    transmitterMode();

    delay(300);
    while(digitalRead(PRG_BTN) == LOW); // Wait for button to be released
    receiverMode();
  }
  
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    Serial.println("Received packet '");
    
    display.clearLine(2);
    display.clearLine(4);
    display.drawString(0, 0, "Packet received!");

    while(LoRa.available()) {
      Serial.print((char)LoRa.read());
    }

    Serial.print("' with RSSI "); // RSSI = Received Signal Strength Indicator
    Serial.println(LoRa.packetRssi() + " dBm");

    delay(1000);
    display.clearLine(0);
  }
}
