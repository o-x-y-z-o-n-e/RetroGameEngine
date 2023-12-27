#include "tile_set.hpp"
#include "tile_loader.hpp"

tile_set::tile_set(rge::texture::ptr texture) {
    sheet = texture;
}

tile_set::tile_set(rge::texture::ptr texture, int tile_width, int tile_height) {
	sheet = texture;

	int w = texture->get_width() / tile_width;
	int h = texture->get_height() / tile_height;

	for(int y = 0; y < h; y++) {
		for(int x = 0; x < w; x++) {
			tile t;
			t.x = x * tile_width;
			t.y = y * tile_height;
			t.width = tile_width;
			t.height = tile_height;
			add_tile(t);
		}
	}
}

tile* tile_set::get_tile(int i) {
    if(i < 0 || i >= tiles.size())
        return nullptr;
    else
        return &tiles[i];
}

void tile_set::add_tile(const tile& tile) {
    tiles.push_back(tile);
}

static bool read_image(xml_node<>* node, rge::texture::ptr* texture) {
    char* source = nullptr;
    
    if(node == nullptr)
		return false;

    if(!read_attribute_str(node, "source", &source)) {
		rge::log::error("Failed to read source attribute");
		return false;
	}

    rge::texture::ptr t = rge::texture::load(source);
    if(!t) {
		return false;
    }

    *texture = t;
    return true;
}

static bool read_tile(xml_node<>* node, tile_set* set) {
	int id = -1;

	if(!node)
		return false;

	if(!read_attribute_int(node, "id", &id)) {
		return false;
	}

	xml_node<>* object_group = node->first_node("objectgroup");
	if(!object_group) return false;

	tile* tile = set->get_tile(id);

	xml_node<>* child_node = object_group->first_node("object");
	char* type = nullptr;
	rge::rect bounds;
	while(child_node) {
		if(!read_attribute_str(child_node, "type", &type)) {
			rge::log::error("TODO: tile_set.cpp");
			return false;
		}

		if(!STR_EQUAL("collide", type)) {
			rge::log::error("TODO: tile_set.cpp");
			return false;
		}

		if(child_node->first_attribute("rotation")) {
			rge::log::error("TODO: tile_set.cpp");
			return false;
		}

		if(!read_attribute_float(child_node, "x", &bounds.x)) {
			rge::log::error("TODO: tile_set.cpp");
			return false;
		}

		if(!read_attribute_float(child_node, "y", &bounds.y)) {
			rge::log::error("TODO: tile_set.cpp");
			return false;
		}

		if(!read_attribute_float(child_node, "width", &bounds.w)) {
			rge::log::error("TODO: tile_set.cpp");
			return false;
		}

		if(!read_attribute_float(child_node, "height", &bounds.h)) {
			rge::log::error("TODO: tile_set.cpp");
			return false;
		}

		tile->collision.push_back(bounds);

		child_node = child_node->next_sibling("object");
	}

	return true;
}

static bool read_tile_set(xml_node<>* node, tile_set** set) {
	char* name = nullptr;
    int tile_width = 0;
    int tile_height = 0;

	if(node == nullptr)
		return false;

	if(!read_attribute_str(node, "name", &name)) {
		rge::log::error("Failed to read name attribute");
		return false;
	}

    if(!read_attribute_int(node, "tilewidth", &tile_width)) {
		rge::log::error("Failed to read source attribute");
		return false;
	}

    if(!read_attribute_int(node, "tileheight", &tile_height)) {
		rge::log::error("Failed to read source attribute");
		return false;
	}

    rge::texture::ptr image;
    xml_node<>* image_node = node->first_node("image");
    if(!read_image(image_node, &image)) {
        rge::log::error("Failed to read <image> node");
		return false;
    }

    *set = new tile_set(image, tile_width, tile_height);

	xml_node<>* tile_node = node->first_node("tile");
	while(read_tile(tile_node, *set)) {
		tile_node = tile_node->next_sibling("tile");
	}

	// TODO: Set name.

	return true;
}

static tile_set* read(char* text) {
    tile_set* set = nullptr;
	xml_document<> doc;

	try {
		doc.parse<0>(text);
	} catch(const parse_error& e) {
		rge::log::error("Failed to parse xml: %s", e.what());
		return nullptr;
	}

    xml_node<>* set_node = doc.first_node("tileset");
	if(!read_tile_set(set_node, &set)) {
		rge::log::error("<tileset> node not found");
		return nullptr;
	}

    return set;
}

tile_set* tile_set::load(const std::string& file_name) {
    FILE* file = nullptr;
	tile_set* set = nullptr;
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

	set = read(text);

	fclose(file);
	delete[] text;
    return set;
}