#include "core/assets.h"
#include "util/hash_table.h"
#include "assets/texture.h"
#include "assets/sound.h"
#include "assets/pak.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_TABLES 2
#define TEXTURE_TABLE 0
#define SOUND_TABLE 1

#define TEXTURE_MAX 300
#define SOUND_MAX 300

#define REGISTRY_SIZE 1000

typedef struct record_t {
	char** path;
	uint32_t type;
	void* data;
} record_t;


//------------------------------------------------------------------------------


static record_t registry[REGISTRY_SIZE];
static hash_table_t* tables[NUM_TABLES];


//------------------------------------------------------------------------------


int rge_assets_init() {
	tables[TEXTURE_TABLE] = rge_hash_table_init(TEXTURE_MAX, sizeof(texture_t));
	tables[SOUND_TABLE] = rge_hash_table_init(SOUND_MAX, sizeof(sound_t));

	return 1;
}


//------------------------------------------------------------------------------


static void* read_from_disk(const char* path, int* out_size) {
	int s = 0;
	int n = strlen(path);
	for(s = 0; s < n; s++)
		if(path[s] == ':')
			break;

	if(s < n) {
		char* pack_path = malloc(s + 1);
		if(!pack_path)
			return NULL;

		for(int i = 0; i < s; i++)
			pack_path[i] = path[i];
		pack_path[s] = 0;

		pak_file_t file = rge_pak_load(pack_path, &path[s]);
		free(pack_path);

		if(out_size != NULL)
			*out_size = file.size;

		return file.data;
	} else {
		FILE* file = fopen(path, "rb");
		if(!file)
			return NULL;

		fseek(file, 0, SEEK_END);
		int size = ftell(file);
		rewind(file);

		void* data = malloc(size);
		if(!data)
			goto error;

		fread(data, 1, size, file);

		if(out_size != NULL)
			*out_size = size;

		error:
		fclose(file);
		return data;
	}
}


//------------------------------------------------------------------------------


static size_t get_data_index(int table, void* data) {
	return ((uint8_t*)data - (uint8_t*)tables[table]->data) / tables[table]->element_size;
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

	int size;
	void* raw = read_from_disk(path, &size);
	if(raw == NULL)
		return NULL;

	*texture = rge_texture_parse(raw, size);

	free(raw);
	return texture;
}


//------------------------------------------------------------------------------


sound_t* rge_sound_load(const char* path) {
	sound_t* clip = rge_hash_table_add(tables[SOUND_TABLE], path);
	if(clip->data != NULL)
		return clip;

	int size;
	void* raw = read_from_disk(path, &size);
	if(raw == NULL)
		return NULL;

	*clip = rge_sound_parse(raw, size);

	free(raw);
	return clip;
}