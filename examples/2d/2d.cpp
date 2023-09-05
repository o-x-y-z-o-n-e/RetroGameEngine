#define RGE_IMPL
#define RGE_USE_STB_IMAGE_WRITE
#define RGE_USE_STB_IMAGE
#include "rge.hpp"

#include <iostream>
#include <fstream>

static rge::mesh* load_triangle() {
	rge::mesh* mdl = new rge::mesh;

	mdl->vertices.push_back(rge::vec3(-1, -1, 0));
	mdl->vertices.push_back(rge::vec3(0, 1, 0));
	mdl->vertices.push_back(rge::vec3(1, -1, 0));

	mdl->normals.push_back(rge::vec3(0, 0, 1));
	mdl->normals.push_back(rge::vec3(0, 0, 1));
	mdl->normals.push_back(rge::vec3(0, 0, 1));

	mdl->triangles.push_back(0);
	mdl->triangles.push_back(2);
	mdl->triangles.push_back(1);

	mdl->uvs.push_back(rge::vec2(0, 0));
	mdl->uvs.push_back(rge::vec2(0.5F, 1.0F));
	mdl->uvs.push_back(rge::vec2(1, 0));

	return mdl;
}

class game : public rge::engine {
private:
    rge::material* material;
	rge::renderer* renderer;
    rge::camera* camera;
	rge::sprite* smile;
	rge::sprite* background;
	rge::mesh* triangle;
	float counter;

public:
    game() : rge::engine() {
        material = new rge::material();
		camera = new rge::camera();
		smile = new rge::sprite();
		background = new rge::sprite();
		triangle = nullptr;
		counter = 0;
    }

    void on_init() override {
		renderer = get_renderer();

		triangle = load_triangle();

		background->texture = rge::texture::read_from_disk("background.png");
		background->transform->position = rge::vec3(0, 0, 1);
		background->pixels_per_unit = 16;
		renderer->upload_texture(background->texture);

		smile->texture = rge::texture::read_from_disk("smile.bmp");
		smile->pixels_per_unit = 16;
		smile->centered = true;
		renderer->upload_texture(smile->texture);

		camera->set_orthographic(-8, 8, 6, -6, 0.0F, 100.0F);
		camera->transform->position = rge::vec3(0, 0, -1);

        renderer->set_camera(camera);
		renderer->set_ambience(rge::color(0.2F, 0.2F, 0.2F));

		rge::texture* test_tex = rge::texture::read_from_disk("smile.bmp");
		renderer->upload_texture(test_tex);

		material->diffuse = rge::color(1, 0, 1);
		material->texture = test_tex;
    }

	void on_update(float delta_time) override {
		counter += delta_time;
		if(counter > PI * 2)
			counter = 0;

		smile->transform->position = rge::vec3(cosf(counter) * 3.0F, sinf(counter) * 3.0F, 0.0F);

		{
			rge::vec3 velocity = rge::vec3(rge::input::get_axis(rge::input::GAMEPAD_LEFT_STICK_X), rge::input::get_axis(rge::input::GAMEPAD_LEFT_STICK_Y), 0.0F) * 10.0F;
			camera->transform->position += velocity * delta_time;
		}

		{
			rge::vec3 velocity = rge::vec3();

			if(rge::input::is_down(rge::input::KEY_A))
				velocity.x -= 1;

			if(rge::input::is_down(rge::input::KEY_D))
				velocity.x += 1;

			if(rge::input::is_down(rge::input::KEY_W))
				velocity.y += 1;

			if(rge::input::is_down(rge::input::KEY_S))
				velocity.y -= 1;

			camera->transform->position += velocity * 10.0F * delta_time;
		}
	}

    void on_render() override {
		renderer->clear(rge::color(0.8F, 0.4F, 0.4F));
		
		renderer->draw(*background);
		renderer->draw(*smile);

		if(triangle) {
			renderer->draw(
				rge::mat4::trs(rge::vec3(0, 0, 0), rge::quaternion::yaw_pitch_roll(counter, 0, 0), rge::vec3(1, 1, 1)),
				*triangle,
				*material
			);
		}

		renderer->draw(*material->texture, rge::vec2(0.0F, 0.0F), rge::vec2(0.5F, 0.25F), rge::vec2(0.0F, 0.0F), rge::vec2(1.0F, 1.0F));
    }
};


int main(int argc, char** argv) {
    game* gm = new game();
	gm->create(true);
	gm->wait_for_exit();
	delete gm;
    return 0;
}