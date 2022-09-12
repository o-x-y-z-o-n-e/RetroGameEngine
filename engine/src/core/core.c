#include "api/rge.h"
#include "core/core.h"
#include "core/input.h"
#include "core/scene.h"
#include "core/renderer.h"
#include "core/audio_player.h"
#include "core/asset_manager.h"
#include "core/script_manager.h"
#include "platform/system.h"
#include "platform/window.h"

#include <stdlib.h>


//------------------------------------------------------------------------------


const float RENDER_FPS_TARGET = 1.0F / 60;

static char has_init = 0;
static char is_running = 0;
static uint64_t last_time = 0;
static float render_counter = 0;

static void (*on_core_update)(float delta);


//------------------------------------------------------------------------------


int rge_core_init() {
	if(has_init) {
		rge_log_error("Core has already been initialized");
		return 0;
	}

	if(!rge_system_init())
		return 0;

	if(!rge_window_create())
		return 0;

	if(!rge_renderer_init())
		return 0;

	if(!rge_audio_init())
		return 0;

	if(!rge_assets_init())
		return 0;

	if(!rge_scene_init())
		return 0;

	if(!rge_script_init())
		return 0;

	has_init = 1;

	return 1;
}


//------------------------------------------------------------------------------


void rge_core_start() {
	if(!has_init) {
		rge_log_error("Core has not been initialized");
		return;
	}

	if(is_running) {
		rge_log_error("Core is already running");
		return;
	}

	is_running = 1;

	last_time = rge_system_get_time();
	while(is_running) {
		rge_window_poll_events();

		uint64_t current_time = rge_system_get_time();
		uint64_t delta_time = current_time - last_time;

		if(delta_time > 0) {
			last_time = current_time;
			float delta = ((float)delta_time) * 0.001F;

			if(on_core_update != NULL)
				on_core_update(delta);

			rge_scene_update(delta);

			render_counter += delta;
			if(render_counter > RENDER_FPS_TARGET) {
				render_counter -= RENDER_FPS_TARGET;

				rge_renderer_draw_all();
			}

			rge_input_flush_click();
		}
	}
}


//------------------------------------------------------------------------------


void rge_core_close() {
	if(!has_init) {
		rge_log_error("Core has not been initialized");
		return;
	}

	if(!is_running) {
		rge_log_error("Core is no running");
		return;
	}

	is_running = 0;

	exit(0);
}


//------------------------------------------------------------------------------


void rge_core_set_on_update(void (*func)(float delta)) {
	on_core_update = func;
}


//------------------------------------------------------------------------------


void rge_core_crash(int error) {
	rge_log_error("Critical crash. Error code: [%d]", error);
	exit(0);
}