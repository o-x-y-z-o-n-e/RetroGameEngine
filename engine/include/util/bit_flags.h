#ifndef BIT_FLAGS_H
#define BIT_FLAGS_H

#include <stdint.h>
#include <stdbool.h>

uint8_t set_bit(uint8_t flags, int bit);
uint8_t clear_bit(uint8_t flags, int bit);
bool get_bit(uint8_t flags, int bit);

#endif