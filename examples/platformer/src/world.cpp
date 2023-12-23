#include "world.hpp"

world::world() {
	player_obj = new player();
	current_level = 0;
	level_objs.push_back(new level());
}

world::~world() {

}