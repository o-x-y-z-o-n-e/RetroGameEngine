/* RetroGameEngine (RGE)
   Author: Jeremy Kiel 
   Version: 0.00.1
   License: N/A
*/

#ifndef RGE_DEF
#define RGE_DEF

#define RGE_VERSION 0001

#include <cstdint>
#include <cmath>
#include <cstring>
#include <string>
#include <chrono>
#include <thread>
#include <iostream>
#include <functional>
#include <vector>

namespace rge {

	struct rect;
	struct vec2;
	struct vec3;
	struct vec4;
	struct quaternion;
	struct mat4;
	struct color;
	class engine;
	class event;
	class transform;
	class camera;
	class light;
	class texture;
	class material;
	class render_target;
	class renderer;
	class renderer2d;
	class renderer3d;
	class window;
	namespace platform {
		class window_impl;
	};

	enum result { FAIL = 0, OK = 1 };

	enum class light_mode {
		DIRECTIONAL,
		POINT,
		SPOT
	};

	#pragma region /* rge::key */
	//********************************************//
	//* Key module.                              *//
	//********************************************//
	namespace key {
		enum code {
			NONE = 0,

			A = 65,
			B = 66,
			C = 67,
			D = 68,
			E = 69,
			F = 70,
			G = 71,
			H = 72,
			I = 73,
			J = 74,
			K = 75,
			L = 76,
			M = 77,
			N = 78,
			O = 79,
			P = 80,
			Q = 81,
			R = 82,
			S = 83,
			T = 84,
			U = 85,
			V = 86,
			W = 87,
			X = 88,
			Y = 89,
			Z = 90,
		};
	}
	//********************************************//
	//* Key module.                              *//
	//********************************************//
	#pragma endregion

	#pragma region /* rge::rect */
	//********************************************//
	//* Rectangle struct.                        *//
	//********************************************//
	struct rect {
		float x, y, w, h;

		rect(float x, float y, float w, float h);

		vec2 get_min() const;
		vec2 get_max() const;
	};
	//********************************************//
	//* Rectangle struct.                        *//
	//********************************************//
	#pragma endregion

	#pragma region /* rge::vec2 */
	//********************************************//
	//* Vector2 struct.                          *//
	//********************************************//
	struct vec2 {
		float x, y;

		vec2();
		vec2(float x, float y);

		float magnitude() const;

		static float dot(const vec2& a, const vec2& b);
		static vec2 normalize(const vec2& v);

		vec2 operator + (const vec2& rhs) const;
		vec2 operator - (const vec2& rhs) const;
		vec2 operator * (const float& rhs) const;
		vec2 operator * (const vec2& rhs) const;
		vec2 operator / (const float& rhs) const;
		vec2 operator / (const vec2& rhs) const;

		vec2& operator += (const vec2& rhs);
		vec2& operator -= (const vec2& rhs);
		vec2& operator *= (const float& rhs);
		vec2& operator *= (const vec2& rhs);
		vec2& operator /= (const float& rhs);
		vec2& operator /= (const vec2& rhs);

		vec2 operator + () const;
		vec2 operator - () const;

		bool operator == (const vec2& rhs) const;
		bool operator != (const vec2& rhs) const;

		operator vec3() const;
		operator vec4() const;
	};
	//********************************************//
	//* Vector2 struct.                          *//
	//********************************************//
	#pragma endregion

	#pragma region /* rge::vec3 */
	//********************************************//
	//* Vector3 struct.                          *//
	//********************************************//
	struct vec3 {
		float x, y, z;

		vec3();
		vec3(float x, float y, float z);

		float magnitude() const;

		static float dot(const vec3& v1, const vec3& v2);
		static vec3 cross(const vec3& v1, const vec3& v2);
		static vec3 normalize(const vec3& v);

		vec3 operator + (const vec3& rhs) const { return vec3(this->x + rhs.x, this->y + rhs.y, this->z + rhs.z); }
		vec3 operator - (const vec3& rhs) const { return vec3(this->x - rhs.x, this->y - rhs.y, this->z - rhs.z); }
		vec3 operator * (const float& rhs) const { return vec3(this->x * rhs, this->y * rhs, this->z * rhs); }
		vec3 operator * (const vec3& rhs) const { return vec3(this->x * rhs.x, this->y * rhs.y, this->z * rhs.z); }
		vec3 operator / (const float& rhs) const { return vec3(this->x / rhs, this->y / rhs, this->z / rhs); }
		vec3 operator / (const vec3& rhs) const { return vec3(this->x / rhs.x, this->y / rhs.y, this->z / rhs.z); }

		vec3& operator += (const vec3& rhs) { this->x += rhs.x; this->y += rhs.y; this->z += rhs.z; return *this; }
		vec3& operator -= (const vec3& rhs) { this->x -= rhs.x; this->y -= rhs.y; this->z -= rhs.z; return *this; }
		vec3& operator *= (const float& rhs) { this->x *= rhs;  this->y *= rhs; this->z *= rhs; return *this; }
		vec3& operator *= (const vec3& rhs) { this->x *= rhs.x; this->y *= rhs.y; this->z *= rhs.z; return *this; }
		vec3& operator /= (const float& rhs) { this->x /= rhs;  this->y /= rhs; this->z /= rhs; return *this; }
		vec3& operator /= (const vec3& rhs) { this->x /= rhs.x; this->y /= rhs.y; this->z /= rhs.z; return *this; }

		vec3 operator + () const { return { +x, +y, +z }; }
		vec3 operator - () const { return { -x, -y, -z }; }

		bool operator == (const vec3& rhs) const { return (this->x == rhs.x && this->y == rhs.y && this->z == rhs.z); }
		bool operator != (const vec3& rhs) const { return (this->x != rhs.x || this->y != rhs.y || this->z != rhs.z); }
	};
	//********************************************//
	//* Vector3 struct.                          *//
	//********************************************//
	#pragma endregion

	#pragma region /* rge::vec4 */
	//********************************************//
	//* Vector4 struct.                          *//
	//********************************************//
	struct vec4 {
		float x, y, z, w;

		vec4();
		vec4(float x, float y, float z, float w);

		vec4 operator + (const vec4& rhs) const { return vec4(this->x + rhs.x, this->y + rhs.y, this->z + rhs.z, this->w + rhs.w); }
		vec4 operator - (const vec4& rhs) const { return vec4(this->x - rhs.x, this->y - rhs.y, this->z - rhs.z, this->w - rhs.w); }
		vec4 operator * (const float& rhs) const { return vec4(this->x * rhs, this->y * rhs, this->z * rhs, this->w * rhs); }
		vec4 operator * (const vec4& rhs) const { return vec4(this->x * rhs.x, this->y * rhs.y, this->z * rhs.z, this->w * rhs.w); }
		vec4 operator / (const float& rhs) const { return vec4(this->x / rhs, this->y / rhs, this->z / rhs, this->w / rhs); }
		vec4 operator / (const vec4& rhs) const { return vec4(this->x / rhs.x, this->y / rhs.y, this->z / rhs.z, this->w / rhs.w); }

		vec4& operator += (const vec4& rhs) { this->x += rhs.x; this->y += rhs.y; this->z += rhs.z; this->w += rhs.w; return *this; }
		vec4& operator -= (const vec4& rhs) { this->x -= rhs.x; this->y -= rhs.y; this->z -= rhs.z; this->w -= rhs.w; return *this; }
		vec4& operator *= (const float& rhs) { this->x *= rhs;  this->y *= rhs; this->z *= rhs; this->w *= rhs; return *this; }
		vec4& operator *= (const vec4& rhs) { this->x *= rhs.x; this->y *= rhs.y; this->z *= rhs.z; this->w *= rhs.w; return *this; }
		vec4& operator /= (const float& rhs) { this->x /= rhs;  this->y /= rhs; this->z /= rhs; this->w /= rhs; return *this; }
		vec4& operator /= (const vec4& rhs) { this->x /= rhs.x; this->y /= rhs.y; this->z /= rhs.z; this->w /= rhs.w; return *this; }

		vec4 operator + () const { return { +x, +y, +z, +w }; }
		vec4 operator - () const { return { -x, -y, -z, -w }; }

		bool operator == (const vec4& rhs) const { return (this->x == rhs.x && this->y == rhs.y && this->z == rhs.z && this->w == rhs.w); }
		bool operator != (const vec4& rhs) const { return (this->x != rhs.x || this->y != rhs.y || this->z != rhs.z || this->w != rhs.w); }

		operator vec3() const { return { x, y, z }; }
		operator vec2() const { return { x, y }; }
	};
	//********************************************//
	//* Vector4 struct.                          *//
	//********************************************//
	#pragma endregion

