#include "physics.hpp"
#include <limits>
using namespace rge::physics;

#pragma region Casting

bool rge::physics::cast_ray(cast_hit* out_hit, const ray& ray, const std::vector<collider*>& colliders) {
	rge::line line;
	line.start = ray.origin;
	line.end = line.start + ray.direction * ray.distance;
	return intersect(out_hit, line, colliders);
}

bool rge::physics::cast_ray(cast_hit* out_hit, const ray& ray, const rect& rect) {
	rge::line line;
	line.start = ray.origin;
	line.end = line.start + ray.direction * ray.distance;
	return intersect(out_hit, line, rect);
}

bool rge::physics::cast_ray(cast_hit* out_hit, const ray& ray, const circle& circle) {
	rge::line line;
	line.start = ray.origin;
	line.end = line.start + ray.direction * ray.distance;
	return intersect(out_hit, line, circle);
}

bool rge::physics::cast_ray(cast_hit* out_hit, const ray& ray, const line& line) {
	rge::line line1;
	line1.start = ray.origin;
	line1.end = line1.start + ray.direction * ray.distance;
	return intersect(out_hit, line1, line);
}

#pragma endregion

#pragma region Intersection

bool rge::physics::intersect(cast_hit* out_hit, const line& line, const std::vector<collider*>& colliders) {
	cast_hit closet;
	cast_hit current;
	bool any_hit = false;
	bool current_hit = false;

	if(colliders.size() > 0) {
		for(int i = 0; i < colliders.size(); i++) {
			switch(colliders[i]->get_shape_type()) {
				case shape::RECTANGLE:
					current_hit = intersect(&current, line, colliders[i]->get_rect());

				case shape::CIRCLE:
					current_hit = intersect(&current, line, colliders[i]->get_circle());

				case shape::LINE:
					current_hit = intersect(&current, line, colliders[i]->get_line());

				default:
					continue;
			}

			if(current_hit) {
				if(current.distance < closet.distance || !any_hit) {
					closet = current;
					any_hit = true;
				}
				current_hit = false;
			}
		}
	}

	return any_hit;
}

bool rge::physics::intersect(cast_hit* out_hit, const line& line, const rect& rect) {
	// TODO
	return false;
}

bool rge::physics::intersect(cast_hit* out_hit, const line& line, const circle& circle) {
	// TODO
	return false;
}

bool rge::physics::intersect(cast_hit* out_hit, const line& line1, const line& line2) {
	vec2 d1 = line1.end - line1.start;
	vec2 d2 = line2.end - line2.start;

	float s = (-d1.y * (line1.start.x - line2.start.x) + d1.x * (line1.start.y - line2.start.y)) / (-d2.x * d1.y + d1.x * d2.y);
	float t = (d2.x * (line1.start.y - line2.start.y) - d2.y * (line1.start.x - line2.start.x)) / (-d2.x * d1.y + d1.x * d2.y);

	if(s >= 0 && s <= 1 && t >= 0 && t <= 1) {
		vec2 r = vec2::normalize(d2);

		out_hit->point = line1.start + (d1 * t);
		out_hit->normal = vec2(-r.y, r.x); // TODO: change vec2(r.y, -r.x);
		out_hit->distance = (d1 * t).magnitude();
		return true;
	}

	return false;
}

#pragma endregion

#pragma region Overlapping

bool rge::physics::overlap(const rect& rect1, const rect& rect2) {
	return
		(rect1.get_max().x > rect2.get_min().x && rect1.get_min().x < rect2.get_max().x) &&
		(rect1.get_max().y > rect2.get_min().y && rect1.get_min().y < rect2.get_max().y);
}

bool rge::physics::overlap(const circle& circle1, const circle& circle2) {
	vec2 delta = circle2.center - circle1.center;
	float distance = delta.magnitude() - circle1.radius - circle2.radius;

	if(distance <= 0) {
		return false;
	}

	/*
	out_hit->point = circle1.center + vec2::normalize(delta) * (circle1.radius + distance);
	out_hit->normal = -vec2::normalize(delta);
	out_hit->distance = distance;
	*/

	return true;
}

#pragma endregion

#pragma region Sweeping

sweep_result rge::physics::sweep(const circle& circle, const vec2& delta, const std::vector<collider*>& colliders) {
	sweep_result closet = sweep_result(vec2(0, 0), 1.0F);
	sweep_result current;

	if(colliders.size() > 0) {
		for(int i = 0; i < colliders.size(); i++) {
			switch(colliders[i]->get_shape_type()) {
				case shape::RECTANGLE:
					current = sweep(circle, delta, colliders[i]->get_rect());

				case shape::LINE:
					current = sweep(circle, delta, colliders[i]->get_line());

				default:
					continue;
			}

			if(current.travel_percent <= closet.travel_percent) {
				closet = current;
			}
		}
	}

	return closet;
}

