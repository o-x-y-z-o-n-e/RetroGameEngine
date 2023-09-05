#define RGE_IMPL
#define RGE_USE_STB_IMAGE_WRITE
#define RGE_USE_STB_IMAGE
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

static rge::mesh* load_obj(const char* fname) {
	std::ifstream fp_in;
	fp_in.open(fname, std::ios::in);
	if(!fp_in.is_open()) {
		std::cout << "Error opening mesh file" << std::endl;
		return nullptr;
	}

	rge::mesh* mdl = new rge::mesh();

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

				if(face_comps.size() > 0)
					vi = std::stoi(face_comps[0]) - 1;
				if(face_comps.size() > 1)
					vti = std::stoi(face_comps[1]) - 1;
				if(face_comps.size() > 2)
					vni = std::stoi(face_comps[2]) - 1;

				if(vti < 0) vti = vi;
				if(vni < 0) vni = vi;

				mdl->triangles.push_back(mdl->vertices.size());
				mdl->vertices.push_back(vertices[vi]);
				mdl->uvs.push_back(uvs[vti]);
				mdl->normals.push_back(normals[vni]);
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

static rge::mesh* load_floor() {
	rge::mesh* mdl = new rge::mesh;

	mdl->vertices.push_back(rge::vec3(-1, 0, -1));
	mdl->vertices.push_back(rge::vec3(1, 0, -1));
	mdl->vertices.push_back(rge::vec3(1, 0, 1));
	mdl->vertices.push_back(rge::vec3(-1, 0, 1));

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
    rge::material* material;
	rge::renderer* renderer;
    rge::camera* camera;
	rge::mesh* model;
	rge::mesh* triangle;
	rge::mesh* floor;

	float counter;

public:
    game() : rge::engine() {
        material = new rge::material();
		camera = new rge::camera();
		model = nullptr;
		floor = nullptr;
		triangle = nullptr;
		counter = 0;
    }

    void on_init() override {
		renderer = get_renderer();

		// model = load_obj("tests/cube.obj");
		triangle = load_triangle();
		floor = load_floor();

        camera->set_perspective(60, 1.6F, 0.0F, 1000.0F);
		camera->transform->position = rge::vec3(0, 2, -10);
		camera->transform->rotation = rge::quaternion::yaw_pitch_roll(0, 22.5F * DEG_2_RAD, 0);

        // renderer->set_target(render);
        renderer->set_camera(camera);
		renderer->set_ambience(rge::color(0.2F, 0.2F, 0.2F));

		material->texture = rge::texture::read_from_disk("floor.png");
		renderer->upload_texture(material->texture);
    }

	void on_update(float delta_time) override {
		counter += delta_time;
		if(counter > PI * 2)
			counter = 0;

		{
			rge::vec3 velocity = rge::vec3();

			if(rge::input::is_down(rge::input::KEY_A))
				velocity.x -= 1;

			if(rge::input::is_down(rge::input::KEY_D))
				velocity.x += 1;

			if(rge::input::is_down(rge::input::KEY_W))
				velocity.z += 1;

			if(rge::input::is_down(rge::input::KEY_S))
				velocity.z -= 1;

			camera->transform->position += velocity * 10.0F * delta_time;
		}
	}

    void on_render() override {
		renderer->clear(rge::color(0.8F, 0.4F, 0.4F));

		if(floor) {
			renderer->draw(
				rge::mat4::identity(),
				*floor,
				*material
			);
		}

		if(triangle) {
			renderer->draw(
				rge::mat4::trs(rge::vec3(0, 0, 0), rge::quaternion::yaw_pitch_roll(counter, 0, 0), rge::vec3(1, 1, 1)),
				*triangle,
				*material
			);
		}
    }
};


int main(int argc, char** argv) {
    game* gm = new game();
	gm->create(true);
	gm->wait_for_exit();
	delete gm;
    return 0;
}