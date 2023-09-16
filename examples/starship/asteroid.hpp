#ifndef _ASTEROID_HPP_
#define _ASTEROID_HPP_

#include "rge.hpp"

class asteroid {
public:
	typedef std::pair<asteroid*, bool> entry;
	typedef std::vector<entry> table;

public:
	asteroid();
	~asteroid();
	void reset();
	void update(float delta_time);
	void draw();

	void gen_starting_params();

	static asteroid* create();
	static void destroy(asteroid* ins);
	static void destroy_all();
	static void update_all(float delta_time);
	static void draw_all();

private:
	float radius;
	rge::vec2 velocity;
	float rotation;
	float turn;
	rge::transform::ptr transform;
	rge::sprite::ptr sprite;
	static table pool;
};

#endif /* _ASTEROID_HPP_ */