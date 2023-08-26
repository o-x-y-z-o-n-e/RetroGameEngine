#define RGE_IMPL
#define RGE_USE_STB_IMAGE_WRITE
#define RGE_USE_STB_IMAGE
#include <rge/rge.hpp>
#include <rge/ecs.hpp>

class game : public rge::engine {

private:
    ptr(rge::material) material;
    rge::camera* camera;
    rge::renderer3d* renderer;
    rge::render_target* render;

	std::vector<rge::vec3> model_verts;
    std::vector<int> model_tris;
	std::vector<rge::vec3> model_norms;
    std::vector<rge::vec2> model_uvs;

public:
    game() : rge::engine() {
        material = alloc(rge::material)();
        render = new rge::render_target(320, 200);
		camera = new rge::camera();
        renderer = new rge::renderer3d();
    }

    void on_init() override {
        //camera->set_perspective(60, 1.6F, 1.0F, 1000.0F);
		camera->set_orthographic(-16, 16, 10, -10, 0.0F, 100.0F);
        camera->transform->position = rge::vec3(0,0,0);
		camera->transform->rotation = rge::quaternion::euler(0, 0, 0);

        renderer->set_target(render);
        renderer->set_camera(camera);
		renderer->set_ambience(rge::color(0.2F, 0.2F, 0.2F));

		material->diffuse = rge::color(1, 0, 1);
        //material->texture = rge::texture::read_from_disk("tests/test.bmp");

        model_verts.push_back(rge::vec3(-1,0,0));
        model_verts.push_back(rge::vec3(0,2,0));
        model_verts.push_back(rge::vec3(1,0,0));

        model_tris.push_back(0);
        model_tris.push_back(1);
        model_tris.push_back(2);

        model_norms.push_back(rge::vec3(0,0,-1));
        model_norms.push_back(rge::vec3(0,0,-1));
        model_norms.push_back(rge::vec3(0,0,-1));

        model_uvs.push_back(rge::vec2(0,0));
        model_uvs.push_back(rge::vec2(0.5F,1));
        model_uvs.push_back(rge::vec2(1,0));
    }

    bool on_command(const std::string& cmd) override {
        if(cmd == "print") {
            rge::log::info("Render to file.");
            
			renderer->clear(rge::color(0.4F, 0.4F, 0.4F));

			renderer->draw(
				rge::mat4::trs(rge::vec3(0, 0, 2), rge::quaternion::euler(0, 45 * DEG_2_RAD, 0), rge::vec3(3, 1, 1)),
				model_verts,
				model_tris,
				model_norms,
				model_uvs,
				*material
			);
			
            /*
            rge::vec4 r_v1 = rge::vec4(4, 4, 0.0F, 0.0F);
			rge::vec4 r_v2 = rge::vec4(14, 12, 0.0F, 0.0F);
			rge::vec4 r_v3 = rge::vec4(12, 4, 0.0F, 0.0F);
			rge::vec3 w_v1 = rge::vec3(-1, 0, 5);
			rge::vec3 w_v2 = rge::vec3(0, 2, 5);
			rge::vec3 w_v3 = rge::vec3(1, 0, 5);
			rge::vec3 w_n1 = rge::vec3(0, 0, -1);
			rge::vec3 w_n2 = rge::vec3(0, 0, -1);
			rge::vec3 w_n3 = rge::vec3(0, 0, -1);
			rge::vec2 t_uv1 = rge::vec2(0.0F, 0.0F);
			rge::vec2 t_uv2 = rge::vec2(0.5F, 1.0F);
			rge::vec2 t_uv3 = rge::vec2(1.0F, 0.0F);
			renderer->draw_interpolated_triangle(
				r_v1, r_v2, r_v3,
				w_v1, w_v2, w_v3,
				w_n1, w_n2, w_n3,
				t_uv1, t_uv2, t_uv3,
				*material
			);
            */

			render->get_frame_buffer()->write_to_disk("tests/render.bmp");
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
    
	if(gm->init() != rge::OK)
		goto error_quit;

	if(gm->start(false, &thread) != rge::OK)
		goto error_quit;

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

error_quit:
	if(gm) delete gm;
	printf("RGE crashed!\n");
	return 1;
}