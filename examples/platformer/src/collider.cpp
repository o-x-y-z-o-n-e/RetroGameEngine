#include "collider.hpp"
#include "tile_map.hpp"
#include "tile_set.hpp"

rge::rect collider::get_bounds() const {
	return rge::rect();
}

tile_collider::tile_collider(tile_map* map, int layer_id, int index) {
	this->map = map;
	this->layer_id = layer_id;
	this->index = index;
};

rge::rect tile_collider::get_bounds() const {
	tile_layer* layer = map->get_tile_layer(layer_id);
	int tile_id = layer->grid[index];
	tile* tile = map->get_tile_registry()->get_tile(tile_id);

	rge::vec2 offset = rge::vec2(layer->offset_x, layer->offset_y);

	int x = index % layer->width;
	int y = index / layer->height;

	offset.x += x * map->tile_width;
	offset.y += y * map->tile_height;

	rge::rect tex_bounds = tile->collision[0];

	float j = (map->tile_height - tex_bounds.y) - tex_bounds.h;
	return rge::rect(offset.x + tex_bounds.x, offset.y + j, tex_bounds.w, tex_bounds.h);
};