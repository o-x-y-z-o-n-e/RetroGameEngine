#include "api/rge.h"
#include "video/texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define TABLE_SIZE 4096


//------------------------------------------------------------------------------


static texture_t hash_table[TABLE_SIZE];


//------------------------------------------------------------------------------


pixel_t rge_texture_sample(texture_t* texture, uint16_t x, uint16_t y) {
	return texture->data[y * texture->width + x];
}


//------------------------------------------------------------------------------


static uint8_t* rgb_to_rgba(const uint8_t* data, int width, int height) {
	uint8_t* new_data = (uint8_t*)malloc(sizeof(uint8_t) * 4 * width * height);
	if(new_data == NULL)
		return NULL;

	for(size_t i = 0; i < width * height; i++) {
		size_t offset1 = i * 4;
		size_t offset2 = i * 3;
		new_data[offset1]     = data[offset2];
		new_data[offset1 + 1] = data[offset2 + 1];
		new_data[offset1 + 2] = data[offset2 + 2];
		new_data[offset1 + 3] = 255;
	}

	return new_data;
}


//------------------------------------------------------------------------------


int rge_texture_init() {
	for(size_t i = 0; i < TABLE_SIZE; i++)
		hash_table[i].hash = 0;

	return 1;
}


//------------------------------------------------------------------------------


static size_t get_str_hash(const char* str) {
	size_t hash = 5381;
	char c;
	while((c = *str++) != 0)
		hash = ((hash << 5) + hash) + c;
	
	return hash;
}


//------------------------------------------------------------------------------


static texture_t* get_texture_slot(size_t hash) {
	size_t start = hash % TABLE_SIZE;
	size_t i = 0;

	while(1) {
		size_t index = (start + (i * i) % TABLE_SIZE);

		if(hash_table[index].data == NULL || hash_table[index].hash == hash) {
			// Found empty or matching slot.
			return &hash_table[index];
		} else {
			i++;
		}
	}
}


//------------------------------------------------------------------------------


void rge_texture_free(texture_t* texture) {
	free(texture->data);

	texture->width = 0;
	texture->height = 0;
	texture->hash = 0;
	texture->data = NULL;
}


//------------------------------------------------------------------------------


texture_t* rge_texture_load(const char* path) {
	size_t hash = get_str_hash(path);

	texture_t* texture = get_texture_slot(hash);
	if(texture->data)
		return texture;

	int width, height, channels;
	uint8_t* data = stbi_load(path, &width, &height, &channels, STBI_rgb_alpha);
	if(!data) {
		rge_log_error("Texture could not be loaded: %s", path);
		return NULL;
	}

	if(channels == STBI_rgb) {
		uint8_t* new_data = rgb_to_rgba(data, width, height);
		stbi_image_free(data);
		data = new_data;
	}

	texture->width = width;
	texture->height = height;
	texture->data = (pixel_t*)data;

	return texture;
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