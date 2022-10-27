#include "core/physics.h"

#include <math.h>


//------------------------------------------------------------------------------


bool rge_physics_ray_intersects_ray(ray_t ray1, ray_t ray2) {
	// TODO: Implement line segment intersection.
	return false;
}


//------------------------------------------------------------------------------


bool rge_physics_ray_intersects_area(ray_t ray, rect_t area) {
	point_t min = area.origin;
	point_t max = { min.x + area.width, min.y + area.height };

	float t_min_x = (min.x - ray.origin.x) / ray.direction.x;
	float t_max_x = (max.x - ray.origin.x) / ray.direction.x;

	float t_min_y = (min.y - ray.origin.y) / ray.direction.y;
	float t_max_y = (max.y - ray.origin.y) / ray.direction.y;

	float t_min = fmaxf(fminf(t_min_x, t_max_x), fminf(t_min_y, t_max_y));
	float t_max = fminf(fmaxf(t_min_x, t_max_x), fmaxf(t_min_y, t_max_y));

	// If ray intersects but AABB is 'behind' the ray origin.
	if(t_max < 0)
		return false;

	// No intersection.
	if(t_max < t_min)
		return false;

	float t = fminf(t_min, t_max);

	// If the first intersection is further than ray distance.
	if(t > ray.max_distance)
		return false;

	// Else, there was an intersection.
	return true;
}


//------------------------------------------------------------------------------


bool rge_physics_area_overlaps_area(rect_t area1, rect_t area2) {
	bool h = area1.x < area2.x + area2.width && area1.x + area1.width > area2.x;
	bool v = area1.y < area2.y + area2.height && area1.y + area1.height > area2.y;
	return h && v;
}