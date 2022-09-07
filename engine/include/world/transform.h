#ifndef TRANSFORM_T
#define TRANSFORM_T

#include <stdint.h>
#include "util/types.h"

#define TYPE_TRANSFORM 0

transform_t* create_transform(entity_t* entity);
point_t float_to_point(float x, float y);

#endif