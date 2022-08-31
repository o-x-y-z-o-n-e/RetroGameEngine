#ifndef TRANSFORM_T
#define TRANSFORM_T

#include <stdint.h>
#include "util/types.h"

#define TYPE_TRANSFORM 0

typedef struct entity_t entity_t;

typedef struct transform_t {
	point_t location;
} transform_t;

transform_t* create_transform(entity_t* entity);

#endif