#include "api/rge.h"
#include "core/scene.h"
#include "core/core.h"
#include "components/transform.h"
#include "util/ptr_buffer.h"

#include <stdlib.h>

#define ENTITY_BUFFER_STEP 25
#define REGISTRY_BUFFER_STEP 25

struct {
	char has_init;
	ptr_buffer_t registries;
	ptr_buffer_t entities;
} static scene;

#define CHECK_INIT if(!scene.has_init) { rge_log_error("Scene not initialized"); return; }
#define CHECK_INIT_VAL(R) if(!scene.has_init) { rge_log_error("Scene not initialized"); return R; }


//------------------------------------------------------------------------------


static void create_registries() {
	rge_registry_create(TYPE_TRANSFORM, sizeof(transform_t));
}


//------------------------------------------------------------------------------


static void alloc_scene() {
	scene.entities = rge_ptr_buffer_init(ENTITY_BUFFER_STEP);
	scene.registries = rge_ptr_buffer_init(REGISTRY_BUFFER_STEP);
}


//------------------------------------------------------------------------------


static bool rge_entity_add_child(entity_t* entity, entity_t* child) {
	if(entity == NULL || child == NULL)
		return false;

	if(rge_entity_contains_child(entity, child))
		return false;

	uint32_t new_count = entity->child_count + 1;
	entity_t** new_buffer = realloc(entity->children, sizeof(entity_t*) * new_count);
	if(new_buffer == NULL)
		return false;

	new_buffer[entity->child_count] = child;
	entity->children = new_buffer;
	entity->child_count = new_count;
}


//------------------------------------------------------------------------------


static void rge_entity_remove_child(entity_t* entity, entity_t* child) {
	if(entity == NULL || child == NULL)
		return;

	uint32_t index = rge_entity_get_child_index(entity, child);
	if(index >= entity->child_count)
		return;

	// Resize component references on entity.
	uint8_t new_count = entity->child_count - 1;
	entity_t** new_buffer = calloc(new_count, sizeof(entity_t*));
	if(new_buffer == NULL)
		return;

	// Copy data from old buffer to new.
	for(uint8_t j = 0; j < index; j++)
		new_buffer[j] = entity->children[j];
	for(uint8_t j = index + 1; j < entity->child_count; j++)
		new_buffer[j - 1] = entity->children[j];

	// Free old component buffer.
	free(entity->children);

	// Assign new component buffer.
	entity->children = new_buffer;
	entity->child_count = new_count;
}


//------------------------------------------------------------------------------


static void rge_entity_free(entity_t* entity) {
	CHECK_INIT;

	if(entity == NULL)
		return;

	// Free children.
	free(entity->children);

	// Free components.
	for(uint8_t i = 0; i < entity->component_count; i++) {
		cmp_ref_t cmp_ref = entity->components[i];

		// Call dispose fucntion for component.
		if(cmp_ref.registry->on_dispose != NULL)
			cmp_ref.registry->on_dispose(rge_component_get(entity, i));

		// Remove component from registry.
		rge_data_buffer_remove(&cmp_ref.registry->components, cmp_ref.index);
		cmp_ref.registry->owners[cmp_ref.index] = NULL;
	}
	free(entity->components);

	// Remove from entity list.
	rge_ptr_buffer_remove(&scene.entities, entity);

	// Free entity.
	free(entity);
}


//------------------------------------------------------------------------------


int rge_scene_init() {
	if(scene.has_init) {
		rge_log_error("Scene already initialized");
		return 0;
	}

	scene.has_init = 1;

	alloc_scene();
	create_registries();

	return 1;
}


//------------------------------------------------------------------------------


void rge_scene_clear() {
	CHECK_INIT;

	// Free each entity.
	for(uint32_t i = 0; i < scene.entities.buffer_size; i++) {
		entity_t* entity = rge_ptr_buffer_get(&scene.entities, i);
		if(entity != NULL)
			rge_entity_free(entity);
	}

	// Free each registry.
	for(uint32_t i = 0; i < scene.registries.buffer_size; i++) {
		registry_t* registry = rge_ptr_buffer_get(&scene.registries, i);
		if(registry != NULL)
			rge_registry_free(registry);
	}

	// Free old entity & registry lists.
	rge_ptr_buffer_free(&scene.registries);
	rge_ptr_buffer_free(&scene.entities);
	
	// Create new scene.
	alloc_scene();
	create_registries();
}


