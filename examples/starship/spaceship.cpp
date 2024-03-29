#include "spaceship.hpp"
#include "game.hpp"

const int MAX_HEALTH = 8;

spaceship::spaceship() {
	transform = rge::transform::create();
	sprite = rge::sprite::create();
	sprite->transform->parent = transform;
	sprite->pixels_per_unit = 16;
	sprite->centered = true;
	sprite->material = rge::material::create();

	flame_sprite = rge::sprite::create();
	flame_sprite->transform->parent = transform;
	flame_sprite->transform->position = rge::vec3(-0.125F, -1.0F, -SPACESHIP_LAYER);
	flame_sprite->pixels_per_unit = 16;

	health_sprite = rge::sprite::create();
	health_sprite->pixels_per_unit = 16;

	health_textures.push_back(rge::texture::load("res/health_point_off.png"));
	health_textures.push_back(rge::texture::load("res/health_point_on.png"));

	textures.push_back(rge::texture::load("res/spaceship_0.png"));
	textures.push_back(rge::texture::load("res/spaceship_1.png"));
	textures.push_back(rge::texture::load("res/spaceship_2.png"));

	flames.push_back(rge::texture::load("res/flame_0.png"));
	flames.push_back(rge::texture::load("res/flame_1.png"));
	flames.push_back(rge::texture::load("res/flame_2.png"));
	flames.push_back(rge::texture::load("res/flame_3.png"));
	flames.push_back(rge::texture::load("res/flame_4.png"));
	flames.push_back(rge::texture::load("res/flame_5.png"));

	shoot_action.add_binding(rge::input::KEY_SPACE);
	shoot_action.add_binding(rge::input::GAMEPAD_LEFT_TRIGGER);
	shoot_action.add_binding(rge::input::GAMEPAD_RIGHT_TRIGGER);

	reset();
}

spaceship::~spaceship() {

}

void spaceship::reset() {
	transform->position = rge::vec3(0, 0, -SPACESHIP_LAYER);

	shoot_side = 1;
	shoot_cooldown = 0;

	flame_counter = 0;
	flame_index = 0;

	dmg_count = 0;
	dmg_t = 0.0F;

	health = MAX_HEALTH;
}

void spaceship::draw() {
	transform->position.z = -SPACESHIP_LAYER;
	rge::engine::get_renderer()->draw(*flame_sprite);
	rge::engine::get_renderer()->draw(*sprite);

	for(int i = 0; i < MAX_HEALTH; i++) {
		health_sprite->transform->position = rge::vec3(-7.5F + (i * 0.25F), -5.5F, -UI_LAYER);
		health_sprite->texture = health_textures[i < health];
		rge::engine::get_renderer()->draw(*health_sprite);
	}
}

void spaceship::update(float delta_time) {
	const float ACCEL = 16.0F;
	const float MAX_SPEED = 16.0F;
	const float SHOOT_INTERVAL = 0.2F;
	const float DMG_FLASH_SPEED = 10.0F;

	if(rge::input::is_down(rge::input::KEY_A)) {
		velocity.x -= ACCEL * delta_time;
	}
	if(rge::input::is_down(rge::input::KEY_D)) {
		velocity.x += ACCEL * delta_time;
	}
	if(rge::input::is_down(rge::input::KEY_S)) {
		velocity.y -= ACCEL * delta_time;
	}
	if(rge::input::is_down(rge::input::KEY_W)) {
		velocity.y += ACCEL * delta_time;
	}

	float d = velocity.magnitude();
	if(d > MAX_SPEED) {
		velocity = rge::vec2::normalize(velocity) * MAX_SPEED;
	}

	if(velocity.x < -2.0F) {
		sprite->texture = textures[1];
	} else if(velocity.x > 2.0F) {
		sprite->texture = textures[2];
	} else {
		sprite->texture = textures[0];
	}

	transform->position += velocity * delta_time;

	if(shoot_cooldown > 0.0F) shoot_cooldown -= delta_time;
	if(shoot_cooldown <= 0.0F && rge::input::is_down(shoot_action)) {
		laser* l = laser::create();
		rge::vec2 p = transform->position + rge::vec2(0.375F * shoot_side, -0.5F);
		if(shoot_side < 0) p.x -= (1.0F / 16.0F);
		l->set_position(p);
		shoot_side *= -1;
		shoot_cooldown = SHOOT_INTERVAL;
	}

	flame_counter += delta_time;
	if(flame_counter > 0.1F) {
		flame_counter -= 0.1F;

		flame_index = (flame_index + 1) % flames.size();
		flame_sprite->texture = flames[flame_index];
	}

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

	if(transform->position.x < -7.5F) {
		transform->position.x = -7.5F;
		velocity.x *= -1;
	}

	if(transform->position.x > 7.5F) {
		transform->position.x = 7.5F;
		velocity.x *= -1;
	}

	if(transform->position.y < -5.5F) {
		transform->position.y = -5.5F;
		velocity.y *= -1;
	}

	if(transform->position.y > 5.5F) {
		transform->position.y = 5.5F;
		velocity.y *= -1;
	}
}

void spaceship::damage(int amount) {
	dmg_count = 6;
	dmg_t = 1.0F;

	health -= amount;
	if(health <= 0) {
		game::get()->end(false);
		return;
	}
}
