#ifndef RGE_HASH_TABLE_H
#define RGE_HASH_TABLE_H

#include <stddef.h>

typedef struct hash_table_t hash_table_t;

hash_table_t rge_hash_table_init(size_t table_size, size_t element_size);
void rge_hash_table_free(hash_table_t table);

#endif