#ifndef _LEVEL_HPP_
#define _LEVEL_HPP_

#include "game.hpp"

class level {
public:
	level();
	~level();

private:
	std::vector<area*> area_objs;
};

#endif /* _LEVEL_HPP_ */