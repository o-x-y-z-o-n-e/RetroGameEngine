#include "player.hpp"

player::player() : pawn() {
	transform = rge::transform::create();
	sprite = rge::sprite::create();
	sprite->texture = rge::texture::load("res/player_0.png");
	sprite->centered = false;
	sprite->pixels_per_unit = PPU;
	sprite->transform->parent = transform;
}

player::~player() {

}

void player::draw() {
	game::get_renderer()->draw(*sprite);
}