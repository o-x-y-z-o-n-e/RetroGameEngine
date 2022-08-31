#include "video/renderer.h"
#include "video/sprite.h"
#include "video/texture.h"
#include "platform/window.h"
#include "world/scene.h"
#include "world/transform.h"
#include "util/debug.h"

#include <stdlib.h>
#include <stddef.h>

#define MAX_LAYERS 10
#define DEFAULT_VIEW_WIDTH 320
#define DEFAULT_VIEW_HEIGHT 200
#define DEFAULT_CLEAR_COLOR COLOR_RGB(0, 0, 0)

#define START_SPRITES_COUNT 100
#define INCREASE_SPRITES_STEP 100

static pixel_t clear_color;
static viewport_t* viewport;
static point_t camera_offset;
static point_t camera_location = { 0, 0 };

static registry_t* layers[MAX_LAYERS];


//------------------------------------------------------------------------------


void on_sprite_add(void* cmp, entity_t* entity) {
	((sprite_t*)(cmp))->owner = entity;
}


//------------------------------------------------------------------------------


pixel_t blend(pixel_t base, pixel_t overlap) {
	if(overlap.a == 0)
		return base;

	float t = overlap.a / 255.0F;

	uint16_t r = (uint8_t)(t * overlap.r) + (uint8_t)((1 - t) * base.r);
	if(r > 255)
		r = 255;

	uint16_t g = (uint8_t)(t * overlap.g) + (uint8_t)((1 - t) * base.g);
	if(g > 255)
		g = 255;

	uint16_t b = (uint8_t)(t * overlap.b) + (uint8_t)((1 - t) * base.b);
	if(b > 255)
		b = 255;

	pixel_t color;
	color.r = (uint8_t)r;
	color.g = (uint8_t)g;
	color.b = (uint8_t)b;
	color.a = overlap.a;

	return color;
}


//------------------------------------------------------------------------------


pixel_t rgba_to_argb(pixel_t color) {
	color.p = (color.a << 24) + (color.r << 16) + (color.g << 8) + (color.b << 0);
	return color;
}


//------------------------------------------------------------------------------


int init_renderer() {
	viewport = get_viewport();

	if(viewport == NULL) {
		log_error("Failed to initalize renderer");
		return 0;
	}

	set_clear_color(DEFAULT_CLEAR_COLOR);
	set_viewport_size(DEFAULT_VIEW_WIDTH, DEFAULT_VIEW_HEIGHT);

	for(uint16_t i = 0; i < MAX_LAYERS; i++) {
		layers[i] = init_registry(TYPE_SPRITE, sizeof(sprite_t), START_SPRITES_COUNT, INCREASE_SPRITES_STEP);
		set_on_add(layers[i], on_sprite_add);
		set_on_update(layers[i], draw_sprite);
	}

	return 1;
}


//------------------------------------------------------------------------------


char is_sprite_visible(const sprite_t* sprite) {
	int32_t ox = sprite->location.x + camera_offset.x - camera_location.x;
	int32_t oy = -sprite->location.y + camera_offset.y + camera_location.y;

    if(ox > viewport->width)
        return 0;
    
    if(ox + sprite->section.width < 0)
        return 0;
    
    if(oy > viewport->height)
        return 0;
    
    if(oy + sprite->section.height < 0)
        return 0;

    return 1;
}


//------------------------------------------------------------------------------


void set_pixel(uint16_t x, uint16_t y, pixel_t color) {
	uint16_t by = y * viewport->scale;
	uint16_t bx = x * viewport->scale;
	uint16_t w = viewport->width * viewport->scale;

#if SYS_WINDOWS
	color = rgba_to_argb(color);
#endif

	if(color.a < 255) {
		pixel_t base = viewport->buffer[(by * w) + bx];
		color = blend(base, color);
	}

	for(int yo = 0; yo < viewport->scale; yo++) {
		size_t n = ((by + yo) * w);
		for(int xo = 0; xo < viewport->scale; xo++) {
			viewport->buffer[n + bx + xo] = color;
		}
	}
}


//------------------------------------------------------------------------------


void clear_buffer() {
	size_t n = viewport->width * viewport->height * viewport->scale * viewport->scale;
	for(size_t i = 0; i < n; i++)
		viewport->buffer[i] = clear_color;
}


//------------------------------------------------------------------------------


void draw_sprite(const sprite_t* sprite, float delta) {
	int32_t ox = 0;
	int32_t oy = 0;

	transform_t* transform = get_component_of_type(sprite->owner, TYPE_TRANSFORM);
	if(transform != NULL) {
		ox = transform->location.x + camera_offset.x - camera_location.x;
		oy = -transform->location.y + camera_offset.y + camera_location.y;
	}

	uint16_t bx = 0;
	uint16_t wx = sprite->section.width;
	uint16_t by = 0;
	uint16_t wy = sprite->section.height;

	int32_t lx = (ox + wx) - viewport->width;
	if(lx > 0)
		wx -= lx;

	if(ox < 0)
		bx -= ox;

	int32_t ly = (oy + wy) - viewport->height;
	if(ly > 0)
		wy -= ly;

	if(oy < 0)
		by -= oy;

	for(uint16_t sx = bx; sx < wx; sx++) {
		for(uint16_t sy = by; sy < wy; sy++) {
			int16_t x = ox + sx;
			int16_t y = oy + sy;

			set_pixel(
				x,
				y,
				sample_texture(
					sprite->texture,
					sprite->section.x + sx,
					sprite->section.y + sy
				)
			);
		}
	}
}


//------------------------------------------------------------------------------


void draw_all() {
	clear_buffer();

    for(uint8_t i = 0; i < MAX_LAYERS; i++)
        update_registry(layers[i], 0);

	refresh_window();
}


//------------------------------------------------------------------------------


uint16_t get_view_width() {
	if(viewport == NULL) {
		log_error("Renderer not initialized yet");
		return 0;
	}

	return viewport->width;
}


//------------------------------------------------------------------------------


uint16_t get_view_height() {
	if(viewport == NULL) {
		log_error("Renderer not initialized yet");
		return 0;
	}

	return viewport->height;
}


//------------------------------------------------------------------------------


void set_viewport_size(uint16_t width, uint16_t height) {
	set_viewport(width, height);

	camera_offset.x = width / 2;
	camera_offset.y = height / 2;
}


//------------------------------------------------------------------------------


void set_camera_location(point_t location) {
	camera_location = location;
}


//------------------------------------------------------------------------------


point_t get_camera_location() {
	return camera_location;
}


//------------------------------------------------------------------------------


void set_clear_color(pixel_t color) { clear_color = color; }


//------------------------------------------------------------------------------


registry_t* get_layer(uint8_t layer) {
	if(layer >= MAX_LAYERS) {
		log_error("Layer does not exist");
		return NULL;
	}

	return layers[layer]; //TODO
}