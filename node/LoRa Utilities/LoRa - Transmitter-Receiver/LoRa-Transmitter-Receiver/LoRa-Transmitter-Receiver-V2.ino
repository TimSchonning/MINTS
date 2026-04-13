#include <RadioLib.h>

// För Heltec V2 pins, byt dessa sedan när vi byggt stationerna
// NSS: 18, DIO0: 26, RESET: 14, DIO1: 35
SX1276 radio = new Module(18, 26, 14, 35);

String msg = "Yippie, det funkade!"; // Meddelandet som skickas

int receiveState = RADIOLIB_ERR_NONE;

#define PRG_BTN 0

void transmitterMode(String message)
{
    Serial.println("Changing to transmitter mode.");
    int transmitState = radio.transmit(message);

    Serial.println("Sending data...");

    if (transmitState == RADIOLIB_ERR_NONE)
    {
        Serial.println(F("Message sent."));
    }
    else
    {
        Serial.print(F("Failed to send: "));
        Serial.println(transmitState);
    }
}

int receiverModeNotification()
{
    Serial.println("Changing to receiver mode.");
    // receiveState = radio.startReceive();
}

void receiverMode()
{
    String packet;
    int state = radio.readData(packet);

    if (state == RADIOLIB_ERR_NONE)
    {
        Serial.print(F("Received message "));

        Serial.println(packet);

        radio.startReceive();
    }
}

void setup()
{
    Serial.begin(115200);

    pinMode(21, OUTPUT);
    digitalWrite(21, LOW);
    pinMode(PRG_BTN, INPUT_PULLUP);

    Serial.print(F("Initialising "));

    // Carrier Freq, BW, SF, CR, SyncWord, Power(dBm), PreambleLength
    int radioState = radio.begin(868.1, 125.0, 9, 7, 0x12, 17, 8);

    delay(500);

    if (radioState == RADIOLIB_ERR_NONE)
    {
        Serial.println(F("System ready!"));
        radio.startReceive();
    }
    else
    {
        Serial.print(F("Initialisation failed: "));
        Serial.println(radioState);
        while (true)
            ;
    }
}

void loop()
{
    if (digitalRead(PRG_BTN) == LOW)
    {
        transmitterMode(msg);
        delay(300);

        while (digitalRead(PRG_BTN) == LOW)
            ;
        delay(100);

        receiveState = receiverModeNotification();
    }

    receiverMode();
}