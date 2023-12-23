#ifndef _AREA_HPP_
#define _AREA_HPP_

#include "game.hpp"

class tile_map;
class entity;

class area {
public:
	area();
	~area();

	void draw();

private:
	std::vector<tile_map*> tile_map_objs;
	std::vector<entity*> entity_objs;
};

#endif /* _AREA_HPP_ */