#define RGE_IMPL
#define RGE_STB_IMAGE_ENABLED
#include "game.hpp"

/*
==CODE==
player idle
player basic move
tile collision
*/

int main(int argc, char** argv) {
	game* gm = rge::engine::create<game>();
	gm->run();
	gm->wait_for_exit();
	delete gm;
	return 0;
}