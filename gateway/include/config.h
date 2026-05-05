#ifndef CONFIG_H
#define CONFIG_H

/// @brief Lora configs
int CS = 21, DIO1 = 16, BUSY = 18, RST = 20;

float FREQ = 868.1; // Frequency
float BW = 125.0;   // Bandwidth
int SF = 8;         // Spreading Factor
int CR = 8;         // Coding Rate
int SYNC = 0x12;    // Sync word
int PWR = 13;       // Power
int PRE = 8;        // Preamble
int BAUD = 115200;  // Baud


#endif