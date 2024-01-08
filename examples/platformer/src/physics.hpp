#ifndef _PHYSICS_HPP_
#define _PHYSICS_HPP_

#include "rge.hpp"

namespace rge {
namespace physics {

    struct ray {
		vec2 origin;
		vec2 direction;
		float distance;

		ray() {
			this->origin = vec2();
			this->direction = vec2();
			this->distance = 0;
		}

		ray(vec2 origin, vec2 direction, float distance) {
			this->origin = origin;
			this->direction = direction;
			this->distance = distance;
		}
    };

    struct cast_hit {
		vec2 point;
		vec2 normal;
		float distance;
    };

	struct sweep_result {
		vec2 normal;
		float travel_percent;

		sweep_result() {
			this->normal = vec2();
			this->travel_percent = 0;
		}

		sweep_result(vec2 normal, float travel_percent) {
			this->normal = normal;
			this->travel_percent = travel_percent;
		}
	};

	// Casting (ray vs ...)
	bool cast_ray(cast_hit* out_hit, const ray& ray, const std::vector<collider*>& colliders);
	bool cast_ray(cast_hit* out_hit, const ray& ray, const rect& rect);
	bool cast_ray(cast_hit* out_hit, const ray& ray, const circle& circle);
	bool cast_ray(cast_hit* out_hit, const ray& ray, const line& line);

	// Intersection (line vs ...)
	bool intersect(cast_hit* out_hit, const line& line, const std::vector<collider*>& colliders);
	bool intersect(cast_hit* out_hit, const line& line, const rect& rect);
	bool intersect(cast_hit* out_hit, const line& line, const circle& circle);
	bool intersect(cast_hit* out_hit, const line& line1, const line& line2);

	// Overlapping (rect vs ...)
	bool overlap(const rect& rect1, const rect& rect2);

	// Overlapping (circle vs ...)
	bool overlap(const circle& circle1, const circle& circle2);

	// Sweeping (circle vs ...)
	sweep_result sweep(const circle& circle, const vec2& delta, const std::vector<collider*>& colliders);
	sweep_result sweep(const circle& circle_origin, const vec2& circle_delta, const rect& rect);
	sweep_result sweep(const circle& circle_origin, const vec2& circle_delta, const line& line);

	// Sweeping (rect vs ...)
	sweep_result sweep(const rect& rect, const vec2& delta, const std::vector<collider*>& colliders);
	sweep_result sweep(const rect& rect1_origin, const vec2& rect1_delta, const rect& rect2);
	sweep_result sweep(const rect& rect_origin, const vec2& rect_delta, const line&line);

}
}

#endif /* _PHYSICS_HPP_ */