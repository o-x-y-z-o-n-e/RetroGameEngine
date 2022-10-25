#include "api/rge.h"
#include "core/input.h"
#include "util/bit_flags.h"
#include "platform/system.h"


//------------------------------------------------------------------------------


static uint8_t binding_states[256];
static void(*on_button_down)(rge_input_t binding);


//------------------------------------------------------------------------------


bool rge_input_is_press(rge_input_t binding) {
	return rge_bit_get(binding_states[binding], 0);
}


//------------------------------------------------------------------------------


bool rge_input_is_click(rge_input_t binding) {
	return rge_bit_get(binding_states[binding], 1);
}


//------------------------------------------------------------------------------


void rge_input_set_state(rge_input_t binding, bool down) {
	if(down) {
		if(!rge_input_is_press(binding)) {
			binding_states[binding] = rge_bit_set(binding_states[binding], 1);
			if(on_button_down != NULL)
				on_button_down(binding);
		}

		binding_states[binding] = rge_bit_set(binding_states[binding], 0);
	} else {
		binding_states[binding] = rge_bit_clear(binding_states[binding], 0);
	}
}


//------------------------------------------------------------------------------


void rge_input_set_on_down(void(*func)(rge_input_t binding)) {
	on_button_down = func;
}


//------------------------------------------------------------------------------


void rge_input_flush_click() {
	for(int i = 0; i < 256; i++)
		binding_states[i] = rge_bit_clear(binding_states[i], 1);
}


//------------------------------------------------------------------------------


void rge_input_flush_all() {
	for(int i = 0; i < 256; i++)
		binding_states[i] = 0;
}


//------------------------------------------------------------------------------


float rge_input_get_axis(rge_input_t binding) {
	switch(binding) {
		case RGE_PAD_LT:
		case RGE_PAD_RT:
		case RGE_PAD_LS_AXIS_X:
		case RGE_PAD_LS_AXIS_Y:
		case RGE_PAD_RS_AXIS_X:
		case RGE_PAD_RS_AXIS_Y:
			return rge_system_poll_axis(binding);
	}

	return rge_input_is_press(binding) ? 1.0F : 0.0F;
}