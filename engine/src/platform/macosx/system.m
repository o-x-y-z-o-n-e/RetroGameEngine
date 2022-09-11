#ifdef SYS_MACOSX

#include "api/rge.h"
#include "platform/system.h"
#include <time.h>

enum {
    kVK_ANSI_A                    = 0x00,
    kVK_ANSI_S                    = 0x01,
    kVK_ANSI_D                    = 0x02,
    kVK_ANSI_F                    = 0x03,
    kVK_ANSI_H                    = 0x04,
    kVK_ANSI_G                    = 0x05,
    kVK_ANSI_Z                    = 0x06,
    kVK_ANSI_X                    = 0x07,
    kVK_ANSI_C                    = 0x08,
    kVK_ANSI_V                    = 0x09,
    kVK_ANSI_B                    = 0x0B,
    kVK_ANSI_Q                    = 0x0C,
    kVK_ANSI_W                    = 0x0D,
    kVK_ANSI_E                    = 0x0E,
    kVK_ANSI_R                    = 0x0F,
    kVK_ANSI_Y                    = 0x10,
    kVK_ANSI_T                    = 0x11,
    kVK_ANSI_1                    = 0x12,
    kVK_ANSI_2                    = 0x13,
    kVK_ANSI_3                    = 0x14,
    kVK_ANSI_4                    = 0x15,
    kVK_ANSI_6                    = 0x16,
    kVK_ANSI_5                    = 0x17,
    kVK_ANSI_Equal                = 0x18,
    kVK_ANSI_9                    = 0x19,
    kVK_ANSI_7                    = 0x1A,
    kVK_ANSI_Minus                = 0x1B,
    kVK_ANSI_8                    = 0x1C,
    kVK_ANSI_0                    = 0x1D,
    kVK_ANSI_RightBracket         = 0x1E,
    kVK_ANSI_O                    = 0x1F,
    kVK_ANSI_U                    = 0x20,
    kVK_ANSI_LeftBracket          = 0x21,
    kVK_ANSI_I                    = 0x22,
    kVK_ANSI_P                    = 0x23,
    kVK_ANSI_L                    = 0x25,
    kVK_ANSI_J                    = 0x26,
    kVK_ANSI_Quote                = 0x27,
    kVK_ANSI_K                    = 0x28,
    kVK_ANSI_Semicolon            = 0x29,
    kVK_ANSI_Backslash            = 0x2A,
    kVK_ANSI_Comma                = 0x2B,
    kVK_ANSI_Slash                = 0x2C,
    kVK_ANSI_N                    = 0x2D,
    kVK_ANSI_M                    = 0x2E,
    kVK_ANSI_Period               = 0x2F,
    kVK_ANSI_Grave                = 0x32,
    kVK_ANSI_KeypadDecimal        = 0x41,
    kVK_ANSI_KeypadMultiply       = 0x43,
    kVK_ANSI_KeypadPlus           = 0x45,
    kVK_ANSI_KeypadClear          = 0x47,
    kVK_ANSI_KeypadDivide         = 0x4B,
    kVK_ANSI_KeypadEnter          = 0x4C,
    kVK_ANSI_KeypadMinus          = 0x4E,
    kVK_ANSI_KeypadEquals         = 0x51,
    kVK_ANSI_Keypad0              = 0x52,
    kVK_ANSI_Keypad1              = 0x53,
    kVK_ANSI_Keypad2              = 0x54,
    kVK_ANSI_Keypad3              = 0x55,
    kVK_ANSI_Keypad4              = 0x56,
    kVK_ANSI_Keypad5              = 0x57,
    kVK_ANSI_Keypad6              = 0x58,
    kVK_ANSI_Keypad7              = 0x59,
    kVK_ANSI_Keypad8              = 0x5B,
    kVK_ANSI_Keypad9              = 0x5C
};

