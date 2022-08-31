#include "util/ptr_buffer.h"
#include "util/debug.h"
#include <stdlib.h>


//------------------------------------------------------------------------------


void free_ptr_buffer(ptr_buffer_t* ptr_buffer) {
	free(ptr_buffer->buffer);
	ptr_buffer->buffer = NULL;
	ptr_buffer->buffer_size = 0;
	ptr_buffer->buffer_step = 0;
	ptr_buffer->next_check = 0;
}


//------------------------------------------------------------------------------


ptr_buffer_t init_ptr_buffer(uint16_t realloc_step) {
	ptr_buffer_t ptr_buffer;

	ptr_buffer.buffer = calloc(realloc_step, sizeof(void*));
	ptr_buffer.buffer_size = realloc_step;
	ptr_buffer.buffer_step = realloc_step;
	ptr_buffer.next_check = 0;

	return ptr_buffer;
}


//------------------------------------------------------------------------------


uint32_t get_ptr_buffer_next(ptr_buffer_t* ptr_buffer) {
	// Find next available pointer.
	while(ptr_buffer->next_check < ptr_buffer->buffer_size) {
		if(ptr_buffer->buffer[ptr_buffer->next_check] == NULL)
			break;

		ptr_buffer->next_check++;
	}

	if(ptr_buffer->next_check >= ptr_buffer->buffer_size) {
		ptr_buffer->next_check = ptr_buffer->buffer_size;

		// Create new buffer.
		uint32_t new_size = ptr_buffer->buffer_size + ptr_buffer->buffer_step;
		void** new_buffer = realloc(ptr_buffer->buffer, sizeof(void*) * new_size);
		if(new_buffer == NULL) {
			log_error("Failed to resize pointer buffer");
			return -1;
		}

		// Clear the new alloc memory.
		for(uint32_t i = ptr_buffer->buffer_size; i < new_size; i++)
			new_buffer[i] = NULL;

		// Assign new buffer to scene.
		ptr_buffer->buffer = new_buffer;
		ptr_buffer->buffer_size = new_size;
	}

	return ptr_buffer->next_check;
}


//------------------------------------------------------------------------------


uint32_t add_ptr_buffer(ptr_buffer_t* ptr_buffer, void* item) {
	uint32_t index = get_ptr_buffer_next(ptr_buffer);
	ptr_buffer->buffer[index] = item;

	return index;
}


//------------------------------------------------------------------------------


void remove_ptr_buffer(ptr_buffer_t* ptr_buffer, void* item) {
	uint32_t index = (uint32_t)(((size_t)ptr_buffer->buffer - (size_t)item) / sizeof(void*));
	if(index < 0 || index >= ptr_buffer->buffer_size) {
		log_error("Failed to remove pointer: Index out of bounds");
		return;
	}

	if(index < ptr_buffer->next_check)
		ptr_buffer->next_check = index;

	ptr_buffer->buffer[index] = NULL;
}


//------------------------------------------------------------------------------


void* get_ptr_buffer(ptr_buffer_t* ptr_buffer, uint32_t i) {
	return ptr_buffer->buffer[i];
}


//------------------------------------------------------------------------------


char contains_ptr_buffer(ptr_buffer_t* ptr_buffer, void* item) {
	uint32_t index = (uint32_t)(((size_t)ptr_buffer->buffer - (size_t)item) / sizeof(void*));
	return index >= 0 && index < ptr_buffer->buffer_size;
}