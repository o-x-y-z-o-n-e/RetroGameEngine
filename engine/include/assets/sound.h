#ifndef RGE_SOUND_H
#define RGE_SOUND_H

typedef struct sound_t {
	void* data;
} sound_t;

sound_t rge_sound_parse(void* buffer, int size);

#endif