	#pragma region /* rge::quaternion */
	//********************************************//
	//* Quaternion struct.                       *//
	//********************************************//
	struct quaternion {
		float x, y, z, w;

		quaternion();
		quaternion(float x, float y, float z, float w);

		static quaternion identity() { return quaternion(); }
		static quaternion look(const vec3& forward, const vec3& up);

		vec3 operator * (const vec3& rhs) const;
	};
	//********************************************//
	//* Quaternion struct.                       *//
	//********************************************//
	#pragma endregion

	#pragma region /* rge::mat4 */
	//********************************************//
	//* Matrix 4x4 struct.                       *//
	//********************************************//
	struct mat4 {
		float m[4][4]; // Rows by columns.

		mat4();
		mat4(vec4 col0, vec4 col1, vec4 col2, vec4 col3);

		static mat4 identity() { return mat4(); }
		static mat4 translate(const vec3& translation);
		static mat4 rotate(const quaternion& rotation);
		static mat4 scale(const vec3& scale);
		static mat4 trs(const vec3& position, const quaternion& rotation, const vec3& scale);

		vec3 multiply_point_3x4(const vec3& v) const;
		vec3 multiply_vector(const vec3& v) const;
		vec3 extract_translation() const;
		quaternion extract_rotation() const;
		vec3 extract_right_axis() const;
		vec3 extract_up_axis() const;
		vec3 extract_forward_axis() const;

		vec4 operator * (const vec4& rhs) const;
		mat4 operator * (const mat4& rhs) const;
	};
	//********************************************//
	//* Matrix 4x4 struct.                       *//
	//********************************************//
	#pragma endregion

	#pragma region /* rge::color */
	//********************************************//
	//* Color struct.                            *//
	//********************************************//
	struct color {
		float r, g, b, a;

		color();
		color(float r, float g, float b);
		color(float r, float g, float b, float a);

		static color lerp(const color& a, const color& b, float t);

		color operator + (const color& rhs) const;
		color& operator += (const color& rhs);
		color operator - (const color& rhs) const;
		color& operator -= (const color& rhs);
		color operator * (const color& rhs) const;
		color& operator *= (const color& rhs);

		color operator * (const float& rhs) const;
		color& operator *= (const float& rhs);
		color operator / (const float& rhs) const;
		color& operator /= (const float& rhs);
	};
	//********************************************//
	//* Color struct.                            *//
	//********************************************//
	#pragma endregion

	#pragma region /* rge::math */
	//********************************************//
	//* Math Module.                             *//
	//********************************************//
	namespace math {
		float lerp(float a, float b, float t);
		int min(int a, int b) { return a < b ? a : b; }
		int max(int a, int b) { return a > b ? a : b; }
	}
	//********************************************//
	//* Math Module.                             *//
	//********************************************//
	#pragma endregion

	#pragma region /* rge::log */
	//********************************************//
	//* Logging Module.                          *//
	//********************************************//
	namespace log {
		void info(const std::string& msg);
		void warning(const std::string& msg);
		void error(const std::string& msg);
	}
	//********************************************//
	//* Logging Module.                          *//
	//********************************************//
	#pragma endregion

	#pragma region /* rge::engine */
	//********************************************//
	//* Core Engine class.                       *//
	//********************************************//
	class engine {
	public:
		engine();
		virtual ~engine();
	
	public:
		rge::result init();
		rge::result start(bool wait_until_exit = true, std::thread** game_thread = nullptr);
		rge::result exit();
		rge::result command(const std::string& cmd);
	
	protected:
		virtual void on_init();
		virtual bool on_command(const std::string& cmd);
		virtual void on_start();
		virtual void on_update(float delta_time);
		virtual void on_physics(float delta_time);
		virtual void on_render();
		virtual void on_exit();
	
	public:
		int get_frame_rate() const;
		bool get_is_running() const;
	
	public:
		float update_interval;
		float physics_interval;
		float render_interval;
	
	private:
		void loop();
	
	private:
		bool is_running;
		std::thread thread;
		window* app_window;
		float update_counter;
		float physics_counter;
		float render_counter;
		std::chrono::time_point<std::chrono::system_clock> time_stamp_1, time_stamp_2;
		int frame_counter;
		int frame_rate;
		float frame_timer;
	};
	//********************************************//
	//* Core Engine class.                       *//
	//********************************************//
	#pragma endregion

	#pragma region /* rge::event */
	//********************************************//
	//* Event class.                             *//
	//********************************************//
	enum class event_type {
		NONE = 0,
		WINDOW_CLOSE_REQUESTED, WINDOW_MOVED, WINDOW_RESIZED, WINDOW_FOCUSED, WINDOW_UNFOCUSED,
		KEY_PRESSED, KEY_RELEASED,
		MOUSE_PRESSED, MOUSE_RELEASED, MOUSE_MOVED, MOUSE_SCROLLED
	};
	//----------------------------------------------
	#define EVENT_ENUM_TYPE(type) public:\
	static event_type get_static_type() { return event_type::type; } \
	virtual event_type get_event_type() const override { return get_static_type(); } \
	//----------------------------------------------
	class event {
	public:
		event();

	public:
		template<typename T>
		bool dispatch(std::function<bool(const T&)> func) {
			if(get_event_type() == T::get_static_type()) {
				handled |= func(static_cast<const T&>(*this));
				return true;
			}
			return false;
		}
		bool get_handled() const;
		virtual event_type get_event_type() const = 0;


	private:
		bool handled;
	};
	//----------------------------------------------
	class key_event : public event {
	protected: // Abstract class.
		key_event(key::code key_code);

	public:
		key::code get_key_code() const;

	protected:
		key::code key_code;
	};
	//----------------------------------------------
	class key_pressed_event : public key_event {
	public:
		key_pressed_event(key::code key_code);

		EVENT_ENUM_TYPE(KEY_PRESSED)
	};
	//********************************************//
	//* Event class.                             *//
	//********************************************//
	#pragma endregion

	#pragma region /* rge::transform */
	//********************************************//
	//* Transform class.                         *//
	//********************************************//
	class transform {
	public:
		transform();
		transform(transform* parent);
		transform(vec3 position, quaternion rotation, vec3 scale);
		transform(vec3 position, quaternion rotation, vec3 scale, transform* parent);
	
	public:
		mat4 get_global_matrix() const;

		vec3 get_forward() const;
		vec3 get_up() const;
		vec3 get_right() const;
		vec3 get_backward() const { return -get_forward(); };
		vec3 get_down() const { return -get_up(); };
		vec3 get_left() const { return -get_right(); };
		// TODO: Add set_DIRECTION functions.
		
		vec3 get_global_forward() const;
		vec3 get_global_up() const;
		vec3 get_global_right() const;
		vec3 get_global_backward() const { return -get_global_forward(); };
		vec3 get_global_down() const { return -get_global_up(); };
		vec3 get_global_left() const { return -get_global_right(); };
		// TODO: Add set_global_DIRECTION functions.

		vec3 get_global_position() const;
		quaternion get_global_rotation() const;
		void set_global_position(const vec3& position);
		void set_global_rotation(const quaternion& rotation);

	public:
		transform* parent;
		vec3 position;
		quaternion rotation;
		vec3 scale;
	};
	//********************************************//
	//* Transform class.                         *//
	//********************************************//
	#pragma endregion

	#pragma region /* rge::camera */
	//********************************************//
	//* Camera class.                            *//
	//********************************************//
	class camera {
	public:
		camera();
		~camera();

	public:
		mat4 get_view_matrix() const;
		mat4 get_projection_matrix() const;
		void set_projection_matrix(float fov, float aspect, float near_plane, float far_plane);

	public:
		transform* transform;

	private:
		mat4 view; // TODO: iirc this is the same a world transform matrix (but for camera). Might be redundent.
		mat4 projection;
	};
	//********************************************//
	//* Camera class.                            *//
	//********************************************//
	#pragma endregion

	#pragma region /* rge::light */
	//********************************************//
	//* Light class.                             *//
	//********************************************//
	class light {
	public:
		light();
		~light();

	public:
		color tint;
		float intensity;
		float range;
		light_mode type;
		transform* transform;
	};
	//********************************************//
	//* Light class.                             *//
	//********************************************//
	#pragma endregion

	#pragma region /* rge::texture */
	//********************************************//
	//* Texture class.                           *//
	//********************************************//
	class texture {
	public:
		texture(int width, int height);
		~texture();

	public:
		int get_width() const;
		int get_height() const;
		bool get_on_disk() const;
		bool get_on_cpu() const;
		bool get_on_gpu() const;
		color sample(float u, float v) const;
		color* get_data() const;

