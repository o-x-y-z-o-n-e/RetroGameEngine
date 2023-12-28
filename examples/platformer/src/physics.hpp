#ifndef _PHYSICS_HPP_
#define _PHYSICS_HPP_

#include "rge.hpp"
#include "collider.hpp"

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

	struct line {
		vec2 start;
		vec2 end;

		line() {
			this->start = vec2();
			this->end = vec2();
		}

		line(vec2 start, vec2 end) {
			this->start = start;
			this->end = end;
		}
	};

	struct circle {
		vec2 center;
		float radius;

		circle() {
			this->center = vec2();
			this->radius = 0;
		}

		circle(vec2 center, float radius) {
			this->center = center;
			this->radius = radius;
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

	// Casting
	bool cast_ray(cast_hit* out_hit, const ray& ray);

	bool cast_ray(cast_hit* out_hit, const ray& ray, const rect& rect);
	bool cast_ray(cast_hit* out_hit, const ray& ray, const circle& circle);
	bool cast_ray(cast_hit* out_hit, const ray& ray, const line& line);

	// Intersection
	bool intersect(cast_hit* out_hit, const line& line);

	bool intersect(cast_hit* out_hit, const line& line, const rect& rect);
	bool intersect(cast_hit* out_hit, const line& line, const circle& circle);
	bool intersect(cast_hit* out_hit, const line& line1, const line& line2);

	// Overlapping
	bool overlap(cast_hit* out_hit, const circle& circle);
	bool overlap(cast_hit* out_hit, const rect& rect);

	bool overlap(cast_hit* out_hit, const circle& circle, const rect& rect);
	bool overlap(cast_hit* out_hit, const circle& circle1, const circle& circle2);
	bool overlap(cast_hit* out_hit, const circle& circle, const line& line);

	bool overlap(cast_hit* out_hit, const rect& rect1, const rect& rect2);
	bool overlap(cast_hit* out_hit, const rect& rect, const circle& circle);
	bool overlap(cast_hit* out_hit, const rect& rect, const line& line);

	// Sweeping
	sweep_result sweep(const circle& circle_origin, const vec2& circle_delta);
	sweep_result sweep(const rect& rect1, const vec2& delta, const std::vector<collider*>& colliders);

	sweep_result sweep(const circle& circle_origin, const vec2& circle_delta, const rect& rect);
	sweep_result sweep(const circle& circle_origin, const vec2& circle_delta, const line& line);

	sweep_result sweep(const rect& rect1_origin, const vec2& rect1_delta, const rect& rect2);
	sweep_result sweep(const rect& rect_origin, const vec2& rect_delta, const line&line);

}

}

#endif /* _PHYSICS_HPP_ */