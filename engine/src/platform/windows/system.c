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

#endif