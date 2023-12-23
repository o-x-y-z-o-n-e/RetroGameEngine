#include "game.hpp"

game::game() : rge::engine() {
	
}

void game::get_default_window_params(std::string& title, int& width, int& height, bool& fullscreen) {
	title = "Platformer";
	width = 800;
	height = 600;
	fullscreen = false;
}

void game::on_init() {
	
}

void game::on_start() {
	
}

void game::on_update(float delta_time) {
	
}

void game::on_render() {
	get_renderer()->clear(rge::color(0.063F, 0.071F, 0.11F));
}