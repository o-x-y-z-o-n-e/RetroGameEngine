#define WIN_MAIN
#include "engine.h"
#include "scene.h"

const float CAM_SPEED = 50;

static float cam_pos_x = 0;
static float cam_pos_y = 0;


//------------------------------------------------------------------------------


static void on_core_update(float delta) {
	if(is_button_press(KEY_LEFT)) {
		cam_pos_x -= CAM_SPEED * delta;
	}

	if(is_button_press(KEY_RIGHT)) {
		cam_pos_x += CAM_SPEED * delta;
	}

	if(is_button_press(KEY_UP)) {
		cam_pos_y += CAM_SPEED * delta;
	}

	if(is_button_press(KEY_DOWN)) {
		cam_pos_y -= CAM_SPEED * delta;
	}

	//set_camera_location(float_to_point(cam_pos_x, cam_pos_y));

	update_my_scene(delta);
}


//------------------------------------------------------------------------------


int main() {
	log_info("Example Starting...");

	if(!init_core()) {
		log_error("Could not initialize core!");
		return 0;
	}

	set_title_window("Example App");
	set_on_core_update(on_core_update);
	set_clear_color(COLOR_RGB(255, 255, 255));

	setup_my_scene();

	start_core();

	return 0;
}