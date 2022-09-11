#ifndef BIT_FLAGS_H
#define BIT_FLAGS_H

#include <stdint.h>
#include <stdbool.h>

uint8_t rge_bit_set(uint8_t flags, int bit);
uint8_t rge_bit_clear(uint8_t flags, int bit);
bool rge_bit_get(uint8_t flags, int bit);

#endif