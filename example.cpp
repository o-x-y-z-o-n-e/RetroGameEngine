#define RGE_IMPL
#include "rge.hpp"

int main() {
    std::thread* thread;
    rge::engine* game = new rge::engine;

    game->init();
    game->start(false, &thread);

    while(game->get_is_running()) {
        std::string cmd;
        std::getline(std::cin, cmd);
        

        if(!game->get_is_running())
            break;

        if(game->command(cmd)) {
            rge::log::info("Test");
        } else {
            rge::log::error("Unknown command!");
        }
    }

    thread->join();

    return 0;
}