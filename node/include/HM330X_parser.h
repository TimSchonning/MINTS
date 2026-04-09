#ifndef HM330X_PARSER_H
#define HM330X_PARSER_H

#include <Seeed_HM330X.h>

/* Use SerialUSB for SAMD boards, otherwise standard Serial */
#ifdef ARDUINO_SAMD_VARIANT_COMPLIANCE
    #define SERIAL_OUTPUT SerialUSB
#else
    #define SERIAL_OUTPUT Serial
#endif

/**
 * @brief HM330X Sensor Data Buffer Mapping (29 Bytes)
 * * The sensor transmits a 29-byte packet via I2C. Data is sent as Big-Endian 
 * (High Byte followed by Low Byte) for each 16-bit measurement.
 * * | Index | Name          | Description                                    |
 * |-------|---------------|------------------------------------------------|
 * | 0     | Start Byte 1  | Fixed: 0x42 ('B')                              |
 * | 1     | Start Byte 2  | Fixed: 0x4D ('M')                              |
 * | 2-3   | Frame Length  | Length of data frame (usually 28 bytes)        |
 * | 4-5   | PM1.0 (CF=1)  | PM1.0 Std. particulate matter (ug/m3)          |
 * | 6-7   | PM2.5 (CF=1)  | PM2.5 Std. particulate matter (ug/m3)          |
 * | 8-9   | PM10  (CF=1)  | PM10  Std. particulate matter (ug/m3)          |
 * | 10-11 | PM1.0 (ATM)   | PM1.0 Atmospheric environment (ug/m3)          |
 * | 12-13 | PM2.5 (ATM)   | PM2.5 Atmospheric environment (ug/m3)          |
 * | 14-15 | PM10  (ATM)   | PM10  Atmospheric environment (ug/m3)          |
 * | 16-17 | Count 0.3um   | Number of particles > 0.3um in 0.1L air        |
 * | 18-19 | Count 0.5um   | Number of particles > 0.5um in 0.1L air        |
 * | 20-21 | Count 1.0um   | Number of particles > 1.0um in 0.1L air        |
 * | 22-23 | Count 2.5um   | Number of particles > 2.5um in 0.1L air        |
 * | 24-25 | Count 5.0um   | Number of particles > 5.0um in 0.1L air        |
 * | 26-27 | Count 10um    | Number of particles > 10um in 0.1L air         |
 * | 28    | Checksum      | Sum of bytes 0 to 27 (modulo 256)              |
 * * @note Reconstruct 16-bit values using: (buffer[n] << 8) | buffer[n+1]
 */

/**
 * @brief Prints a specific PM measurement to the Serial output.
 * @param str The label for the measurement.
 * @param value The 16-bit concentration value.
 * @return HM330XErrorCode 
 */
HM330XErrorCode print_result(const char* str, uint16_t value);

/**
 * @brief Combines raw bytes and prints human-readable PM concentrations.
 * @param data Pointer to the 29-byte sensor buffer.
 * @return HM330XErrorCode 
 */
HM330XErrorCode parse_result(uint8_t* data);

/**
 * @brief Debug function to print raw HEX data and verify the checksum.
 * @param data Pointer to the 29-byte sensor buffer.
 * @return HM330XErrorCode 
 */
HM330XErrorCode parse_result_value(uint8_t* data);

#endif