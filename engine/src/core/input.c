#include "api/rge.h"
#include "core/input.h"
#include "util/bit_flags.h"
#include "platform/system.h"


#define IS_GAMEPAD(X) ((X) >= RGE_PAD_D_LEFT && (X) <= RGE_PAD_START)


//------------------------------------------------------------------------------


typedef struct gamepad_state_t {
	uint8_t d_left;
	uint8_t d_up;
	uint8_t d_right;
	uint8_t d_down;

	uint8_t west;
	uint8_t north;
	uint8_t east;
	uint8_t south;

	uint8_t left_trigger;
	uint8_t right_trigger;

	uint8_t left_bumper;
	uint8_t right_bumper;

	uint8_t left_stick;
	uint8_t right_stick;

	uint8_t options;
	uint8_t start;

	uint8_t left_stick_left;
	uint8_t left_stick_up;
	uint8_t left_stick_right;
	uint8_t left_stick_down;

	uint8_t right_stick_left;
	uint8_t right_stick_up;
	uint8_t right_stick_right;
	uint8_t right_stick_down;

	float left_stick_axis_x;
	float left_stick_axis_y;
	float right_stick_axis_x;
	float right_stick_axis_y;

	float left_trigger_axis;
	float right_trigger_axis;
} gamepad_state_t;


//------------------------------------------------------------------------------


static gamepad_state_t gamepad_states[4];
static uint8_t binding_states[256];
static void(*on_button_down)(rge_input_t binding);


//------------------------------------------------------------------------------


static uint8_t* get_gamepad_ptr(int gamepad, rge_input_t binding) {
	gamepad_state_t* g = &gamepad_states[gamepad];
	switch(binding) {
		case RGE_PAD_D_LEFT:
			return &g->d_left;
		case RGE_PAD_D_UP:
			return &g->d_up;
		case RGE_PAD_D_RIGHT:
			return &g->d_right;
		case RGE_PAD_D_DOWN:
			return &g->d_down;

		case RGE_PAD_WEST:
			return &g->west;
		case RGE_PAD_NORTH:
			return &g->north;
		case RGE_PAD_EAST:
			return &g->east;
		case RGE_PAD_SOUTH:
			return &g->south;

		case RGE_PAD_LS_LEFT:
			return &g->left_stick_left;
		case RGE_PAD_LS_UP:
			return &g->left_stick_up;
		case RGE_PAD_LS_RIGHT:
			return &g->left_stick_right;
		case RGE_PAD_LS_DOWN:
			return &g->left_stick_down;

		case RGE_PAD_RS_LEFT:
			return &g->right_stick_left;
		case RGE_PAD_RS_UP:
			return &g->right_stick_up;
		case RGE_PAD_RS_RIGHT:
			return &g->right_stick_right;
		case RGE_PAD_RS_DOWN:
			return &g->right_stick_down;

		case RGE_PAD_LB:
			return &g->left_bumper;
		case RGE_PAD_RB:
			return &g->right_bumper;

		case RGE_PAD_LT:
			return &g->left_trigger;
		case RGE_PAD_RT:
			return &g->right_trigger;

		case RGE_PAD_L3:
			return &g->left_stick;
		case RGE_PAD_R3:
			return &g->right_stick;

		case RGE_PAD_OPTIONS:
			return &g->options;
		case RGE_PAD_START:
			return &g->start;

		default:
			return NULL;
	}
}


//------------------------------------------------------------------------------


static void flush_click_gamepad(int gamepad) {
	for(int i = RGE_PAD_D_LEFT; i <= RGE_PAD_START; i++) {
		uint8_t* s = get_gamepad_ptr(gamepad, i);
		if(s != NULL)
			*s = rge_bit_clear(*s, 1);
	}
}


//------------------------------------------------------------------------------


bool rge_input_is_press(rge_input_t binding) {
	if(IS_GAMEPAD(binding))
		return rge_input_gamepad_is_press(0, binding);

	return rge_bit_get(binding_states[binding], 0);
}


//------------------------------------------------------------------------------


