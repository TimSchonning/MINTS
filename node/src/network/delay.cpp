#include "master.h"

void random_tx_delay(uint16_t max_delay) {
    srand((unsigned int)time(NULL) + node_id);
    delay((rand() % max_delay) * S_TO_mS);
}