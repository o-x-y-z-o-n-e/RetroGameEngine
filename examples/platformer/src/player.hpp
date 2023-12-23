#ifndef _PLAYER_HPP_
#define _PLAYER_HPP_

#include "game.hpp"

class player : public pawn {
public:
	player();
	~player();

	void draw() override;
};

#endif /* _PLAYER_HPP_ */