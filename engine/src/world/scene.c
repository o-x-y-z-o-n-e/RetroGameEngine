#include "world/scene.h"
#include "world/transform.h"
#include "util/ptr_buffer.h"
#include "util/debug.h"
#include "core/core.h"

#include <stdlib.h>
#include <stdint.h>

#define ENTITY_BUFFER_STEP 25
#define REGISTRY_BUFFER_STEP 25

struct {
	char has_init;
	ptr_buffer_t registries;
	ptr_buffer_t entities;
} static scene;

#define CHECK_INIT if(!scene.has_init) { log_error("Scene not initialized"); return; }
#define CHECK_INIT_VAL(R) if(!scene.has_init) { log_error("Scene not initialized"); return R; }


//------------------------------------------------------------------------------


static void create_registries() {
	create_registry(TYPE_TRANSFORM, sizeof(transform_t));
}


//------------------------------------------------------------------------------


static void alloc_scene() {
	scene.entities = init_ptr_buffer(ENTITY_BUFFER_STEP);
	scene.registries = init_ptr_buffer(REGISTRY_BUFFER_STEP);
}


//------------------------------------------------------------------------------


int init_scene() {
	if(scene.has_init) {
		log_error("Scene already initialized");
		return 0;
	}

	scene.has_init = 1;

	alloc_scene();
	create_registries();

	return 1;
}


//------------------------------------------------------------------------------


void clear_scene() {
	CHECK_INIT;

	// Free each entity.
	for(uint32_t i = 0; i < scene.entities.buffer_size; i++) {
		entity_t* entity = get_ptr_buffer(&scene.entities, i);
		if(entity != NULL)
			free_entity(entity);
	}

	// Free each registry.
	for(uint32_t i = 0; i < scene.registries.buffer_size; i++) {
		registry_t* registry = get_ptr_buffer(&scene.registries, i);
		if(registry != NULL)
			free_registry(registry);
	}

	// Free old entity & registry lists.
	free_ptr_buffer(&scene.registries);
	free_ptr_buffer(&scene.entities);
	
	// Create new scene.
	alloc_scene();
	create_registries();
}


//------------------------------------------------------------------------------


void update_scene(float delta) {
	CHECK_INIT;

	for(uint32_t i = 0; i < scene.registries.buffer_size; i++) {
		registry_t* reg = scene.registries.buffer[i];
		if(reg != NULL)
			update_registry(reg, delta);
	}
}


//------------------------------------------------------------------------------


void update_registry(const registry_t* registry, float delta) {
	if(registry->on_update == NULL)
		return;

	for(uint16_t j = 0; j < registry->components.buffer_size; j++) {
		if(registry->owners[j] == NULL)
			continue;

		void* cmp = get_data_buffer(&registry->components, j);
		entity_t* entity = registry->owners[j];

		registry->on_update(cmp, delta);
	}
}


//------------------------------------------------------------------------------


static entity_t* init_entity() {
	entity_t* entity = calloc(1, sizeof(entity_t));

	return entity;
}


//------------------------------------------------------------------------------


entity_t* create_entity() {
	CHECK_INIT_VAL(NULL);

	entity_t* entity = init_entity();
	add_ptr_buffer(&scene.entities, entity);

	return entity;
}


//------------------------------------------------------------------------------


void free_entity(entity_t* entity) {
	CHECK_INIT;

	// Free components.
	for(uint8_t i = 0; i < entity->component_count; i++) {
		cmp_ref_t cmp_ref = entity->components[i];
		
		// Call dispose fucntion for component.
		if(cmp_ref.registry->on_dispose != NULL)
			cmp_ref.registry->on_dispose(get_component(entity, i));

		// Remove component from registry.
		remove_data_buffer(&cmp_ref.registry->components, cmp_ref.index);
		cmp_ref.registry->owners[cmp_ref.index] = NULL;
	}
	free(entity->components);

	// Remove from entity list.
	remove_ptr_buffer(&scene.entities, entity);
	
	// Free entity.
	free(entity);
}


//------------------------------------------------------------------------------


static cmp_ref_t alloc_component(registry_t* registry) {
	// Allocate component block.
	uint32_t index = add_data_buffer(&registry->components);

	// Resize registry owners array, if needed.
	if(registry->owners_size < registry->components.buffer_size) {
		entity_t** new_owners = realloc(registry->owners, sizeof(entity_t*) * registry->components.buffer_size);
		if(new_owners == NULL) {
			log_error("Oh no!");
			crash_core(1);
		}

		for(uint32_t i = registry->owners_size; i < registry->components.buffer_size; i++)
			new_owners[i] = NULL;
		
		registry->owners = new_owners;
		registry->owners_size = registry->components.buffer_size;
	}

	return (cmp_ref_t) {
		registry,
		(uint16_t)index
	};
}


//------------------------------------------------------------------------------


static uint8_t add_component(entity_t* entity, cmp_ref_t cmp_ref) {
	// Resize entity component reference.
	uint8_t new_count = entity->component_count + 1;
	cmp_ref_t* new_buffer = realloc(entity->components, sizeof(cmp_ref_t) * new_count);
	if(new_buffer == NULL)
		return -1;

	uint8_t index = new_count - 1;

	// Assign new component reference on entity.
	entity->components = new_buffer;
	entity->components[index] = cmp_ref;
	entity->component_count = new_count;

	// Assign entity as owner of component on registry.
	cmp_ref.registry->owners[cmp_ref.index] = entity;

	// Call component on add function.
	if(cmp_ref.registry->on_add != NULL)
		cmp_ref.registry->on_add(get_component(entity, index), entity);

	return index;
}


