#include "api/rge.h"
#include "core/renderer.h"
#include "ecs/scene.h"
#include "ecs/sprite.h"
#include "ecs/transform.h"
#include "assets/texture.h"
#include "platform/window.h"

#include <stdlib.h>

#define MAX_LAYERS 10
#define DEFAULT_VIEW_WIDTH 320
#define DEFAULT_VIEW_HEIGHT 200
#define DEFAULT_CLEAR_COLOR COLOR_RGB(0, 0, 0)

#define START_SPRITES_COUNT 100
#define INCREASE_SPRITES_STEP 100

static bool do_render = true;
static pixel_t clear_color;
static viewport_t* viewport;
static point_t camera_offset;
static point_t camera_location = { 0, 0 };

static layer_t* layers_head;


//------------------------------------------------------------------------------


static void on_sprite_add(void* cmp, entity_t* entity) {
	((sprite_t*)(cmp))->owner = entity;
}


//------------------------------------------------------------------------------


static pixel_t blend(pixel_t base, pixel_t overlap) {
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


static pixel_t rgba_to_argb(pixel_t color) {
	color.p = (color.a << 24) + (color.r << 16) + (color.g << 8) + (color.b << 0);
	return color;
}


//------------------------------------------------------------------------------


void rge_renderer_set_pixel(uint16_t x, uint16_t y, pixel_t color) {
	if(x >= viewport->width || y >= viewport->height)
		return;

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


void rge_renderer_clear() {
	size_t n = viewport->width * viewport->height * viewport->scale * viewport->scale;
	for(size_t i = 0; i < n; i++)
		viewport->buffer[i] = clear_color;
}


//------------------------------------------------------------------------------


static void draw_sprite(void* component, float delta) {
	sprite_t* sprite = (sprite_t*)component;

	point_t location = rge_transform_get_global(sprite->owner);
	int32_t ox = location.x + sprite->offset.x + camera_offset.x - camera_location.x;
	int32_t oy = -location.y + sprite->offset.y + camera_offset.y + camera_location.y;

	uint16_t bx = 0;
	uint16_t wx = sprite->section.width;
	uint16_t by = 0;
	uint16_t wy = sprite->section.height;

	if(ox >= viewport->width || oy >= viewport->height || ox + wx < 0 || oy + wy < 0)
		return;

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
			uint16_t x = ox + sx;
			uint16_t y = oy + sy;

			rge_renderer_set_pixel(
				x,
				y,
				rge_texture_sample(
					sprite->texture,
					sprite->section.x + sx,
					sprite->section.y + sy
				)
			);
		}
	}
}


//------------------------------------------------------------------------------


static layer_t* init_layer(int16_t level) {
	layer_t* layer = malloc(sizeof(layer_t));
	if(layer == NULL)
		return NULL;

	layer->level = level;
	layer->sprites = rge_registry_init(TYPE_SPRITE, sizeof(sprite_t), START_SPRITES_COUNT, INCREASE_SPRITES_STEP);
	layer->next = NULL;

	rge_registry_set_on_add(layer->sprites, on_sprite_add);
	rge_registry_set_on_update(layer->sprites, draw_sprite);

	return layer;
}


//------------------------------------------------------------------------------


static layer_t* create_layer(int16_t level) {
	// Insert at head.
	if(level < layers_head->level) {
		layer_t* layer = init_layer(level);
		layer->next = layers_head;
		layers_head = layer;
		return layer;
	}

	layer_t* previous = NULL;
	layer_t* current = layers_head;
	while(current != NULL) {
		if(level == current->level)
			return current;

		if(previous == NULL)
			goto next;

		// Insert in between.
		if(level > previous->level && level < current->level) {
			layer_t* layer = init_layer(level);
			layer->next = previous->next;
			previous->next = layer;
			return layer;
		}

	next:
		previous = current;
		current = current->next;
	}

	// Insert at tail.
	layer_t* layer = init_layer(level);
	previous->next = layer;
	return layer;
}


//------------------------------------------------------------------------------


layer_t* rge_renderer_get_layer(int16_t level) {
	layer_t* current = layers_head;
	while(current != NULL) {
		if(current->level == level)
			return current;

		current = current->next;
	}
	return create_layer(level);
}


//------------------------------------------------------------------------------


int rge_renderer_init() {
	viewport = rge_window_get_viewport();

	if(viewport == NULL) {
		rge_log_error("Failed to initalize renderer");
		return 0;
	}

	rge_view_set_background(DEFAULT_CLEAR_COLOR);
	rge_view_set_size(DEFAULT_VIEW_WIDTH, DEFAULT_VIEW_HEIGHT);

	layers_head = init_layer(0);

	return 1;
}


//------------------------------------------------------------------------------


void rge_renderer_draw_all() {
	rge_renderer_clear();

	layer_t* current = layers_head;
	while(current != NULL) {
		rge_registry_update(current->sprites, 0);
		current = current->next;
	}

	rge_window_refresh();
}


//------------------------------------------------------------------------------


uint16_t rge_view_get_width() {
	if(viewport == NULL) {
		rge_log_error("Renderer not initialized yet");
		return 0;
	}

	return viewport->width;
}


//------------------------------------------------------------------------------


uint16_t rge_view_get_height() {
	if(viewport == NULL) {
		rge_log_error("Renderer not initialized yet");
		return 0;
	}

	return viewport->height;
}


//------------------------------------------------------------------------------


void rge_view_get_size(uint16_t* w, uint16_t* h) {
	if(viewport == NULL) {
		rge_log_error("Renderer not initialized yet");
		*w = 0;
		*h = 0;
		return;
	}

	*w = viewport->width;
	*h = viewport->height;
}


//------------------------------------------------------------------------------


void rge_view_set_size(uint16_t width, uint16_t height) {
	rge_window_set_viewport(width, height);

	camera_offset.x = width / 2;
	camera_offset.y = height / 2;
}


//------------------------------------------------------------------------------


void rge_camera_set_location(point_t location) {
	camera_location = location;
}


//------------------------------------------------------------------------------


point_t rge_camera_get_location() {
	return camera_location;
}


//------------------------------------------------------------------------------


void rge_view_set_background(pixel_t color) { clear_color = color; }


//------------------------------------------------------------------------------


void rge_renderer_auto_set(bool auto_render) {
	do_render = auto_render;
}


//------------------------------------------------------------------------------


bool rge_renderer_auto_get() { return do_render; }