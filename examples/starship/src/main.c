#define WIN_MAIN
#include "rge.h"
#include "game.h"


//------------------------------------------------------------------------------


int main() {
	rge_log_info("Starship Starting...");

	if(!rge_core_init()) {
		rge_log_error("Could not initialize core!");
		return 0;
	}

	rge_window_set_title("Example App");
	rge_view_set_size(WINDOW_WIDTH, WINDOW_HEIGHT);
	rge_view_set_background(COLOR_RGB(16, 16, 16));

	rge_core_set_on_update(game_update);

	// game_load_title();
	game_load_level(0);

	rge_core_start();

	return 0;
}