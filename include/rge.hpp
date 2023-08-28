/* RetroGameEngine (RGE)

Author: Jeremy Kiel
Version: 0.00.1
License: MIT
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Copyright (c) 2023 Jeremy Kiel

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/


#define RGE_VERSION 0001


#ifndef RGE_API
#define RGE_API


#include <cstdint>
#include <cstdarg>
#include <cmath>
#include <cstring>
#include <string>
#include <chrono>
#include <thread>
#include <iostream>
#include <functional>
#include <vector>
#include <memory>


#define ptr(T) std::shared_ptr<T>
#define alloc(T) std::make_shared<T>


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
class platform;


enum result {
	FAIL = 0,
	OK = 1
};


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
	static float cross(const vec2& a, const vec2& b);
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
	static quaternion yaw_pitch_roll(float yaw, float pitch, float roll);
	static quaternion euler(float x, float y, float z);

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
	static mat4 zero() { return mat4(vec4(0, 0, 0, 0), vec4(0, 0, 0, 0), vec4(0, 0, 0, 0), vec4(0, 0, 0, 0)); }
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
	#define DEG_2_RAD 0.0174532924F
	#define RAD_2_DEG 57.29578F
	float lerp(float a, float b, float t);
	float inverse_lerp(float a, float b, float v);
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
	void info(const char* msg, ...);
	void warning(const char* msg, ...);
	void error(const char* msg, ...);
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
	~engine();

public:
	void create(bool wait_until_exit = true);
	rge::result exit();
	rge::result command(const std::string& cmd);
	void wait_for_exit();
	int get_frame_rate() const;
	bool get_is_running() const;
	platform* get_platform() const;
	renderer* get_renderer() const;

public:
	float update_interval;
	float physics_interval;
	float render_interval;

protected:
	virtual void on_init() {}
	virtual bool on_command(const std::string& cmd) { return false; }
	virtual void on_start() {}
	virtual void on_update(float delta_time) {}
	virtual void on_physics(float delta_time) {}
	virtual void on_render() {}
	virtual void on_exit() {}

private:
	void configure();
	void procedure();
	rge::result init();
	rge::result start();
	void loop();

private:
	bool has_init;
	bool is_running;
	std::thread thread;
	bool multi_threaded;
	platform* platform_impl;
	renderer* renderer_impl;
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

	void set_perspective(float fov, float aspect, float near_plane, float far_plane);
	void set_orthographic(float left_plane, float right_plane, float top_plane, float bottom_plane, float near_plane, float far_plane);

public:
	transform* transform;

private:
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
	ptr(transform) transform;
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
	void dump_to_raw_buffer(uint8_t* buffer) const;

	// NOTE: TESTING FUNCTION
	rge::result write_to_disk(const std::string& path) const;
	static ptr(texture) read_from_disk(const std::string& path);



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
	ptr(texture) texture;
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
class render_target {
public:
	render_target();
	render_target(int width, int height);

public:
	rge::result resize(int width, int height);

	int get_width() const;
	int get_height() const;

	texture* get_frame_buffer() const;
	texture* get_depth_buffer() const;
	

private:
	int width;
	int height;
	texture* frame_buffer;
	texture* depth_buffer;
};
//********************************************//
//* Render Target class.                     *//
//********************************************//
#pragma endregion


#pragma region /* rge::platform */
//********************************************//
//* Base Platform Class                      *//
//********************************************//
class platform {
public:
	virtual rge::result init(rge::engine* engine) = 0;
	virtual rge::result create_window() = 0;
	virtual void set_window_title(const char* title) = 0;
	virtual void poll_events() = 0;
	virtual void refresh_window() = 0;

public:
	virtual ~platform() {}

protected:
	platform() {}
};
//********************************************//
//* Base Platform Class                      *//
//********************************************//
#pragma endregion


#pragma region /* rge::renderer */
//********************************************//
//* Base Renderer class                      *//
//********************************************//
class renderer {
public:
	void set_camera(camera* camera);
	void set_ambience(const color& ambient_color);
	rge::result set_target(render_target* target);
	render_target* get_target() const;

public:
	virtual rge::result init(platform* platform) = 0;
	virtual render_target* create_render_target(int width, int height) = 0;
	virtual void free_render_target(render_target* target) = 0;
	virtual void clear(color background) = 0;
	virtual void display() = 0;
	virtual rge::result draw(
		const mat4& model_to_world,
		const std::vector<vec3>& vertices,
		const std::vector<int>& triangles,
		const std::vector<vec3>& normals,
		const std::vector<vec2>& uvs,
		const material& material
	) = 0;
	virtual void draw(
		const texture& texture,
		const rect& dest,
		const rect& src
	) = 0;

	void draw(const texture& texture, const rect& dest) {
		draw(
			texture,
			dest,
			rge::rect(
				0,
				0,
				float(texture.get_width()),
				float(texture.get_height())
			)
		);
	}

public:
	virtual void on_window_resized(int width, int height) {}

public:
	virtual ~renderer() {}

protected:
	renderer();

protected:
	camera* input_camera;
	render_target* output_render;
	color ambient_color;
};
//********************************************//
//* Base Renderer class                      *//
//********************************************//
#pragma endregion


} /* namespace rge */


#endif /* RGE_API */


#ifdef RGE_IMPL
#undef RGE_IMPL


// Forward declaration of the user main() function.
int main(int argc, char** argv);


#pragma region /* System Configuration Check */
//********************************************//
//* System Configuration Check               *//
//********************************************//
#ifdef SYS_WINDOWS
#ifdef RGE_PLATFORM_SET
#error Multiple platforms set!
#endif
#define RGE_PLATFORM_SET
#endif

#ifdef SYS_LINUX
#ifdef RGE_PLATFORM_SET
#error Multiple platforms set!
#endif
#define RGE_PLATFORM_SET
#endif

#ifdef SYS_MACOSX
#ifdef RGE_PLATFORM_SET
#error Multiple platforms set!
#endif
#define RGE_PLATFORM_SET
#endif

#ifndef RGE_PLATFORM_SET
#error No platform set!
#endif

#ifdef SYS_SOFTWARE_GL
#ifdef RGE_RENDERER_SET
#error Multiple renderers set!
#endif
#define RGE_RENDERER_SET
#endif

