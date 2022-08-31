#include "core/core.h"
#include "platform/system.h"
#include "platform/window.h"
#include "video/renderer.h"
#include "video/texture.h"
#include "world/scene.h"
#include "util/debug.h"

#include <stdlib.h>

#include <math.h>

const float RENDER_FPS_TARGET = 1.0F / 60;

static char has_init = 0;
static char is_running = 0;
static uint64_t last_time = 0;
static float render_counter = 0;

static void (*on_core_update)(float delta);


//------------------------------------------------------------------------------


int init_core() {
	if(has_init) {
		log_error("Core has already been initialized");
		return 0;
	}

	if(!create_window())
		return 0;

	if(!init_renderer())
		return 0;

	if(!init_textures())
		return 0;

	if(!init_scene())
		return 0;

	has_init = 1;

	return 1;
}


//------------------------------------------------------------------------------


void start_core() {
	if(!has_init) {
		log_error("Core has not been initialized");
		return;
	}

	if(is_running) {
		log_error("Core is already running");
		return;
	}

	is_running = 1;

	last_time = get_current_time();
	while(is_running) {
		poll_window_events();

		uint64_t current_time = get_current_time();
		uint64_t delta_time = current_time - last_time;

		if(delta_time > 0) {
			last_time = current_time;
			float delta = ((float)delta_time) * 0.001F;

			if(on_core_update != NULL)
				on_core_update(delta);

			update_scene(delta);

			render_counter += delta;
			if(render_counter > RENDER_FPS_TARGET) {
				render_counter -= RENDER_FPS_TARGET;

				draw_all();
			}
		}
	}
}


//------------------------------------------------------------------------------


void close_core() {
	if(!has_init) {
		log_error("Core has not been initialized");
		return;
	}

	if(!is_running) {
		log_error("Core is no running");
		return;
	}

	is_running = 0;

	exit(0);
}


//------------------------------------------------------------------------------


void set_on_core_update(void (*func)(float delta)) {
	on_core_update = func;
}


//------------------------------------------------------------------------------


void crash(int error) {
	log_error("Critical crash. Error code: [%d]", error);
	exit(0);
}