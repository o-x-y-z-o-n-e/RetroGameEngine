#define RGE_IMPL
#define RGE_USE_STB_IMAGE_WRITE
#include <rge.hpp>

class game : public rge::engine {

private:
    rge::material material;
    rge::camera camera;
    rge::renderer3d renderer;
    rge::render_target* render;

    std::vector<rge::vec3> model_verts;
    std::vector<int> model_tris;
	std::vector<rge::vec3> model_norms;
    std::vector<rge::vec2> model_uvs;

public:
    game() : rge::engine() {
        material = rge::material();
        render = new rge::render_target(320, 200);
        camera = rge::camera();
        renderer = rge::renderer3d();

        model_verts = std::vector<rge::vec3>(3);
        model_tris = std::vector<int>(3);
        model_norms = std::vector<rge::vec3>(3);
        model_uvs = std::vector<rge::vec2>(3);
    }

    void on_init() override {
        renderer.set_target(render);
        renderer.set_camera(&camera);

        camera.transform->position = rge::vec3(0,0,-10);

        model_verts.push_back(rge::vec3(-1,0,0));
        model_verts.push_back(rge::vec3(0,2,0));
        model_verts.push_back(rge::vec3(1,0,0));

        model_tris.push_back(0);
        model_tris.push_back(1);
        model_tris.push_back(2);

        model_norms.push_back(rge::vec3(0,0,1));
        model_norms.push_back(rge::vec3(0,0,1));
        model_norms.push_back(rge::vec3(0,0,1));

        model_uvs.push_back(rge::vec2(0,0));
        model_uvs.push_back(rge::vec2(0.5F,1));
        model_uvs.push_back(rge::vec2(1,0));

        material.diffuse = rge::color(1,0,0);
    }

    bool on_command(const std::string& cmd) override {
        if(cmd == "print") {
            rge::log::info("Render to file.");
            render->write_to_disk("render.png");
            return true;
        }
		return false;
    }

    void on_render() override {
        renderer.clear(rge::color(0, 1, 0));
		
        
        renderer.draw(
            rge::mat4::identity(),
            model_verts,
            model_tris,
            model_norms,
            model_uvs,
            material
        );
    }
    
};

int main(int argc, char** argv) {
    std::thread* thread;
    game* gm = new game();
    
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