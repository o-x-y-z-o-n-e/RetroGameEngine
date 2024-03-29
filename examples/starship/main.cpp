#define RGE_IMPL
#define RGE_USE_STB_IMAGE
#include "rge.hpp"
#include "game.hpp"

/* TODO:
	==SPRITES==
	Pause Screen
	Progress Meter
	Explode
	Enemy 1
	Enemy 2
	Enemy 3
	==CODE==
	Pause State
	Progress Meter
	Enemy 1
	Enemy 2
	Enemy 3
*/

int main(int argc, char** argv) {
	game* gm = rge::engine::create<game>();
	gm->run();
	gm->wait_for_exit();
	delete gm;
	return 0;
}