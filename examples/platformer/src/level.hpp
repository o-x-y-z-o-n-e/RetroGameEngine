#ifndef _LEVEL_HPP_
#define _LEVEL_HPP_

#include "rge.hpp"
#include "area.hpp"

class level {
public:
	level();
	~level();

	inline area* get_area() { return area_objs[current_area]; }

private:
	std::vector<area*> area_objs;
	int current_area;
};

#endif /* _LEVEL_HPP_ */