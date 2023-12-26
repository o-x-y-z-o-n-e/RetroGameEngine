#include "area.hpp"

area::area() {
	tile_map_obj = tile_map::load("res/tilemaps/test_level.tmx");
	if(tile_map_obj) {
		tile_map_obj->set_tile_registry(new tile_set(rge::texture::load("res/tilesets/paper.png"), 8, 8));
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