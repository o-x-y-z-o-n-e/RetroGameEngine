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
#include <queue>
#include <memory>

#define RGE_BIND_EVENT_HANDLER(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

namespace rge {


struct rect;
struct vec2;
struct vec3;
struct vec4;
struct quaternion;
struct mat4;
struct color;
class event;
class window_close_requested_event;
class window_moved_event;
class window_resized_event;
class window_focused_event;
class window_unfocused_event;
class key_event;
class key_pressed_event;
class key_released_event;
class mouse_pressed_event;
class mouse_released_event;
class mouse_moved_event;
class mouse_scrolled_event;
class gamepad_pressed_event;
class gamepad_released_event;
class gamepad_axis_event;
class engine;
class transform;
class camera;
class light;
class mesh;
class sprite;
class texture;
class material;
class render_target;
class renderer;
class platform;


enum result {
	FAIL = 0,
	OK = 1
};


#pragma region /* rge::rect */
//********************************************//
//* Rectangle Struct                         *//
//********************************************//
struct rect {
	float x, y, w, h;

	rect(float x, float y, float w, float h);

	vec2 get_min() const;
	vec2 get_max() const;
};
//********************************************//
//* Rectangle Struct                         *//
//********************************************//
#pragma endregion


#pragma region /* rge::vec2 */
//********************************************//
//* Vector2 Struct                           *//
//********************************************//
struct vec2 {
	float x, y;

	vec2();
	vec2(float x, float y);

	float magnitude() const;

	static float distance(const vec2& a, const vec2& b);
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
//* Vector2 Struct                           *//
//********************************************//
#pragma endregion


#pragma region /* rge::vec3 */
//********************************************//
//* Vector3 Struct                           *//
//********************************************//
struct vec3 {
	float x, y, z;

	vec3();
	vec3(float x, float y, float z);

	float magnitude() const;

	static float distance(const vec3& a, const vec3& b);
	static float dot(const vec3& v1, const vec3& v2);
	static vec3 cross(const vec3& v1, const vec3& v2);
	static vec3 normalize(const vec3& v);

	vec3 operator + (const vec3& rhs) const;
	vec3 operator - (const vec3& rhs) const;
	vec3 operator * (const float& rhs) const;
	vec3 operator * (const vec3& rhs) const;
	vec3 operator / (const float& rhs) const;
	vec3 operator / (const vec3& rhs) const;

	vec3& operator += (const vec3& rhs);
	vec3& operator -= (const vec3& rhs);
	vec3& operator *= (const float& rhs);
	vec3& operator *= (const vec3& rhs);
	vec3& operator /= (const float& rhs);
	vec3& operator /= (const vec3& rhs);

	vec3 operator + () const;
	vec3 operator - () const;

	bool operator == (const vec3& rhs) const;
	bool operator != (const vec3& rhs) const;

	operator vec2() const;
	operator vec4() const;

};
//********************************************//
//* Vector3 Struct                           *//
//********************************************//
#pragma endregion


#pragma region /* rge::vec4 */
//********************************************//
//* Vector4 Struct                           *//
//********************************************//
struct vec4 {
	float x, y, z, w;

	vec4();
	vec4(float x, float y, float z, float w);

	vec4 operator + (const vec4& rhs) const;
	vec4 operator - (const vec4& rhs) const;
	vec4 operator * (const float& rhs) const;
	vec4 operator * (const vec4& rhs) const;
	vec4 operator / (const float& rhs) const;
	vec4 operator / (const vec4& rhs) const;

	vec4& operator += (const vec4& rhs);
	vec4& operator -= (const vec4& rhs);
	vec4& operator *= (const float& rhs);
	vec4& operator *= (const vec4& rhs);
	vec4& operator /= (const float& rhs);
	vec4& operator /= (const vec4& rhs);

	vec4 operator + () const;
	vec4 operator - () const;

	bool operator == (const vec4& rhs) const;
	bool operator != (const vec4& rhs) const;

	operator vec3() const;
	operator vec2() const;
};
//********************************************//
//* Vector4 Struct                           *//
//********************************************//
#pragma endregion


#pragma region /* rge::quaternion */
//********************************************//
//* Quaternion Struct                        *//
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
//* Quaternion Struct                        *//
//********************************************//
#pragma endregion


#pragma region /* rge::mat4 */
//********************************************//
//* Matrix 4x4 Struct                        *//
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
//* Matrix 4x4 Struct                        *//
//********************************************//
#pragma endregion


#pragma region /* rge::color */
//********************************************//
//* Color Struct                             *//
//********************************************//
struct color {
	float r, g, b, a;

	color();
	color(float r, float g, float b);
	color(float r, float g, float b, float a);

	// Linearly interpolate between colors a & b.
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
//* Color Struct                             *//
//********************************************//
#pragma endregion


#pragma region /* rge::math */
//********************************************//
//* Math Module                              *//
//********************************************//
namespace math {
	#define DEG_2_RAD 0.0174532924F
	#define RAD_2_DEG 57.29578F
	#define PI 3.14159265F

	// Linearly interpolate between numbers a & b.
	float lerp(float a, float b, float t);

	// Gets the linear percent between points a & b.
	float inverse_lerp(float a, float b, float v);

	// Returns smallest integer.
	int min(int a, int b) { return a < b ? a : b; }

	// Returns largest integer.
	int max(int a, int b) { return a > b ? a : b; }
}
//********************************************//
//* Math Module                              *//
//********************************************//
#pragma endregion


#pragma region /* rge::log */
//********************************************//
//* Logging Module                           *//
//********************************************//
namespace log {
	void info(const char* msg, ...);
	void warning(const char* msg, ...);
	void error(const char* msg, ...);
}
//********************************************//
//* Logging Module                           *//
//********************************************//
#pragma endregion


#pragma region /* rge::input */
//********************************************//
//* Input Module                             *//
//********************************************//
namespace input {
	enum code {
		NONE = 0,

		// Keyboard keys.
		KEY_A = 1,
		KEY_B = 2,
		KEY_C = 3,
		KEY_D = 4,
		KEY_E = 5,
		KEY_F = 6,
		KEY_G = 7,
		KEY_H = 8,
		KEY_I = 9,
		KEY_J = 10,
		KEY_K = 11,
		KEY_L = 12,
		KEY_M = 13,
		KEY_N = 14,
		KEY_O = 15,
		KEY_P = 16,
		KEY_Q = 17,
		KEY_R = 18,
		KEY_S = 19,
		KEY_T = 20,
		KEY_U = 21,
		KEY_V = 22,
		KEY_W = 23,
		KEY_X = 24,
		KEY_Y = 25,
		KEY_Z = 26,

		KEY_SPACE = 27,
		KEY_CAPS = 28,
		KEY_RETURN = 29,

		KEY_0 = 30,
		KEY_1 = 31,
		KEY_2 = 32,
		KEY_3 = 33,
		KEY_4 = 34,
		KEY_5 = 35,
		KEY_6 = 36,
		KEY_7 = 37,
		KEY_8 = 38,
		KEY_9 = 39,

		KEY_UP = 40,
		KEY_DOWN = 41,
		KEY_LEFT = 42,
		KEY_RIGHT = 43,

		KEY_LEFT_SHIFT = 44,
		KEY_LEFT_CTRL = 45,
		KEY_LEFT_ALT = 46,

		KEY_RIGHT_SHIFT = 47,
		KEY_RIGHT_CTRL = 48,
		KEY_RIGHT_ALT = 49,

		KEY_TAB = 50,
		KEY_BACKSPACE = 51,

		KEY_ESC = 60,

		// Mouse buttons.
		MOUSE_LEFT = 100,
		MOUSE_RIGHT = 101,
		MOUSE_MIDDLE = 102,
		MOUSE_SCROLL = 103,

		// Gamepad buttons.
		GAMEPAD_UP = 150,
		GAMEPAD_DOWN = 151,
		GAMEPAD_LEFT = 152,
		GAMEPAD_RIGHT = 153,

		GAMEPAD_NORTH = 154,
		GAMEPAD_SOUTH = 155,
		GAMEPAD_WEST = 156,
		GAMEPAD_EAST = 157,

		GAMEPAD_LEFT_BUMPER = 158,
		GAMEPAD_RIGHT_BUMPER = 159,

		GAMEPAD_LEFT_STICK = 160,
		GAMEPAD_RIGHT_STICK = 161,

		GAMEPAD_OPTIONS = 162,
		GAMEPAD_START = 163,

		// Gamepad axis.
		GAMEPAD_LEFT_TRIGGER = 180,
		GAMEPAD_RIGHT_TRIGGER = 181,

		GAMEPAD_LEFT_STICK_X = 182,
		GAMEPAD_LEFT_STICK_Y = 183,
		GAMEPAD_RIGHT_STICK_X = 184,
		GAMEPAD_RIGHT_STICK_Y = 185,
	};

	// Returns true if a control is being held down.
	bool is_down(input::code input_code, int user = 0);

	// Returns true if a control is not being touched.
	bool is_up(input::code input_code, int user = 0);

	// Returns true if a control has been pressed within last update.
	bool has_pressed(input::code input_code, int user = 0);

	// Returns true if a control has been released within last update.
	bool has_released(input::code input_code, int user = 0);

	// Return input axis value [-1, 1] of a control.
	float get_axis(input::code input_code, int user = 0);

	// Returns the position of the mouse cursor in window-space. 
	vec2 get_mouse_position();

