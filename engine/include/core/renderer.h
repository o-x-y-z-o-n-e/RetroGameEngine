#ifndef RGE_RENDERER_H
#define RGE_RENDERER_H

#include <stdint.h>

typedef struct registry_t registry_t;
typedef struct pixel_t pixel_t;

typedef struct viewport_t {
	pixel_t* buffer;
	uint16_t width;
	uint16_t height;
	uint16_t scale;
} viewport_t;

int rge_renderer_init();

#endif