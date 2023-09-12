#include "game.hpp"

const float BG_SCROLL_SPEED = 0.25F;

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
	camera->set_orthographic(-8, 8, 6, -6, 0.0F, 100.0F);
	camera->transform->position = rge::vec3(0, 0, -1);

	get_renderer()->set_camera(camera);

	ship = new spaceship();

	bg_texture = rge::texture::load("res/background.png");
	bg_sprite_0 = rge::sprite::create();
	bg_sprite_0->texture = bg_texture;
	bg_sprite_0->pixels_per_unit = 16;
	bg_sprite_1 = rge::sprite::create();
	bg_sprite_1->texture = bg_texture;
	bg_sprite_1->pixels_per_unit = 16;
}

void game::on_start() {
	state = game_state::IN_GAME;
	bg_scroll_0 = 0.0F;
	bg_scroll_1 = 0.5F;
}

void game::on_update(float delta_time) {
	if(state == game_state::MAIN_MENU) {

	} else if(state == game_state::IN_GAME) {
		scroll_bg(delta_time);
		ship->update(delta_time);
	} else if(state == game_state::END_SCREEN) {
		
	}
}

void game::on_render() {
	get_renderer()->clear(rge::color(0.2F, 0.2F, 0.2F));

	if(state == game_state::MAIN_MENU) {

	} else if(state == game_state::IN_GAME) {
		get_renderer()->draw(*bg_sprite_0);
		get_renderer()->draw(*bg_sprite_1);
		ship->draw();
	} else if(state == game_state::END_SCREEN) {

	}
}

void game::scroll_bg(float delta_time) {
	bg_scroll_0 += delta_time * BG_SCROLL_SPEED;
	bg_scroll_1 += delta_time * BG_SCROLL_SPEED;
	if(bg_scroll_0 > 1) bg_scroll_0 -= 1;
	if(bg_scroll_1 > 1) bg_scroll_1 -= 1;

	bg_sprite_0->transform->position = rge::vec3(-8, rge::math::lerp(6, -18, bg_scroll_0), 1);
	bg_sprite_1->transform->position = rge::vec3(-8, rge::math::lerp(6, -18, bg_scroll_1), 1);
}
