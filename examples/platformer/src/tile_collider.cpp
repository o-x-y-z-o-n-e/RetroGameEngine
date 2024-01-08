#include "tile_map.hpp"
#include "tile_set.hpp"
#include "tile_collider.hpp"

tile_collider::tile_collider(tile_map* map, int layer_id, int index) {
	this->map = map;
	this->layer_id = layer_id;
	this->index = index;
}

rge::rect tile_collider::get_rect() const {
	tile_layer* layer = map->get_tile_layer(layer_id);
	int tile_id = layer->grid[index];
	tile* tile = map->get_tile_registry()->get_tile(tile_id);

	rge::vec2 offset = rge::vec2(layer->offset_x, layer->offset_y);

	int x = index % layer->width;
	int y = index / layer->width;

	offset.x += x * map->tile_width;
	offset.y += (layer->height - y - 1) * map->tile_height;

	rge::rect tex_bounds = tile->collision[0];

	int t_y = tex_bounds.h - (tex_bounds.y + tex_bounds.h);
	rge::rect r = rge::rect(offset.x + tex_bounds.x, offset.y + t_y, tex_bounds.w, tex_bounds.h);

	return r;
}