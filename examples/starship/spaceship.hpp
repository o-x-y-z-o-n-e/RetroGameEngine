#ifndef _SPACESHIP_HPP_
#define _SPACESHIP_HPP_

#include "rge.hpp"

class spaceship {

public:
	spaceship();
	~spaceship();
	void reset();
	void draw();
	void update(float delta_time);

private:
	std::vector<rge::texture::ptr> textures;
	rge::transform::ptr transform;
	rge::sprite::ptr sprite;
	rge::vec2 velocity;
	rge::vec2 move_input;
};

#endif /* _SPACESHIP_HPP_ */