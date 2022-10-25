#ifdef SYS_WINDOWS
#include "api/rge.h"
#include "platform/system.h"
#include "core/input.h"

#include <windows.h>
#include <xinput.h>
#include <math.h>


//------------------------------------------------------------------------------


int rge_system_init() {
	
	return 1;
}


//------------------------------------------------------------------------------


uint64_t rge_system_get_time() {
	LARGE_INTEGER freq;
	LARGE_INTEGER counter;
	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&counter);

	return (counter.QuadPart * 1000LL) / freq.QuadPart;
}


//------------------------------------------------------------------------------


uint8_t rge_system_parse_key(uint16_t system_key) {
	// If system key is a letter.
	if(system_key > 0x40 && system_key < 0x5B)
		return system_key - 0x40;

	// If system key is a digit (keypad).
	if(system_key > 0x5F && system_key < 0x6A)
		return system_key - 0x60 + 30;

	// If system key is a digit (alpha).
	if(system_key > 0x2F && system_key < 0x3A)
		return system_key - 0x30 + 30;

	// Otherwise,
	switch(system_key) {
		case VK_SPACE: return RGE_KEY_SPACE;
		case VK_CAPITAL: return RGE_KEY_CAPS;
		case VK_RETURN: return RGE_KEY_RETURN;
		case VK_LEFT: return RGE_KEY_LEFT;
		case VK_UP: return RGE_KEY_UP;
		case VK_RIGHT: return RGE_KEY_RIGHT;
		case VK_DOWN: return RGE_KEY_DOWN;
		case VK_LSHIFT: return RGE_KEY_LSHIFT;
		case VK_CONTROL: return RGE_KEY_LCTRL;
		case VK_RSHIFT: return RGE_KEY_RSHIFT;
		case VK_TAB: return RGE_KEY_TAB;
		case VK_BACK: return RGE_KEY_BACKSPACE;
		case VK_ESCAPE: return RGE_KEY_ESC;
	}

	return 255;
}


//------------------------------------------------------------------------------


float rge_system_poll_axis(uint8_t binding) {
	XINPUT_STATE state;
	XInputGetState(0, &state);

	switch(binding) {
		case RGE_PAD_LT:
			return (float)state.Gamepad.bLeftTrigger / 255;

		case RGE_PAD_RT:
			return (float)state.Gamepad.bRightTrigger / 255;

		case RGE_PAD_LS_AXIS_X:
			return fmaxf(-1, (float)state.Gamepad.sThumbLX / 32767);

		case RGE_PAD_LS_AXIS_Y:
			return fmaxf(-1, (float)state.Gamepad.sThumbLY / 32767);

		case RGE_PAD_RS_AXIS_X:
			return fmaxf(-1, (float)state.Gamepad.sThumbRX / 32767);

		case RGE_PAD_RS_AXIS_Y:
			return fmaxf(-1, (float)state.Gamepad.sThumbRY / 32767);
	}

	return 0.0F;
}


//------------------------------------------------------------------------------


void rge_system_poll_gamepad() {
	for(int i = 0; i < 4; i++) {
		XINPUT_STATE state;
		XInputGetState(i, &state);

		float lt = (float)state.Gamepad.bLeftTrigger / 255;
		float rt = (float)state.Gamepad.bRightTrigger / 255;

		float lx = fmaxf(-1, (float)state.Gamepad.sThumbLX / 32767);
		float ly = fmaxf(-1, (float)state.Gamepad.sThumbLY / 32767);
		float rx = fmaxf(-1, (float)state.Gamepad.sThumbRX / 32767);
		float ry = fmaxf(-1, (float)state.Gamepad.sThumbRY / 32767);

		rge_input_gamepad_set_axis(i, RGE_PAD_LT, lt);
		rge_input_gamepad_set_axis(i, RGE_PAD_RT, rt);

		rge_input_gamepad_set_axis(i, RGE_PAD_LS_AXIS_X, lx);
		rge_input_gamepad_set_axis(i, RGE_PAD_LS_AXIS_Y, ly);
		rge_input_gamepad_set_axis(i, RGE_PAD_RS_AXIS_X, rx);
		rge_input_gamepad_set_axis(i, RGE_PAD_RS_AXIS_Y, ry);

		rge_input_gamepad_set_state(i, RGE_PAD_D_LEFT, state.Gamepad.wButtons & 0x0004);
		rge_input_gamepad_set_state(i, RGE_PAD_D_UP, state.Gamepad.wButtons & 0x0001);
		rge_input_gamepad_set_state(i, RGE_PAD_D_RIGHT, state.Gamepad.wButtons & 0x0008);
		rge_input_gamepad_set_state(i, RGE_PAD_D_DOWN, state.Gamepad.wButtons & 0x0002);

		rge_input_gamepad_set_state(i, RGE_PAD_WEST, state.Gamepad.wButtons & 0x4000);
		rge_input_gamepad_set_state(i, RGE_PAD_NORTH, state.Gamepad.wButtons & 0x8000);
		rge_input_gamepad_set_state(i, RGE_PAD_EAST, state.Gamepad.wButtons & 0x2000);
		rge_input_gamepad_set_state(i, RGE_PAD_SOUTH, state.Gamepad.wButtons & 0x1000);

		rge_input_gamepad_set_state(i, RGE_PAD_LS_LEFT, lx < 0.5F);
		rge_input_gamepad_set_state(i, RGE_PAD_LS_UP, ly > 0.5F);
		rge_input_gamepad_set_state(i, RGE_PAD_LS_RIGHT, lx > 0.5F);
		rge_input_gamepad_set_state(i, RGE_PAD_LS_DOWN, ly < 0.5F);

		rge_input_gamepad_set_state(i, RGE_PAD_RS_LEFT, rx < 0.5F);
		rge_input_gamepad_set_state(i, RGE_PAD_RS_UP, ry > 0.5F);
		rge_input_gamepad_set_state(i, RGE_PAD_RS_RIGHT, rx > 0.5F);
		rge_input_gamepad_set_state(i, RGE_PAD_RS_DOWN, ry < 0.5F);

		rge_input_gamepad_set_state(i, RGE_PAD_LB, state.Gamepad.wButtons & 0x0100);
		rge_input_gamepad_set_state(i, RGE_PAD_RB, state.Gamepad.wButtons & 0x0200);

		rge_input_gamepad_set_state(i, RGE_PAD_LT, lt > 0.5F);
		rge_input_gamepad_set_state(i, RGE_PAD_RT, rt > 0.5F);

		rge_input_gamepad_set_state(i, RGE_PAD_L3, state.Gamepad.wButtons & 0x0040);
		rge_input_gamepad_set_state(i, RGE_PAD_R3, state.Gamepad.wButtons & 0x0080);

		rge_input_gamepad_set_state(i, RGE_PAD_OPTIONS, state.Gamepad.wButtons & 0x0020);
		rge_input_gamepad_set_state(i, RGE_PAD_START, state.Gamepad.wButtons & 0x0010);
	}
}

#endif