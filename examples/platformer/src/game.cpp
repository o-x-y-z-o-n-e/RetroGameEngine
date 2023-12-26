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
	camera->transform->position = rge::vec3(15*8, 10*8, -1);
	get_renderer()->set_camera(camera);
	
	render = get_renderer()->create_render_target(FRAME_WIDTH, FRAME_HEIGHT);
}

void game::on_start() {
	world_obj = new world();
}

void game::on_update(float delta_time) {
	
}

void game::on_render() {
	/* Draw world. */ {
		get_renderer()->set_target(render);
		get_renderer()->clear(BACKGROUND);

		if(WORLD_EXISTS) {
			get_world()->get_level()->get_area()->draw();
			get_world()->get_player()->draw();
		}
	}

	/* Draw render to screen. */ {
		float h_ratio = float(get_renderer()->get_width()) / float(FRAME_WIDTH);
		float v_ratio = float(get_renderer()->get_height()) / float(FRAME_HEIGHT);
		int v_reduction = 0;
		int h_reduction = 0;

		if(h_ratio < v_ratio) {
			v_reduction = get_renderer()->get_height() - int(FRAME_HEIGHT * h_ratio);
		} else {
			h_reduction = get_renderer()->get_width() - int(FRAME_WIDTH * v_ratio);
		}

		int top = v_reduction / 2;
		int bottom = get_renderer()->get_height() - (v_reduction - top);

		int left = h_reduction / 2;
		int right = get_renderer()->get_width() - (h_reduction - left);

		get_renderer()->set_target(nullptr);
		get_renderer()->draw(*render, left, top, right, bottom);
	}
}