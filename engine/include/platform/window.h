#ifndef RGE_WINDOW_H
#define RGE_WINDOW_H

#include <stdint.h>

typedef struct viewport_t viewport_t;

int rge_window_create();
void rge_window_close();
void rge_window_poll_events();
void rge_window_refresh();
void rge_window_set_viewport(uint16_t width, uint16_t height);
viewport_t* rge_window_get_viewport();

#endif