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

ptr_buffer_t rge_ptr_buffer_init(uint16_t realloc_step);
void rge_ptr_buffer_free(ptr_buffer_t* ptr_buffer);
uint32_t rge_ptr_buffer_add(ptr_buffer_t* ptr_buffer, void* item);
void* rge_ptr_buffer_get(ptr_buffer_t* ptr_buffer, uint32_t i);
uint32_t rge_ptr_buffer_get_next(ptr_buffer_t* ptr_buffer);
void rge_ptr_buffer_remove(ptr_buffer_t* ptr_buffer, void* item);
char rge_ptr_buffer_contains(ptr_buffer_t* ptr_buffer, void* item);

#endif