#ifdef SYS_OPENGL_1_0
#ifdef RGE_RENDERER_SET
#error Multiple renderers set!
#endif
#define RGE_RENDERER_SET
#endif

#ifdef SYS_OPENGL_3_3
#ifdef RGE_RENDERER_SET
#error Multiple renderers set!
#endif
#define RGE_RENDERER_SET
#endif

#ifndef RGE_RENDERER_SET
#error No renderer set!
#endif
//********************************************//
//* System Configuration Check               *//
//********************************************//
#pragma endregion


#pragma region /* Platform Dependancies */
//********************************************//
//* Platform Dependancies                    *//
//********************************************//
#ifdef SYS_WINDOWS
#include <windows.h>
#pragma comment(lib, "user32.lib")
class windows;
#endif /* SYS_WINDOWS */

#ifdef SYS_LINUX
class linux;
#endif /* SYS_LINUX */

#ifdef SYS_MACOSX
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#include <objc/runtime.h>
#include <objc/message.h>
#include <objc/NSObjCRuntime.h>
class macosx;
#endif /* SYS_MACOSX */
//********************************************//
//* Platform Dependancies                    *//
//********************************************//
#pragma endregion


#pragma region /* Renderer Dependancies */
//********************************************//
//* Renderer Dependancies                    *//
//********************************************//
#ifdef SYS_SOFTWARE_GL
class software_gl;
#endif /* SYS_SOFTWARE_GL */

#ifdef SYS_OPENGL_1_0
#ifdef SYS_WINDOWS

#include <dwmapi.h>
#include <GL/gl.h>

#pragma comment(lib, "dwmapi.lib")
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "opengl32.lib")

typedef HDC gl_device_context_t;
typedef HGLRC gl_render_context_t;

#endif /* SYS_WINDOWS */

#ifdef SYS_LINUX

#endif /* SYS_LINUX */

#ifdef SYS_MACOSX
#include <OpenGL/OpenGL.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#endif /* SYS_MACOSX */

class opengl_1_0;
#endif /* SYS_OPENGL_1_0 */

#ifdef SYS_OPENGL_3_3

class opengl_3_3;
#endif /* SYS_OPENGL_3_3 */
//********************************************//
//* Renderer Dependancies                    *//
//********************************************//
#pragma endregion


#pragma region /* Extra Feature Dependancies */
//********************************************//
//* Extra Feature Dependancies               *//
//********************************************//
#ifdef RGE_USE_STB_IMAGE_WRITE
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>
#endif /* RGE_USE_STB_IMAGE_WRITE */

#ifdef RGE_USE_STB_IMAGE
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#endif /* RGE_USE_STB_IMAGE */
//********************************************//
//* Extra Feature Dependancies               *//
//********************************************//
#pragma endregion


#define LOG_MISSING_DEP(OP, LIB) rge::log::error("Operation '"#OP"' failed! Dependancy not installed: "#LIB);


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

