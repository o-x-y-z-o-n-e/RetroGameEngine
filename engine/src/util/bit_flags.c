#include "util/bit_flags.h"


//------------------------------------------------------------------------------


uint8_t rge_bit_set(uint8_t flags, int bit) {
	return flags | (0b1 << bit);
}


//------------------------------------------------------------------------------


uint8_t rge_bit_clear(uint8_t flags, int bit) {
	return flags & ~(0b1 << bit);
}


//------------------------------------------------------------------------------


bool rge_bit_get(uint8_t flags, int bit) {
	return flags & (0b1 << bit);
}