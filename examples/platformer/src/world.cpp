#include "world.hpp"

world::world() {
	player_obj = new player();
	current_level = 0;
}

world::~world() {

}

player* world::get_player() {
	return player_obj;
}

level* world::get_level() {
	return level_objs[current_level];
}