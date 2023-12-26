#ifndef _PLAYER_HPP_
#define _PLAYER_HPP_

#include "rge.hpp"
#include "pawn.hpp"

class player : public pawn {
public:
	player();
	~player();

	void draw() override;

	void update(float delta_time) override;

private:
	rge::transform::ptr transform;
	rge::sprite::ptr sprite;

	float anim_counter;
	int anim_index;
};

#endif /* _PLAYER_HPP_ */