#ifndef _TILE_SET_HPP_
#define _TILE_SET_HPP_

#include "rge.hpp"

struct tile {
    rge::texture::ptr texture;
    int x;
    int y;
    int width;
    int height;

	tile();
    tile(rge::texture::ptr texture);
    tile(rge::texture::ptr texture, int x, int y, int w, int h);
};

class tile_set {

public:
    tile_set();
    tile_set(int capacity);

    tile* get_tile(int i);
    void add_tile(tile t);
    
    inline int get_tile_count() { return tiles.size(); }

private:
    std::vector<tile> tiles;
};

#endif /* _TILE_SET_HPP_ */