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

	float counter;

public:
    game() : rge::engine() {
        material = alloc(rge::material)();
		render = nullptr;
		camera = new rge::camera();
        renderer = new rge::renderer3d();
		counter = 0;
    }

    void on_init() override {
		render = get_window()->get_render_target();
		// render = new rge::render_target(320, 200);

        // camera->set_perspective(60, 1.6F, 1.0F, 1000.0F);
		camera->set_orthographic(-16, 16, 10, -10, 0.0F, 100.0F);
        camera->transform->position = rge::vec3(0,0,0);
		camera->transform->rotation = rge::quaternion::euler(0, 0, 0);

        renderer->set_target(render);
        renderer->set_camera(camera);
		renderer->set_ambience(rge::color(0.2F, 0.2F, 0.2F));

		material->diffuse = rge::color(1, 0, 1);
        // material->texture = rge::texture::read_from_disk("tests/test.bmp");

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

	void on_update(float delta_time) override {
		counter += delta_time;
		if(counter > 1)
			counter = 0;
	}

    void on_render() override {
		renderer->clear(rge::color(0.4F, 0.4F, 0.4F));

		renderer->draw(
			rge::mat4::trs(rge::vec3(0, 0, 2), rge::quaternion::euler(0, counter * 45 * DEG_2_RAD, 0), rge::vec3(3, 1, 1)),
			model_verts,
			model_tris,
			model_norms,
			model_uvs,
			*material
		);

		/* TODO: Implement rge::renderer2d
		int width, height;
		get_window()->get_size(width, height);
		get_window()->get_compositor()->draw(*render, rge::rect(0, 0, width, height));
		*/
    }
};


int main(int argc, char** argv) {
    game* gm = new game();
	gm->create(false);

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

	gm->wait_for_exit();
	delete gm;
    return 0;
}