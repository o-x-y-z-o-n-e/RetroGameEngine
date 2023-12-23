#include "explode.hpp"
#include "game.hpp"

explode::table explode::pool;

explode::explode() {
    transform = rge::transform::create();
    sprite = rge::sprite::create();
    sprite->transform->parent = transform;
    sprite->pixels_per_unit = 16;
	sprite->centered = true;

	textures.push_back(rge::texture::load("res/explode_0.png"));
	textures.push_back(rge::texture::load("res/explode_1.png"));
	textures.push_back(rge::texture::load("res/explode_2.png"));
	textures.push_back(rge::texture::load("res/explode_3.png"));
	textures.push_back(rge::texture::load("res/explode_4.png"));

	reset();
}

explode::~explode() {
    
}

void explode::reset() {
	index = 0;
	counter = 0;
}

void explode::update(float delta_time) {
    counter += delta_time;
    if(counter >= 0.1F) {
        counter -= 0.1F;
        index++;
    }

    if(index >= textures.size()) {
        destroy(this);
    }
}

void explode::draw() {
    sprite->texture = textures[index];
	rge::engine::get_renderer()->draw(*sprite);
}

void explode::set(rge::vec2 pos) {
	transform->position = rge::vec3(pos.x, pos.y, LAYER_TO_Z(FX_LAYER));
	transform->rotation = rge::quaternion::yaw_pitch_roll(0, 0, game::get()->get_random()->range(0.0F, 360.0F) * DEG_TO_RAD);
}

explode* explode::create() {
	table::iterator it;
	for(it = pool.begin(); it != pool.end(); it++) {
		if(!it->second) {
			it->second = true;
			it->first->reset();
			return it->first;
		}
	}

	explode* ins = new explode();
	pool.push_back(entry(ins, true));
	return ins;
}

void explode::destroy(explode* ins) {
	table::iterator it;
	for(it = pool.begin(); it != pool.end(); it++) {
		if(it->first == ins) {
			it->second = false;
			return;
		}
	}
}

void explode::destroy_all() {
	table::iterator it;
	for(it = pool.begin(); it != pool.end(); it++) {
		it->second = false;
	}
}

void explode::update_all(float delta_time) {
	table::iterator it;
	for(it = pool.begin(); it != pool.end(); it++) {
		if(it->second) {
			it->first->update(delta_time);
		}
	}
}

void explode::draw_all() {
	table::iterator it;
	for(it = pool.begin(); it != pool.end(); it++) {
		if(it->second) {
			it->first->draw();
		}
	}
}