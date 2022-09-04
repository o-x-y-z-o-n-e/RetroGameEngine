#include "world/transform.h"
#include "world/scene.h"


//------------------------------------------------------------------------------


static int32_t round(float f) {
	float i = (int)f;
	float l = f - i;

	if(l > 0.5F)
		i++;
	else if(l < -0.5F)
		i--;

	return i;
}


//------------------------------------------------------------------------------


transform_t* create_transform(entity_t* entity) {
	registry_t* registry = get_registry_of_type(TYPE_TRANSFORM);
	return (transform_t*)create_component(entity, registry);
}


//------------------------------------------------------------------------------


point_t float_to_point(float x, float y) {
	return (point_t) {
		round(x),
		round(y)
	};
}