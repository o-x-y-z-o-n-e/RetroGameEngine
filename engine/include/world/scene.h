#ifndef SCENE_H
#define SCENE_H

#include "api/rge.h"
#include "util/data_buffer.h"

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

int rge_scene_init();
void rge_scene_clear();
void rge_scene_update(float delta);

registry_t* rge_registry_init(uint8_t type, size_t element_size, uint32_t start_size, uint32_t increase_step);
void rge_registry_update(const registry_t* registry, float delta);
void rge_registry_free(registry_t* registry);

#endif