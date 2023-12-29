#include "world.hpp"
#include "player.hpp"
#include "level.hpp"
#include "collider.hpp"
#include "tile_map.hpp"

// TODO: TESTING
static std::vector<collider*> test_colliders;

world::world() {
	player_obj = new player();
	current_level = 0;
	level_objs.push_back(new level());

	// TODO: TESTING
	test_colliders.push_back(new rect_collider(rge::rect(0, 0, 100, 48)));
	test_colliders.push_back(new rect_collider(rge::rect(64, 48, 8, 16)));
}

world::~world() {

}

std::vector<collider*>* world::get_colliders() {
	collider_buffer.clear();

	/*
	std::vector<tile_collider*>* tiles = get_level()->get_area()->get_map()->get_colliders();
	for(int i = 0; i < tiles->size(); i++) {
		collider_buffer.push_back(tiles->at(i));
	}
	*/
	
	// TODO: TESTING
	for(int i = 0; i < test_colliders.size(); i++) {
		collider_buffer.push_back(test_colliders[i]);
	}

	return &collider_buffer;
}