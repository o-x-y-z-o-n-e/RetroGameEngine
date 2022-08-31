#ifndef PTR_BUFFER_H
#define PTR_BUFFER_H

#include <stdint.h>

typedef struct ptr_buffer_t {
	void** buffer;
	uint32_t buffer_size;
	uint16_t buffer_step;
	uint32_t next_check;
	// TODO: Change next_check to a stack.
	uint32_t* free_stack;
	uint32_t free_stack_ptr;
	uint32_t free_stack_size;
} ptr_buffer_t;

ptr_buffer_t init_ptr_buffer(uint16_t realloc_step);
void free_ptr_buffer(ptr_buffer_t* ptr_buffer);
uint32_t add_ptr_buffer(ptr_buffer_t* ptr_buffer, void* item);
void* get_ptr_buffer(ptr_buffer_t* ptr_buffer, uint32_t i);
uint32_t get_ptr_buffer_next(ptr_buffer_t* ptr_buffer);
void remove_ptr_buffer(ptr_buffer_t* ptr_buffer, void* item);
char contains_ptr_buffer(ptr_buffer_t* ptr_buffer, void* item);

#endif