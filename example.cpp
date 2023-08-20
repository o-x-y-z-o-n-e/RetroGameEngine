#define RGE_IMPL
#include "rge.hpp"

class game : public rge::engine {

private:
    rge::renderer2d* renderer;

    void on_init() override {
        renderer = new rge::renderer2d;
        renderer->set_target(nullptr);
    }

    bool on_command(const std::string& cmd) override {
        if(cmd == "hello") {
            rge::log::info("why hello there!");
            return true;
        }
    }

    void on_render() override {
        
    }
    
};

int main() {
    std::thread* thread;
    game* gm = new game;
    
    gm->init();
    gm->start(false, &thread);

    while(gm->get_is_running()) {
        std::string cmd;
		std::cout << "> ";
        std::getline(std::cin, cmd);
        
        if(!gm->get_is_running())
            break;

        if(gm->command(cmd) == rge::FAIL) {
            rge::log::error("Unknown command!");
        }
    }

    thread->join();

    return 0;
}