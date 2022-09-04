#ifndef SYSTEM_H
#define SYSTEM_H

#include <stdint.h>

int init_system();
uint64_t get_current_time();
uint8_t system_key_to_rge_key(uint16_t system_key);

#endif