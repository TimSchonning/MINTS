#ifndef DEBUG_MACROS_H
#define DEBUG_MACROS_H

#include "config.h"
#include "debug_macros.h"
#include "encode_payload.h"
#include "protocol.h"
#include "sensor_logic.h"
#include "utils.h"

#define DEBUG_MODE // Comment this to disable debug mode

#ifdef DEBUG_MODE
  #define DEBUG_PRINT(x) Serial.print(x)
  #define DEBUG_PRINTLN(x) Serial.println(x)
  #define DEBUG_BEGIN(x) Serial.begin(x)
#else
  #define DEBUG_PRINT(x)
  #define DEBUG_PRINTLN(x)
  #define DEBUG_BEGIN(x)
#endif

#endif