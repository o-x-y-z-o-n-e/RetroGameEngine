#ifndef _WORLD_HPP_
#define _WORLD_HPP_

#include "rge.hpp"
#include "player.hpp"
#include "level.hpp"

class world {
public:
	world();
	~world();

	inline player* get_player() { return player_obj; }
	inline level* get_level() { return level_objs[current_level]; }

private:
	player* player_obj;
	std::vector<level*> level_objs;
	int current_level;
};

#endif /* _WORLD_HPP_ */