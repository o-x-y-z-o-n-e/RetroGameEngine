#include "assets/sound.h"
#include "core/audio.h"
#include <stddef.h>

#include "miniaudio.h"


//------------------------------------------------------------------------------


float rge_sound_get_length(const sound_t* clip) {
	// TODO
    return 0;
}


//------------------------------------------------------------------------------


// TODO: Delete
sound_t rge_sound_read(const char* path) {
	ma_sound sound;
	ma_result result = ma_sound_init_from_file(rge_audio_get_engine(), path, 0, NULL, NULL, &sound);
	if(result != MA_SUCCESS) {
		return (sound_t) {
			NULL
		};
	}

	// TODO

	return (sound_t) {
		NULL
	};
}


//------------------------------------------------------------------------------


sound_t rge_sound_parse(void* buffer, int size) {
	return (sound_t) {
		NULL
	};
}