#include "tile_map.hpp"
#include "game.hpp"
#include "rapidxml/rapidxml.hpp"

using namespace rapidxml;

#define STR_EQUAL(A, B) (strcmp(A, B) == 0)

static bool read_attribute_int(xml_node<>* node, const char* name, int* value) {
	if(node == nullptr)
		return false;

	xml_attribute<>* attribute = node->first_attribute(name);
	if(attribute == nullptr)
		return false;

	try {
		*value = std::stoi(attribute->value());
		return true;
	} catch(std::exception e) {
		return false;
	}
}

static bool read_attribute_float(xml_node<>* node, const char* name, float* value) {
	if(node == nullptr)
		return false;

	xml_attribute<>* attribute = node->first_attribute(name);
	if(attribute == nullptr)
		return false;

	try {
		*value = std::stof(attribute->value());
		return true;
	} catch(std::exception e) {
		return false;
	}
}

static bool read_attribute_str(xml_node<>* node, const char* name, char** str) {
	if(node == nullptr)
		return false;

	xml_attribute<>* attribute = node->first_attribute(name);
	if(attribute == nullptr)
		return false;

	*str = attribute->value();
	return true;
}

static bool read_attribute_bool(xml_node<>* node, const char* name, bool* value) {
	if(node == nullptr)
		return false;

	xml_attribute<>* attribute = node->first_attribute(name);
	if(attribute == nullptr)
		return false;

	if(
		STR_EQUAL(attribute->value(), "true") ||
		STR_EQUAL(attribute->value(), "TRUE") ||
		STR_EQUAL(attribute->value(), "True") ||
		STR_EQUAL(attribute->value(), "1")
	) {
		*value = true;
		return true;
	} else if(
		STR_EQUAL(attribute->value(), "false") ||
		STR_EQUAL(attribute->value(), "FALSE") ||
		STR_EQUAL(attribute->value(), "False") ||
		STR_EQUAL(attribute->value(), "0")
	) {
		*value = false;
		return true;
	} else {
		return false;
	}
}

static bool read_data(xml_node<>* node, tile_layer* layer) {
	char* encoding = nullptr;

	if(node == nullptr)
		return false;

	if(read_attribute_str(node, "encoding", &encoding)) {
		if(!STR_EQUAL(encoding, "csv")) {
			rge::log::error("tile_map doesn't support grid layouts other than orthogonal!");
			return false;
		}
	}

	// TODO
	rge::log::info("csv: %s", node->value());

	return true;
}

static bool read_layer(xml_node<>* node, tile_layer* layer, bool use_local_dimensions) {
	char* name = nullptr;
	int id = 0;
	int width = 0;
	int height = 0;

	if(node == nullptr)
		return false;

	/*
	if(!read_attribute_str(node, "name", &name)) {
		rge::log::error("TODO: Error! tile_map.cpp");
		return false;
	}

	if(!read_attribute_int(node, "id", &id)) {
		rge::log::error("TODO: Error! tile_map.cpp");
		return false;
	}
	*/

	if(!read_attribute_int(node, "width", &width)) {
		rge::log::error("TODO: Error! tile_map.cpp");
		return false;
	}

	if(!read_attribute_int(node, "height", &height)) {
		rge::log::error("TODO: Error! tile_map.cpp");
		return false;
	}

	*layer = tile_layer();
	if(use_local_dimensions) {
		layer->width = width;
		layer->height = height;
	}

	layer->grid = new int[layer->width * layer->height];

	xml_node<>* data_node = node->first_node("data");
	if(!read_data(data_node, layer)) {
		rge::log::error("TODO: Error! tile_map.cpp");
		return false;
	}

	return true;
}

static bool read_tile_set(xml_node<>* node, tile_set** set) {
	char* path;

	if(node == nullptr)
		return false;

	if(!read_attribute_str(node, "source", &path)) {
		rge::log::error("TODO: Error! tile_map.cpp");
		return false;
	}

	// TODO
	*set = nullptr;
	return true;
}

