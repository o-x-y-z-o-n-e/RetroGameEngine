#ifndef RENDERER_H
#define RENDERER_H

#include <stdint.h>

typedef struct layer_t layer_t;
typedef struct registry_t registry_t;
typedef struct pixel_t pixel_t;

typedef struct viewport_t {
	pixel_t* buffer;
	uint16_t width;
	uint16_t height;
	uint16_t scale;
} viewport_t;

typedef struct layer_t {
	int16_t level;
	registry_t* sprites;
	layer_t* next;
} layer_t;

int rge_renderer_init();
void rge_renderer_draw_all();
layer_t* rge_renderer_get_layer(int16_t level);

#endif