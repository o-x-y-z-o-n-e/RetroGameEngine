#ifndef _COLLIDER_HPP_
#define _COLLIDER_HPP_

#include "rge.hpp"

class tile_map;
class tile_layer;

class collider {

public:
	virtual rge::rect get_bounds() const;

};

class rect_collider : public collider {
public:
	rge::rect get_bounds() const override {
		rge::vec2 position = parent->get_global_position();
		return rge::rect(position.x + shape.x, position.y + shape.y, shape.w, shape.h);
	};

private:
	rge::transform::ptr parent;
	rge::rect shape;

};

class tile_collider : public collider {
public:
	tile_collider(tile_map* map, int layer_id, int index);

	rge::rect get_bounds() const override;

private:
	tile_map* map;
	int layer_id;
	int index;
};

#endif /* _COLLIDER_HPP_ */