bool rge_input_is_click(rge_input_t binding) {
	if(IS_GAMEPAD(binding))
		return rge_input_gamepad_is_click(0, binding);

	return rge_bit_get(binding_states[binding], 1);
}


//------------------------------------------------------------------------------


void rge_input_key_set_state(rge_input_t binding, bool down) {
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

	for(int i = 0; i < 4; i++)
		flush_click_gamepad(i);
}


//------------------------------------------------------------------------------


void rge_input_flush_all() {
	for(int i = 0; i < 256; i++)
		binding_states[i] = 0;

	for(int i = 0; i < 4; i++)
		gamepad_states[i] = (const gamepad_state_t){0};
}


//------------------------------------------------------------------------------


float rge_input_get_axis(rge_input_t binding) {
	if(IS_GAMEPAD(binding))
		return rge_input_gamepad_get_axis(0, binding);

	return rge_input_is_press(binding) ? 1.0F : 0.0F;
}


//------------------------------------------------------------------------------


void rge_input_gamepad_set_state(int gamepad, rge_input_t binding, bool down) {
	if(gamepad < 0 || gamepad >= 4)
		return;

	uint8_t* state = get_gamepad_ptr(gamepad, binding);

	if(down) {
		if(!rge_bit_get(*state, 0)) {
			*state = rge_bit_set(*state, 1);
			if(on_button_down != NULL)
				on_button_down(binding);
		}

		*state = rge_bit_set(*state, 0);
	} else {
		*state = rge_bit_clear(*state, 0);
	}
}


//------------------------------------------------------------------------------


void rge_input_gamepad_set_axis(int gamepad, rge_input_t binding, float value) {
	if(gamepad < 0 || gamepad >= 4)
		return;

	switch(binding) {
		case RGE_PAD_LT:
			gamepad_states[gamepad].left_trigger_axis = value;
			return;
		case RGE_PAD_RT:
			gamepad_states[gamepad].right_trigger_axis = value;
			return;
		case RGE_PAD_LS_AXIS_X:
			gamepad_states[gamepad].left_stick_axis_x = value;
			return;
		case RGE_PAD_LS_AXIS_Y:
			gamepad_states[gamepad].left_stick_axis_y = value;
			return;
		case RGE_PAD_RS_AXIS_X:
			gamepad_states[gamepad].right_stick_axis_x = value;
			return;
		case RGE_PAD_RS_AXIS_Y:
			gamepad_states[gamepad].right_stick_axis_y = value;
			return;
		default:
			return;
	}
}


//------------------------------------------------------------------------------


bool rge_input_gamepad_is_press(int gamepad, rge_input_t binding) {
	if(gamepad < 0 || gamepad >= 4)
		return false;

	return rge_bit_get(*get_gamepad_ptr(gamepad, binding), 0);
}


//------------------------------------------------------------------------------


bool rge_input_gamepad_is_click(int gamepad, rge_input_t binding) {
	if(gamepad < 0 || gamepad >= 4)
		return false;

	return rge_bit_get(*get_gamepad_ptr(gamepad, binding), 1);
}


//------------------------------------------------------------------------------


float rge_input_gamepad_get_axis(int gamepad, rge_input_t binding) {
	if(gamepad < 0 || gamepad >= 4)
		return 0.0F;

	switch(binding) {
		case RGE_PAD_LT:
			return gamepad_states[gamepad].left_trigger_axis;
		case RGE_PAD_RT:
			return gamepad_states[gamepad].right_trigger_axis;
		case RGE_PAD_LS_AXIS_X:
			return gamepad_states[gamepad].left_stick_axis_x;
		case RGE_PAD_LS_AXIS_Y:
			return gamepad_states[gamepad].left_stick_axis_y;
		case RGE_PAD_RS_AXIS_X:
			return gamepad_states[gamepad].right_stick_axis_x;
		case RGE_PAD_RS_AXIS_Y:
			return gamepad_states[gamepad].right_stick_axis_y;
		default:
			return rge_input_gamepad_is_press(gamepad, binding) ? 1.0F : 0.0F;
	}
}