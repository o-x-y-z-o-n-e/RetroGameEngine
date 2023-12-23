#ifndef _TILE_MAP_HPP_
#define _TILE_MAP_HPP_

#include "game.hpp"

class tile_set;

class tile_map {
public:
    tile_map(int width, int height);
    ~tile_map();
    
    void draw();
    void set_tile_registry(tile_set* set);

public:
    inline int get_width() { return width; }
    inline int get_height() { return height; }

public:
    int x;
    int y;
    int layer;
    int tile_size;

private:
    tile_set* registry;
    int* grid;
    int width;
    int height;
};

#endif /* _TILE_MAP_HPP_ */