#include "config.h"
#include "debug_macros.h"
#include "encode_payload.h"
#include "sensor_logic.h"
#include "utils.h"

#include <stdint.h>
#include <RadioLib.h>

extern SX1262 radio;

void random_tx_delay() {
    srand((unsigned int)time(NULL) + node_id);
    delay((rand() % MAX_TX_DELAY_S) * S_TO_mS);
}