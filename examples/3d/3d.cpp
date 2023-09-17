#define RGE_IMPL
#define RGE_USE_STB_IMAGE
#define RGE_USE_STB_IMAGE_WRITE
#include "rge.hpp"

#include <iostream>
#include <fstream>

static std::vector<std::string> str_split(std::string& s, char sep) {
	std::vector<std::string> output;
	std::string::size_type prev_pos = 0, pos = 0;
	while((pos = s.find(sep, pos)) != std::string::npos) {
		std::string substring(s.substr(prev_pos, pos - prev_pos));
		output.push_back(substring);
		prev_pos = ++pos;
	}
	output.push_back(s.substr(prev_pos, pos - prev_pos));

	return output;
}

static rge::mesh::ptr load_obj(const char* fname) {
	std::ifstream fp_in;
	fp_in.open(fname, std::ios::in);
	if(!fp_in.is_open()) {
		std::cout << "Error opening mesh file" << std::endl;
		return nullptr;
	}

	rge::mesh::ptr mdl = rge::mesh::ptr();

	std::vector<rge::vec3> vertices;
	std::vector<rge::vec3> normals;
	std::vector<rge::vec2> uvs;
	std::string line;
	std::vector<std::string> comps;
	std::vector<std::string> face_comps;
	while(std::getline(fp_in, line)) {
		comps.clear();
		comps = str_split(line, ' ');
		if(comps.size() == 0)
			continue;

		if(comps[0] == "v") {
			if(comps.size() >= 4)
				vertices.push_back(rge::vec3(std::stof(comps[1]), std::stof(comps[2]), std::stof(comps[3])));
		} else if(comps[0] == "vn") {
			if(comps.size() >= 4)
				normals.push_back(rge::vec3(std::stof(comps[1]), std::stof(comps[2]), std::stof(comps[3])));
		} else if(comps[0] == "vt") {
			if(comps.size() >= 3) {
				uvs.push_back(rge::vec2(std::stof(comps[1]), std::stof(comps[2])));
			}
		} else if(comps[0] == "f") {
			for(int i = 1; i < 4; i++) {
				face_comps.clear();
				face_comps = str_split(comps[i], '/');
				int vi = 0, vti = 0, vni = 0;

				mdl->triangles.push_back(mdl->vertices.size());

				if(face_comps.size() > 0) {
					vi = std::stoi(face_comps[0]) - 1;
					mdl->vertices.push_back(vertices[vi]);
				} else {
					mdl->vertices.push_back(rge::vec3());
				}
				
				if(face_comps.size() > 1) {
					vti = std::stoi(face_comps[1]) - 1;
					mdl->uvs.push_back(uvs[vti]);
				} else {
					mdl->uvs.push_back(rge::vec2());
				}
				if(face_comps.size() > 2) {
					vni = std::stoi(face_comps[2]) - 1;
					mdl->normals.push_back(normals[vni]);
				} else {
					mdl->normals.push_back(rge::vec3());
				}				
			}
		}
	}

	vertices.clear();
	normals.clear();
	uvs.clear();
	comps.clear();
	face_comps.clear();
	fp_in.close();
	std::cout << " File successfully read." << std::endl;

	return mdl;
}

static rge::mesh::ptr load_triangle() {
	rge::mesh::ptr mdl = rge::mesh::create();

	mdl->vertices.push_back(rge::vec3(-1, -1, 0));
	mdl->vertices.push_back(rge::vec3(0, 1, 0));
	mdl->vertices.push_back(rge::vec3(1, -1, 0));

	mdl->normals.push_back(rge::vec3(0, 0, 1));
	mdl->normals.push_back(rge::vec3(0, 0, 1));
	mdl->normals.push_back(rge::vec3(0, 0, 1));

	mdl->triangles.push_back(0);
	mdl->triangles.push_back(1);
	mdl->triangles.push_back(2);

	mdl->uvs.push_back(rge::vec2(0, 0));
	mdl->uvs.push_back(rge::vec2(0.5F, 1.0F));
	mdl->uvs.push_back(rge::vec2(1, 0));

	return mdl;
}

