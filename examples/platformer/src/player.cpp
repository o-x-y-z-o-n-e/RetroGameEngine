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
	transform->position = vec3(16, 48, 0);
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

	physics::cast_hit hit;
	physics::ray ray = physics::ray(
		transform->transform_point(center - vec2(0, -radius)) + vec2(0, 0.01F),
		vec2(0, -1),
		0.02F
	);
	bool touching_ground = transform->get_global_position().y <= 48; // physics::cast_ray(&hit, ray);
	if(touching_ground != is_grounded) {
		is_grounded = touching_ground;

		if(is_grounded) {
			if(velocity.y < 0)
				velocity.y = 0;

			anim_index = 0;
			anim_counter = 0;
			set_sprite(0, 56);
		} else {

		}
	}

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

	float dist = delta.magnitude() + SKIN_WIDTH;

	physics::cast_hit hit;
	physics::circle circle = physics::circle(transform->transform_point(center), radius);
	if(physics::sweep(&hit, circle, delta)) {
		vec2 surface_snap = rge::vec2::normalize(delta) * (hit.distance - SKIN_WIDTH);
		vec2 left_over = delta - surface_snap;

		float m = left_over.magnitude();
		vec2 v = vec2(hit.normal.y, -hit.normal.x);

		left_over = vec2::normalize(v * vec2::dot(v, left_over));
		left_over *= m;

		return surface_snap + collide_and_slide(left_over, pos + surface_snap, depth + 1);
	}

	return delta;
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
	
	if(transform->get_global_position().y > 48) {
		velocity.y -= GRAVITY * delta_time;

		if(cmd_jump_hold && velocity.y > 0) {
			cmd_jump_hold = false;
			velocity.y += JUMP_HOLD * delta_time;
		}
	} else {
		velocity.y = 0;

		if(cmd_jump_press) {
			cmd_jump_press = false;

			velocity.y = JUMP_VELOCITY;
		}
	}

	vec2 pos = transform->get_global_position();
	vec2 delta = collide_and_slide(velocity * delta_time, pos);

	pos += delta;
	velocity = delta / delta_time;

	if(pos.y < 48) {
		pos.y = 48;
		velocity.y = 0;
	}

	transform->set_global_position(pos);
}

void player::set_sprite(int x, int y) {
	sprite->section.x = x;
	sprite->section.y = y;
}