#ifndef _LASER_HPP_
#define _LASER_HPP_

#include "rge.hpp"

class laser {
public:
	typedef std::pair<laser*, bool> entry;
	typedef std::vector<entry> table;

public:
	laser();
	void reset();
	void update(float delta_time);
	void draw();
	void set_position(rge::vec2 p);

	static laser* create();
	static void destroy(laser* ins);
	static void destroy_all();
	static void update_all(float delta_time);
	static void draw_all();

private:
	rge::transform::ptr transform;
	rge::sprite::ptr sprite;
	static table pool;
};

#endif /* _LASER_HPP_ */