float vec2::cross(const vec2& a, const vec2& b) {
	return a.x * b.y - a.y * b.x;
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
	return -vec3(
		(v1.y * v2.z) - (v1.z * v2.y),
		(v1.z * v2.x) - (v1.x * v2.z),
		(v1.x * v2.y) - (v1.y * v2.x)
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

quaternion quaternion::yaw_pitch_roll(float yaw, float pitch, float roll) {
	float half_roll = roll * 0.5f;
	float half_pitch = pitch * 0.5f;
	float half_yaw = yaw * 0.5f;

	float sin_roll = sinf(half_roll);
	float cos_roll = cosf(half_roll);
	float sin_pitch = sinf(half_pitch);
	float cos_pitch = cosf(half_pitch);
	float sin_yaw = sinf(half_yaw);
	float cos_yaw = cosf(half_yaw);

	return quaternion(
		(cos_yaw * sin_pitch * cos_roll) + (sin_yaw * cos_pitch * sin_roll),
		(sin_yaw * cos_pitch * cos_roll) - (cos_yaw * sin_pitch * sin_roll),
		(cos_yaw * cos_pitch * sin_roll) - (sin_yaw * sin_pitch * cos_roll),
		(cos_yaw * cos_pitch * cos_roll) + (sin_yaw * sin_pitch * sin_roll)
	);
}

quaternion quaternion::euler(float x, float y, float z) {
	// TODO

	return quaternion(
		0,0,0,1
	);
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
	return result;
}

vec3 mat4::multiply_vector(const vec3& v) const {
	vec3 result = vec3();
	result.x = m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z;
	result.y = m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z;
	result.z = m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z;
	return result;
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

float math::inverse_lerp(float a, float b, float v) {
	return (v - a) / (b - a);
}
//********************************************//
//* Logging Module.                          *//
//********************************************//
#pragma endregion


#pragma region /* rge::log */
//********************************************//
//* Logging Module.                          *//
//********************************************//
namespace log { const int BUFFER_SIZE = 512; }

void log::info(const char* msg, ...) {
	char buffer[log::BUFFER_SIZE];
    std::va_list args;
    va_start(args, msg);
    #ifdef SYS_WINDOWS
	vsprintf_s(buffer, log::BUFFER_SIZE, msg, args);
	#else
	vsprintf(buffer, msg, args);
	#endif
    va_end(args);
	std::cout << "[INFO] " << buffer << std::endl;
}

void log::warning(const char* msg, ...) {
	char buffer[log::BUFFER_SIZE];
    std::va_list args;
    va_start(args, msg);
    #ifdef SYS_WINDOWS
	vsprintf_s(buffer, log::BUFFER_SIZE, msg, args);
	#else
	vsprintf(buffer, msg, args);
	#endif
    va_end(args);
	std::cout << "[WARNING] " << msg << std::endl;
}

void log::error(const char* msg, ...) {
	char buffer[log::BUFFER_SIZE];
    std::va_list args;
    va_start(args, msg);
    #ifdef SYS_WINDOWS
	vsprintf_s(buffer, log::BUFFER_SIZE, msg, args);
	#else
	vsprintf(buffer, msg, args);
	#endif
    va_end(args);
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
	has_init = false;
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
	platform_impl = nullptr;
	renderer_impl = nullptr;
	multi_threaded = false;

	configure();
}

engine::~engine() {
	delete renderer_impl;
	delete platform_impl;
}

void engine::create(bool wait_until_exit) {
	if(wait_until_exit) {
		procedure();
	} else {
		multi_threaded = true;
		thread = std::thread(&engine::procedure, this);
		while(!is_running) continue;
	}
}

void engine::procedure() {
	if(init() != rge::OK) return;
	if(start() != rge::OK) return;
	loop();
}

rge::result engine::init() {
	if(has_init) {
		log::error("RGE core has already been initialised!");
		return rge::FAIL;
	}

	log::info("Initialising RGE...");

	if(platform_impl == nullptr || renderer_impl == nullptr) return rge::FAIL;

	if(platform_impl->init(this) != rge::OK) {
		log::error("Failed to initialise platform module!");
		return rge::FAIL;
	}

	if(platform_impl->create_window() != rge::OK) {
		log::error("Failed to create window!");
		return rge::FAIL;
	}

	if(renderer_impl->init(platform_impl) != rge::OK) {
		log::error("Failed to initialise renderer module!");
		return rge::FAIL;
	}

	on_init();
	has_init = true;
	return rge::OK;
}

rge::result engine::start() {
	if(!has_init) {
		log::error("RGE core has not been initialised!");
		return rge::FAIL;
	}

	log::info("Starting RGE...");
	// TODO
	
	on_start();
	
	is_running = true;
	
	return rge::OK;
}

void engine::loop() {
	while(is_running) {
		platform_impl->poll_events();

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
			renderer_impl->display();
			render_counter = 0;
		}
		
		// Calculate fps.
		frame_timer += delta_time;
		frame_counter++;
		if(frame_timer >= 1.0F) {
			frame_timer -= 1.0F;
			frame_rate = frame_counter;
			frame_counter = 0;
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
	} else if(cmd == "fps") {
		rge::log::info("fps: %d", frame_rate);
	} else {
		return rge::FAIL;
	}
	
	return rge::OK;
}

rge::result engine::exit() {
	if(!is_running) return rge::FAIL;

	on_exit();
	
	printf("\n[Press any key to exit]");

	is_running = false;
	return rge::OK;
}

int engine::get_frame_rate() const {
	return frame_rate;
}

bool engine::get_is_running() const {
	return is_running;
}

platform* engine::get_platform() const {
	return platform_impl;
}

renderer* engine::get_renderer() const {
	return renderer_impl;
}

void engine::wait_for_exit() {
	if(multi_threaded)
		thread.join();
}
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
	this->scale = vec3(1, 1, 1);
}

transform::transform(transform* parent) {
	this->parent = parent;
	this->scale = vec3(1, 1, 1);
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
	transform = new rge::transform();
}

camera::~camera() {
	delete transform;
}

mat4 camera::get_view_matrix() const {
	mat4 r = mat4::identity();

	if(transform == nullptr) return r;

	mat4 m = transform->get_global_matrix();
	vec3 pos = m.extract_translation();
	vec3 rgt = m.extract_right_axis();
	vec3 up = m.extract_up_axis();
	vec3 fwd = m.extract_forward_axis();
	
	r.m[0][0] = rgt.x;
	r.m[1][0] = rgt.y;
	r.m[2][0] = rgt.z;
	r.m[0][1] = up.x;
	r.m[1][1] = up.y;
	r.m[2][1] = up.z;
	r.m[0][2] = fwd.x;
	r.m[1][2] = fwd.y;
	r.m[2][2] = fwd.z;
	r.m[0][3] = -vec3::dot(rgt, pos);
	r.m[1][3] = -vec3::dot(up, pos);
	r.m[2][3] = -vec3::dot(fwd, pos);

	// NOTE: Debugging
	// printf("px: %f\n", pos.x);
	// printf("py: %f\n", pos.y);
	// printf("pz: %f\n", pos.z);
	// printf("rx: %f\n", rgt.x);
	// printf("ry: %f\n", rgt.y);
	// printf("rz: %f\n", rgt.z);
	// printf("ux: %f\n", up.x);
	// printf("uy: %f\n", up.y);
	// printf("uz: %f\n", up.z);
	// printf("fx: %f\n", fwd.x);
	// printf("fy: %f\n", fwd.y);
	// printf("fz: %f\n", fwd.z);

	return r;
}

mat4 camera::get_projection_matrix() const {
	return projection;
}

void camera::set_perspective(float fov, float aspect, float near_plane, float far_plane) {
	// float uh, uw, frustum_depth, one_over_depth;

	// General form of the Projection Matrix
	//
	// uh = cot(fov / 2) = 1 / tan(fov / 2)
	// uw / uh = 1 / aspect
	// 
	//   uw         0       0       0
	//    0        uh       0       0
	//    0         0      f/(f-n)  1
	//    0         0    -fn/(f-n)  0

	fov *= DEG_2_RAD;

	/*
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
	*/

	projection = mat4::zero();
	projection.m[0][0] = 1.0F / (aspect * tanf(fov / 2.0F));
	projection.m[1][1] = 1.0F / tanf(fov / 2.0F);
	projection.m[2][2] = -((-near_plane - far_plane) / (near_plane - far_plane));
	projection.m[2][3] = (2 * far_plane * near_plane) / (near_plane - far_plane);
	projection.m[3][2] = -1.0F;
}

void camera::set_orthographic(float left_plane, float right_plane, float top_plane, float bottom_plane, float near_plane, float far_plane) {
	projection = mat4::zero();
	projection.m[0][0] = 2.0F / (right_plane - left_plane);
	projection.m[1][1] = 2.0F / (top_plane - bottom_plane);
	// projection.m[2][2] = 1.0F / (far_plane - near_plane);
	projection.m[2][2] = 2.0F / (far_plane - near_plane);

	projection.m[0][3] = -((right_plane + left_plane) / (right_plane - left_plane));
	projection.m[1][3] = -((top_plane + bottom_plane) / (top_plane - bottom_plane));
	// projection.m[2][3] = near_plane / (near_plane - far_plane);
	projection.m[2][3] = -((far_plane + near_plane) / (far_plane - near_plane));

	projection.m[3][3] = 1.0F;
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

void texture::dump_to_raw_buffer(uint8_t* buffer) const {
	if(!on_cpu) return;

	for(int i = 0; i < width * height; i++) {
		color c = data[i];
		buffer[i * 4] = (uint8_t)(c.r * 255);
		buffer[i * 4 + 1] = (uint8_t)(c.g * 255);
		buffer[i * 4 + 2] = (uint8_t)(c.b * 255);
		buffer[i * 4 + 3] = (uint8_t)(c.a * 255);
	}
}

rge::result texture::write_to_disk(const std::string& path) const {
	if(!on_cpu) return rge::FAIL;

	#ifdef RGE_USE_STB_IMAGE_WRITE
	uint8_t* buffer = (uint8_t*)malloc(4 * width * height);
	dump_to_raw_buffer(buffer);
	/*
	if(!stbi_write_png(path.c_str(), width, height, 4, buffer, 4)) {
		rge::log::error("File write fail.");
		free(buffer);
		return rge::FAIL;
	} */
	if(!stbi_write_bmp(path.c_str(), width, height, 4, buffer)) {
		rge::log::error("File write fail.");
		free(buffer);
		return rge::FAIL;
	} else {
		free(buffer);
		return rge::OK;
	}
	#else
	LOG_MISSING_DEP(write_texture_to_disk, stb_image_write.h)
	return rge::FAIL;
	#endif
}

ptr(texture) texture::read_from_disk(const std::string& path) {
	// TODO: Check if file exists.

	#ifdef RGE_USE_STB_IMAGE

	int i, w, h, ch;
	uint8_t* input_buffer = stbi_load(path.c_str(), &w, &h, &ch, 4);

	if(ch != 3 && ch != 4) {
		rge::log::error("Texture file read failed: only RGB & RGBA formats supported!");
		stbi_image_free(input_buffer);
		return nullptr;
	}

	ptr(texture) tex = alloc(texture)(w, h);
	color* tex_data = tex->get_data();
	color c;
	for(i = 0; i < w * h; ++i) {
		if(ch == 3) {
			c = color(
				input_buffer[i*3] / 255.0F,
				input_buffer[i*3+1] / 255.0F,
				input_buffer[i*3+2] / 255.0F
			);
		} else if(ch == 4) {
			c = color(
				input_buffer[i*4] / 255.0F,
				input_buffer[i*4+1] / 255.0F,
				input_buffer[i*4+2] / 255.0F,
				input_buffer[i*4+3] / 255.0F
			);
		}

		tex_data[i] = c;
	}

	stbi_image_free(input_buffer);
	return tex;
	#else
	LOG_MISSING_DEP(read_texture_from_disk, stb_image.h)
	return nullptr;
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
//* Material class.                          *//
//********************************************//
material::material() {
	diffuse = color(1,1,1);
	specular = color(1,1,1);
	shininess = 0;
}

material::~material() {
	
}
//********************************************//
//* Material class.                          *//
//********************************************//
#pragma endregion


#pragma region /* rge::render_target */
//********************************************//
//* Render Target class.                     *//
//********************************************//
render_target::render_target() {
	width = 1;
	height = 1;
	frame_buffer = nullptr;
	depth_buffer = nullptr;
}

render_target::render_target(int width, int height) {
	if(width < 1) width = 1;
	if(height < 1) height = 1;

	this->width = width;
	this->height = height;

	frame_buffer = new texture(width, height);
	depth_buffer = new texture(width, height);
}

rge::result render_target::resize(int width, int height) {
	if(width < 0) return rge::FAIL;
	if(height < 0) return rge::FAIL;

	this->width = width;
	this->height = height;

	if(frame_buffer) delete frame_buffer;
	if(depth_buffer) delete depth_buffer;

	frame_buffer = new texture(width, height);
	depth_buffer = new texture(width, height);

	return rge::OK;
}

int render_target::get_width() const {
	return width;
}

int render_target::get_height() const {
	return height;
}

texture* render_target::get_frame_buffer() const {
	return frame_buffer;
}

texture* render_target::get_depth_buffer() const {
	return depth_buffer;
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
	input_camera = nullptr;
	output_render = nullptr;
	ambient_color = color(0,0,0);
}

void renderer::set_camera(camera* camera) {
	input_camera = camera;
}

void renderer::set_ambience(const color& ambient_color) {
	this->ambient_color = ambient_color;
}

rge::result renderer::set_target(render_target* target) {
	output_render = target;
	return rge::OK;
}

render_target* renderer::get_target() const {
	return output_render;
}
//********************************************//
//* Renderer class.                          *//
//********************************************//
#pragma endregion


#pragma region /* rge::windows */
//********************************************//
//* Windows platform class.                  *//
//********************************************//
#ifdef SYS_WINDOWS
// Real win32 entry point for release mode (DesktopApp).
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {
	// TODO: Get entry parameters.

	return main(0, nullptr);
}

class windows : public platform {
public:
	const LPCWSTR CLASS_NAME = L"RETRO_GAME_ENGINE_CLASS";
	const LPCWSTR WINDOW_NAME = L"RETRO_GAME_ENGINE_WINDOW";
	WNDCLASS config;
	HWND handle;
	static engine* engine_instance;

	windows() {

	}

public:
	rge::result init(rge::engine* engine) override {
		this->engine_instance = engine;

		ZeroMemory(&config, sizeof(WNDCLASS));
		config.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		config.hCursor = LoadCursor(NULL, IDC_ARROW);
		config.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
		config.hInstance = GetModuleHandle(nullptr);
		config.lpfnWndProc = on_event;
		config.cbClsExtra = 0;
		config.cbWndExtra = 0;
		config.lpszMenuName = nullptr;
		config.hbrBackground = nullptr;
		config.lpszClassName = CLASS_NAME;

		if(!RegisterClass(&config)) {
			rge::log::error("Failed to register platform class (winapi).");
			return rge::FAIL;
		}

		// TODO: Key mapping
		
		return rge::OK;
	}

	rge::result create_window() override {
		DWORD style_ex = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
		DWORD style = WS_CAPTION | WS_SYSMENU | WS_VISIBLE | WS_THICKFRAME;

		int width = 800; // TODO: Temp
		int height = 600;
		RECT rWndRect = { 0, 0, width, height };
		AdjustWindowRectEx(&rWndRect, style, FALSE, style_ex);
		width = rWndRect.right - rWndRect.left;
		height = rWndRect.bottom - rWndRect.top;

		handle = CreateWindowEx(
			style_ex,
			CLASS_NAME,
			WINDOW_NAME,
			style,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			width,
			height,
			nullptr,
			nullptr,
			config.hInstance,
			0
		);

		if(handle == nullptr) {
			rge::log::error("Failed to create window (winapi).");
			return rge::FAIL;
		}

		return rge::OK;
	}

	void set_window_title(const char* title) override {
		// TODO
	}

	void poll_events() override {
		MSG msg;

		while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	void refresh_window() override {
		// TODO
	}

	static LRESULT CALLBACK on_event(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
		switch(msg) {
			case WM_CLOSE: {
				engine_instance->exit();
				break;
			}

			case WM_DESTROY: {
				PostQuitMessage(0);
				DestroyWindow(hwnd);
				break;
			}

			case WM_SIZE: {
				engine_instance->get_renderer()->on_window_resized(LOWORD(lParam), HIWORD(lParam)); // TODO: Change to proper event propagation.
				break;
			}

			default:
			{
				return DefWindowProc(hwnd, msg, wParam, lParam);
			}
		}

		return 0;
	}

};

engine* windows::engine_instance = nullptr;

#endif /* SYS_WINDOWS */
//********************************************//
//* Windows platform class.                  *//
//********************************************//
#pragma endregion


#pragma region /* rge::linux */
//********************************************//
//* Linux platform class.                    *//
//********************************************//
#ifdef SYS_LINUX
class linux : public platform {

};
#endif /* SYS_LINUX */
//********************************************//
//* Linux platform class.                    *//
//********************************************//
#pragma endregion


#pragma region /* rge::macosx */
//********************************************//
//* MacOS X platform class.                  *//
//********************************************//
#ifdef SYS_MACOSX
class macosx : public platform {
private:
	int window_width;
	int window_height;

public:
	macosx() {
		window_width = 0;
		window_height = 0;
	}

	rge::result init(rge::engine* engine) override {
		Class GLUTViewClass = objc_getClass("GLUTView");

		// SEL scrollWheelSel = sel_registerName("scrollWheel:");
		// bool resultAddMethod = class_addMethod(GLUTViewClass, scrollWheelSel, (IMP)scrollWheelUpdate, "v@:@");
		// assert(resultAddMethod);

		int argc = 0;
		char* argv[1] = { (char*)"" };
		glutInit(&argc, argv);
		glutInitWindowPosition(0, 0);
		glutInitWindowSize(512, 512);
		glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);

		// TODO: Key mapping
		
		return rge::OK;
	}

	rge::result create_window() override {
		// Creates the window and the OpenGL context for it.
		glutCreateWindow("OneLoneCoder.com - Pixel Game Engine");
		glEnable(GL_TEXTURE_2D); // Turn on texturing.
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

		if(false) {
			window_width = glutGet(GLUT_SCREEN_WIDTH);
			window_height = glutGet(GLUT_SCREEN_HEIGHT);
			glutFullScreen();
		} else {
			if(window_width > glutGet(GLUT_SCREEN_WIDTH) || window_height > glutGet(GLUT_SCREEN_HEIGHT)) {
				rge::log::error("The specified window dimensions do not fit on your screen.");
				return rge::FAIL;
			}
			glutReshapeWindow(window_width, window_height - 1);
		}
		return rge::OK;
	}

	void set_window_title(const char* title) override {
		glutSetWindowTitle(title);
	}

	void poll_events() override {
		// TODO
	}

	void refresh_window() override {
		// TODO
	}
};
#endif /* SYS_MACOSX */
//********************************************//
//* MacOS X platform class.                  *//
//********************************************//
#pragma endregion


#pragma region /* rge::software_gl */
//********************************************//
//* Software Renderer                        *//
//********************************************//
#ifdef SYS_SOFTWARE_GL
class software_gl : public renderer {
private:
	std::vector<light*> lights; // TODO: Move to rge::renderer.


public:
	software_gl() : renderer() {

	}

public:
	rge::result init(platform* platform) override {
		return rge::OK;
	}

	void clear(color background) override {
		color* frame_buffer = output_render->get_frame_buffer()->get_data();
		color* depth_buffer = output_render->get_depth_buffer()->get_data();
		for(int i = 0; i < output_render->get_width() * output_render->get_height(); i++) {
			frame_buffer[i] = background;
			depth_buffer[i] = color(1, 0, 0, 0);
		}
	}

	void display() override {
		#ifdef SYS_WINDOWS
		uint8_t* buffer;
		// TODO: output_render->get_depth_buffer()->dump_to_raw_buffer(buffer);
		#endif
	}

	rge::result draw(
		const mat4& model_to_world,
		const std::vector<vec3>& vertices,
		const std::vector<int>& triangles,
		const std::vector<vec3>& normals,
		const std::vector<vec2>& uvs,
		const material& material
	) override {
		if(input_camera == nullptr || output_render == nullptr) return rge::FAIL;

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
		vec3 camera_position = input_camera->transform != nullptr ? input_camera->transform->get_global_position() : vec3();
		mat4 world_to_projection = input_camera->get_projection_matrix() * input_camera->get_view_matrix();

		float w = (float)get_target()->get_width();
		float h = (float)get_target()->get_height();

		// Loop through each of the triplets of triangle indices.
		for(i = 0; i < triangles.size(); i += 3) {
			// Transform model vertices to world vertices.
			world_v1 = model_to_world.multiply_point_3x4(vertices[triangles[i]]);
			world_v2 = model_to_world.multiply_point_3x4(vertices[triangles[i + 1]]);
			world_v3 = model_to_world.multiply_point_3x4(vertices[triangles[i + 2]]);

			// Transform model normals to world normals.
			world_n1 = model_to_world.multiply_vector(normals[triangles[i]]);
			world_n2 = model_to_world.multiply_vector(normals[triangles[i + 1]]);
			world_n2 = model_to_world.multiply_vector(normals[triangles[i + 2]]);

			// Get the projected vertices that make up the triangle based
			// on these indices.
			proj_v1 = project_world_vertex(world_v1, world_to_projection);
			proj_v2 = project_world_vertex(world_v2, world_to_projection);
			proj_v3 = project_world_vertex(world_v3, world_to_projection);

			// Cheap hack: convert camera space z from [-1, 1] to [0, 1]
			proj_v1.z /= 2.0F;
			proj_v1.z += 0.5F;
			proj_v2.z /= 2.0F;
			proj_v2.z += 0.5F;
			proj_v3.z /= 2.0F;
			proj_v3.z += 0.5F;

			// NOTE: Debugging
			// printf("p1x: %f, p1y: %f, p1z: %f\n", proj_v1.x, proj_v1.y, proj_v1.z);
			// printf("p2x: %f, p2y: %f, p2z: %f\n", proj_v2.x, proj_v2.y, proj_v2.z);
			// printf("p3x: %f, p3y: %f, p3z: %f\n", proj_v3.x, proj_v3.y, proj_v3.z);

			if(/* Check if all three projected vertices are within homogeneous clip bounds. */
			   proj_v1.x >= -1 && proj_v1.x <= 1 && proj_v1.y >= -1 && proj_v1.y <= 1 &&
			   proj_v2.x >= -1 && proj_v2.x <= 1 && proj_v2.y >= -1 && proj_v2.y <= 1 &&
			   proj_v3.x >= -1 && proj_v3.x <= 1 && proj_v3.y >= -1 && proj_v3.y <= 1
			   ) {
				// NOTE: Debugging
				// printf("inside bounds\n");

				// Calculate the normal of the projected triangle from the cross
				// product of two of its edges.
				proj_tri_normal = vec3::cross(proj_v2 - proj_v1, proj_v3 - proj_v1);

				// Calculate the centre of the projected triangle.
				proj_tri_center = (proj_v1 + proj_v2 + proj_v3) / 3;

				// NOTE: Debugging
				// printf("cx: %f\n", camera_position.x);
				// printf("cy: %f\n", camera_position.y);
				// printf("cz: %f\n", camera_position.z);
				// printf("nx: %f\n", proj_tri_normal.x);
				// printf("ny: %f\n", proj_tri_normal.y);
				// printf("nz: %f\n", proj_tri_normal.z);
				// printf("ax: %f\n", proj_tri_center.x);
				// printf("ay: %f\n", proj_tri_center.y);
				// printf("az: %f\n", proj_tri_center.z);

				// Check the dot project of the projected triangle normal and
				// the camera to triangle centre vector - if the dot product is
				// <=0, the normal and vector point at each other, and the triangle
				// must be facing the camera, so we should render it. If the dot
				// product is >0, the are facing the same direction, therefore
				// the triangle is facing away from the camera - don't render it.
				float d = vec3::dot(proj_tri_normal, proj_tri_center - camera_position);

				// NOTE: Debugging
				// printf("d: %f\n", d);

				if(d >= 0) {
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
					rasterize_triangle(
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
						uvs[triangles[i + 1]],
						uvs[triangles[i + 2]],
						material
					);
				}
			}
		}

		return rge::OK;
	}

	void draw(const texture& texture, const rect& dest, const rect& src) override {
		if(!texture.get_on_cpu()) return;

		int x, y, ptr;
		float u, v;

		vec2 min = dest.get_min();
		vec3 max = dest.get_max();

		int x_min = (int)(min.x);
		int y_min = (int)(min.y);
		int x_max = (int)(max.x);
		int y_max = (int)(max.y);

		if(x_min < 0) x_min = 0;
		if(y_min < 0) y_min = 0;
		if(x_max > output_render->get_width()) x_max = output_render->get_width();
		if(y_max > output_render->get_height()) y_max = output_render->get_height();

		color* input_buffer = texture.get_data();
		color* frame_buffer = output_render->get_frame_buffer()->get_data();

		for(y = y_min; y <= y_max; y++) {
			for(x = x_min; x <= x_max; x++) {
				vec2 p(x + 0.5F, y + 0.5F);
				if(p.x >= min.x && p.x <= max.x && p.y >= min.y && p.y <= max.y) {
					ptr = x + (y * output_render->get_width());
					u = math::inverse_lerp(min.x, max.x, p.x);
					v = math::inverse_lerp(min.y, max.y, p.y);

					frame_buffer[ptr] = texture.sample(u, v);
				}
			}
		}
	}

private:
	void rasterize_triangle(
		const vec4& r_v1, // <- render_target coords
		const vec4& r_v2, // <- ^^^
		const vec4& r_v3, // <- ^^^
		const vec3& w_v1, // <- world vertices
		const vec3& w_v2, // <- ^^^
		const vec3& w_v3, // <- ^^^
		const vec3& w_n1, // <- world normals
		const vec3& w_n2, // <- ^^^
		const vec3& w_n3, // <- ^^^
		const vec2& t_uv1, // <- texture coords
		const vec2& t_uv2, // <- ^^^
		const vec2& t_uv3, // <- ^^^
		const material& material
	) {
		int x, y;
		int ptr;
		float denom;
		float weight_v1, weight_v2, weight_v3;
		float depth;
		vec3 v;
		vec3 n;
		vec2 uv;
		color diffuse;
		color source;
		color destination;
		vec3 camera_position = input_camera->transform != nullptr ? input_camera->transform->get_global_position() : vec3();
		color* frame_buffer = output_render->get_frame_buffer()->get_data();
		color* depth_buffer = output_render->get_depth_buffer()->get_data();

		// Calculate the bounding rectangle of the triangle based on the
		// three vertices.
		int x_min = (int)fminf(r_v1.x, fminf(r_v2.x, r_v3.x));
		int x_max = (int)fmaxf(r_v1.x, fmaxf(r_v2.x, r_v3.x));
		int y_min = (int)fminf(r_v1.y, fminf(r_v2.y, r_v3.y));
		int y_max = (int)fmaxf(r_v1.y, fmaxf(r_v2.y, r_v3.y));

		// Cull the bounding rect to the size of the texture we're rendering to.
		if(x_min < 0) x_min = 0;
		if(x_max > output_render->get_width()) x_max = output_render->get_width();
		if(y_min < 0) y_min = 0;
		if(y_max > output_render->get_height()) y_max = output_render->get_height();

		// NOTE: Debugging
		// printf("xmin:%d\n", x_min);
		// printf("xmax:%d\n", x_max);
		// printf("ymin:%d\n", y_min);
		// printf("ymax:%d\n", y_max);

		// TODO: Delete
		// vec2 v0(r_v1.x, r_v1.y);
		// vec2 v1(r_v2.x, r_v2.y);
		// vec2 v2(r_v3.x, r_v3.y);
		// vec2 e0 = v1 - v0;
		// vec2 e1 = v2 - v1;
		// vec2 e2 = v0 - v2;

		// Loop through every pixel in the bounding rect.
		for(y = y_min; y <= y_max; y++) {
			for(x = x_min; x <= x_max; x++) {
				vec2 p(x + 0.5F, y + 0.5F);

				// TODO: Delete
				// vec2 v0_to_p = p - v0;
				// vec2 v1_to_p = p - v1;
				// vec2 v2_to_p = p - v2;
				// float v0v1p = vec2::cross(e0, v0_to_p);
				// float v1v2p = vec2::cross(e1, v1_to_p);
				// float v2v0p = vec2::cross(e2, v2_to_p);

				// Calculate the weights w1, w2 and w3 for the barycentric
				// coordinates based on the positions of the three vertices.
				denom = (r_v2.y - r_v3.y) * (r_v1.x - r_v3.x) + (r_v3.x - r_v2.x) * (r_v1.y - r_v3.y);
				weight_v1 = ((r_v2.y - r_v3.y) * (p.x - r_v3.x) + (r_v3.x - r_v2.x) * (p.y - r_v3.y)) / denom;
				weight_v2 = ((r_v3.y - r_v1.y) * (p.x - r_v3.x) + (r_v1.x - r_v3.x) * (p.y - r_v3.y)) / denom;
				weight_v3 = 1.0F - weight_v1 - weight_v2;

				// TODO: Delete
				// float e1 = (ps.x-r_v1.x)*(r_v2.y-r_v1.y)-(ps.y-r_v1.y)*(r_v2.x-r_v1.x);
				// float e2 = (ps.x-r_v2.x)*(r_v3.y-r_v2.y)-(ps.y-r_v2.y)*(r_v3.x-r_v2.x);
				// float e3 = (ps.x-r_v3.x)*(r_v1.y-r_v3.y)-(ps.y-r_v3.y)*(r_v1.x-r_v3.x);

				// TODO: Delete
				// float w0 = edge_func(v1, v2, p);
				// float w1 = edge_func(v2, v0, p);
				// float w2 = edge_func(v0, v1, p);

				// If w1, w2 and w3 are >= 0, we are inside the triangle (or
				// on an edge, but either way, render the pixel).
				if(weight_v1 >= 0.0F && weight_v2 >= 0.0F && weight_v3 >= 0.0F) {
					// Calculate the position in our buffer based on our x and y values.
					ptr = x + (y * get_target()->get_width());

					// NOTE: Debugging
					// printf("ptr: %d, x: %d, y: %d\n", ptr, x, y);

					// Calculate the depth value of this pixel.
					depth = r_v1.z * weight_v1 + r_v2.z * weight_v2 + r_v3.z * weight_v3;

					// If the depth value is less than what is currently in the
					// depth buffer for this pixel.
					if(depth < depth_buffer[ptr].r) {
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
							ambient_color,
							material.shininess,
							camera_position,
							lights
						);

						// Match alpha to diffuse.
						source.a = diffuse.a;

						// Write color to render target.
						frame_buffer[ptr] = diffuse;

						// Update the depth buffer with this depth value.
						depth_buffer[ptr].r = depth;
					}
				}
			}
		}
	}

	static float edge_func(const vec2& a, const vec2& b, const vec2& c) {
		return (c.x - a.x) * (b.y - a.y) - (c.y - a.y) * (b.x - a.x);
	}

	static vec4 project_world_vertex(const vec3& v, const mat4& world_to_projection) {
		vec4 hpv = world_to_projection * vec4(v.x, v.y, v.z, 1);
		return vec4(hpv.x / hpv.w, hpv.y / hpv.w, hpv.z / hpv.w, hpv.w);
	}

	static color calculate_blinn_phong(
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


};
#endif /* SYS_SOFTWARE_GL */
//********************************************//
//* Software Renderer                        *//
//********************************************//
#pragma endregion


#pragma region /* rge::opengl_1_0 */
//********************************************//
//* OpenGL 1.0 Renderer                      *//
//********************************************//
#ifdef SYS_OPENGL_1_0
class opengl_1_0 : public rge::renderer {
private:
	#ifdef SYS_WINDOWS
	gl_device_context_t device = 0;
	gl_render_context_t render = 0;
	#endif

public:
	opengl_1_0() {

	}

	rge::result init(platform* platform) override {
		#ifdef SYS_WINDOWS
		windows* winapi = (windows*)platform;
		device = GetDC(winapi->handle);
		PIXELFORMATDESCRIPTOR pfd = {
			sizeof(PIXELFORMATDESCRIPTOR), 1,
			PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
			PFD_TYPE_RGBA, 32, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			PFD_MAIN_PLANE, 0, 0, 0, 0
		};

		int pf = 0;
		if(!(pf = ChoosePixelFormat(device, &pfd)))
			return rge::FAIL;
		SetPixelFormat(device, pf, &pfd);

		if(!(render = wglCreateContext(device)))
			return rge::FAIL;
		wglMakeCurrent(device, render);

		// Remove Frame cap
		/*
		wglSwapInterval = (wglSwapInterval_t*)wglGetProcAddress("wglSwapIntervalEXT");
		if(wglSwapInterval && !bVSYNC) wglSwapInterval(0);
		bSync = false;
		*/
		#endif

		#ifdef SYS_LINUX
		
		#endif
		
		#ifdef SYS_MACOSX
		
		#endif

		return rge::OK;
	}

	render_target* create_render_target(int width, int height) override {
		// NOT: Feature not supported.
		rge::log::error("Render targets not supported with OpenGL 1.0!");
		return nullptr;
	}

	void free_render_target(render_target* target) override {
		// NOT: Feature not supported.
		rge::log::error("Render targets not supported with OpenGL 1.0!");
	}

	void clear(color background) override {
		glClearColor(
			float(background.r),
			float(background.g),
			float(background.b),
			float(background.a)
		);

		glClear(GL_COLOR_BUFFER_BIT);

		// TODO: Clear depth.
		// if(bDepth) glClear(GL_DEPTH_BUFFER_BIT);
		glClear(GL_DEPTH_BUFFER_BIT);
	}

	static void convert_matrix(GLfloat* gl, const mat4& m) {
		for(int i = 0; i < 16; ++i) gl[i] = m.m[i % 4][i / 4];
	}

	void display() override {
		#ifdef SYS_WINDOWS
		glFlush();
		SwapBuffers(device);
		// if(bSync) DwmFlush();
		#endif

		#ifdef SYS_LINUX
		// TODO
		// X11::glXSwapBuffers(olc_Display, *olc_Window);
		#endif

		#ifdef SYS_MACOSX
		// TODO
		// glutSwapBuffers();
		#endif
	}

	rge::result draw(
		const mat4& model_to_world,
		const std::vector<vec3>& vertices,
		const std::vector<int>& triangles,
		const std::vector<vec3>& normals,
		const std::vector<vec2>& uvs,
		const material& material
	) override {
		int i;
		int v;
		vec3 vertex;
		vec3 normal;
		GLfloat gl_m[16];
		
		convert_matrix(gl_m, input_camera->get_view_matrix());
		glMatrixMode(GL_MODELVIEW);
		glLoadMatrixf(gl_m);

		convert_matrix(gl_m, input_camera->get_projection_matrix());
		glMatrixMode(GL_PROJECTION);
		glLoadMatrixf(gl_m);

		glBegin(GL_TRIANGLES);
		for(i = 0; i < triangles.size(); i++) {
			v = triangles[i];

			if(v < vertices.size()) {
				vertex = model_to_world.multiply_point_3x4(vertices[v]);
				glVertex3f(vertex.x, vertex.y, vertex.z);
			}

			if(v < normals.size()) {
				normal = model_to_world.multiply_vector(normals[v]);
				glNormal3f(normal.x, normal.y, normal.z);
			}

			if(v < uvs.size()) {
				glTexCoord2f(uvs[v].x, uvs[v].y);
			}
		}
		glEnd();

		return rge::OK;
	}

	void draw(const texture& texture, const rect& dest, const rect& src) override {
		GLfloat vertices[] = {
			-1, -1,  0,  // bottom left corner
			-1,  1,  0,  // top left corner
			 1,  1,  0,  // top right corner
			 1, -1,  0   // bottom right corner
		};

		GLubyte indices[] = {
			0, 1, 2, // first triangle (bottom left - top left - top right)
			0, 2, 3  // second triangle (bottom left - top right - bottom right)
		};

		glColor3b(120, 156, 35);
		glVertexPointer(3, GL_FLOAT, 0, vertices);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, indices);
	}

	void on_window_resized(int width, int height) override {
		glViewport(0, 0, width, height);
	}
};
#endif /* SYS_OPENGL_1_0 */
//********************************************//
//* OpenGL 1.0 Renderer                      *//
//********************************************//
#pragma endregion


#pragma region /* rge::opengl_3_3 */
//********************************************//
//* OpenGL 3.3 Renderer                      *//
//********************************************//
#ifdef SYS_OPENGL_3_3
class opengl_3_3 : public rge::renderer {

public:
	opengl_3_3() {

	}

	rge::result init(platform* platform) override {
		#ifdef SYS_WINDOWS
				
		#endif
		
		#ifdef SYS_LINUX
		
		#endif
		
		#ifdef SYS_MACOSX
		
		#endif

		return rge::OK;
	}

	render_target* create_render_target(int width, int height) override {
		// TODO
		return nullptr;
	}

	void free_render_target(render_target* target) override {
		// TODO
	}

	void clear(color background) override {
		// TODO
	}

	static void convert_matrix(GLfloat* gl, const mat4& m) {
		for(int i = 0; i < 16; ++i) gl[i] = m.m[i % 4][i / 4];
	}

	void display() override {
		#ifdef SYS_WINDOWS
				
		#endif
		
		#ifdef SYS_LINUX
		
		#endif
		
		#ifdef SYS_MACOSX
		
		#endif
	}

	rge::result draw(
		const mat4& model_to_world,
		const std::vector<vec3>& vertices,
		const std::vector<int>& triangles,
		const std::vector<vec3>& normals,
		const std::vector<vec2>& uvs,
		const material& material
	) override {
		// TODO

		return rge::OK;
	}

	void draw(const texture& texture, const rect& dest, const rect& src) override {
		// TODO
	}

	void on_window_resized(int width, int height) override {
		// TODO
		// glViewport(0, 0, width, height);
	}
};
#endif /* SYS_OPENGL_3_3 */
//********************************************//
//* OpenGL 3.3 Renderer                      *//
//********************************************//
#pragma endregion


#pragma region /* Engine Configuration */
//********************************************//
//* Engine Configuration                     *//
//********************************************//
void engine::configure() {
	#ifdef SYS_WINDOWS
	platform_impl = new windows();
	#endif

	#ifdef SYS_LINUX
	plaftrom_impl = new linux();
	#endif

	#ifdef SYS_MACOSX
	platform_impl = new macosx();
	#endif

	#ifdef SYS_SOFTWARE_GL
	renderer_impl = new software_gl();
	#endif

	#ifdef SYS_OPENGL_1_0
	renderer_impl = new opengl_1_0();
	#endif

	#ifdef SYS_OPENGL_2_1
	renderer_impl = new opengl_2_1();
	#endif

	#ifdef SYS_OPENGL_3_3
	renderer_impl = new opengl_3_3();
	#endif
}
//********************************************//
//* Engine Configuration                     *//
//********************************************//
#pragma endregion


} /* namespace rge */

#endif /* RGE_IMPL */