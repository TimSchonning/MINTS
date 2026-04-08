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

#endif // HM330X_PARSER_H