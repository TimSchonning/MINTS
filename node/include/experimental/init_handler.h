#ifndef INIT_HANDLER_H
#define INIT_HANDLER_H

/* EXPERIMENTAL - MOVE WHEN ADDED TO PRODUCTION */

/**
 * @brief Initializes the LoRa radio and performs a handshake with the gateway
 * to receive a unique node ID.
 * @note Sets init_flag to false upon success.
 * @note Is blocking.
 */
void initialise_node();

/**
 * @brief Synchronizes with the gateway and sets a Deep Sleep timer until the next window.
 * @return success
 * @note Is blocking.
 */
bool standby_mode();

#endif