		// NOTE: TESTING FUNCTION
		rge::result write_to_disk(const std::string& path) const;
		// rge::result read_from_disk(const std::string& path);

	private:
		void allocate();

	private:
		bool on_disk, on_cpu, on_gpu;
		int width;
		int height;
		color* data;
	};
	//********************************************//
	//* Texture class.                           *//
	//********************************************//
	#pragma endregion

	#pragma region /* rge::material */
	//********************************************//
	//* Material class.                          *//
	//********************************************//
	class material {
	public:
		material();
		~material();

	public:
		texture* texture;
		color diffuse;
		color specular;
		float shininess;
	};
	//********************************************//
	//* Material class.                          *//
	//********************************************//
	#pragma endregion

	#pragma region /* rge::render_target */
	//********************************************//
	//* Render Target class.                     *//
	//********************************************//
	class render_target : public texture {
	public:
		render_target();
		render_target(int width, int height);
	};
	//********************************************//
	//* Render Target class.                     *//
	//********************************************//
	#pragma endregion

	#pragma region /* rge::renderer */
	//********************************************//
	//* Renderer class.                          *//
	//********************************************//
	class renderer {
	public:
		renderer();
		virtual ~renderer();

	public:
		rge::result set_target(render_target* target);
		render_target* get_target() const;
		void clear(color c);

	protected:
		render_target* target;
	};
	//********************************************//
	//* Renderer class.                          *//
	//********************************************//
	#pragma endregion

	#pragma region /* rge::renderer2d */
	//********************************************//
	//* Software Renderer 2D class.              *//
	//********************************************//
	class renderer2d : public renderer {
	public:
		renderer2d();
		virtual ~renderer2d();

	public:
		void draw(const texture& texture, const rect& dest);
		void draw(const texture& texture, const rect& dest, const rect& src);
	};
	//********************************************//
	//* Software Renderer 2D class.              *//
	//********************************************//
	#pragma endregion

	#pragma region /* rge::renderer3d */
	//********************************************//
	//* Software Renderer 3D class.              *//
	//********************************************//
	class renderer3d : public renderer {
	public:
		renderer3d();
		virtual ~renderer3d();

	public:
		void set_camera(camera* camera);
		void set_ambience(const color& ambient_color);
		rge::result draw(
			const mat4& model_to_world,
			const std::vector<vec3>& vertices,
			const std::vector<int>& triangles,
			const std::vector<vec3>& normals,
			const std::vector<vec2>& uvs,
			const material& material
		);

	public:
		void draw_interpolated_triangle(
			const vec4& r_v1,
			const vec4& r_v2,
			const vec4& r_v3,
			const vec3& w_v1,
			const vec3& w_v2,
			const vec3& w_v3,
			const vec3& w_n1,
			const vec3& w_n2,
			const vec3& w_n3,
			const vec2& t_uv1,
			const vec2& t_uv2,
			const vec2& t_uv3,
			const material& material
		);

	private:
		static vec4 project_world_vertex(const vec3& vertex, const mat4& projection);
		static color calculate_blinn_phong(
			const vec3& position,
			const vec3& normal,
			const color& diffuse,
			const color& specular,
			const color& ambient,
			float shininess,
			const vec3& camera_position,
			const std::vector<light*>& lights
		);

	private:
		camera* world_camera;
		std::vector<light*> lights;
		color ambience;
	};
	//********************************************//
	//* Software Renderer 3D class.              *//
	//********************************************//
	#pragma endregion

	#pragma region /* rge::window */
	//********************************************//
	//* Window class.                            *//
	//********************************************//
	class window {
	public:
		window();
		~window();

	public:
		virtual rge::result create();
		virtual rge::result set_size(int width, int height);
		void get_size(int& width, int& height) const;

	private:
		class platform::window_impl* impl;
		// TODO: bool is_fullscreen;
	};
	//********************************************//
	//* Window class.                            *//
	//********************************************//
	#pragma endregion

}

#endif /* RGE_DEF */

#ifdef RGE_IMPL
#undef RGE_IMPL

// Forward declaration of the user main() function.
int main(int argc, char** argv);

#ifdef SYS_WINDOWS
#include <windows.h>
// Real win32 entry point for release mode (DesktopApp).
/*
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nShowCmd) {
	// TODO: Get parameters.
	return main(0, nullptr);
}
*/
#endif

#ifdef RGE_USE_STB_IMAGE_WRITE
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#endif

namespace rge {

	#pragma region /* rge::rect */
	//********************************************//
	//* Rectangle struct.                        *//
	//********************************************//
	rect::rect(float x, float y, float w, float h) {
		this->x = x;
		this->y = y;
		this->w = w;
		this->h = h;
	}

	vec2 rect::get_min() const {
		return vec2(x, y);
	}

	vec2 rect::get_max() const {
		return vec2(x+w, y+h);
	}
	//********************************************//
	//* Rectangle struct.                        *//
	//********************************************//
	#pragma endregion

	#pragma region /* rge::vec2 */
	//********************************************//
	//* Vector2 struct.                          *//
	//********************************************//
	vec2::vec2() {
		this->x = 0;
		this->y = 0;
	}

	vec2::vec2(float x, float y) {
		this->x = x;
		this->y = y;
	}

	float vec2::magnitude() const {
		return sqrtf(x * x + y * y);
	}

	float vec2::dot(const vec2& a, const vec2& b) {
		return a.x * b.x + a.y * b.y;
	}

	vec2 vec2::normalize(const vec2& v) {
		return v / v.magnitude();
	}

	vec2 vec2::operator + (const vec2& rhs) const {
		return vec2(this->x + rhs.x, this->y + rhs.y);
	}

	vec2 vec2::operator - (const vec2& rhs) const {
		return vec2(this->x - rhs.x, this->y - rhs.y);
	}

	vec2 vec2::operator * (const float& rhs) const {
		return vec2(this->x * rhs, this->y * rhs);
	}

	vec2 vec2::operator * (const vec2& rhs) const {
		return vec2(this->x * rhs.x, this->y * rhs.y);
	}

	vec2 vec2::operator / (const float& rhs) const {
		return vec2(this->x / rhs, this->y / rhs);
	}
	
	vec2 vec2::operator / (const vec2& rhs) const {
		return vec2(this->x / rhs.x, this->y / rhs.y);
	}

	vec2& vec2::operator += (const vec2& rhs) {
		this->x += rhs.x; this->y += rhs.y; return *this;
	}

	vec2& vec2::operator -= (const vec2& rhs) { 
		this->x -= rhs.x; this->y -= rhs.y; return *this; 
	}

	vec2& vec2::operator *= (const float& rhs) { 
		this->x *= rhs;  this->y *= rhs;return *this;
	}

	vec2& vec2::operator *= (const vec2& rhs) {
		this->x *= rhs.x; this->y *= rhs.y; return *this;
	}

	vec2& vec2::operator /= (const float& rhs) {
		this->x /= rhs;  this->y /= rhs; return *this;
	}

	vec2& vec2::operator /= (const vec2& rhs) {
		this->x /= rhs.x; this->y /= rhs.y; return *this;
	}

	vec2 vec2::operator + () const {
		return { +x, +y };
	}

	vec2 vec2::operator - () const {
		return { -x, -y };
	}

	bool vec2::operator == (const vec2& rhs) const {
		return (this->x == rhs.x && this->y == rhs.y);
	}

	bool vec2::operator != (const vec2& rhs) const {
		return (this->x != rhs.x || this->y != rhs.y);
	}

	vec2::operator vec3() const {
		return vec3(x, y, 0);
	}

	vec2::operator vec4() const {
		return vec4(x, y, 0, 0);
	}
	//********************************************//
	//* Vector2 struct.                          *//
	//********************************************//
	#pragma endregion

	#pragma region /* rge::vec3 */
	//********************************************//
	//* Vector3 struct.                          *//
	//********************************************//
	vec3::vec3() {
		this->x = 0;
		this->y = 0;
		this->z = 0;
	}

	vec3::vec3(float x, float y, float z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}

	float vec3::magnitude() const {
		return sqrtf(x * x + y * y + z * z);
	}

	float vec3::dot(const vec3& v1, const vec3& v2) {
		return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	}

	vec3 vec3::cross(const vec3& v1, const vec3& v2) {
		return vec3(
			v1.y * v2.z - v1.z * v2.y,
			v1.z * v2.x - v1.x * v2.z,
			v1.x * v2.y - v1.y * v2.x
		);
	}

	vec3 vec3::normalize(const vec3& v) {
		return v / v.magnitude();
	}

	// TODO: Move operator definitions here

	//********************************************//
	//* Vector3 struct.                          *//
	//********************************************//
	#pragma endregion

