#include "tile_set.hpp"
#include "tile_loader.hpp"

tile_set::tile_set(rge::texture::ptr texture) {
    sheet = texture;
}

tile* tile_set::get_tile(int i) {
    if(i < 0 || i >= tiles.size())
        return nullptr;
    else
        return &tiles[i];
}

void tile_set::add_tile(const tile& t) {
    tiles.push_back(t);
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

static bool read_tile_set(xml_node<>* node, tile_set** set) {
	char* path = nullptr;
    int tile_width = 0;
    int tile_height = 0;

	if(node == nullptr)
		return false;

	if(!read_attribute_str(node, "source", &path)) {
		rge::log::error("Failed to read source attribute");
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

    *set = new tile_set(image);

	int w = image->get_width() / tile_width;
	int h = image->get_height() / tile_height;

	for(int i = 0; i < w * h; i++) {
		tile t;
		t.x = i % w;
		t.y = i / w;
		t.width = tile_width;
		t.height = tile_height;
		(*set)->add_tile(t);
	}

	return true;
}

static tile_set* read(char* text) {
    tile_set* set = nullptr;
	xml_document<> doc;

	try {
		doc.parse<parse_non_destructive>(text);
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