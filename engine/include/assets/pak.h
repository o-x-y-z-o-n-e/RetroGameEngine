#ifndef RGE_PAK_H
#define RGE_PAK_H

#include "api/rge.h"

typedef struct pak_file_t {
	uint32_t size;
	void* data;
} pak_file_t;

pak_file_t rge_pak_load(const char* pak_path, const char* file_path);

#endif