/**
 * Firmware for LoRa signal experiment.
 * One device is a transmitter and sends many transmissions to another device acting as receiver.
 * When a packet is received, RSSI and SNR is printed.
 * After a specified number of pings, the packet loss percentage as well as average RSSI and average SNR is printed.
 * The next configuration is then changed to the next one until all have been tested.
 * Designed to run in Arduino IDE.
 * Requires two LoRa nodes at the same frequency and spreading factor.
 * Based on the RadioLib library.
 * @see RadioLib GitHub: https://jgromes.github.io/RadioLib/
 * Last updated: 25/04-2026
 */

#include <Arduino.h>
#undef pinMode
#undef digitalWrite
#undef digitalRead

#include <RadioLib.h>

/**
 * Definition of a single radio configuration.
 * Is used in RadioLib's begin function.
 * @see RadioLib documentation.
 * @param float bandwidth: decides which bandwidth to use.
 * @param int spreadingFactor: decides which spreadingFactor to use.
 * @param int codingRate: decides the nominator the coding rate should use.
 * The denominator is always 8, @see RadioLib documentation.
 * @param int power: decides how much power to use.
 */
struct RadioConfig
{
  float bandwidth;
  int spreadingFactor;
  int timeBetweenTx;
};

/**
 * Definition of a configuration's test result.
 * @param float avgRSSI: Sum of reported RSSI values divided by number of received packets.
 * @param float avgSNR: Sum of reported SNR values divided by number of received packets.
 * @param float packetLoss: Percentage of packets not received.
 */
struct ConfigResult
{
  float avgRSSI;
  float avgSNR;
  float packetLoss;
};

/**
 * Stores the data collected from a configuration experiment.
 * @param float totalRSSI: The sum of the RSSI of all packets received.
 * @param float totalSNR: The sum of the SNR of all packets received.
 * @param int numPackets: Number of packets received.
 */
struct CollectedData
{
  float totalRSSI;
  float totalSNR;
  int numPackets;
};

// Give this node a unique ID
int deviceId = 1;

// Experiment Settings
bool isReceiver = true;          // Choose if this node should be the receiver or the transmitter. 
int iterationsPerConfig = 50;                  // Total number of pings in this experiement (must be divisible by length of configs)
String msgToSend = "H";      // Transmission message

/**
 * User-defined tests.
 * Parameter values must be valid.
 * BW: Bandwidth: 7.8, 10.4, 15.6, 20.8, 31.25, 41.7,
 * 62.5, 125.0, 250.0, 500.0
 * SF: Spreading factor: 7 to 12
 */
RadioConfig configs[] = {
    // BW, SF, CR, PWR
    {125.0f, 8, 70}, // Config 2
    {125.0f, 10, 250},  // Config 4
    {125.0f, 12, 1000}, // Config 6
    {250.0f, 8, 35}, // Config 8
    {250.0f, 10, 125},  // Config 10
    {250.0f, 12, 500}, // Config 12
};
#define CR 8 // Coding rate
#define PWR 13 // dBm

const int nmbrOfConfigs = sizeof(configs) / sizeof(RadioConfig);

// LoRa Radio Settings, will not change during the experiment.
const float FREQ = 868.1;                           // Frequency in MHz
const int SYNC = RADIOLIB_SX126X_SYNC_WORD_PRIVATE; // Syncword
const int PRE = 8;                                  // Preamble length
const float TCXO_V = 1.6;                           // TCXO voltage in V

// LoRa GPIO pin mapping (using legacy mode in Arduino IDE)
const int CS = 21;
const int DIO1 = 5;
const int RST = 7;
const int BSY = 6;
const int TXEN = 8;
const int RXEN = 9;

const int buttonHigh = A6;
const int buttonPin = A7;

// Define LoRa radio
SX1262 radio = new Module(CS, DIO1, RST, BSY);

// State Variables
int txState = RADIOLIB_ERR_NONE;
bool transmitFlag = false;
volatile bool receivedFlag = false;

// Interrupt Service Routine
#if defined(ESP8266) || defined(ESP32)
ICACHE_RAM_ATTR
#endif
void setFlag(void)
{
  receivedFlag = true;
}

/**
 * Displays current radio parameter values.
 */
void displayRadioParams(float BW, uint8_t SF)
{
  Serial.print("Frequency: ");
  Serial.print(FREQ);
  Serial.print(" | Bandwidth: ");
  Serial.print(BW);
  Serial.print(" | Spreading Factor: ");
  Serial.println(SF);
}

/**
 * Changes bandwidth, spreading factor, coding rate and power of the LoRa radio.
 */