static bool read_map(xml_node<>* node, tile_map** map) {
	char* orientation = nullptr;
	int width = 1;
	int height = 1;
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

	if(!read_attribute_int(node, "width", &width)) {
		rge::log::error("TODO: Error! tile_map.cpp");
		return false;
	}

	if(!read_attribute_int(node, "height", &height)) {
		rge::log::error("TODO: Error! tile_map.cpp");
		return false;
	}

	if(read_attribute_bool(node, "infinite", &infinite)) {
		if(infinite) {
			rge::log::error("TODO: Error! tile_map.cpp");
			return false;
		}
	}

	if(!read_attribute_int(node, "tilewidth", &tile_width)) {
		rge::log::error("TODO: Error! tile_map.cpp");
		return false;
	}

	if(!read_attribute_int(node, "tileheight", &tile_height)) {
		rge::log::error("TODO: Error! tile_map.cpp");
		return false;
	}

	if(tile_width != tile_height || tile_width < 0 || tile_height < 0) {
		rge::log::error("TODO: Error! tile_map.cpp");
		return false;
	}

	xml_node<>* tile_set_node = node->first_node("tileset");
	if(!read_tile_set(tile_set_node, &set)) {
		rge::log::error("TODO: Error! tile_map.cpp");
		return false;
	}

	*map = new tile_map(width, height);
	(*map)->set_tile_registry(set);

	xml_node<>* layer_node = node->first_node("layer");
	while(layer_node) {
		tile_layer layer;
		layer.width = width;
		layer.height = height;
		if(!read_layer(layer_node, &layer, infinite)) {
			rge::log::error("TODO: Error! tile_map.cpp");
			return false;
		}

		(*map)->add_tile_layer(layer);

		layer_node = layer_node->next_sibling("layer");
	}

	return true;
}

static tile_map* read(char* text) {
	tile_map* map = nullptr;
	xml_document<> doc;

	try {
		doc.parse<parse_non_destructive>(text);
	} catch(const parse_error& e) {
		rge::log::error("TODO: Failed to parse xml: %s", e.what());
		return nullptr;
	}

	xml_node<>* map_node = doc.first_node("map");
	if(map_node == nullptr) {
		rge::log::error("TODO: .tmx does not contain <map> node");
		return nullptr;
	}

	if(!read_map(map_node, &map)) {
		return nullptr;
	}

	return map;
}

tile_map* tile_map::load(const std::string& file_name) {
	FILE* file = nullptr;
	tile_map* map = nullptr;
	xml_document<> doc;
	size_t size = 0;
	char* text = nullptr;

	if(!(file = fopen(file_name.c_str(), "r"))) {
		rge::log::error("Failed to open tile map file: %s", file_name.c_str());
		return nullptr;
	}

	try {
		fseek(file, 0, SEEK_END);
		size = ftell(file);
		fseek(file, 0, SEEK_SET);
	} catch(const std::exception& e) {
		rge::log::error("TODO: Failed to read file size: %s", file_name.c_str());
		if(file) fclose(file);
		return nullptr;
	}

	try {
		text = new char[size + 1];
		fread(text, 1, size, file);
		text[size] = 0;
	} catch(const std::exception& e) {
		rge::log::error("TODO: Failed to read file text: %s", file_name.c_str());
		if(file) fclose(file);
		if(text) delete[] text;
		return nullptr;
	}

	map = read(text);

	fclose(file);
	delete[] text;
	return map;
}

tile_map::tile_map(int width, int height) {
    this->width = width;
    this->height = height;

    x = 0;
    y = 0;
    tile_size = 1;

    registry = nullptr;

	layers.clear();
}

tile_map::~tile_map() {
	for(int i = 0; i < layers.size(); i++) {
		delete[] layers[i].grid;
	}
}

void tile_map::draw_layer(int i) {
	int j = -1;
	for(int h = 0; h < width; h++) {
		for(int v = 0; v < height; v++) {
			j = layers[i].grid[v * width + h];
			if(j >= 0) {
				tile* t = registry->get_tile(j);

				game::get_renderer()->draw_tile(
					*t->texture,
					x + h,
					y + v,
					i - (layers.size() - 1),
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