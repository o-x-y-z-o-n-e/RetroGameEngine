#ifndef RGE_TEXTURE_H
#define RGE_TEXTURE_H

#include "api/rge.h"

typedef struct texture_t {
    uint16_t width, height;
    pixel_t* data;
} texture_t;

texture_t rge_texture_parse(void* buffer, int size);
pixel_t rge_texture_sample(texture_t* texture, uint16_t x, uint16_t y);

#endif