//------------------------------------------------------------------------------


void rge_scene_update(float delta) {
	CHECK_INIT;

	for(uint32_t i = 0; i < scene.registries.buffer_size; i++) {
		registry_t* reg = scene.registries.buffer[i];
		if(reg != NULL)
			rge_registry_update(reg, delta);
	}
}


//------------------------------------------------------------------------------


void rge_registry_update(const registry_t* registry, float delta) {
	if(registry->on_update == NULL)
		return;

	for(uint16_t j = 0; j < registry->components.buffer_size; j++) {
		if(registry->owners[j] == NULL)
			continue;

		void* cmp = rge_data_buffer_get(&registry->components, j);
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


entity_t* rge_entity_create() {
	CHECK_INIT_VAL(NULL);

	entity_t* entity = init_entity();
	rge_ptr_buffer_add(&scene.entities, entity);

	return entity;
}


//------------------------------------------------------------------------------


void rge_entity_destroy(entity_t* entity) {
	CHECK_INIT;

	if(entity == NULL)
		return;

	// Detach from parent.
	if(entity->parent != NULL)
		rge_entity_remove_child(entity->parent, entity);

	// Destroy children.
	for(uint32_t i = 0; i < entity->child_count; i++)
		rge_entity_destroy(entity->children[i]);

	// Free entity.
	rge_entity_free(entity);
}


//------------------------------------------------------------------------------


bool rge_entity_contains_child(const entity_t* entity, const entity_t* child) {
	for(uint32_t i = 0; i < entity->child_count; i++)
		if(entity->children[i] == child)
			return true;

	return false;
}


//------------------------------------------------------------------------------


entity_t* rge_entity_get_child(const entity_t* entity, uint32_t index) {
	if(entity == NULL)
		return NULL;

	if(index >= entity->child_count)
		return NULL;

	return entity->children[index];
}


//------------------------------------------------------------------------------


uint32_t rge_entity_get_child_count(const entity_t* entity) {
	if(entity == NULL)
		return 0;

	return entity->child_count;
}


//------------------------------------------------------------------------------


uint32_t rge_entity_get_child_index(const entity_t* entity, const entity_t* child) {
	for(uint32_t i = 0; i < entity->child_count; i++)
		if(entity->children[i] == child)
			return i;
	
	return -1;
}


//------------------------------------------------------------------------------


bool rge_entity_set_parent(entity_t* entity, entity_t* parent) {
	if(entity == NULL)
		return false;

	if(entity->parent == parent)
		return false;

	if(entity->parent != NULL)
		rge_entity_remove_child(entity->parent, entity);

	if(parent != NULL) {
		if(rge_entity_add_child(parent, entity)) {
			entity->parent = parent;
			return true;
		} else {
			entity->parent = NULL;
			return false;
		}
	} else {
		entity->parent = NULL;
		return true;
	}
}


//------------------------------------------------------------------------------


static cmp_ref_t alloc_component(registry_t* registry) {
	// Allocate component block.
	uint32_t index = rge_data_buffer_add(&registry->components);

	// Resize registry owners array, if needed.
	if(registry->owners_size < registry->components.buffer_size) {
		entity_t** new_owners = realloc(registry->owners, sizeof(entity_t*) * registry->components.buffer_size);
		if(new_owners == NULL) {
			rge_log_error("Oh no!");
			rge_core_crash(1);
			return;
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
		cmp_ref.registry->on_add(rge_component_get(entity, index), entity);

	return index;
}


//------------------------------------------------------------------------------


uint8_t rge_component_get_index(const entity_t* entity, const void* component) {
	for(uint8_t i = 0; i < entity->component_count; i++)
		if(rge_component_get(entity, i) == component)
			return i;
	
	return 255;
}


//------------------------------------------------------------------------------


void rge_component_remove(entity_t* entity, uint8_t i) {
	if(i >= entity->component_count)
		return;

	cmp_ref_t cmp_ref = entity->components[i];
	registry_t* registry = cmp_ref.registry;

	// Call dispose fucntion for component.
	if(registry->on_dispose != NULL)
		registry->on_dispose(rge_component_get(entity, i));

	// Remove component from registry.
	rge_data_buffer_remove(&registry->components, cmp_ref.index);
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


void* rge_component_create(entity_t* entity, registry_t* registry) {
	CHECK_INIT_VAL(NULL);

	if(registry == NULL) {
		rge_log_error("No component buffer passed");
		return NULL;
	}

	if(entity == NULL) {
		rge_log_error("No entity passed");
		return NULL;
	}

	cmp_ref_t cmp_ref = alloc_component(registry);
	uint8_t index = add_component(entity, cmp_ref);

	return rge_component_get(entity, index);
}


//------------------------------------------------------------------------------


void* rge_component_get(const entity_t* entity, uint8_t i) {
	if(entity == NULL) {
		rge_log_error("No entity passed");
		return NULL;
	}

	if(i >= entity->component_count) {
		rge_log_error("Component index out of bounds");
		return NULL;
	}

	cmp_ref_t ref = entity->components[i];
	return rge_data_buffer_get(&ref.registry->components, ref.index);
}


//------------------------------------------------------------------------------


registry_t* rge_registry_create(uint8_t type, size_t element_size) {
	CHECK_INIT_VAL(NULL);

	registry_t* registry = rge_registry_init(type, element_size, 25, 25); // TODO: custom start & increase.
	rge_ptr_buffer_add(&scene.registries, registry);

	return registry;
}


//------------------------------------------------------------------------------


registry_t* rge_registry_init(uint8_t type, size_t element_size, uint32_t start_size, uint32_t increase_step) {
	registry_t* registry = calloc(1, sizeof(registry_t));
	if(registry == NULL) {
		rge_log_error("Failed to create component buffer");
		return NULL;
	}

	registry->type = type;
	registry->components = rge_data_buffer_init(element_size, start_size, increase_step);
	registry->owners = calloc(start_size, sizeof(entity_t*));
	registry->owners_size = start_size;
	registry->on_add = NULL;
	registry->on_update = NULL;
	registry->on_dispose = NULL;

	return registry;
}


//------------------------------------------------------------------------------


void rge_registry_free(registry_t* registry) {
	// Remove from registry list.
	rge_ptr_buffer_remove(&scene.registries, registry);

	// Free registry.
	rge_data_buffer_free(&registry->components);
	free(registry->owners);
	free(registry);
}


//------------------------------------------------------------------------------


uint8_t rge_component_get_count(const entity_t* entity) {
	if(entity == NULL) {
		rge_log_error("No entity passed");
		return 0;
	}

	return entity->component_count;
}


//------------------------------------------------------------------------------


void rge_registry_set_on_add(registry_t* registry, void (*func)(void* cmp, entity_t* entity)) {
	registry->on_add = func;
}


//------------------------------------------------------------------------------


void rge_registry_set_on_update(registry_t* registry, void (*func)(void* cmp, float delta)) {
	registry->on_update = func;
}


//------------------------------------------------------------------------------


void rge_registry_set_on_dispose(registry_t* registry, void (*func)(void* cmp)) {
	registry->on_dispose = func;
}


//------------------------------------------------------------------------------


void* rge_component_get_from_type(const entity_t* entity, uint8_t type) {
	if(entity == NULL) {
		rge_log_error("No entity passed");
		return NULL;
	}

	for(uint8_t i = 0; i < entity->component_count; i++)
		if(entity->components[i].registry->type == type)
			return rge_component_get(entity, i);
	
	return NULL;
}


//------------------------------------------------------------------------------


registry_t* rge_registry_get_from_type(uint8_t type) {
	for(uint32_t i = 0; i < scene.registries.buffer_size; i++)
		if(scene.registries.buffer[i] != NULL)
			if(((registry_t*)(scene.registries.buffer[i]))->type == type)
				return scene.registries.buffer[i];

	return NULL;
}