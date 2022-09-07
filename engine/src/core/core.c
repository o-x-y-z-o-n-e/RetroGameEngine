#include "core/core.h"
#include "core/input.h"
#include "platform/system.h"
#include "platform/window.h"
#include "video/renderer.h"
#include "video/texture.h"
#include "world/scene.h"
#include "util/debug.h"

#include <stdlib.h>
#include <math.h>

#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"


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

	if(!init_system())
		return 0;

	if(!create_window())
		return 0;

	if(!init_renderer())
		return 0;

	if(!init_textures())
		return 0;

	if(!init_scene())
		return 0;

	has_init = 1;

	// TEST
	lua_State* L = luaL_newstate();

	int r = luaL_dostring(L, "a = 7 + 11");

	if(r == LUA_OK) {
		lua_getglobal(L, "a");
		if(lua_isnumber(L, -1)) {
			int a = (int)lua_tonumber(L, -1);
			log_info("a = %d", a);
		} else {
			log_error("a is not number");
		}
	} else {
		log_error("Lua failed");
	}
	// TEST

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

			flush_click_input();
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


void crash_core(int error) {
	log_error("Critical crash. Error code: [%d]", error);
	exit(0);
}