sweep_result rge::physics::sweep(const circle& circle, const vec2& delta, const rect& rect) {
	/*
	vec2 diff = rect.get_center() - circle.center;
	vec2 diff_clamped = vec2::clamp(diff, -rect.get_extents(), rect.get_extents());
	vec2 closet_point = rect.get_center() + diff_clamped;

	// TODO
	const int LEFT = 0;
	const int RIGHT = 1;
	const int BOTTOM = 2;
	const int TOP = 3;

	line lines[4];
	lines[LEFT] = line(vec2(rect.x, rect.y), vec2(rect.x, rect.y + rect.h));
	lines[RIGHT]  = line(vec2(rect.x + rect.w, rect.y), vec2(rect.x + rect.w, rect.y + rect.h));
	lines[BOTTOM] = line(vec2(rect.x, rect.y), vec2(rect.x + rect.w, rect.y));
	lines[TOP] = line(vec2(rect.x, rect.y + rect.h), vec2(rect.x + rect.w, rect.y + rect.h));

	sweep_result closet = sweep_result(vec2(0, 0), 1.0F);
	sweep_result current;

	for(int i = 0; i < 4; i++) {
		current = sweep(circle, delta, lines[i]);

		if(current.travel_percent < closet.travel_percent) {
			closet = current;
		}
	}
	*/

	return sweep_result(vec2(0, 0), 1.0F);
}

sweep_result rge::physics::sweep(const circle& circle, const vec2& delta, const line& line) {
	sweep_result result = sweep_result(vec2(0, 0), 1.0F);

	// TODO

	vec2 point;
	vec2 diff = circle.center - point;

	if(vec2::dot(diff, diff) > circle.radius * circle.radius) {
		return result;
	}

	float dist = diff.magnitude();
	result.travel_percent = dist / delta.magnitude();
	result.normal = diff * (1.0F / dist);
	return result;
}

sweep_result rge::physics::sweep(const rect& rect, const vec2& delta, const std::vector<collider*>& colliders) {
	sweep_result closet = sweep_result(vec2(0, 0), 1.0F);
	sweep_result current;

	if(colliders.size() > 0) {
		for(int i = 0; i < colliders.size(); i++) {
			switch(colliders[i]->get_shape_type()) {
				case shape::RECTANGLE:
					current = sweep(rect, delta, colliders[i]->get_rect());

				case shape::LINE:
					current = sweep(rect, delta, colliders[i]->get_line());

				default:
					continue;
			}

			if(current.travel_percent <= closet.travel_percent) {
				closet = current;
			}
		}
	}

	return closet;
}

sweep_result rge::physics::sweep(const rect& rect1, const vec2& delta, const rect& rect2) {
	sweep_result result;

	float x_inv_entry;
	float x_inv_exit;
	float y_inv_entry;
	float y_inv_exit;

	float x_entry;
	float x_exit;
	float y_entry;
	float y_exit;

	float t_entry;
	float t_exit;

	rect sum = rect1;
	sum.w += delta.x;
	sum.h += delta.y;
	if(delta.x < 0) sum.x -= delta.x;
	if(delta.y < 0) sum.y -= delta.y;


	if(delta.x > 0) {
		x_inv_entry = rect2.x - (rect1.x + rect1.w);
		x_inv_exit = (rect2.x + rect2.w) - rect1.x;
	} else {
		x_inv_entry = (rect2.x + rect2.w) - rect1.x;
		x_inv_exit = rect2.x - (rect1.x + rect1.w);
	}

	if(delta.y > 0) {
		y_inv_entry = rect2.y - (rect1.y + rect1.h);
		y_inv_exit = (rect2.y + rect2.h) - rect1.y;
	} else {
		y_inv_entry = (rect2.y + rect2.h) - rect1.y;
		y_inv_exit = rect2.y - (rect1.y + rect1.h);
	}

	if(delta.x == 0.0F) {
		x_entry = -std::numeric_limits<float>::infinity();
		x_exit = std::numeric_limits<float>::infinity();
	} else {
		x_entry = x_inv_entry / delta.x;
		x_exit = x_inv_exit / delta.x;
	}

	if(delta.y == 0.0F) {
		y_entry = -std::numeric_limits<float>::infinity();
		y_exit = std::numeric_limits<float>::infinity();
	} else {
		y_entry = y_inv_entry / delta.y;
		y_exit = y_inv_exit / delta.y;
	}

	t_entry = std::max(x_entry, y_entry);
	t_exit = std::min(x_exit, y_exit);

	if(t_entry > t_exit || x_entry < 0.0F && y_entry < 0.0F || x_entry > 1.0F || y_entry > 1.0F) {
		result.normal = vec2(0, 0);
		result.travel_percent = 1.0F;
	} else {
		if(x_entry > y_entry) {
			result.normal = x_inv_entry < 0.0F ? vec2(1, 0) : vec2(-1, 0);
		} else {
			result.normal = y_inv_entry < 0.0F ? vec2(0, 1) : vec2(0, -1);
		}
		result.travel_percent = t_entry;
	}

	rge::log::info("t: %f", result.travel_percent);

	//rge::log::info("x: %f, y: %f, w: %f, h: %f", rect2.x, rect2.y, rect2.w, rect2.h);

	return result;
}

sweep_result rge::physics::sweep(const rect& rect, const vec2& delta, const line& line) {
	// TODO
	return sweep_result(vec2(0, 0), 1.0F);
}

#pragma endregion