#ifndef TEXTURE_H
#define TEXTURE_H

#include "util/types.h"
#include <stddef.h>

typedef struct pixel_t pixel_t;

typedef struct texture_t {
	size_t hash;
    uint16_t width, height;
    pixel_t* data;
} texture_t;

int init_textures();
texture_t* load_texture(const char* path);
pixel_t sample_texture(texture_t* texture, uint16_t x, uint16_t y);
void get_texture_size(const texture_t* texture, uint16_t* w, uint16_t* h);
uint16_t get_texture_width(const texture_t* texture);
uint16_t get_texture_height(const texture_t* texture);

#endif