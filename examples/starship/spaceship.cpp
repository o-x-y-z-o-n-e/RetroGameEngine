#include "spaceship.hpp"

spaceship::spaceship() {
	transform = rge::transform::create();
	sprite = rge::sprite::create();
	sprite->transform->parent = transform;
	sprite->pixels_per_unit = 16;
	sprite->centered = true;

	textures.push_back(rge::texture::load("res/spaceship_0.png"));
	textures.push_back(rge::texture::load("res/spaceship_1.png"));
	textures.push_back(rge::texture::load("res/spaceship_2.png"));
}

spaceship::~spaceship() {

}

void spaceship::reset() {

}

void spaceship::draw() {
	if(velocity.x < -1.0F) {
		sprite->texture = textures[1];
	} else if(velocity.x > 1.0F) {
		sprite->texture = textures[2];
	} else {
		sprite->texture = textures[0];
	}
	
	rge::engine::get_renderer()->draw(*sprite);
}

void spaceship::update(float delta_time) {
	const float ACCEL = 1.0F;
	const float SPEED = 16.0F;

	if(rge::input::is_down(rge::input::KEY_A)) {
		move_input.x -= ACCEL * delta_time;
		if(move_input.x < -1.0F) move_input.x = -1.0F;
	}
	if(rge::input::is_down(rge::input::KEY_D)) {
		move_input.x += ACCEL * delta_time;
		if(move_input.x > 1.0F) move_input.x = 1.0F;
	}
	if(rge::input::is_down(rge::input::KEY_S)) {
		move_input.y -= ACCEL * delta_time;
		if(move_input.y < -1.0F) move_input.y = -1.0F;
	}
	if(rge::input::is_down(rge::input::KEY_W)) {
		move_input.y += ACCEL * delta_time;
		if(move_input.y > 1.0F) move_input.y = 1.0F;
	}

	if(transform->position.x < -7.5F) {
		transform->position.x = -7.5F;
		move_input.x *= -1;
	}

	if(transform->position.x > 7.5F) {
		transform->position.x = 7.5F;
		move_input.x *= -1;
	}

	if(transform->position.y < -5.5F) {
		transform->position.y = -5.5F;
		move_input.y *= -1;
	}

	if(transform->position.y > 5.5F) {
		transform->position.y = 5.5F;
		move_input.y *= -1;
	}

	velocity = move_input * SPEED;
	transform->position += velocity * delta_time;
}