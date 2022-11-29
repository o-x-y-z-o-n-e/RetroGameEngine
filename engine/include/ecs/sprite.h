#ifndef RGE_SPRITE_H
#define RGE_SPRITE_H

#include "api/rge.h"

typedef struct sprite_t {
	entity_t* owner;
    texture_t* texture;
    rect_t section;
    point_t offset;
	uint8_t flags;
} sprite_t;

int rge_sprite_init();
void rge_sprite_draw_all();

#endif