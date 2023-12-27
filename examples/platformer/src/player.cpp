#include "player.hpp"
#include "game.hpp"

player::player() : pawn() {
	transform = rge::transform::create();
	transform->position = rge::vec3(16, 48, 0);
	sprite = rge::sprite::create();
	sprite->texture = rge::texture::load("res/entities/player.png");
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

	if(anim_counter > 0.5F) {
		anim_counter -= 0.5F;

		anim_index = (anim_index + 1) % 2;

		if(anim_index == 0) {
			sprite->section.x = 0;
			sprite->section.y = 56;
		} else if(anim_index == 1) {
			sprite->section.x = 16;
			sprite->section.y = 56;
		}
	}
}

void player::poll_input() {
	if(rge::input::was_pressed(rge::input::KEY_SPACE)) {
		cmd_jump = true;
	}

	if(rge::input::is_down(rge::input::KEY_A)) {
		cmd_left = true;
	}

	if(rge::input::is_down(rge::input::KEY_D)) {
		cmd_right = true;
	}
}