//------------------------------------------------------------------------------


uint8_t get_component_index(const entity_t* entity, const void* component) {
	for(uint8_t i = 0; i < entity->component_count; i++)
		if(get_component(entity, i) == component)
			return i;
	
	return 255;
}


//------------------------------------------------------------------------------


void remove_component(entity_t* entity, uint8_t i) {
	if(i >= entity->component_count)
		return;

	cmp_ref_t cmp_ref = entity->components[i];
	registry_t* registry = cmp_ref.registry;

	// Call dispose fucntion for component.
	if(registry->on_dispose != NULL)
		registry->on_dispose(get_component(entity, i));

	// Remove component from registry.
	remove_data_buffer(&registry->components, cmp_ref.index);
	registry->owners[cmp_ref.index] = NULL;
	
	// Resize component references on entity.
	uint8_t new_count = entity->component_count - 1;
	cmp_ref_t* new_buffer = calloc(new_count, sizeof(cmp_ref_t));
	if(new_buffer == NULL)
		return;

	// Copy data from old buffer to new.
	for(uint8_t j = 0; j < i; j++)
		new_buffer[j] = entity->components[j];
	for(uint8_t j = i + 1; j < entity->component_count; j++)
		new_buffer[j - 1] = entity->components[j];

	// Free old component buffer.
	free(entity->components);

	// Assign new component buffer.
	entity->components = new_buffer;
	entity->component_count = new_count;
}


//------------------------------------------------------------------------------


void* create_component(entity_t* entity, registry_t* registry) {
	CHECK_INIT_VAL(NULL);

	if(registry == NULL) {
		log_error("No component buffer passed");
		return NULL;
	}

	if(entity == NULL) {
		log_error("No entity passed");
		return NULL;
	}

	cmp_ref_t cmp_ref = alloc_component(registry);
	uint8_t index = add_component(entity, cmp_ref);

	return get_component(entity, index);
}


//------------------------------------------------------------------------------


void* get_component(const entity_t* entity, uint8_t i) {
	if(entity == NULL) {
		log_error("No entity passed");
		return NULL;
	}

	if(i >= entity->component_count) {
		log_error("Component index out of bounds");
		return NULL;
	}

	cmp_ref_t ref = entity->components[i];
	return get_data_buffer(&ref.registry->components, ref.index);
}


//------------------------------------------------------------------------------


registry_t* create_registry(uint8_t type, size_t element_size) {
	CHECK_INIT_VAL(NULL);

	registry_t* registry = init_registry(type, element_size, 25, 25); // TODO: custom start & increase.
	add_ptr_buffer(&scene.registries, registry);

	return registry;
}


//------------------------------------------------------------------------------


registry_t* init_registry(uint8_t type, size_t element_size, uint32_t start_size, uint32_t increase_step) {
	registry_t* registry = calloc(1, sizeof(registry_t));
	if(registry == NULL) {
		log_error("Failed to create component buffer");
		return NULL;
	}

	registry->type = type;
	registry->components = init_data_buffer(element_size, start_size, increase_step);
	registry->owners = calloc(start_size, sizeof(entity_t*));
	registry->owners_size = start_size;
	registry->on_add = NULL;
	registry->on_update = NULL;
	registry->on_dispose = NULL;

	return registry;
}


//------------------------------------------------------------------------------


void free_registry(registry_t* registry) {
	// Remove from registry list.
	remove_ptr_buffer(&scene.registries, registry);

	// Free registry.
	free_data_buffer(&registry->components);
	free(registry->owners);
	free(registry);
}


//------------------------------------------------------------------------------


uint8_t get_component_count(const entity_t* entity) {
	if(entity == NULL) {
		log_error("No entity passed");
		return 0;
	}

	return entity->component_count;
}


//------------------------------------------------------------------------------


void set_on_add(registry_t* registry, void (*func)(void* cmp, entity_t* entity)) {
	registry->on_add = func;
}


//------------------------------------------------------------------------------


void set_on_update(registry_t* registry, void (*func)(void* cmp, float delta)) {
	registry->on_update = func;
}


//------------------------------------------------------------------------------


void set_on_dispose(registry_t* registry, void (*func)(void* cmp)) {
	registry->on_dispose = func;
}


//------------------------------------------------------------------------------


void* get_component_of_type(const entity_t* entity, uint8_t type) {
	if(entity == NULL) {
		log_error("No entity passed");
		return NULL;
	}

	for(uint8_t i = 0; i < entity->component_count; i++)
		if(entity->components[i].registry->type == type)
			return get_component(entity, i);
	
	return NULL;
}


//------------------------------------------------------------------------------


registry_t* get_registry_of_type(uint8_t type) {
	for(uint32_t i = 0; i < scene.registries.buffer_size; i++)
		if(scene.registries.buffer[i] != NULL)
			if(((registry_t*)(scene.registries.buffer[i]))->type == type)
				return scene.registries.buffer[i];

	return NULL;
}