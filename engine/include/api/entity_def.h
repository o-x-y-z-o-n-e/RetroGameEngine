#include <stdint.h>
#include <stdbool.h>
typedef entity_t entity_t;
typedef registry_t registry_t;

// Entity functions.
entity_t* create_entity();
void free_entity(entity_t* entity);

// Inheritence functions.
entity_t* get_child(const entity_t* entity, uint32_t index);
uint32_t get_child_count(const entity_t* entity);
uint32_t get_child_index(const entity_t* entity, const entity_t* child);
bool add_child(entity_t* entity, entity_t* child);
bool remove_child(entity_t* entity, entity_t* child);
bool set_parent(entity_t* entity, entity_t* parent);

// Component functions.
void* create_component(entity_t* entity, registry_t* registry);
void remove_component(entity_t* entity, uint8_t index);
void* get_component(const entity_t* entity, uint8_t index);
uint8_t get_component_count(const entity_t* entity);
uint8_t get_component_index(const entity_t* entity, void* component);
void* get_component_of_type(const entity_t* entity, uint8_t type);