void setRadio(float BW, uint8_t SF)
{
  Serial.println("Initialising LoRa with parameters:");
  displayRadioParams(BW, SF);

  int state = radio.begin(FREQ, BW, SF, 4, SYNC, PWR, PRE, TCXO_V);

  if (state == RADIOLIB_ERR_NONE)
  {
    Serial.println("LoRa ready.");
    radio.setDio1Action(setFlag); // Ensure interrupt is re-attached
  }
  else
  {
    Serial.print("LoRa failed. Error code: ");
    Serial.println(state);
    while (true)
      ;
  }
}

void experimentSummary(ConfigResult summary[])
{
  Serial.println("The experiment is done. Here are the results:");

  int nrConfigs = nmbrOfConfigs;

  for (int i = 0; i < nrConfigs; i++)
  {
    Serial.print("--- Results for config ");
    Serial.print(i + 1);
    Serial.println(" ---");
    displayRadioParams(configs[i].bandwidth, configs[i].spreadingFactor);
    Serial.println();
    Serial.print("Average RSSI: ");
    Serial.print(summary[i].avgRSSI);
    Serial.println(" dBm");

    Serial.print("Average SNR:  ");
    Serial.print(summary[i].avgSNR);
    Serial.println(" dB");

    Serial.print("Packet loss:  ");
    Serial.print(summary[i].packetLoss);
    Serial.println(" %");
    Serial.println();
  }
}

void awaitButton() {
  Serial.println("Waiting for button press...");

  // "Await" the press: Loop stays here as long as the pin is LOW (not pressed)
  while (analogRead(buttonPin) < 4095) {
    delay(250);
  }
  

  Serial.println("Button pressed! Continuing program...");
}

void receiver() {
  ConfigResult results[nmbrOfConfigs];
  for (int i=0; i<nmbrOfConfigs; i++) {
    awaitButton();
    RadioConfig config = configs[i];
    
    float bw = config.bandwidth;
    int sf = config.spreadingFactor;
    int txDuration = config.timeBetweenTx;
    int totalDuration = iterationsPerConfig * txDuration;
    Serial.print("Beginning to listen ");
    Serial.print(totalDuration / 1000);
    Serial.print(" seconds for config ");
    Serial.println(i+1);

    setRadio(bw, sf);

    CollectedData data;
    data.numPackets = 0;
    data.totalRSSI = 0;
    data.totalSNR = 0;

    int startTime = millis();
    radio.startReceive();
    while(millis() - startTime < totalDuration + 5000) {
      if (receivedFlag) {
        receivedFlag = false;
        String str;
        int state = radio.readData(str);

        if (state == RADIOLIB_ERR_NONE) {
          float RSSI = radio.getRSSI();
          float SNR = radio.getSNR();

          data.numPackets += 1;
          data.totalRSSI += RSSI;
          data.totalSNR += SNR;
          Serial.print(data.numPackets);
          Serial.print("Packet Received! RSSI: ");
          Serial.print(RSSI);
          Serial.print(" dBm, SNR: ");
          Serial.println(SNR);
        }

        // Resume listening for the next packet
        radio.startReceive();
      }
    }
    Serial.println("Listening complete.");
    ConfigResult result;
    result.packetLoss = (1 - data.numPackets / iterationsPerConfig) * 100;
    result.avgRSSI = data.totalRSSI / data.numPackets;
    result.avgSNR = data.totalSNR / data.numPackets;
    results[i] = result;
  }
  experimentSummary(results);
}

void transmitter() {
  for (int i=0; i<nmbrOfConfigs; i++) {
    awaitButton();
    RadioConfig config = configs[i];
    
    float bw = config.bandwidth;
    int sf = config.spreadingFactor;
    Serial.print("Beginning to transmit.");
    setRadio(bw, sf);
    for (int j=0; j<iterationsPerConfig; j++) {
      radio.startTransmit(msgToSend);
      delay(config.timeBetweenTx);
    }
  }
}
 
/**
 * Arduino setup function.
 */
void setup()
{
  Serial.begin(115200);
  delay(1000);
  pinMode(buttonPin, INPUT);
  pinMode(buttonHigh, OUTPUT);
  digitalWrite(buttonHigh, HIGH);
  digitalWrite(buttonPin, LOW);

  while (!Serial)
  {
    delay(10);
  }
  radio.setRfSwitchPins(RXEN, TXEN);

  if (isReceiver)
  {
    Serial.println("Node set as RECEIVER.");
  }
  else
  {
    Serial.println("Node set as TRANSMITTER.");
  }

  if (isReceiver) {
    receiver();
  } else {
    transmitter();
  }
}

void loop() {}