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
 *            The denominator is always 8 @see RadioLib documentation.
 * @param int power: decides how much power to use.
 */
struct RadioConfig {
  float bandwidth;
  int spreadingFactor;
  int codingRate;
  int power;
};

// Give this node a unique ID
int deviceId = 1;

// Experiment Settings
bool initiatingNode = false; // Choose if this node should initiate the experiment
int iterations = 50; // Total number of pings in this experiement (must be divisible by length of configs)
const String msgToSend = "Ping";
int timeBetweenTx = 500;

/**
 * User-defined tests.
 * Parameter values must be valid.
 * BW: Bandwidth: 7.8, 10.4, 15.6, 20.8, 31.25, 41.7, 
 *                62.5, 125.0, 250.0, 500.0
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

// LoRa Radio Settings, will not change during the experiment.
const int FREQ = 868.1;                              // Frequency in MHz
const int SYNC = RADIOLIB_SX126X_SYNC_WORD_PRIVATE;  // Syncword
const int PRE = 8;                                   // Preamble length
const int TCXO_V = 1.6;                              // TCXO voltage in V

// LoRa GPIO pin mapping (using legacy mode in Arduino IDE)
// Adjust to fit your configuration
const int CS  = 21;
const int DIO1 = 5;
const int RST  = 7;
const int BSY = 6;
const int TXEN = 8;
const int RXEN = 9;

// Define LoRa radio
SX1262 radio = new Module(CS, DIO1, RST, BSY);

// States and Flags
int txState = RADIOLIB_ERR_NONE;
bool transmitFlag = false;
volatile bool operationDone = false;

// Interrupt Service Routine
#if defined(ESP8266) || defined(ESP32)
  ICACHE_RAM_ATTR
#endif
void setFlag(void) {
  operationDone = true;
}

/**
 * Get the length of an RadioConfig array.
 * @param RadioConfig cfg: Pointer to an array of RadioConfig structs.
 * @returns Length of the array.
 */
int len(RadioConfig *cfg) {
  return sizeof(configs) / sizeof(RadioConfig);
}

/**
 * Changes bandwidth, spreading factor, coding rate and power of the LoRa radio.
 * If new initialisation of radio fails, error code is printed.
 * @see RadioLib documentation for error codes.
 * @param float BW: New bandwidth in MHz.
 * @param uint8_t SF: New spreading factor.
 * @param uint8_t CR: New coding rate.
 * @param uing8_t PWR: New power.
 */
void setRadio(float BW, uint8_t SF, uint8_t CR, uint8_t PWR) {
  Serial.println("Initialising LoRa with parameters:");
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

  int state = radio.begin(FREQ, BW, SF, CR, SYNC, PWR, PRE, TCXO_V);

    if (state == RADIOLIB_ERR_NONE) {
    Serial.println("LoRa ready.");
  } else {
    Serial.print("LoRa failed, adjust your parameters and try again.");
    Serial.println("Error code: ");
    Serial.println(state);
    while (true);
  }
}

/**
 * Pings a node and listens for a response.
 * @param int pings: Number of pings to transmit.
 * @returns Number of received packets.
 */
int pingNode(int pings){
  int receivedPackets = 0;

  for (int i = 0; i < pings; i++) {
    if(operationDone) {
    operationDone = false;

    if(transmitFlag) {
      // Previous Operation was Transmit
      if (txState == RADIOLIB_ERR_NONE) {
        Serial.println("Transmission finished!");
      } else {
        Serial.print("TX failed, code ");
        Serial.println(txState);
      }

      // Switch to listening
      radio.startReceive();
      transmitFlag = false;

    } else {
      // Previous Operation was Receive
      String str;
      int state = radio.readData(str);

      if (state == RADIOLIB_ERR_NONE) {
        Serial.println("Received packet!");
        Serial.print("Data:\t\t"); Serial.println(str);
        Serial.print("RSSI:\t\t"); Serial.print(radio.getRSSI()); Serial.println(" dBm");
        Serial.print("SNR:\t\t"); Serial.print(radio.getSNR()); Serial.println( "dB");

        ++receivedPackets;
      }

      delay(timeBetweenTx);

      // Send response
      Serial.print("Sending response...");
      String msg = "Ping from ID " + String(deviceId);
      txState = radio.startTransmit(msg);

      if (txState == RADIOLIB_ERR_NONE) {
        Serial.println("Sent.");
      } else {
        Serial.println("An error occured. Error code: ");
        Serial.print(txState);
      }

      transmitFlag = true;
      }
    }
  }

  return receivedPackets;
}

/**
 * Runs the specified configs.
 * @param int nrOfPackets: Number of packets to transmit.
 * @param int currentConfig: The config used.
 */
void testConfig(int nrOfPackets, int currentConfig) {
  Serial.println("");
  Serial.print("--- Config ");
  Serial.print(currentConfig + 1);
  Serial.print(" ---");

  float bw = configs[currentConfig].bandwidth;
  int sf = configs[currentConfig].spreadingFactor;
  int cr = configs[currentConfig].codingRate;
  int pwr = configs[currentConfig].power;
  
  setRadio(bw, sf, cr, pwr);

  int receivedPackets = pingNode(nrOfPackets);

  Serial.println("Packets sent: ");
  Serial.print(nrOfPackets);
  Serial.println("Packets received: ");
  Serial.print(receivedPackets);

  float packetLoss = (nrOfPackets - receivedPackets) / nrOfPackets;

  Serial.println("Packet Loss: ");
  Serial.print(packetLoss * 100);
  Serial.print("%");

  Serial.println("");
}

/**
 * Arduino setup function.
 * Initialises the system.
 * Makes a test transmit to verify the connecion.
 */
void setup() {
  Serial.begin(115200);

  while (!Serial) {
    Serial.println("Serial failed.");
    delay(10000);
  }

  int radioConfigs = len(configs);

  if ((iterations % radioConfigs) != 0 || iterations <= 0 || radioConfigs <= 0) {
    Serial.println("The experiment configuration you have chosen is invalid.");
    while(true);
  }

  radio.setRfSwitchPins(RXEN, TXEN);

  // Initialise LoRa Radio
  Serial.print("Initialising LoRa...");

  setRadio(125.0, 9, 7, 10);
  int state = radio.begin(FREQ, 125.0, 9, 7, SYNC, 10, PRE, TCXO_V);

  // Sets the Interrupt Action
  radio.setDio1Action(setFlag);

  // Initial Transmission
  if (initiatingNode == true) {
    Serial.print("Sending start-up packet... ");
    txState = radio.startTransmit("ping");
    transmitFlag = true;
  } else {
    Serial.print("Listening at frequency: ");
    Serial.print(FREQ);

    state = radio.startReceive();
    if (state == RADIOLIB_ERR_NONE) {
      Serial.print("Packet received, starting experiment.");
  } else {
      Serial.print("LoRa failed, error code: ");
      Serial.println(state);
      while (true);
    }
  }
}

/**
 * Main loop, runs the experiment.
 */
void loop() {
  int nmbrOfConfigs = len(configs);

  if (nmbrOfConfigs <= 0) {
    Serial.print("Invalid number of configurations.");
    while(true);
  }

  int packetsToSend = iterations/nmbrOfConfigs;
  int currentConfig = 0;

  if (currentConfig < nmbrOfConfigs) {
    testConfig(packetsToSend, currentConfig);
    ++currentConfig;
  } else {
    Serial.print("The experiment is done.");
    while(true) {
      delay(10000);
    }    
  }
}