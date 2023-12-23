#ifndef _AREA_HPP_
#define _AREA_HPP_

#include "game.hpp"

class area {
public:
	area();
	~area();

private:
	std::vector<entity*> entity_objs;
};

#endif /* _AREA_HPP_ */