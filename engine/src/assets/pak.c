#include "assets/pak.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct pak_header_t {
	char id[4];
	uint32_t offset;
	uint32_t size;
} pak_header_t;

typedef struct pak_entry_t {
	char name[56];
	uint32_t offset;
	uint32_t size;
} pak_entry_t;


//------------------------------------------------------------------------------


pak_file_t rge_pak_load(const char* pak_path, const char* file_path) {
	FILE* file;
	pak_header_t header;
	pak_entry_t entry;
	uint32_t num_files;
	void* buffer;

	file = fopen(pak_path, "rb");
	if(!file)
		return (const pak_file_t) { 0, NULL };

	if(!fread(&header, sizeof(pak_header_t), 1, file))
		goto error;

	if(memcmp(header.id, "PACK", 4))
		goto error;

	num_files = header.size / sizeof(pak_file_t);

	if(fseek(file, header.offset, SEEK_SET))
		goto error;

	// Loop through file index.
	for(uint32_t i = 0; i < num_files; i++) {
		// Load file entry.
		if(!fread(&entry, sizeof(pak_file_t), 1, file))
			goto error;

		// If entry name & file_path do not match, then skip...
		if(strcmp(entry.name, file_path))
			continue;

		// Seek to start of file.
		if(fseek(file, entry.offset, SEEK_SET))
			goto error;

		// Allocate room for file.
		buffer = malloc(entry.size);
		if(!buffer)
			goto error;

		// Copy file contents into buffer.
		if(!fread(buffer, entry.size, 1, file)) {
			free(buffer);
			goto error;
		}

		fclose(file);
		return (pak_file_t) {
			entry.size,
			buffer
		};
	}

	error:
	fclose(file);
	return (const pak_file_t) { 0, NULL };
}