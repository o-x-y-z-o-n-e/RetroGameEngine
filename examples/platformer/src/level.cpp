#include "level.hpp"

level::level() {
    current_area = 0;
}

level::~level() {

}

area* level::get_area() {
	return area_objs[current_area];
}