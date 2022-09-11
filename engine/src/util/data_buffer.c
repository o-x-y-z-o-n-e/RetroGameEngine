#include "util/data_buffer.h"
#include <stdlib.h>
#include <stdint.h>

#define FREE_STACK_STEP 10


//------------------------------------------------------------------------------


data_buffer_t rge_data_buffer_init(size_t element_size, uint32_t start_size, uint32_t buffer_step) {
	data_buffer_t data_buffer;

	// Alloc the data buffer.
	data_buffer.buffer = calloc(start_size, element_size);
	data_buffer.element_size = element_size;
	data_buffer.buffer_step = buffer_step;
	data_buffer.buffer_size = start_size;

	// Alloc the free stack.
	data_buffer.free_stack_size = start_size;
	data_buffer.free_stack = calloc(start_size, sizeof(uint32_t));
	data_buffer.free_stack_ptr = data_buffer.free_stack_size - 1;

	// Fill the free stack.
	for(uint32_t i = 0; i < start_size; i++)
		data_buffer.free_stack[i] = start_size - 1 - i;
	
	return data_buffer;
}


//------------------------------------------------------------------------------


void rge_data_buffer_free(data_buffer_t* data_buffer) {
	free(data_buffer->buffer);
	free(data_buffer->free_stack);

	data_buffer->buffer = NULL;
	data_buffer->free_stack = NULL;
	data_buffer->buffer_size = 0;
	data_buffer->buffer_step = 0;
	data_buffer->element_size = 0;
	data_buffer->free_stack_ptr = 0;
	data_buffer->free_stack_size = 0;
}


//------------------------------------------------------------------------------


static void realloc_free_stack(data_buffer_t* data_buffer, uint32_t free_stack_size) {
	uint32_t* new_stack = realloc(data_buffer->free_stack, sizeof(uint32_t) * free_stack_size);
	data_buffer->free_stack = new_stack;
	data_buffer->free_stack_size = free_stack_size;
}


//------------------------------------------------------------------------------


uint32_t rge_data_buffer_add(data_buffer_t* data_buffer) {
	// Alloc new data.
	uint32_t index = data_buffer->free_stack[data_buffer->free_stack_ptr];
	uint8_t* data = rge_data_buffer_get(data_buffer, index);
	data_buffer->free_stack_ptr--;

	// Clear new data.
	for(size_t i = 0; i < data_buffer->element_size; i++)
		data[i] = 0;
	
	// Increase data buffer, if needed.
	if(data_buffer->free_stack_ptr == -1) {
		// Realloc new data buffer.
		uint32_t new_size = data_buffer->buffer_size + data_buffer->buffer_step;
		void* new_buffer = realloc(data_buffer->buffer, data_buffer->element_size * new_size);

		// Assign new data buffer.
		data_buffer->buffer = new_buffer;
		data_buffer->buffer_size = new_size;

		// Resize free stack, if needed.
		if(data_buffer->free_stack_size < data_buffer->buffer_step)
			realloc_free_stack(data_buffer, data_buffer->buffer_step);
		
		// Fill free stack.
		for(uint32_t i = 0; i < data_buffer->buffer_step; i++)
			data_buffer->free_stack[i] = new_size - 1 - i;

		// Set start of free stack.
		data_buffer->free_stack_ptr = data_buffer->free_stack_size - 1;
	}

	return index;
}


//------------------------------------------------------------------------------


void rge_data_buffer_remove(data_buffer_t* data_buffer, uint32_t index) {
	if(index < 0 || index >= data_buffer->buffer_size)
		return;

	data_buffer->free_stack_ptr++;

	// Increase free stack, if needed.
	if(data_buffer->free_stack_ptr >= data_buffer->free_stack_size) {
		data_buffer->free_stack_ptr = data_buffer->free_stack_size;

		uint32_t new_size = data_buffer->free_stack_size + FREE_STACK_STEP;
		uint32_t* new_stack = realloc(data_buffer->free_stack, sizeof(uint32_t) * new_size);
		if(new_stack == NULL)
			return;

		data_buffer->free_stack = new_stack;
		data_buffer->free_stack_size = new_size;
	}

	data_buffer->free_stack[data_buffer->free_stack_ptr] = index;
}


//------------------------------------------------------------------------------


void* rge_data_buffer_get(const data_buffer_t* data_buffer, uint32_t index) {
	if(index < 0 || index >= data_buffer->buffer_size)
		return NULL;

	uint8_t* ptr = data_buffer->buffer;
	ptr += index * data_buffer->element_size;

	return (void*)ptr;
}