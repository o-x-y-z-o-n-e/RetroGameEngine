#define WIN_MAIN
#include "rge.h"
#include "cpu.h"


//------------------------------------------------------------------------------


int main() {
	rge_log_info("CHIP-8 Starting...");

	if(!rge_init()) {
		rge_log_error("Could not initialize core!");
		return 0;
	}

	rge_window_set_title("CHIP-8");
	rge_set_on_tick(cpu_tick);
	rge_set_on_update(NULL);
	rge_set_on_render(NULL);
	rge_view_set_background(COLOR_RGB(0, 0, 0));
	rge_view_set_size(64, 32);

	if(!cpu_init()) {
		rge_log_error("Could not initialize cpu!");
		return 0;
	}

	rge_start();

	return 0;
}