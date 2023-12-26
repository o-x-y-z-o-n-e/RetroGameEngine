#include "tile_map.hpp"
#include "tile_loader.hpp"
#include "game.hpp"
#include <sstream>

static bool read_data(xml_node<>* node, tile_layer* layer) {
	const char DELIM = ',';

	char* encoding = nullptr;

	if(node == nullptr)
		return false;

	if(read_attribute_str(node, "encoding", &encoding)) {
		if(!STR_EQUAL(encoding, "csv")) {
			rge::log::error("Only csv supported for tile_map layer data");
			return false;
		}
	}

	std::string str = node->value();
	std::stringstream ss = std::stringstream(str);

	int tmp_i = 0;
	std::string tmp_s;
	int t = 0;
	try {
		while(ss >> tmp_i) {
			layer->grid[t] = tmp_i - 1;
			getline(ss, tmp_s, DELIM);
			t++;
		}
	} catch(std::exception e) {
		rge::log::error("Failed to parse csv tilemap data");
		return false;
	}

	return true;
}

static bool read_layer(xml_node<>* node, tile_layer* layer, bool use_local_dimensions) {
	int width = 0;
	int height = 0;
	int offset_x = 0;
	int offset_y = 0;

	if(node == nullptr)
		return false;

	if(!read_attribute_int(node, "width", &width)) {
		rge::log::error("Failed to read width attribute");
		return false;
	}

	if(!read_attribute_int(node, "height", &height)) {
		rge::log::error("Failed to read height attribute");
		return false;
	}

	read_attribute_int(node, "offsetx", &offset_x);
	read_attribute_int(node, "offsety", &offset_y);

	if(use_local_dimensions) {
		layer->width = width;
		layer->height = height;
	}

	layer->offset_x = offset_x;
	layer->offset_y = -offset_y; // NOTE: Tiled has flipped y dimension.
	layer->grid = new int[layer->width * layer->height];

	xml_node<>* data_node = node->first_node("data");
	if(!read_data(data_node, layer)) {
		rge::log::error("Failed to to read <data> node");
		return false;
	}

	return true;
}

static bool read_tile_set(xml_node<>* node, tile_set** set) {
	char* path;

	if(node == nullptr)
		return false;

	if(!read_attribute_str(node, "source", &path)) {
		rge::log::error("Failed to read source attribute");
		return false;
	}

	// TODO
	*set = nullptr;

	return true;
}

static bool read_map(xml_node<>* node, tile_map** map) {
	char* orientation = nullptr;
	int map_width = 1;
	int map_height = 1;
	bool infinite = false;
	int tile_width = 1;
	int tile_height = 1;
	tile_set* set = nullptr;

	if(node == nullptr)
		return false;

	if(read_attribute_str(node, "orientation", &orientation)) {
		if(!STR_EQUAL(orientation, "orthogonal")) {
			rge::log::error("tile_map doesn't support grid layouts other than orthogonal!");
			return false;
		}
	}

	if(!read_attribute_int(node, "width", &map_width)) {
		rge::log::error("Failed to read width attribute");
		return false;
	}

	if(!read_attribute_int(node, "height", &map_height)) {
		rge::log::error("Failed to read height attribute");
		return false;
	}

	if(read_attribute_bool(node, "infinite", &infinite)) {
		if(infinite) {
			rge::log::error("infinite tile_map not supported");
			return false;
		}
	}

	if(!read_attribute_int(node, "tilewidth", &tile_width)) {
		rge::log::error("failed to read tilewidth attribute");
		return false;
	}

	if(!read_attribute_int(node, "tileheight", &tile_height)) {
		rge::log::error("Failed to read tileheight attribute");
		return false;
	}

	if(tile_width < 1 || tile_height < 1) {
		rge::log::error("tilewidth & tileheight attributes must not be less than 1");
		return false;
	}

	xml_node<>* tile_set_node = node->first_node("tileset");
	if(!read_tile_set(tile_set_node, &set)) {
		rge::log::error("<tileset> node not found");
		return false;
	}

	*map = new tile_map(map_width, map_height, tile_width, tile_height);
	(*map)->set_tile_registry(set);

	
	xml_node<>* layer_node = node->first_node("layer");
	while(layer_node) {
		tile_layer layer;
		layer.width = map_width;
		layer.height = map_height;
		if(!read_layer(layer_node, &layer, infinite)) {
			rge::log::error("Failed to read <layer> node");
			return false;
		}

		(*map)->add_tile_layer(layer);

		layer_node = layer_node->next_sibling("layer");
	}

	return true;
}

static tile_map* read(char* text) {
	tile_map* map = nullptr;
	xml_document<>* doc = new xml_document<>();

	try {
		doc->parse<parse_no_utf8>(text);
	} catch(const parse_error& e) {
		rge::log::error("Failed to parse xml: %s", e.what());
		goto error;
	}

	xml_node<>* map_node = doc->first_node("map");
	if(map_node == nullptr) {
		rge::log::error("<map> node not found");
		goto error;
	}

	if(!read_map(map_node, &map)) {
		rge::log::error("Failed to read <map> node");
		goto error;
	}

	delete doc;
	return map;

error:
	delete doc;
	return nullptr;
}

tile_map* tile_map::load(const std::string& file_name) {
	try {
		file<> file(file_name.c_str());
		return read(file.data());
	} catch(std::exception e) {
		rge::log::error("Failed to load tile map: %s", file_name.c_str());
		return nullptr;
	}
}

tile_map::tile_map(int map_width, int map_height, int tile_width, int tile_height) {
    this->map_width =  map_width;
    this->map_height = map_height;
	this->tile_width = tile_width;
	this->tile_height = tile_height;
    
    registry = nullptr;
}

tile_map::~tile_map() {
	for(int i = 0; i < layers.size(); i++) {
		delete[] layers[i].grid;
	}
}

void tile_map::draw_layer(int i) {
	if(!registry) return;
	if(!registry->get_sheet()) return;

	int j = -1;
	for(int h = 0; h < map_width; h++) {
		for(int v = 0; v < map_height; v++) {
			j = layers[i].grid[v * map_width + h];
			if(j >= 0) {
				tile* t = registry->get_tile(j);

				game::get_renderer()->draw_tile(
					*registry->get_sheet(),
					(layers.size() - 1) - i + 1,
					rge::vec2(layers[i].offset_x, layers[i].offset_y),
					tile_width,
					tile_height,
					h,
					map_height - v,
					t->x,
					t->y,
					t->width,
					t->height
				);
			}
		}
	}
}

void tile_map::draw() {
	for(int i = 0; i < layers.size(); i++) {
		draw_layer(i);
	}
}

void tile_map::set_tile_registry(tile_set* set) {
    registry = set;
}

void tile_map::add_tile_layer(tile_layer& layer) {
	layers.push_back(layer);
}