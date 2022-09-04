#ifndef INPUT_H
#define INPUT_H

#include <stdbool.h>

#include "api/input_def.h"

bool is_button_press(rge_key_t key);
bool is_button_click(rge_key_t key);
void flush_click_input();
void flush_all_input();
void set_key_state(rge_key_t key, bool down);
void set_on_button_down(void(*func)(rge_key_t key));

#endif