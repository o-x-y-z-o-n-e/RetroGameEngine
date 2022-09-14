#include "util/hash_table.h"

#include <stdlib.h>

typedef struct hash_table_meta_t {
    char used;
    size_t hash;
} hash_table_meta_t;

typedef struct hash_table_t {
    size_t table_size;
    size_t element_size;
    void* data;
    hash_table_meta_t* meta;
} hash_table_t;


//------------------------------------------------------------------------------


hash_table_t rge_hash_table_init(size_t table_size, size_t element_size) {
    hash_table_t table;

    table.table_size = table_size;
    table.element_size = element_size;
    table.data = calloc(table_size, element_size);
    table.meta = calloc(table_size, sizeof(hash_table_meta_t));

    return table;
}


//------------------------------------------------------------------------------


void rge_hash_table_free(hash_table_t table) {
    free(table.data);
    free(table.meta);
}