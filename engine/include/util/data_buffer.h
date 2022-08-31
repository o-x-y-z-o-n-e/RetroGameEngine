#ifndef DATA_BUFFER_H
#define DATA_BUFFER_H

#include <stdint.h>
#include <stddef.h>

typedef struct data_buffer_t {
	void* buffer;
	size_t element_size;
	uint32_t buffer_size;
	uint32_t buffer_step;

	uint32_t* free_stack;
	uint32_t free_stack_ptr;
	uint32_t free_stack_size;
} data_buffer_t;

data_buffer_t init_data_buffer(size_t element_size, uint32_t start_size, uint32_t buffer_step);
void free_data_buffer(data_buffer_t* data_buffer);
uint32_t add_data_buffer(data_buffer_t* data_buffer);
void remove_data_buffer(data_buffer_t* data_buffer, uint32_t index);
void* get_data_buffer(const data_buffer_t* data_buffer, uint32_t index);

#endif