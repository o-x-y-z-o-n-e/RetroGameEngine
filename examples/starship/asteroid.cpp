#include "game.hpp"
#include "asteroid.hpp"

asteroid::asteroid_table asteroid::pool;

asteroid::asteroid() {
	transform = rge::transform::create();
	sprite = rge::sprite::create();
	sprite->transform->parent = transform;
	sprite->pixels_per_unit = 16;
	sprite->centered = true;

	gen_starting_params();
}

asteroid::~asteroid() {

}

void asteroid::reset() {
	gen_starting_params();
}

void asteroid::update(float delta_time) {
	// Move...
	transform->position += velocity * delta_time;
	rotation += turn * delta_time;
	transform->rotation = rge::quaternion::yaw_pitch_roll(0, 0, rotation); // TODO: Add rge::quaternion::rotate(flaot angle, vec3 axis);

	// Detect collision...
	if(velocity.x < 0.0F) {
		// Check left side...
		if(transform->position.x < -8 - radius) {
			destroy(this);
			return;
		}
	} else {
		// Check right side...
		if(transform->position.x > 8 + radius) {
			destroy(this);
			return;
		}
	}
	if(velocity.y < 0.0F) {
		// Check bottom side...
		if(transform->position.y < -6 - radius) {
			destroy(this);
			return;
		}
	}
}

void asteroid::draw() {
	transform->position.z = -ASTEROID_LAYER;
	rge::engine::get_renderer()->draw(*sprite);
}

void asteroid::gen_starting_params() {
	sprite->texture = rge::texture::load("res/asteroid_0.png");
	radius = 1.0F;
	velocity = rge::vec2();
	turn = 10;

	transform->position = rge::vec3(0, 0, 0);
}

asteroid* asteroid::create() {
	asteroid_table::iterator it;
	for(it = pool.begin(); it != pool.end(); it++) {
		if(!it->second) {
			it->second = true;
			it->first->reset();
			return it->first;
		}
	}

	asteroid* ins = new asteroid();
	pool.push_back(asteroid_entry(ins, true));
	return ins;
}

void asteroid::destroy(asteroid* ins) {
	asteroid_table::iterator it;
	for(it = pool.begin(); it != pool.end(); it++) {
		if(it->first == ins) {
			it->second = false;
			return;
		}
	}
}

void asteroid::update_all(float delta_time) {
	asteroid_table::iterator it;
	for(it = pool.begin(); it != pool.end(); it++) {
		if(it->second) {
			it->first->update(delta_time);
		}
	}
}

void asteroid::draw_all() {
	asteroid_table::iterator it;
	for(it = pool.begin(); it != pool.end(); it++) {
		if(it->second) {
			it->first->draw();
		}
	}
}