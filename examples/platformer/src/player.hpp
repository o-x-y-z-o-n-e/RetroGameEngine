#ifndef _PLAYER_HPP_
#define _PLAYER_HPP_

#include "game.hpp"

class player : public pawn {
public:
	player();
	~player();

	void draw() override;

private:
	rge::transform::ptr transform;
	rge::sprite::ptr sprite;
};

#endif /* _PLAYER_HPP_ */