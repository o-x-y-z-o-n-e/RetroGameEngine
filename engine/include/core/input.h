#ifndef RGE_INPUT_H
#define RGE_INPUT_H

#include "api/rge.h"

void rge_input_flush_click();
void rge_input_flush_all();
void rge_input_set_state(rge_key_t key, bool down);

#endif