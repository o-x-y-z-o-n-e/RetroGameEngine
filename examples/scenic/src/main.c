#define WIN_MAIN
#include "rge.h"
#include "scene.h"

const float CAM_SPEED = 50;

static float cam_pos_x = 0;
static float cam_pos_y = 0;


//------------------------------------------------------------------------------


static void on_core_update(float delta) {
	if(rge_input_is_press(RGE_KEY_LEFT)) {
		cam_pos_x -= CAM_SPEED * delta;
	}

	if(rge_input_is_press(RGE_KEY_RIGHT)) {
		cam_pos_x += CAM_SPEED * delta;
	}

	if(rge_input_is_press(RGE_KEY_UP)) {
		cam_pos_y += CAM_SPEED * delta;
	}

	if(rge_input_is_press(RGE_KEY_DOWN)) {
		cam_pos_y -= CAM_SPEED * delta;
	}

	//set_camera_location(float_to_point(cam_pos_x, cam_pos_y));

	update_my_scene(delta);
}


//------------------------------------------------------------------------------


int main() {
	rge_log_info("Example Starting...");

	if(!rge_core_init()) {
		rge_log_error("Could not initialize core!");
		return 0;
	}

	rge_window_set_title("Example App");
	rge_core_set_on_update(on_core_update);
	rge_view_set_background(COLOR_RGB(255, 255, 255));

	setup_my_scene();

	rge_core_start();

	return 0;
}