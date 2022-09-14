#include "core/asset_manager.h"
#include "assets/texture.h"
#include "assets/audio.h"
#include <stdlib.h>

#define NUM_TABLES 2
#define TEXTURE_TABLE 0
#define AUDIO_TABLE 1

#define TEXTURE_MAX 300
#define AUDIO_MAX 300


//------------------------------------------------------------------------------


static void* tables[NUM_TABLES];


//------------------------------------------------------------------------------


static void* get_slot(int table, int item) {
	switch(table) {
		case TEXTURE_TABLE:
			return tables[TEXTURE_TABLE] + (item * sizeof(texture_t));
		case AUDIO_TABLE:
			return tables[AUDIO_TABLE] + (item * sizeof(audio_t));
	}

	return NULL;
}


//------------------------------------------------------------------------------


size_t rge_get_str_hash(const char* str) {
	size_t hash = 5381;
	char c;
	while((c = *str++) != 0)
		hash = ((hash << 5) + hash) + c;

	return hash;
}


//------------------------------------------------------------------------------


int rge_assets_init() {
	tables[TEXTURE_TABLE] = calloc(TEXTURE_MAX, sizeof(texture_t));
	tables[AUDIO_TABLE] = calloc(AUDIO_MAX, sizeof(audio_t));
	return 1;
}