#define RGE_IMPL
#define RGE_STB_IMAGE_ENABLED
#include "game.hpp"

/*

==SPRITES==
wall.png

==CODE==
setup example tile_map
collide & slide entity with tile_map
player physics

*/

int main(int argc, char** argv) {
	game* gm = rge::engine::create<game>();
	gm->run();
	gm->wait_for_exit();
	delete gm;
	return 0;
}