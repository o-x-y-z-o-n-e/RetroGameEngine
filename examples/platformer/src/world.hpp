#ifndef _WORLD_HPP_
#define _WORLD_HPP_

#include "game.hpp"

class player;
class level;

class world {
public:
	world();
	~world();
	player* get_player();
	level* get_level();

private:
	player* player_obj;
	std::vector<level*> level_objs;
	int current_level;
};

#endif /* _WORLD_HPP_ */