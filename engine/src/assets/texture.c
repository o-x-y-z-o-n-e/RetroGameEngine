#include "assets/texture.h"


//------------------------------------------------------------------------------


pixel_t rge_texture_sample(texture_t* texture, uint16_t x, uint16_t y) {
	return texture->data[y * texture->width + x];
}


//------------------------------------------------------------------------------


void rge_texture_get_size(const texture_t* texture, uint16_t* w, uint16_t* h) {
	*w = texture->width;
	*h = texture->height;
}


//------------------------------------------------------------------------------


uint16_t rge_texture_get_width(const texture_t* texture) {
	return texture->width;
}


//------------------------------------------------------------------------------


uint16_t rge_texture_get_height(const texture_t* texture) {
	return texture->height;
}