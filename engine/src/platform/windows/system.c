#ifdef SYS_WINDOWS
#include "platform/system.h"
#include "core/input.h"
#include <windows.h>


int init_system() {
	
	return 1;
}


//------------------------------------------------------------------------------


uint64_t get_current_time() {
	LARGE_INTEGER freq;
	LARGE_INTEGER counter;
	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&counter);

	return (counter.QuadPart * 1000LL) / freq.QuadPart;
}


//------------------------------------------------------------------------------


uint8_t system_key_to_rge_key(uint16_t system_key) {
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
		case VK_SPACE: return KEY_SPACE;
		case VK_CAPITAL: return KEY_CAPS;
		case VK_RETURN: return KEY_RETURN;
		case VK_LEFT: return KEY_LEFT;
		case VK_UP: return KEY_UP;
		case VK_RIGHT: return KEY_RIGHT;
		case VK_DOWN: return KEY_DOWN;
		case VK_LSHIFT: return KEY_LSHIFT;
		case VK_CONTROL: return KEY_LCTRL;
		case VK_RSHIFT: return KEY_RSHIFT;
		case VK_TAB: return KEY_TAB;
		case VK_BACK: return KEY_BACKSPACE;
		case VK_ESCAPE: return KEY_ESC;
	}

	return 255;
}

#endif