#include "area.hpp"

area::area() {

}

area::~area() {

}

void area::draw() {
    for(int i = 0; i < tile_map_objs.size(); i++) {
        tile_map_objs[i]->draw();
    }

    for(int i = 0; i < entity_objs.size(); i++) {
        entity_objs[i]->draw();
    }
}