#include "api/rge.h"
#include "core/renderer.h"
#include "assets/texture.h"
#include "platform/window.h"

#define DEFAULT_VIEW_WIDTH 320
#define DEFAULT_VIEW_HEIGHT 200
#define DEFAULT_CLEAR_COLOR COLOR_RGB(0, 0, 0)

static pixel_t clear_color;
static viewport_t* viewport;
static point_t camera_offset;
static point_t camera_location = { 0, 0 };


//------------------------------------------------------------------------------


static pixel_t rgba_to_argb(pixel_t color) {
	color.p = (color.a << 24) + (color.r << 16) + (color.g << 8) + (color.b << 0);
	return color;
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


void rge_renderer_draw_texture(texture_t* texture, int32_t x, int32_t y) {
	x += camera_offset.x - camera_location.x;
	y += camera_offset.y + camera_location.y;

	uint16_t bx = 0;
	uint16_t wx = texture->width;
	uint16_t by = 0;
	uint16_t wy = texture->height;

	if(x >= viewport->width || y >= viewport->height || x + wx < 0 || y + wy < 0)
		return;

	int32_t lx = (x + wx) - viewport->width;
	if(lx > 0)
		wx -= lx;

	if(x < 0)
		bx -= x;

	int32_t ly = (y + wy) - viewport->height;
	if(ly > 0)
		wy -= ly;

	if(y < 0)
		by -= y;

	uint16_t nx, ny;
	for(uint16_t sx = bx; sx < wx; sx++) {
		for(uint16_t sy = by; sy < wy; sy++) {
			nx = x + sx;
			ny = y + sy;

			rge_renderer_set_pixel(
				nx,
				ny,
				rge_texture_sample(
					texture,
					sx,
					sy
				)
			);
		}
	}
}


//------------------------------------------------------------------------------


void rge_renderer_draw_atlas(texture_t* texture, int32_t x, int32_t y, rect_t bounds) {
	int32_t ox = x + camera_offset.x - camera_location.x;
	int32_t oy = -y + camera_offset.y + camera_location.y;

	uint16_t bx = 0;
	uint16_t wx = bounds.width;
	uint16_t by = 0;
	uint16_t wy = bounds.height;

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

	uint16_t nx, ny;
	for(uint16_t sx = bx; sx < wx; sx++) {
		for(uint16_t sy = by; sy < wy; sy++) {
			nx = ox + sx;
			ny = oy + sy;

			rge_renderer_set_pixel(
				nx,
				ny,
				rge_texture_sample(
					texture,
					bounds.x + sx,
					bounds.y + sy
				)
			);
		}
	}
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

	return 1;
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