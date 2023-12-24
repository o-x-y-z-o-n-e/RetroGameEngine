#include "area.hpp"

area::area() {
	tile_map_obj = tile_map::load("res/tilemaps/test_level.tmx");
	if(!tile_map_obj) {
		rge::log::error("no");
	}
}

area::~area() {

}

void area::draw() {
	//tile_map_obj->draw();

    for(int i = 0; i < entity_objs.size(); i++) {
        entity_objs[i]->draw();
    }
}