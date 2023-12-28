#ifndef _PLAYER_HPP_
#define _PLAYER_HPP_

#include "rge.hpp"
#include "pawn.hpp"

using namespace rge;

class player : public pawn {
public:
	player();
	~player();

	void draw() override;

	void update(float delta_time) override;

private:
	void poll_input();
	void move(float delta_time);
	vec2 collide_and_slide(vec2 delta, vec2 pos, int depth = 0);
	void set_sprite(int x, int y);

private:
	vec2 velocity;

private:
	transform::ptr transform;
	sprite::ptr sprite;
	vec2 center;
	float radius;

	float anim_counter;
	int anim_index;

	bool is_grounded;

	// Input commands.
	bool cmd_jump_press;
	bool cmd_jump_hold;
	bool cmd_left_hold;
	bool cmd_right_hold;
};

#endif /* _PLAYER_HPP_ */