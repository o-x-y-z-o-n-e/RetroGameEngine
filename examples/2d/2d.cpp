#define RGE_IMPL
#define RGE_USE_STB_IMAGE_WRITE
#define RGE_USE_STB_IMAGE
#include "rge.hpp"

#include <iostream>
#include <fstream>

static rge::mesh::ptr load_triangle() {
	rge::mesh::ptr mdl = rge::mesh::create();

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
	rge::renderer* renderer;
    rge::material::ptr material;
    rge::camera::ptr camera;
	rge::sprite::ptr smile;
	rge::sprite::ptr background;
	rge::mesh::ptr triangle;
	float counter;

public:
    game() : rge::engine() {
		renderer = nullptr;
        material = rge::material::create();
		camera = rge::camera::create();
		smile = rge::sprite::create();
		background = rge::sprite::create();
		triangle = nullptr;
		counter = 0;
    }

    void on_init() override {
		renderer = get_renderer();

		background->texture = rge::texture::load("background.png");
		background->transform->position = rge::vec3(0, 0, 1);
		background->pixels_per_unit = 16;

		smile->texture = rge::texture::load("smile.bmp");
		smile->material = rge::material::create();
		smile->material->diffuse = rge::color(1, 0, 1, 0.5F);
		smile->pixels_per_unit = 16;
		smile->centered = true;

		triangle = load_triangle();
		material->diffuse = rge::color(1, 0, 1);
		material->texture = rge::texture::load("smile.bmp");

		camera->set_orthographic(-8, 8, 6, -6, 0.0F, 100.0F);
		camera->transform->position = rge::vec3(0, 0, -1);

        renderer->set_camera(camera);
		renderer->set_ambience(rge::color(0.2F, 0.2F, 0.2F));
    }

	void on_update(float delta_time) override {
		counter += delta_time;
		if(counter > PI * 2)
			counter = 0;

		smile->transform->position = rge::vec3(cosf(counter) * 3.0F, sinf(counter) * 3.0F, 0.0F);
		smile->transform->rotation = rge::quaternion::yaw_pitch_roll(0, 0, -counter);

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
	game* gm = rge::engine::create<game>();
	gm->run();
	gm->wait_for_exit();
	delete gm;
    return 0;
}