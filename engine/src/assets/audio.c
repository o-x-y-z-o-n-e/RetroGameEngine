#include "assets/audio.h"
#include "core/audio_player.h"
#include <stddef.h>

#include "miniaudio.h"


//------------------------------------------------------------------------------


float rge_audio_get_length(const audio_t* clip) {
	// TODO
    return 0;
}


//------------------------------------------------------------------------------


audio_t rge_audio_read(const char* path) {
	ma_sound sound;
	ma_result result = ma_sound_init_from_file(rge_audio_get_engine(), path, 0, NULL, NULL, &sound);
	if(result != MA_SUCCESS) {
		return (audio_t) {
			NULL
		};
	}

	// TODO

	return (audio_t) {
		NULL
	};
}