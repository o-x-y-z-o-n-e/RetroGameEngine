#define WIN_MAIN
#include "rge.h"

#include "gb/gb.h"

#define AUTHORS "Jeremy Kiel"
#define VERSION "0.1.0"


//---------------------------------------------------------------------------------------------------


uint8_t DEBUG_MODE;


//---------------------------------------------------------------------------------------------------


static void on_core_tick(int ticks) {
	gb_step(ticks);
}


//---------------------------------------------------------------------------------------------------


static int check_arg(const char* input, const char* one, const char* two) {
	int i = 0;
	while(1) {
		if(input[i] == '\0' && one[i] == '\0')
			return 1;

		if(input[i] == '\0' || one[i] == '\0' || input[i] != one[i])
			break;

		i++;
	}

	i = 0;

	while(1) {
		if(input[i] == '\0' && two[i] == '\0')
			return 1;

		if(input[i] == '\0' || two[i] == '\0' || input[i] != two[i])
			break;

		i++;
	}

	return 0;
}


//---------------------------------------------------------------------------------------------------


int main(int argc, char* argv[]) {
	char* file_path = NULL;

	for(int i = 1; i < argc; i++) {
		if(check_arg(argv[i], "-v", "-version") || check_arg(argv[i], "--v", "--version") ||
		   check_arg(argv[i], "-i", "-info") || check_arg(argv[i], "--i", "--info")) {
			rge_log_info("MyGameBoy");
			rge_log_info("Version: %s", VERSION);
			rge_log_info("Authors: %s", AUTHORS);
			return 0;
		}

		if(check_arg(argv[i], "-d", "-debug") || check_arg(argv[i], "--d", "--debug")) {
			DEBUG_MODE = 1;
			continue;
		}

		file_path = argv[i];
	}

	if(!rge_core_init()) {
		rge_log_error("Could not initialize core!");
		return 0;
	}

	if(file_path == NULL) {
		rge_log_error("Pass path to game cartridge file.");
		return 1;
	}

	if(gb_init() != 0) {
		rge_log_error("Failed to initailize GB core");
		return 1;
	}

	if(gb_load(argv[1]) != 0) {
		rge_log_error("Failed to load GB rom");
		return 1;
	}

	rge_window_set_title("MyGameBoy");
	rge_view_set_background(COLOR_RGB(255, 255, 255));
	rge_renderer_auto_set(false);
	rge_view_set_size(160, 144);
	rge_core_set_on_tick(gb_step);
	
	rge_core_start();

	gb_close();

	return 0;
}