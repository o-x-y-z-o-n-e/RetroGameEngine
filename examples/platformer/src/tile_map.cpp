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

static bool read_layer(xml_node<>* node, void* layer) {

}

static bool read_tile_set(xml_node<>* node, tile_set** set) {
	char* path;
	if(!read_attribute_str(node, "source", &path)) {
		rge::log::error("TODO: Error! tile_map.cpp");
		return false;
	}

	// TODO
	*set = nullptr;
	return true;
}

static bool read_map(xml_node<>* node, tile_map** map) {
	xml_attribute<>* orientation_node = node->first_attribute("orientation");
	if(orientation_node == nullptr) {
		rge::log::error("TODO: Error! tile_map.cpp");
		return false;
	}

	if(STR_EQUAL(orientation_node->value(), "orthogonal")) {
		rge::log::error("tile_map doesn't support grid layouts other than orthogonal!");
		return false;
	}

	int width;
	int height;
	bool infinite;

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

	*map = new tile_map(width, height);
	return true;
}

static tile_map* read(char* text) {
	tile_map* map = nullptr;
	xml_document<> doc;

	try {
		doc.parse<0>(text);
	} catch(const std::exception& e) {
		return nullptr;
	}

	xml_node<>* map_node = doc.first_node("map");
	if(map_node == nullptr) {
		rge::log::error("TODO: Error! tile_map.cpp");
		return nullptr;
	}

	if(!read_map(map_node, &map)) {
		rge::log::error("TODO: Error! tile_map.cpp");
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
		rge::log::error("Failed to open tile map file: %s", file_name);
		return nullptr;
	}

	try {
		fseek(file, 0, SEEK_END);
		size = ftell(file);
		fseek(file, 0, SEEK_SET);
	} catch(const std::exception& e) {
		if(file) fclose(file);
		return nullptr;
	}

	try {
		text = new char[size + 1];
		fread(text, 1, size, file);
		text[size] = 0;
	} catch(const std::exception& e) {
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