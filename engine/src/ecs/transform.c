#include "ecs/transform.h"
#include "ecs/scene.h"


//------------------------------------------------------------------------------


static int32_t round_f(float f) {
	float i = (int)f;
	float l = f - i;

	if(l > 0.5F)
		i++;
	else if(l < -0.5F)
		i--;

	return (int32_t)i;
}


//------------------------------------------------------------------------------


transform_t* rge_transform_create(entity_t* entity) {
	registry_t* registry = rge_registry_get_from_type(TYPE_TRANSFORM);
	return (transform_t*)rge_component_create(entity, registry);
}


//------------------------------------------------------------------------------


point_t rge_float_to_point(float x, float y) {
	return (point_t) {
		round_f(x),
		round_f(y)
	};
}


//------------------------------------------------------------------------------


point_t rge_transform_get_global(const entity_t* entity) {
	point_t offset = { 0, 0 };

	transform_t* t = rge_component_get_from_type(entity, TYPE_TRANSFORM);
	if(t == NULL)
		return offset;

	if(entity->parent != NULL)
		offset = rge_transform_get_global(entity->parent);

	offset.x += t->location.x;
	offset.y += t->location.y;

	return offset;
}


//------------------------------------------------------------------------------


void rge_transform_set_global(entity_t* entity, point_t location) {
	transform_t* t = rge_component_get_from_type(entity, TYPE_TRANSFORM);
	if(t == NULL)
		return;

	point_t offset = { 0, 0 };

	if(entity->parent != NULL)
		offset = rge_transform_get_global(entity->parent);
	
	t->location.x = location.x - offset.x;
	t->location.y = location.y - offset.y;
}