#ifndef _TILE_COLLIDER_HPP_
#define _TILE_COLLIDER_HPP_

#include "rge.hpp"

class tile_map;
class tile_layer;

class tile_collider : public rge::collider {
public:
	tile_collider(tile_map* map, int layer_id, int index);

	rge::shape get_shape_type() const override { return rge::shape::RECTANGLE; };
	rge::rect get_rect() const override;

private:
	tile_map* map;
	int layer_id;
	int index;
};

#endif /* _TILE_COLLIDER_HPP_ */