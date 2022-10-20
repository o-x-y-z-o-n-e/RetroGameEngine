#define WIN_MAIN
#include "rge.h"

int main() {
	rge_log_info("Starship Starting...");

	if(!rge_core_init()) {
		rge_log_error("Could not initialize core!");
		return 0;
	}

	rge_window_set_title("Example App");
	rge_view_set_background(COLOR_RGB(255, 255, 255));

	rge_core_start();

	return 0;
}