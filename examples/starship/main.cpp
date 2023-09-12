#define RGE_IMPL
#define RGE_USE_STB_IMAGE
#include "rge.hpp"
#include "game.hpp"

/* Assets Needed:
	==SPRITES==
	Title
	"Press any key to start"
	"Press any key to play again"
	"End Reached"
	"You Died"
	Progress Meter
	Scrolling Background
	Spaceship + flame anim
	Plasma Bolt
	Explode
	Asteroid 1
	Asteroid 2
	Asteroid 3
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