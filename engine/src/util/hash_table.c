#include "util/hash_table.h"

#include <stdint.h>
#include <stdlib.h>

//------------------------------------------------------------------------------


static size_t get_str_hash(const char* str) {
	size_t hash = 5381;
	char c;
	while((c = *str++) != 0)
		hash = ((hash << 5) + hash) + c;

	return hash;
}


//------------------------------------------------------------------------------


hash_table_t* rge_hash_table_init(size_t table_size, size_t element_size) {
	hash_table_t* table = calloc(1, sizeof(hash_table_t));
	if(table == NULL)
		return NULL;

    table->table_size = table_size;
    table->element_size = element_size;
    table->data = calloc(table_size, element_size);
    table->meta = calloc(table_size, sizeof(hash_table_meta_t));

    return table;
}


//------------------------------------------------------------------------------


static void* rge_hash_table_fetch(const hash_table_t* table, uint32_t index) {
	return (void*)(((size_t)table->data) + (index * table->element_size));
}


//------------------------------------------------------------------------------


static uint32_t rge_hash_table_find(const hash_table_t* table, size_t hash, bool alloc_new) {
	// TODO: Check for overloaded table.
	// TODO: When items are removed and later items are 'get' but where collision probed was used.

	size_t start = hash % table->table_size;
	size_t i = 0;
	while(i < table->table_size) {
		size_t index = (start + (i * i)) % table->table_size;

		if((!table->meta[index].used && alloc_new) || table->meta[index].hash == hash) {
			// Found empty or matching slot.
			return (uint32_t)index;
		} else {
			i++;
		}
	}

	return table->table_size;
}


//------------------------------------------------------------------------------


void* rge_hash_table_get(const hash_table_t* table, const char* id) {
	size_t hash = get_str_hash(id);
	uint32_t index = rge_hash_table_find(table, hash, false);
	if(index >= table->table_size)
		return NULL;

	return rge_hash_table_fetch(table, index);
}


//------------------------------------------------------------------------------


void rge_hash_table_remove(hash_table_t* table, const char* id) {
	size_t hash = get_str_hash(id);

	uint32_t index = rge_hash_table_fetch(table, id);
	if(index >= table->table_size)
		return;

	if(!table->meta[index].used)
		return;

	table->meta[index].hash = 0;
	table->meta[index].used = false;
}


//------------------------------------------------------------------------------


void* rge_hash_table_add(hash_table_t* table, const char* id) {
	size_t hash = get_str_hash(id);

	uint32_t index = rge_hash_table_find(table, hash, true);
	if(index >= table->table_size)
		return NULL;

	table->meta[index].hash = hash;
	table->meta[index].used = true;

	return rge_hash_table_fetch(table, index);
}


//------------------------------------------------------------------------------


void* rge_hash_table_contains(const hash_table_t* table, const char* id) {
	return rge_hash_table_find(table, get_str_hash(id), false) < table->table_size;
}


//------------------------------------------------------------------------------


void rge_hash_table_free(hash_table_t* table) {
    free(table->data);
    free(table->meta);
	free(table);
}