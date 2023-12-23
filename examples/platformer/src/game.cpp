#include "game.hpp"

game::game() : rge::engine() {
	world_obj = nullptr;
	camera = nullptr;
	render = nullptr;
}

void game::get_default_window_params(std::string& title, int& width, int& height, bool& fullscreen) {
	title = "Platformer";
	width = 800;
	height = 600;
	fullscreen = false;
}

void game::on_init() {
	camera = rge::camera::create();
	camera->set_orthographic(0, 100, FRAME_HEIGHT);
	get_renderer()->set_camera(camera);
	
	render = get_renderer()->create_render_target(FRAME_WIDTH, FRAME_HEIGHT);
}

void game::on_start() {
	world_obj = new world();
}

void game::on_update(float delta_time) {
	
}

void game::on_render() {
	get_renderer()->set_target(render);
	get_renderer()->clear(BACKGROUND);

	if(WORLD_EXISTS) {
		get_world()->get_level()->get_area()->draw();
		get_world()->get_player()->draw();
	}

	get_renderer()->set_target(nullptr);
	get_renderer()->draw(*render);
}