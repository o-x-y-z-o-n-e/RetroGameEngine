#include "world/transform.h"
#include "world/scene.h"

transform_t* create_transform(entity_t* entity) {
	registry_t* registry = get_registry_of_type(TYPE_TRANSFORM);
	return (transform_t*)create_component(entity, registry);
}