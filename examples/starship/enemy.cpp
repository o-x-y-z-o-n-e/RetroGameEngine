#include "enemy.hpp"
#include "game.hpp"

const float RADIUS = 0.5F;

enemy::table enemy::pool;

enemy::enemy() {
	transform = rge::transform::create();
	sprite = rge::sprite::create();
	sprite->transform->parent = transform;
	sprite->pixels_per_unit = 16;
	sprite->centered = true;
	sprite->material = rge::material::create();

	reset();
}

void enemy::gen_starting_params() {
	transform->position = rge::vec3(game::get()->get_random()->range(-7.0F, 7.0F), 8, LAYER_TO_Z(ENEMY_LAYER));

	type = game::get()->get_random()->next_u64() % 3;
	if(type == 0) {
		sprite->texture = rge::texture::load("res/enemy_0.png");
	} else if(type == 1) {
		sprite->texture = rge::texture::load("res/enemy_1.png");
	} else if(type == 2) {
		sprite->texture = rge::texture::load("res/enemy_2.png");
	}
}

void enemy::reset() {
	health = 3;
	dmg_count = 0;
	dmg_t = 0.0F;
	anim_counter = 0;
	sprite->material->diffuse = rge::color(1, 1, 1, sprite->material->diffuse.a);

	transform->rotation = rge::quaternion();

	gen_starting_params();
}

void enemy::update(float delta_time) {
	const float DMG_FLASH_SPEED = 10.0F;
	const float MOVE_SPEED = 1.5F;

	if(dmg_count > 0) {
		dmg_t += delta_time * DMG_FLASH_SPEED;
		if(dmg_t >= 1.0F) {
			dmg_t -= 1.0F;
			dmg_count--;
			if(dmg_count % 2 == 0) {
				sprite->material->diffuse = rge::color(1, 1, 1, sprite->material->diffuse.a);
			} else {
				sprite->material->diffuse = rge::color(1, 0, 0, sprite->material->diffuse.a);
			}
		}
	}

	anim_counter += delta_time;
	if(type == 0) {
		transform->rotation = rge::quaternion::yaw_pitch_roll(0, 0, sinf(anim_counter*10) * 0.25F);
	} else if(type == 1) {

	} else if(type == 2) {
		transform->rotation = rge::quaternion::yaw_pitch_roll(0, 0, anim_counter * 3);
	}

	transform->position += rge::vec2(0, -MOVE_SPEED) * delta_time;
	if(transform->position.y < -8) {
		destroy(this);
	}

	spaceship* ship = game::get()->get_ship();
	float dist = rge::vec2::distance(ship->get_position(), transform->get_global_position());
	dist -= RADIUS;
	dist -= ship->get_radius();
	if(dist < 0.0F) {
		ship->damage(1);
		explode* e = explode::create();
		e->set(transform->get_global_position());
		destroy(this);
		return;
	}
}

void enemy::draw() {
	rge::engine::get_renderer()->draw(*sprite);
}

bool enemy::overlap(rge::vec2 point) const {
	return rge::vec2::distance(point, transform->position) - RADIUS < 0.0F;
}

void enemy::take_damage() {
	dmg_count = 6;
	dmg_t = 1.0F;
	health--;
	if(health <= 0) {
		explode* e = explode::create();
		e->set(transform->get_global_position());
		destroy(this);
	}
}

enemy* enemy::create() {
	table::iterator it;
	for(it = pool.begin(); it != pool.end(); it++) {
		if(!it->second) {
			it->second = true;
			it->first->reset();
			return it->first;
		}
	}

	enemy* ins = new enemy();
	pool.push_back(entry(ins, true));
	return ins;
}

void enemy::destroy(enemy* ins) {
	table::iterator it;
	for(it = pool.begin(); it != pool.end(); it++) {
		if(it->first == ins) {
			it->second = false;
			return;
		}
	}
}

void enemy::destroy_all() {
	table::iterator it;
	for(it = pool.begin(); it != pool.end(); it++) {
		it->second = false;
	}
}

void enemy::update_all(float delta_time) {
	table::iterator it;
	for(it = pool.begin(); it != pool.end(); it++) {
		if(it->second) {
			it->first->update(delta_time);
		}
	}
}

void enemy::draw_all() {
	table::iterator it;
	for(it = pool.begin(); it != pool.end(); it++) {
		if(it->second) {
			it->first->draw();
		}
	}
}

bool enemy::overlap_all(rge::vec2 point, std::function<void(enemy& e)> on_overlap) {
	bool did_overlap = false;

	table::iterator it;
	for(it = pool.begin(); it != pool.end(); it++) {
		if(it->second) {
			if(it->first->overlap(point)) {
				on_overlap(*it->first);
				did_overlap = true;
			}
		}
	}

	return did_overlap;
}