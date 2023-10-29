#ifndef _PLAYER_HPP_
#define _PLAYER_HPP_

#include "rge.hpp"

class player {

public:
	player();

	virtual void update(float delta_time);
	virtual void draw();

private:
	rge::transform::ptr transform;
	rge::sprite::ptr main_sprite;

};

#endif /* _PLAYER_HPP_ */