static rge::mesh::ptr load_floor() {
	rge::mesh::ptr mdl = rge::mesh::create();

	mdl->vertices.push_back(rge::vec3(-10, 0, -10));
	mdl->vertices.push_back(rge::vec3(10, 0, -10));
	mdl->vertices.push_back(rge::vec3(10, 0, 10));
	mdl->vertices.push_back(rge::vec3(-10, 0, 10));

	mdl->normals.push_back(rge::vec3(0, 1, 0));
	mdl->normals.push_back(rge::vec3(0, 1, 0));
	mdl->normals.push_back(rge::vec3(0, 1, 0));
	mdl->normals.push_back(rge::vec3(0, 1, 0));

	mdl->triangles.push_back(0);
	mdl->triangles.push_back(1);
	mdl->triangles.push_back(3);

	mdl->triangles.push_back(2);
	mdl->triangles.push_back(3);
	mdl->triangles.push_back(1);

	mdl->uvs.push_back(rge::vec2(0, 0));
	mdl->uvs.push_back(rge::vec2(1, 0));
	mdl->uvs.push_back(rge::vec2(1, 1));
	mdl->uvs.push_back(rge::vec2(0, 1));

	return mdl;
}

class game : public rge::engine {
private:
    rge::material::ptr material;
	rge::renderer* renderer;
    rge::camera::ptr camera;
	rge::mesh::ptr model;
	rge::mesh::ptr triangle;
	rge::mesh::ptr floor;
	rge::render_target::ptr render;

	rge::input::action turn_action;

	rge::vec2 move_input;
	float counter;
	float rotation;
	float turn;

public:
    game() : rge::engine() {
        material = rge::material::create();
		camera = rge::camera::create();
		model = nullptr;
		floor = nullptr;
		triangle = nullptr;
		counter = 0;
		rotation = 0;
		turn = 0;
    }

    void on_init() override {
		renderer = get_renderer();

		render = rge::render_target::create(renderer, 800, 600);

		// model = load_obj("res/cube.obj");
		triangle = load_triangle();
		floor = load_floor();

        camera->set_perspective(80, 0.01F, 100.0F);
		camera->transform->position = rge::vec3(0, 2, 0);

        renderer->set_camera(camera);
		renderer->set_ambience(rge::color(0.2F, 0.2F, 0.2F));

		material->texture = rge::texture::load("floor.png");
		material->diffuse = rge::color(0.4F, 0.0F, 1.0F);
		renderer->upload_texture(*material->texture);

		turn_action.add_binding(rge::input::KEY_LEFT, -1.0F);
		turn_action.add_binding(rge::input::KEY_RIGHT, 1.0F);
    }

	void on_update(float delta_time) override {
		counter += delta_time;
		if(counter > PI * 2)
			counter = 0;

		{
			rge::vec2 input_target = rge::vec2();

			if(rge::input::is_down(rge::input::KEY_A))
				input_target.x -= 1;

			if(rge::input::is_down(rge::input::KEY_D))
				input_target.x += 1;

			if(rge::input::is_down(rge::input::KEY_W))
				input_target.y += 1;

			if(rge::input::is_down(rge::input::KEY_S))
				input_target.y -= 1;

			move_input = rge::vec2::move_towards(move_input, input_target, delta_time * 4.0F);

			rge::vec3 velocity = camera->transform->get_forward() * move_input.y + camera->transform->get_right() * move_input.x;
			velocity *= 10.0F;

			camera->transform->position += velocity * delta_time;
		}

		turn = rge::math::move_towards(turn, rge::input::get_axis(turn_action), delta_time * 4.0F);
		rotation += turn * 90.0F * delta_time;
		camera->transform->rotation = rge::quaternion::yaw_pitch_roll(rotation * DEG_TO_RAD, 0, 0);
	}

    void on_render() override {
		renderer->clear(rge::color(0.8F, 0.4F, 0.4F));

		if(floor) {
			renderer->draw(
				rge::mat4::translate(rge::vec3(0, 0, 0)),
				*floor,
				*material
			);
		}
		
		if(triangle) {
			renderer->draw(
				rge::mat4::trs(rge::vec3(0, 2, 5), rge::quaternion::yaw_pitch_roll(counter, 0, 0), rge::vec3(1, 1, 1)),
				*triangle,
				*material
			);
		}

		if(triangle) {
			renderer->draw(
				rge::mat4::trs(rge::vec3(2, 2, 10), rge::quaternion::yaw_pitch_roll(180 * DEG_TO_RAD, 0, 0), rge::vec3(1, 1, 1)),
				*triangle,
				*material
			);
		}

		if(model) {
			renderer->draw(
				rge::mat4::trs(rge::vec3(-2, 1, 5), rge::quaternion::yaw_pitch_roll(0, 0, 0), rge::vec3(1, 1, 1)),
				*model,
				*material
			);
		}
    }
};


int main(int argc, char** argv) {
	game* gm = rge::engine::create<game>();
	gm->run();
	gm->wait_for_exit();
	delete gm;
    return 0;
}