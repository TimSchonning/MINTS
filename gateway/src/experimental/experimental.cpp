#include <cstdint>
#include "RadioLib.h"

bool IdAssignment() {
    uint8_t id = 1;     //TODO: ID from db. 1 is placeholder.
    // TODO: db error handling
    
    msg_ack_t idReqACK;
    idReqACK.node_id = id;  // The new ID!
    idReqACK.ack_for = MSG_TYPE_JOIN_REQ;

    int state = radio.transmit((uint8_t*)&idReqACK, sizeof(msg_ack_t));
    //error_handler(state);  // TODO: error handling
    return (state == RADIOLIB_ERR_NONE); // If succeeded return true
}