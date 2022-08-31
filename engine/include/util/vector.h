#ifndef VECTOR_H
#define VECTOR_H

#include <stdint.h>
#include <stddef.h>

typedef struct vector_t vector_t;

vector_t* vecinit(size_t size, uint32_t length);
void vecfree(vector_t* vec);
void vecsize(vector_t* vec, uint32_t length);
uint32_t veclen(vector_t* vec);
void* vecget(vector_t* vec, uint32_t i);
void vecset(vector_t* vec, uint32_t i, void* data);

#endif