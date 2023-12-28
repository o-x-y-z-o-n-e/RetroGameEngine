#include "player.hpp"
#include "game.hpp"

const float MOVE_SPEED = 32;
const float MOVE_ACCERATE = 96;
const float MOVE_DECERATE = 32;
const float JUMP_VELOCITY = 56;
const float JUMP_HOLD = 96;
const float GRAVITY = 192;


player::player() : pawn() {
	transform = transform::create();
	transform->position = vec3(16, 60, 0);
	sprite = sprite::create();
	sprite->texture = texture::load("res/entities/player.png");
	sprite->sub_sprite = true;
	sprite->section.x = 0;
	sprite->section.y = 8;
	sprite->section.w = 8;
	sprite->section.h = 8;
	sprite->centered = false;
	sprite->pixels_per_unit = PPU;
	sprite->transform->parent = transform;

	anim_counter = 0;
	anim_index = 0;
	is_grounded = false;

	cmd_jump_press = false;
	cmd_jump_hold = false;
	cmd_left_hold = false;
	cmd_right_hold = false;
}

player::~player() {

}

void player::draw() {
	game::get_renderer()->draw(*sprite);
}

void player::update(float delta_time) {
	pawn::update(delta_time);

	poll_input();

	anim_counter += delta_time;

	float vel_x = velocity.x;
	move(delta_time);

	if(math::sign(vel_x) != math::sign(velocity.x)) {
		if(math::sign(velocity.x) != 0) {
			sprite->flip_x = math::sign(velocity.x) < 0;
		}
	}

	if(!is_grounded) {
		if(velocity.y < 0) {
			set_sprite(16, 80);
		} else {
			set_sprite(8, 80);
		}
			
		/*
		if(velocity.y < 0) {
			set_sprite(8, 80);
		} else if(velocity.y < 40.0F) {
			set_sprite(16, 80);
		} else {
			set_sprite(8, 80);
		}
		*/
	} else if(math::abs(velocity.x) > 0.05F) {
		anim_counter += delta_time * math::abs(velocity.x) / MOVE_SPEED;
		if(anim_counter > 0.125F) {
			anim_counter = 0;
			anim_index = (anim_index + 1) % 8;

			set_sprite(8 * anim_index, 8);
		}
	} else {
		anim_counter += delta_time;
		if(anim_counter > 0.25F) {
			anim_counter = 0;
			anim_index = (anim_index + 1) % 4;

			set_sprite(8 * anim_index, 56);
		}
	}
}

void player::poll_input() {
	if(input::was_pressed(input::KEY_SPACE)) {
		cmd_jump_press = true;
	}

	if(input::is_down(input::KEY_SPACE)) {
		cmd_jump_hold = true;
	}

	if(input::is_down(input::KEY_A)) {
		cmd_left_hold = true;
	}

	if(input::is_down(input::KEY_D)) {
		cmd_right_hold = true;
	}
}

vec2 player::collide_and_slide(vec2 delta, vec2 pos, int depth) {
	const int MAX_PASSES = 5;
	const float SKIN_WIDTH = 0.01F;

	if(depth >= MAX_PASSES) {
		return rge::vec2();
	}

	/*
	rge::rect ground = rge::rect(0, 0, 100, 48);
	rge::rect wall = rge::rect(8 * 8, 48, 8, 16);
	std::vector<rect*> colliders;
	colliders.push_back(&ground);
	colliders.push_back(&wall);
	*/

	const std::vector<collider*>* colliders = game::get_world()->get_colliders();
	rge::log::info("%i", colliders->size());
	physics::sweep_result result = physics::sweep(rect(pos.x, pos.y, 8, 8), delta, *colliders);

	if(result.travel_percent >= 1.0F)
		return delta;

	float remaining_percent = 1.0F - result.travel_percent;
	float dot_product = (delta.x * result.normal.y + delta.y * result.normal.x) * remaining_percent;
	
	vec2 new_delta = vec2(result.normal.y, result.normal.x) * dot_product;

	delta *= result.travel_percent;
	return delta + collide_and_slide(new_delta, pos + delta, depth + 1);
}

void player::move(float delta_time) {
	float move_input = (cmd_left_hold ? -1 : 0) + (cmd_right_hold ? 1 : 0);
	float vel_x_target = move_input * MOVE_SPEED;

	cmd_left_hold = false;
	cmd_right_hold = false;

	bool counter_move = math::abs(move_input) > 0.05F && math::sign(vel_x_target) != math::sign(velocity.x);

	float acceration;
	if(math::abs(velocity.x) < math::abs(vel_x_target) || counter_move) {
		acceration = MOVE_ACCERATE;
	} else {
		acceration = MOVE_DECERATE;
	}

	if(counter_move) {
		acceration *= 1.5F; // on flip
	}

	velocity.x = math::move_towards(velocity.x, vel_x_target, acceration * delta_time);
	
	if(is_grounded) {
		if(velocity.y <= 0)
			velocity.y = -1;

		if(cmd_jump_press) {
			cmd_jump_press = false;

			velocity.y = JUMP_VELOCITY;
		}
	} else {
		velocity.y -= GRAVITY * delta_time;

		if(cmd_jump_hold && velocity.y > 0) {
			cmd_jump_hold = false;
			velocity.y += JUMP_HOLD * delta_time;
		}
	}

	vec2 pos = transform->get_global_position();
	vec2 target_delta = velocity * delta_time;
	vec2 real_delta = collide_and_slide(target_delta, pos);

	bool touching_ground = target_delta.y < 0 && real_delta.y > target_delta.y;
	if(touching_ground != is_grounded) {
		is_grounded = touching_ground;

		if(is_grounded) {
			anim_index = 0;
			anim_counter = 0;
			set_sprite(0, 56);
		} else {

		}
	}

	pos += real_delta;
	velocity = real_delta / delta_time;

	transform->set_global_position(pos);
}

void player::set_sprite(int x, int y) {
	sprite->section.x = x;
	sprite->section.y = y;
}