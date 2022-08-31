#include "util/vector.h"
#include <stdlib.h>


//------------------------------------------------------------------------------


#define DEFAULT_BUFFER_SIZE 10

typedef uint8_t byte_t;

typedef struct vector_t {
    byte_t* ptr;    // pointer to buffer.
    size_t m;       // element size (immutable).
    uint32_t n;     // element count.
    uint32_t s;     // element buffer step (immutable).
    uint32_t b;     // element buffer count.
} vector_t;


//------------------------------------------------------------------------------


void vecsize(vector_t* vec, uint32_t length) {
    // if new length is greater than current buffer.
    if(length > vec->b) {
        int k = length / vec->s;
        if(length % vec->s > 0)
            k++;

        // new element buffer count.
        vec->b = k * vec->s;

        // create new buffer.
        byte_t* newptr = (byte_t*)malloc(vec->m * vec->b);
        if(newptr == NULL)
            return;

        // copy element data from old buffer to new buffer.
        if(vec->ptr != NULL) {
            size_t c = vec->m*vec->n;

            for(size_t i = 0; i < c; i++)
                newptr[i] = vec->ptr[i];

            free(vec->ptr);
        }

        // assign new buffer.
        vec->ptr = newptr;
    }

    // set new element count.
    vec->n = length;
}


//------------------------------------------------------------------------------


vector_t* vecinit(size_t size, uint32_t length) {
    vector_t* vec = (vector_t*)malloc(sizeof(vector_t));
    if(vec == NULL)
        return NULL;

    vec->m = size;
    vec->s = DEFAULT_BUFFER_SIZE;
    vecsize(vec, length);

    return vec;
}


//------------------------------------------------------------------------------


uint32_t veclen(vector_t* vec) {
    return vec->n;
}


//------------------------------------------------------------------------------


void* vecget(vector_t* vec, uint32_t i) {
    if(i < 0 || i >= vec->n)
        return NULL;
    
    return &vec->ptr[i*vec->m];
}


//------------------------------------------------------------------------------


void vecset(vector_t* vec, uint32_t i, void* data) {
    if(i < 0 || i >= vec->n)
        return;

    for(size_t j = 0; j < vec->m; j++)
        vec->ptr[(i*vec->m) + j] = ((byte_t*)data)[j];
}


//------------------------------------------------------------------------------


void vecfree(vector_t* vec) {
    if(vec == NULL)
        return;

    if(vec->ptr != NULL)
        free(vec->ptr);

    free(vec);
}