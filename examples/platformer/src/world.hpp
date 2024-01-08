#ifndef _WORLD_HPP_
#define _WORLD_HPP_

#include "rge.hpp"

class player;
class level;
class collider;

class world {
public:
	world();
	~world();

	inline player* get_player() { return player_obj; }
	inline level* get_level() { return level_objs[current_level]; }
	std::vector<rge::collider*>* get_colliders();

private:
	player* player_obj;
	std::vector<level*> level_objs;
	int current_level;
	std::vector<rge::collider*> collider_buffer;
};

#endif /* _WORLD_HPP_ */