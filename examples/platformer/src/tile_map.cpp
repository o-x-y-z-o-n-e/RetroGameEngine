#include "tile_map.hpp"
#include "game.hpp"

tile_map::tile_map(int width, int height) {
    this->width = width;
    this->height = height;

    x = 0;
    y = 0;
    layer = 0;
    tile_size = 1;

    grid = new int[width * height];
    registry = nullptr;
}

tile_map::~tile_map() {
    delete[] grid;
}

void tile_map::draw() {
    rge::renderer* renderer = game::get_renderer();

    int i = -1;
    for(int h = 0; h < width; h++) {
        for(int v = 0; v < height; v++) {
            i = grid[v * width + h];
            if(i >= 0) {
                tile* t = registry->get_tile(i);
                
                renderer->draw_tile(
                    *t->texture,
                    x + h,
                    y + v,
                    layer,
                    tile_size,
                    t->x,
                    t->y,
                    t->width,
                    t->height
                );
            }
        }
    }
}

void tile_map::set_tile_registry(tile_set* set) {
    registry = set;
}