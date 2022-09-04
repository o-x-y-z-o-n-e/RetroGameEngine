#include "core/input.h"
#include <stdint.h>
#include <stddef.h>

#define SET(D, B) D |= (1 << B)
#define CLEAR(D, B) D &= ~(1 << B)
#define GET(D, B) D & (1 << B)


//------------------------------------------------------------------------------


static uint8_t key_states[256];
static void(*on_button_down)(rge_key_t key);


//------------------------------------------------------------------------------


bool is_button_press(rge_key_t key) {
	return GET(key_states[key], 0);
}


//------------------------------------------------------------------------------


bool is_button_click(rge_key_t key) {
	return GET(key_states[key], 1);
}


//------------------------------------------------------------------------------


void set_key_state(rge_key_t key, bool down) {
	if(down) {
		if(!is_button_press(key)) {
			SET(key_states[key], 1);
			if(on_button_down != NULL)
				on_button_down(key);
		}

		SET(key_states[key], 0);
	} else {
		CLEAR(key_states[key], 0);
	}
}


//------------------------------------------------------------------------------


void set_on_button_down(void(*func)(rge_key_t key)) {
	on_button_down = func;
}


//------------------------------------------------------------------------------


void flush_click_input() {
	for(int i = 0; i < 256; i++)
		CLEAR(key_states[i], 1);
}


//------------------------------------------------------------------------------


void flush_all_input() {
	for(int i = 0; i < 256; i++)
		key_states[i] = 0;
}