/* keycodes for keys that are independent of keyboard layout*/
enum {
    kVK_Return                    = 0x24,
    kVK_Tab                       = 0x30,
    kVK_Space                     = 0x31,
    kVK_Delete                    = 0x33,
    kVK_Escape                    = 0x35,
    kVK_Command                   = 0x37,
    kVK_Shift                     = 0x38,
    kVK_CapsLock                  = 0x39,
    kVK_Option                    = 0x3A,
    kVK_Control                   = 0x3B,
    kVK_RightShift                = 0x3C,
    kVK_RightOption               = 0x3D,
    kVK_RightControl              = 0x3E,
    kVK_Function                  = 0x3F,
    kVK_F17                       = 0x40,
    kVK_VolumeUp                  = 0x48,
    kVK_VolumeDown                = 0x49,
    kVK_Mute                      = 0x4A,
    kVK_F18                       = 0x4F,
    kVK_F19                       = 0x50,
    kVK_F20                       = 0x5A,
    kVK_F5                        = 0x60,
    kVK_F6                        = 0x61,
    kVK_F7                        = 0x62,
    kVK_F3                        = 0x63,
    kVK_F8                        = 0x64,
    kVK_F9                        = 0x65,
    kVK_F11                       = 0x67,
    kVK_F13                       = 0x69,
    kVK_F16                       = 0x6A,
    kVK_F14                       = 0x6B,
    kVK_F10                       = 0x6D,
    kVK_F12                       = 0x6F,
    kVK_F15                       = 0x71,
    kVK_Help                      = 0x72,
    kVK_Home                      = 0x73,
    kVK_PageUp                    = 0x74,
    kVK_ForwardDelete             = 0x75,
    kVK_F4                        = 0x76,
    kVK_End                       = 0x77,
    kVK_F2                        = 0x78,
    kVK_PageDown                  = 0x79,
    kVK_F1                        = 0x7A,
    kVK_LeftArrow                 = 0x7B,
    kVK_RightArrow                = 0x7C,
    kVK_DownArrow                 = 0x7D,
    kVK_UpArrow                   = 0x7E
};

/* DEPRECATED
#include <CoreServices/CoreServices.h>
#include <mach/mach.h>
#include <mach/mach_time.h>

uint64_t get_current_time() {
    uint64_t time = mach_absolute_time();
    
    Nanoseconds nano = AbsoluteToNanoseconds(*(AbsoluteTime*)&time);

    return (*(uint64_t*)&nano)/1000/1000;
}
*/

uint64_t rge_system_get_time() {
    struct timespec time;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time);

    return (time.tv_sec * 1000) + (time.tv_nsec / 1000000);
}


//------------------------------------------------------------------------------


uint8_t rge_system_parse_key(uint16_t system_key) {
    switch(system_key) {
        case kVK_ANSI_A: return KEY_A;
        case kVK_ANSI_B: return KEY_B;
        case kVK_ANSI_C: return KEY_C;
        case kVK_ANSI_D: return KEY_D;
        case kVK_ANSI_E: return KEY_E;
        case kVK_ANSI_F: return KEY_F;
        case kVK_ANSI_G: return KEY_G;
        case kVK_ANSI_H: return KEY_H;
        case kVK_ANSI_I: return KEY_I;
        case kVK_ANSI_J: return KEY_J;
        case kVK_ANSI_K: return KEY_K;
        case kVK_ANSI_L: return KEY_L;
        case kVK_ANSI_M: return KEY_M;
        case kVK_ANSI_N: return KEY_N;
        case kVK_ANSI_O: return KEY_0;
        case kVK_ANSI_P: return KEY_P;
        case kVK_ANSI_Q: return KEY_Q;
        case kVK_ANSI_R: return KEY_R;
        case kVK_ANSI_S: return KEY_S;
        case kVK_ANSI_T: return KEY_T;
        case kVK_ANSI_U: return KEY_U;
        case kVK_ANSI_V: return KEY_V;
        case kVK_ANSI_W: return KEY_W;
        case kVK_ANSI_X: return KEY_X;
        case kVK_ANSI_Y: return KEY_Y;
        case kVK_ANSI_Z: return KEY_Z;

        case kVK_ANSI_0: return KEY_0;
        case kVK_ANSI_1: return KEY_1;
        case kVK_ANSI_2: return KEY_2;
        case kVK_ANSI_3: return KEY_3;
        case kVK_ANSI_4: return KEY_4;
        case kVK_ANSI_5: return KEY_5;
        case kVK_ANSI_6: return KEY_6;
        case kVK_ANSI_7: return KEY_7;
        case kVK_ANSI_8: return KEY_8;
        case kVK_ANSI_9: return KEY_9;

        case kVK_Space: return KEY_SPACE;
        case kVK_CapsLock: return KEY_CAPS;
        case kVK_Return: return KEY_RETURN;
        case kVK_LeftArrow: return KEY_LEFT;
        case kVK_UpArrow: return KEY_UP;
        case kVK_RightArrow: return KEY_RIGHT;
        case kVK_DownArrow: return KEY_DOWN;
        case kVK_Shift: return KEY_LSHIFT;
        case kVK_Control: return KEY_LCTRL;
        case kVK_Command: return KEY_LALT;

        case kVK_RightShift: return KEY_RSHIFT;
        case kVK_RightControl: return KEY_RCTRL;
        case kVK_Tab: return KEY_TAB;
        case kVK_Delete: return KEY_BACKSPACE;
        case kVK_Escape: return KEY_ESC;

    }

    return 255;
}


#endif