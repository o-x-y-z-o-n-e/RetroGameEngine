#ifndef SCENE_H
#define SCENE_H

#include <stddef.h>
#include <stdint.h>

#include "util/data_buffer.h"

typedef struct entity_t entity_t;

typedef struct registry_t {
	uint8_t type;

	data_buffer_t components;
	entity_t** owners;
	uint32_t owners_size;
	
	void (*on_add)(void* cmp, entity_t* entity);
	void (*on_update)(void* cmp, float delta);
	void (*on_dispose)(void* cmp);
} registry_t;


typedef struct cmp_ref_t {
	registry_t* registry;
	uint16_t index;
} cmp_ref_t;


typedef struct entity_t {
	cmp_ref_t* components;
	uint8_t component_count;
} entity_t;


int init_scene();
void clear_scene();
void update_scene(float delta);

entity_t* create_entity();
void free_entity(entity_t* entity);

registry_t* init_registry(uint8_t type, size_t element_size, uint32_t start_size, uint32_t increase_step);
registry_t* create_registry(uint8_t type, size_t element_size);
void update_registry(const registry_t* registry, float delta);
registry_t* get_registry_of_type(uint8_t type);
void free_registry(registry_t* registry);

void* create_component(entity_t* entity, registry_t* registry);
void remove_component(entity_t* entity, uint8_t i);
void* get_component(const entity_t* entity, uint8_t i);
uint8_t get_component_index(const entity_t* entity, const void* component);
void* get_component_of_type(const entity_t* entity, uint8_t type);
uint8_t get_component_count(const entity_t* entity);

void set_on_add(registry_t* registry, void (*func)(void* cmp, entity_t* entity));
void set_on_update(registry_t* registry, void (*func)(void* cmp, float delta));
void set_on_dispose(registry_t* registry, void (*func)(void* cmp));

#endif