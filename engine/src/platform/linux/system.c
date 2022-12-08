#ifdef SYS_LINUX
#include "api/rge.h"
#include "platform/system.h"

int rge_system_init() {
    return 0;
}


//------------------------------------------------------------------------------


uint64_t rge_system_get_time() {
    return 0;
}


//------------------------------------------------------------------------------


uint8_t rge_system_parse_key(uint16_t system_key) {
    return 0;
}


//------------------------------------------------------------------------------


void rge_system_poll_gamepad() {

}

#endif