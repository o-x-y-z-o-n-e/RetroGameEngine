#ifndef _ASTEROID_HPP_
#define _ASTEROID_HPP_

#include "rge.hpp"

class asteroid {
public:
	typedef std::pair<asteroid*, bool> asteroid_entry;
	typedef std::vector<asteroid_entry> asteroid_table;

public:
	asteroid();
	~asteroid();
	void reset();
	void update(float delta_time);
	void draw();

	void gen_starting_params();

	static asteroid* create();
	static void destroy(asteroid* ins);
	static void update_all(float delta_time);
	static void draw_all();

private:
	float radius;
	rge::vec2 velocity;
	float rotation;
	float turn;
	rge::transform::ptr transform;
	rge::sprite::ptr sprite;
	static asteroid_table pool;
};

#endif /* _ASTEROID_HPP_ */