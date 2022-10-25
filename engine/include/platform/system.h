#ifndef RGE_SYSTEM_H
#define RGE_SYSTEM_H

#include <stdint.h>

int rge_system_init();
uint64_t rge_system_get_time();
uint8_t rge_system_parse_key(uint16_t system_key);
float rge_system_poll_axis(uint8_t binding);

#endif