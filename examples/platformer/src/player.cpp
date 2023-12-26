#include "player.hpp"
#include "game.hpp"

player::player() : pawn() {
	transform = rge::transform::create();
	transform->position = rge::vec3(8*2, 8*14, 0);
	sprite = rge::sprite::create();
	sprite->texture = rge::texture::load("res/entities/player.png");
	sprite->sub_sprite = true;
	sprite->section.x = 0;
	sprite->section.y = 56;
	sprite->section.w = 8;
	sprite->section.h = 8;
	sprite->centered = false;
	sprite->pixels_per_unit = PPU;
	sprite->transform->parent = transform;
}

player::~player() {

}

void player::draw() {
	game::get_renderer()->draw(*sprite);
}