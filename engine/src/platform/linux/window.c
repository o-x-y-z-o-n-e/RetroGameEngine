#ifdef SYS_LINUX
#include "api/rge.h"
#include "platform/window.h"

int rge_window_create() {
    return 0;
}


//------------------------------------------------------------------------------


void rge_window_close() {

}


//------------------------------------------------------------------------------


void rge_window_poll_events() {

}


//------------------------------------------------------------------------------


void rge_window_refresh() {

}


//------------------------------------------------------------------------------


void rge_window_set_viewport(uint16_t width, uint16_t height) {

}


//------------------------------------------------------------------------------


viewport_t* rge_window_get_viewport() {
    return 0;
}


//------------------------------------------------------------------------------


void rge_window_set_title(const char* title) {

}

#endif