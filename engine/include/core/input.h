#ifndef RGE_INPUT_H
#define RGE_INPUT_H

#include "api/rge.h"

void rge_input_flush_click();
void rge_input_flush_all();
void rge_input_key_set_state(rge_input_t binding, bool down);
void rge_input_gamepad_set_state(int gamepad, rge_input_t binding, bool down);
void rge_input_gamepad_set_axis(int gamepad, rge_input_t binding, float value);

#endif