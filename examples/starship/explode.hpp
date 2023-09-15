#ifndef EXPLODE_H
#define EXPLODE_H

#include "rge.hpp"

class explode {
public:
	typedef std::pair<explode*, bool> entry;
	typedef std::vector<entry> table;

public:
    explode();
	~explode();
	void reset();
	void update(float delta_time);
	void draw();

	void set(rge::vec2 pos);

	static explode* create();
	static void destroy(explode* ins);
	static void destroy_all();
	static void update_all(float delta_time);
	static void draw_all();

private:
	static table pool;
    std::vector<rge::texture::ptr> textures;
    rge::transform::ptr transform;
    rge::sprite::ptr sprite;
    float counter;
    int index;
};

#endif