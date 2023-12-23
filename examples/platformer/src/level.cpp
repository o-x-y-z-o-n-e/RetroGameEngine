#include "level.hpp"

level::level() {
    current_area = 0;
	area_objs.push_back(new area());
}

level::~level() {

}