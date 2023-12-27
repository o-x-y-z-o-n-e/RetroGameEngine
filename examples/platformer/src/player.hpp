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
	void poll_input();

private:
	rge::transform::ptr transform;
	rge::sprite::ptr sprite;

	float anim_counter;
	int anim_index;

	// Input commands.
	bool cmd_jump;
	bool cmd_left;
	bool cmd_right;
};

#endif /* _PLAYER_HPP_ */