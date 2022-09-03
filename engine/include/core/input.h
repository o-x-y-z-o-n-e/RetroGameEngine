#ifndef INPUT_H
#define INPUT_H

#include <stdbool.h>

#include "api/input_def.h"

bool is_button_press(key_t key);
bool is_button_click(key_t key);
void flush_click_input();
void flush_all_input();
void set_key_state(key_t key, bool down);
void set_on_button_down(void(*func)(key_t key));

#endif