#include "game.hpp"

const float BG_SCROLL_SPEED = 0.25F;
const float GAME_DURATION = 60 * 4;

game::game() : rge::engine() {
	camera = rge::camera::create();
}

void game::get_default_window_params(std::string& title, int& width, int& height, bool& fullscreen) {
	title = "Starship";
	width = 800;
	height = 600;
	fullscreen = false;
}

void game::on_init() {
	camera->set_orthographic(0.0F, 100.0F, -8, 8, 6, -6);
	camera->transform->position = rge::vec3(0, 0, -1);

	get_renderer()->set_camera(camera);

	ship = new spaceship();

	title_sprite = rge::sprite::create();
	title_sprite->texture = rge::texture::load("res/title.png");
	title_sprite->pixels_per_unit = 16;
	title_sprite->centered = true;
	title_sprite->transform->position = rge::vec3(0, 0, LAYER_TO_Z(UI_LAYER));

	win_sprite = rge::sprite::create();
	win_sprite->texture = rge::texture::load("res/won.png");
	win_sprite->pixels_per_unit = 16;
	win_sprite->centered = true;
	win_sprite->transform->position = rge::vec3(0, 0, LAYER_TO_Z(UI_LAYER));

	lose_sprite = rge::sprite::create();
	lose_sprite->texture = rge::texture::load("res/lost.png");
	lose_sprite->pixels_per_unit = 16;
	lose_sprite->centered = true;
	lose_sprite->transform->position = rge::vec3(0, 0, LAYER_TO_Z(UI_LAYER));

	pause_sprite = rge::sprite::create();
	pause_sprite->texture = rge::texture::load("res/pause.png");
	pause_sprite->pixels_per_unit = 16;
	pause_sprite->centered = true;
	pause_sprite->transform->position = rge::vec3(0, 0, LAYER_TO_Z(UI_LAYER));

	press_key_sprite_0 = rge::sprite::create();
	press_key_sprite_0->texture = rge::texture::load("res/press_any_key_to_start.png");
	press_key_sprite_0->pixels_per_unit = 16;
	press_key_sprite_0->centered = true;
	press_key_sprite_0->transform->position = rge::vec3(0, -4, LAYER_TO_Z(UI_LAYER));

	press_key_sprite_1 = rge::sprite::create();
	press_key_sprite_1->texture = rge::texture::load("res/press_esc_key_to_return.png");
	press_key_sprite_1->pixels_per_unit = 16;
	press_key_sprite_1->centered = true;
	press_key_sprite_1->transform->position = rge::vec3(0, -4, LAYER_TO_Z(UI_LAYER));

	bg_sprite_0 = rge::sprite::create();
	bg_sprite_0->texture = rge::texture::load("res/background.png");
	bg_sprite_0->pixels_per_unit = 16;
	bg_sprite_1 = rge::sprite::create();
	bg_sprite_1->texture = rge::texture::load("res/background.png");
	bg_sprite_1->pixels_per_unit = 16;

	progress_meter = rge::sprite::create();
	progress_meter->material = rge::material::create();
	progress_meter->texture = rge::texture::load("res/meter.png");
	progress_meter->pixels_per_unit = 16;
	progress_meter->section = rge::rect(0, 0, 64, 4);
	progress_meter->sub_sprite = true;

	cooldown_meter = rge::sprite::create();
	cooldown_meter->material = rge::material::create();
	cooldown_meter->texture = rge::texture::load("res/meter_32.png");
	cooldown_meter->pixels_per_unit = 16;
	cooldown_meter->section = rge::rect(0, 0, 32, 4);
	cooldown_meter->sub_sprite = true;

	meter = rge::texture::create(1, 1);
	meter->allocate();
	meter->get_data()[0] = rge::color(1, 1, 1);
	get_renderer()->upload_texture(*meter);

	meter_bg = rge::texture::create(1, 1);
	meter_bg->allocate();
	meter_bg->get_data()[0] = rge::color(0.5F, 0.5F, 0.5F);
	get_renderer()->upload_texture(*meter_bg);
}

void game::on_start() {
	state = game_state::MAIN_MENU;
}

void game::on_update(float delta_time) {
	if(state == game_state::MAIN_MENU) {
		if(rge::input::was_released(rge::input::KEY_ESC)) {
			exit();
		} else if(rge::input::was_released(rge::input::ANY)) {
			start_game();
		}
	} else if(state == game_state::IN_GAME) {
		if(rge::input::was_released(rge::input::KEY_ESC)) {
			state = game_state::PAUSED;
			return;
		}

		asteroid_countdown -= delta_time;
		if(asteroid_countdown <= 0.0F) {
			set_rand_asteroid_wait();

			asteroid::create();
		}

		enemy_countdown -= delta_time;
		if(enemy_countdown <= 0.0F) {
			set_rand_enemy_wait();

			enemy::create();
		}

		scroll_bg(delta_time);
		ship->update(delta_time);
		asteroid::update_all(delta_time);
		laser::update_all(delta_time);
		explode::update_all(delta_time);
		enemy::update_all(delta_time);

		progress += delta_time / GAME_DURATION;
		if(progress >= 1.0F) {
			progress = 1.0F;
			end(true);
		}
	} else if(state == game_state::PAUSED) {
		if(rge::input::was_released(rge::input::KEY_ESC)) {
			state = game_state::IN_GAME;
			return;
		}
	} else if(state == game_state::END_SCREEN) {
		if(rge::input::was_released(rge::input::KEY_ESC)) {
			state = game_state::MAIN_MENU;
		}
	}
}

