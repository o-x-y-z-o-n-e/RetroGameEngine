#ifndef RGE_AUDIO_H
#define RGE_AUDIO_H

typedef struct audio_t {
	void* data;
} audio_t;

audio_t rge_audio_read(const char* path);

#endif