	#ifdef RGE_IMPL // Internal functions, no touchy.
	void flush_all();
	void flush_presses_and_releases();
	bool on_key_pressed(const key_pressed_event& e);
	bool on_key_released(const key_released_event& e);
	bool on_mouse_pressed(const mouse_pressed_event& e);
	bool on_mouse_released(const mouse_released_event& e);
	bool on_mouse_scrolled(const mouse_scrolled_event& e);
	bool on_mouse_moved(const mouse_moved_event& e);
	bool on_gamepad_pressed(const gamepad_pressed_event& e);
	bool on_gamepad_released(const gamepad_released_event& e);
	bool on_gamepad_axis(const gamepad_axis_event& e);
	#endif
}
//********************************************//
//* Input module                             *//
//********************************************//
#pragma endregion


#pragma region /* rge::event */
//********************************************//
//* Event class                              *//
//********************************************//
enum class event_type {
	NONE = 0,
	WINDOW_CLOSE_REQUESTED, WINDOW_MOVED, WINDOW_RESIZED, WINDOW_FOCUSED, WINDOW_UNFOCUSED,
	KEY_PRESSED, KEY_RELEASED,
	MOUSE_PRESSED, MOUSE_RELEASED, MOUSE_MOVED, MOUSE_SCROLLED,
	GAMEPAD_PRESSED, GAMEPAD_RELEASED, GAMEPAD_AXIS
};
#define EVENT_ENUM_TYPE(type) public: \
static event_type get_static_type() { return event_type::type; } \
virtual event_type get_event_type() const override { return get_static_type(); }
class event {
protected: // Abstract class.
	event() {}

public:
	virtual event_type get_event_type() const = 0;
};
//********************************************//
//* Event class                              *//
//********************************************//
#pragma endregion


#pragma region /* rge::window_event */
//********************************************//
//* Window events                            *//
//********************************************//
class window_close_requested_event : public event {
	EVENT_ENUM_TYPE(WINDOW_CLOSE_REQUESTED)
};
//----------------------------------------------
class window_moved_event : public event {
	EVENT_ENUM_TYPE(WINDOW_MOVED)
public:
	int x, y;
};
//----------------------------------------------
class window_resized_event : public event {
	EVENT_ENUM_TYPE(WINDOW_RESIZED)
public:
	int width, height;
};
//----------------------------------------------
class window_focused_event : public event {
	EVENT_ENUM_TYPE(WINDOW_FOCUSED)
};
//----------------------------------------------
class window_unfocused_event : public event {
	EVENT_ENUM_TYPE(WINDOW_UNFOCUSED)
};
//********************************************//
//* Window events                            *//
//********************************************//
#pragma endregion


#pragma region /* rge::key_event */
//********************************************//
//* Key events                               *//
//********************************************//
class key_pressed_event : public event {
	EVENT_ENUM_TYPE(KEY_PRESSED)
public:
	input::code input_code;
};
//----------------------------------------------
class key_released_event : public event {
	EVENT_ENUM_TYPE(KEY_RELEASED)
public:
	input::code input_code;
};
//********************************************//
//* Key events                               *//
//********************************************//
#pragma endregion


#pragma region /* rge::mouse_event */
//********************************************//
//* Mouse events                             *//
//********************************************//
class mouse_pressed_event : public event {
	EVENT_ENUM_TYPE(MOUSE_PRESSED)
public:
	input::code input_code;
};
//----------------------------------------------
class mouse_released_event : public event {
	EVENT_ENUM_TYPE(MOUSE_RELEASED)
public:
	input::code input_code;
};
//----------------------------------------------
class mouse_moved_event : public event {
	EVENT_ENUM_TYPE(MOUSE_MOVED)
public:
	int x, y;
};
//----------------------------------------------
class mouse_scrolled_event : public event {
	EVENT_ENUM_TYPE(MOUSE_SCROLLED)
public:
	int scroll;
};
//********************************************//
//* Mouse events                             *//
//********************************************//
#pragma endregion


#pragma region /* rge::mouse_event */
//********************************************//
//* Gamepad events                           *//
//********************************************//
class gamepad_pressed_event : public event {
	EVENT_ENUM_TYPE(GAMEPAD_PRESSED)
public:
	input::code input_code;
	int user;
};
//----------------------------------------------
class gamepad_released_event : public event {
	EVENT_ENUM_TYPE(GAMEPAD_RELEASED)
public:
	input::code input_code;
	int user;
};
//----------------------------------------------
class gamepad_axis_event : public event {
	EVENT_ENUM_TYPE(GAMEPAD_AXIS)
public:
	input::code input_code;
	int user;
	float value;
};
//********************************************//
//* Gamepad events                           *//
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
	void post_event(const event& e);
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
	virtual bool on_window_close_requested(const window_close_requested_event& e);

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
	class event_manager* events_impl;
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
	// Returns matrix used to convert world-space to view-space.
	mat4 get_view_matrix() const;

	// Returns matrix used to convert view-space to camera-space.
	mat4 get_projection_matrix() const;

	// Sets camera's projection to perspective.
	void set_perspective(float fov, float aspect, float near_plane, float far_plane);
	
	// Sets camera's projection to orthographic.
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
//* Light Class                              *//
//********************************************//
enum class light_mode {
	DIRECTIONAL,
	POINT,
	SPOT
};

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
//* Light Class                              *//
//********************************************//
#pragma endregion


#pragma region /* rge::mesh */
//********************************************//
//* Mesh Class                               *//
//********************************************//
class mesh {
public:
	mesh();
	~mesh();

public:
	std::vector<rge::vec3> vertices;
	std::vector<int> triangles;
	std::vector<rge::vec3> normals;
	std::vector<rge::vec2> uvs;
};
//********************************************//
//* Mesh Class                               *//
//********************************************//
#pragma endregion


#pragma region /* rge::sprite */
//********************************************//
//* Sprite Class                             *//
//********************************************//
class sprite {
public:
	sprite();
	sprite(texture* texture);
	~sprite();

public:
	bool centered;
	int pixels_per_unit;

	texture* texture;
	transform* transform;
};
//********************************************//
//* Sprite Class                             *//
//********************************************//
#pragma endregion


#pragma region /* rge::texture */
//********************************************//
//* Texture class.                           *//
//********************************************//
enum class texture_filter {
	NEAREST = 0,
	BILINEAR = 1,
	// TRILINEAR = 2
};
class texture {
public:
	texture(int width, int height);
	~texture();

public:
	int get_width() const;
	int get_height() const;

	// Returns true if space is allocated on cpu.
	bool is_on_cpu() const;

	// Returns true if space is allocated on gpu.
	bool is_on_gpu() const;

	// Returns sampled color at uv texture coords.
	color sample(float u, float v) const;

	// Returns color buffer stored on cpu.
	color* get_data() const;

	// Returns gpu texture reference.
	uint32_t get_handle() const;

	// Convert and store float color buffer to raw byte color buffer.
	void dump_to_raw_buffer(uint8_t* buffer) const;

	// NOTE: TESTING FUNCTION
	rge::result write_to_disk(const std::string& path) const;
	static texture* read_from_disk(const std::string& path);

public:
	// Allocates space on cpu for texture data.
	void allocate();

public:
	texture_filter filter;

private:
	int width;
	int height;

	// Internal variables
	#ifdef RGE_IMPL
public:
	#else
private:
	#endif
	color* data;     // For CPU buffer
	uint32_t handle; // For GPU ref

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
class render_target {
public:
	static render_target* create(renderer* renderer, int width, int height);
	rge::result resize(int width, int height);

	int get_width() const;
	int get_height() const;

	texture* get_frame_buffer() const;
	texture* get_depth_buffer() const;

public:
	~render_target();

private:
	render_target(renderer* renderer);

private:
	renderer* renderer_instance;
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
	virtual void set_window_title(const std::string& title) = 0;
	virtual void poll_events() = 0;
	virtual void poll_gamepads() = 0;
	virtual void refresh_window() = 0;
	virtual bool is_focused() const = 0;

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

	// Creates a texture with allocated space on gpu.
	virtual texture* create_texture(int width, int height) = 0;
	// Copies the texture data, on cpu, to gpu.
	virtual void upload_texture(texture* texture) = 0;
	// Frees the allocated texture data on gpu.
	virtual void free_texture(texture* texture) = 0;

	// Clears the depth & frame buffers.
	virtual void clear(color background) = 0;

	// Update current frame buffer to window.
	virtual void display() = 0;

	// Draw 3D geometry, using model space data.
	virtual rge::result draw(
		const mat4& local_to_world,
		const std::vector<vec3>& vertices,
		const std::vector<int>& triangles,
		const std::vector<vec3>& normals,
		const std::vector<vec2>& uvs,
		const material& material
	) = 0;

	// Draw a 2D sprite onto camera space.
	virtual void draw(const sprite& sprite) = 0;

	// Draw a 2D texture onto view [0,1] space.
	virtual void draw(
		const texture& texture,
		vec2 dest_min,
		vec2 dest_max,
		vec2 src_min,
		vec2 src_max
	) = 0;

	// Draw a 2D texture onto window [0, w/h] space.
	virtual void draw(
		const texture& texture,
		int dest_min_x,
		int dest_min_y,
		int dest_max_x,
		int dest_max_y,
		int src_min_x,
		int src_min_y,
		int src_max_x,
		int src_max_y
	) = 0;

public: // Inline macro short args functions.
	// Draw 3D geometry, using local/model space data.
	rge::result draw(
		const mat4& local_to_world,
		const mesh& mesh,
		const material& material
	) {
		return draw(
			local_to_world,
			mesh.vertices,
			mesh.triangles,
			mesh.normals,
			mesh.uvs,
			material
		);
	}

