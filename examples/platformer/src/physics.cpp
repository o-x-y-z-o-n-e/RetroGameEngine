#include "physics.hpp"
using namespace rge::physics;

bool rge::physics::cast_ray(cast_hit* out_hit, const ray& ray, const rect& rect) {
	line line;
	line.start = ray.origin;
	line.end = line.start + ray.direction * ray.distance;
	return intersect(out_hit, line, rect);
}

bool rge::physics::cast_ray(cast_hit* out_hit, const ray& ray, const circle& circle) {
	line line;
	line.start = ray.origin;
	line.end = line.start + ray.direction * ray.distance;
	return intersect(out_hit, line, circle);
}

bool rge::physics::cast_ray(cast_hit* out_hit, const ray& ray, const line& line) {
	physics::line line1;
	line1.start = ray.origin;
	line1.end = line1.start + ray.direction * ray.distance;
	return intersect(out_hit, line1, line);
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

bool rge::physics::overlap(cast_hit* out_hit, const circle& circle, const rect& rect) {
	// TODO
	return false;
}

bool rge::physics::overlap(cast_hit* out_hit, const circle& circle1, const circle& circle2) {
	vec2 delta = circle2.center - circle1.center;
	float distance = delta.magnitude() - circle1.radius - circle2.radius;

	if(distance <= 0) {
		return false;
	}

	out_hit->point = circle1.center + vec2::normalize(delta) * (circle1.radius + distance);
	out_hit->normal = -vec2::normalize(delta);
	out_hit->distance = distance;

	return true;
}

bool rge::physics::overlap(cast_hit* out_hit, const circle& circle, const line& line) {
	// TODO
	return false;
}

bool rge::physics::overlap(cast_hit* out_hit, const rect& rect1, const rect& rect2) {
	return
		(rect1.get_max().x > rect2.get_min().x && rect1.get_min().x < rect2.get_max().x) &&
		(rect1.get_max().y > rect2.get_min().y && rect1.get_min().y < rect2.get_max().y);
}

bool rge::physics::overlap(cast_hit* out_hit, const rect& rect, const circle& circle) {
	// TODO
	return false;
}

bool rge::physics::overlap(cast_hit* out_hit, const rect& rect, const line& line) {
	// TODO
	return false;
}

bool rge::physics::sweep(cast_hit* out_hit, const circle& circle_origin, const vec2& circle_delta, const rect& rect) {
	// TODO
	return false;
}

bool rge::physics::sweep(cast_hit* out_hit, const circle& circle_origin, const vec2& circle_delta, const line& line) {
	// TODO
	return false;
}

bool rge::physics::sweep(cast_hit* out_hit, const rect& rect1_origin, const vec2& rect1_delta, const rect& rect2) {
	// TODO
	return false;
}

bool rge::physics::sweep(cast_hit* out_hit, const rect& rect_origin, const vec2& rect_delta, const line& line) {
	// TODO
	return false;
}

//--------------------------

bool rge::physics::cast_ray(cast_hit* out_hit, const ray& ray) {
	// TODO
	return false;
}

bool rge::physics::intersect(cast_hit* out_hit, const line& line) {
	// TODO
	return false;
}

bool rge::physics::overlap(cast_hit* out_hit, const circle& circle) {
	// TODO
	return false;
}

bool rge::physics::overlap(cast_hit* out_hit, const rect& rect) {
	// TODO
	return false;
}

bool rge::physics::sweep(cast_hit* out_hit, const circle& circle_origin, const vec2& circle_delta) {
	// TODO
	return false;
}

bool rge::physics::sweep(cast_hit* out_hit, const rect& rect_origin, const vec2& rect_delta) {
	// TODO
	return false;
}