#include "tile_set.hpp"

tile::tile() {
	texture = nullptr;
	x = 0;
	y = 0;
	width = 1;
	height = 1;
}

tile::tile(rge::texture::ptr texture) {
    this->texture = texture;
    x = 0;
    y = 0;
    width = texture->get_width();
    height = texture->get_height();
}

tile::tile(rge::texture::ptr texture, int x, int y, int w, int h) {
    this->texture = texture;
    if(x < 0)
        x = 0;
    if(x > texture->get_width() - 1)
        x = texture->get_width() - 1;
    if(y < 0)
        y = 0;
    if(y > texture->get_height() - 1)
        y = texture->get_height() - 1;
    if(width < 1)
        width = 1;
    if(width > texture->get_width() - x)
        width = texture->get_width() - x;
    if(height < 1)
        height = 1;
    if(height > texture->get_height() - y)
        height = texture->get_height() - y;
    this->x = x; 
    this->y = y;
    this->width = w;
    this->height = h;
}

tile_set::tile_set() {

}

tile_set::tile_set(int capacity) : tiles(std::vector<tile>(capacity)) {
    
}

tile* tile_set::get_tile(int i) {
    if(i < 0 || i >= tiles.size())
        return nullptr;
    else
        return &tiles[i];
}

void tile_set::add_tile(tile t) {
    tiles.push_back(t);
}