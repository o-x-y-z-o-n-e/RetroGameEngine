#ifndef RGE_PHYSICS_H
#define RGE_PHYSICS_H

#include "api/rge.h"

typedef struct vector_t {
	float x, y;
} vector_t;

typedef struct ray_t {
	vector_t origin;
	vector_t direction;
	float max_distance;
} ray_t;

bool rge_physics_ray_intersects_ray(ray_t ray1, ray_t ray2);
bool rge_physics_ray_intersects_area(ray_t ray, rect_t area);
bool rge_physics_area_overlaps_area(rect_t area1, rect_t area2);

#endif