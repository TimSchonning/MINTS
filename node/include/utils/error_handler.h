#ifndef ERROR_HANDLER_H
#define ERROR_HANDLER_H

#include <cstdint>

/**
 * @brief Logic for handling radio status codes.
 * @param state The return code from the radio library.
 * @param message The error message to print if the state is not successful.
 * @param inform_gateway True = sends a message to the gateway with the specified error_code.
 * @param error_code the error code that gets sent to the gateway.
 * @return true if an error occurred, false if successful.
 * @note if inform_gateway is set to false, set error_code to UNDEFINED_ERROR
 */
bool error_handler(int16_t state, bool inform_gateway, uint8_t error_code, const char* message);


#endif