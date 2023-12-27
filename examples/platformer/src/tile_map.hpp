#ifndef _TILE_MAP_HPP_
#define _TILE_MAP_HPP_

#include "rge.hpp"
#include "tile_set.hpp"

struct tile_layer {
	int* grid;
	int width;
	int height;
	int offset_x;
	int offset_y;

	inline tile_layer() {
		grid = nullptr;
		width = 0;
		height = 0;
		offset_x = 0;
		offset_y = 0;
	}
};

class tile_map {
public:
    tile_map(int map_width, int map_height, int tile_width, int tile_height);
    ~tile_map();

	static tile_map* load(const std::string& file_name);
    
    void draw();
    void set_tile_registry(tile_set* set);
	void add_tile_layer(tile_layer& layer);

public:
    inline int get_width() const { return map_width; }
    inline int get_height() const { return map_height; }

private:
	void draw_layer(int i);

public:
    int tile_width;
	int tile_height;

private:
    tile_set* registry;
	std::vector<tile_layer> layers;
    int map_width;
    int map_height;
};

/* Tiled 1.8 spec support list
Legend:
"*" wild card
"..." all before/after/inbetween
"!*" not
"* & *" and
"* | *" or
"* < *" less than
"* > *" greater than
"( ... )" group
"[*, *, *]" list

<map>
[ ]---> version = `1.8`
[ ]---> tiledversion = [`0.0.0`, ..., `*.*.*`]
[+]---> orientation = (orthogonal) & !(isometric | staggered | hexagonal)
[ ]---> class = *
[ ]---> renderorder = [right-down, right-up, left-down, left-up]
[ ]---> compressionlevel = -1
[+]---> width = * > 0
[+]---> height = * > 0
[+]---> tilewidth = * > 0 & (tilewidth == tileheight)
[+]---> tileheight = * > 0 & (tileheight == tilewidth)
[ ]---> staggeraxis = *
[ ]---> staggerindex = *
[ ]---> parallaxoriginx = 0
[ ]---> parallaxoriginy = 0
[ ]---> backgroundcolor = [#000000, ..., #FFFFFF]
[ ]---> nextlayerid = *
[ ]---> nextobjectid = *
[ ]---> infinite = 0

<tileset>
[ ]---> firstgid = *
[+]---> source = *
[ ]---> name = *
[ ]---> class = *
TODO

<layer>
[ ]---> id = *
[ ]---> name = *
[ ]---> class = *
[*]---> width = * > 0
[*]---> height = * > 0
[ ]---> opacity = [0.0, ..., 1.0]
[ ]---> visible = [0, 1]
[ ]---> tintcolor = [#000000, ..., #FFFFFF]
[*]---> offsetx = *
[*]---> offsety = *
[ ]---> parallaxx = 1
[ ]---> parallaxy = 1

<data>
[*]---> encoding = csv & !base64
[ ]---> compression = ![gzip, zlib, zstd]
*/

#endif /* _TILE_MAP_HPP_ */