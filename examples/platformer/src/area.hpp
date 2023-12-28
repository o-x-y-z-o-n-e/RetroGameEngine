#ifndef _AREA_HPP_
#define _AREA_HPP_

#include "rge.hpp"

class tile_map;
class entity;

class area {
public:
	area();
	~area();

	void draw();

	inline tile_map* get_map() { return tile_map_obj; }

private:
	tile_map* tile_map_obj;
	std::vector<entity*> entity_objs;
};

#endif /* _AREA_HPP_ */