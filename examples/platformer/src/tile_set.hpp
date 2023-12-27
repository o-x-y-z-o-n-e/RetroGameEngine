#ifndef _TILE_SET_HPP_
#define _TILE_SET_HPP_

#include "rge.hpp"

struct tile {
    int x;
    int y;
    int width;
    int height;
	std::vector<rge::rect> collision;
};

class tile_set {

public:
    tile_set(rge::texture::ptr texture);
	tile_set(rge::texture::ptr texture, int tile_width, int tile_height);

    static tile_set* load(const std::string& file_name);

    tile* get_tile(int i);
    void add_tile(const tile& t);
    
    inline int get_tile_count() const { return tiles.size(); }
    inline rge::texture::ptr get_sheet() const { return sheet; }

private:
    std::vector<tile> tiles;
    rge::texture::ptr sheet;
};

#endif /* _TILE_SET_HPP_ */