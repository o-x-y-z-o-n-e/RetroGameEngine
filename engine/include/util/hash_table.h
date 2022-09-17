#ifndef RGE_HASH_TABLE_H
#define RGE_HASH_TABLE_H

#include <stddef.h>
#include <stdbool.h>

typedef struct hash_table_meta_t {
	bool used;
	size_t hash;
} hash_table_meta_t;

typedef struct hash_table_t {
	size_t table_size;
	size_t element_size;
	void* data;
	hash_table_meta_t* meta;
} hash_table_t;

hash_table_t* rge_hash_table_init(size_t table_size, size_t element_size);
void rge_hash_table_free(hash_table_t* table);
void rge_hash_table_remove(hash_table_t* table, const char* id);
void* rge_hash_table_add(hash_table_t* table, const char* id);
void* rge_hash_table_contains(const hash_table_t* table, const char* id);
void* rge_hash_table_get(const hash_table_t* table, const char* id);

#endif