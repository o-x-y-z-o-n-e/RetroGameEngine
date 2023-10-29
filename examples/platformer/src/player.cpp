#include "player.hpp"
#include "platformer.hpp"

player::player() {
	transform = rge::transform::create();
	main_sprite = rge::sprite::create();
	main_sprite->transform->parent = transform;
}

void player::update(float delta_time) {

}

void player::draw() {
	platformer::get_renderer()->draw(*main_sprite);
}