#include "api/rge.h"
#include "core/input.h"
#include "util/bit_flags.h"


//------------------------------------------------------------------------------


static uint8_t key_states[256];
static void(*on_button_down)(rge_key_t key);


//------------------------------------------------------------------------------


bool rge_input_is_press(rge_key_t key) {
	return rge_bit_get(key_states[key], 0);
}


//------------------------------------------------------------------------------


bool rge_input_is_click(rge_key_t key) {
	return rge_bit_get(key_states[key], 1);
}


//------------------------------------------------------------------------------


void rge_input_set_state(rge_key_t key, bool down) {
	if(down) {
		if(!rge_input_is_press(key)) {
			key_states[key] = rge_bit_set(key_states[key], 1);
			if(on_button_down != NULL)
				on_button_down(key);
		}

		key_states[key] = rge_bit_set(key_states[key], 0);
	} else {
		key_states[key] = rge_bit_clear(key_states[key], 0);
	}
}


//------------------------------------------------------------------------------


void rge_input_set_on_down(void(*func)(rge_key_t key)) {
	on_button_down = func;
}


//------------------------------------------------------------------------------


void rge_input_flush_click() {
	for(int i = 0; i < 256; i++)
		key_states[i] = rge_bit_clear(key_states[i], 1);
}


//------------------------------------------------------------------------------


void rge_input_flush_all() {
	for(int i = 0; i < 256; i++)
		key_states[i] = 0;
}