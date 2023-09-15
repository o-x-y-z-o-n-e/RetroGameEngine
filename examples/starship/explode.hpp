#ifndef EXPLODE_H
#define EXPLODE_H

#include "rge.hpp"

class explode {
public:
    explode();
	~explode();
	void reset();
	void update(float delta_time);
	void draw();

private:
    std::vector<rge::texture::ptr> textures;
    rge::transform::ptr transform;
    rge::sprite::ptr sprite;
    float counter;
    int index;
};

#endif