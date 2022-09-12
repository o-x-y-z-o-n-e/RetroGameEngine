#include "components/transform.h"
#include "core/scene.h"


//------------------------------------------------------------------------------


static int32_t round(float f) {
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
		round(x),
		round(y)
	};
}