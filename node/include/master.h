#ifndef MASTER_H
#define MASTER_H

// Standard libraries
#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <stddef.h>
#include <cmath>

// Third party libraries
#include <Seeed_HM330X.h>
#include <RadioLib.h>
#include <SPI.h>
#include <Preferences.h>
#include <esp_wifi.h>
#include <esp_bt.h>
#include <WiFi.h>

// Drivers
#include "power.h"
#include "sensor_logic.h"
#include "storage.h"

// Network
#include "config_handler.h"
#include "encode_payload.h"
#include "protocol.h"

// Utilities
#include "debug_macros.h"
#include "error_handler.h"

// Configurations
#include "config.h"

#endif