#include "rge.h"
#include "game.h"
#include "ship.h"


//------------------------------------------------------------------------------


static bool in_level;


//------------------------------------------------------------------------------


void game_update(float delta) {
	if(in_level) {
		ship_update(delta);
	}
}


//------------------------------------------------------------------------------


void game_load_title() {
	rge_scene_clear();

	in_level = false;
}


//------------------------------------------------------------------------------


void game_load_level(int i) {
	rge_scene_clear();

	in_level = true;

	ship_init();
}