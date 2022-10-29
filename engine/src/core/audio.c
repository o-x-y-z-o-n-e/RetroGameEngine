#include "api/rge.h"
#include "assets/sound.h"

#define STB_VORBIS_HEADER_ONLY
#include "stb_vorbis.c"    /* Enables Vorbis decoding. */

#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"

/* stb_vorbis implementation must come after the implementation of miniaudio. */
#undef STB_VORBIS_HEADER_ONLY
#include "stb_vorbis.c"


//------------------------------------------------------------------------------


static ma_engine engine;


//------------------------------------------------------------------------------


void rge_audio_play(const sound_t* clip) {

}


//------------------------------------------------------------------------------


void rge_audio_stop_all() {

}


//------------------------------------------------------------------------------


int rge_audio_init() {
	ma_result result = ma_engine_init(NULL, &engine);
	if(result != MA_SUCCESS) {
		rge_log_error("Could not initialize audio");
		return 0;
	}

	return 1;
}


//------------------------------------------------------------------------------


void* rge_audio_get_engine() {
	return &engine;
}