#ifndef _LEVEL_HPP_
#define _LEVEL_HPP_

#include "game.hpp"

class area;

class level {
public:
	level();
	~level();

	area* get_area();

private:
	std::vector<area*> area_objs;
	int current_area;
};

#endif /* _LEVEL_HPP_ */