	#pragma region /* rge::vec4 */
	//********************************************//
	//* Vector4 struct.                          *//
	//********************************************//
	vec4::vec4() {
		this->x = 0;
		this->y = 0;
		this->z = 0;
		this->w = 0;
	}

	vec4::vec4(float x, float y, float z, float w) {
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	// TODO: Move operator definitions here

	//********************************************//
	//* Vector4 struct.                          *//
	//********************************************//
	#pragma endregion

	#pragma region /* rge::quaternion */
	//********************************************//
	//* Quaternion struct.                       *//
	//********************************************//
	quaternion::quaternion() {
		this->x = 0;
		this->y = 0;
		this->z = 0;
		this->w = 1;
	}

	quaternion::quaternion(float x, float y, float z, float w) {
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	quaternion quaternion::look(const vec3& forward, const vec3& up) {
		quaternion q = quaternion::identity();
		vec3 f = vec3::normalize(forward);
		vec3 r = vec3::normalize(vec3::cross(up, f));
		vec3 u = vec3::cross(f, r);
		float num1;
		float num2;
		float num3;
		float num4;
		float num5;
		float num6;
		float num7;
		float num8;

		/*
		mat4 m = mat4(
			vec4(r.x,r.y,r.z,0),
			vec4(u.x,u.y,u.z,0),
			vec4(f.x,f.y,f.z,0),
			vec4(0,0,0,1)
		);*/

		num8 = r.x + u.y + f.z;
		if(num8 > 0.0F) {
			num1 = sqrtf(num8 + 1.0F);
			num1 = 0.5F / num1;
			q.x = (u.z - f.z) * num1;
			q.y = (f.x - r.z) * num1;
			q.z = (r.y - u.x) * num1;
			q.w = num1 * 0.5F;
		} else if((r.x >= u.y) && (r.x >= f.z)) {
			num7 = sqrtf(((1.0F + r.x) - u.y) - f.z);
			num4 = 0.5F / num7;
			q.x = num7 * 0.5F;
			q.y = (r.y + u.x) * num4;
			q.z = (r.z + f.x) * num4;
			q.w = (u.z - f.y) * num4;
		} else if(u.y > f.z) {
			num6 = sqrtf(((1.0F + u.y) - r.x) - f.z);
			num3 = 0.5F / num6;
			q.x = (u.x + r.y) * num3;
			q.y = num6 * 0.5F;
			q.z = (f.y + u.z) * num3;
			q.w = (f.x - r.z) * num3;
		} else {
			num5 = sqrtf(((1.0F + f.z) - r.x) - u.y);
			num2 = 0.5F / num5;
			q.x = (f.x + r.z) * num2;
			q.y = (f.y + u.z) * num2;
			q.z = num5 * 0.5F;
			q.w = (r.y - u.x) * num2;
		}

		return q;
	}

	vec3 quaternion::operator * (const vec3& rhs) const {
		vec3 result = vec3();
		float num1 =  this->x * 2.0F;
		float num2 =  this->y * 2.0F;
		float num3 =  this->z * 2.0F;
		float num4 =  this->x * num1;
		float num5 =  this->y * num2;
		float num6 =  this->z * num3;
		float num7 =  this->x * num2;
		float num8 =  this->x * num3;
		float num9 =  this->y * num3;
		float num10 = this->w * num1;
		float num11 = this->w * num2;
		float num12 = this->w * num3;
		
		result.x = (1.0F - (num5 + num6)) * rhs.x + (num7 - num12) * rhs.y + (num8 + num11) * rhs.z;
		result.y = (num7 + num12) * rhs.x + (1.0F - (num4 + num6)) * rhs.y + (num9 - num10) * rhs.z;
		result.z = (num8 - num11) * rhs.x + (num9 + num10) * rhs.y + (1.0F - (num4 + num5)) * rhs.z;

		return result;
	}
	//********************************************//
	//* Quaternion struct.                       *//
	//********************************************//
	#pragma endregion

	#pragma region /* rge::mat4 */
	//********************************************//
	//* Matrix 4x4 struct.                       *//
	//********************************************//
	mat4::mat4() {
		m[0][0] = 1;
		m[0][1] = 0;
		m[0][2] = 0;
		m[0][3] = 0;
		m[1][0] = 0;
		m[1][1] = 1;
		m[1][2] = 0;
		m[1][3] = 0;
		m[2][0] = 0;
		m[2][1] = 0;
		m[2][2] = 1;
		m[2][3] = 0;
		m[3][0] = 0;
		m[3][1] = 0;
		m[3][2] = 0;
		m[3][3] = 1;
	}

	mat4::mat4(vec4 col0, vec4 col1, vec4 col2, vec4 col3) {
		m[0][0] = col0.x;
		m[0][1] = col1.x;
		m[0][2] = col2.x;
		m[0][3] = col3.x;
		m[1][0] = col0.y;
		m[1][1] = col1.y;
		m[1][2] = col2.y;
		m[1][3] = col3.y;
		m[2][0] = col0.z;
		m[2][1] = col1.z;
		m[2][2] = col2.z;
		m[2][3] = col3.z;
		m[3][0] = col0.w;
		m[3][1] = col1.w;
		m[3][2] = col2.w;
		m[3][3] = col3.w;
	}

	mat4 mat4::translate(const vec3& translation) {
		mat4 m = mat4::identity();
		m.m[0][3] = translation.x;
		m.m[1][3] = translation.y;
		m.m[2][3] = translation.z;
		return m;
	}

	mat4 mat4::rotate(const quaternion& rotation) {
		mat4 m = mat4::identity();
		float x = rotation.x * 2.0F;
		float y = rotation.y * 2.0F;
		float z = rotation.z * 2.0F;
		float xx = rotation.x * x;
		float yy = rotation.y * y;
		float zz = rotation.z * z;
		float xy = rotation.x * y;
		float xz = rotation.x * z;
		float yz = rotation.y * z;
		float wx = rotation.w * x;
		float wy = rotation.w * y;
		float wz = rotation.w * z;
		
		m.m[0][0] = 1.0f - (yy + zz);
		m.m[1][0] = xy + wz;
		m.m[2][0] = xz - wy;
		m.m[0][1] = xy - wz;
		m.m[1][1] = 1.0f - (xx + zz);
		m.m[2][1] = yz + wx;
		m.m[0][2] = xz + wy;
		m.m[1][2] = yz - wx;
		m.m[2][2] = 1.0f - (xx + yy);
		
		return m;
	}

	mat4 mat4::scale(const vec3& scale) {
		mat4 m = mat4::identity();
		m.m[0][0] = scale.x;
		m.m[1][1] = scale.y;
		m.m[2][2] = scale.z;
		return m;
	}

	mat4 mat4::trs(const vec3& translation, const quaternion& rotation, const vec3& scale) {
		return (mat4::translate(translation) * mat4::rotate(rotation)) * mat4::scale(scale);
	}

	vec3 mat4::multiply_point_3x4(const vec3& v) const {
		vec3 result = vec3();
		result.x = m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z + m[0][3];
		result.y = m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z + m[1][3];
		result.z = m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z + m[2][3];
		return v;
	}

	vec3 mat4::multiply_vector(const vec3& v) const {
		vec3 result = vec3();
		result.x = m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z;
		result.y = m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z;
		result.z = m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z;
		return v;
	}

	vec3 mat4::extract_translation() const {
		return vec3(m[0][3], m[1][3], m[2][3]);
	}

	quaternion mat4::extract_rotation() const {
		/*
		quaternion q = quaternion();
		
		q.w = sqrtf(fmaxf(0, 1.0F + m[0][0] + m[1][1] + m[2][2])) / 2.0F;
		q.x = sqrtf(fmaxf(0, 1.0F + m[0][0] - m[1][1] - m[2][2])) / 2.0F;
		q.y = sqrtf(fmaxf(0, 1.0F - m[0][0] + m[1][1] - m[2][2])) / 2.0F;
		q.z = sqrtf(fmaxf(0, 1.0F - m[0][0] - m[1][1] + m[2][2])) / 2.0F;
		if(q.x * (m[2][1] - m[1][2]) < 0) q.x *= -1;
		if(q.y * (m[0][2] - m[2][0]) < 0) q.y *= -1;
		if(q.z * (m[1][0] - m[0][1]) < 0) q.z *= -1;
		
		return q;
		*/
		
		vec3 forward;
		forward.x = m[0][2];
		forward.y = m[1][2];
		forward.z = m[2][2];
		
		vec3 up;
		up.x = m[0][1];
		up.y = m[1][1];
		up.z = m[2][1];
		
		return quaternion::look(forward, up);
	}

	vec3 mat4::extract_right_axis() const {
		return vec3::normalize(vec3(m[0][0], m[1][0], m[2][0]));
	}

	vec3 mat4::extract_up_axis() const {
		return vec3::normalize(vec3(m[0][1], m[1][1], m[2][1]));
	}

	vec3 mat4::extract_forward_axis() const {
		return vec3::normalize(vec3(m[0][2], m[1][2], m[2][2]));
	}

	vec4 mat4::operator * (const vec4& rhs) const {
		vec4 result = vec4();
		result.x = this->m[0][0] * rhs.x + this->m[0][1] * rhs.y + this->m[0][2] * rhs.z + this->m[0][3] * rhs.w;
		result.y = this->m[1][0] * rhs.x + this->m[1][1] * rhs.y + this->m[1][2] * rhs.z + this->m[1][3] * rhs.w;
		result.z = this->m[2][0] * rhs.x + this->m[2][1] * rhs.y + this->m[2][2] * rhs.z + this->m[2][3] * rhs.w;
		result.w = this->m[3][0] * rhs.x + this->m[3][1] * rhs.y + this->m[3][2] * rhs.z + this->m[3][3] * rhs.w;
		return result;
	}

	mat4 mat4::operator * (const mat4& rhs) const {
		mat4 result = mat4();
		result.m[0][0] = this->m[0][0] * rhs.m[0][0] + this->m[0][1] * rhs.m[1][0] + this->m[0][2] * rhs.m[2][0] + this->m[0][3] * rhs.m[3][0];
		result.m[0][1] = this->m[0][0] * rhs.m[0][1] + this->m[0][1] * rhs.m[1][1] + this->m[0][2] * rhs.m[2][1] + this->m[0][3] * rhs.m[3][1];
		result.m[0][2] = this->m[0][0] * rhs.m[0][2] + this->m[0][1] * rhs.m[1][2] + this->m[0][2] * rhs.m[2][2] + this->m[0][3] * rhs.m[3][2];
		result.m[0][3] = this->m[0][0] * rhs.m[0][3] + this->m[0][1] * rhs.m[1][3] + this->m[0][2] * rhs.m[2][3] + this->m[0][3] * rhs.m[3][3];
		result.m[1][0] = this->m[1][0] * rhs.m[0][0] + this->m[1][1] * rhs.m[1][0] + this->m[1][2] * rhs.m[2][0] + this->m[1][3] * rhs.m[3][0];
		result.m[1][1] = this->m[1][0] * rhs.m[0][1] + this->m[1][1] * rhs.m[1][1] + this->m[1][2] * rhs.m[2][1] + this->m[1][3] * rhs.m[3][1];
		result.m[1][2] = this->m[1][0] * rhs.m[0][2] + this->m[1][1] * rhs.m[1][2] + this->m[1][2] * rhs.m[2][2] + this->m[1][3] * rhs.m[3][2];
		result.m[1][3] = this->m[1][0] * rhs.m[0][3] + this->m[1][1] * rhs.m[1][3] + this->m[1][2] * rhs.m[2][3] + this->m[1][3] * rhs.m[3][3];
		result.m[2][0] = this->m[2][0] * rhs.m[0][0] + this->m[2][1] * rhs.m[1][0] + this->m[2][2] * rhs.m[2][0] + this->m[2][3] * rhs.m[3][0];
		result.m[2][1] = this->m[2][0] * rhs.m[0][1] + this->m[2][1] * rhs.m[1][1] + this->m[2][2] * rhs.m[2][1] + this->m[2][3] * rhs.m[3][1];
		result.m[2][2] = this->m[2][0] * rhs.m[0][2] + this->m[2][1] * rhs.m[1][2] + this->m[2][2] * rhs.m[2][2] + this->m[2][3] * rhs.m[3][2];
		result.m[2][3] = this->m[2][0] * rhs.m[0][3] + this->m[2][1] * rhs.m[1][3] + this->m[2][2] * rhs.m[2][3] + this->m[2][3] * rhs.m[3][3];
		result.m[3][0] = this->m[3][0] * rhs.m[0][0] + this->m[3][1] * rhs.m[1][0] + this->m[3][2] * rhs.m[2][0] + this->m[3][3] * rhs.m[3][0];
		result.m[3][1] = this->m[3][0] * rhs.m[0][1] + this->m[3][1] * rhs.m[1][1] + this->m[3][2] * rhs.m[2][1] + this->m[3][3] * rhs.m[3][1];
		result.m[3][2] = this->m[3][0] * rhs.m[0][2] + this->m[3][1] * rhs.m[1][2] + this->m[3][2] * rhs.m[2][2] + this->m[3][3] * rhs.m[3][2];
		result.m[3][3] = this->m[3][0] * rhs.m[0][3] + this->m[3][1] * rhs.m[1][3] + this->m[3][2] * rhs.m[2][3] + this->m[3][3] * rhs.m[3][3];
		return result;
	}
	//********************************************//
	//* Matrix 4x4 struct.                       *//
	//********************************************//
	#pragma endregion

	#pragma region /* rge::color */
	//********************************************//
	//* Color struct.                            *//
	//********************************************//
	color::color() {
		this->r = 1;
		this->g = 1;
		this->b = 1;
		this->a = 1;
	}

	color::color(float r, float g, float b) {
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = 1;
	}

	color::color(float r, float g, float b, float a) {
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}

	color color::lerp(const color& a, const color& b, float t) {
		if(t < 0) t = 0;
		if(t > 1) t = 1;

		return color(
			a.r * (1 - t) + b.r * t,
			a.g * (1 - t) + b.g * t,
			a.b * (1 - t) + b.b * t,
			a.a * (1 - t) + b.a * t
		);
	}

	color color::operator + (const color& rhs) const {
		return color(this->r + rhs.r, this->g + rhs.g, this->b + rhs.b, this->a + rhs.a);
	}

	color& color::operator += (const color& rhs) {
		this->r += rhs.r; this->g += rhs.g; this->b += rhs.b; this->a += rhs.a; return *this;
	}

	color color::operator - (const color& rhs) const {
		return color(this->r - rhs.r, this->g - rhs.g, this->b - rhs.b, this->a - rhs.a);
	}

	color& color::operator -= (const color& rhs) {
		this->r -= rhs.r; this->g -= rhs.g; this->b -= rhs.b; this->a -= rhs.a; return *this;
	}

	color color::operator * (const color& rhs) const {
		return color(this->r * rhs.r, this->g * rhs.g, this->b * rhs.b, this->a * rhs.a);
	}

	color& color::operator *= (const color& rhs) {
		this->r *= rhs.r; this->g *= rhs.g; this->b *= rhs.b; this->a *= rhs.a; return *this;
	}

	color color::operator * (const float& rhs) const {
		return color(this->r * rhs, this->g * rhs, this->b * rhs, this->a * rhs);
	}

	color& color::operator *= (const float& rhs) {
		this->r *= rhs; this->g *= rhs; this->b *= rhs; this->a *= rhs; return *this;
	}

	color color::operator / (const float& rhs) const {
		return color(this->r / rhs, this->g / rhs, this->b / rhs, this->a / rhs);
	}

	color& color::operator /= (const float& rhs) {
		this->r /= rhs; this->g /= rhs; this->b /= rhs; this->a /= rhs; return *this;
	}
	//********************************************//
	//* Color struct.                            *//
	//********************************************//
	#pragma endregion

	#pragma region /* rge::math */
	//********************************************//
	//* Math Module.                             *//
	//********************************************//
	float math::lerp(float a, float b, float t) {
		if(t < 0) t = 0;
		if(t > 1) t = 1;
		return (a * (1 - t)) + (b * t);
	}
	//********************************************//
	//* Logging Module.                          *//
	//********************************************//
	#pragma endregion

	#pragma region /* rge::log */
	//********************************************//
	//* Logging Module.                          *//
	//********************************************//
	void log::info(const std::string& msg) {
		std::cout << "[INFO] " << msg << std::endl;
	}

	void log::warning(const std::string& msg) {
		std::cout << "[WARNING] " << msg << std::endl;
	}

	void log::error(const std::string& msg) {
		std::cout << "[ERROR] " << msg << std::endl;
	}
	//********************************************//
	//* Logging Module.                          *//
	//********************************************//
	#pragma endregion

	#pragma region /* rge::engine */
	//********************************************//
	//* Core Engine class.                       *//
	//********************************************//
	engine::engine() {
		is_running = false;
		update_counter = 0;
		physics_counter = 0;
		render_counter = 0;
		update_interval = 1.0F / 60.0F;
		physics_interval = 1.0F / 60.0F;
		render_interval = 1.0F / 60.0F;
		frame_counter = 0;
		frame_timer = 0;
		frame_rate = 0;
		
		time_stamp_1 = std::chrono::system_clock::now();
		time_stamp_2 = std::chrono::system_clock::now();
	}
	
	engine::~engine() {
		delete app_window;
	}
	
	rge::result engine::init() {
		log::info("Initialising RGE...");
		// TODO
		
		app_window = new window();
		
		on_init();
		return rge::OK;
	}
	
	rge::result engine::start(bool wait_until_exit, std::thread** game_thread) {
		log::info("Starting RGE...");
		// TODO
		
		on_start();
		
		is_running = true;
		thread = std::thread(&engine::loop, this);
		
		if(wait_until_exit)
			thread.join();
		
		if(game_thread != nullptr)
			*game_thread = &thread;
		
		return rge::OK;
	}
	
	void engine::loop() {
		while(is_running) {
			// Calculate the elapsed time since last frame.
			time_stamp_2 = std::chrono::system_clock::now();
			std::chrono::duration<float> elapsed_time = time_stamp_2 - time_stamp_1;
			time_stamp_1 = time_stamp_2;
			float delta_time = elapsed_time.count();
			
			// Tick the update routine.
			update_counter += delta_time;
			if(update_counter > update_interval) {
				on_update(update_counter);
				update_counter = 0;
			}
			
			// Tick the physics routine.
			physics_counter += delta_time;
			if(physics_counter > physics_interval) {
				on_physics(physics_counter);
				physics_counter = 0;
			}
			
			// Tick the rendering routine.
			render_counter += delta_time;
			if(render_counter > render_interval) {
				on_render();
				render_counter = 0;
			}
			
			// Calculate fps.
			frame_timer += delta_time;
			frame_counter++;
			if(frame_timer >= 1.0F) {
				frame_timer -= 1.0F;
				frame_rate = frame_counter;
				frame_counter = 0;
				
				//std::cout << "fps: " << frame_counter << std::endl;
			}
		}
	}
	
	rge::result engine::command(const std::string& cmd) {
		if(on_command(cmd))
			return rge::OK;
		   
		if(cmd == "exit" || cmd == "quit") {
			exit();
		} else if(cmd == "rge_version") {
			log::info("RGE VERSION: 0.00.1");
		} else {
			return rge::FAIL;
		}
		
		return rge::OK;
	}
	
	rge::result engine::exit() {
		is_running = false;
		
		// TODO
		
		on_exit();
		return rge::OK;
	}
	
	int engine::get_frame_rate() const {
		return frame_rate;
	}
	
	bool engine::get_is_running() const {
		return is_running;
	}
	
	void engine::on_update(float delta_time) {}
	void engine::on_physics(float delta_time) {}
	void engine::on_render() {}
	void engine::on_init() {}
	bool engine::on_command(const std::string& cmd) { return false; }
	void engine::on_start() {}
	void engine::on_exit() {}
	//********************************************//
	//* Core Engine class.                       *//
	//********************************************//
	#pragma endregion

	#pragma region /* rge::event */
	//********************************************//
	//* Event class.                             *//
	//********************************************//
	event::event() {
		handled = false;
	}

	bool event::get_handled() const {
		return handled;
	}
	//----------------------------------------------
	key_event::key_event(key::code key_code) : event() {
		this->key_code = key_code;
	}

	key::code key_event::get_key_code() const {
		return key_code;
	}
	//----------------------------------------------
	key_pressed_event::key_pressed_event(key::code key_code) : key_event(key_code) {

	}
	//********************************************//
	//* Event class.                             *//
	//********************************************//
	#pragma endregion

	#pragma region /* rge::transform */
	//********************************************//
	//* Transform class.                         *//
	//********************************************//
	transform::transform() {
		parent = nullptr;
	}

	transform::transform(transform* parent) {
		this->parent = parent;
	}

	transform::transform(vec3 position, quaternion rotation, vec3 scale) {
		parent = nullptr;
		this->position = position;
		this->rotation = rotation;
		this->scale = scale;
	}

	transform::transform(vec3 position, quaternion rotation, vec3 scale, transform* parent) {
		this->parent = parent;
		this->position = position;
		this->rotation = rotation;
		this->scale = scale;
	}

	mat4 transform::get_global_matrix() const {
		mat4 m = mat4::trs(position, rotation, scale);

		if(parent != nullptr)
			return parent->get_global_matrix() * m;
		else
			return m;
	}

	vec3 transform::get_forward() const {
		return rotation * vec3(0, 0, 1);
	}

	vec3 transform::get_up() const {
		return rotation * vec3(0, 1, 0);
	}

	vec3 transform::get_right() const {
		return rotation * vec3(1, 0, 0);
	}

	vec3 transform::get_global_forward() const {
		return get_global_matrix().extract_forward_axis();
	}

	vec3 transform::get_global_up() const {
		return get_global_matrix().extract_up_axis();
	}

	vec3 transform::get_global_right() const {
		return get_global_matrix().extract_right_axis();
	}

	vec3 transform::get_global_position() const {
		return get_global_matrix().extract_translation();
	}

	quaternion transform::get_global_rotation() const {
		return get_global_matrix().extract_rotation();
	}

	void transform::set_global_position(const vec3& position) {
		// TODO
	}
	
	void transform::set_global_rotation(const quaternion& rotation) {
		// TODO
	}
	//********************************************//
	//* Transform class.                         *//
	//********************************************//
	#pragma endregion

	#pragma region /* rge::camera */
	//********************************************//
	//* Camera class.                            *//
	//********************************************//
	camera::camera() {
		transform = new rge::transform(nullptr);
	}

	camera::~camera() {
		delete transform;
	}

	mat4 camera::get_view_matrix() const {
		return view;
	}
	
	mat4 camera::get_projection_matrix() const {
		return projection;
	}

	void camera::set_projection_matrix(float fov, float aspect, float near_plane, float far_plane) {
		float uh, uw, frustum_depth, one_over_depth;

		// General form of the Projection Matrix
    	//
    	// uh = cot(fov / 2) = 1 / tan(fov / 2)
    	// uw / uh = 1 / aspect
    	// 
    	//   uw         0       0       0
    	//    0        uh       0       0
    	//    0         0      f/(f-n)  1
    	//    0         0    -fn/(f-n)  0

		uh = 1.0F / tanf(fov * 0.5F);
		uw = uh / aspect;
		frustum_depth = far_plane - near_plane;
		one_over_depth = 1.0F / frustum_depth;

		projection = mat4::identity();
		projection.m[0][0] = uw;
		projection.m[1][1] = uh;
		projection.m[2][2] = far_plane / (far_plane - near_plane);
		projection.m[3][2] = -far_plane * near_plane / (far_plane - near_plane);
		projection.m[2][3] = 1.0F;
		projection.m[3][3] = 0.0F;
	}
	//********************************************//
	//* Camera class.                            *//
	//********************************************//
	#pragma endregion

	#pragma region /* rge::light */
	//********************************************//
	//* Light class.                             *//
	//********************************************//
	light::light() {
		tint = color(1, 1, 1);
		intensity = 1.0F;
		range = 10;
		type = light_mode::POINT;
	}

	light::~light() {

	}
	//********************************************//
	//* Light class.                             *//
	//********************************************//
	#pragma endregion

	#pragma region /* rge::texture */
	//********************************************//
	//* Texture class.                           *//
	//********************************************//
	texture::texture(int width, int height) {
		this->width = width;
		this->height = height;

		on_disk = false;
		on_cpu = false;
		on_gpu = false;
		data = nullptr;

		allocate();
	}

	texture::~texture() {
		if(data) delete[] data;
	}

	int texture::get_width() const {
		return width;
	}

	int texture::get_height() const {
		return height;
	}

	bool texture::get_on_disk() const {
		return on_disk;
	}

	bool texture::get_on_cpu() const {
		return on_cpu;
	}

	bool texture::get_on_gpu() const {
		return on_gpu;
	}

	color texture::sample(float u, float v) const {
		if(data == nullptr) return color(0, 0, 0);

		int ui = (int)(u * width) % width;
		int vi = (int)(v * height) % height;

		if(ui < 0) ui += width;
		if(vi < 0) vi += height;

		return data[ui + (vi * width)];
	}

	color* texture::get_data() const {
		return data;
	}

	rge::result texture::write_to_disk(const std::string& path) const {
		if(!on_cpu) return rge::FAIL;

		#ifdef RGE_USE_STB_IMAGE_WRITE
		uint8_t* buffer = (uint8_t*)malloc(4 * width * height);
		for(int i = 0; i < width * height; ++i) {
			color c = data[i];
			buffer[i*4] = (uint8_t)(c.r * 255);
			buffer[i*4+1] = (uint8_t)(c.g * 255);
			buffer[i*4+2] = (uint8_t)(c.b * 255);
			buffer[i*4+3] = (uint8_t)(c.a * 255);
		}
		if(!stbi_write_png(path.c_str(), width, height, 4, buffer, 4)) {
			rge::log::error("File write fail.");
			free(buffer);
			return rge::FAIL;
		} else {
			free(buffer);
			return rge::OK;
		}
		#else
		return rge::FAIL;
		#endif
	}

	void texture::allocate() {
		if(data) return;

		data = new color[width * height];
		on_cpu = true;
	}

	//********************************************//
	//* Texture class.                           *//
	//********************************************//
	#pragma endregion

	#pragma region /* rge::material */
	//********************************************//
	//* Material class.                           *//
	//********************************************//
	material::material() {
		texture = nullptr;
		diffuse = color(1,1,1);
		specular = color(1,1,1);
		shininess = 0;
	}

	material::~material() {
		if(texture) delete texture;
	}
	//********************************************//
	//* Texture class.                           *//
	//********************************************//
	#pragma endregion

	#pragma region /* rge::render_target */
	//********************************************//
	//* Render Target class.                     *//
	//********************************************//
	render_target::render_target() : texture(0, 0) {

	}

	render_target::render_target(int width, int height) : texture(width, height) {
		
	}
	//********************************************//
	//* Render Target class.                     *//
	//********************************************//
	#pragma endregion

	#pragma region /* rge::renderer */
	//********************************************//
	//* Renderer class.                          *//
	//********************************************//
	renderer::renderer() {
		target = nullptr;
	}

	renderer::~renderer() {

	}

	rge::result renderer::set_target(render_target* target) {
		this->target = target;
		return rge::OK;
	}

	render_target* renderer::get_target() const {
		return target;
	}

	void renderer::clear(color c) {
		color* data = target->get_data();
		for(int i = 0; i < target->get_width() * target->get_height(); i++)
			data[i] = c;
	}
	//********************************************//
	//* Renderer class.                          *//
	//********************************************//
	#pragma endregion

	#pragma region /* rge::renderer2d */
	//********************************************//
	//* Software Renderer 2D class.              *//
	//********************************************//
	renderer2d::renderer2d() : renderer() {

	}

	renderer2d::~renderer2d() {

	}

	void renderer2d::draw(const texture& texture, const rect& dest) {
		if(!texture.get_on_cpu()) return;
		
	}

	void renderer2d::draw(const texture& texture, const rect& dest, const rect& src) {
		if(!texture.get_on_cpu()) return;

	}
	//********************************************//
	//* Software Renderer 2D class.              *//
	//********************************************//
	#pragma endregion

	#pragma region /* rge::renderer3d */
	//********************************************//
	//* Software Renderer 3D class.              *//
	//********************************************//
	renderer3d::renderer3d() : renderer() {
		world_camera = nullptr;
	}

	renderer3d::~renderer3d() {

	}

	void renderer3d::set_camera(camera* camera) {
		this->world_camera = camera;
	}

	void renderer3d::set_ambience(const color& ambient_color) {
		ambience = ambient_color;
	}

	rge::result renderer3d::draw(
		const mat4& model_to_world,
		const std::vector<vec3>& vertices,
		const std::vector<int>& triangles,
		const std::vector<vec3>& normals,
		const std::vector<vec2>& uvs,
		const material& material)
	{
		if(world_camera == nullptr || target == nullptr) return rge::FAIL;
		
		int i;
		vec3 world_v1;
		vec3 world_v2;
		vec3 world_v3;
		vec3 world_n1;
		vec3 world_n2;
		vec3 world_n3;
		vec4 proj_v1;
		vec4 proj_v2;
		vec4 proj_v3;
		vec3 proj_tri_normal;
		vec3 proj_tri_center;
		vec2 normalized_v1;
		vec2 normalized_v2;
		vec2 normalized_v3;
		vec4 texturespace_v1;
		vec4 texturespace_v2;
		vec4 texturespace_v3;
		vec3 camera_position = world_camera->transform != nullptr ? world_camera->transform->get_global_position() : vec3();
		mat4 world_to_projection = world_camera->get_projection_matrix() * world_camera->get_view_matrix();

		float w = (float)get_target()->get_width();
		float h = (float)get_target()->get_height();

		// Loop through each of the triplets of triangle indices.
		for(i = 0; i < triangles.size(); i += 3) {
			// Transform model vertices to world vertices.
			world_v1 = model_to_world.multiply_point_3x4(vertices[triangles[i]]);
			world_v2 = model_to_world.multiply_point_3x4(vertices[triangles[i+1]]);
			world_v3 = model_to_world.multiply_point_3x4(vertices[triangles[i+2]]);

			// Transform model normals to world normals.
			world_n1 = model_to_world.multiply_vector(normals[triangles[i]]);
			world_n2 = model_to_world.multiply_vector(normals[triangles[i+1]]);
			world_n2 = model_to_world.multiply_vector(normals[triangles[i+2]]);

			// Get the projected vertices that make up the triangle based
			// on these indices.
			proj_v1 = project_world_vertex(world_v1, world_to_projection);
			proj_v2 = project_world_vertex(world_v2, world_to_projection);
			proj_v3 = project_world_vertex(world_v3, world_to_projection);

			if(/* Check if all three projected vertices are within homogeneous clip bounds. */
				proj_v1.x >= -1 && proj_v1.x <= 1 && proj_v1.y >= -1 && proj_v1.y <= 1 &&
				proj_v2.x >= -1 && proj_v2.x <= 1 && proj_v2.y >= -1 && proj_v2.y <= 1 &&
				proj_v3.x >= -1 && proj_v3.x <= 1 && proj_v3.y >= -1 && proj_v3.y <= 1
			) {
				// Calculate the normal of the projected triangle from the cross
			    // product of two of its edges.
				proj_tri_normal = vec3::cross(proj_v2 - proj_v1, proj_v3 - proj_v1);

				// Calculate the centre of the projected triangle.
				proj_tri_center = (proj_v1 + proj_v2 + proj_v3) / 3;

				// Check the dot project of the projected triangle normal and
				// the camera to triangle centre vector - if the dot product is
				// <=0, the normal and vector point at each other, and the triangle
				// must be facing the camera, so we should render it. If the dot
				// product is >0, the are facing the same direction, therefore
				// the triangle is facing away from the camera - don't render it.
				if(vec3::dot(proj_tri_normal, proj_tri_center - camera_position) <= 0) {
					// Normalize our projected vertices so that they are in the range
					// Between 0 and 1 (instead of -1 and 1).
					normalized_v1 = vec2((proj_v1.x + 1) / 2.0F, (proj_v1.y + 1) / 2.0F);
					normalized_v2 = vec2((proj_v2.x + 1) / 2.0F, (proj_v2.y + 1) / 2.0F);
					normalized_v3 = vec2((proj_v3.x + 1) / 2.0F, (proj_v3.y + 1) / 2.0F);

					// Multiply our normalized vertex positions by the render target size
					// to get their position in texture space (or if we were rendering
					// to the screen - screen space).
					texturespace_v1 = vec4(normalized_v1.x * w, normalized_v1.y * h, proj_v1.z, proj_v1.w);
					texturespace_v2 = vec4(normalized_v2.x * w, normalized_v2.y * h, proj_v2.z, proj_v2.w);
					texturespace_v3 = vec4(normalized_v3.x * w, normalized_v3.y * h, proj_v3.z, proj_v3.w);

					// Draw the triangle interpolated between the three vertices,
					// using the colours calculated for these vertices based
					// on the triangle indices.
					draw_interpolated_triangle(
						texturespace_v1,
						texturespace_v2,
						texturespace_v3,
						world_v1,
						world_v2,
						world_v3,
						world_n1,
						world_n2,
						world_n3,
						uvs[triangles[i]],
						uvs[triangles[i+1]],
						uvs[triangles[i+2]],
						material
					);
				}
			}
		}

		return rge::OK;
	}

	void renderer3d::draw_interpolated_triangle(
		const vec4& r_v1,
		const vec4& r_v2,
		const vec4& r_v3,
		const vec3& w_v1,
		const vec3& w_v2,
		const vec3& w_v3,
		const vec3& w_n1,
		const vec3& w_n2,
		const vec3& w_n3,
		const vec2& t_uv1,
		const vec2& t_uv2,
		const vec2& t_uv3,
		const material& material
	) {
		int x, y, p;
		float denom;
		float weight_v1, weight_v2, weight_v3;
		float depth;
		vec3 v;
		vec3 n;
		vec2 uv;
		color diffuse;
		color source;
		color destination;
		vec3 camera_position = world_camera->transform != nullptr ? world_camera->transform->get_global_position() : vec3();
		color* buffer = target->get_data();

		printf("x:%f\n", r_v1.x);

		// Calculate the bounding rectangle of the triangle based on the
		// three vertices.
		int x_min = (int)fminf(r_v1.x, fminf(r_v2.x, r_v3.x));
		int x_max = (int)fmaxf(r_v1.x, fmaxf(r_v2.x, r_v3.x));
		int y_min = (int)fminf(r_v1.y, fminf(r_v2.y, r_v3.y));
		int y_max = (int)fmaxf(r_v1.y, fmaxf(r_v2.y, r_v3.y));

		// Cull the bounding rect to the size of the texture we're rendering to.
		if(x_min < 0) x_min = 0;
		if(x_max > target->get_width()) x_max = target->get_width();
		if(y_min < 0) y_min = 0;
		if(y_max > target->get_height()) y_max = target->get_height();

		printf("xmin:%d\n", x_min);
		printf("xmax:%d\n", x_max);
		printf("ymin:%d\n", y_min);
		printf("ymax:%d\n", y_max);

		// Loop through every pixel in the bounding rect.
		for(y = y_min; y <= y_max; y++) {
			for(x = x_min; x <= x_max; x++) {
				vec2 ps = vec2(x, y);

				// Calculate the weights w1, w2 and w3 for the barycentric
				// coordinates based on the positions of the three vertices.
				denom = (r_v2.y - r_v3.y) * (r_v1.x - r_v3.x) + (r_v3.x - r_v2.x) * (r_v1.y - r_v3.y);
				weight_v1 = ((r_v2.y - r_v3.y) * (ps.x - r_v3.x) + (r_v3.x - r_v2.x) * (ps.y - r_v3.y)) / denom;
				weight_v2 = ((r_v3.y - r_v1.y) * (ps.x - r_v3.x) + (r_v1.x - r_v3.x) * (ps.y - r_v3.y)) / denom;
				weight_v3 = 1.0F - weight_v1 - weight_v2;

				// If w1, w2 and w3 are >= 0, we are inside the triangle (or
				// on an edge, but either way, render the pixel).
				if(weight_v1 >= 0.0F && weight_v2 >= 0.0F && weight_v3 >= 0.0F) {
					// Calculate the position in our buffer based on our x and y values.
					// p = y + (x * get_target()->get_height());
					p = x + (y * get_target()->get_width());

					// Calculate the depth value of this pixel.
					depth = r_v1.z * weight_v1 + r_v2.z * weight_v2 + r_v3.z * weight_v3;

					// If the depth value is less than what is currently in the
					// depth buffer for this pixel.
					if(depth < 10000000000000000000) { // TODO: Depth buffer
						// Calculate the world position for this pixel.
						v = w_v1 * weight_v1 + w_v2 * weight_v2 + w_v3 * weight_v3;

						// Calculate the world normal for this pixel.
						n = w_n1 * weight_v1 + w_n2 * weight_v2 + w_n3 * weight_v3;

						// Calculate the UV coordinate for this pixel.
						uv = t_uv1 * weight_v1 + t_uv2 * weight_v2 + t_uv3 * weight_v3;

						// Base diffuse color from material.
						diffuse = material.diffuse;

						// Sample material texture.
						if(material.texture != nullptr)
							diffuse *= material.texture->sample(uv.x, uv.y);

						// Calculate the pixel colour based on the weighted vertex colours.
						source = calculate_blinn_phong(
							v,
							n,
							diffuse,
							material.specular,
							ambience,
							material.shininess,
							camera_position,
							lights
						);

						// Match alpha to diffuse.
						source.a = diffuse.a;

						buffer[p] = diffuse;

						// Write color to render target.
						// TODO: frameBuffer[bufferPosition] = sourcePixelColour;

						// Update the depth buffer with this depth value.
						// TODO
					}
				}
			}
		}
	}
	
	vec4 renderer3d::project_world_vertex(const vec3& v, const mat4& world_to_projection) {
		vec4 hpv = world_to_projection * vec4(v.x, v.y, v.z, 1);
		return vec4(hpv.x / hpv.w, hpv.y / hpv.w, hpv.z / hpv.w, hpv.w);
	}

	color renderer3d::calculate_blinn_phong(
		const vec3& position,
		const vec3& normal,
		const color& diffuse,
		const color& specular,
		const color& ambient,
		float shininess,
		const vec3& camera_position,
		const std::vector<light*>& lights
	) {
		int i;
		color diffuse_sum = color(0, 0, 0);
		color specular_sum = color(0, 0, 0);
		float light_w;
		vec3 light_pos;
		color light_color;
		float attenuation;
		vec3 normal_direction = vec3::normalize(normal);
		vec3 view_direction = vec3::normalize(camera_position - position);
		vec3 vert_to_light;
		float vert_to_light_mag;
		vec3 light_direction;
		color diffuse_reflection;
		color specular_reflection;
		color ambient_lighting = ambient * diffuse;
		light* light;

		// Loop through each light source.
		for(i = 0; i < lights.size(); ++i) {
			light = lights[i];

			if(light->transform == nullptr)
				continue;

			// Calculate the light position and colour based on the light properties
			// light_w is set to 0 if the light is directional, and 1 otherwise.
			if(light->type == light_mode::DIRECTIONAL) {
				light_pos = light->transform->get_global_backward();
				light_w = 0.0F;
				light_color = light->tint * light->intensity;
				attenuation = 1.0F;
			} else {
				light_pos = light->transform->get_global_position();
				light_w = 1.0F;

				// For non direcitonal lights, we'll figure out the light
				// color per pixel, based on the distance from the light
				// to the pixel.
				light_color = color(0, 0, 0);

				// Calculate the distance from the light to the pixel, and 1/distance.
				vert_to_light = light_pos - position;
				vert_to_light_mag = vert_to_light.magnitude();

				attenuation = 1.0F / vert_to_light_mag;

				// Calculate the colour based on the distance and light range.
				if(vert_to_light_mag < light->range)
					light_color *= light->intensity;
			}

			// Calculate light direction.
			light_direction = light_pos - (position * light_w);

			// Calculate diffuse lighting.
			diffuse_reflection = light_color * diffuse * fmaxf(0, vec3::dot(normal_direction, view_direction)) * attenuation;

			// Calculate Specular reflection if the normal is pointing in the
			// lights direction.
			if(vec3::dot(normal_direction, light_direction) < 0.0) {
				specular_reflection = color(0, 0, 0);
			} else {
				// Calculate the specular colour using Blinn-Phong lighting
				specular_reflection = light_color * specular * powf(fmaxf(0.0F, vec3::dot(normal_direction, vec3::normalize(light_direction + view_direction))), shininess * 128) * attenuation;
			}

			diffuse_sum += diffuse_reflection;
			specular_sum += specular_reflection;
		}

		// The final color for this pixel is the sum of the ambient, diffuse and specular.
		return ambient_lighting + diffuse_sum + specular_sum;
	}
	//********************************************//
	//* Software Renderer 3D class.              *//
	//********************************************//
	#pragma endregion

	#pragma region /* rge::window */
	//********************************************//
	//* Window class.                            *//
	//********************************************//
	namespace platform {
		#ifdef SYS_WINDOWS
		class window_impl {
		public:
			window_impl(window* window) {
				this->window = window;
			}
			~window_impl() {}

		public:
			int width, height;
			window* window;
		};
		#elif SYS_LINUX
		class window_impl {
		public:
			window_impl(window* window) {
				this->window = window;
			}
			~window_impl() {}

		public:
			int width, height;
			window* window;
		};
		#elif SYS_MACOSX
		class window_impl {
		public:
			window_impl(window* window) {
				this->window = window;
			}
			~window_impl() {}

		public:
			int width, height;
			window* window;
		};
		#endif
	}

	window::window() {
		impl = new platform::window_impl(this);
		impl->width = 800;
		impl->height = 600;
	}

	window::~window() {
		delete impl;
	}

	rge::result window::create() {
		return rge::OK;
	}

	rge::result window::set_size(int width, int height) {
		if(width < 1) return rge::FAIL;
		if(height < 1) return rge::FAIL;
		impl->width = width;
		impl->height = height;
		return rge::OK;
	}

	void window::get_size(int& width, int& height) const {
		width = impl->width;
		height = impl->height;
	}
	//********************************************//
	//* Windows implementation of window class.  *//
	//********************************************//
	#pragma endregion
}

#endif /* RGE_IMPL */