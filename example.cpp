#define RGE_IMPL
#define RGE_USE_STB_IMAGE_WRITE
#include <rge.hpp>

class game : public rge::engine {

private:
    rge::material* material;
    rge::camera* camera;
    rge::renderer3d* renderer;
    rge::render_target* render;

	std::vector<rge::vec3> model_verts;
    std::vector<int> model_tris;
	std::vector<rge::vec3> model_norms;
    std::vector<rge::vec2> model_uvs;

public:
    game() : rge::engine() {
        material = new rge::material();
        render = new rge::render_target(16, 16);
		camera = new rge::camera();
        renderer = new rge::renderer3d();
    }

    void on_init() override {
        renderer->set_target(render);
        renderer->set_camera(camera);
		renderer->set_ambience(rge::color(0.2F, 0.2F, 0.2F));

        camera->transform->position = rge::vec3(0,0,0);
		material->diffuse = rge::color(1, 0, 0);

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

        
    }

    bool on_command(const std::string& cmd) override {
        if(cmd == "print") {
            rge::log::info("Render to file.");
            
			renderer->clear(rge::color(0.4F, 0.4F, 0.4F));

			rge::vec4 r_v1 = rge::vec4(2, 0, 0.0F, 0.0F);
			rge::vec4 r_v2 = rge::vec4(8, 16, 0.0F, 0.0F);
			rge::vec4 r_v3 = rge::vec4(16, 0, 0.0F, 0.0F);
			rge::vec3 w_v1 = rge::vec3(-1, 0, 5);
			rge::vec3 w_v2 = rge::vec3(0, 2, 5);
			rge::vec3 w_v3 = rge::vec3(1, 0, 5);
			rge::vec3 w_n1 = rge::vec3(0, 0, -1);
			rge::vec3 w_n2 = rge::vec3(0, 0, -1);
			rge::vec3 w_n3 = rge::vec3(0, 0, -1);
			rge::vec2 t_uv1 = rge::vec2(0.0F, 0.0F);
			rge::vec2 t_uv2 = rge::vec2(0.5F, 1.0F);
			rge::vec2 t_uv3 = rge::vec2(1.0F, 0.0F);

			/*
			renderer.draw(
				rge::mat4::identity(),
				model_verts,
				model_tris,
				model_norms,
				model_uvs,
				material
			);
			*/

			renderer->draw_interpolated_triangle(
				r_v1, r_v2, r_v3,
				w_v1, w_v2, w_v3,
				w_n1, w_n2, w_n3,
				t_uv1, t_uv2, t_uv3,
				*material
			);

			render->write_to_disk("render.png");
            return true;
        }
		return false;
    }

    void on_render() override {
        
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