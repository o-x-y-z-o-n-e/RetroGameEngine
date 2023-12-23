#ifndef _AREA_HPP_
#define _AREA_HPP_

#include "rge.hpp"
#include "tile_map.hpp"
#include "entity.hpp"

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