#ifndef INIT_HANDLER_H
#define INIT_HANDLER_H

/**
 * @brief Initializes the LoRa radio and performs a handshake with the gateway
 * to receive a unique node ID.
 * @note Sets init_flag to false upon success.
 * @note enters standby mode until clearence is received from the gateway
 * @note Is blocking.
 */
void initialise_node();

#endif