	// Draw a 2D texture onto view [0,1] space.
	void draw(const texture& texture, const vec2& dest_min, const vec2& dest_max) {
		draw(texture, dest_min, dest_max, vec2(0, 0), vec2(1, 1));
	}

	// Draw a 2D texture onto window [0, w/h] space.
	void draw(const texture& texture, int dest_min_x, int dest_min_y, int dest_max_x, int dest_max_y) {
		draw(texture, dest_min_x, dest_min_y, dest_max_x, dest_max_y, 0, 0, texture.get_width(), texture.get_height());
	}

public: // Events handlers.
	virtual bool on_window_resized(const window_resized_event& e) { return false; }

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
#include <xinput.h>
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "xinput.lib")
#undef MOUSE_MOVED // Annoying general #define name taking over possible names bs.
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
#ifdef SYS_WINDOWS
#include <dwmapi.h>
#include <GL/gl.h>
#pragma comment(lib, "dwmapi.lib")
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "opengl32.lib")
typedef HDC gl_device_context_t;
typedef HGLRC gl_render_context_t;
#define OPENGL_LOAD(t, n) (t*)wglGetProcAddress(#n)
#define CALLSTYLE __stdcall
#endif /* SYS_WINDOWS */

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

float vec2::distance(const vec2& a, const vec2& b) {
	return (b - a).magnitude();
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

float vec3::distance(const vec3& a, const vec3& b) {
	return (b - a).magnitude();
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

vec3 vec3::operator + (const vec3& rhs) const {
	return vec3(this->x + rhs.x, this->y + rhs.y, this->z + rhs.z);
}

vec3 vec3::operator - (const vec3& rhs) const {
	return vec3(this->x - rhs.x, this->y - rhs.y, this->z - rhs.z);
}

vec3 vec3::operator * (const float& rhs) const {
	return vec3(this->x * rhs, this->y * rhs, this->z * rhs);
}

vec3 vec3::operator * (const vec3& rhs) const {
	return vec3(this->x * rhs.x, this->y * rhs.y, this->z * rhs.z);
}

vec3 vec3::operator / (const float& rhs) const {
	return vec3(this->x / rhs, this->y / rhs, this->z / rhs);
}

vec3 vec3::operator / (const vec3& rhs) const {
	return vec3(this->x / rhs.x, this->y / rhs.y, this->z / rhs.z);
}

vec3& vec3::operator += (const vec3& rhs) {
	this->x += rhs.x; this->y += rhs.y; this->z += rhs.z; return *this;
}

vec3& vec3::operator -= (const vec3& rhs) {
	this->x -= rhs.x; this->y -= rhs.y; this->z -= rhs.z; return *this;
}

vec3& vec3::operator *= (const float& rhs) {
	this->x *= rhs;  this->y *= rhs; this->z *= rhs; return *this;
}

vec3& vec3::operator *= (const vec3& rhs) {
	this->x *= rhs.x; this->y *= rhs.y; this->z *= rhs.z; return *this;
	}

vec3& vec3::operator /= (const float& rhs) {
	this->x /= rhs;  this->y /= rhs; this->z /= rhs; return *this;
}

vec3& vec3::operator /= (const vec3& rhs) {
	this->x /= rhs.x; this->y /= rhs.y; this->z /= rhs.z; return *this;
}

vec3 vec3::operator + () const {
	return { +x, +y, +z };
}

vec3 vec3::operator - () const {
	return { -x, -y, -z };
}

bool vec3::operator == (const vec3& rhs) const {
	return (this->x == rhs.x && this->y == rhs.y && this->z == rhs.z);
}

bool vec3::operator != (const vec3& rhs) const {
	return (this->x != rhs.x || this->y != rhs.y || this->z != rhs.z);
}

vec3::operator vec2() const {
	return vec2(x, y);
}

vec3::operator vec4() const {
	return vec4(x, y, z, 0);
}
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

vec4 vec4::operator + (const vec4& rhs) const {
	return vec4(this->x + rhs.x, this->y + rhs.y, this->z + rhs.z, this->w + rhs.w);
}

vec4 vec4::operator - (const vec4& rhs) const {
	return vec4(this->x - rhs.x, this->y - rhs.y, this->z - rhs.z, this->w - rhs.w);
}

vec4 vec4::operator * (const float& rhs) const {
	return vec4(this->x * rhs, this->y * rhs, this->z * rhs, this->w * rhs);
}

vec4 vec4::operator * (const vec4& rhs) const {
	return vec4(this->x * rhs.x, this->y * rhs.y, this->z * rhs.z, this->w * rhs.w);
}

vec4 vec4::operator / (const float& rhs) const {
	return vec4(this->x / rhs, this->y / rhs, this->z / rhs, this->w / rhs);
}

vec4 vec4::operator / (const vec4& rhs) const {
	return vec4(this->x / rhs.x, this->y / rhs.y, this->z / rhs.z, this->w / rhs.w);
}

vec4& vec4::operator += (const vec4& rhs) {
	this->x += rhs.x; this->y += rhs.y; this->z += rhs.z; this->w += rhs.w; return *this;
}

vec4& vec4::operator -= (const vec4& rhs) {
	this->x -= rhs.x; this->y -= rhs.y; this->z -= rhs.z; this->w -= rhs.w; return *this;
}

vec4& vec4::operator *= (const float& rhs) {
	this->x *= rhs; this->y *= rhs; this->z *= rhs; this->w *= rhs; return *this;
}

vec4& vec4::operator *= (const vec4& rhs) {
	this->x *= rhs.x; this->y *= rhs.y; this->z *= rhs.z; this->w *= rhs.w; return *this;
}

vec4& vec4::operator /= (const float& rhs) {
	this->x /= rhs; this->y /= rhs; this->z /= rhs; this->w /= rhs; return *this;
}

vec4& vec4::operator /= (const vec4& rhs) {
	this->x /= rhs.x; this->y /= rhs.y; this->z /= rhs.z; this->w /= rhs.w; return *this;
}

vec4 vec4::operator + () const {
	return { +x, +y, +z, +w };
}

vec4 vec4::operator - () const {
	return { -x, -y, -z, -w };
}

bool vec4::operator == (const vec4& rhs) const {
	return (this->x == rhs.x && this->y == rhs.y && this->z == rhs.z && this->w == rhs.w);
}

bool vec4::operator != (const vec4& rhs) const {
	return (this->x != rhs.x || this->y != rhs.y || this->z != rhs.z || this->w != rhs.w);
}

vec4::operator vec3() const {
	return vec3(x, y, z);
}

vec4::operator vec2() const {
	return vec2(x, y);
}
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
	float t = (v - a) / (b - a);
	if(t < 0) t = 0;
	if(t > 1) t = 1;
	return t;
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


#pragma region /* rge::input */
//********************************************//
//* Input Module                             *//
//********************************************//
namespace input {
	typedef uint8_t button;
	const int NUM_KEYBOARD_BUTTONS = 60;
	const int NUM_MOUSE_BUTTONS = 3;
	const int NUM_GAMEPAD_BUTTONS = 14;
	const int NUM_GAMEPAD_AXIS = 6;
	const int MAX_GAMEPAD_COUNT = 4;

	static button keyboard_buttons[NUM_KEYBOARD_BUTTONS];

	static button mouse_buttons[NUM_MOUSE_BUTTONS];
	static float mouse_scroll = 0;
	static vec2 mouse_position = vec2();

	static button gamepad_buttons[NUM_GAMEPAD_BUTTONS][MAX_GAMEPAD_COUNT];
	static float gamepad_axis[NUM_GAMEPAD_AXIS][MAX_GAMEPAD_COUNT];

	inline void clear(button* d, int b) {
		*d &= ~(1 << b);
	}

	inline void set(button* d, int b) {
		*d |= (1 << b);
	}

	inline bool get(button* d, int b) {
		return (*d & (1 << b)) != 0;
	}

	bool is_down(input::code input_code, int user) {
		if(input_code >= KEY_A && input_code <= KEY_ESC) {
			return get(&keyboard_buttons[input_code - KEY_A], 0);
		}

		if(input_code >= MOUSE_LEFT && input_code <= MOUSE_MIDDLE) {
			return get(&mouse_buttons[input_code - MOUSE_LEFT], 0);
		}

		if(input_code >= GAMEPAD_UP && input_code <= GAMEPAD_START && user >= 0 && user < MAX_GAMEPAD_COUNT) {
			return get(&gamepad_buttons[input_code - GAMEPAD_UP][user], 0);
		}

		return false;
	}

	bool is_up(input::code input_code, int user) {
		return !is_down(input_code, user);
	}

	bool has_pressed(input::code input_code, int user) {
		if(input_code >= KEY_A && input_code <= KEY_ESC) {
			return get(&keyboard_buttons[input_code - KEY_A], 1);
		}

		if(input_code >= MOUSE_LEFT && input_code <= MOUSE_MIDDLE) {
			return get(&mouse_buttons[input_code - MOUSE_LEFT], 1);
		}

		if(input_code >= GAMEPAD_UP && input_code <= GAMEPAD_START && user >= 0 && user < MAX_GAMEPAD_COUNT) {
			return get(&gamepad_buttons[input_code - GAMEPAD_UP][user], 1);
		}

		return false;
	}

	bool has_released(rge::input::code input_code, int user) {
		if(input_code >= KEY_A && input_code <= KEY_ESC) {
			return get(&keyboard_buttons[input_code], 2);
		}

		if(input_code >= MOUSE_LEFT && input_code <= MOUSE_MIDDLE) {
			return get(&mouse_buttons[input_code - MOUSE_LEFT], 2);
		}

		if(input_code >= GAMEPAD_UP && input_code <= GAMEPAD_START && user >= 0 && user < MAX_GAMEPAD_COUNT) {
			return get(&gamepad_buttons[input_code - GAMEPAD_UP][user], 2);
		}

		return false;
	}

	vec2 get_mouse_position() {
		return mouse_position;
	}

	float get_axis(input::code input_code, int user) {
		if(input_code == MOUSE_SCROLL) {
			return mouse_scroll;
		}

		if(input_code >= GAMEPAD_LEFT_TRIGGER && input_code <= GAMEPAD_RIGHT_STICK_Y && user >= 0 && user < MAX_GAMEPAD_COUNT) {
			return gamepad_axis[input_code - GAMEPAD_LEFT_TRIGGER][user];
		}

		return 0;
	}

	bool on_key_pressed(const key_pressed_event& e) {
		set(&keyboard_buttons[e.input_code - KEY_A], 1);
		set(&keyboard_buttons[e.input_code - KEY_A], 0);
		return false; // Do not consume event. Let it propagate through higher layers.
	}

	bool on_key_released(const key_released_event& e) {
		set(&keyboard_buttons[e.input_code - KEY_A], 2);
		clear(&keyboard_buttons[e.input_code - KEY_A], 0);
		return false; // Do not consume event. Let it propagate through higher layers.
	}

	bool on_mouse_pressed(const mouse_pressed_event& e) {
		set(&mouse_buttons[e.input_code - MOUSE_LEFT], 1);
		set(&mouse_buttons[e.input_code - MOUSE_LEFT], 0);
		return false; // Do not consume event. Let it propagate through higher layers.
	}

	bool on_mouse_released(const mouse_released_event& e) {
		set(&mouse_buttons[e.input_code - MOUSE_LEFT], 2);
		clear(&mouse_buttons[e.input_code - MOUSE_LEFT], 0);
		return false; // Do not consume event. Let it propagate through higher layers.
	}

	bool on_mouse_moved(const mouse_moved_event& e) {
		mouse_position = vec2(e.x, e.y);
		return false; // Do not consume event. Let it propagate through higher layers.
	}

	bool on_mouse_scrolled(const mouse_scrolled_event& e) {
		mouse_scroll = e.scroll;
		return false; // Do not consume event. Let it propagate through higher layers.
	}

	bool on_gamepad_pressed(const gamepad_pressed_event& e) {
		set(&gamepad_buttons[e.input_code - GAMEPAD_UP][e.user], 1);
		set(&gamepad_buttons[e.input_code - GAMEPAD_UP][e.user], 0);
		return false; // Do not consume event. Let it propagate through higher layers.
	}

	bool on_gamepad_released(const gamepad_released_event& e) {
		set(&gamepad_buttons[e.input_code - GAMEPAD_UP][e.user], 2);
		clear(&gamepad_buttons[e.input_code - GAMEPAD_UP][e.user], 0);
		return false; // Do not consume event. Let it propagate through higher layers.
	}

	bool on_gamepad_axis(const gamepad_axis_event& e) {
		gamepad_axis[e.input_code - GAMEPAD_LEFT_TRIGGER][e.user] = e.value;
		return false; // Do not consume event. Let it propagate through higher layers.
	}

	void flush_all() {
		for(int i = 0; i < NUM_KEYBOARD_BUTTONS; i++) keyboard_buttons[i] = 0;
		for(int i = 0; i < NUM_MOUSE_BUTTONS; i++) mouse_buttons[i] = 0;
		for(int i = 0; i < NUM_GAMEPAD_BUTTONS; i++)
			for(int j = 0; j < MAX_GAMEPAD_COUNT; j++)
				gamepad_buttons[i][j] = 0;
	}

	void flush_presses_and_releases() {
		for(int i = 0; i < NUM_KEYBOARD_BUTTONS; i++) {
			clear(&keyboard_buttons[i], 1);
			clear(&keyboard_buttons[i], 2);
		}

		for(int i = 0; i < NUM_MOUSE_BUTTONS; i++) {
			clear(&keyboard_buttons[i], 1);
			clear(&keyboard_buttons[i], 2);
		}

		for(int i = 0; i < NUM_GAMEPAD_BUTTONS; i++) {
			for(int j = 0; j < MAX_GAMEPAD_COUNT; j++) {
				clear(&gamepad_buttons[i][j], 1);
				clear(&gamepad_buttons[i][j], 2);
			}
		}
	}
}
//********************************************//
//* Input Module                             *//
//********************************************//
#pragma endregion


#pragma region /* rge::event_dispatcher */
//********************************************//
//* Event dispatcher                         *//
//********************************************//
template<typename T>
class event_dispatcher {
public:
	std::queue<T> queue;
	std::vector<std::function<bool(const T&)>> handlers;

public:
	void process() {
		while(queue.size() > 0) {
			dispatch(queue.front());
			queue.pop();
		}
	}

	void dispatch(const T& e) {
		std::function<bool(const T&)> handler;
		for(std::vector<std::function<bool(const T&)>>::iterator it = handlers.begin(); it != handlers.end(); it++) {
			handler = (*it);

			if(handler(e)) break;
		}
	}

	bool add_event(const event& e) {
		if(e.get_event_type() != T::get_static_type())
			return false;

		queue.push(static_cast<const T&>(e));

		return true;
	}

	void add_handler(std::function<bool(const T&)> handler) {
		handlers.push_back(handler);
	}

	event_type get_event_type() {
		return T::get_static_type();
	}
};
//********************************************//
//* Event dispatcher                         *//
//********************************************//
#pragma endregion


#pragma region /* rge::event_manager */
//********************************************//
//* Event manager class                      *//
//********************************************//
class event_manager {
public:
	event_dispatcher<window_close_requested_event> on_window_close_requested;
	event_dispatcher<window_moved_event> on_window_moved;
	event_dispatcher<window_resized_event> on_window_resized;
	event_dispatcher<window_focused_event> on_window_focused;
	event_dispatcher<window_unfocused_event> on_window_unfocused;
	event_dispatcher<key_pressed_event> on_key_pressed;
	event_dispatcher<key_released_event> on_key_released;
	event_dispatcher<mouse_pressed_event> on_mouse_pressed;
	event_dispatcher<mouse_released_event> on_mouse_released;
	event_dispatcher<mouse_moved_event> on_mouse_moved;
	event_dispatcher<mouse_scrolled_event> on_mouse_scrolled;
	event_dispatcher<gamepad_pressed_event> on_gamepad_pressed;
	event_dispatcher<gamepad_released_event> on_gamepad_released;
	event_dispatcher<gamepad_axis_event> on_gamepad_axis;

public:
	bool post(const rge::event& e) {
		switch(e.get_event_type()) {
			case event_type::WINDOW_CLOSE_REQUESTED:
				return on_window_close_requested.add_event(e);

			case event_type::WINDOW_MOVED:
				return on_window_moved.add_event(e);

			case event_type::WINDOW_RESIZED:
				return on_window_resized.add_event(e);

			case event_type::WINDOW_FOCUSED:
				return on_window_focused.add_event(e);

			case event_type::WINDOW_UNFOCUSED:
				return on_window_unfocused.add_event(e);

			case event_type::KEY_PRESSED:
				return on_key_pressed.add_event(e);

			case event_type::KEY_RELEASED:
				return on_key_released.add_event(e);

			case event_type::MOUSE_PRESSED:
				return on_mouse_pressed.add_event(e);

			case event_type::MOUSE_RELEASED:
				return on_mouse_released.add_event(e);

			case event_type::MOUSE_MOVED:
				return on_mouse_moved.add_event(e);

			case event_type::MOUSE_SCROLLED:
				return on_mouse_scrolled.add_event(e);

			case event_type::GAMEPAD_PRESSED:
				return on_gamepad_pressed.add_event(e);

			case event_type::GAMEPAD_RELEASED:
				return on_gamepad_released.add_event(e);

			case event_type::GAMEPAD_AXIS:
				return on_gamepad_axis.add_event(e);
		}

		return false;
	}

	void process() {
		on_window_close_requested.process();
		on_window_moved.process();
		on_window_resized.process();
		on_window_focused.process();
		on_window_unfocused.process();
		on_key_pressed.process();
		on_key_released.process();
		on_mouse_pressed.process();
		on_mouse_released.process();
		on_mouse_moved.process();
		on_mouse_scrolled.process();
		on_gamepad_pressed.process();
		on_gamepad_released.process();
		on_gamepad_axis.process();
	}
};
//********************************************//
//* Event manager class                      *//
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
	events_impl = new event_manager();

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

	events_impl->on_window_close_requested.add_handler(RGE_BIND_EVENT_HANDLER(on_window_close_requested));
	events_impl->on_window_resized.add_handler(RGE_BIND_EVENT_HANDLER(renderer_impl->on_window_resized));
	events_impl->on_key_pressed.add_handler(&input::on_key_pressed);
	events_impl->on_key_released.add_handler(&input::on_key_released);
	events_impl->on_mouse_pressed.add_handler(&input::on_mouse_pressed);
	events_impl->on_mouse_released.add_handler(&input::on_mouse_released);
	events_impl->on_mouse_scrolled.add_handler(&input::on_mouse_scrolled);
	events_impl->on_mouse_moved.add_handler(&input::on_mouse_moved);
	events_impl->on_gamepad_pressed.add_handler(&input::on_gamepad_pressed);
	events_impl->on_gamepad_released.add_handler(&input::on_gamepad_released);
	events_impl->on_gamepad_axis.add_handler(&input::on_gamepad_axis);

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
		// Handle all events.
		platform_impl->poll_events();
		events_impl->process();

		// In case exit() was called during event handling.
		if(!is_running) break; 

		// Calculate the elapsed time since last frame.
		time_stamp_2 = std::chrono::system_clock::now();
		std::chrono::duration<float> elapsed_time = time_stamp_2 - time_stamp_1;
		time_stamp_1 = time_stamp_2;
		float delta_time = elapsed_time.count();
		
		// Tick the update routine.
		update_counter += delta_time;
		if(update_counter > update_interval) {
			platform_impl->poll_gamepads();
			on_update(update_counter);
			update_counter = 0;
			input::flush_presses_and_releases();
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
			platform_impl->refresh_window();
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

bool engine::on_window_close_requested(const window_close_requested_event& e) {
	exit();
	return true;
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

void engine::post_event(const event& e) {
	events_impl->post(e);
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


#pragma region /* rge::transform */
//********************************************//
//* Transform class.                         *//
//********************************************//
transform::transform() {
	parent = nullptr;
	this->position = vec3();
	this->rotation = quaternion::identity();
	this->scale = vec3(1, 1, 1);
}

transform::transform(transform* parent) {
	this->parent = parent;
	this->position = vec3();
	this->rotation = quaternion::identity();
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
	fov *= DEG_2_RAD;

	projection = mat4::zero();
	projection.m[0][0] = aspect / tanf(fov / 2.0F);
	projection.m[1][1] = 1.0F / tanf(fov / 2.0F);
	projection.m[2][2] = -(far_plane + near_plane) / (far_plane - near_plane);
	projection.m[2][3] = (2 * far_plane * near_plane) / (far_plane - near_plane);
	projection.m[3][2] = 1.0F;
}

void camera::set_orthographic(float left_plane, float right_plane, float top_plane, float bottom_plane, float near_plane, float far_plane) {
	projection = mat4::zero();
	projection.m[0][0] = 2.0F / (right_plane - left_plane);
	projection.m[1][1] = 2.0F / (top_plane - bottom_plane);
	projection.m[2][2] = 2.0F / (far_plane - near_plane);

	projection.m[0][3] = -((right_plane + left_plane) / (right_plane - left_plane));
	projection.m[1][3] = -((top_plane + bottom_plane) / (top_plane - bottom_plane));
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


#pragma region /* rge::mesh */
//********************************************//
//* Mesh Class                               *//
//********************************************//
mesh::mesh() {

}

mesh::~mesh() {

}
//********************************************//
//* Mesh Class                               *//
//********************************************//
#pragma endregion


#pragma region /* rge::sprite */
//********************************************//
//* Sprite Class                             *//
//********************************************//
sprite::sprite() {
	texture = nullptr;
	transform = new rge::transform();
	centered = false;
	pixels_per_unit = 32;
}

sprite::sprite(rge::texture* texture) {
	this->texture = texture;
	transform = new rge::transform();
	centered = false;
	pixels_per_unit = 32;
}

sprite::~sprite() {
	delete transform;
}
//********************************************//
//* Sprite Class                             *//
//********************************************//
#pragma endregion


#pragma region /* rge::texture */
//********************************************//
//* Texture class.                           *//
//********************************************//
texture::texture(int width, int height) {
	this->width = width;
	this->height = height;

	filter = texture_filter::NEAREST;
	data = nullptr;
	handle = 0;
}

texture::~texture() {
	// TODO: Make sure GPU side is cleared as well.
	if(data) delete[] data;
}

int texture::get_width() const {
	return width;
}

int texture::get_height() const {
	return height;
}

bool texture::is_on_cpu() const {
	return data != nullptr;
}

bool texture::is_on_gpu() const {
	return handle > 0;
}

color texture::sample(float u, float v) const {
	if(data == nullptr) return color(0, 0, 0);

	if(filter == texture_filter::NEAREST) {
		int ui = (int)(u * width) % width;
		int vi = (int)(v * height) % height;

		if(ui < 0) ui += width;
		if(vi < 0) vi += height;

		return data[ui + (vi * width)];
	} else if(filter == texture_filter::BILINEAR) {
		// TODO: Add repeating uv
		float uw = u * width;
		float vh = v * height;
		int ui = int(u * width);
		int vi = int(v * height);

		int fui = int(floor(uw));
		int fvi = int(floor(vh));
		int cui = int(ceil(uw));
		int cvi = int(ceil(vh));

		if(fui < 0) fui = 0;
		if(fvi < 0) fvi = 0;
		if(cui >= width) cui = width - 1;
		if(cvi >= height) cvi = height - 1;

		color bl = data[fui + (fvi * width)];
		color br = data[cui + (fvi * width)];
		color tl = data[fui + (cvi * width)];
		color tr = data[cui + (cvi * width)];

		float ix = math::inverse_lerp(fui, cui, uw);
		float iy = math::inverse_lerp(fvi, cvi, vh);

		return color::lerp(color::lerp(bl, br, ix), color::lerp(tl, tr, ix), iy);
	}

	return color(0, 0, 0);
}

color* texture::get_data() const {
	return data;
}

uint32_t texture::get_handle() const {
	return handle;
}

void texture::dump_to_raw_buffer(uint8_t* buffer) const {
	if(!is_on_cpu()) return;

	for(int i = 0; i < width * height; i++) {
		color c = data[i];
		buffer[i * 4] = (uint8_t)(c.r * 255);
		buffer[i * 4 + 1] = (uint8_t)(c.g * 255);
		buffer[i * 4 + 2] = (uint8_t)(c.b * 255);
		buffer[i * 4 + 3] = (uint8_t)(c.a * 255);
	}
}

rge::result texture::write_to_disk(const std::string& path) const {
	if(!is_on_cpu()) return rge::FAIL;

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

texture* texture::read_from_disk(const std::string& path) {
	// TODO: Check if file exists.

	#ifdef RGE_USE_STB_IMAGE

	int i, w, h, ch;
	uint8_t* input_buffer = stbi_load(path.c_str(), &w, &h, &ch, 4);

	if(ch != 3 && ch != 4) {
		rge::log::error("Texture file read failed: only RGB & RGBA formats supported!");
		stbi_image_free(input_buffer);
		return nullptr;
	}

	texture* tex = new texture(w, h);
	tex->allocate();
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
render_target* render_target::create(renderer* renderer, int width, int height) {
	if(renderer == nullptr) return nullptr;
	if(width < 1) return nullptr;
	if(height < 1) return nullptr;

	render_target* target = new render_target(renderer);

	target->resize(width, height);

	return target;
}

rge::result render_target::resize(int width, int height) {
	if(width < 1) return rge::FAIL;
	if(height < 1) return rge::FAIL;

	this->width = width;
	this->height = height;

	if(frame_buffer) renderer_instance->free_texture(frame_buffer);
	if(depth_buffer) renderer_instance->free_texture(depth_buffer);

	frame_buffer = renderer_instance->create_texture(width, height);
	depth_buffer = renderer_instance->create_texture(width, height);

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

render_target::~render_target() {

	delete frame_buffer;
	delete depth_buffer;
}

render_target::render_target(renderer* renderer) {
	renderer_instance = renderer;

	if(width < 1) width = 1;
	if(height < 1) height = 1;

	this->width = width;
	this->height = height;

	frame_buffer = renderer->create_texture(width, height);
	depth_buffer = renderer->create_texture(width, height);
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
	HDC device_context;

	int window_width;
	int window_height;

	bool has_init;
	bool has_window;
	bool has_focus;

	struct {
		BITMAPINFO bitmap_info;
		HBITMAP bitmap;
		void* buffer;
	} frame;

	static engine* engine_instance;
	static windows* windows_instance;

	windows() {
		windows_instance = this;
		has_init = false;
		has_window = false;
		has_focus = false;
	}

public:
	rge::result init(rge::engine* engine) override {
		if(has_init) return rge::FAIL;

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

		#ifdef SYS_SOFTWARE_GL
		device_context = CreateCompatibleDC(0);
		#endif /* SYS_SOFTWARE_GL */

		// TODO: Key mapping
		
		has_init = true;
		return rge::OK;
	}

	rge::result create_window() override {
		if(!has_init) return rge::FAIL;
		if(has_window) return rge::FAIL;

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

		//SendMessage(handle, WM_SIZE, 0, (window_width) + (window_height << 16));

		has_window = true;
		return rge::OK;
	}

	static std::wstring convert_str_to_wstr(const std::string& str) {
		#ifdef __MINGW32__
		wchar_t* buffer = new wchar_t[str.length() + 1];
		mbstowcs(buffer, str.c_str(), str.length());
		buffer[str.length()] = L'\0';
		#else
		int count = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0);
		wchar_t* buffer = new wchar_t[count];
		MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, buffer, count);
		#endif

		std::wstring w(buffer);
		delete[] buffer;

		return w;
	}

	static rge::input::code convert_sys_key_to_rge_key(uint8_t sys_key) {
		// If system key is a letter.
		if(sys_key > 0x40 && sys_key < 0x5B)
			return (rge::input::code)(sys_key - 0x40);

		// If system key is a digit (keypad).
		if(sys_key > 0x5F && sys_key < 0x6A)
			return (rge::input::code)(sys_key - 0x60 + 30);

		// If system key is a digit (alpha).
		if(sys_key > 0x2F && sys_key < 0x3A)
			return (rge::input::code)(sys_key - 0x30 + 30);

		// Otherwise...
		switch(sys_key) {
			case VK_SPACE: return	rge::input::KEY_SPACE;
			case VK_CAPITAL: return rge::input::KEY_CAPS;
			case VK_RETURN: return	rge::input::KEY_RETURN;
			case VK_LEFT: return	rge::input::KEY_LEFT;
			case VK_UP: return		rge::input::KEY_UP;
			case VK_RIGHT: return	rge::input::KEY_RIGHT;
			case VK_DOWN: return	rge::input::KEY_DOWN;
			case VK_LSHIFT: return	rge::input::KEY_LEFT_SHIFT;
			case VK_CONTROL: return rge::input::KEY_LEFT_CTRL;
			case VK_RSHIFT: return	rge::input::KEY_RIGHT_SHIFT;
			case VK_TAB: return		rge::input::KEY_TAB;
			case VK_BACK: return	rge::input::KEY_BACKSPACE;
			case VK_ESCAPE: return	rge::input::KEY_ESC;
		}

		return rge::input::NONE;
	}

	void set_window_title(const std::string& title) override {
		if(!has_window) return;

		#ifdef UNICODE
		SetWindowText(handle, convert_str_to_wstr(title).c_str());
		#else
		SetWindowText(handle, title.c_str());
		#endif
	}

	void poll_events() override {
		if(!has_window) return;

		MSG msg;

		while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	void refresh_window() override {
		if(!has_window) return;

		#ifdef SYS_SOFTWARE_GL
		InvalidateRect(handle, NULL, FALSE);
		UpdateWindow(handle);
		#endif /* SYS_SOFTWARE_GL */
	}

	static LRESULT CALLBACK on_event(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
		switch(msg) {
			case WM_CLOSE: {
				window_close_requested_event e;
				engine_instance->post_event(e);
				break;
			}

			case WM_DESTROY: {
				PostQuitMessage(0);
				DestroyWindow(hwnd);
				break;
			}

			case WM_SIZE: {
				window_resized_event e;
				e.width = LOWORD(lParam);
				e.height = HIWORD(lParam);

				windows_instance->create_frame(e.width, e.height);
				engine_instance->post_event(e);
				break;
			}

			case WM_MOVE: {
				window_moved_event e;
				e.x = (int)(short)LOWORD(lParam); // Horizontal position.
				e.y = (int)(short)HIWORD(lParam); // Vertical position.
				engine_instance->post_event(e);
				break;
			}

			case WM_KILLFOCUS: {
				windows_instance->has_focus = false;
				window_unfocused_event e;
				engine_instance->post_event(e);
				break;
			}

			case WM_SETFOCUS: {
				windows_instance->has_focus = true;
				window_focused_event e;
				engine_instance->post_event(e);
				break;
			}
			
			case WM_KEYUP: {
				key_released_event e;
				e.input_code = convert_sys_key_to_rge_key((uint8_t)wParam);
				engine_instance->post_event(e);
				break;
			}

			case WM_KEYDOWN: {
				bool key_was_down = ((lParam & (1 << 30)) != 0);
				if(!key_was_down) {
					key_pressed_event e;
					e.input_code = convert_sys_key_to_rge_key((uint8_t)wParam);
					engine_instance->post_event(e);
				}
				break;
			}

			case WM_LBUTTONDOWN: {
				mouse_pressed_event e;
				e.input_code = rge::input::MOUSE_LEFT;
				engine_instance->post_event(e);
				break;
			}

			case WM_RBUTTONDOWN: {
				mouse_pressed_event e;
				e.input_code = rge::input::MOUSE_RIGHT;
				engine_instance->post_event(e);
				break;
			}

			case WM_MBUTTONDOWN: {
				mouse_pressed_event e;
				e.input_code = rge::input::MOUSE_MIDDLE;
				engine_instance->post_event(e);
				break;
			}

			case WM_LBUTTONUP: {
				mouse_released_event e;
				e.input_code = rge::input::MOUSE_LEFT;
				engine_instance->post_event(e);
				break;
			}

			case WM_RBUTTONUP: {
				mouse_released_event e;
				e.input_code = rge::input::MOUSE_RIGHT;
				engine_instance->post_event(e);
				break;
			}

			case WM_MBUTTONUP: {
				mouse_released_event e;
				e.input_code = rge::input::MOUSE_MIDDLE;
				engine_instance->post_event(e);
				break;
			}

			case WM_MOUSEMOVE: {
				mouse_moved_event e;
				e.x = (int)(short)LOWORD(lParam); // Horizontal position.
				e.y = (int)(short)HIWORD(lParam); // Vertical position.
				engine_instance->post_event(e);
				break;
			}

			case WM_MOUSEWHEEL: {
				mouse_scrolled_event e;
				e.scroll = (short)HIWORD(wParam) / 120;
				engine_instance->post_event(e);
				break;
			}

			default: {
				return DefWindowProc(hwnd, msg, wParam, lParam);
			}
		}

		return 0;
	}

	inline void post_gamepad_axis(float v, input::code ic, int u) {
		gamepad_axis_event e;
		e.input_code = ic;
		e.user = u;
		e.value = v;
		engine_instance->post_event(e);
	}

	void poll_gamepads() override {
		for(int u = 0; u < input::MAX_GAMEPAD_COUNT; u++) {
			XINPUT_STATE state;
			if(XInputGetState(u, &state) != ERROR_SUCCESS)
				continue;

			post_gamepad_axis(float(state.Gamepad.bLeftTrigger) / 255, input::GAMEPAD_LEFT_TRIGGER, u);
			post_gamepad_axis(float(state.Gamepad.bRightTrigger) / 255, input::GAMEPAD_RIGHT_TRIGGER, u);
			post_gamepad_axis(fmaxf(-1, (float)state.Gamepad.sThumbLX / 32767), input::GAMEPAD_LEFT_STICK_X, u);
			post_gamepad_axis(fmaxf(-1, (float)state.Gamepad.sThumbLY / 32767), input::GAMEPAD_LEFT_STICK_Y, u);
			post_gamepad_axis(fmaxf(-1, (float)state.Gamepad.sThumbRX / 32767), input::GAMEPAD_RIGHT_STICK_X, u);
			post_gamepad_axis(fmaxf(-1, (float)state.Gamepad.sThumbRY / 32767), input::GAMEPAD_RIGHT_STICK_Y, u);

			// Generate gamepad button events.
			int i;
			int mask;
			bool is_pressed;
			bool was_pressed;
			for(i = input::GAMEPAD_UP; i <= input::GAMEPAD_START; i++) {
				switch(i) {
					case input::GAMEPAD_UP:
						mask = 0x0001;
						break;
					case input::GAMEPAD_DOWN:
						mask = 0x0002;
						break;
					case input::GAMEPAD_LEFT:
						mask = 0x0004;
						break;
					case input::GAMEPAD_RIGHT:
						mask = 0x0008;
						break;

					case input::GAMEPAD_NORTH:
						mask = 0x8000;
						break;
					case input::GAMEPAD_SOUTH:
						mask = 0x1000;
						break;
					case input::GAMEPAD_WEST:
						mask = 0x4000;
						break;
					case input::GAMEPAD_EAST:
						mask = 0x2000;
						break;

					case input::GAMEPAD_LEFT_BUMPER:
						mask = 0x0100;
						break;
					case input::GAMEPAD_RIGHT_BUMPER:
						mask = 0x0200;
						break;

					case input::GAMEPAD_LEFT_STICK:
						mask = 0x0040;
						break;
					case input::GAMEPAD_RIGHT_STICK:
						mask = 0x0080;
						break;

					case input::GAMEPAD_OPTIONS:
						mask = 0x0020;
						break;
					case input::GAMEPAD_START:
						mask = 0x0010;
						break;

					default:
						continue;
				}

				is_pressed = state.Gamepad.wButtons & mask;
				was_pressed = input::is_down((input::code)i, u);

				if(is_pressed && !was_pressed) {
					gamepad_pressed_event e;
					e.input_code = (input::code)i;
					e.user = u;
					engine_instance->post_event(e);
				} else if(!is_pressed && was_pressed) {
					gamepad_released_event e;
					e.input_code = (input::code)i;
					e.user = u;
					engine_instance->post_event(e);
				}
			}
		}
	}

	void create_frame(int width, int height) {
		window_width = width;
		window_height = height;
		#ifdef SYS_SOFTWARE_GL
		frame.bitmap_info.bmiHeader.biWidth = width;
		frame.bitmap_info.bmiHeader.biHeight = height;

		if(frame.bitmap)
			DeleteObject(frame.bitmap);

		frame.bitmap = CreateDIBSection(NULL, &frame.bitmap_info, DIB_RGB_COLORS, &frame.buffer, 0, 0);
		if(frame.bitmap == NULL)
			return;

		SelectObject(device_context, frame.bitmap);
		#endif /* SYS_SOFTWARE_GL */
	}

	uint8_t* get_frame_buffer() {
		return (uint8_t*)frame.buffer;
	}

	bool is_focused() const {
		return has_focus;
	}
};

engine* windows::engine_instance = nullptr;
windows* windows::windows_instance = nullptr;

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

	void set_window_title(const std::string& title) override {
		glutSetWindowTitle(title.c_str());
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
	render_target* output_window;
	platform* platform_instance;

	render_target* get_real_target() {
		return output_render != nullptr ? output_render : output_window;
	}

public:
	software_gl() : renderer() {}

public:
	rge::result init(platform* platform) override {
		platform_instance = platform;
		output_window = render_target::create(this, 1, 1);
		return rge::OK;
	}

	texture* create_texture(int width, int height) override {
		texture* t = new texture(width, height);

		t->allocate_cpu();

		return t;
	}

	void upload_texture(texture* texture) override {
		// NOTE: N/A to software renderer.
	}

	void free_texture(texture* texture) override {
		// TODO: Deallocate cpu
		delete texture;
	}

	bool on_window_resized(const window_resized_event& e) override {
		output_window->resize(e.width, e.height);
		return false; // Do not consume event. Let it propagate through higher layers.
	}

	void clear(color background) override {
		color* frame_buffer = get_real_target()->get_frame_buffer()->get_data();
		color* depth_buffer = get_real_target()->get_depth_buffer()->get_data();
		for(int i = 0; i < get_real_target()->get_width() * get_real_target()->get_height(); i++) {
			frame_buffer[i] = background;
			depth_buffer[i] = color(1, 0, 0, 0);
		}
	}

	void display() override {
		#ifdef SYS_WINDOWS
		windows* winapi = (windows*)platform_instance;
		uint8_t* buffer = winapi->get_frame_buffer();
		output_window->get_frame_buffer()->dump_to_raw_buffer(buffer);
		#endif
	}

	rge::result draw(
		const mat4& local_to_world,
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

		float w = (float)get_real_target()->get_width();
		float h = (float)get_real_target()->get_height();

		// Loop through each of the triplets of triangle indices.
		for(i = 0; i < triangles.size(); i += 3) {
			// Transform model vertices to world vertices.
			world_v1 = local_to_world.multiply_point_3x4(vertices[triangles[i]]);
			world_v2 = local_to_world.multiply_point_3x4(vertices[triangles[i + 1]]);
			world_v3 = local_to_world.multiply_point_3x4(vertices[triangles[i + 2]]);

			// Transform model normals to world normals.
			world_n1 = local_to_world.multiply_vector(normals[triangles[i]]);
			world_n2 = local_to_world.multiply_vector(normals[triangles[i + 1]]);
			world_n2 = local_to_world.multiply_vector(normals[triangles[i + 2]]);

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
		draw(
			texture,
			int(dest.x * get_real_target()->get_width()),
			int(dest.y * get_real_target()->get_height()),
			int(dest.w * get_real_target()->get_width()),
			int(dest.h * get_real_target()->get_height()),
			int(src.x * get_real_target()->get_width()),
			int(src.y * get_real_target()->get_height()),
			int(src.w * get_real_target()->get_width()),
			int(src.h * get_real_target()->get_height())
		);
	}

	void draw(
		const texture& texture,
		int dest_x,
		int dest_y,
		int dest_width,
		int dest_height,
		int src_x,
		int src_y,
		int src_width,
		int src_height
	) override {
		if(!texture.get_on_cpu()) return;

		int x, y, ptr;
		float u, v;
		float ut, vt;

		int wt = get_real_target()->get_width();
		int ht = get_real_target()->get_height();

		int x_min = dest_x;
		int y_min = dest_y;
		int x_max = dest_x + dest_width;
		int y_max = dest_y + dest_height;

		color* input_buffer = texture.get_data();
		color* frame_buffer = get_real_target()->get_frame_buffer()->get_data();

		if(x_min < 0) x_min = 0;
		if(y_min < 0) y_min = 0;
		if(x_max > wt) x_max = wt;
		if(y_max > ht) y_max = ht;

		for(y = y_min; y <= y_max; y++) {
			for(x = x_min; x <= x_max; x++) {
				if(x >= x_min && x < x_max && y >= y_min && y < y_max) {
					ptr = x + (y * wt);
					u = math::inverse_lerp(x_min, x_max, x);
					v = math::inverse_lerp(y_min, y_max, y);
					ut = math::lerp(src_x, src_x + src_width, u) / wt;
					vt = math::lerp(src_y, src_y + src_height, u) / ht;
					
					frame_buffer[ptr] = texture.sample(ut, vt);
				}
			}
		}
	}

	void draw(const sprite& sprite) override {
		// TODO
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
		color* frame_buffer = get_real_target()->get_frame_buffer()->get_data();
		color* depth_buffer = get_real_target()->get_depth_buffer()->get_data();

		// Calculate the bounding rectangle of the triangle based on the
		// three vertices.
		int x_min = (int)fminf(r_v1.x, fminf(r_v2.x, r_v3.x));
		int x_max = (int)fmaxf(r_v1.x, fmaxf(r_v2.x, r_v3.x));
		int y_min = (int)fminf(r_v1.y, fminf(r_v2.y, r_v3.y));
		int y_max = (int)fmaxf(r_v1.y, fmaxf(r_v2.y, r_v3.y));

		// Cull the bounding rect to the size of the texture we're rendering to.
		if(x_min < 0) x_min = 0;
		if(x_max > get_real_target()->get_width()) x_max = get_real_target()->get_width();
		if(y_min < 0) y_min = 0;
		if(y_max > get_real_target()->get_height()) y_max = get_real_target()->get_height();

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
					ptr = x + (y * get_real_target()->get_width());

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

	int window_width;
	int window_height;

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

		//glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glEnable(GL_COLOR_MATERIAL);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_NORMALIZE);

		glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

		return rge::OK;
	}

	texture* create_texture(int width, int height) override {
		texture* t = new texture(width, height);

		glGenTextures(1, &t->handle);

		return t;
	}

	void upload_texture(texture* texture) override {
		if(!texture->is_on_cpu()) return;

		if(!texture->is_on_gpu())
			glGenTextures(1, &texture->handle);

		glBindTexture(GL_TEXTURE_2D, texture->handle);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		if(texture->filter == texture_filter::NEAREST) {
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		} else if(texture->filter == texture_filter::BILINEAR) {
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}

		glTexImage2D(GL_TEXTURE_2D, 0, 4, texture->get_width(), texture->get_height(), 0, GL_RGBA, GL_FLOAT, texture->get_data());
	}

	void free_texture(texture* texture) override {
		if(texture->is_on_gpu())
			glDeleteTextures(1, &texture->handle);

		delete texture;
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
		glFlush();
		glutSwapBuffers();
		#endif
	}

	rge::result draw(
		const mat4& local_to_world,
		const std::vector<vec3>& vertices,
		const std::vector<int>& triangles,
		const std::vector<vec3>& normals,
		const std::vector<vec2>& uvs,
		const material& material
	) override {
		int t;
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

		/*
		glEnable(GL_ALPHA_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		*/

		if(material.texture != nullptr && material.texture->is_on_gpu()) {
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, material.texture->handle);
		} else {
			glDisable(GL_TEXTURE_2D);
		}

		float lpos[4] = { 0, 1, 0, 1.0 };  //light's position
		//glLightfv(GL_LIGHT0, GL_POSITION, lpos);   //Set light position

		glBegin(GL_TRIANGLES);
		for(i = 0; i < triangles.size(); i++) {
			v = triangles[i];

			if(v < uvs.size()) {
				glTexCoord2f(uvs[v].x, 1.0F - uvs[v].y);
			}

			if(v < vertices.size()) {
				vertex = local_to_world.multiply_point_3x4(vertices[v]);
				glVertex3f(vertex.x, vertex.y, vertex.z);
			}

			if(v < normals.size()) {
				normal = local_to_world.multiply_vector(normals[v]);
				glNormal3f(normal.x, normal.y, normal.z);
			}

			
		}
		glEnd();

		//glDisable(GL_TEXTURE_2D);
		/*
		glDisable(GL_BLEND);
		glDisable(GL_LIGHTING);
		*/

		glFlush();

		return rge::OK;
	}

	// Draw a 2D sprite onto camera space.
	void draw(const sprite& sprite) override {
		GLfloat gl_m[16];
		mat4 m = sprite.transform->get_global_matrix();
		vec3 n = m.multiply_vector(vec3(0, 0, -1));

		float w = float(sprite.texture->get_width()) / sprite.pixels_per_unit;
		float h = float(sprite.texture->get_height()) / sprite.pixels_per_unit;

		vec3 p = vec2(0, 0);
		vec3 r = vec2(w, 0);
		vec3 u = vec2(0, h);

		if(sprite.centered) {
			p.x -= w / 2.0F;
			p.y -= h / 2.0F;
		}
		
		vec3 p_bl = m.multiply_point_3x4(p);
		vec3 p_br = m.multiply_point_3x4(p + r);
		vec3 p_tl = m.multiply_point_3x4(p + u);
		vec3 p_tr = m.multiply_point_3x4(p + r + u);

		convert_matrix(gl_m, input_camera->get_view_matrix());
		glMatrixMode(GL_MODELVIEW);
		glLoadMatrixf(gl_m);

		convert_matrix(gl_m, input_camera->get_projection_matrix());
		glMatrixMode(GL_PROJECTION);
		glLoadMatrixf(gl_m);

		if(sprite.texture->is_on_gpu()) {
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, sprite.texture->handle);
		} else {
			glDisable(GL_TEXTURE_2D);
		}

		glBegin(GL_QUADS);

		glTexCoord2f(0.0F, 1.0F);
		glVertex3f(p_bl.x, p_bl.y, p_bl.z);
		glNormal3f(n.x, n.y, n.z);

		glTexCoord2f(1.0F, 1.0F);
		glVertex3f(p_br.x, p_br.y, p_br.z);
		glNormal3f(n.x, n.y, n.z);

		glTexCoord2f(1.0F, 0.0F);
		glVertex3f(p_tr.x, p_tr.y, p_tr.z);
		glNormal3f(n.x, n.y, n.z);

		glTexCoord2f(0.0F, 0.0F);
		glVertex3f(p_tl.x, p_tl.y, p_tl.z);
		glNormal3f(n.x, n.y, n.z);

		glEnd();

		glDisable(GL_TEXTURE_2D);

		glFlush();
	}

	// Draw a 2D texture onto view [0,1] space.
	void draw(const texture& texture, vec2 dest_min, vec2 dest_max, vec2 src_min, vec2 src_max) override {
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		dest_min.x = (dest_min.x * 2.0F) - 1.0F;
		dest_min.y = (dest_min.y * 2.0F) - 1.0F;
		dest_max.x = (dest_max.x * 2.0F) - 1.0F;
		dest_max.y = (dest_max.y * 2.0F) - 1.0F;

		if(texture.is_on_gpu()) {
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, texture.handle);
		} else {
			glDisable(GL_TEXTURE_2D);
		}

		glDisable(GL_DEPTH_TEST);
		glDepthMask(GL_FALSE);

		glBegin(GL_QUADS);

		glTexCoord2f(src_min.x, 1.0F - src_min.y);
		glVertex3f(dest_min.x, dest_min.y, 0.0F);

		glTexCoord2f(src_max.x, 1.0F - src_min.y);
		glVertex3f(dest_max.x, dest_min.y, 0.0F);

		glTexCoord2f(src_max.x, 1.0F - src_max.y);
		glVertex3f(dest_max.x, dest_max.y, 0.0F);

		glTexCoord2f(src_min.x, 1.0F - src_max.y);
		glVertex3f(dest_min.x, dest_max.y, 0.0F);

		glEnd();

		glFlush();

		glDisable(GL_TEXTURE_2D);
		glDepthMask(GL_TRUE);
		glEnable(GL_DEPTH_TEST);
	}

	// Draw a 2D texture onto window [0, w/h] space.
	void draw(
		const texture& texture,
		int dest_min_x,
		int dest_min_y,
		int dest_max_x,
		int dest_max_y,
		int src_min_x,
		int src_min_y,
		int src_max_x,
		int src_max_y
	) override {
		vec2 dest_min;
		vec2 dest_max;
		vec2 src_min;
		vec2 src_max;

		dest_min.x = float(dest_min_x) / window_width;
		dest_min.y = float(dest_min_y) / window_height;
		dest_max.x = float(dest_max_x) / window_width;
		dest_max.y = float(dest_max_y) / window_height;

		src_min.x = float(src_min_x) / texture.get_width();
		src_min.y = float(src_min_y) / texture.get_height();
		src_max.x = float(src_max_x) / texture.get_width();
		src_max.y = float(src_max_y) / texture.get_height();

		draw(texture, dest_min, dest_max, src_min, src_max);
	}

	bool on_window_resized(const window_resized_event& e) override {
		window_width = e.width;
		window_height = e.height;
		glViewport(0, 0, window_width, window_height);
		return false; // Do not consume event. Let it propagate through higher layers.
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
typedef char GLchar;
typedef ptrdiff_t GLsizeiptr;
typedef GLuint CALLSTYLE locCreateShader_t(GLenum type);
typedef GLuint CALLSTYLE locCreateProgram_t(void);
typedef void CALLSTYLE locDeleteShader_t(GLuint shader);
typedef void CALLSTYLE locCompileShader_t(GLuint shader);
typedef void CALLSTYLE locLinkProgram_t(GLuint program);
typedef void CALLSTYLE locDeleteProgram_t(GLuint program);
typedef void CALLSTYLE locAttachShader_t(GLuint program, GLuint shader);
typedef void CALLSTYLE locBindBuffer_t(GLenum target, GLuint buffer);
typedef void CALLSTYLE locBufferData_t(GLenum target, GLsizeiptr size, const void* data, GLenum usage);
typedef void CALLSTYLE locGenBuffers_t(GLsizei n, GLuint* buffers);
typedef void CALLSTYLE locVertexAttribPointer_t(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer);
typedef void CALLSTYLE locEnableVertexAttribArray_t(GLuint index);
typedef void CALLSTYLE locUseProgram_t(GLuint program);
typedef void CALLSTYLE locBindVertexArray_t(GLuint array);
typedef void CALLSTYLE locGenVertexArrays_t(GLsizei n, GLuint* arrays);
typedef void CALLSTYLE locGetShaderInfoLog_t(GLuint shader, GLsizei bufSize, GLsizei* length, GLchar* infoLog);
typedef GLint CALLSTYLE locGetUniformLocation_t(GLuint program, const GLchar* name);
typedef void CALLSTYLE locUniform1f_t(GLint location, GLfloat v0);
typedef void CALLSTYLE locUniform1i_t(GLint location, GLint v0);
typedef void CALLSTYLE locUniform2fv_t(GLint location, GLsizei count, const GLfloat* value);
typedef void CALLSTYLE locActiveTexture_t(GLenum texture);
typedef void CALLSTYLE locGenFrameBuffers_t(GLsizei n, GLuint* ids);
typedef void CALLSTYLE locBindFrameBuffer_t(GLenum target, GLuint fb);
typedef GLenum CALLSTYLE locCheckFrameBufferStatus_t(GLenum target);
typedef void CALLSTYLE locDeleteFrameBuffers_t(GLsizei n, const GLuint* fbs);
typedef void CALLSTYLE locFrameBufferTexture2D_t(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
typedef void CALLSTYLE locDrawBuffers_t(GLsizei n, const GLenum* bufs);
typedef void CALLSTYLE locBlendFuncSeparate_t(GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);
#ifdef SYS_WINDOWS
typedef void CALLSTYLE locSwapInterval_t(GLsizei n);
#endif /* SYS_WINDOWS */

class opengl_3_3 : public rge::renderer {
private:
	#ifdef SYS_WINDOWS
	gl_device_context_t device = 0;
	gl_render_context_t render = 0;
	#endif

	/*
	locCreateShader_t* glCreateShader = nullptr;
	locShaderSource_t* glShaderSource = nullptr;
	locCompileShader_t* glCompileShader = nullptr;
	locDeleteShader_t* glDeleteShader = nullptr;
	locCreateProgram_t* glCreateProgram = nullptr;
	locDeleteProgram_t* glDeleteProgram = nullptr;
	locLinkProgram_t* glLinkProgram = nullptr;
	locAttachShader_t* glAttachShader = nullptr;
	*/
	locBindBuffer_t* glBindBuffer = nullptr;
	locBufferData_t* glBufferData = nullptr;
	locGenBuffers_t* glGenBuffers = nullptr;
	locVertexAttribPointer_t* glVertexAttribPointer = nullptr;
	locEnableVertexAttribArray_t* glEnableVertexAttribArray = nullptr;
	locUseProgram_t* glUseProgram = nullptr;
	locBindVertexArray_t* glBindVertexArray = nullptr;
	locGenVertexArrays_t* glGenVertexArrays = nullptr;
	locSwapInterval_t* glSwapInterval = nullptr;
	locGetShaderInfoLog_t* glGetShaderInfoLog = nullptr;

public:
	opengl_3_3() {

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

		glBindBuffer = OPENGL_LOAD(locBindBuffer_t, glBindBuffer);
		glBufferData = OPENGL_LOAD(locBufferData_t, glBufferData);
		glGenBuffers = OPENGL_LOAD(locGenBuffers_t, glGenBuffers);
		glVertexAttribPointer = OPENGL_LOAD(locVertexAttribPointer_t, glVertexAttribPointer);
		glEnableVertexAttribArray = OPENGL_LOAD(locEnableVertexAttribArray_t, glEnableVertexAttribArray);
		glUseProgram = OPENGL_LOAD(locUseProgram_t, glUseProgram);
		glGetShaderInfoLog = OPENGL_LOAD(locGetShaderInfoLog_t, glGetShaderInfoLog);

		return rge::OK;
	}

	texture* create_texture(int width, int height) override {
		texture* t = new texture(width, height);

		// TODO

		return t;
	}

	void upload_texture(texture* texture) override {
		// TODO
	}

	void free_texture(texture* texture) override {
		// TODO: Free GPU texture.
		delete texture;
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
		
		#endif
		
		#ifdef SYS_MACOSX
		
		#endif
	}

	rge::result draw(
		const mat4& local_to_world,
		const std::vector<vec3>& vertices,
		const std::vector<int>& triangles,
		const std::vector<vec3>& normals,
		const std::vector<vec2>& uvs,
		const material& material
	) override {
		// TODO

		return rge::OK;
	}

	void draw(const sprite& sprite) override {
		// TODO
	}

	void draw(const texture& texture, const rect& dest, const rect& src) override {
		// TODO
	}

	void draw(
		const texture& texture,
		int dest_x,
		int dest_y,
		int dest_width,
		int dest_height,
		int src_x,
		int src_y,
		int src_width,
		int src_height
	) override {
		// TODO
	}

	bool on_window_resized(const window_resized_event& e) override {
		window_width = e.width;
		window_height = e.height;
		glViewport(0, 0, window_width, window_height);
		return false; // Do not consume event. Let it propagate through higher layers.
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