#include "core/asset_manager.h"
#include "util/hash_table.h"
#include "assets/texture.h"
#include "assets/audio.h"
#include <stdlib.h>

#define NUM_TABLES 2
#define TEXTURE_TABLE 0
#define AUDIO_TABLE 1

#define TEXTURE_MAX 300
#define AUDIO_MAX 300


//------------------------------------------------------------------------------


static hash_table_t* tables[NUM_TABLES];


//------------------------------------------------------------------------------


int rge_assets_init() {
	tables[TEXTURE_TABLE] = rge_hash_table_init(TEXTURE_MAX, sizeof(texture_t));
	tables[AUDIO_TABLE] = rge_hash_table_init(AUDIO_MAX, sizeof(audio_t));
	return 1;
}


//------------------------------------------------------------------------------


static size_t get_data_index(int table, void* data) {
	return ((uint8_t*)data - tables[table]->data) / tables[table]->element_size;
}


//------------------------------------------------------------------------------


static void clear_meta(int table, void* data) {
	size_t index = get_data_index(table, data);

	tables[table]->meta[index].used = false;
	tables[table]->meta[index].hash = 0;
}


//------------------------------------------------------------------------------


texture_t* rge_texture_load(const char* path) {
	texture_t* texture = rge_hash_table_add(tables[TEXTURE_TABLE], path);
	if(texture->data != NULL)
		return texture;

	*texture = rge_texture_read(path);

	return texture;
}


//------------------------------------------------------------------------------


void rge_texture_free(texture_t* texture) {
	clear_meta(TEXTURE_TABLE, texture);

	free(texture->data);

	texture->width = 0;
	texture->height = 0;
	texture->data = NULL;
}


//------------------------------------------------------------------------------


audio_t* rge_audio_load(const char* path) {
	audio_t* clip = rge_hash_table_add(tables[AUDIO_TABLE], path);
	if(clip->data != NULL)
		return clip;

	*clip = rge_audio_read(path);

	return clip;
}


//------------------------------------------------------------------------------


void rge_audio_free(audio_t* clip) {
	clear_meta(AUDIO_TABLE, clip);

	free(clip->data);

	// clip->length = 0;
}