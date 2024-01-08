#include "game.hpp"

game::game() : rge::engine() {
	world_obj = nullptr;
	camera = nullptr;
	render = nullptr;
}

void game::get_default_window_params(std::string& title, int& width, int& height, bool& fullscreen) {
	title = "Platformer";
	width = 1920;
	height = 1080;
	fullscreen = false;
}

void game::on_init() {
	camera = rge::camera::create();
	camera->set_orthographic(0.0F, 100.0F, -FRAME_WIDTH / 2, FRAME_WIDTH / 2, FRAME_HEIGHT / 2, -FRAME_HEIGHT / 2);
	camera->transform->position = rge::vec3(15*8, 10*8, -0.5F);
	camera->transform->rotation = rge::quaternion::identity();
	get_renderer()->set_camera(camera);
	
	render = get_renderer()->create_render_target(FRAME_WIDTH, FRAME_HEIGHT);
}

void game::on_start() {
	world_obj = new world();
}

void game::on_update(float delta_time) {
	if(!WORLD_EXISTS) return;

	if(rge::input::was_pressed(rge::input::KEY_ESC)) {
		exit();
		return;
	}

	get_world()->get_player()->update(delta_time);
}

void game::on_render() {
	rge::renderer::ptr renderer = get_renderer();

	renderer->set_target(render);
	renderer->clear(BACKGROUND);

	if(WORLD_EXISTS) {
		get_world()->get_level()->get_area()->draw();
		get_world()->get_player()->draw();
	}

	renderer->set_target(nullptr);
	renderer->draw(*render, true, true);
}