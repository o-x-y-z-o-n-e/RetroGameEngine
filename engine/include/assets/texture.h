#ifndef RGE_TEXTURE_H
#define RGE_TEXTURE_H

#include "api/rge.h"

typedef struct texture_t {
	size_t hash;
    uint16_t width, height;
    pixel_t* data;
} texture_t;

pixel_t rge_texture_sample(texture_t* texture, uint16_t x, uint16_t y);

#endif