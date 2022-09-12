#ifndef RGE_DATA_BUFFER_H
#define RGE_DATA_BUFFER_H

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

data_buffer_t rge_data_buffer_init(size_t element_size, uint32_t start_size, uint32_t buffer_step);
void rge_data_buffer_free(data_buffer_t* data_buffer);
uint32_t rge_data_buffer_add(data_buffer_t* data_buffer);
void rge_data_buffer_remove(data_buffer_t* data_buffer, uint32_t index);
void* rge_data_buffer_get(const data_buffer_t* data_buffer, uint32_t index);

#endif