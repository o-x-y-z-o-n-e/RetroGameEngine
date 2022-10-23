#include "assets/texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


//------------------------------------------------------------------------------


static uint8_t* rgb_to_rgba(const uint8_t* data, int width, int height) {
	uint8_t* new_data = (uint8_t*)malloc(sizeof(uint8_t) * 4 * width * height);
	if(new_data == NULL)
		return NULL;

	for(size_t i = 0; i < width * height; i++) {
		size_t offset1 = i * 4;
		size_t offset2 = i * 3;
		new_data[offset1] = data[offset2];
		new_data[offset1 + 1] = data[offset2 + 1];
		new_data[offset1 + 2] = data[offset2 + 2];
		new_data[offset1 + 3] = 255;
	}

	return new_data;
}


//------------------------------------------------------------------------------


texture_t rge_texture_read(const char* path) {
	int width, height, channels;
	uint8_t* data = stbi_load(path, &width, &height, &channels, STBI_rgb_alpha);
	if(!data) {
		rge_log_error("Texture could not be loaded: %s", path);
		return (texture_t) {
			0,
			0,
			NULL
		};
	}

	if(channels == STBI_rgb) {
		uint8_t* new_data = rgb_to_rgba(data, width, height);
		stbi_image_free(data);
		data = new_data;
	}

	return (texture_t) {
		width,
		height,
		(pixel_t*)data
	};
}


//------------------------------------------------------------------------------


pixel_t rge_texture_sample(texture_t* texture, uint16_t x, uint16_t y) {
	if(x >= texture->width || y >= texture->height)
		return COLOR_RGB(0, 0, 0);

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