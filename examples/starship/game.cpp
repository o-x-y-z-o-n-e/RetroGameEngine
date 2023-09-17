#include "game.hpp"

const float BG_SCROLL_SPEED = 0.25F;
const float GAME_DURATION = 60*5;

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
	title_sprite->transform->position = rge::vec3(0, 0, -UI_LAYER);

	win_sprite = rge::sprite::create();
	win_sprite->texture = rge::texture::load("res/won.png");
	win_sprite->pixels_per_unit = 16;
	win_sprite->centered = true;
	win_sprite->transform->position = rge::vec3(0, 0, -UI_LAYER);

	lose_sprite = rge::sprite::create();
	lose_sprite->texture = rge::texture::load("res/lost.png");
	lose_sprite->pixels_per_unit = 16;
	lose_sprite->centered = true;
	lose_sprite->transform->position = rge::vec3(0, 0, -UI_LAYER);

	pause_sprite = rge::sprite::create();
	pause_sprite->texture = rge::texture::load("res/pause.png");
	pause_sprite->pixels_per_unit = 16;
	pause_sprite->centered = true;
	pause_sprite->transform->position = rge::vec3(0, 0, -UI_LAYER);

	press_key_sprite_0 = rge::sprite::create();
	press_key_sprite_0->texture = rge::texture::load("res/press_any_key_to_start.png");
	press_key_sprite_0->pixels_per_unit = 16;
	press_key_sprite_0->centered = true;
	press_key_sprite_0->transform->position = rge::vec3(0, -4, -UI_LAYER);

	press_key_sprite_1 = rge::sprite::create();
	press_key_sprite_1->texture = rge::texture::load("res/press_esc_key_to_return.png");
	press_key_sprite_1->pixels_per_unit = 16;
	press_key_sprite_1->centered = true;
	press_key_sprite_1->transform->position = rge::vec3(0, -4, -UI_LAYER);

	bg_sprite_0 = rge::sprite::create();
	bg_sprite_0->texture = rge::texture::load("res/background.png");
	bg_sprite_0->pixels_per_unit = 16;
	bg_sprite_1 = rge::sprite::create();
	bg_sprite_1->texture = rge::texture::load("res/background.png");
	bg_sprite_1->pixels_per_unit = 16;

	meter = rge::texture::create(1, 1);
	meter->allocate();
	meter->get_data()[0] = rge::color(1, 1, 1);
	get_renderer()->upload_texture(*meter);
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

		scroll_bg(delta_time);
		ship->update(delta_time);
		asteroid::update_all(delta_time);
		laser::update_all(delta_time);
		explode::update_all(delta_time);

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
	get_renderer()->clear(rge::color(0.2F, 0.2F, 0.2F));

	if(state == game_state::MAIN_MENU) {
		get_renderer()->draw(*title_sprite);
		get_renderer()->draw(*press_key_sprite_0);
	} else if(state == game_state::IN_GAME) {
		get_renderer()->draw(*bg_sprite_0);
		get_renderer()->draw(*bg_sprite_1);

		asteroid::draw_all();
		laser::draw_all();
		explode::draw_all();
		ship->draw();
	} else if(state == game_state::PAUSED) {
		get_renderer()->draw(*pause_sprite);
		get_renderer()->draw(*press_key_sprite_1);
	} else if(state == game_state::END_SCREEN) {
		if(did_win) {
			get_renderer()->draw(*win_sprite);
		} else {
			get_renderer()->draw(*lose_sprite);

			progress = 0.5F;
			get_renderer()->draw(*meter, rge::vec2(0.01F, 0.01F), rge::vec2(0.04F, rge::math::lerp(0.01F, 0.99F, progress)));
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

	set_rand_asteroid_wait();
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

	bg_sprite_0->transform->position = rge::vec3(-8, rge::math::lerp(6, -18, bg_scroll_0), -BACKGROUND_LAYER);
	bg_sprite_1->transform->position = rge::vec3(-8, rge::math::lerp(6, -18, bg_scroll_1), -BACKGROUND_LAYER);
}

void game::set_rand_asteroid_wait() {
	asteroid_countdown = random.range(1.0F, 2.0F);
}
