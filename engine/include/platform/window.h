#ifndef WINDOW_H
#define WINDOW_H

#include <stdint.h>

typedef struct viewport_t viewport_t;

int create_window();
void close_window();
void poll_window_events();
void refresh_window();
void set_viewport(uint16_t width, uint16_t height);
viewport_t* get_viewport();

void set_title_window(const char* title);

#endif