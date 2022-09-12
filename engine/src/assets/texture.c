#include "assets/texture.h"


//------------------------------------------------------------------------------


pixel_t rge_texture_sample(texture_t* texture, uint16_t x, uint16_t y) {
	return texture->data[y * texture->width + x];
}