#include "world.hpp"
#include "player.hpp"
#include "level.hpp"
#include "collider.hpp"
#include "tile_map.hpp"

world::world() {
	player_obj = new player();
	current_level = 0;
	level_objs.push_back(new level());
}

world::~world() {

}

std::vector<collider*>* world::get_colliders() {
	collider_buffer.clear();

	std::vector<tile_collider*> tiles = *get_level()->get_area()->get_map()->get_colliders();

	tile_collider* t;
	for(int i = 0; i < tiles.size(); i++) {
		t = tiles[i];
		collider_buffer.push_back(t);
	}

	return &collider_buffer;
}