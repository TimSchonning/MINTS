/**
 * Firmware for LoRa signal experiment.
 * A "ping-pong" like signal transmission where one device initiates the experiment, the other listens.
 * When a packet is received, RSSI and SNR is printed.
 * After a specified number of pings, radio configuration is updated and packet loss is printed.
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
  int codingRate;
  int power;
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

// Give this node a unique ID
int deviceId = 1;

// Experiment Settings
bool initiatingNode = false;          // Choose if this node should initiate the experiment
int iterations = 50;                  // Total number of pings in this experiement (must be divisible by length of configs)
const String msgToSend = "Ping";      // Transmission message
int timeBetweenTx = 500;              // Time in ms between transmissions
unsigned long responseTimeout = 2000; // Counts packet loss if timeout reached

/**
 * User-defined tests.
 * Parameter values must be valid.
 * BW: Bandwidth: 7.8, 10.4, 15.6, 20.8, 31.25, 41.7,
 * 62.5, 125.0, 250.0, 500.0
 * SF: Spreading factor: 7 to 12
 * CR: Coding rate: 5 to 8
 * PWR: Power: -17 to 22
 */
RadioConfig configs[] = {
    // BW, SF, CR, PWR
    {125.0f, 10, 6, 17}, // Config 1
    {125.0f, 12, 8, 20}, // Config 2
    {62.5f, 11, 8, 22},  // Config 3
    {62.5f, 12, 8, 22},  // Config 4
    {31.25f, 12, 8, 22}, // Config 5
};

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

// Define LoRa radio
SX1262 radio = new Module(CS, DIO1, RST, BSY);

// State Variables
int txState = RADIOLIB_ERR_NONE;
bool transmitFlag = false;
volatile bool operationDone = false;

// Interrupt Service Routine
#if defined(ESP8266) || defined(ESP32)
ICACHE_RAM_ATTR
#endif
void setFlag(void)
{
  operationDone = true;
}

/**
 * Displays current radio parameter values.
 */
void displayRadioParams(float BW, uint8_t SF, uint8_t CR, uint8_t PWR)
{
  Serial.print("Frequency: ");
  Serial.print(FREQ);
  Serial.print(" | Bandwidth: ");
  Serial.print(BW);
  Serial.print(" | Spreading Factor: ");
  Serial.print(SF);
  Serial.print(" | Coding Rate: ");
  Serial.print(CR);
  Serial.print(" | Power: ");
  Serial.print(PWR);
}

/**
 * Changes bandwidth, spreading factor, coding rate and power of the LoRa radio.
 */
void setRadio(float BW, uint8_t SF, uint8_t CR, uint8_t PWR)
{
  Serial.println("Initialising LoRa with parameters:");
  displayRadioParams(BW, SF, CR, PWR);

  int state = radio.begin(FREQ, BW, SF, CR, SYNC, PWR, PRE, TCXO_V);

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

/**
 * Pings a node and listens for a response.
 * @param int pings: Number of pings to transmit.
 * @returns A three element array of floats.
 */
float *pingNode(int pings)
{
  static float collectedData[3];
  collectedData[0] = 0; // Received count
  collectedData[1] = 0; // Sum of RSSIs
  collectedData[2] = 0; // Sum of SNRs

  for (int i = 0; i < pings; i++)
  {
    // Start Transmission
    operationDone = false;
    transmitFlag = true;
    txState = radio.startTransmit("Ping");

    // Wait for TX to finish
    while (!operationDone)
    {
      yield();
    }

    // Switch to listening
    operationDone = false;
    transmitFlag = false;
    radio.startReceive();

    // Timeout
    unsigned long startWait = millis();
    bool received = false;

    while (millis() - startWait < responseTimeout)
    {
      if (operationDone)
      {
        String str;
        int state = radio.readData(str);
        if (state == RADIOLIB_ERR_NONE)
        {
          float RSSI = radio.getRSSI();
          float SNR = radio.getSNR();

          collectedData[0]++;
          collectedData[1] += RSSI;
          collectedData[2] += SNR;
          received = true;

          Serial.print("Packet Received! RSSI: ");
          Serial.print(RSSI);
          Serial.println(" dBm");
        }
        break;
      }
      yield();
    }

    if (!received)
    {
      Serial.println("Packet Lost (Timeout)");
    }

    delay(timeBetweenTx);
  }

  // Calculate Averages
  if (collectedData[0] > 0)
  {
    collectedData[1] = collectedData[1] / collectedData[0];
    collectedData[2] = collectedData[2] / collectedData[0];
  }

  return collectedData;
}

/**
 * Runs the specified configs.
 */
ConfigResult testConfig(int nrOfPackets, int currentConfig)
{
  ConfigResult result;

  Serial.println("");
  Serial.print("--- Config ");
  Serial.print(currentConfig + 1);
  Serial.print(" ---");

  float bw = configs[currentConfig].bandwidth;
  int sf = configs[currentConfig].spreadingFactor;
  int cr = configs[currentConfig].codingRate;
  int pwr = configs[currentConfig].power;

  setRadio(bw, sf, cr, pwr);

  float *pingResult = pingNode(nrOfPackets);
  int receivedPackets = (int)pingResult[0];

  Serial.print("Packets sent: ");
  Serial.println(nrOfPackets);
  Serial.print("Packets received: ");
  Serial.println(receivedPackets);

  float packetLoss = ((float)(nrOfPackets - receivedPackets) / nrOfPackets) * 100.0;

  result.packetLoss = packetLoss;
  result.avgRSSI = pingResult[1];
  result.avgSNR = pingResult[2];

  Serial.print("Packet Loss: ");
  Serial.print(packetLoss);
  Serial.println("%");

  return result;
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
    displayRadioParams(configs[i].bandwidth, configs[i].spreadingFactor,
                       configs[i].codingRate, configs[i].power);
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

/**
 * Arduino setup function.
 */
void setup()
{
  Serial.begin(115200);

  while (!Serial)
  {
    delay(10);
  }

  if ((iterations % nmbrOfConfigs) != 0 || iterations <= 0)
  {
    Serial.println("Invalid configuration: iterations must be divisible by config count.");
    while (true)
      ;
  }

  radio.setRfSwitchPins(RXEN, TXEN);

  if (initiatingNode)
  {
    Serial.println("Node set as INITIATOR.");
  }
  else
  {
    Serial.println("Node set as LISTENER.");
  }
}

// Variables across main loop
int currentConfig = 0;
ConfigResult results[nmbrOfConfigs];

/**
 * Main loop, runs the experiment.
 */
void loop()
{
  if (currentConfig < nmbrOfConfigs)
  {
    int packetsToSend = iterations / nmbrOfConfigs;
    results[currentConfig] = testConfig(packetsToSend, currentConfig);
    currentConfig++;
  }
  else
  {
    experimentSummary(results);
    while (true)
    {
      delay(10000);
    }
  }
}