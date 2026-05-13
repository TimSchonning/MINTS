#ifndef CONFIG_HANDLER_H
#define CONFIG_HANDLER_H

/**
 * @brief Sets the node to config mode - where it can receive updates to state RTC variables.
 * @note Starts and sleeps the radio upon use.
 * @note Acks the gateway upon received config message
 */
void config_mode();


#endif