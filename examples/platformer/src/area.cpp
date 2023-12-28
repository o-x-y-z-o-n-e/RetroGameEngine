#include "area.hpp"
#include "tile_map.hpp"
#include "tile_set.hpp"
#include "entity.hpp"

area::area() {
	tile_map_obj = tile_map::load("res/tilemaps/test_level.tmx");
	if(tile_map_obj) {
		tile_set* set = new tile_set(rge::texture::load("res/tilesets/paper.png"), 8, 8);

		set->get_tile(112)->collision.push_back(rge::rect(0, 0, 8, 2));
		set->get_tile(113)->collision.push_back(rge::rect(0, 0, 8, 2));
		set->get_tile(128)->collision.push_back(rge::rect(0, 0, 8, 8));
		set->get_tile(146)->collision.push_back(rge::rect(0, 0, 3, 8));

		tile_map_obj->set_tile_registry(set);
		tile_map_obj->create_colliders();
	}
}

area::~area() {

}

void area::draw() {
	tile_map_obj->draw();

    for(int i = 0; i < entity_objs.size(); i++) {
        entity_objs[i]->draw();
    }
}