void game::on_render() {
	get_renderer()->clear(rge::color(0.063F, 0.071F, 0.11F));

	if(state == game_state::MAIN_MENU) {
		get_renderer()->draw(*title_sprite);
		get_renderer()->draw(*press_key_sprite_0);
	} else if(state == game_state::IN_GAME) {
		get_renderer()->draw(*bg_sprite_0);
		get_renderer()->draw(*bg_sprite_1);

		asteroid::draw_all();
		laser::draw_all();
		explode::draw_all();
		enemy::draw_all();
		ship->draw();

		progress_meter->transform->position = rge::vec3(-5.0F, -5.5F, LAYER_TO_Z(UI_LAYER));
		progress_meter->section = rge::rect(0, 0, 64 * progress, 4);
		progress_meter->material->diffuse = rge::color();
		get_renderer()->draw(*progress_meter);

		progress_meter->transform->position = rge::vec3(-5.0F + (64 * progress) / float(progress_meter->pixels_per_unit), -5.5F, LAYER_TO_Z(UI_LAYER));
		progress_meter->section = rge::rect(0, 0, 64 * (1.0F - progress), 4);
		progress_meter->material->diffuse = rge::color(0.173F, 0.118F, 0.192F);
		get_renderer()->draw(*progress_meter);

		float cooldown = ship->get_cooldown();

		cooldown_meter->transform->position = rge::vec3(-7.5F, -5.0F, LAYER_TO_Z(UI_LAYER));
		cooldown_meter->section = rge::rect(0, 0, 32 * cooldown, 4);
		cooldown_meter->material->diffuse = rge::color::lerp(rge::color(0, 0, 1), rge::color(1, 0, 0), cooldown);
		get_renderer()->draw(*cooldown_meter);

		cooldown_meter->transform->position = rge::vec3(-7.5F + (32 * cooldown) / float(cooldown_meter->pixels_per_unit), -5.0F, LAYER_TO_Z(UI_LAYER));
		cooldown_meter->section = rge::rect(0, 0, 32 * (1.0F - cooldown), 4);
		cooldown_meter->material->diffuse = rge::color(0.173F, 0.118F, 0.192F);
		get_renderer()->draw(*cooldown_meter);

	} else if(state == game_state::PAUSED) {
		get_renderer()->draw(*pause_sprite);
		get_renderer()->draw(*press_key_sprite_1);
	} else if(state == game_state::END_SCREEN) {
		if(did_win) {
			get_renderer()->draw(*win_sprite);
		} else {
			get_renderer()->draw(*lose_sprite);

			get_renderer()->draw(
				*meter,
				rge::vec2(0.1F, 0.3F),
				rge::vec2(rge::math::lerp(0.1F, 0.9F, progress), 0.35F)
			);

			get_renderer()->draw(
				*meter_bg,
				rge::vec2(rge::math::lerp(0.1F, 0.9F, progress), 0.3F),
				rge::vec2(0.9F, 0.35F)
			);
		}

		get_renderer()->draw(*press_key_sprite_1);
	}
}

void game::start_game() {
	state = game_state::IN_GAME;
	random = rge::random();
	bg_scroll_0 = 0.0F;
	bg_scroll_1 = 0.5F;
	did_win = false;
	progress = 0.0F;

	explode::destroy_all();
	laser::destroy_all();
	asteroid::destroy_all();
	enemy::destroy_all();

	set_rand_asteroid_wait();
	set_rand_enemy_wait();
	enemy::create();
	ship->reset();
}

void game::end(bool win) {
	did_win = win;
	state = game_state::END_SCREEN;
}

spaceship* game::get_ship() {
	return ship;
}

void game::scroll_bg(float delta_time) {
	bg_scroll_0 += delta_time * BG_SCROLL_SPEED;
	bg_scroll_1 += delta_time * BG_SCROLL_SPEED;
	if(bg_scroll_0 > 1) bg_scroll_0 -= 1;
	if(bg_scroll_1 > 1) bg_scroll_1 -= 1;

	bg_sprite_0->transform->position = rge::vec3(-8, rge::math::lerp(6, -18, bg_scroll_0), LAYER_TO_Z(BACKGROUND_LAYER));
	bg_sprite_1->transform->position = rge::vec3(-8, rge::math::lerp(6, -18, bg_scroll_1), LAYER_TO_Z(BACKGROUND_LAYER));
}

void game::set_rand_asteroid_wait() {
	asteroid_countdown = random.range(1.0F, 2.0F);
}

void game::set_rand_enemy_wait() {
	enemy_countdown = rge::math::lerp(2.0F, 0.0F, progress) + random.range(1.0F, 2.0F);
}

void game::draw_progress() {
	rge::vec2 min = rge::vec2(128.0F / get_renderer()->get_width(), 32.0F / get_renderer()->get_height());
	rge::vec2 max = min + rge::vec2(128.F / get_renderer()->get_width(), 16.0F / get_renderer()->get_height());
}