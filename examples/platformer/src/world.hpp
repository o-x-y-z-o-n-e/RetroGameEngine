#ifndef _WORLD_HPP_
#define _WORLD_HPP_

#include "game.hpp"

class world {
public:
	world();
	~world();
	inline player* get_player() { return player_obj; }

private:
	player* player_obj;
	std::vector<level*> level_objs;

};

#endif /* _WORLD_HPP_ */