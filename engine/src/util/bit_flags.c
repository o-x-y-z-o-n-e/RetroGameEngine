#include "util/bit_flags.h"


//------------------------------------------------------------------------------


uint8_t set_bit(uint8_t flags, int bit) {
	return flags | (0b1 << bit);
}


//------------------------------------------------------------------------------


uint8_t clear_bit(uint8_t flags, int bit) {
	return flags & ~(0b1 << bit);
}


//------------------------------------------------------------------------------


bool get_bit(uint8_t flags, int bit) {
	return flags & (0b1 << bit);
}