/* RetroGameEngine (RGE)

Author: Jeremy Kiel
Version: 0.1.0
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


#define RGE_VERSION_MAJOR 0
#define RGE_VERSION_MINOR 1
#define RGE_VERSION_PATCH 0

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
#include <set>
#include <unordered_map>
#include <memory>
#include <type_traits>


#define RGE_BIND_EVENT_HANDLER(fn, T) [this](const T& e) -> bool { return this->fn(e); }


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
class texture;
class sound;
class material;
class sprite;
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
struct rect final {
	float x, y, w, h;

	rect();
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
struct vec2 final {
	float x, y;

	vec2();
	vec2(float x, float y);

	float magnitude() const;

	static float distance(const vec2& a, const vec2& b);
	static float dot(const vec2& a, const vec2& b);
	static float cross(const vec2& a, const vec2& b);
	static vec2 normalize(const vec2& v);

	// Steps current towards target at most max_delta distance.
	static vec2 move_towards(vec2 current, vec2 target, float max_delta);

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
struct vec3 final {
	float x, y, z;

	vec3();
	vec3(float x, float y, float z);

	float magnitude() const;

	static float distance(const vec3& a, const vec3& b);
	static float dot(const vec3& v1, const vec3& v2);
	static vec3 cross(const vec3& v1, const vec3& v2);
	static vec3 normalize(const vec3& v);

	// Steps current towards target at most max_delta distance.
	static vec3 move_towards(vec3 current, vec3 target, float max_delta);

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
struct vec4 final {
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
struct quaternion final {
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
struct mat4 final {
	float m[4][4]; // Rows by columns.

	mat4();
	mat4(vec4 col0, vec4 col1, vec4 col2, vec4 col3);

	static mat4 identity() { return mat4(); }
	static mat4 zero() { return mat4(vec4(0, 0, 0, 0), vec4(0, 0, 0, 0), vec4(0, 0, 0, 0), vec4(0, 0, 0, 0)); }
	static mat4 translate(const vec3& translation);
	static mat4 rotate(const quaternion& rotation);
	static mat4 scale(const vec3& scale);
	static mat4 trs(const vec3& position, const quaternion& rotation, const vec3& scale);
	static mat4 inverse(const mat4& m);

	vec4 get_col(int i) const { return vec4(m[0][i], m[1][i], m[2][i], m[3][i]); };
	vec4 get_row(int i) const { return vec4(m[i][0], m[i][1], m[i][2], m[i][3]); };

	vec3 multiply_point_3x4(const vec3& v) const;
	vec3 multiply_vector(const vec3& v) const;
	vec3 extract_translation() const;
	quaternion extract_rotation() const;
	vec3 extract_right_axis() const;
	vec3 extract_up_axis() const;
	vec3 extract_forward_axis() const;

	mat4 operator * (const float& rhs) const { return mat4(get_col(0) * rhs, get_col(1) * rhs, get_col(2) * rhs, get_col(3) * rhs); };

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
struct color final {
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
	#define DEG_TO_RAD 0.0174532924F
	#define RAD_TO_DEG 57.29578F
	#define PI 3.14159265F

	// Linearly interpolate between numbers a & b.
	float lerp(float a, float b, float t);

	// Gets the linear percent between points a & b.
	float inverse_lerp(float a, float b, float v);

	// Returns smallest integer.
	inline int min(int a, int b) { return a < b ? a : b; }

	// Returns largest integer.
	inline int max(int a, int b) { return a > b ? a : b; }

	// Steps current towards target at most max_delta distance.
	float move_towards(float current, float target, float max_delta);
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

		// Mouse axis.
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

		GAMEPAD_LEFT_STICK_UP = 164,
		GAMEPAD_LEFT_STICK_DOWN = 165,
		GAMEPAD_LEFT_STICK_LEFT = 166,
		GAMEPAD_LEFT_STICK_RIGHT = 167,

		GAMEPAD_RIGHT_STICK_UP = 168,
		GAMEPAD_RIGHT_STICK_DOWN = 169,
		GAMEPAD_RIGHT_STICK_LEFT = 170,
		GAMEPAD_RIGHT_STICK_RIGHT = 171,

		// Gamepad axis.
		GAMEPAD_LEFT_TRIGGER = 180,
		GAMEPAD_RIGHT_TRIGGER = 181,

		GAMEPAD_LEFT_STICK_X = 182,
		GAMEPAD_LEFT_STICK_Y = 183,
		GAMEPAD_RIGHT_STICK_X = 184,
		GAMEPAD_RIGHT_STICK_Y = 185,

		ANY = 255
	};

	struct action {
		typedef std::pair<input::code, float> entry;
		std::vector<entry> bindings;

		void add_binding(input::code binding, float value = 1.0F);
		void remove_binding(input::code binding);
		void clear_bindings();
	};

	// Returns true if a control is being held down.
	bool is_down(input::code input_code, int user = 0);

	// Returns true if a control is not being touched.
	bool is_up(input::code input_code, int user = 0);

	// Returns true if a control has been pressed within last update.
	bool was_pressed(input::code input_code, int user = 0);

	// Returns true if a control has been released within last update.
	bool was_released(input::code input_code, int user = 0);

	// Return input axis value [-1, 1] of a control.
	float get_axis(input::code input_code, int user = 0);

	// Returns true if a control is being held down.
	bool is_down(const input::action& input_action, int user = 0);

	// Returns true if a control is not being touched.
	bool is_up(const input::action& input_action, int user = 0);

	// Returns true if a control has been pressed within last update.
	bool was_pressed(const input::action& input_action, int user = 0);

	// Returns true if a control has been released within last update.
	bool was_released(const input::action& input_action, int user = 0);

	// Return input axis value [-1, 1] of a control.
	float get_axis(const input::action& input_action, int user = 0);

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
//* Input Module                             *//
//********************************************//
#pragma endregion


#pragma region /* rge::random */
//********************************************//
//* Random Number Generator                  *//
//********************************************//
class random {
public:
	random(uint64_t seed);
	random();

	float range(float min, float max);
	double range(double min, double max);

	/* Generates number between min [inclusive] & max [exclusive] */
	int range(int min, int max);

	float next_f32();
	double next_f64();

	uint8_t next_u8();
	uint16_t next_u16();
	uint32_t next_u32();
	uint64_t next_u64();

	int8_t next_i8();
	int16_t next_i16();
	int32_t next_i32();
	int64_t next_i64();

	uint64_t get_seed() { return seed; }
	
private:
	uint64_t state;
	uint64_t seed;

};
//********************************************//
//* Random Number Generator                  *//
//********************************************//
#pragma endregion


#pragma region /* rge::event */
//********************************************//
//* Event Base Class                         *//
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
//* Event Base Class                         *//
//********************************************//
#pragma endregion


#pragma region /* rge::window_event */
//********************************************//
//* Window Events                            *//
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
//* Window Events                            *//
//********************************************//
#pragma endregion


#pragma region /* rge::key_event */
//********************************************//
//* Key Events                               *//
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
//* Key Events                               *//
//********************************************//
#pragma endregion


#pragma region /* rge::mouse_event */
//********************************************//
//* Mouse Events                             *//
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
//* Mouse Events                             *//
//********************************************//
#pragma endregion


#pragma region /* rge::mouse_event */
//********************************************//
//* Gamepad Events                           *//
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
//* Gamepad Events                           *//
//********************************************//
#pragma endregion


#pragma region /* rge::engine */
//********************************************//
//* Core Engine Class                        *//
//********************************************//
class engine {
public:
	template<typename T>
	static T* create() {
		static_assert(std::is_base_of<engine, T>::value, "T must be a derived class of rge::engine in create<T>");
		if(!can_create_instance()) return nullptr;
		T* t = new T();
		static_cast<engine*>(t)->init();
		return t;
	}

	void run(bool wait_until_exit = true);
	rge::result exit();
	rge::result command(const std::string& cmd);
	void post_event(const event& e);
	void wait_for_exit();
	int get_frame_rate() const;
	bool get_is_running() const;
	static engine* get_instance();
	static platform* get_platform();
	static renderer* get_renderer();
	~engine();

public:
	float update_interval;
	float physics_interval;
	float render_interval;

protected:
	engine();
	virtual void on_init() {}
	virtual bool on_command(const std::string& cmd) { return false; }
	virtual void on_start() {}
	virtual void on_update(float delta_time) {}
	virtual void on_physics(float delta_time) {}
	virtual void on_render() {}
	virtual void on_exit() {}
	virtual bool on_window_close_requested(const window_close_requested_event& e);
	virtual void get_default_window_params(std::string& title, int& width, int& height, bool& fullscreen) {}

private:
	static bool can_create_instance();
	void configure();
	void procedure();
	rge::result init();
	rge::result start();
	void loop();
	
private:
	static engine* instance;
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
	float resources_flush_counter;
};
//********************************************//
//* Core Engine Class                        *//
//********************************************//
#pragma endregion


#pragma region /* rge::transform */
//********************************************//
//* Transform Class                          *//
//********************************************//
class transform final {
public:
	typedef std::shared_ptr<transform> ptr;

public:
	static transform::ptr create();
	static transform::ptr create(transform::ptr parent);
	static transform::ptr create(vec3 position, quaternion rotation, vec3 scale);
	static transform::ptr create(vec3 position, quaternion rotation, vec3 scale, transform::ptr parent);

	// Only use if needed. Prefer create() instead.
	transform();
	transform(transform::ptr parent);
	transform(vec3 position, quaternion rotation, vec3 scale);
	transform(vec3 position, quaternion rotation, vec3 scale, transform::ptr parent);

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
	transform::ptr parent;
	vec3 position;
	quaternion rotation;
	vec3 scale;
};
//********************************************//
//* Transform Class                          *//
//********************************************//
#pragma endregion


#pragma region /* rge::camera */
//********************************************//
//* Camera Class                             *//
//********************************************//
class camera final {
public:
	typedef std::shared_ptr<camera> ptr;
	enum projection_type {
		PERSPECTIVE,
		ORTHOGRAPHIC
	};

public:
	static camera::ptr create();

	// Only use if needed. Prefer create() instead.
	camera();
	~camera();

public:
	// Returns matrix used to convert world-space to view-space.
	mat4 get_view_matrix() const;

	// Sets camera's projection to perspective.
	void set_perspective(float fov, float near_plane, float far_plane);

	// Sets camera's projection to perspective.
	void set_perspective(float fov, float near_plane, float far_plane, float aspect);
	
	// Sets camera's projection to orthographic.
	void set_orthographic(float near_plane, float far_plane, float vertical_size);

	// Sets camera's projection to orthographic.
	void set_orthographic(float left_plane, float right_plane, float top_plane, float bottom_plane, float near_plane, float far_plane);

	// Set's whether the width of the view frustum is automatically calculated from the view size in the renderer.
	void set_auto_width_adjust(bool auto_width_adjust);

	// Returns matrix used to convert view-space to camera-space.
	mat4 calculate_projection_matrix();

public:
	transform::ptr transform;

private:
	bool auto_width;
	// mat4 projection;
	projection_type type;
	float near_plane;
	float far_plane;
	float left_plane;
	float right_plane;
	float top_plane;
	float bottom_plane;
	float aspect;
	float fov;
};
//********************************************//
//* Camera Class                             *//
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

class light final {
public:
	typedef std::shared_ptr<light> ptr;

public:
	static light::ptr create();

	// Only use if needed. Prefer create() instead
	light();
	~light();

public:
	color tint;
	float intensity;
	float range;
	light_mode type;
	transform::ptr transform;
};
//********************************************//
//* Light Class                              *//
//********************************************//
#pragma endregion


#pragma region /* rge::mesh */
//********************************************//
//* Mesh Class                               *//
//********************************************//
class mesh final {
public:
	typedef std::shared_ptr<mesh> ptr;

public:
	static mesh::ptr create();

	// Only use if needed. Prefer create() instead.
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


#pragma region /* rge::texture */
//********************************************//
//* Texture Class                            *//
//********************************************//
enum class texture_filter {
	NEAREST = 0,
	BILINEAR = 1,
	// TRILINEAR = 2
};
class texture final {
public:
	typedef std::shared_ptr<rge::texture> ptr;

public:
	static ptr create(int width, int height);
	static ptr load(const std::string& path, bool load_to_gpu = true);
	static ptr copy(const ptr& original);

	// Only use if needed. Prefer create() instead.
	texture(int width, int height);
	~texture();

	// Returns width of texture in pixels.
	int get_width() const;

	// Returns height of texture in pixels.
	int get_height() const;

	// Returns true if space is allocated on cpu.
	bool is_on_cpu() const;

	// Returns true if space is allocated on gpu.
	bool is_on_gpu() const;

	// Returns sampled color at uv texture coords.
	color sample(float u, float v) const;

	// Allocates space on cpu for texture data.
	void allocate();

	// Returns color buffer stored on cpu.
	color* get_data() const;

	// Returns gpu texture reference.
	uint32_t get_handle() const;

	// Convert and store float color buffer to raw byte color buffer.
	void dump_to_raw_buffer(uint8_t* buffer) const;
	
	// NOTE: TESTING FUNCTION
	rge::result write_to_disk(const std::string& path) const;

public:
	texture_filter filter;

	// ==Internal Members==
private: 
	int width;
	int height;

	typedef std::unordered_map<std::string, ptr> table;
	static table registry;
	
	#ifdef RGE_IMPL
public:
	#else
private:
	#endif
	static void flush_registry();
	
	color* data;     // For CPU buffer
	uint32_t handle; // For GPU ref
	// ==Internal Members==
};
//********************************************//
//* Texture Class                            *//
//********************************************//
#pragma endregion


#pragma region /* rge::sound */
//********************************************//
//* Sound Class                              *//
//********************************************//
class sound final {
public:
	typedef std::shared_ptr<rge::sound> ptr;

public:
	static ptr load(const std::string& path);

private:
	uint32_t sample_rate;
	uint8_t sample_depth;
	uint8_t num_channels;
};
//********************************************//
//* Sound Class                              *//
//********************************************//
#pragma endregion


#pragma region /* rge::material */
//********************************************//
//* Material Class                           *//
//********************************************//
class material final {
public:
	typedef std::shared_ptr<material> ptr;

public:
	static material::ptr create();

	// Only use if needed. Prefer create() instead.
	material();
	~material();

public:
	texture::ptr texture;
	color diffuse;
	color specular;
	color emission;
	float shininess;
};
//********************************************//
//* Material Class                           *//
//********************************************//
#pragma endregion


#pragma region /* rge::sprite */
//********************************************//
//* Sprite Class                             *//
//********************************************//
class sprite final {
public:
	typedef std::shared_ptr<sprite> ptr;

public:
	static sprite::ptr create();
	static sprite::ptr create(const rge::texture::ptr& texture);

	// Only use if needed. Prefer create() instead.
	sprite();
	sprite(const rge::texture::ptr& texture);
	~sprite();

public:
	bool sub_sprite;
	bool centered;
	bool billboard;
	int pixels_per_unit;
	rect section;

	texture::ptr texture;
	material::ptr material;
	transform::ptr transform;
};
//********************************************//
//* Sprite Class                             *//
//********************************************//
#pragma endregion


#pragma region /* rge::render_target */
//********************************************//
//* Render Target                            *//
//********************************************//
class render_target final {
public:
	typedef std::shared_ptr<render_target> ptr;

public:
	static render_target::ptr create(renderer* renderer, int width, int height);

	// Only use if needed. Prefer create() instead.
	render_target(renderer* renderer, int width, int height);
	~render_target();

public:
	rge::result resize(int width, int height);

	int get_width() const;
	int get_height() const;

	texture* get_frame_buffer() const;
	texture* get_depth_buffer() const;

private:
	int width;
	int height;
	renderer* renderer_instance;
	texture::ptr frame_buffer;
	texture::ptr depth_buffer;
};
//********************************************//
//* Render Target                            *//
//********************************************//
#pragma endregion


#pragma region /* rge::platform */
//********************************************//
//* Base Platform Class                      *//
//********************************************//
class platform {
public:
	virtual rge::result init(rge::engine* engine) = 0;
	virtual rge::result create_window(const std::string& title, int width, int height, bool fullscreen) = 0;
	virtual void set_window_title(const std::string& title) = 0;
	virtual void set_window_size(int width, int height) = 0;
	virtual void set_fullscreen(bool fullscreen) = 0;
	virtual void poll_events() = 0;
	virtual void poll_gamepads() = 0;
	virtual void refresh_window() = 0;
	virtual bool is_focused() const = 0;
	virtual void clean_up() = 0;

public:
	virtual ~platform() {}

protected:
	platform() {}

public:
	bool skip_next_frame;
};
//********************************************//
//* Base Platform Class                      *//
//********************************************//
#pragma endregion


#pragma region /* rge::renderer */
//********************************************//
//* Base Renderer Class                      *//
//********************************************//
class renderer {
public:
	void set_camera(camera::ptr camera);
	void set_ambience(const color& ambient_color);
	rge::result set_target(render_target::ptr target);
	render_target::ptr get_target() const;
	void prepare_render();

public:
	virtual rge::result init(platform* platform) = 0;

	// Creates a texture with allocated space on gpu.
	virtual texture::ptr create_texture(int width, int height) = 0;

	// Allocates space on gpu for texture.
	virtual void alloc_texture(texture& texture) = 0;

	// Copies the texture data, on cpu, to gpu.
	virtual void upload_texture(texture& texture) = 0;

	// Frees the allocated texture data on gpu.
	virtual void free_texture(texture& texture) = 0;

	virtual render_target::ptr create_render_target(int width, int height) = 0;

	// Get width of currently set frame buffer.
	virtual int get_width() const = 0;

	// Get height of currently set frame buffer.
	virtual int get_height() const = 0;

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

	// Draw a 2D texture onto (dest)[0, 1] view space, from (src)[0, 1] uv space.
	virtual void draw(
		const texture& texture,
		vec2 dest_min,
		vec2 dest_max,
		vec2 src_min,
		vec2 src_max
	) = 0;

	// Draw a 2D texture onto (dest)[0, w/h] frame space, from (src)[0, w/h] texel space.
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
	// Draw 3D geometry, using model space data.
	inline rge::result draw(
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

	// Draw a 2D texture onto (dest)[0, 1] view space.
	inline void draw(const texture& texture, const vec2& dest_min, const vec2& dest_max) {
		draw(texture, dest_min, dest_max, vec2(0, 0), vec2(1, 1));
	}

	// Draw a 2D texture onto (dest)[0, w/h] frame space.
	inline void draw(const texture& texture, int dest_min_x, int dest_min_y, int dest_max_x, int dest_max_y) {
		draw(texture, dest_min_x, dest_min_y, dest_max_x, dest_max_y, 0, 0, texture.get_width(), texture.get_height());
	}

	// Draw a render target onto (dest)[0, 1] view space.
	inline void draw(const render_target& render, const vec2& dest_min, const vec2& dest_max) {
		draw(*render.get_frame_buffer(), dest_min, dest_max, vec2(0, 0), vec2(1, 1));
	}

	// Draw a render target onto (dest)[0, w/h] frame space.
	inline void draw(const render_target& render, int dest_min_x, int dest_min_y, int dest_max_x, int dest_max_y) {
		draw(*render.get_frame_buffer(), dest_min_x, dest_min_y, dest_max_x, dest_max_y);
	}

	// Draw a texture onto (pos)[-i32, +i32] frame space.
	inline void draw(const texture& texture, int pos_x, int pos_y) {
		draw(texture, pos_x, pos_y, pos_x + texture.get_width(), pos_y + texture.get_height(), 0, 0, texture.get_width(), texture.get_height());
	}

public: // Events handlers.
	virtual bool on_window_resized(const window_resized_event& e) { return false; }

public:
	virtual ~renderer() {}

protected:
	renderer();

protected:
	camera::ptr input_camera;
	render_target::ptr output_render;
	color ambient_color;
};
//********************************************//
//* Base Renderer Class                      *//
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
//#include <OpenGL/OpenGL.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#endif /* SYS_MACOSX */

class opengl_1_0;
#endif /* SYS_OPENGL_1_0 */

#ifdef SYS_OPENGL_3_3
#ifdef SYS_WINDOWS
#include <dwmapi.h>
#pragma comment(lib, "dwmapi.lib")
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "opengl32.lib")
typedef HDC gl_device_context_t;
typedef HGLRC gl_render_context_t;
#endif /* SYS_WINDOWS */

#pragma region GLAD
#define GLAD_GL_IMPLEMENTATION
/**
 * Loader generated by glad 2.0.4 on Fri Dec 22 21:14:42 2023
 *
 * SPDX-License-Identifier: (WTFPL OR CC0-1.0) AND Apache-2.0
 *
 * Generator: C/C++
 * Specification: gl
 * Extensions: 0
 *
 * APIs:
 *  - gl:compatibility=3.3
 *
 * Options:
 *  - ALIAS = False
 *  - DEBUG = False
 *  - HEADER_ONLY = True
 *  - LOADER = True
 *  - MX = False
 *  - ON_DEMAND = False
 *
 * Commandline:
 *    --api='gl:compatibility=3.3' --extensions='' c --header-only --loader
 *
 * Online:
 *    http://glad.sh/#api=gl%3Acompatibility%3D3.3&extensions=&generator=c&options=HEADER_ONLY%2CLOADER
 *
 */

#ifndef GLAD_GL_H_
#define GLAD_GL_H_

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif
#ifdef __gl_h_
#error OpenGL (gl.h) header already included (API: gl), remove previous include!
#endif
#define __gl_h_ 1
#ifdef __gl3_h_
#error OpenGL (gl3.h) header already included (API: gl), remove previous include!
#endif
#define __gl3_h_ 1
#ifdef __glext_h_
#error OpenGL (glext.h) header already included (API: gl), remove previous include!
#endif
#define __glext_h_ 1
#ifdef __gl3ext_h_
#error OpenGL (gl3ext.h) header already included (API: gl), remove previous include!
#endif
#define __gl3ext_h_ 1
#ifdef __clang__
#pragma clang diagnostic pop
#endif

#define GLAD_GL
#define GLAD_OPTION_GL_HEADER_ONLY
#define GLAD_OPTION_GL_LOADER

#ifdef __cplusplus
extern "C" {
#endif

#ifndef GLAD_PLATFORM_H_
#define GLAD_PLATFORM_H_

#ifndef GLAD_PLATFORM_WIN32
#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32) || defined(__MINGW32__)
#define GLAD_PLATFORM_WIN32 1
#else
#define GLAD_PLATFORM_WIN32 0
#endif
#endif

#ifndef GLAD_PLATFORM_APPLE
#ifdef __APPLE__
#define GLAD_PLATFORM_APPLE 1
#else
#define GLAD_PLATFORM_APPLE 0
#endif
#endif

#ifndef GLAD_PLATFORM_EMSCRIPTEN
#ifdef __EMSCRIPTEN__
#define GLAD_PLATFORM_EMSCRIPTEN 1
#else
#define GLAD_PLATFORM_EMSCRIPTEN 0
#endif
#endif

#ifndef GLAD_PLATFORM_UWP
#if defined(_MSC_VER) && !defined(GLAD_INTERNAL_HAVE_WINAPIFAMILY)
#ifdef __has_include
#if __has_include(<winapifamily.h>)
#define GLAD_INTERNAL_HAVE_WINAPIFAMILY 1
#endif
#elif _MSC_VER >= 1700 && !_USING_V110_SDK71_
#define GLAD_INTERNAL_HAVE_WINAPIFAMILY 1
#endif
#endif

#ifdef GLAD_INTERNAL_HAVE_WINAPIFAMILY
#include <winapifamily.h>
#if !WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP) && WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
#define GLAD_PLATFORM_UWP 1
#endif
#endif

#ifndef GLAD_PLATFORM_UWP
#define GLAD_PLATFORM_UWP 0
#endif
#endif

#ifdef __GNUC__
#define GLAD_GNUC_EXTENSION __extension__
#else
#define GLAD_GNUC_EXTENSION
#endif

#define GLAD_UNUSED(x) (void)(x)

#ifndef GLAD_API_CALL
#if defined(GLAD_API_CALL_EXPORT)
#if GLAD_PLATFORM_WIN32 || defined(__CYGWIN__)
#if defined(GLAD_API_CALL_EXPORT_BUILD)
#if defined(__GNUC__)
#define GLAD_API_CALL __attribute__ ((dllexport)) extern
#else
#define GLAD_API_CALL __declspec(dllexport) extern
#endif
#else
#if defined(__GNUC__)
#define GLAD_API_CALL __attribute__ ((dllimport)) extern
#else
#define GLAD_API_CALL __declspec(dllimport) extern
#endif
#endif
#elif defined(__GNUC__) && defined(GLAD_API_CALL_EXPORT_BUILD)
#define GLAD_API_CALL __attribute__ ((visibility ("default"))) extern
#else
#define GLAD_API_CALL extern
#endif
#else
#define GLAD_API_CALL extern
#endif
#endif

#ifdef APIENTRY
#define GLAD_API_PTR APIENTRY
#elif GLAD_PLATFORM_WIN32
#define GLAD_API_PTR __stdcall
#else
#define GLAD_API_PTR
#endif

#ifndef GLAPI
#define GLAPI GLAD_API_CALL
#endif

#ifndef GLAPIENTRY
#define GLAPIENTRY GLAD_API_PTR
#endif

#define GLAD_MAKE_VERSION(major, minor) (major * 10000 + minor)
#define GLAD_VERSION_MAJOR(version) (version / 10000)
#define GLAD_VERSION_MINOR(version) (version % 10000)

#define GLAD_GENERATOR_VERSION "2.0.4"

	typedef void (*GLADapiproc)(void);

	typedef GLADapiproc(*GLADloadfunc)(const char* name);
	typedef GLADapiproc(*GLADuserptrloadfunc)(void* userptr, const char* name);

	typedef void (*GLADprecallback)(const char* name, GLADapiproc apiproc, int len_args, ...);
	typedef void (*GLADpostcallback)(void* ret, const char* name, GLADapiproc apiproc, int len_args, ...);

#endif /* GLAD_PLATFORM_H_ */

#define GL_2D 0x0600
#define GL_2_BYTES 0x1407
#define GL_3D 0x0601
#define GL_3D_COLOR 0x0602
#define GL_3D_COLOR_TEXTURE 0x0603
#define GL_3_BYTES 0x1408
#define GL_4D_COLOR_TEXTURE 0x0604
#define GL_4_BYTES 0x1409
#define GL_ACCUM 0x0100
#define GL_ACCUM_ALPHA_BITS 0x0D5B
#define GL_ACCUM_BLUE_BITS 0x0D5A
#define GL_ACCUM_BUFFER_BIT 0x00000200
#define GL_ACCUM_CLEAR_VALUE 0x0B80
#define GL_ACCUM_GREEN_BITS 0x0D59
#define GL_ACCUM_RED_BITS 0x0D58
#define GL_ACTIVE_ATTRIBUTES 0x8B89
#define GL_ACTIVE_ATTRIBUTE_MAX_LENGTH 0x8B8A
#define GL_ACTIVE_TEXTURE 0x84E0
#define GL_ACTIVE_UNIFORMS 0x8B86
#define GL_ACTIVE_UNIFORM_BLOCKS 0x8A36
#define GL_ACTIVE_UNIFORM_BLOCK_MAX_NAME_LENGTH 0x8A35
#define GL_ACTIVE_UNIFORM_MAX_LENGTH 0x8B87
#define GL_ADD 0x0104
#define GL_ADD_SIGNED 0x8574
#define GL_ALIASED_LINE_WIDTH_RANGE 0x846E
#define GL_ALIASED_POINT_SIZE_RANGE 0x846D
#define GL_ALL_ATTRIB_BITS 0xFFFFFFFF
#define GL_ALPHA 0x1906
#define GL_ALPHA12 0x803D
#define GL_ALPHA16 0x803E
#define GL_ALPHA4 0x803B
#define GL_ALPHA8 0x803C
#define GL_ALPHA_BIAS 0x0D1D
#define GL_ALPHA_BITS 0x0D55
#define GL_ALPHA_INTEGER 0x8D97
#define GL_ALPHA_SCALE 0x0D1C
#define GL_ALPHA_TEST 0x0BC0
#define GL_ALPHA_TEST_FUNC 0x0BC1
#define GL_ALPHA_TEST_REF 0x0BC2
#define GL_ALREADY_SIGNALED 0x911A
#define GL_ALWAYS 0x0207
#define GL_AMBIENT 0x1200
#define GL_AMBIENT_AND_DIFFUSE 0x1602
#define GL_AND 0x1501
#define GL_AND_INVERTED 0x1504
#define GL_AND_REVERSE 0x1502
#define GL_ANY_SAMPLES_PASSED 0x8C2F
#define GL_ARRAY_BUFFER 0x8892
#define GL_ARRAY_BUFFER_BINDING 0x8894
#define GL_ATTACHED_SHADERS 0x8B85
#define GL_ATTRIB_STACK_DEPTH 0x0BB0
#define GL_AUTO_NORMAL 0x0D80
#define GL_AUX0 0x0409
#define GL_AUX1 0x040A
#define GL_AUX2 0x040B
#define GL_AUX3 0x040C
#define GL_AUX_BUFFERS 0x0C00
#define GL_BACK 0x0405
#define GL_BACK_LEFT 0x0402
#define GL_BACK_RIGHT 0x0403
#define GL_BGR 0x80E0
#define GL_BGRA 0x80E1
#define GL_BGRA_INTEGER 0x8D9B
#define GL_BGR_INTEGER 0x8D9A
#define GL_BITMAP 0x1A00
#define GL_BITMAP_TOKEN 0x0704
#define GL_BLEND 0x0BE2
#define GL_BLEND_COLOR 0x8005
#define GL_BLEND_DST 0x0BE0
#define GL_BLEND_DST_ALPHA 0x80CA
#define GL_BLEND_DST_RGB 0x80C8
#define GL_BLEND_EQUATION 0x8009
#define GL_BLEND_EQUATION_ALPHA 0x883D
#define GL_BLEND_EQUATION_RGB 0x8009
#define GL_BLEND_SRC 0x0BE1
#define GL_BLEND_SRC_ALPHA 0x80CB
#define GL_BLEND_SRC_RGB 0x80C9
#define GL_BLUE 0x1905
#define GL_BLUE_BIAS 0x0D1B
#define GL_BLUE_BITS 0x0D54
#define GL_BLUE_INTEGER 0x8D96
#define GL_BLUE_SCALE 0x0D1A
#define GL_BOOL 0x8B56
#define GL_BOOL_VEC2 0x8B57
#define GL_BOOL_VEC3 0x8B58
#define GL_BOOL_VEC4 0x8B59
#define GL_BUFFER_ACCESS 0x88BB
#define GL_BUFFER_ACCESS_FLAGS 0x911F
#define GL_BUFFER_MAPPED 0x88BC
#define GL_BUFFER_MAP_LENGTH 0x9120
#define GL_BUFFER_MAP_OFFSET 0x9121
#define GL_BUFFER_MAP_POINTER 0x88BD
#define GL_BUFFER_SIZE 0x8764
#define GL_BUFFER_USAGE 0x8765
#define GL_BYTE 0x1400
#define GL_C3F_V3F 0x2A24
#define GL_C4F_N3F_V3F 0x2A26
#define GL_C4UB_V2F 0x2A22
#define GL_C4UB_V3F 0x2A23
#define GL_CCW 0x0901
#define GL_CLAMP 0x2900
#define GL_CLAMP_FRAGMENT_COLOR 0x891B
#define GL_CLAMP_READ_COLOR 0x891C
#define GL_CLAMP_TO_BORDER 0x812D
#define GL_CLAMP_TO_EDGE 0x812F
#define GL_CLAMP_VERTEX_COLOR 0x891A
#define GL_CLEAR 0x1500
#define GL_CLIENT_ACTIVE_TEXTURE 0x84E1
#define GL_CLIENT_ALL_ATTRIB_BITS 0xFFFFFFFF
#define GL_CLIENT_ATTRIB_STACK_DEPTH 0x0BB1
#define GL_CLIENT_PIXEL_STORE_BIT 0x00000001
#define GL_CLIENT_VERTEX_ARRAY_BIT 0x00000002
#define GL_CLIP_DISTANCE0 0x3000
#define GL_CLIP_DISTANCE1 0x3001
#define GL_CLIP_DISTANCE2 0x3002
#define GL_CLIP_DISTANCE3 0x3003
#define GL_CLIP_DISTANCE4 0x3004
#define GL_CLIP_DISTANCE5 0x3005
#define GL_CLIP_DISTANCE6 0x3006
#define GL_CLIP_DISTANCE7 0x3007
#define GL_CLIP_PLANE0 0x3000
#define GL_CLIP_PLANE1 0x3001
#define GL_CLIP_PLANE2 0x3002
#define GL_CLIP_PLANE3 0x3003
#define GL_CLIP_PLANE4 0x3004
#define GL_CLIP_PLANE5 0x3005
#define GL_COEFF 0x0A00
#define GL_COLOR 0x1800
#define GL_COLOR_ARRAY 0x8076
#define GL_COLOR_ARRAY_BUFFER_BINDING 0x8898
#define GL_COLOR_ARRAY_POINTER 0x8090
#define GL_COLOR_ARRAY_SIZE 0x8081
#define GL_COLOR_ARRAY_STRIDE 0x8083
#define GL_COLOR_ARRAY_TYPE 0x8082
#define GL_COLOR_ATTACHMENT0 0x8CE0
#define GL_COLOR_ATTACHMENT1 0x8CE1
#define GL_COLOR_ATTACHMENT10 0x8CEA
#define GL_COLOR_ATTACHMENT11 0x8CEB
#define GL_COLOR_ATTACHMENT12 0x8CEC
#define GL_COLOR_ATTACHMENT13 0x8CED
#define GL_COLOR_ATTACHMENT14 0x8CEE
#define GL_COLOR_ATTACHMENT15 0x8CEF
#define GL_COLOR_ATTACHMENT16 0x8CF0
#define GL_COLOR_ATTACHMENT17 0x8CF1
#define GL_COLOR_ATTACHMENT18 0x8CF2
#define GL_COLOR_ATTACHMENT19 0x8CF3
#define GL_COLOR_ATTACHMENT2 0x8CE2
#define GL_COLOR_ATTACHMENT20 0x8CF4
#define GL_COLOR_ATTACHMENT21 0x8CF5
#define GL_COLOR_ATTACHMENT22 0x8CF6
#define GL_COLOR_ATTACHMENT23 0x8CF7
#define GL_COLOR_ATTACHMENT24 0x8CF8
#define GL_COLOR_ATTACHMENT25 0x8CF9
#define GL_COLOR_ATTACHMENT26 0x8CFA
#define GL_COLOR_ATTACHMENT27 0x8CFB
#define GL_COLOR_ATTACHMENT28 0x8CFC
#define GL_COLOR_ATTACHMENT29 0x8CFD
#define GL_COLOR_ATTACHMENT3 0x8CE3
#define GL_COLOR_ATTACHMENT30 0x8CFE
#define GL_COLOR_ATTACHMENT31 0x8CFF
#define GL_COLOR_ATTACHMENT4 0x8CE4
#define GL_COLOR_ATTACHMENT5 0x8CE5
#define GL_COLOR_ATTACHMENT6 0x8CE6
#define GL_COLOR_ATTACHMENT7 0x8CE7
#define GL_COLOR_ATTACHMENT8 0x8CE8
#define GL_COLOR_ATTACHMENT9 0x8CE9
#define GL_COLOR_BUFFER_BIT 0x00004000
#define GL_COLOR_CLEAR_VALUE 0x0C22
#define GL_COLOR_INDEX 0x1900
#define GL_COLOR_INDEXES 0x1603
#define GL_COLOR_LOGIC_OP 0x0BF2
#define GL_COLOR_MATERIAL 0x0B57
#define GL_COLOR_MATERIAL_FACE 0x0B55
#define GL_COLOR_MATERIAL_PARAMETER 0x0B56
#define GL_COLOR_SUM 0x8458
#define GL_COLOR_WRITEMASK 0x0C23
#define GL_COMBINE 0x8570
#define GL_COMBINE_ALPHA 0x8572
#define GL_COMBINE_RGB 0x8571
#define GL_COMPARE_REF_TO_TEXTURE 0x884E
#define GL_COMPARE_R_TO_TEXTURE 0x884E
#define GL_COMPILE 0x1300
#define GL_COMPILE_AND_EXECUTE 0x1301
#define GL_COMPILE_STATUS 0x8B81
#define GL_COMPRESSED_ALPHA 0x84E9
#define GL_COMPRESSED_INTENSITY 0x84EC
#define GL_COMPRESSED_LUMINANCE 0x84EA
#define GL_COMPRESSED_LUMINANCE_ALPHA 0x84EB
#define GL_COMPRESSED_RED 0x8225
#define GL_COMPRESSED_RED_RGTC1 0x8DBB
#define GL_COMPRESSED_RG 0x8226
#define GL_COMPRESSED_RGB 0x84ED
#define GL_COMPRESSED_RGBA 0x84EE
#define GL_COMPRESSED_RG_RGTC2 0x8DBD
#define GL_COMPRESSED_SIGNED_RED_RGTC1 0x8DBC
#define GL_COMPRESSED_SIGNED_RG_RGTC2 0x8DBE
#define GL_COMPRESSED_SLUMINANCE 0x8C4A
#define GL_COMPRESSED_SLUMINANCE_ALPHA 0x8C4B
#define GL_COMPRESSED_SRGB 0x8C48
#define GL_COMPRESSED_SRGB_ALPHA 0x8C49
#define GL_COMPRESSED_TEXTURE_FORMATS 0x86A3
#define GL_CONDITION_SATISFIED 0x911C
#define GL_CONSTANT 0x8576
#define GL_CONSTANT_ALPHA 0x8003
#define GL_CONSTANT_ATTENUATION 0x1207
#define GL_CONSTANT_COLOR 0x8001
#define GL_CONTEXT_COMPATIBILITY_PROFILE_BIT 0x00000002
#define GL_CONTEXT_CORE_PROFILE_BIT 0x00000001
#define GL_CONTEXT_FLAGS 0x821E
#define GL_CONTEXT_FLAG_FORWARD_COMPATIBLE_BIT 0x00000001
#define GL_CONTEXT_PROFILE_MASK 0x9126
#define GL_COORD_REPLACE 0x8862
#define GL_COPY 0x1503
#define GL_COPY_INVERTED 0x150C
#define GL_COPY_PIXEL_TOKEN 0x0706
#define GL_COPY_READ_BUFFER 0x8F36
#define GL_COPY_WRITE_BUFFER 0x8F37
#define GL_CULL_FACE 0x0B44
#define GL_CULL_FACE_MODE 0x0B45
#define GL_CURRENT_BIT 0x00000001
#define GL_CURRENT_COLOR 0x0B00
#define GL_CURRENT_FOG_COORD 0x8453
#define GL_CURRENT_FOG_COORDINATE 0x8453
#define GL_CURRENT_INDEX 0x0B01
#define GL_CURRENT_NORMAL 0x0B02
#define GL_CURRENT_PROGRAM 0x8B8D
#define GL_CURRENT_QUERY 0x8865
#define GL_CURRENT_RASTER_COLOR 0x0B04
#define GL_CURRENT_RASTER_DISTANCE 0x0B09
#define GL_CURRENT_RASTER_INDEX 0x0B05
#define GL_CURRENT_RASTER_POSITION 0x0B07
#define GL_CURRENT_RASTER_POSITION_VALID 0x0B08
#define GL_CURRENT_RASTER_SECONDARY_COLOR 0x845F
#define GL_CURRENT_RASTER_TEXTURE_COORDS 0x0B06
#define GL_CURRENT_SECONDARY_COLOR 0x8459
#define GL_CURRENT_TEXTURE_COORDS 0x0B03
#define GL_CURRENT_VERTEX_ATTRIB 0x8626
#define GL_CW 0x0900
#define GL_DECAL 0x2101
#define GL_DECR 0x1E03
#define GL_DECR_WRAP 0x8508
#define GL_DELETE_STATUS 0x8B80
#define GL_DEPTH 0x1801
#define GL_DEPTH24_STENCIL8 0x88F0
#define GL_DEPTH32F_STENCIL8 0x8CAD
#define GL_DEPTH_ATTACHMENT 0x8D00
#define GL_DEPTH_BIAS 0x0D1F
#define GL_DEPTH_BITS 0x0D56
#define GL_DEPTH_BUFFER_BIT 0x00000100
#define GL_DEPTH_CLAMP 0x864F
#define GL_DEPTH_CLEAR_VALUE 0x0B73
#define GL_DEPTH_COMPONENT 0x1902
#define GL_DEPTH_COMPONENT16 0x81A5
#define GL_DEPTH_COMPONENT24 0x81A6
#define GL_DEPTH_COMPONENT32 0x81A7
#define GL_DEPTH_COMPONENT32F 0x8CAC
#define GL_DEPTH_FUNC 0x0B74
#define GL_DEPTH_RANGE 0x0B70
#define GL_DEPTH_SCALE 0x0D1E
#define GL_DEPTH_STENCIL 0x84F9
#define GL_DEPTH_STENCIL_ATTACHMENT 0x821A
#define GL_DEPTH_TEST 0x0B71
#define GL_DEPTH_TEXTURE_MODE 0x884B
#define GL_DEPTH_WRITEMASK 0x0B72
#define GL_DIFFUSE 0x1201
#define GL_DITHER 0x0BD0
#define GL_DOMAIN 0x0A02
#define GL_DONT_CARE 0x1100
#define GL_DOT3_RGB 0x86AE
#define GL_DOT3_RGBA 0x86AF
#define GL_DOUBLE 0x140A
#define GL_DOUBLEBUFFER 0x0C32
#define GL_DRAW_BUFFER 0x0C01
#define GL_DRAW_BUFFER0 0x8825
#define GL_DRAW_BUFFER1 0x8826
#define GL_DRAW_BUFFER10 0x882F
#define GL_DRAW_BUFFER11 0x8830
#define GL_DRAW_BUFFER12 0x8831
#define GL_DRAW_BUFFER13 0x8832
#define GL_DRAW_BUFFER14 0x8833
#define GL_DRAW_BUFFER15 0x8834
#define GL_DRAW_BUFFER2 0x8827
#define GL_DRAW_BUFFER3 0x8828
#define GL_DRAW_BUFFER4 0x8829
#define GL_DRAW_BUFFER5 0x882A
#define GL_DRAW_BUFFER6 0x882B
#define GL_DRAW_BUFFER7 0x882C
#define GL_DRAW_BUFFER8 0x882D
#define GL_DRAW_BUFFER9 0x882E
#define GL_DRAW_FRAMEBUFFER 0x8CA9
#define GL_DRAW_FRAMEBUFFER_BINDING 0x8CA6
#define GL_DRAW_PIXEL_TOKEN 0x0705
#define GL_DST_ALPHA 0x0304
#define GL_DST_COLOR 0x0306
#define GL_DYNAMIC_COPY 0x88EA
#define GL_DYNAMIC_DRAW 0x88E8
#define GL_DYNAMIC_READ 0x88E9
#define GL_EDGE_FLAG 0x0B43
#define GL_EDGE_FLAG_ARRAY 0x8079
#define GL_EDGE_FLAG_ARRAY_BUFFER_BINDING 0x889B
#define GL_EDGE_FLAG_ARRAY_POINTER 0x8093
#define GL_EDGE_FLAG_ARRAY_STRIDE 0x808C
#define GL_ELEMENT_ARRAY_BUFFER 0x8893
#define GL_ELEMENT_ARRAY_BUFFER_BINDING 0x8895
#define GL_EMISSION 0x1600
#define GL_ENABLE_BIT 0x00002000
#define GL_EQUAL 0x0202
#define GL_EQUIV 0x1509
#define GL_EVAL_BIT 0x00010000
#define GL_EXP 0x0800
#define GL_EXP2 0x0801
#define GL_EXTENSIONS 0x1F03
#define GL_EYE_LINEAR 0x2400
#define GL_EYE_PLANE 0x2502
#define GL_FALSE 0
#define GL_FASTEST 0x1101
#define GL_FEEDBACK 0x1C01
#define GL_FEEDBACK_BUFFER_POINTER 0x0DF0
#define GL_FEEDBACK_BUFFER_SIZE 0x0DF1
#define GL_FEEDBACK_BUFFER_TYPE 0x0DF2
#define GL_FILL 0x1B02
#define GL_FIRST_VERTEX_CONVENTION 0x8E4D
#define GL_FIXED_ONLY 0x891D
#define GL_FLAT 0x1D00
#define GL_FLOAT 0x1406
#define GL_FLOAT_32_UNSIGNED_INT_24_8_REV 0x8DAD
#define GL_FLOAT_MAT2 0x8B5A
#define GL_FLOAT_MAT2x3 0x8B65
#define GL_FLOAT_MAT2x4 0x8B66
#define GL_FLOAT_MAT3 0x8B5B
#define GL_FLOAT_MAT3x2 0x8B67
#define GL_FLOAT_MAT3x4 0x8B68
#define GL_FLOAT_MAT4 0x8B5C
#define GL_FLOAT_MAT4x2 0x8B69
#define GL_FLOAT_MAT4x3 0x8B6A
#define GL_FLOAT_VEC2 0x8B50
#define GL_FLOAT_VEC3 0x8B51
#define GL_FLOAT_VEC4 0x8B52
#define GL_FOG 0x0B60
#define GL_FOG_BIT 0x00000080
#define GL_FOG_COLOR 0x0B66
#define GL_FOG_COORD 0x8451
#define GL_FOG_COORDINATE 0x8451
#define GL_FOG_COORDINATE_ARRAY 0x8457
#define GL_FOG_COORDINATE_ARRAY_BUFFER_BINDING 0x889D
#define GL_FOG_COORDINATE_ARRAY_POINTER 0x8456
#define GL_FOG_COORDINATE_ARRAY_STRIDE 0x8455
#define GL_FOG_COORDINATE_ARRAY_TYPE 0x8454
#define GL_FOG_COORDINATE_SOURCE 0x8450
#define GL_FOG_COORD_ARRAY 0x8457
#define GL_FOG_COORD_ARRAY_BUFFER_BINDING 0x889D
#define GL_FOG_COORD_ARRAY_POINTER 0x8456
#define GL_FOG_COORD_ARRAY_STRIDE 0x8455
#define GL_FOG_COORD_ARRAY_TYPE 0x8454
#define GL_FOG_COORD_SRC 0x8450
#define GL_FOG_DENSITY 0x0B62
#define GL_FOG_END 0x0B64
#define GL_FOG_HINT 0x0C54
#define GL_FOG_INDEX 0x0B61
#define GL_FOG_MODE 0x0B65
#define GL_FOG_START 0x0B63
#define GL_FRAGMENT_DEPTH 0x8452
#define GL_FRAGMENT_SHADER 0x8B30
#define GL_FRAGMENT_SHADER_DERIVATIVE_HINT 0x8B8B
#define GL_FRAMEBUFFER 0x8D40
#define GL_FRAMEBUFFER_ATTACHMENT_ALPHA_SIZE 0x8215
#define GL_FRAMEBUFFER_ATTACHMENT_BLUE_SIZE 0x8214
#define GL_FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING 0x8210
#define GL_FRAMEBUFFER_ATTACHMENT_COMPONENT_TYPE 0x8211
#define GL_FRAMEBUFFER_ATTACHMENT_DEPTH_SIZE 0x8216
#define GL_FRAMEBUFFER_ATTACHMENT_GREEN_SIZE 0x8213
#define GL_FRAMEBUFFER_ATTACHMENT_LAYERED 0x8DA7
#define GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME 0x8CD1
#define GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE 0x8CD0
#define GL_FRAMEBUFFER_ATTACHMENT_RED_SIZE 0x8212
#define GL_FRAMEBUFFER_ATTACHMENT_STENCIL_SIZE 0x8217
#define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE 0x8CD3
#define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LAYER 0x8CD4
#define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL 0x8CD2
#define GL_FRAMEBUFFER_BINDING 0x8CA6
#define GL_FRAMEBUFFER_COMPLETE 0x8CD5
#define GL_FRAMEBUFFER_DEFAULT 0x8218
#define GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT 0x8CD6
#define GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER 0x8CDB
#define GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS 0x8DA8
#define GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT 0x8CD7
#define GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE 0x8D56
#define GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER 0x8CDC
#define GL_FRAMEBUFFER_SRGB 0x8DB9
#define GL_FRAMEBUFFER_UNDEFINED 0x8219
#define GL_FRAMEBUFFER_UNSUPPORTED 0x8CDD
#define GL_FRONT 0x0404
#define GL_FRONT_AND_BACK 0x0408
#define GL_FRONT_FACE 0x0B46
#define GL_FRONT_LEFT 0x0400
#define GL_FRONT_RIGHT 0x0401
#define GL_FUNC_ADD 0x8006
#define GL_FUNC_REVERSE_SUBTRACT 0x800B
#define GL_FUNC_SUBTRACT 0x800A
#define GL_GENERATE_MIPMAP 0x8191
#define GL_GENERATE_MIPMAP_HINT 0x8192
#define GL_GEOMETRY_INPUT_TYPE 0x8917
#define GL_GEOMETRY_OUTPUT_TYPE 0x8918
#define GL_GEOMETRY_SHADER 0x8DD9
#define GL_GEOMETRY_VERTICES_OUT 0x8916
#define GL_GEQUAL 0x0206
#define GL_GREATER 0x0204
#define GL_GREEN 0x1904
#define GL_GREEN_BIAS 0x0D19
#define GL_GREEN_BITS 0x0D53
#define GL_GREEN_INTEGER 0x8D95
#define GL_GREEN_SCALE 0x0D18
#define GL_HALF_FLOAT 0x140B
#define GL_HINT_BIT 0x00008000
#define GL_INCR 0x1E02
#define GL_INCR_WRAP 0x8507
#define GL_INDEX 0x8222
#define GL_INDEX_ARRAY 0x8077
#define GL_INDEX_ARRAY_BUFFER_BINDING 0x8899
#define GL_INDEX_ARRAY_POINTER 0x8091
#define GL_INDEX_ARRAY_STRIDE 0x8086
#define GL_INDEX_ARRAY_TYPE 0x8085
#define GL_INDEX_BITS 0x0D51
#define GL_INDEX_CLEAR_VALUE 0x0C20
#define GL_INDEX_LOGIC_OP 0x0BF1
#define GL_INDEX_MODE 0x0C30
#define GL_INDEX_OFFSET 0x0D13
#define GL_INDEX_SHIFT 0x0D12
#define GL_INDEX_WRITEMASK 0x0C21
#define GL_INFO_LOG_LENGTH 0x8B84
#define GL_INT 0x1404
#define GL_INTENSITY 0x8049
#define GL_INTENSITY12 0x804C
#define GL_INTENSITY16 0x804D
#define GL_INTENSITY4 0x804A
#define GL_INTENSITY8 0x804B
#define GL_INTERLEAVED_ATTRIBS 0x8C8C
#define GL_INTERPOLATE 0x8575
#define GL_INT_2_10_10_10_REV 0x8D9F
#define GL_INT_SAMPLER_1D 0x8DC9
#define GL_INT_SAMPLER_1D_ARRAY 0x8DCE
#define GL_INT_SAMPLER_2D 0x8DCA
#define GL_INT_SAMPLER_2D_ARRAY 0x8DCF
#define GL_INT_SAMPLER_2D_MULTISAMPLE 0x9109
#define GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY 0x910C
#define GL_INT_SAMPLER_2D_RECT 0x8DCD
#define GL_INT_SAMPLER_3D 0x8DCB
#define GL_INT_SAMPLER_BUFFER 0x8DD0
#define GL_INT_SAMPLER_CUBE 0x8DCC
#define GL_INT_VEC2 0x8B53
#define GL_INT_VEC3 0x8B54
#define GL_INT_VEC4 0x8B55
#define GL_INVALID_ENUM 0x0500
#define GL_INVALID_FRAMEBUFFER_OPERATION 0x0506
#define GL_INVALID_INDEX 0xFFFFFFFF
#define GL_INVALID_OPERATION 0x0502
#define GL_INVALID_VALUE 0x0501
#define GL_INVERT 0x150A
#define GL_KEEP 0x1E00
#define GL_LAST_VERTEX_CONVENTION 0x8E4E
#define GL_LEFT 0x0406
#define GL_LEQUAL 0x0203
#define GL_LESS 0x0201
#define GL_LIGHT0 0x4000
#define GL_LIGHT1 0x4001
#define GL_LIGHT2 0x4002
#define GL_LIGHT3 0x4003
#define GL_LIGHT4 0x4004
#define GL_LIGHT5 0x4005
#define GL_LIGHT6 0x4006
#define GL_LIGHT7 0x4007
#define GL_LIGHTING 0x0B50
#define GL_LIGHTING_BIT 0x00000040
#define GL_LIGHT_MODEL_AMBIENT 0x0B53
#define GL_LIGHT_MODEL_COLOR_CONTROL 0x81F8
#define GL_LIGHT_MODEL_LOCAL_VIEWER 0x0B51
#define GL_LIGHT_MODEL_TWO_SIDE 0x0B52
#define GL_LINE 0x1B01
#define GL_LINEAR 0x2601
#define GL_LINEAR_ATTENUATION 0x1208
#define GL_LINEAR_MIPMAP_LINEAR 0x2703
#define GL_LINEAR_MIPMAP_NEAREST 0x2701
#define GL_LINES 0x0001
#define GL_LINES_ADJACENCY 0x000A
#define GL_LINE_BIT 0x00000004
#define GL_LINE_LOOP 0x0002
#define GL_LINE_RESET_TOKEN 0x0707
#define GL_LINE_SMOOTH 0x0B20
#define GL_LINE_SMOOTH_HINT 0x0C52
#define GL_LINE_STIPPLE 0x0B24
#define GL_LINE_STIPPLE_PATTERN 0x0B25
#define GL_LINE_STIPPLE_REPEAT 0x0B26
#define GL_LINE_STRIP 0x0003
#define GL_LINE_STRIP_ADJACENCY 0x000B
#define GL_LINE_TOKEN 0x0702
#define GL_LINE_WIDTH 0x0B21
#define GL_LINE_WIDTH_GRANULARITY 0x0B23
#define GL_LINE_WIDTH_RANGE 0x0B22
#define GL_LINK_STATUS 0x8B82
#define GL_LIST_BASE 0x0B32
#define GL_LIST_BIT 0x00020000
#define GL_LIST_INDEX 0x0B33
#define GL_LIST_MODE 0x0B30
#define GL_LOAD 0x0101
#define GL_LOGIC_OP 0x0BF1
#define GL_LOGIC_OP_MODE 0x0BF0
#define GL_LOWER_LEFT 0x8CA1
#define GL_LUMINANCE 0x1909
#define GL_LUMINANCE12 0x8041
#define GL_LUMINANCE12_ALPHA12 0x8047
#define GL_LUMINANCE12_ALPHA4 0x8046
#define GL_LUMINANCE16 0x8042
#define GL_LUMINANCE16_ALPHA16 0x8048
#define GL_LUMINANCE4 0x803F
#define GL_LUMINANCE4_ALPHA4 0x8043
#define GL_LUMINANCE6_ALPHA2 0x8044
#define GL_LUMINANCE8 0x8040
#define GL_LUMINANCE8_ALPHA8 0x8045
#define GL_LUMINANCE_ALPHA 0x190A
#define GL_MAJOR_VERSION 0x821B
#define GL_MAP1_COLOR_4 0x0D90
#define GL_MAP1_GRID_DOMAIN 0x0DD0
#define GL_MAP1_GRID_SEGMENTS 0x0DD1
#define GL_MAP1_INDEX 0x0D91
#define GL_MAP1_NORMAL 0x0D92
#define GL_MAP1_TEXTURE_COORD_1 0x0D93
#define GL_MAP1_TEXTURE_COORD_2 0x0D94
#define GL_MAP1_TEXTURE_COORD_3 0x0D95
#define GL_MAP1_TEXTURE_COORD_4 0x0D96
#define GL_MAP1_VERTEX_3 0x0D97
#define GL_MAP1_VERTEX_4 0x0D98
#define GL_MAP2_COLOR_4 0x0DB0
#define GL_MAP2_GRID_DOMAIN 0x0DD2
#define GL_MAP2_GRID_SEGMENTS 0x0DD3
#define GL_MAP2_INDEX 0x0DB1
#define GL_MAP2_NORMAL 0x0DB2
#define GL_MAP2_TEXTURE_COORD_1 0x0DB3
#define GL_MAP2_TEXTURE_COORD_2 0x0DB4
#define GL_MAP2_TEXTURE_COORD_3 0x0DB5
#define GL_MAP2_TEXTURE_COORD_4 0x0DB6
#define GL_MAP2_VERTEX_3 0x0DB7
#define GL_MAP2_VERTEX_4 0x0DB8
#define GL_MAP_COLOR 0x0D10
#define GL_MAP_FLUSH_EXPLICIT_BIT 0x0010
#define GL_MAP_INVALIDATE_BUFFER_BIT 0x0008
#define GL_MAP_INVALIDATE_RANGE_BIT 0x0004
#define GL_MAP_READ_BIT 0x0001
#define GL_MAP_STENCIL 0x0D11
#define GL_MAP_UNSYNCHRONIZED_BIT 0x0020
#define GL_MAP_WRITE_BIT 0x0002
#define GL_MATRIX_MODE 0x0BA0
#define GL_MAX 0x8008
#define GL_MAX_3D_TEXTURE_SIZE 0x8073
#define GL_MAX_ARRAY_TEXTURE_LAYERS 0x88FF
#define GL_MAX_ATTRIB_STACK_DEPTH 0x0D35
#define GL_MAX_CLIENT_ATTRIB_STACK_DEPTH 0x0D3B
#define GL_MAX_CLIP_DISTANCES 0x0D32
#define GL_MAX_CLIP_PLANES 0x0D32
#define GL_MAX_COLOR_ATTACHMENTS 0x8CDF
#define GL_MAX_COLOR_TEXTURE_SAMPLES 0x910E
#define GL_MAX_COMBINED_FRAGMENT_UNIFORM_COMPONENTS 0x8A33
#define GL_MAX_COMBINED_GEOMETRY_UNIFORM_COMPONENTS 0x8A32
#define GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS 0x8B4D
#define GL_MAX_COMBINED_UNIFORM_BLOCKS 0x8A2E
#define GL_MAX_COMBINED_VERTEX_UNIFORM_COMPONENTS 0x8A31
#define GL_MAX_CUBE_MAP_TEXTURE_SIZE 0x851C
#define GL_MAX_DEPTH_TEXTURE_SAMPLES 0x910F
#define GL_MAX_DRAW_BUFFERS 0x8824
#define GL_MAX_DUAL_SOURCE_DRAW_BUFFERS 0x88FC
#define GL_MAX_ELEMENTS_INDICES 0x80E9
#define GL_MAX_ELEMENTS_VERTICES 0x80E8
#define GL_MAX_EVAL_ORDER 0x0D30
#define GL_MAX_FRAGMENT_INPUT_COMPONENTS 0x9125
#define GL_MAX_FRAGMENT_UNIFORM_BLOCKS 0x8A2D
#define GL_MAX_FRAGMENT_UNIFORM_COMPONENTS 0x8B49
#define GL_MAX_GEOMETRY_INPUT_COMPONENTS 0x9123
#define GL_MAX_GEOMETRY_OUTPUT_COMPONENTS 0x9124
#define GL_MAX_GEOMETRY_OUTPUT_VERTICES 0x8DE0
#define GL_MAX_GEOMETRY_TEXTURE_IMAGE_UNITS 0x8C29
#define GL_MAX_GEOMETRY_TOTAL_OUTPUT_COMPONENTS 0x8DE1
#define GL_MAX_GEOMETRY_UNIFORM_BLOCKS 0x8A2C
#define GL_MAX_GEOMETRY_UNIFORM_COMPONENTS 0x8DDF
#define GL_MAX_INTEGER_SAMPLES 0x9110
#define GL_MAX_LIGHTS 0x0D31
#define GL_MAX_LIST_NESTING 0x0B31
#define GL_MAX_MODELVIEW_STACK_DEPTH 0x0D36
#define GL_MAX_NAME_STACK_DEPTH 0x0D37
#define GL_MAX_PIXEL_MAP_TABLE 0x0D34
#define GL_MAX_PROGRAM_TEXEL_OFFSET 0x8905
#define GL_MAX_PROJECTION_STACK_DEPTH 0x0D38
#define GL_MAX_RECTANGLE_TEXTURE_SIZE 0x84F8
#define GL_MAX_RENDERBUFFER_SIZE 0x84E8
#define GL_MAX_SAMPLES 0x8D57
#define GL_MAX_SAMPLE_MASK_WORDS 0x8E59
#define GL_MAX_SERVER_WAIT_TIMEOUT 0x9111
#define GL_MAX_TEXTURE_BUFFER_SIZE 0x8C2B
#define GL_MAX_TEXTURE_COORDS 0x8871
#define GL_MAX_TEXTURE_IMAGE_UNITS 0x8872
#define GL_MAX_TEXTURE_LOD_BIAS 0x84FD
#define GL_MAX_TEXTURE_SIZE 0x0D33
#define GL_MAX_TEXTURE_STACK_DEPTH 0x0D39
#define GL_MAX_TEXTURE_UNITS 0x84E2
#define GL_MAX_TRANSFORM_FEEDBACK_INTERLEAVED_COMPONENTS 0x8C8A
#define GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_ATTRIBS 0x8C8B
#define GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_COMPONENTS 0x8C80
#define GL_MAX_UNIFORM_BLOCK_SIZE 0x8A30
#define GL_MAX_UNIFORM_BUFFER_BINDINGS 0x8A2F
#define GL_MAX_VARYING_COMPONENTS 0x8B4B
#define GL_MAX_VARYING_FLOATS 0x8B4B
#define GL_MAX_VERTEX_ATTRIBS 0x8869
#define GL_MAX_VERTEX_OUTPUT_COMPONENTS 0x9122
#define GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS 0x8B4C
#define GL_MAX_VERTEX_UNIFORM_BLOCKS 0x8A2B
#define GL_MAX_VERTEX_UNIFORM_COMPONENTS 0x8B4A
#define GL_MAX_VIEWPORT_DIMS 0x0D3A
#define GL_MIN 0x8007
#define GL_MINOR_VERSION 0x821C
#define GL_MIN_PROGRAM_TEXEL_OFFSET 0x8904
#define GL_MIRRORED_REPEAT 0x8370
#define GL_MODELVIEW 0x1700
#define GL_MODELVIEW_MATRIX 0x0BA6
#define GL_MODELVIEW_STACK_DEPTH 0x0BA3
#define GL_MODULATE 0x2100
#define GL_MULT 0x0103
#define GL_MULTISAMPLE 0x809D
#define GL_MULTISAMPLE_BIT 0x20000000
#define GL_N3F_V3F 0x2A25
#define GL_NAME_STACK_DEPTH 0x0D70
#define GL_NAND 0x150E
#define GL_NEAREST 0x2600
#define GL_NEAREST_MIPMAP_LINEAR 0x2702
#define GL_NEAREST_MIPMAP_NEAREST 0x2700
#define GL_NEVER 0x0200
#define GL_NICEST 0x1102
#define GL_NONE 0
#define GL_NOOP 0x1505
#define GL_NOR 0x1508
#define GL_NORMALIZE 0x0BA1
#define GL_NORMAL_ARRAY 0x8075
#define GL_NORMAL_ARRAY_BUFFER_BINDING 0x8897
#define GL_NORMAL_ARRAY_POINTER 0x808F
#define GL_NORMAL_ARRAY_STRIDE 0x807F
#define GL_NORMAL_ARRAY_TYPE 0x807E
#define GL_NORMAL_MAP 0x8511
#define GL_NOTEQUAL 0x0205
#define GL_NO_ERROR 0
#define GL_NUM_COMPRESSED_TEXTURE_FORMATS 0x86A2
#define GL_NUM_EXTENSIONS 0x821D
#define GL_OBJECT_LINEAR 0x2401
#define GL_OBJECT_PLANE 0x2501
#define GL_OBJECT_TYPE 0x9112
#define GL_ONE 1
#define GL_ONE_MINUS_CONSTANT_ALPHA 0x8004
#define GL_ONE_MINUS_CONSTANT_COLOR 0x8002
#define GL_ONE_MINUS_DST_ALPHA 0x0305
#define GL_ONE_MINUS_DST_COLOR 0x0307
#define GL_ONE_MINUS_SRC1_ALPHA 0x88FB
#define GL_ONE_MINUS_SRC1_COLOR 0x88FA
#define GL_ONE_MINUS_SRC_ALPHA 0x0303
#define GL_ONE_MINUS_SRC_COLOR 0x0301
#define GL_OPERAND0_ALPHA 0x8598
#define GL_OPERAND0_RGB 0x8590
#define GL_OPERAND1_ALPHA 0x8599
#define GL_OPERAND1_RGB 0x8591
#define GL_OPERAND2_ALPHA 0x859A
#define GL_OPERAND2_RGB 0x8592
#define GL_OR 0x1507
#define GL_ORDER 0x0A01
#define GL_OR_INVERTED 0x150D
#define GL_OR_REVERSE 0x150B
#define GL_OUT_OF_MEMORY 0x0505
#define GL_PACK_ALIGNMENT 0x0D05
#define GL_PACK_IMAGE_HEIGHT 0x806C
#define GL_PACK_LSB_FIRST 0x0D01
#define GL_PACK_ROW_LENGTH 0x0D02
#define GL_PACK_SKIP_IMAGES 0x806B
#define GL_PACK_SKIP_PIXELS 0x0D04
#define GL_PACK_SKIP_ROWS 0x0D03
#define GL_PACK_SWAP_BYTES 0x0D00
#define GL_PASS_THROUGH_TOKEN 0x0700
#define GL_PERSPECTIVE_CORRECTION_HINT 0x0C50
#define GL_PIXEL_MAP_A_TO_A 0x0C79
#define GL_PIXEL_MAP_A_TO_A_SIZE 0x0CB9
#define GL_PIXEL_MAP_B_TO_B 0x0C78
#define GL_PIXEL_MAP_B_TO_B_SIZE 0x0CB8
#define GL_PIXEL_MAP_G_TO_G 0x0C77
#define GL_PIXEL_MAP_G_TO_G_SIZE 0x0CB7
#define GL_PIXEL_MAP_I_TO_A 0x0C75
#define GL_PIXEL_MAP_I_TO_A_SIZE 0x0CB5
#define GL_PIXEL_MAP_I_TO_B 0x0C74
#define GL_PIXEL_MAP_I_TO_B_SIZE 0x0CB4
#define GL_PIXEL_MAP_I_TO_G 0x0C73
#define GL_PIXEL_MAP_I_TO_G_SIZE 0x0CB3
#define GL_PIXEL_MAP_I_TO_I 0x0C70
#define GL_PIXEL_MAP_I_TO_I_SIZE 0x0CB0
#define GL_PIXEL_MAP_I_TO_R 0x0C72
#define GL_PIXEL_MAP_I_TO_R_SIZE 0x0CB2
#define GL_PIXEL_MAP_R_TO_R 0x0C76
#define GL_PIXEL_MAP_R_TO_R_SIZE 0x0CB6
#define GL_PIXEL_MAP_S_TO_S 0x0C71
#define GL_PIXEL_MAP_S_TO_S_SIZE 0x0CB1
#define GL_PIXEL_MODE_BIT 0x00000020
#define GL_PIXEL_PACK_BUFFER 0x88EB
#define GL_PIXEL_PACK_BUFFER_BINDING 0x88ED
#define GL_PIXEL_UNPACK_BUFFER 0x88EC
#define GL_PIXEL_UNPACK_BUFFER_BINDING 0x88EF
#define GL_POINT 0x1B00
#define GL_POINTS 0x0000
#define GL_POINT_BIT 0x00000002
#define GL_POINT_DISTANCE_ATTENUATION 0x8129
#define GL_POINT_FADE_THRESHOLD_SIZE 0x8128
#define GL_POINT_SIZE 0x0B11
#define GL_POINT_SIZE_GRANULARITY 0x0B13
#define GL_POINT_SIZE_MAX 0x8127
#define GL_POINT_SIZE_MIN 0x8126
#define GL_POINT_SIZE_RANGE 0x0B12
#define GL_POINT_SMOOTH 0x0B10
#define GL_POINT_SMOOTH_HINT 0x0C51
#define GL_POINT_SPRITE 0x8861
#define GL_POINT_SPRITE_COORD_ORIGIN 0x8CA0
#define GL_POINT_TOKEN 0x0701
#define GL_POLYGON 0x0009
#define GL_POLYGON_BIT 0x00000008
#define GL_POLYGON_MODE 0x0B40
#define GL_POLYGON_OFFSET_FACTOR 0x8038
#define GL_POLYGON_OFFSET_FILL 0x8037
#define GL_POLYGON_OFFSET_LINE 0x2A02
#define GL_POLYGON_OFFSET_POINT 0x2A01
#define GL_POLYGON_OFFSET_UNITS 0x2A00
#define GL_POLYGON_SMOOTH 0x0B41
#define GL_POLYGON_SMOOTH_HINT 0x0C53
#define GL_POLYGON_STIPPLE 0x0B42
#define GL_POLYGON_STIPPLE_BIT 0x00000010
#define GL_POLYGON_TOKEN 0x0703
#define GL_POSITION 0x1203
#define GL_PREVIOUS 0x8578
#define GL_PRIMARY_COLOR 0x8577
#define GL_PRIMITIVES_GENERATED 0x8C87
#define GL_PRIMITIVE_RESTART 0x8F9D
#define GL_PRIMITIVE_RESTART_INDEX 0x8F9E
#define GL_PROGRAM_POINT_SIZE 0x8642
#define GL_PROJECTION 0x1701
#define GL_PROJECTION_MATRIX 0x0BA7
#define GL_PROJECTION_STACK_DEPTH 0x0BA4
#define GL_PROVOKING_VERTEX 0x8E4F
#define GL_PROXY_TEXTURE_1D 0x8063
#define GL_PROXY_TEXTURE_1D_ARRAY 0x8C19
#define GL_PROXY_TEXTURE_2D 0x8064
#define GL_PROXY_TEXTURE_2D_ARRAY 0x8C1B
#define GL_PROXY_TEXTURE_2D_MULTISAMPLE 0x9101
#define GL_PROXY_TEXTURE_2D_MULTISAMPLE_ARRAY 0x9103
#define GL_PROXY_TEXTURE_3D 0x8070
#define GL_PROXY_TEXTURE_CUBE_MAP 0x851B
#define GL_PROXY_TEXTURE_RECTANGLE 0x84F7
#define GL_Q 0x2003
#define GL_QUADRATIC_ATTENUATION 0x1209
#define GL_QUADS 0x0007
#define GL_QUADS_FOLLOW_PROVOKING_VERTEX_CONVENTION 0x8E4C
#define GL_QUAD_STRIP 0x0008
#define GL_QUERY_BY_REGION_NO_WAIT 0x8E16
#define GL_QUERY_BY_REGION_WAIT 0x8E15
#define GL_QUERY_COUNTER_BITS 0x8864
#define GL_QUERY_NO_WAIT 0x8E14
#define GL_QUERY_RESULT 0x8866
#define GL_QUERY_RESULT_AVAILABLE 0x8867
#define GL_QUERY_WAIT 0x8E13
#define GL_R 0x2002
#define GL_R11F_G11F_B10F 0x8C3A
#define GL_R16 0x822A
#define GL_R16F 0x822D
#define GL_R16I 0x8233
#define GL_R16UI 0x8234
#define GL_R16_SNORM 0x8F98
#define GL_R32F 0x822E
#define GL_R32I 0x8235
#define GL_R32UI 0x8236
#define GL_R3_G3_B2 0x2A10
#define GL_R8 0x8229
#define GL_R8I 0x8231
#define GL_R8UI 0x8232
#define GL_R8_SNORM 0x8F94
#define GL_RASTERIZER_DISCARD 0x8C89
#define GL_READ_BUFFER 0x0C02
#define GL_READ_FRAMEBUFFER 0x8CA8
#define GL_READ_FRAMEBUFFER_BINDING 0x8CAA
#define GL_READ_ONLY 0x88B8
#define GL_READ_WRITE 0x88BA
#define GL_RED 0x1903
#define GL_RED_BIAS 0x0D15
#define GL_RED_BITS 0x0D52
#define GL_RED_INTEGER 0x8D94
#define GL_RED_SCALE 0x0D14
#define GL_REFLECTION_MAP 0x8512
#define GL_RENDER 0x1C00
#define GL_RENDERBUFFER 0x8D41
#define GL_RENDERBUFFER_ALPHA_SIZE 0x8D53
#define GL_RENDERBUFFER_BINDING 0x8CA7
#define GL_RENDERBUFFER_BLUE_SIZE 0x8D52
#define GL_RENDERBUFFER_DEPTH_SIZE 0x8D54
#define GL_RENDERBUFFER_GREEN_SIZE 0x8D51
#define GL_RENDERBUFFER_HEIGHT 0x8D43
#define GL_RENDERBUFFER_INTERNAL_FORMAT 0x8D44
#define GL_RENDERBUFFER_RED_SIZE 0x8D50
#define GL_RENDERBUFFER_SAMPLES 0x8CAB
#define GL_RENDERBUFFER_STENCIL_SIZE 0x8D55
#define GL_RENDERBUFFER_WIDTH 0x8D42
#define GL_RENDERER 0x1F01
#define GL_RENDER_MODE 0x0C40
#define GL_REPEAT 0x2901
#define GL_REPLACE 0x1E01
#define GL_RESCALE_NORMAL 0x803A
#define GL_RETURN 0x0102
#define GL_RG 0x8227
#define GL_RG16 0x822C
#define GL_RG16F 0x822F
#define GL_RG16I 0x8239
#define GL_RG16UI 0x823A
#define GL_RG16_SNORM 0x8F99
#define GL_RG32F 0x8230
#define GL_RG32I 0x823B
#define GL_RG32UI 0x823C
#define GL_RG8 0x822B
#define GL_RG8I 0x8237
#define GL_RG8UI 0x8238
#define GL_RG8_SNORM 0x8F95
#define GL_RGB 0x1907
#define GL_RGB10 0x8052
#define GL_RGB10_A2 0x8059
#define GL_RGB10_A2UI 0x906F
#define GL_RGB12 0x8053
#define GL_RGB16 0x8054
#define GL_RGB16F 0x881B
#define GL_RGB16I 0x8D89
#define GL_RGB16UI 0x8D77
#define GL_RGB16_SNORM 0x8F9A
#define GL_RGB32F 0x8815
#define GL_RGB32I 0x8D83
#define GL_RGB32UI 0x8D71
#define GL_RGB4 0x804F
#define GL_RGB5 0x8050
#define GL_RGB5_A1 0x8057
#define GL_RGB8 0x8051
#define GL_RGB8I 0x8D8F
#define GL_RGB8UI 0x8D7D
#define GL_RGB8_SNORM 0x8F96
#define GL_RGB9_E5 0x8C3D
#define GL_RGBA 0x1908
#define GL_RGBA12 0x805A
#define GL_RGBA16 0x805B
#define GL_RGBA16F 0x881A
#define GL_RGBA16I 0x8D88
#define GL_RGBA16UI 0x8D76
#define GL_RGBA16_SNORM 0x8F9B
#define GL_RGBA2 0x8055
#define GL_RGBA32F 0x8814
#define GL_RGBA32I 0x8D82
#define GL_RGBA32UI 0x8D70
#define GL_RGBA4 0x8056
#define GL_RGBA8 0x8058
#define GL_RGBA8I 0x8D8E
#define GL_RGBA8UI 0x8D7C
#define GL_RGBA8_SNORM 0x8F97
#define GL_RGBA_INTEGER 0x8D99
#define GL_RGBA_MODE 0x0C31
#define GL_RGB_INTEGER 0x8D98
#define GL_RGB_SCALE 0x8573
#define GL_RG_INTEGER 0x8228
#define GL_RIGHT 0x0407
#define GL_S 0x2000
#define GL_SAMPLER_1D 0x8B5D
#define GL_SAMPLER_1D_ARRAY 0x8DC0
#define GL_SAMPLER_1D_ARRAY_SHADOW 0x8DC3
#define GL_SAMPLER_1D_SHADOW 0x8B61
#define GL_SAMPLER_2D 0x8B5E
#define GL_SAMPLER_2D_ARRAY 0x8DC1
#define GL_SAMPLER_2D_ARRAY_SHADOW 0x8DC4
#define GL_SAMPLER_2D_MULTISAMPLE 0x9108
#define GL_SAMPLER_2D_MULTISAMPLE_ARRAY 0x910B
#define GL_SAMPLER_2D_RECT 0x8B63
#define GL_SAMPLER_2D_RECT_SHADOW 0x8B64
#define GL_SAMPLER_2D_SHADOW 0x8B62
#define GL_SAMPLER_3D 0x8B5F
#define GL_SAMPLER_BINDING 0x8919
#define GL_SAMPLER_BUFFER 0x8DC2
#define GL_SAMPLER_CUBE 0x8B60
#define GL_SAMPLER_CUBE_SHADOW 0x8DC5
#define GL_SAMPLES 0x80A9
#define GL_SAMPLES_PASSED 0x8914
#define GL_SAMPLE_ALPHA_TO_COVERAGE 0x809E
#define GL_SAMPLE_ALPHA_TO_ONE 0x809F
#define GL_SAMPLE_BUFFERS 0x80A8
#define GL_SAMPLE_COVERAGE 0x80A0
#define GL_SAMPLE_COVERAGE_INVERT 0x80AB
#define GL_SAMPLE_COVERAGE_VALUE 0x80AA
#define GL_SAMPLE_MASK 0x8E51
#define GL_SAMPLE_MASK_VALUE 0x8E52
#define GL_SAMPLE_POSITION 0x8E50
#define GL_SCISSOR_BIT 0x00080000
#define GL_SCISSOR_BOX 0x0C10
#define GL_SCISSOR_TEST 0x0C11
#define GL_SECONDARY_COLOR_ARRAY 0x845E
#define GL_SECONDARY_COLOR_ARRAY_BUFFER_BINDING 0x889C
#define GL_SECONDARY_COLOR_ARRAY_POINTER 0x845D
#define GL_SECONDARY_COLOR_ARRAY_SIZE 0x845A
#define GL_SECONDARY_COLOR_ARRAY_STRIDE 0x845C
#define GL_SECONDARY_COLOR_ARRAY_TYPE 0x845B
#define GL_SELECT 0x1C02
#define GL_SELECTION_BUFFER_POINTER 0x0DF3
#define GL_SELECTION_BUFFER_SIZE 0x0DF4
#define GL_SEPARATE_ATTRIBS 0x8C8D
#define GL_SEPARATE_SPECULAR_COLOR 0x81FA
#define GL_SET 0x150F
#define GL_SHADER_SOURCE_LENGTH 0x8B88
#define GL_SHADER_TYPE 0x8B4F
#define GL_SHADE_MODEL 0x0B54
#define GL_SHADING_LANGUAGE_VERSION 0x8B8C
#define GL_SHININESS 0x1601
#define GL_SHORT 0x1402
#define GL_SIGNALED 0x9119
#define GL_SIGNED_NORMALIZED 0x8F9C
#define GL_SINGLE_COLOR 0x81F9
#define GL_SLUMINANCE 0x8C46
#define GL_SLUMINANCE8 0x8C47
#define GL_SLUMINANCE8_ALPHA8 0x8C45
#define GL_SLUMINANCE_ALPHA 0x8C44
#define GL_SMOOTH 0x1D01
#define GL_SMOOTH_LINE_WIDTH_GRANULARITY 0x0B23
#define GL_SMOOTH_LINE_WIDTH_RANGE 0x0B22
#define GL_SMOOTH_POINT_SIZE_GRANULARITY 0x0B13
#define GL_SMOOTH_POINT_SIZE_RANGE 0x0B12
#define GL_SOURCE0_ALPHA 0x8588
#define GL_SOURCE0_RGB 0x8580
#define GL_SOURCE1_ALPHA 0x8589
#define GL_SOURCE1_RGB 0x8581
#define GL_SOURCE2_ALPHA 0x858A
#define GL_SOURCE2_RGB 0x8582
#define GL_SPECULAR 0x1202
#define GL_SPHERE_MAP 0x2402
#define GL_SPOT_CUTOFF 0x1206
#define GL_SPOT_DIRECTION 0x1204
#define GL_SPOT_EXPONENT 0x1205
#define GL_SRC0_ALPHA 0x8588
#define GL_SRC0_RGB 0x8580
#define GL_SRC1_ALPHA 0x8589
#define GL_SRC1_COLOR 0x88F9
#define GL_SRC1_RGB 0x8581
#define GL_SRC2_ALPHA 0x858A
#define GL_SRC2_RGB 0x8582
#define GL_SRC_ALPHA 0x0302
#define GL_SRC_ALPHA_SATURATE 0x0308
#define GL_SRC_COLOR 0x0300
#define GL_SRGB 0x8C40
#define GL_SRGB8 0x8C41
#define GL_SRGB8_ALPHA8 0x8C43
#define GL_SRGB_ALPHA 0x8C42
#define GL_STACK_OVERFLOW 0x0503
#define GL_STACK_UNDERFLOW 0x0504
#define GL_STATIC_COPY 0x88E6
#define GL_STATIC_DRAW 0x88E4
#define GL_STATIC_READ 0x88E5
#define GL_STENCIL 0x1802
#define GL_STENCIL_ATTACHMENT 0x8D20
#define GL_STENCIL_BACK_FAIL 0x8801
#define GL_STENCIL_BACK_FUNC 0x8800
#define GL_STENCIL_BACK_PASS_DEPTH_FAIL 0x8802
#define GL_STENCIL_BACK_PASS_DEPTH_PASS 0x8803
#define GL_STENCIL_BACK_REF 0x8CA3
#define GL_STENCIL_BACK_VALUE_MASK 0x8CA4
#define GL_STENCIL_BACK_WRITEMASK 0x8CA5
#define GL_STENCIL_BITS 0x0D57
#define GL_STENCIL_BUFFER_BIT 0x00000400
#define GL_STENCIL_CLEAR_VALUE 0x0B91
#define GL_STENCIL_FAIL 0x0B94
#define GL_STENCIL_FUNC 0x0B92
#define GL_STENCIL_INDEX 0x1901
#define GL_STENCIL_INDEX1 0x8D46
#define GL_STENCIL_INDEX16 0x8D49
#define GL_STENCIL_INDEX4 0x8D47
#define GL_STENCIL_INDEX8 0x8D48
#define GL_STENCIL_PASS_DEPTH_FAIL 0x0B95
#define GL_STENCIL_PASS_DEPTH_PASS 0x0B96
#define GL_STENCIL_REF 0x0B97
#define GL_STENCIL_TEST 0x0B90
#define GL_STENCIL_VALUE_MASK 0x0B93
#define GL_STENCIL_WRITEMASK 0x0B98
#define GL_STEREO 0x0C33
#define GL_STREAM_COPY 0x88E2
#define GL_STREAM_DRAW 0x88E0
#define GL_STREAM_READ 0x88E1
#define GL_SUBPIXEL_BITS 0x0D50
#define GL_SUBTRACT 0x84E7
#define GL_SYNC_CONDITION 0x9113
#define GL_SYNC_FENCE 0x9116
#define GL_SYNC_FLAGS 0x9115
#define GL_SYNC_FLUSH_COMMANDS_BIT 0x00000001
#define GL_SYNC_GPU_COMMANDS_COMPLETE 0x9117
#define GL_SYNC_STATUS 0x9114
#define GL_T 0x2001
#define GL_T2F_C3F_V3F 0x2A2A
#define GL_T2F_C4F_N3F_V3F 0x2A2C
#define GL_T2F_C4UB_V3F 0x2A29
#define GL_T2F_N3F_V3F 0x2A2B
#define GL_T2F_V3F 0x2A27
#define GL_T4F_C4F_N3F_V4F 0x2A2D
#define GL_T4F_V4F 0x2A28
#define GL_TEXTURE 0x1702
#define GL_TEXTURE0 0x84C0
#define GL_TEXTURE1 0x84C1
#define GL_TEXTURE10 0x84CA
#define GL_TEXTURE11 0x84CB
#define GL_TEXTURE12 0x84CC
#define GL_TEXTURE13 0x84CD
#define GL_TEXTURE14 0x84CE
#define GL_TEXTURE15 0x84CF
#define GL_TEXTURE16 0x84D0
#define GL_TEXTURE17 0x84D1
#define GL_TEXTURE18 0x84D2
#define GL_TEXTURE19 0x84D3
#define GL_TEXTURE2 0x84C2
#define GL_TEXTURE20 0x84D4
#define GL_TEXTURE21 0x84D5
#define GL_TEXTURE22 0x84D6
#define GL_TEXTURE23 0x84D7
#define GL_TEXTURE24 0x84D8
#define GL_TEXTURE25 0x84D9
#define GL_TEXTURE26 0x84DA
#define GL_TEXTURE27 0x84DB
#define GL_TEXTURE28 0x84DC
#define GL_TEXTURE29 0x84DD
#define GL_TEXTURE3 0x84C3
#define GL_TEXTURE30 0x84DE
#define GL_TEXTURE31 0x84DF
#define GL_TEXTURE4 0x84C4
#define GL_TEXTURE5 0x84C5
#define GL_TEXTURE6 0x84C6
#define GL_TEXTURE7 0x84C7
#define GL_TEXTURE8 0x84C8
#define GL_TEXTURE9 0x84C9
#define GL_TEXTURE_1D 0x0DE0
#define GL_TEXTURE_1D_ARRAY 0x8C18
#define GL_TEXTURE_2D 0x0DE1
#define GL_TEXTURE_2D_ARRAY 0x8C1A
#define GL_TEXTURE_2D_MULTISAMPLE 0x9100
#define GL_TEXTURE_2D_MULTISAMPLE_ARRAY 0x9102
#define GL_TEXTURE_3D 0x806F
#define GL_TEXTURE_ALPHA_SIZE 0x805F
#define GL_TEXTURE_ALPHA_TYPE 0x8C13
#define GL_TEXTURE_BASE_LEVEL 0x813C
#define GL_TEXTURE_BINDING_1D 0x8068
#define GL_TEXTURE_BINDING_1D_ARRAY 0x8C1C
#define GL_TEXTURE_BINDING_2D 0x8069
#define GL_TEXTURE_BINDING_2D_ARRAY 0x8C1D
#define GL_TEXTURE_BINDING_2D_MULTISAMPLE 0x9104
#define GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY 0x9105
#define GL_TEXTURE_BINDING_3D 0x806A
#define GL_TEXTURE_BINDING_BUFFER 0x8C2C
#define GL_TEXTURE_BINDING_CUBE_MAP 0x8514
#define GL_TEXTURE_BINDING_RECTANGLE 0x84F6
#define GL_TEXTURE_BIT 0x00040000
#define GL_TEXTURE_BLUE_SIZE 0x805E
#define GL_TEXTURE_BLUE_TYPE 0x8C12
#define GL_TEXTURE_BORDER 0x1005
#define GL_TEXTURE_BORDER_COLOR 0x1004
#define GL_TEXTURE_BUFFER 0x8C2A
#define GL_TEXTURE_BUFFER_DATA_STORE_BINDING 0x8C2D
#define GL_TEXTURE_COMPARE_FUNC 0x884D
#define GL_TEXTURE_COMPARE_MODE 0x884C
#define GL_TEXTURE_COMPONENTS 0x1003
#define GL_TEXTURE_COMPRESSED 0x86A1
#define GL_TEXTURE_COMPRESSED_IMAGE_SIZE 0x86A0
#define GL_TEXTURE_COMPRESSION_HINT 0x84EF
#define GL_TEXTURE_COORD_ARRAY 0x8078
#define GL_TEXTURE_COORD_ARRAY_BUFFER_BINDING 0x889A
#define GL_TEXTURE_COORD_ARRAY_POINTER 0x8092
#define GL_TEXTURE_COORD_ARRAY_SIZE 0x8088
#define GL_TEXTURE_COORD_ARRAY_STRIDE 0x808A
#define GL_TEXTURE_COORD_ARRAY_TYPE 0x8089
#define GL_TEXTURE_CUBE_MAP 0x8513
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_X 0x8516
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_Y 0x8518
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_Z 0x851A
#define GL_TEXTURE_CUBE_MAP_POSITIVE_X 0x8515
#define GL_TEXTURE_CUBE_MAP_POSITIVE_Y 0x8517
#define GL_TEXTURE_CUBE_MAP_POSITIVE_Z 0x8519
#define GL_TEXTURE_CUBE_MAP_SEAMLESS 0x884F
#define GL_TEXTURE_DEPTH 0x8071
#define GL_TEXTURE_DEPTH_SIZE 0x884A
#define GL_TEXTURE_DEPTH_TYPE 0x8C16
#define GL_TEXTURE_ENV 0x2300
#define GL_TEXTURE_ENV_COLOR 0x2201
#define GL_TEXTURE_ENV_MODE 0x2200
#define GL_TEXTURE_FILTER_CONTROL 0x8500
#define GL_TEXTURE_FIXED_SAMPLE_LOCATIONS 0x9107
#define GL_TEXTURE_GEN_MODE 0x2500
#define GL_TEXTURE_GEN_Q 0x0C63
#define GL_TEXTURE_GEN_R 0x0C62
#define GL_TEXTURE_GEN_S 0x0C60
#define GL_TEXTURE_GEN_T 0x0C61
#define GL_TEXTURE_GREEN_SIZE 0x805D
#define GL_TEXTURE_GREEN_TYPE 0x8C11
#define GL_TEXTURE_HEIGHT 0x1001
#define GL_TEXTURE_INTENSITY_SIZE 0x8061
#define GL_TEXTURE_INTENSITY_TYPE 0x8C15
#define GL_TEXTURE_INTERNAL_FORMAT 0x1003
#define GL_TEXTURE_LOD_BIAS 0x8501
#define GL_TEXTURE_LUMINANCE_SIZE 0x8060
#define GL_TEXTURE_LUMINANCE_TYPE 0x8C14
#define GL_TEXTURE_MAG_FILTER 0x2800
#define GL_TEXTURE_MATRIX 0x0BA8
#define GL_TEXTURE_MAX_LEVEL 0x813D
#define GL_TEXTURE_MAX_LOD 0x813B
#define GL_TEXTURE_MIN_FILTER 0x2801
#define GL_TEXTURE_MIN_LOD 0x813A
#define GL_TEXTURE_PRIORITY 0x8066
#define GL_TEXTURE_RECTANGLE 0x84F5
#define GL_TEXTURE_RED_SIZE 0x805C
#define GL_TEXTURE_RED_TYPE 0x8C10
#define GL_TEXTURE_RESIDENT 0x8067
#define GL_TEXTURE_SAMPLES 0x9106
#define GL_TEXTURE_SHARED_SIZE 0x8C3F
#define GL_TEXTURE_STACK_DEPTH 0x0BA5
#define GL_TEXTURE_STENCIL_SIZE 0x88F1
#define GL_TEXTURE_SWIZZLE_A 0x8E45
#define GL_TEXTURE_SWIZZLE_B 0x8E44
#define GL_TEXTURE_SWIZZLE_G 0x8E43
#define GL_TEXTURE_SWIZZLE_R 0x8E42
#define GL_TEXTURE_SWIZZLE_RGBA 0x8E46
#define GL_TEXTURE_WIDTH 0x1000
#define GL_TEXTURE_WRAP_R 0x8072
#define GL_TEXTURE_WRAP_S 0x2802
#define GL_TEXTURE_WRAP_T 0x2803
#define GL_TIMEOUT_EXPIRED 0x911B
#define GL_TIMEOUT_IGNORED 0xFFFFFFFFFFFFFFFF
#define GL_TIMESTAMP 0x8E28
#define GL_TIME_ELAPSED 0x88BF
#define GL_TRANSFORM_BIT 0x00001000
#define GL_TRANSFORM_FEEDBACK_BUFFER 0x8C8E
#define GL_TRANSFORM_FEEDBACK_BUFFER_BINDING 0x8C8F
#define GL_TRANSFORM_FEEDBACK_BUFFER_MODE 0x8C7F
#define GL_TRANSFORM_FEEDBACK_BUFFER_SIZE 0x8C85
#define GL_TRANSFORM_FEEDBACK_BUFFER_START 0x8C84
#define GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN 0x8C88
#define GL_TRANSFORM_FEEDBACK_VARYINGS 0x8C83
#define GL_TRANSFORM_FEEDBACK_VARYING_MAX_LENGTH 0x8C76
#define GL_TRANSPOSE_COLOR_MATRIX 0x84E6
#define GL_TRANSPOSE_MODELVIEW_MATRIX 0x84E3
#define GL_TRANSPOSE_PROJECTION_MATRIX 0x84E4
#define GL_TRANSPOSE_TEXTURE_MATRIX 0x84E5
#define GL_TRIANGLES 0x0004
#define GL_TRIANGLES_ADJACENCY 0x000C
#define GL_TRIANGLE_FAN 0x0006
#define GL_TRIANGLE_STRIP 0x0005
#define GL_TRIANGLE_STRIP_ADJACENCY 0x000D
#define GL_TRUE 1
#define GL_UNIFORM_ARRAY_STRIDE 0x8A3C
#define GL_UNIFORM_BLOCK_ACTIVE_UNIFORMS 0x8A42
#define GL_UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES 0x8A43
#define GL_UNIFORM_BLOCK_BINDING 0x8A3F
#define GL_UNIFORM_BLOCK_DATA_SIZE 0x8A40
#define GL_UNIFORM_BLOCK_INDEX 0x8A3A
#define GL_UNIFORM_BLOCK_NAME_LENGTH 0x8A41
#define GL_UNIFORM_BLOCK_REFERENCED_BY_FRAGMENT_SHADER 0x8A46
#define GL_UNIFORM_BLOCK_REFERENCED_BY_GEOMETRY_SHADER 0x8A45
#define GL_UNIFORM_BLOCK_REFERENCED_BY_VERTEX_SHADER 0x8A44
#define GL_UNIFORM_BUFFER 0x8A11
#define GL_UNIFORM_BUFFER_BINDING 0x8A28
#define GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT 0x8A34
#define GL_UNIFORM_BUFFER_SIZE 0x8A2A
#define GL_UNIFORM_BUFFER_START 0x8A29
#define GL_UNIFORM_IS_ROW_MAJOR 0x8A3E
#define GL_UNIFORM_MATRIX_STRIDE 0x8A3D
#define GL_UNIFORM_NAME_LENGTH 0x8A39
#define GL_UNIFORM_OFFSET 0x8A3B
#define GL_UNIFORM_SIZE 0x8A38
#define GL_UNIFORM_TYPE 0x8A37
#define GL_UNPACK_ALIGNMENT 0x0CF5
#define GL_UNPACK_IMAGE_HEIGHT 0x806E
#define GL_UNPACK_LSB_FIRST 0x0CF1
#define GL_UNPACK_ROW_LENGTH 0x0CF2
#define GL_UNPACK_SKIP_IMAGES 0x806D
#define GL_UNPACK_SKIP_PIXELS 0x0CF4
#define GL_UNPACK_SKIP_ROWS 0x0CF3
#define GL_UNPACK_SWAP_BYTES 0x0CF0
#define GL_UNSIGNALED 0x9118
#define GL_UNSIGNED_BYTE 0x1401
#define GL_UNSIGNED_BYTE_2_3_3_REV 0x8362
#define GL_UNSIGNED_BYTE_3_3_2 0x8032
#define GL_UNSIGNED_INT 0x1405
#define GL_UNSIGNED_INT_10F_11F_11F_REV 0x8C3B
#define GL_UNSIGNED_INT_10_10_10_2 0x8036
#define GL_UNSIGNED_INT_24_8 0x84FA
#define GL_UNSIGNED_INT_2_10_10_10_REV 0x8368
#define GL_UNSIGNED_INT_5_9_9_9_REV 0x8C3E
#define GL_UNSIGNED_INT_8_8_8_8 0x8035
#define GL_UNSIGNED_INT_8_8_8_8_REV 0x8367
#define GL_UNSIGNED_INT_SAMPLER_1D 0x8DD1
#define GL_UNSIGNED_INT_SAMPLER_1D_ARRAY 0x8DD6
#define GL_UNSIGNED_INT_SAMPLER_2D 0x8DD2
#define GL_UNSIGNED_INT_SAMPLER_2D_ARRAY 0x8DD7
#define GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE 0x910A
#define GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY 0x910D
#define GL_UNSIGNED_INT_SAMPLER_2D_RECT 0x8DD5
#define GL_UNSIGNED_INT_SAMPLER_3D 0x8DD3
#define GL_UNSIGNED_INT_SAMPLER_BUFFER 0x8DD8
#define GL_UNSIGNED_INT_SAMPLER_CUBE 0x8DD4
#define GL_UNSIGNED_INT_VEC2 0x8DC6
#define GL_UNSIGNED_INT_VEC3 0x8DC7
#define GL_UNSIGNED_INT_VEC4 0x8DC8
#define GL_UNSIGNED_NORMALIZED 0x8C17
#define GL_UNSIGNED_SHORT 0x1403
#define GL_UNSIGNED_SHORT_1_5_5_5_REV 0x8366
#define GL_UNSIGNED_SHORT_4_4_4_4 0x8033
#define GL_UNSIGNED_SHORT_4_4_4_4_REV 0x8365
#define GL_UNSIGNED_SHORT_5_5_5_1 0x8034
#define GL_UNSIGNED_SHORT_5_6_5 0x8363
#define GL_UNSIGNED_SHORT_5_6_5_REV 0x8364
#define GL_UPPER_LEFT 0x8CA2
#define GL_V2F 0x2A20
#define GL_V3F 0x2A21
#define GL_VALIDATE_STATUS 0x8B83
#define GL_VENDOR 0x1F00
#define GL_VERSION 0x1F02
#define GL_VERTEX_ARRAY 0x8074
#define GL_VERTEX_ARRAY_BINDING 0x85B5
#define GL_VERTEX_ARRAY_BUFFER_BINDING 0x8896
#define GL_VERTEX_ARRAY_POINTER 0x808E
#define GL_VERTEX_ARRAY_SIZE 0x807A
#define GL_VERTEX_ARRAY_STRIDE 0x807C
#define GL_VERTEX_ARRAY_TYPE 0x807B
#define GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING 0x889F
#define GL_VERTEX_ATTRIB_ARRAY_DIVISOR 0x88FE
#define GL_VERTEX_ATTRIB_ARRAY_ENABLED 0x8622
#define GL_VERTEX_ATTRIB_ARRAY_INTEGER 0x88FD
#define GL_VERTEX_ATTRIB_ARRAY_NORMALIZED 0x886A
#define GL_VERTEX_ATTRIB_ARRAY_POINTER 0x8645
#define GL_VERTEX_ATTRIB_ARRAY_SIZE 0x8623
#define GL_VERTEX_ATTRIB_ARRAY_STRIDE 0x8624
#define GL_VERTEX_ATTRIB_ARRAY_TYPE 0x8625
#define GL_VERTEX_PROGRAM_POINT_SIZE 0x8642
#define GL_VERTEX_PROGRAM_TWO_SIDE 0x8643
#define GL_VERTEX_SHADER 0x8B31
#define GL_VIEWPORT 0x0BA2
#define GL_VIEWPORT_BIT 0x00000800
#define GL_WAIT_FAILED 0x911D
#define GL_WEIGHT_ARRAY_BUFFER_BINDING 0x889E
#define GL_WRITE_ONLY 0x88B9
#define GL_XOR 0x1506
#define GL_ZERO 0
#define GL_ZOOM_X 0x0D16
#define GL_ZOOM_Y 0x0D17


#ifndef __khrplatform_h_
#define __khrplatform_h_

	/*
	** Copyright (c) 2008-2018 The Khronos Group Inc.
	**
	** Permission is hereby granted, free of charge, to any person obtaining a
	** copy of this software and/or associated documentation files (the
	** "Materials"), to deal in the Materials without restriction, including
	** without limitation the rights to use, copy, modify, merge, publish,
	** distribute, sublicense, and/or sell copies of the Materials, and to
	** permit persons to whom the Materials are furnished to do so, subject to
	** the following conditions:
	**
	** The above copyright notice and this permission notice shall be included
	** in all copies or substantial portions of the Materials.
	**
	** THE MATERIALS ARE PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
	** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
	** MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
	** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
	** CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
	** TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
	** MATERIALS OR THE USE OR OTHER DEALINGS IN THE MATERIALS.
	*/

	/* Khronos platform-specific types and definitions.
	 *
	 * The master copy of khrplatform.h is maintained in the Khronos EGL
	 * Registry repository at https://github.com/KhronosGroup/EGL-Registry
	 * The last semantic modification to khrplatform.h was at commit ID:
	 *      67a3e0864c2d75ea5287b9f3d2eb74a745936692
	 *
	 * Adopters may modify this file to suit their platform. Adopters are
	 * encouraged to submit platform specific modifications to the Khronos
	 * group so that they can be included in future versions of this file.
	 * Please submit changes by filing pull requests or issues on
	 * the EGL Registry repository linked above.
	 *
	 *
	 * See the Implementer's Guidelines for information about where this file
	 * should be located on your system and for more details of its use:
	 *    http://www.khronos.org/registry/implementers_guide.pdf
	 *
	 * This file should be included as
	 *        #include <KHR/khrplatform.h>
	 * by Khronos client API header files that use its types and defines.
	 *
	 * The types in khrplatform.h should only be used to define API-specific types.
	 *
	 * Types defined in khrplatform.h:
	 *    khronos_int8_t              signed   8  bit
	 *    khronos_uint8_t             unsigned 8  bit
	 *    khronos_int16_t             signed   16 bit
	 *    khronos_uint16_t            unsigned 16 bit
	 *    khronos_int32_t             signed   32 bit
	 *    khronos_uint32_t            unsigned 32 bit
	 *    khronos_int64_t             signed   64 bit
	 *    khronos_uint64_t            unsigned 64 bit
	 *    khronos_intptr_t            signed   same number of bits as a pointer
	 *    khronos_uintptr_t           unsigned same number of bits as a pointer
	 *    khronos_ssize_t             signed   size
	 *    khronos_usize_t             unsigned size
	 *    khronos_float_t             signed   32 bit floating point
	 *    khronos_time_ns_t           unsigned 64 bit time in nanoseconds
	 *    khronos_utime_nanoseconds_t unsigned time interval or absolute time in
	 *                                         nanoseconds
	 *    khronos_stime_nanoseconds_t signed time interval in nanoseconds
	 *    khronos_boolean_enum_t      enumerated boolean type. This should
	 *      only be used as a base type when a client API's boolean type is
	 *      an enum. Client APIs which use an integer or other type for
	 *      booleans cannot use this as the base type for their boolean.
	 *
	 * Tokens defined in khrplatform.h:
	 *
	 *    KHRONOS_FALSE, KHRONOS_TRUE Enumerated boolean false/true values.
	 *
	 *    KHRONOS_SUPPORT_INT64 is 1 if 64 bit integers are supported; otherwise 0.
	 *    KHRONOS_SUPPORT_FLOAT is 1 if floats are supported; otherwise 0.
	 *
	 * Calling convention macros defined in this file:
	 *    KHRONOS_APICALL
	 *    KHRONOS_GLAD_API_PTR
	 *    KHRONOS_APIATTRIBUTES
	 *
	 * These may be used in function prototypes as:
	 *
	 *      KHRONOS_APICALL void KHRONOS_GLAD_API_PTR funcname(
	 *                                  int arg1,
	 *                                  int arg2) KHRONOS_APIATTRIBUTES;
	 */

#if defined(__SCITECH_SNAP__) && !defined(KHRONOS_STATIC)
#   define KHRONOS_STATIC 1
#endif

	 /*-------------------------------------------------------------------------
	  * Definition of KHRONOS_APICALL
	  *-------------------------------------------------------------------------
	  * This precedes the return type of the function in the function prototype.
	  */
#if defined(KHRONOS_STATIC)
	  /* If the preprocessor constant KHRONOS_STATIC is defined, make the
	   * header compatible with static linking. */
#   define KHRONOS_APICALL
#elif defined(_WIN32)
#   define KHRONOS_APICALL __declspec(dllimport)
#elif defined (__SYMBIAN32__)
#   define KHRONOS_APICALL IMPORT_C
#elif defined(__ANDROID__)
#   define KHRONOS_APICALL __attribute__((visibility("default")))
#else
#   define KHRONOS_APICALL
#endif

	  /*-------------------------------------------------------------------------
	   * Definition of KHRONOS_GLAD_API_PTR
	   *-------------------------------------------------------------------------
	   * This follows the return type of the function  and precedes the function
	   * name in the function prototype.
	   */
#if defined(_WIN32) && !defined(_WIN32_WCE) && !defined(__SCITECH_SNAP__)
	   /* Win32 but not WinCE */
#   define KHRONOS_GLAD_API_PTR __stdcall
#else
#   define KHRONOS_GLAD_API_PTR
#endif

	   /*-------------------------------------------------------------------------
		* Definition of KHRONOS_APIATTRIBUTES
		*-------------------------------------------------------------------------
		* This follows the closing parenthesis of the function prototype arguments.
		*/
#if defined (__ARMCC_2__)
#define KHRONOS_APIATTRIBUTES __softfp
#else
#define KHRONOS_APIATTRIBUTES
#endif

		/*-------------------------------------------------------------------------
		 * basic type definitions
		 *-----------------------------------------------------------------------*/
#if (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L) || defined(__GNUC__) || defined(__SCO__) || defined(__USLC__)


		 /*
		  * Using <stdint.h>
		  */
#include <stdint.h>
	typedef int32_t                 khronos_int32_t;
	typedef uint32_t                khronos_uint32_t;
	typedef int64_t                 khronos_int64_t;
	typedef uint64_t                khronos_uint64_t;
#define KHRONOS_SUPPORT_INT64   1
#define KHRONOS_SUPPORT_FLOAT   1
	/*
	 * To support platform where unsigned long cannot be used interchangeably with
	 * inptr_t (e.g. CHERI-extended ISAs), we can use the stdint.h intptr_t.
	 * Ideally, we could just use (u)intptr_t everywhere, but this could result in
	 * ABI breakage if khronos_uintptr_t is changed from unsigned long to
	 * unsigned long long or similar (this results in different C++ name mangling).
	 * To avoid changes for existing platforms, we restrict usage of intptr_t to
	 * platforms where the size of a pointer is larger than the size of long.
	 */
#if defined(__SIZEOF_LONG__) && defined(__SIZEOF_POINTER__)
#if __SIZEOF_POINTER__ > __SIZEOF_LONG__
#define KHRONOS_USE_INTPTR_T
#endif
#endif

#elif defined(__VMS ) || defined(__sgi)

		 /*
		  * Using <inttypes.h>
		  */
#include <inttypes.h>
	typedef int32_t                 khronos_int32_t;
	typedef uint32_t                khronos_uint32_t;
	typedef int64_t                 khronos_int64_t;
	typedef uint64_t                khronos_uint64_t;
#define KHRONOS_SUPPORT_INT64   1
#define KHRONOS_SUPPORT_FLOAT   1

#elif defined(_WIN32) && !defined(__SCITECH_SNAP__)

		 /*
		  * Win32
		  */
	typedef __int32                 khronos_int32_t;
	typedef unsigned __int32        khronos_uint32_t;
	typedef __int64                 khronos_int64_t;
	typedef unsigned __int64        khronos_uint64_t;
#define KHRONOS_SUPPORT_INT64   1
#define KHRONOS_SUPPORT_FLOAT   1

#elif defined(__sun__) || defined(__digital__)

		 /*
		  * Sun or Digital
		  */
	typedef int                     khronos_int32_t;
	typedef unsigned int            khronos_uint32_t;
#if defined(__arch64__) || defined(_LP64)
	typedef long int                khronos_int64_t;
	typedef unsigned long int       khronos_uint64_t;
#else
	typedef long long int           khronos_int64_t;
	typedef unsigned long long int  khronos_uint64_t;
#endif /* __arch64__ */
#define KHRONOS_SUPPORT_INT64   1
#define KHRONOS_SUPPORT_FLOAT   1

#elif 0

		 /*
		  * Hypothetical platform with no float or int64 support
		  */
	typedef int                     khronos_int32_t;
	typedef unsigned int            khronos_uint32_t;
#define KHRONOS_SUPPORT_INT64   0
#define KHRONOS_SUPPORT_FLOAT   0

#else

		 /*
		  * Generic fallback
		  */
#include <stdint.h>
	typedef int32_t                 khronos_int32_t;
	typedef uint32_t                khronos_uint32_t;
	typedef int64_t                 khronos_int64_t;
	typedef uint64_t                khronos_uint64_t;
#define KHRONOS_SUPPORT_INT64   1
#define KHRONOS_SUPPORT_FLOAT   1

#endif


	/*
	 * Types that are (so far) the same on all platforms
	 */
	typedef signed   char          khronos_int8_t;
	typedef unsigned char          khronos_uint8_t;
	typedef signed   short int     khronos_int16_t;
	typedef unsigned short int     khronos_uint16_t;

	/*
	 * Types that differ between LLP64 and LP64 architectures - in LLP64,
	 * pointers are 64 bits, but 'long' is still 32 bits. Win64 appears
	 * to be the only LLP64 architecture in current use.
	 */
#ifdef KHRONOS_USE_INTPTR_T
	typedef intptr_t               khronos_intptr_t;
	typedef uintptr_t              khronos_uintptr_t;
#elif defined(_WIN64)
	typedef signed   long long int khronos_intptr_t;
	typedef unsigned long long int khronos_uintptr_t;
#else
	typedef signed   long  int     khronos_intptr_t;
	typedef unsigned long  int     khronos_uintptr_t;
#endif

#if defined(_WIN64)
	typedef signed   long long int khronos_ssize_t;
	typedef unsigned long long int khronos_usize_t;
#else
	typedef signed   long  int     khronos_ssize_t;
	typedef unsigned long  int     khronos_usize_t;
#endif

#if KHRONOS_SUPPORT_FLOAT
	/*
	 * Float type
	 */
	typedef          float         khronos_float_t;
#endif

#if KHRONOS_SUPPORT_INT64
	/* Time types
	 *
	 * These types can be used to represent a time interval in nanoseconds or
	 * an absolute Unadjusted System Time.  Unadjusted System Time is the number
	 * of nanoseconds since some arbitrary system event (e.g. since the last
	 * time the system booted).  The Unadjusted System Time is an unsigned
	 * 64 bit value that wraps back to 0 every 584 years.  Time intervals
	 * may be either signed or unsigned.
	 */
	typedef khronos_uint64_t       khronos_utime_nanoseconds_t;
	typedef khronos_int64_t        khronos_stime_nanoseconds_t;
#endif

	/*
	 * Dummy value used to pad enum types to 32 bits.
	 */
#ifndef KHRONOS_MAX_ENUM
#define KHRONOS_MAX_ENUM 0x7FFFFFFF
#endif

	 /*
	  * Enumerated boolean type
	  *
	  * Values other than zero should be considered to be true.  Therefore
	  * comparisons should not be made against KHRONOS_TRUE.
	  */
	typedef enum {
		KHRONOS_FALSE = 0,
		KHRONOS_TRUE = 1,
		KHRONOS_BOOLEAN_ENUM_FORCE_SIZE = KHRONOS_MAX_ENUM
	} khronos_boolean_enum_t;

#endif /* __khrplatform_h_ */
	typedef unsigned int GLenum;
	typedef unsigned char GLboolean;
	typedef unsigned int GLbitfield;
	typedef void GLvoid;
	typedef khronos_int8_t GLbyte;
	typedef khronos_uint8_t GLubyte;
	typedef khronos_int16_t GLshort;
	typedef khronos_uint16_t GLushort;
	typedef int GLint;
	typedef unsigned int GLuint;
	typedef khronos_int32_t GLclampx;
	typedef int GLsizei;
	typedef khronos_float_t GLfloat;
	typedef khronos_float_t GLclampf;
	typedef double GLdouble;
	typedef double GLclampd;
	typedef void* GLeglClientBufferEXT;
	typedef void* GLeglImageOES;
	typedef char GLchar;
	typedef char GLcharARB;
#ifdef __APPLE__
	typedef void* GLhandleARB;
#else
	typedef unsigned int GLhandleARB;
#endif
	typedef khronos_uint16_t GLhalf;
	typedef khronos_uint16_t GLhalfARB;
	typedef khronos_int32_t GLfixed;
#if defined(__ENVIRONMENT_MAC_OS_X_VERSION_MIN_REQUIRED__) && (__ENVIRONMENT_MAC_OS_X_VERSION_MIN_REQUIRED__ > 1060)
	typedef khronos_intptr_t GLintptr;
#else
	typedef khronos_intptr_t GLintptr;
#endif
#if defined(__ENVIRONMENT_MAC_OS_X_VERSION_MIN_REQUIRED__) && (__ENVIRONMENT_MAC_OS_X_VERSION_MIN_REQUIRED__ > 1060)
	typedef khronos_intptr_t GLintptrARB;
#else
	typedef khronos_intptr_t GLintptrARB;
#endif
#if defined(__ENVIRONMENT_MAC_OS_X_VERSION_MIN_REQUIRED__) && (__ENVIRONMENT_MAC_OS_X_VERSION_MIN_REQUIRED__ > 1060)
	typedef khronos_ssize_t GLsizeiptr;
#else
	typedef khronos_ssize_t GLsizeiptr;
#endif
#if defined(__ENVIRONMENT_MAC_OS_X_VERSION_MIN_REQUIRED__) && (__ENVIRONMENT_MAC_OS_X_VERSION_MIN_REQUIRED__ > 1060)
	typedef khronos_ssize_t GLsizeiptrARB;
#else
	typedef khronos_ssize_t GLsizeiptrARB;
#endif
	typedef khronos_int64_t GLint64;
	typedef khronos_int64_t GLint64EXT;
	typedef khronos_uint64_t GLuint64;
	typedef khronos_uint64_t GLuint64EXT;
	typedef struct __GLsync* GLsync;
	struct _cl_context;
	struct _cl_event;
	typedef void (GLAD_API_PTR* GLDEBUGPROC)(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);
	typedef void (GLAD_API_PTR* GLDEBUGPROCARB)(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);
	typedef void (GLAD_API_PTR* GLDEBUGPROCKHR)(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);
	typedef void (GLAD_API_PTR* GLDEBUGPROCAMD)(GLuint id, GLenum category, GLenum severity, GLsizei length, const GLchar* message, void* userParam);
	typedef unsigned short GLhalfNV;
	typedef GLintptr GLvdpauSurfaceNV;
	typedef void (GLAD_API_PTR* GLVULKANPROCNV)(void);


#define GL_VERSION_1_0 1
	GLAD_API_CALL int GLAD_GL_VERSION_1_0;
#define GL_VERSION_1_1 1
	GLAD_API_CALL int GLAD_GL_VERSION_1_1;
#define GL_VERSION_1_2 1
	GLAD_API_CALL int GLAD_GL_VERSION_1_2;
#define GL_VERSION_1_3 1
	GLAD_API_CALL int GLAD_GL_VERSION_1_3;
#define GL_VERSION_1_4 1
	GLAD_API_CALL int GLAD_GL_VERSION_1_4;
#define GL_VERSION_1_5 1
	GLAD_API_CALL int GLAD_GL_VERSION_1_5;
#define GL_VERSION_2_0 1
	GLAD_API_CALL int GLAD_GL_VERSION_2_0;
#define GL_VERSION_2_1 1
	GLAD_API_CALL int GLAD_GL_VERSION_2_1;
#define GL_VERSION_3_0 1
	GLAD_API_CALL int GLAD_GL_VERSION_3_0;
#define GL_VERSION_3_1 1
	GLAD_API_CALL int GLAD_GL_VERSION_3_1;
#define GL_VERSION_3_2 1
	GLAD_API_CALL int GLAD_GL_VERSION_3_2;
#define GL_VERSION_3_3 1
	GLAD_API_CALL int GLAD_GL_VERSION_3_3;


	typedef void (GLAD_API_PTR* PFNGLACCUMPROC)(GLenum op, GLfloat value);
	typedef void (GLAD_API_PTR* PFNGLACTIVETEXTUREPROC)(GLenum texture);
	typedef void (GLAD_API_PTR* PFNGLALPHAFUNCPROC)(GLenum func, GLfloat ref);
	typedef GLboolean(GLAD_API_PTR* PFNGLARETEXTURESRESIDENTPROC)(GLsizei n, const GLuint* textures, GLboolean* residences);
	typedef void (GLAD_API_PTR* PFNGLARRAYELEMENTPROC)(GLint i);
	typedef void (GLAD_API_PTR* PFNGLATTACHSHADERPROC)(GLuint program, GLuint shader);
	typedef void (GLAD_API_PTR* PFNGLBEGINPROC)(GLenum mode);
	typedef void (GLAD_API_PTR* PFNGLBEGINCONDITIONALRENDERPROC)(GLuint id, GLenum mode);
	typedef void (GLAD_API_PTR* PFNGLBEGINQUERYPROC)(GLenum target, GLuint id);
	typedef void (GLAD_API_PTR* PFNGLBEGINTRANSFORMFEEDBACKPROC)(GLenum primitiveMode);
	typedef void (GLAD_API_PTR* PFNGLBINDATTRIBLOCATIONPROC)(GLuint program, GLuint index, const GLchar* name);
	typedef void (GLAD_API_PTR* PFNGLBINDBUFFERPROC)(GLenum target, GLuint buffer);
	typedef void (GLAD_API_PTR* PFNGLBINDBUFFERBASEPROC)(GLenum target, GLuint index, GLuint buffer);
	typedef void (GLAD_API_PTR* PFNGLBINDBUFFERRANGEPROC)(GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size);
	typedef void (GLAD_API_PTR* PFNGLBINDFRAGDATALOCATIONPROC)(GLuint program, GLuint color, const GLchar* name);
	typedef void (GLAD_API_PTR* PFNGLBINDFRAGDATALOCATIONINDEXEDPROC)(GLuint program, GLuint colorNumber, GLuint index, const GLchar* name);
	typedef void (GLAD_API_PTR* PFNGLBINDFRAMEBUFFERPROC)(GLenum target, GLuint framebuffer);
	typedef void (GLAD_API_PTR* PFNGLBINDRENDERBUFFERPROC)(GLenum target, GLuint renderbuffer);
	typedef void (GLAD_API_PTR* PFNGLBINDSAMPLERPROC)(GLuint unit, GLuint sampler);
	typedef void (GLAD_API_PTR* PFNGLBINDTEXTUREPROC)(GLenum target, GLuint texture);
	typedef void (GLAD_API_PTR* PFNGLBINDVERTEXARRAYPROC)(GLuint array);
	typedef void (GLAD_API_PTR* PFNGLBITMAPPROC)(GLsizei width, GLsizei height, GLfloat xorig, GLfloat yorig, GLfloat xmove, GLfloat ymove, const GLubyte* bitmap);
	typedef void (GLAD_API_PTR* PFNGLBLENDCOLORPROC)(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
	typedef void (GLAD_API_PTR* PFNGLBLENDEQUATIONPROC)(GLenum mode);
	typedef void (GLAD_API_PTR* PFNGLBLENDEQUATIONSEPARATEPROC)(GLenum modeRGB, GLenum modeAlpha);
	typedef void (GLAD_API_PTR* PFNGLBLENDFUNCPROC)(GLenum sfactor, GLenum dfactor);
	typedef void (GLAD_API_PTR* PFNGLBLENDFUNCSEPARATEPROC)(GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha);
	typedef void (GLAD_API_PTR* PFNGLBLITFRAMEBUFFERPROC)(GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter);
	typedef void (GLAD_API_PTR* PFNGLBUFFERDATAPROC)(GLenum target, GLsizeiptr size, const void* data, GLenum usage);
	typedef void (GLAD_API_PTR* PFNGLBUFFERSUBDATAPROC)(GLenum target, GLintptr offset, GLsizeiptr size, const void* data);
	typedef void (GLAD_API_PTR* PFNGLCALLLISTPROC)(GLuint list);
	typedef void (GLAD_API_PTR* PFNGLCALLLISTSPROC)(GLsizei n, GLenum type, const void* lists);
	typedef GLenum(GLAD_API_PTR* PFNGLCHECKFRAMEBUFFERSTATUSPROC)(GLenum target);
	typedef void (GLAD_API_PTR* PFNGLCLAMPCOLORPROC)(GLenum target, GLenum clamp);
	typedef void (GLAD_API_PTR* PFNGLCLEARPROC)(GLbitfield mask);
	typedef void (GLAD_API_PTR* PFNGLCLEARACCUMPROC)(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
	typedef void (GLAD_API_PTR* PFNGLCLEARBUFFERFIPROC)(GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil);
	typedef void (GLAD_API_PTR* PFNGLCLEARBUFFERFVPROC)(GLenum buffer, GLint drawbuffer, const GLfloat* value);
	typedef void (GLAD_API_PTR* PFNGLCLEARBUFFERIVPROC)(GLenum buffer, GLint drawbuffer, const GLint* value);
	typedef void (GLAD_API_PTR* PFNGLCLEARBUFFERUIVPROC)(GLenum buffer, GLint drawbuffer, const GLuint* value);
	typedef void (GLAD_API_PTR* PFNGLCLEARCOLORPROC)(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
	typedef void (GLAD_API_PTR* PFNGLCLEARDEPTHPROC)(GLdouble depth);
	typedef void (GLAD_API_PTR* PFNGLCLEARINDEXPROC)(GLfloat c);
	typedef void (GLAD_API_PTR* PFNGLCLEARSTENCILPROC)(GLint s);
	typedef void (GLAD_API_PTR* PFNGLCLIENTACTIVETEXTUREPROC)(GLenum texture);
	typedef GLenum(GLAD_API_PTR* PFNGLCLIENTWAITSYNCPROC)(GLsync sync, GLbitfield flags, GLuint64 timeout);
	typedef void (GLAD_API_PTR* PFNGLCLIPPLANEPROC)(GLenum plane, const GLdouble* equation);
	typedef void (GLAD_API_PTR* PFNGLCOLOR3BPROC)(GLbyte red, GLbyte green, GLbyte blue);
	typedef void (GLAD_API_PTR* PFNGLCOLOR3BVPROC)(const GLbyte* v);
	typedef void (GLAD_API_PTR* PFNGLCOLOR3DPROC)(GLdouble red, GLdouble green, GLdouble blue);
	typedef void (GLAD_API_PTR* PFNGLCOLOR3DVPROC)(const GLdouble* v);
	typedef void (GLAD_API_PTR* PFNGLCOLOR3FPROC)(GLfloat red, GLfloat green, GLfloat blue);
	typedef void (GLAD_API_PTR* PFNGLCOLOR3FVPROC)(const GLfloat* v);
	typedef void (GLAD_API_PTR* PFNGLCOLOR3IPROC)(GLint red, GLint green, GLint blue);
	typedef void (GLAD_API_PTR* PFNGLCOLOR3IVPROC)(const GLint* v);
	typedef void (GLAD_API_PTR* PFNGLCOLOR3SPROC)(GLshort red, GLshort green, GLshort blue);
	typedef void (GLAD_API_PTR* PFNGLCOLOR3SVPROC)(const GLshort* v);
	typedef void (GLAD_API_PTR* PFNGLCOLOR3UBPROC)(GLubyte red, GLubyte green, GLubyte blue);
	typedef void (GLAD_API_PTR* PFNGLCOLOR3UBVPROC)(const GLubyte* v);
	typedef void (GLAD_API_PTR* PFNGLCOLOR3UIPROC)(GLuint red, GLuint green, GLuint blue);
	typedef void (GLAD_API_PTR* PFNGLCOLOR3UIVPROC)(const GLuint* v);
	typedef void (GLAD_API_PTR* PFNGLCOLOR3USPROC)(GLushort red, GLushort green, GLushort blue);
	typedef void (GLAD_API_PTR* PFNGLCOLOR3USVPROC)(const GLushort* v);
	typedef void (GLAD_API_PTR* PFNGLCOLOR4BPROC)(GLbyte red, GLbyte green, GLbyte blue, GLbyte alpha);
	typedef void (GLAD_API_PTR* PFNGLCOLOR4BVPROC)(const GLbyte* v);
	typedef void (GLAD_API_PTR* PFNGLCOLOR4DPROC)(GLdouble red, GLdouble green, GLdouble blue, GLdouble alpha);
	typedef void (GLAD_API_PTR* PFNGLCOLOR4DVPROC)(const GLdouble* v);
	typedef void (GLAD_API_PTR* PFNGLCOLOR4FPROC)(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
	typedef void (GLAD_API_PTR* PFNGLCOLOR4FVPROC)(const GLfloat* v);
	typedef void (GLAD_API_PTR* PFNGLCOLOR4IPROC)(GLint red, GLint green, GLint blue, GLint alpha);
	typedef void (GLAD_API_PTR* PFNGLCOLOR4IVPROC)(const GLint* v);
	typedef void (GLAD_API_PTR* PFNGLCOLOR4SPROC)(GLshort red, GLshort green, GLshort blue, GLshort alpha);
	typedef void (GLAD_API_PTR* PFNGLCOLOR4SVPROC)(const GLshort* v);
	typedef void (GLAD_API_PTR* PFNGLCOLOR4UBPROC)(GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha);
	typedef void (GLAD_API_PTR* PFNGLCOLOR4UBVPROC)(const GLubyte* v);
	typedef void (GLAD_API_PTR* PFNGLCOLOR4UIPROC)(GLuint red, GLuint green, GLuint blue, GLuint alpha);
	typedef void (GLAD_API_PTR* PFNGLCOLOR4UIVPROC)(const GLuint* v);
	typedef void (GLAD_API_PTR* PFNGLCOLOR4USPROC)(GLushort red, GLushort green, GLushort blue, GLushort alpha);
	typedef void (GLAD_API_PTR* PFNGLCOLOR4USVPROC)(const GLushort* v);
	typedef void (GLAD_API_PTR* PFNGLCOLORMASKPROC)(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
	typedef void (GLAD_API_PTR* PFNGLCOLORMASKIPROC)(GLuint index, GLboolean r, GLboolean g, GLboolean b, GLboolean a);
	typedef void (GLAD_API_PTR* PFNGLCOLORMATERIALPROC)(GLenum face, GLenum mode);
	typedef void (GLAD_API_PTR* PFNGLCOLORP3UIPROC)(GLenum type, GLuint color);
	typedef void (GLAD_API_PTR* PFNGLCOLORP3UIVPROC)(GLenum type, const GLuint* color);
	typedef void (GLAD_API_PTR* PFNGLCOLORP4UIPROC)(GLenum type, GLuint color);
	typedef void (GLAD_API_PTR* PFNGLCOLORP4UIVPROC)(GLenum type, const GLuint* color);
	typedef void (GLAD_API_PTR* PFNGLCOLORPOINTERPROC)(GLint size, GLenum type, GLsizei stride, const void* pointer);
	typedef void (GLAD_API_PTR* PFNGLCOMPILESHADERPROC)(GLuint shader);
	typedef void (GLAD_API_PTR* PFNGLCOMPRESSEDTEXIMAGE1DPROC)(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const void* data);
	typedef void (GLAD_API_PTR* PFNGLCOMPRESSEDTEXIMAGE2DPROC)(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void* data);
	typedef void (GLAD_API_PTR* PFNGLCOMPRESSEDTEXIMAGE3DPROC)(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const void* data);
	typedef void (GLAD_API_PTR* PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC)(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const void* data);
	typedef void (GLAD_API_PTR* PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void* data);
	typedef void (GLAD_API_PTR* PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void* data);
	typedef void (GLAD_API_PTR* PFNGLCOPYBUFFERSUBDATAPROC)(GLenum readTarget, GLenum writeTarget, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size);
	typedef void (GLAD_API_PTR* PFNGLCOPYPIXELSPROC)(GLint x, GLint y, GLsizei width, GLsizei height, GLenum type);
	typedef void (GLAD_API_PTR* PFNGLCOPYTEXIMAGE1DPROC)(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLint border);
	typedef void (GLAD_API_PTR* PFNGLCOPYTEXIMAGE2DPROC)(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border);
	typedef void (GLAD_API_PTR* PFNGLCOPYTEXSUBIMAGE1DPROC)(GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width);
	typedef void (GLAD_API_PTR* PFNGLCOPYTEXSUBIMAGE2DPROC)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height);
	typedef void (GLAD_API_PTR* PFNGLCOPYTEXSUBIMAGE3DPROC)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height);
	typedef GLuint(GLAD_API_PTR* PFNGLCREATEPROGRAMPROC)(void);
	typedef GLuint(GLAD_API_PTR* PFNGLCREATESHADERPROC)(GLenum type);
	typedef void (GLAD_API_PTR* PFNGLCULLFACEPROC)(GLenum mode);
	typedef void (GLAD_API_PTR* PFNGLDELETEBUFFERSPROC)(GLsizei n, const GLuint* buffers);
	typedef void (GLAD_API_PTR* PFNGLDELETEFRAMEBUFFERSPROC)(GLsizei n, const GLuint* framebuffers);
	typedef void (GLAD_API_PTR* PFNGLDELETELISTSPROC)(GLuint list, GLsizei range);
	typedef void (GLAD_API_PTR* PFNGLDELETEPROGRAMPROC)(GLuint program);
	typedef void (GLAD_API_PTR* PFNGLDELETEQUERIESPROC)(GLsizei n, const GLuint* ids);
	typedef void (GLAD_API_PTR* PFNGLDELETERENDERBUFFERSPROC)(GLsizei n, const GLuint* renderbuffers);
	typedef void (GLAD_API_PTR* PFNGLDELETESAMPLERSPROC)(GLsizei count, const GLuint* samplers);
	typedef void (GLAD_API_PTR* PFNGLDELETESHADERPROC)(GLuint shader);
	typedef void (GLAD_API_PTR* PFNGLDELETESYNCPROC)(GLsync sync);
	typedef void (GLAD_API_PTR* PFNGLDELETETEXTURESPROC)(GLsizei n, const GLuint* textures);
	typedef void (GLAD_API_PTR* PFNGLDELETEVERTEXARRAYSPROC)(GLsizei n, const GLuint* arrays);
	typedef void (GLAD_API_PTR* PFNGLDEPTHFUNCPROC)(GLenum func);
	typedef void (GLAD_API_PTR* PFNGLDEPTHMASKPROC)(GLboolean flag);
	typedef void (GLAD_API_PTR* PFNGLDEPTHRANGEPROC)(GLdouble n, GLdouble f);
	typedef void (GLAD_API_PTR* PFNGLDETACHSHADERPROC)(GLuint program, GLuint shader);
	typedef void (GLAD_API_PTR* PFNGLDISABLEPROC)(GLenum cap);
	typedef void (GLAD_API_PTR* PFNGLDISABLECLIENTSTATEPROC)(GLenum array);
	typedef void (GLAD_API_PTR* PFNGLDISABLEVERTEXATTRIBARRAYPROC)(GLuint index);
	typedef void (GLAD_API_PTR* PFNGLDISABLEIPROC)(GLenum target, GLuint index);
	typedef void (GLAD_API_PTR* PFNGLDRAWARRAYSPROC)(GLenum mode, GLint first, GLsizei count);
	typedef void (GLAD_API_PTR* PFNGLDRAWARRAYSINSTANCEDPROC)(GLenum mode, GLint first, GLsizei count, GLsizei instancecount);
	typedef void (GLAD_API_PTR* PFNGLDRAWBUFFERPROC)(GLenum buf);
	typedef void (GLAD_API_PTR* PFNGLDRAWBUFFERSPROC)(GLsizei n, const GLenum* bufs);
	typedef void (GLAD_API_PTR* PFNGLDRAWELEMENTSPROC)(GLenum mode, GLsizei count, GLenum type, const void* indices);
	typedef void (GLAD_API_PTR* PFNGLDRAWELEMENTSBASEVERTEXPROC)(GLenum mode, GLsizei count, GLenum type, const void* indices, GLint basevertex);
	typedef void (GLAD_API_PTR* PFNGLDRAWELEMENTSINSTANCEDPROC)(GLenum mode, GLsizei count, GLenum type, const void* indices, GLsizei instancecount);
	typedef void (GLAD_API_PTR* PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXPROC)(GLenum mode, GLsizei count, GLenum type, const void* indices, GLsizei instancecount, GLint basevertex);
	typedef void (GLAD_API_PTR* PFNGLDRAWPIXELSPROC)(GLsizei width, GLsizei height, GLenum format, GLenum type, const void* pixels);
	typedef void (GLAD_API_PTR* PFNGLDRAWRANGEELEMENTSPROC)(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const void* indices);
	typedef void (GLAD_API_PTR* PFNGLDRAWRANGEELEMENTSBASEVERTEXPROC)(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const void* indices, GLint basevertex);
	typedef void (GLAD_API_PTR* PFNGLEDGEFLAGPROC)(GLboolean flag);
	typedef void (GLAD_API_PTR* PFNGLEDGEFLAGPOINTERPROC)(GLsizei stride, const void* pointer);
	typedef void (GLAD_API_PTR* PFNGLEDGEFLAGVPROC)(const GLboolean* flag);
	typedef void (GLAD_API_PTR* PFNGLENABLEPROC)(GLenum cap);
	typedef void (GLAD_API_PTR* PFNGLENABLECLIENTSTATEPROC)(GLenum array);
	typedef void (GLAD_API_PTR* PFNGLENABLEVERTEXATTRIBARRAYPROC)(GLuint index);
	typedef void (GLAD_API_PTR* PFNGLENABLEIPROC)(GLenum target, GLuint index);
	typedef void (GLAD_API_PTR* PFNGLENDPROC)(void);
	typedef void (GLAD_API_PTR* PFNGLENDCONDITIONALRENDERPROC)(void);
	typedef void (GLAD_API_PTR* PFNGLENDLISTPROC)(void);
	typedef void (GLAD_API_PTR* PFNGLENDQUERYPROC)(GLenum target);
	typedef void (GLAD_API_PTR* PFNGLENDTRANSFORMFEEDBACKPROC)(void);
	typedef void (GLAD_API_PTR* PFNGLEVALCOORD1DPROC)(GLdouble u);
	typedef void (GLAD_API_PTR* PFNGLEVALCOORD1DVPROC)(const GLdouble* u);
	typedef void (GLAD_API_PTR* PFNGLEVALCOORD1FPROC)(GLfloat u);
	typedef void (GLAD_API_PTR* PFNGLEVALCOORD1FVPROC)(const GLfloat* u);
	typedef void (GLAD_API_PTR* PFNGLEVALCOORD2DPROC)(GLdouble u, GLdouble v);
	typedef void (GLAD_API_PTR* PFNGLEVALCOORD2DVPROC)(const GLdouble* u);
	typedef void (GLAD_API_PTR* PFNGLEVALCOORD2FPROC)(GLfloat u, GLfloat v);
	typedef void (GLAD_API_PTR* PFNGLEVALCOORD2FVPROC)(const GLfloat* u);
	typedef void (GLAD_API_PTR* PFNGLEVALMESH1PROC)(GLenum mode, GLint i1, GLint i2);
	typedef void (GLAD_API_PTR* PFNGLEVALMESH2PROC)(GLenum mode, GLint i1, GLint i2, GLint j1, GLint j2);
	typedef void (GLAD_API_PTR* PFNGLEVALPOINT1PROC)(GLint i);
	typedef void (GLAD_API_PTR* PFNGLEVALPOINT2PROC)(GLint i, GLint j);
	typedef void (GLAD_API_PTR* PFNGLFEEDBACKBUFFERPROC)(GLsizei size, GLenum type, GLfloat* buffer);
	typedef GLsync(GLAD_API_PTR* PFNGLFENCESYNCPROC)(GLenum condition, GLbitfield flags);
	typedef void (GLAD_API_PTR* PFNGLFINISHPROC)(void);
	typedef void (GLAD_API_PTR* PFNGLFLUSHPROC)(void);
	typedef void (GLAD_API_PTR* PFNGLFLUSHMAPPEDBUFFERRANGEPROC)(GLenum target, GLintptr offset, GLsizeiptr length);
	typedef void (GLAD_API_PTR* PFNGLFOGCOORDPOINTERPROC)(GLenum type, GLsizei stride, const void* pointer);
	typedef void (GLAD_API_PTR* PFNGLFOGCOORDDPROC)(GLdouble coord);
	typedef void (GLAD_API_PTR* PFNGLFOGCOORDDVPROC)(const GLdouble* coord);
	typedef void (GLAD_API_PTR* PFNGLFOGCOORDFPROC)(GLfloat coord);
	typedef void (GLAD_API_PTR* PFNGLFOGCOORDFVPROC)(const GLfloat* coord);
	typedef void (GLAD_API_PTR* PFNGLFOGFPROC)(GLenum pname, GLfloat param);
	typedef void (GLAD_API_PTR* PFNGLFOGFVPROC)(GLenum pname, const GLfloat* params);
	typedef void (GLAD_API_PTR* PFNGLFOGIPROC)(GLenum pname, GLint param);
	typedef void (GLAD_API_PTR* PFNGLFOGIVPROC)(GLenum pname, const GLint* params);
	typedef void (GLAD_API_PTR* PFNGLFRAMEBUFFERRENDERBUFFERPROC)(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
	typedef void (GLAD_API_PTR* PFNGLFRAMEBUFFERTEXTUREPROC)(GLenum target, GLenum attachment, GLuint texture, GLint level);
	typedef void (GLAD_API_PTR* PFNGLFRAMEBUFFERTEXTURE1DPROC)(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
	typedef void (GLAD_API_PTR* PFNGLFRAMEBUFFERTEXTURE2DPROC)(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
	typedef void (GLAD_API_PTR* PFNGLFRAMEBUFFERTEXTURE3DPROC)(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset);
	typedef void (GLAD_API_PTR* PFNGLFRAMEBUFFERTEXTURELAYERPROC)(GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer);
	typedef void (GLAD_API_PTR* PFNGLFRONTFACEPROC)(GLenum mode);
	typedef void (GLAD_API_PTR* PFNGLFRUSTUMPROC)(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar);
	typedef void (GLAD_API_PTR* PFNGLGENBUFFERSPROC)(GLsizei n, GLuint* buffers);
	typedef void (GLAD_API_PTR* PFNGLGENFRAMEBUFFERSPROC)(GLsizei n, GLuint* framebuffers);
	typedef GLuint(GLAD_API_PTR* PFNGLGENLISTSPROC)(GLsizei range);
	typedef void (GLAD_API_PTR* PFNGLGENQUERIESPROC)(GLsizei n, GLuint* ids);
	typedef void (GLAD_API_PTR* PFNGLGENRENDERBUFFERSPROC)(GLsizei n, GLuint* renderbuffers);
	typedef void (GLAD_API_PTR* PFNGLGENSAMPLERSPROC)(GLsizei count, GLuint* samplers);
	typedef void (GLAD_API_PTR* PFNGLGENTEXTURESPROC)(GLsizei n, GLuint* textures);
	typedef void (GLAD_API_PTR* PFNGLGENVERTEXARRAYSPROC)(GLsizei n, GLuint* arrays);
	typedef void (GLAD_API_PTR* PFNGLGENERATEMIPMAPPROC)(GLenum target);
	typedef void (GLAD_API_PTR* PFNGLGETACTIVEATTRIBPROC)(GLuint program, GLuint index, GLsizei bufSize, GLsizei* length, GLint* size, GLenum* type, GLchar* name);
	typedef void (GLAD_API_PTR* PFNGLGETACTIVEUNIFORMPROC)(GLuint program, GLuint index, GLsizei bufSize, GLsizei* length, GLint* size, GLenum* type, GLchar* name);
	typedef void (GLAD_API_PTR* PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC)(GLuint program, GLuint uniformBlockIndex, GLsizei bufSize, GLsizei* length, GLchar* uniformBlockName);
	typedef void (GLAD_API_PTR* PFNGLGETACTIVEUNIFORMBLOCKIVPROC)(GLuint program, GLuint uniformBlockIndex, GLenum pname, GLint* params);
	typedef void (GLAD_API_PTR* PFNGLGETACTIVEUNIFORMNAMEPROC)(GLuint program, GLuint uniformIndex, GLsizei bufSize, GLsizei* length, GLchar* uniformName);
	typedef void (GLAD_API_PTR* PFNGLGETACTIVEUNIFORMSIVPROC)(GLuint program, GLsizei uniformCount, const GLuint* uniformIndices, GLenum pname, GLint* params);
	typedef void (GLAD_API_PTR* PFNGLGETATTACHEDSHADERSPROC)(GLuint program, GLsizei maxCount, GLsizei* count, GLuint* shaders);
	typedef GLint(GLAD_API_PTR* PFNGLGETATTRIBLOCATIONPROC)(GLuint program, const GLchar* name);
	typedef void (GLAD_API_PTR* PFNGLGETBOOLEANI_VPROC)(GLenum target, GLuint index, GLboolean* data);
	typedef void (GLAD_API_PTR* PFNGLGETBOOLEANVPROC)(GLenum pname, GLboolean* data);
	typedef void (GLAD_API_PTR* PFNGLGETBUFFERPARAMETERI64VPROC)(GLenum target, GLenum pname, GLint64* params);
	typedef void (GLAD_API_PTR* PFNGLGETBUFFERPARAMETERIVPROC)(GLenum target, GLenum pname, GLint* params);
	typedef void (GLAD_API_PTR* PFNGLGETBUFFERPOINTERVPROC)(GLenum target, GLenum pname, void** params);
	typedef void (GLAD_API_PTR* PFNGLGETBUFFERSUBDATAPROC)(GLenum target, GLintptr offset, GLsizeiptr size, void* data);
	typedef void (GLAD_API_PTR* PFNGLGETCLIPPLANEPROC)(GLenum plane, GLdouble* equation);
	typedef void (GLAD_API_PTR* PFNGLGETCOMPRESSEDTEXIMAGEPROC)(GLenum target, GLint level, void* img);
	typedef void (GLAD_API_PTR* PFNGLGETDOUBLEVPROC)(GLenum pname, GLdouble* data);
	typedef GLenum(GLAD_API_PTR* PFNGLGETERRORPROC)(void);
	typedef void (GLAD_API_PTR* PFNGLGETFLOATVPROC)(GLenum pname, GLfloat* data);
	typedef GLint(GLAD_API_PTR* PFNGLGETFRAGDATAINDEXPROC)(GLuint program, const GLchar* name);
	typedef GLint(GLAD_API_PTR* PFNGLGETFRAGDATALOCATIONPROC)(GLuint program, const GLchar* name);
	typedef void (GLAD_API_PTR* PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC)(GLenum target, GLenum attachment, GLenum pname, GLint* params);
	typedef void (GLAD_API_PTR* PFNGLGETINTEGER64I_VPROC)(GLenum target, GLuint index, GLint64* data);
	typedef void (GLAD_API_PTR* PFNGLGETINTEGER64VPROC)(GLenum pname, GLint64* data);
	typedef void (GLAD_API_PTR* PFNGLGETINTEGERI_VPROC)(GLenum target, GLuint index, GLint* data);
	typedef void (GLAD_API_PTR* PFNGLGETINTEGERVPROC)(GLenum pname, GLint* data);
	typedef void (GLAD_API_PTR* PFNGLGETLIGHTFVPROC)(GLenum light, GLenum pname, GLfloat* params);
	typedef void (GLAD_API_PTR* PFNGLGETLIGHTIVPROC)(GLenum light, GLenum pname, GLint* params);
	typedef void (GLAD_API_PTR* PFNGLGETMAPDVPROC)(GLenum target, GLenum query, GLdouble* v);
	typedef void (GLAD_API_PTR* PFNGLGETMAPFVPROC)(GLenum target, GLenum query, GLfloat* v);
	typedef void (GLAD_API_PTR* PFNGLGETMAPIVPROC)(GLenum target, GLenum query, GLint* v);
	typedef void (GLAD_API_PTR* PFNGLGETMATERIALFVPROC)(GLenum face, GLenum pname, GLfloat* params);
	typedef void (GLAD_API_PTR* PFNGLGETMATERIALIVPROC)(GLenum face, GLenum pname, GLint* params);
	typedef void (GLAD_API_PTR* PFNGLGETMULTISAMPLEFVPROC)(GLenum pname, GLuint index, GLfloat* val);
	typedef void (GLAD_API_PTR* PFNGLGETPIXELMAPFVPROC)(GLenum map, GLfloat* values);
	typedef void (GLAD_API_PTR* PFNGLGETPIXELMAPUIVPROC)(GLenum map, GLuint* values);
	typedef void (GLAD_API_PTR* PFNGLGETPIXELMAPUSVPROC)(GLenum map, GLushort* values);
	typedef void (GLAD_API_PTR* PFNGLGETPOINTERVPROC)(GLenum pname, void** params);
	typedef void (GLAD_API_PTR* PFNGLGETPOLYGONSTIPPLEPROC)(GLubyte* mask);
	typedef void (GLAD_API_PTR* PFNGLGETPROGRAMINFOLOGPROC)(GLuint program, GLsizei bufSize, GLsizei* length, GLchar* infoLog);
	typedef void (GLAD_API_PTR* PFNGLGETPROGRAMIVPROC)(GLuint program, GLenum pname, GLint* params);
	typedef void (GLAD_API_PTR* PFNGLGETQUERYOBJECTI64VPROC)(GLuint id, GLenum pname, GLint64* params);
	typedef void (GLAD_API_PTR* PFNGLGETQUERYOBJECTIVPROC)(GLuint id, GLenum pname, GLint* params);
	typedef void (GLAD_API_PTR* PFNGLGETQUERYOBJECTUI64VPROC)(GLuint id, GLenum pname, GLuint64* params);
	typedef void (GLAD_API_PTR* PFNGLGETQUERYOBJECTUIVPROC)(GLuint id, GLenum pname, GLuint* params);
	typedef void (GLAD_API_PTR* PFNGLGETQUERYIVPROC)(GLenum target, GLenum pname, GLint* params);
	typedef void (GLAD_API_PTR* PFNGLGETRENDERBUFFERPARAMETERIVPROC)(GLenum target, GLenum pname, GLint* params);
	typedef void (GLAD_API_PTR* PFNGLGETSAMPLERPARAMETERIIVPROC)(GLuint sampler, GLenum pname, GLint* params);
	typedef void (GLAD_API_PTR* PFNGLGETSAMPLERPARAMETERIUIVPROC)(GLuint sampler, GLenum pname, GLuint* params);
	typedef void (GLAD_API_PTR* PFNGLGETSAMPLERPARAMETERFVPROC)(GLuint sampler, GLenum pname, GLfloat* params);
	typedef void (GLAD_API_PTR* PFNGLGETSAMPLERPARAMETERIVPROC)(GLuint sampler, GLenum pname, GLint* params);
	typedef void (GLAD_API_PTR* PFNGLGETSHADERINFOLOGPROC)(GLuint shader, GLsizei bufSize, GLsizei* length, GLchar* infoLog);
	typedef void (GLAD_API_PTR* PFNGLGETSHADERSOURCEPROC)(GLuint shader, GLsizei bufSize, GLsizei* length, GLchar* source);
	typedef void (GLAD_API_PTR* PFNGLGETSHADERIVPROC)(GLuint shader, GLenum pname, GLint* params);
	typedef const GLubyte* (GLAD_API_PTR* PFNGLGETSTRINGPROC)(GLenum name);
	typedef const GLubyte* (GLAD_API_PTR* PFNGLGETSTRINGIPROC)(GLenum name, GLuint index);
	typedef void (GLAD_API_PTR* PFNGLGETSYNCIVPROC)(GLsync sync, GLenum pname, GLsizei count, GLsizei* length, GLint* values);
	typedef void (GLAD_API_PTR* PFNGLGETTEXENVFVPROC)(GLenum target, GLenum pname, GLfloat* params);
	typedef void (GLAD_API_PTR* PFNGLGETTEXENVIVPROC)(GLenum target, GLenum pname, GLint* params);
	typedef void (GLAD_API_PTR* PFNGLGETTEXGENDVPROC)(GLenum coord, GLenum pname, GLdouble* params);
	typedef void (GLAD_API_PTR* PFNGLGETTEXGENFVPROC)(GLenum coord, GLenum pname, GLfloat* params);
	typedef void (GLAD_API_PTR* PFNGLGETTEXGENIVPROC)(GLenum coord, GLenum pname, GLint* params);
	typedef void (GLAD_API_PTR* PFNGLGETTEXIMAGEPROC)(GLenum target, GLint level, GLenum format, GLenum type, void* pixels);
	typedef void (GLAD_API_PTR* PFNGLGETTEXLEVELPARAMETERFVPROC)(GLenum target, GLint level, GLenum pname, GLfloat* params);
	typedef void (GLAD_API_PTR* PFNGLGETTEXLEVELPARAMETERIVPROC)(GLenum target, GLint level, GLenum pname, GLint* params);
	typedef void (GLAD_API_PTR* PFNGLGETTEXPARAMETERIIVPROC)(GLenum target, GLenum pname, GLint* params);
	typedef void (GLAD_API_PTR* PFNGLGETTEXPARAMETERIUIVPROC)(GLenum target, GLenum pname, GLuint* params);
	typedef void (GLAD_API_PTR* PFNGLGETTEXPARAMETERFVPROC)(GLenum target, GLenum pname, GLfloat* params);
	typedef void (GLAD_API_PTR* PFNGLGETTEXPARAMETERIVPROC)(GLenum target, GLenum pname, GLint* params);
	typedef void (GLAD_API_PTR* PFNGLGETTRANSFORMFEEDBACKVARYINGPROC)(GLuint program, GLuint index, GLsizei bufSize, GLsizei* length, GLsizei* size, GLenum* type, GLchar* name);
	typedef GLuint(GLAD_API_PTR* PFNGLGETUNIFORMBLOCKINDEXPROC)(GLuint program, const GLchar* uniformBlockName);
	typedef void (GLAD_API_PTR* PFNGLGETUNIFORMINDICESPROC)(GLuint program, GLsizei uniformCount, const GLchar* const* uniformNames, GLuint* uniformIndices);
	typedef GLint(GLAD_API_PTR* PFNGLGETUNIFORMLOCATIONPROC)(GLuint program, const GLchar* name);
	typedef void (GLAD_API_PTR* PFNGLGETUNIFORMFVPROC)(GLuint program, GLint location, GLfloat* params);
	typedef void (GLAD_API_PTR* PFNGLGETUNIFORMIVPROC)(GLuint program, GLint location, GLint* params);
	typedef void (GLAD_API_PTR* PFNGLGETUNIFORMUIVPROC)(GLuint program, GLint location, GLuint* params);
	typedef void (GLAD_API_PTR* PFNGLGETVERTEXATTRIBIIVPROC)(GLuint index, GLenum pname, GLint* params);
	typedef void (GLAD_API_PTR* PFNGLGETVERTEXATTRIBIUIVPROC)(GLuint index, GLenum pname, GLuint* params);
	typedef void (GLAD_API_PTR* PFNGLGETVERTEXATTRIBPOINTERVPROC)(GLuint index, GLenum pname, void** pointer);
	typedef void (GLAD_API_PTR* PFNGLGETVERTEXATTRIBDVPROC)(GLuint index, GLenum pname, GLdouble* params);
	typedef void (GLAD_API_PTR* PFNGLGETVERTEXATTRIBFVPROC)(GLuint index, GLenum pname, GLfloat* params);
	typedef void (GLAD_API_PTR* PFNGLGETVERTEXATTRIBIVPROC)(GLuint index, GLenum pname, GLint* params);
	typedef void (GLAD_API_PTR* PFNGLHINTPROC)(GLenum target, GLenum mode);
	typedef void (GLAD_API_PTR* PFNGLINDEXMASKPROC)(GLuint mask);
	typedef void (GLAD_API_PTR* PFNGLINDEXPOINTERPROC)(GLenum type, GLsizei stride, const void* pointer);
	typedef void (GLAD_API_PTR* PFNGLINDEXDPROC)(GLdouble c);
	typedef void (GLAD_API_PTR* PFNGLINDEXDVPROC)(const GLdouble* c);
	typedef void (GLAD_API_PTR* PFNGLINDEXFPROC)(GLfloat c);
	typedef void (GLAD_API_PTR* PFNGLINDEXFVPROC)(const GLfloat* c);
	typedef void (GLAD_API_PTR* PFNGLINDEXIPROC)(GLint c);
	typedef void (GLAD_API_PTR* PFNGLINDEXIVPROC)(const GLint* c);
	typedef void (GLAD_API_PTR* PFNGLINDEXSPROC)(GLshort c);
	typedef void (GLAD_API_PTR* PFNGLINDEXSVPROC)(const GLshort* c);
	typedef void (GLAD_API_PTR* PFNGLINDEXUBPROC)(GLubyte c);
	typedef void (GLAD_API_PTR* PFNGLINDEXUBVPROC)(const GLubyte* c);
	typedef void (GLAD_API_PTR* PFNGLINITNAMESPROC)(void);
	typedef void (GLAD_API_PTR* PFNGLINTERLEAVEDARRAYSPROC)(GLenum format, GLsizei stride, const void* pointer);
	typedef GLboolean(GLAD_API_PTR* PFNGLISBUFFERPROC)(GLuint buffer);
	typedef GLboolean(GLAD_API_PTR* PFNGLISENABLEDPROC)(GLenum cap);
	typedef GLboolean(GLAD_API_PTR* PFNGLISENABLEDIPROC)(GLenum target, GLuint index);
	typedef GLboolean(GLAD_API_PTR* PFNGLISFRAMEBUFFERPROC)(GLuint framebuffer);
	typedef GLboolean(GLAD_API_PTR* PFNGLISLISTPROC)(GLuint list);
	typedef GLboolean(GLAD_API_PTR* PFNGLISPROGRAMPROC)(GLuint program);
	typedef GLboolean(GLAD_API_PTR* PFNGLISQUERYPROC)(GLuint id);
	typedef GLboolean(GLAD_API_PTR* PFNGLISRENDERBUFFERPROC)(GLuint renderbuffer);
	typedef GLboolean(GLAD_API_PTR* PFNGLISSAMPLERPROC)(GLuint sampler);
	typedef GLboolean(GLAD_API_PTR* PFNGLISSHADERPROC)(GLuint shader);
	typedef GLboolean(GLAD_API_PTR* PFNGLISSYNCPROC)(GLsync sync);
	typedef GLboolean(GLAD_API_PTR* PFNGLISTEXTUREPROC)(GLuint texture);
	typedef GLboolean(GLAD_API_PTR* PFNGLISVERTEXARRAYPROC)(GLuint array);
	typedef void (GLAD_API_PTR* PFNGLLIGHTMODELFPROC)(GLenum pname, GLfloat param);
	typedef void (GLAD_API_PTR* PFNGLLIGHTMODELFVPROC)(GLenum pname, const GLfloat* params);
	typedef void (GLAD_API_PTR* PFNGLLIGHTMODELIPROC)(GLenum pname, GLint param);
	typedef void (GLAD_API_PTR* PFNGLLIGHTMODELIVPROC)(GLenum pname, const GLint* params);
	typedef void (GLAD_API_PTR* PFNGLLIGHTFPROC)(GLenum light, GLenum pname, GLfloat param);
	typedef void (GLAD_API_PTR* PFNGLLIGHTFVPROC)(GLenum light, GLenum pname, const GLfloat* params);
	typedef void (GLAD_API_PTR* PFNGLLIGHTIPROC)(GLenum light, GLenum pname, GLint param);
	typedef void (GLAD_API_PTR* PFNGLLIGHTIVPROC)(GLenum light, GLenum pname, const GLint* params);
	typedef void (GLAD_API_PTR* PFNGLLINESTIPPLEPROC)(GLint factor, GLushort pattern);
	typedef void (GLAD_API_PTR* PFNGLLINEWIDTHPROC)(GLfloat width);
	typedef void (GLAD_API_PTR* PFNGLLINKPROGRAMPROC)(GLuint program);
	typedef void (GLAD_API_PTR* PFNGLLISTBASEPROC)(GLuint base);
	typedef void (GLAD_API_PTR* PFNGLLOADIDENTITYPROC)(void);
	typedef void (GLAD_API_PTR* PFNGLLOADMATRIXDPROC)(const GLdouble* m);
	typedef void (GLAD_API_PTR* PFNGLLOADMATRIXFPROC)(const GLfloat* m);
	typedef void (GLAD_API_PTR* PFNGLLOADNAMEPROC)(GLuint name);
	typedef void (GLAD_API_PTR* PFNGLLOADTRANSPOSEMATRIXDPROC)(const GLdouble* m);
	typedef void (GLAD_API_PTR* PFNGLLOADTRANSPOSEMATRIXFPROC)(const GLfloat* m);
	typedef void (GLAD_API_PTR* PFNGLLOGICOPPROC)(GLenum opcode);
	typedef void (GLAD_API_PTR* PFNGLMAP1DPROC)(GLenum target, GLdouble u1, GLdouble u2, GLint stride, GLint order, const GLdouble* points);
	typedef void (GLAD_API_PTR* PFNGLMAP1FPROC)(GLenum target, GLfloat u1, GLfloat u2, GLint stride, GLint order, const GLfloat* points);
	typedef void (GLAD_API_PTR* PFNGLMAP2DPROC)(GLenum target, GLdouble u1, GLdouble u2, GLint ustride, GLint uorder, GLdouble v1, GLdouble v2, GLint vstride, GLint vorder, const GLdouble* points);
	typedef void (GLAD_API_PTR* PFNGLMAP2FPROC)(GLenum target, GLfloat u1, GLfloat u2, GLint ustride, GLint uorder, GLfloat v1, GLfloat v2, GLint vstride, GLint vorder, const GLfloat* points);
	typedef void* (GLAD_API_PTR* PFNGLMAPBUFFERPROC)(GLenum target, GLenum access);
	typedef void* (GLAD_API_PTR* PFNGLMAPBUFFERRANGEPROC)(GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access);
	typedef void (GLAD_API_PTR* PFNGLMAPGRID1DPROC)(GLint un, GLdouble u1, GLdouble u2);
	typedef void (GLAD_API_PTR* PFNGLMAPGRID1FPROC)(GLint un, GLfloat u1, GLfloat u2);
	typedef void (GLAD_API_PTR* PFNGLMAPGRID2DPROC)(GLint un, GLdouble u1, GLdouble u2, GLint vn, GLdouble v1, GLdouble v2);
	typedef void (GLAD_API_PTR* PFNGLMAPGRID2FPROC)(GLint un, GLfloat u1, GLfloat u2, GLint vn, GLfloat v1, GLfloat v2);
	typedef void (GLAD_API_PTR* PFNGLMATERIALFPROC)(GLenum face, GLenum pname, GLfloat param);
	typedef void (GLAD_API_PTR* PFNGLMATERIALFVPROC)(GLenum face, GLenum pname, const GLfloat* params);
	typedef void (GLAD_API_PTR* PFNGLMATERIALIPROC)(GLenum face, GLenum pname, GLint param);
	typedef void (GLAD_API_PTR* PFNGLMATERIALIVPROC)(GLenum face, GLenum pname, const GLint* params);
	typedef void (GLAD_API_PTR* PFNGLMATRIXMODEPROC)(GLenum mode);
	typedef void (GLAD_API_PTR* PFNGLMULTMATRIXDPROC)(const GLdouble* m);
	typedef void (GLAD_API_PTR* PFNGLMULTMATRIXFPROC)(const GLfloat* m);
	typedef void (GLAD_API_PTR* PFNGLMULTTRANSPOSEMATRIXDPROC)(const GLdouble* m);
	typedef void (GLAD_API_PTR* PFNGLMULTTRANSPOSEMATRIXFPROC)(const GLfloat* m);
	typedef void (GLAD_API_PTR* PFNGLMULTIDRAWARRAYSPROC)(GLenum mode, const GLint* first, const GLsizei* count, GLsizei drawcount);
	typedef void (GLAD_API_PTR* PFNGLMULTIDRAWELEMENTSPROC)(GLenum mode, const GLsizei* count, GLenum type, const void* const* indices, GLsizei drawcount);
	typedef void (GLAD_API_PTR* PFNGLMULTIDRAWELEMENTSBASEVERTEXPROC)(GLenum mode, const GLsizei* count, GLenum type, const void* const* indices, GLsizei drawcount, const GLint* basevertex);
	typedef void (GLAD_API_PTR* PFNGLMULTITEXCOORD1DPROC)(GLenum target, GLdouble s);
	typedef void (GLAD_API_PTR* PFNGLMULTITEXCOORD1DVPROC)(GLenum target, const GLdouble* v);
	typedef void (GLAD_API_PTR* PFNGLMULTITEXCOORD1FPROC)(GLenum target, GLfloat s);
	typedef void (GLAD_API_PTR* PFNGLMULTITEXCOORD1FVPROC)(GLenum target, const GLfloat* v);
	typedef void (GLAD_API_PTR* PFNGLMULTITEXCOORD1IPROC)(GLenum target, GLint s);
	typedef void (GLAD_API_PTR* PFNGLMULTITEXCOORD1IVPROC)(GLenum target, const GLint* v);
	typedef void (GLAD_API_PTR* PFNGLMULTITEXCOORD1SPROC)(GLenum target, GLshort s);
	typedef void (GLAD_API_PTR* PFNGLMULTITEXCOORD1SVPROC)(GLenum target, const GLshort* v);
	typedef void (GLAD_API_PTR* PFNGLMULTITEXCOORD2DPROC)(GLenum target, GLdouble s, GLdouble t);
	typedef void (GLAD_API_PTR* PFNGLMULTITEXCOORD2DVPROC)(GLenum target, const GLdouble* v);
	typedef void (GLAD_API_PTR* PFNGLMULTITEXCOORD2FPROC)(GLenum target, GLfloat s, GLfloat t);
	typedef void (GLAD_API_PTR* PFNGLMULTITEXCOORD2FVPROC)(GLenum target, const GLfloat* v);
	typedef void (GLAD_API_PTR* PFNGLMULTITEXCOORD2IPROC)(GLenum target, GLint s, GLint t);
	typedef void (GLAD_API_PTR* PFNGLMULTITEXCOORD2IVPROC)(GLenum target, const GLint* v);
	typedef void (GLAD_API_PTR* PFNGLMULTITEXCOORD2SPROC)(GLenum target, GLshort s, GLshort t);
	typedef void (GLAD_API_PTR* PFNGLMULTITEXCOORD2SVPROC)(GLenum target, const GLshort* v);
	typedef void (GLAD_API_PTR* PFNGLMULTITEXCOORD3DPROC)(GLenum target, GLdouble s, GLdouble t, GLdouble r);
	typedef void (GLAD_API_PTR* PFNGLMULTITEXCOORD3DVPROC)(GLenum target, const GLdouble* v);
	typedef void (GLAD_API_PTR* PFNGLMULTITEXCOORD3FPROC)(GLenum target, GLfloat s, GLfloat t, GLfloat r);
	typedef void (GLAD_API_PTR* PFNGLMULTITEXCOORD3FVPROC)(GLenum target, const GLfloat* v);
	typedef void (GLAD_API_PTR* PFNGLMULTITEXCOORD3IPROC)(GLenum target, GLint s, GLint t, GLint r);
	typedef void (GLAD_API_PTR* PFNGLMULTITEXCOORD3IVPROC)(GLenum target, const GLint* v);
	typedef void (GLAD_API_PTR* PFNGLMULTITEXCOORD3SPROC)(GLenum target, GLshort s, GLshort t, GLshort r);
	typedef void (GLAD_API_PTR* PFNGLMULTITEXCOORD3SVPROC)(GLenum target, const GLshort* v);
	typedef void (GLAD_API_PTR* PFNGLMULTITEXCOORD4DPROC)(GLenum target, GLdouble s, GLdouble t, GLdouble r, GLdouble q);
	typedef void (GLAD_API_PTR* PFNGLMULTITEXCOORD4DVPROC)(GLenum target, const GLdouble* v);
	typedef void (GLAD_API_PTR* PFNGLMULTITEXCOORD4FPROC)(GLenum target, GLfloat s, GLfloat t, GLfloat r, GLfloat q);
	typedef void (GLAD_API_PTR* PFNGLMULTITEXCOORD4FVPROC)(GLenum target, const GLfloat* v);
	typedef void (GLAD_API_PTR* PFNGLMULTITEXCOORD4IPROC)(GLenum target, GLint s, GLint t, GLint r, GLint q);
	typedef void (GLAD_API_PTR* PFNGLMULTITEXCOORD4IVPROC)(GLenum target, const GLint* v);
	typedef void (GLAD_API_PTR* PFNGLMULTITEXCOORD4SPROC)(GLenum target, GLshort s, GLshort t, GLshort r, GLshort q);
	typedef void (GLAD_API_PTR* PFNGLMULTITEXCOORD4SVPROC)(GLenum target, const GLshort* v);
	typedef void (GLAD_API_PTR* PFNGLMULTITEXCOORDP1UIPROC)(GLenum texture, GLenum type, GLuint coords);
	typedef void (GLAD_API_PTR* PFNGLMULTITEXCOORDP1UIVPROC)(GLenum texture, GLenum type, const GLuint* coords);
	typedef void (GLAD_API_PTR* PFNGLMULTITEXCOORDP2UIPROC)(GLenum texture, GLenum type, GLuint coords);
	typedef void (GLAD_API_PTR* PFNGLMULTITEXCOORDP2UIVPROC)(GLenum texture, GLenum type, const GLuint* coords);
	typedef void (GLAD_API_PTR* PFNGLMULTITEXCOORDP3UIPROC)(GLenum texture, GLenum type, GLuint coords);
	typedef void (GLAD_API_PTR* PFNGLMULTITEXCOORDP3UIVPROC)(GLenum texture, GLenum type, const GLuint* coords);
	typedef void (GLAD_API_PTR* PFNGLMULTITEXCOORDP4UIPROC)(GLenum texture, GLenum type, GLuint coords);
	typedef void (GLAD_API_PTR* PFNGLMULTITEXCOORDP4UIVPROC)(GLenum texture, GLenum type, const GLuint* coords);
	typedef void (GLAD_API_PTR* PFNGLNEWLISTPROC)(GLuint list, GLenum mode);
	typedef void (GLAD_API_PTR* PFNGLNORMAL3BPROC)(GLbyte nx, GLbyte ny, GLbyte nz);
	typedef void (GLAD_API_PTR* PFNGLNORMAL3BVPROC)(const GLbyte* v);
	typedef void (GLAD_API_PTR* PFNGLNORMAL3DPROC)(GLdouble nx, GLdouble ny, GLdouble nz);
	typedef void (GLAD_API_PTR* PFNGLNORMAL3DVPROC)(const GLdouble* v);
	typedef void (GLAD_API_PTR* PFNGLNORMAL3FPROC)(GLfloat nx, GLfloat ny, GLfloat nz);
	typedef void (GLAD_API_PTR* PFNGLNORMAL3FVPROC)(const GLfloat* v);
	typedef void (GLAD_API_PTR* PFNGLNORMAL3IPROC)(GLint nx, GLint ny, GLint nz);
	typedef void (GLAD_API_PTR* PFNGLNORMAL3IVPROC)(const GLint* v);
	typedef void (GLAD_API_PTR* PFNGLNORMAL3SPROC)(GLshort nx, GLshort ny, GLshort nz);
	typedef void (GLAD_API_PTR* PFNGLNORMAL3SVPROC)(const GLshort* v);
	typedef void (GLAD_API_PTR* PFNGLNORMALP3UIPROC)(GLenum type, GLuint coords);
	typedef void (GLAD_API_PTR* PFNGLNORMALP3UIVPROC)(GLenum type, const GLuint* coords);
	typedef void (GLAD_API_PTR* PFNGLNORMALPOINTERPROC)(GLenum type, GLsizei stride, const void* pointer);
	typedef void (GLAD_API_PTR* PFNGLORTHOPROC)(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar);
	typedef void (GLAD_API_PTR* PFNGLPASSTHROUGHPROC)(GLfloat token);
	typedef void (GLAD_API_PTR* PFNGLPIXELMAPFVPROC)(GLenum map, GLsizei mapsize, const GLfloat* values);
	typedef void (GLAD_API_PTR* PFNGLPIXELMAPUIVPROC)(GLenum map, GLsizei mapsize, const GLuint* values);
	typedef void (GLAD_API_PTR* PFNGLPIXELMAPUSVPROC)(GLenum map, GLsizei mapsize, const GLushort* values);
	typedef void (GLAD_API_PTR* PFNGLPIXELSTOREFPROC)(GLenum pname, GLfloat param);
	typedef void (GLAD_API_PTR* PFNGLPIXELSTOREIPROC)(GLenum pname, GLint param);
	typedef void (GLAD_API_PTR* PFNGLPIXELTRANSFERFPROC)(GLenum pname, GLfloat param);
	typedef void (GLAD_API_PTR* PFNGLPIXELTRANSFERIPROC)(GLenum pname, GLint param);
	typedef void (GLAD_API_PTR* PFNGLPIXELZOOMPROC)(GLfloat xfactor, GLfloat yfactor);
	typedef void (GLAD_API_PTR* PFNGLPOINTPARAMETERFPROC)(GLenum pname, GLfloat param);
	typedef void (GLAD_API_PTR* PFNGLPOINTPARAMETERFVPROC)(GLenum pname, const GLfloat* params);
	typedef void (GLAD_API_PTR* PFNGLPOINTPARAMETERIPROC)(GLenum pname, GLint param);
	typedef void (GLAD_API_PTR* PFNGLPOINTPARAMETERIVPROC)(GLenum pname, const GLint* params);
	typedef void (GLAD_API_PTR* PFNGLPOINTSIZEPROC)(GLfloat size);
	typedef void (GLAD_API_PTR* PFNGLPOLYGONMODEPROC)(GLenum face, GLenum mode);
	typedef void (GLAD_API_PTR* PFNGLPOLYGONOFFSETPROC)(GLfloat factor, GLfloat units);
	typedef void (GLAD_API_PTR* PFNGLPOLYGONSTIPPLEPROC)(const GLubyte* mask);
	typedef void (GLAD_API_PTR* PFNGLPOPATTRIBPROC)(void);
	typedef void (GLAD_API_PTR* PFNGLPOPCLIENTATTRIBPROC)(void);
	typedef void (GLAD_API_PTR* PFNGLPOPMATRIXPROC)(void);
	typedef void (GLAD_API_PTR* PFNGLPOPNAMEPROC)(void);
	typedef void (GLAD_API_PTR* PFNGLPRIMITIVERESTARTINDEXPROC)(GLuint index);
	typedef void (GLAD_API_PTR* PFNGLPRIORITIZETEXTURESPROC)(GLsizei n, const GLuint* textures, const GLfloat* priorities);
	typedef void (GLAD_API_PTR* PFNGLPROVOKINGVERTEXPROC)(GLenum mode);
	typedef void (GLAD_API_PTR* PFNGLPUSHATTRIBPROC)(GLbitfield mask);
	typedef void (GLAD_API_PTR* PFNGLPUSHCLIENTATTRIBPROC)(GLbitfield mask);
	typedef void (GLAD_API_PTR* PFNGLPUSHMATRIXPROC)(void);
	typedef void (GLAD_API_PTR* PFNGLPUSHNAMEPROC)(GLuint name);
	typedef void (GLAD_API_PTR* PFNGLQUERYCOUNTERPROC)(GLuint id, GLenum target);
	typedef void (GLAD_API_PTR* PFNGLRASTERPOS2DPROC)(GLdouble x, GLdouble y);
	typedef void (GLAD_API_PTR* PFNGLRASTERPOS2DVPROC)(const GLdouble* v);
	typedef void (GLAD_API_PTR* PFNGLRASTERPOS2FPROC)(GLfloat x, GLfloat y);
	typedef void (GLAD_API_PTR* PFNGLRASTERPOS2FVPROC)(const GLfloat* v);
	typedef void (GLAD_API_PTR* PFNGLRASTERPOS2IPROC)(GLint x, GLint y);
	typedef void (GLAD_API_PTR* PFNGLRASTERPOS2IVPROC)(const GLint* v);
	typedef void (GLAD_API_PTR* PFNGLRASTERPOS2SPROC)(GLshort x, GLshort y);
	typedef void (GLAD_API_PTR* PFNGLRASTERPOS2SVPROC)(const GLshort* v);
	typedef void (GLAD_API_PTR* PFNGLRASTERPOS3DPROC)(GLdouble x, GLdouble y, GLdouble z);
	typedef void (GLAD_API_PTR* PFNGLRASTERPOS3DVPROC)(const GLdouble* v);
	typedef void (GLAD_API_PTR* PFNGLRASTERPOS3FPROC)(GLfloat x, GLfloat y, GLfloat z);
	typedef void (GLAD_API_PTR* PFNGLRASTERPOS3FVPROC)(const GLfloat* v);
	typedef void (GLAD_API_PTR* PFNGLRASTERPOS3IPROC)(GLint x, GLint y, GLint z);
	typedef void (GLAD_API_PTR* PFNGLRASTERPOS3IVPROC)(const GLint* v);
	typedef void (GLAD_API_PTR* PFNGLRASTERPOS3SPROC)(GLshort x, GLshort y, GLshort z);
	typedef void (GLAD_API_PTR* PFNGLRASTERPOS3SVPROC)(const GLshort* v);
	typedef void (GLAD_API_PTR* PFNGLRASTERPOS4DPROC)(GLdouble x, GLdouble y, GLdouble z, GLdouble w);
	typedef void (GLAD_API_PTR* PFNGLRASTERPOS4DVPROC)(const GLdouble* v);
	typedef void (GLAD_API_PTR* PFNGLRASTERPOS4FPROC)(GLfloat x, GLfloat y, GLfloat z, GLfloat w);
	typedef void (GLAD_API_PTR* PFNGLRASTERPOS4FVPROC)(const GLfloat* v);
	typedef void (GLAD_API_PTR* PFNGLRASTERPOS4IPROC)(GLint x, GLint y, GLint z, GLint w);
	typedef void (GLAD_API_PTR* PFNGLRASTERPOS4IVPROC)(const GLint* v);
	typedef void (GLAD_API_PTR* PFNGLRASTERPOS4SPROC)(GLshort x, GLshort y, GLshort z, GLshort w);
	typedef void (GLAD_API_PTR* PFNGLRASTERPOS4SVPROC)(const GLshort* v);
	typedef void (GLAD_API_PTR* PFNGLREADBUFFERPROC)(GLenum src);
	typedef void (GLAD_API_PTR* PFNGLREADPIXELSPROC)(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, void* pixels);
	typedef void (GLAD_API_PTR* PFNGLRECTDPROC)(GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2);
	typedef void (GLAD_API_PTR* PFNGLRECTDVPROC)(const GLdouble* v1, const GLdouble* v2);
	typedef void (GLAD_API_PTR* PFNGLRECTFPROC)(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2);
	typedef void (GLAD_API_PTR* PFNGLRECTFVPROC)(const GLfloat* v1, const GLfloat* v2);
	typedef void (GLAD_API_PTR* PFNGLRECTIPROC)(GLint x1, GLint y1, GLint x2, GLint y2);
	typedef void (GLAD_API_PTR* PFNGLRECTIVPROC)(const GLint* v1, const GLint* v2);
	typedef void (GLAD_API_PTR* PFNGLRECTSPROC)(GLshort x1, GLshort y1, GLshort x2, GLshort y2);
	typedef void (GLAD_API_PTR* PFNGLRECTSVPROC)(const GLshort* v1, const GLshort* v2);
	typedef GLint(GLAD_API_PTR* PFNGLRENDERMODEPROC)(GLenum mode);
	typedef void (GLAD_API_PTR* PFNGLRENDERBUFFERSTORAGEPROC)(GLenum target, GLenum internalformat, GLsizei width, GLsizei height);
	typedef void (GLAD_API_PTR* PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC)(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height);
	typedef void (GLAD_API_PTR* PFNGLROTATEDPROC)(GLdouble angle, GLdouble x, GLdouble y, GLdouble z);
	typedef void (GLAD_API_PTR* PFNGLROTATEFPROC)(GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
	typedef void (GLAD_API_PTR* PFNGLSAMPLECOVERAGEPROC)(GLfloat value, GLboolean invert);
	typedef void (GLAD_API_PTR* PFNGLSAMPLEMASKIPROC)(GLuint maskNumber, GLbitfield mask);
	typedef void (GLAD_API_PTR* PFNGLSAMPLERPARAMETERIIVPROC)(GLuint sampler, GLenum pname, const GLint* param);
	typedef void (GLAD_API_PTR* PFNGLSAMPLERPARAMETERIUIVPROC)(GLuint sampler, GLenum pname, const GLuint* param);
	typedef void (GLAD_API_PTR* PFNGLSAMPLERPARAMETERFPROC)(GLuint sampler, GLenum pname, GLfloat param);
	typedef void (GLAD_API_PTR* PFNGLSAMPLERPARAMETERFVPROC)(GLuint sampler, GLenum pname, const GLfloat* param);
	typedef void (GLAD_API_PTR* PFNGLSAMPLERPARAMETERIPROC)(GLuint sampler, GLenum pname, GLint param);
	typedef void (GLAD_API_PTR* PFNGLSAMPLERPARAMETERIVPROC)(GLuint sampler, GLenum pname, const GLint* param);
	typedef void (GLAD_API_PTR* PFNGLSCALEDPROC)(GLdouble x, GLdouble y, GLdouble z);
	typedef void (GLAD_API_PTR* PFNGLSCALEFPROC)(GLfloat x, GLfloat y, GLfloat z);
	typedef void (GLAD_API_PTR* PFNGLSCISSORPROC)(GLint x, GLint y, GLsizei width, GLsizei height);
	typedef void (GLAD_API_PTR* PFNGLSECONDARYCOLOR3BPROC)(GLbyte red, GLbyte green, GLbyte blue);
	typedef void (GLAD_API_PTR* PFNGLSECONDARYCOLOR3BVPROC)(const GLbyte* v);
	typedef void (GLAD_API_PTR* PFNGLSECONDARYCOLOR3DPROC)(GLdouble red, GLdouble green, GLdouble blue);
	typedef void (GLAD_API_PTR* PFNGLSECONDARYCOLOR3DVPROC)(const GLdouble* v);
	typedef void (GLAD_API_PTR* PFNGLSECONDARYCOLOR3FPROC)(GLfloat red, GLfloat green, GLfloat blue);
	typedef void (GLAD_API_PTR* PFNGLSECONDARYCOLOR3FVPROC)(const GLfloat* v);
	typedef void (GLAD_API_PTR* PFNGLSECONDARYCOLOR3IPROC)(GLint red, GLint green, GLint blue);
	typedef void (GLAD_API_PTR* PFNGLSECONDARYCOLOR3IVPROC)(const GLint* v);
	typedef void (GLAD_API_PTR* PFNGLSECONDARYCOLOR3SPROC)(GLshort red, GLshort green, GLshort blue);
	typedef void (GLAD_API_PTR* PFNGLSECONDARYCOLOR3SVPROC)(const GLshort* v);
	typedef void (GLAD_API_PTR* PFNGLSECONDARYCOLOR3UBPROC)(GLubyte red, GLubyte green, GLubyte blue);
	typedef void (GLAD_API_PTR* PFNGLSECONDARYCOLOR3UBVPROC)(const GLubyte* v);
	typedef void (GLAD_API_PTR* PFNGLSECONDARYCOLOR3UIPROC)(GLuint red, GLuint green, GLuint blue);
	typedef void (GLAD_API_PTR* PFNGLSECONDARYCOLOR3UIVPROC)(const GLuint* v);
	typedef void (GLAD_API_PTR* PFNGLSECONDARYCOLOR3USPROC)(GLushort red, GLushort green, GLushort blue);
	typedef void (GLAD_API_PTR* PFNGLSECONDARYCOLOR3USVPROC)(const GLushort* v);
	typedef void (GLAD_API_PTR* PFNGLSECONDARYCOLORP3UIPROC)(GLenum type, GLuint color);
	typedef void (GLAD_API_PTR* PFNGLSECONDARYCOLORP3UIVPROC)(GLenum type, const GLuint* color);
	typedef void (GLAD_API_PTR* PFNGLSECONDARYCOLORPOINTERPROC)(GLint size, GLenum type, GLsizei stride, const void* pointer);
	typedef void (GLAD_API_PTR* PFNGLSELECTBUFFERPROC)(GLsizei size, GLuint* buffer);
	typedef void (GLAD_API_PTR* PFNGLSHADEMODELPROC)(GLenum mode);
	typedef void (GLAD_API_PTR* PFNGLSHADERSOURCEPROC)(GLuint shader, GLsizei count, const GLchar* const* string, const GLint* length);
	typedef void (GLAD_API_PTR* PFNGLSTENCILFUNCPROC)(GLenum func, GLint ref, GLuint mask);
	typedef void (GLAD_API_PTR* PFNGLSTENCILFUNCSEPARATEPROC)(GLenum face, GLenum func, GLint ref, GLuint mask);
	typedef void (GLAD_API_PTR* PFNGLSTENCILMASKPROC)(GLuint mask);
	typedef void (GLAD_API_PTR* PFNGLSTENCILMASKSEPARATEPROC)(GLenum face, GLuint mask);
	typedef void (GLAD_API_PTR* PFNGLSTENCILOPPROC)(GLenum fail, GLenum zfail, GLenum zpass);
	typedef void (GLAD_API_PTR* PFNGLSTENCILOPSEPARATEPROC)(GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass);
	typedef void (GLAD_API_PTR* PFNGLTEXBUFFERPROC)(GLenum target, GLenum internalformat, GLuint buffer);
	typedef void (GLAD_API_PTR* PFNGLTEXCOORD1DPROC)(GLdouble s);
	typedef void (GLAD_API_PTR* PFNGLTEXCOORD1DVPROC)(const GLdouble* v);
	typedef void (GLAD_API_PTR* PFNGLTEXCOORD1FPROC)(GLfloat s);
	typedef void (GLAD_API_PTR* PFNGLTEXCOORD1FVPROC)(const GLfloat* v);
	typedef void (GLAD_API_PTR* PFNGLTEXCOORD1IPROC)(GLint s);
	typedef void (GLAD_API_PTR* PFNGLTEXCOORD1IVPROC)(const GLint* v);
	typedef void (GLAD_API_PTR* PFNGLTEXCOORD1SPROC)(GLshort s);
	typedef void (GLAD_API_PTR* PFNGLTEXCOORD1SVPROC)(const GLshort* v);
	typedef void (GLAD_API_PTR* PFNGLTEXCOORD2DPROC)(GLdouble s, GLdouble t);
	typedef void (GLAD_API_PTR* PFNGLTEXCOORD2DVPROC)(const GLdouble* v);
	typedef void (GLAD_API_PTR* PFNGLTEXCOORD2FPROC)(GLfloat s, GLfloat t);
	typedef void (GLAD_API_PTR* PFNGLTEXCOORD2FVPROC)(const GLfloat* v);
	typedef void (GLAD_API_PTR* PFNGLTEXCOORD2IPROC)(GLint s, GLint t);
	typedef void (GLAD_API_PTR* PFNGLTEXCOORD2IVPROC)(const GLint* v);
	typedef void (GLAD_API_PTR* PFNGLTEXCOORD2SPROC)(GLshort s, GLshort t);
	typedef void (GLAD_API_PTR* PFNGLTEXCOORD2SVPROC)(const GLshort* v);
	typedef void (GLAD_API_PTR* PFNGLTEXCOORD3DPROC)(GLdouble s, GLdouble t, GLdouble r);
	typedef void (GLAD_API_PTR* PFNGLTEXCOORD3DVPROC)(const GLdouble* v);
	typedef void (GLAD_API_PTR* PFNGLTEXCOORD3FPROC)(GLfloat s, GLfloat t, GLfloat r);
	typedef void (GLAD_API_PTR* PFNGLTEXCOORD3FVPROC)(const GLfloat* v);
	typedef void (GLAD_API_PTR* PFNGLTEXCOORD3IPROC)(GLint s, GLint t, GLint r);
	typedef void (GLAD_API_PTR* PFNGLTEXCOORD3IVPROC)(const GLint* v);
	typedef void (GLAD_API_PTR* PFNGLTEXCOORD3SPROC)(GLshort s, GLshort t, GLshort r);
	typedef void (GLAD_API_PTR* PFNGLTEXCOORD3SVPROC)(const GLshort* v);
	typedef void (GLAD_API_PTR* PFNGLTEXCOORD4DPROC)(GLdouble s, GLdouble t, GLdouble r, GLdouble q);
	typedef void (GLAD_API_PTR* PFNGLTEXCOORD4DVPROC)(const GLdouble* v);
	typedef void (GLAD_API_PTR* PFNGLTEXCOORD4FPROC)(GLfloat s, GLfloat t, GLfloat r, GLfloat q);
	typedef void (GLAD_API_PTR* PFNGLTEXCOORD4FVPROC)(const GLfloat* v);
	typedef void (GLAD_API_PTR* PFNGLTEXCOORD4IPROC)(GLint s, GLint t, GLint r, GLint q);
	typedef void (GLAD_API_PTR* PFNGLTEXCOORD4IVPROC)(const GLint* v);
	typedef void (GLAD_API_PTR* PFNGLTEXCOORD4SPROC)(GLshort s, GLshort t, GLshort r, GLshort q);
	typedef void (GLAD_API_PTR* PFNGLTEXCOORD4SVPROC)(const GLshort* v);
	typedef void (GLAD_API_PTR* PFNGLTEXCOORDP1UIPROC)(GLenum type, GLuint coords);
	typedef void (GLAD_API_PTR* PFNGLTEXCOORDP1UIVPROC)(GLenum type, const GLuint* coords);
	typedef void (GLAD_API_PTR* PFNGLTEXCOORDP2UIPROC)(GLenum type, GLuint coords);
	typedef void (GLAD_API_PTR* PFNGLTEXCOORDP2UIVPROC)(GLenum type, const GLuint* coords);
	typedef void (GLAD_API_PTR* PFNGLTEXCOORDP3UIPROC)(GLenum type, GLuint coords);
	typedef void (GLAD_API_PTR* PFNGLTEXCOORDP3UIVPROC)(GLenum type, const GLuint* coords);
	typedef void (GLAD_API_PTR* PFNGLTEXCOORDP4UIPROC)(GLenum type, GLuint coords);
	typedef void (GLAD_API_PTR* PFNGLTEXCOORDP4UIVPROC)(GLenum type, const GLuint* coords);
	typedef void (GLAD_API_PTR* PFNGLTEXCOORDPOINTERPROC)(GLint size, GLenum type, GLsizei stride, const void* pointer);
	typedef void (GLAD_API_PTR* PFNGLTEXENVFPROC)(GLenum target, GLenum pname, GLfloat param);
	typedef void (GLAD_API_PTR* PFNGLTEXENVFVPROC)(GLenum target, GLenum pname, const GLfloat* params);
	typedef void (GLAD_API_PTR* PFNGLTEXENVIPROC)(GLenum target, GLenum pname, GLint param);
	typedef void (GLAD_API_PTR* PFNGLTEXENVIVPROC)(GLenum target, GLenum pname, const GLint* params);
	typedef void (GLAD_API_PTR* PFNGLTEXGENDPROC)(GLenum coord, GLenum pname, GLdouble param);
	typedef void (GLAD_API_PTR* PFNGLTEXGENDVPROC)(GLenum coord, GLenum pname, const GLdouble* params);
	typedef void (GLAD_API_PTR* PFNGLTEXGENFPROC)(GLenum coord, GLenum pname, GLfloat param);
	typedef void (GLAD_API_PTR* PFNGLTEXGENFVPROC)(GLenum coord, GLenum pname, const GLfloat* params);
	typedef void (GLAD_API_PTR* PFNGLTEXGENIPROC)(GLenum coord, GLenum pname, GLint param);
	typedef void (GLAD_API_PTR* PFNGLTEXGENIVPROC)(GLenum coord, GLenum pname, const GLint* params);
	typedef void (GLAD_API_PTR* PFNGLTEXIMAGE1DPROC)(GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, const void* pixels);
	typedef void (GLAD_API_PTR* PFNGLTEXIMAGE2DPROC)(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void* pixels);
	typedef void (GLAD_API_PTR* PFNGLTEXIMAGE2DMULTISAMPLEPROC)(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations);
	typedef void (GLAD_API_PTR* PFNGLTEXIMAGE3DPROC)(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const void* pixels);
	typedef void (GLAD_API_PTR* PFNGLTEXIMAGE3DMULTISAMPLEPROC)(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations);
	typedef void (GLAD_API_PTR* PFNGLTEXPARAMETERIIVPROC)(GLenum target, GLenum pname, const GLint* params);
	typedef void (GLAD_API_PTR* PFNGLTEXPARAMETERIUIVPROC)(GLenum target, GLenum pname, const GLuint* params);
	typedef void (GLAD_API_PTR* PFNGLTEXPARAMETERFPROC)(GLenum target, GLenum pname, GLfloat param);
	typedef void (GLAD_API_PTR* PFNGLTEXPARAMETERFVPROC)(GLenum target, GLenum pname, const GLfloat* params);
	typedef void (GLAD_API_PTR* PFNGLTEXPARAMETERIPROC)(GLenum target, GLenum pname, GLint param);
	typedef void (GLAD_API_PTR* PFNGLTEXPARAMETERIVPROC)(GLenum target, GLenum pname, const GLint* params);
	typedef void (GLAD_API_PTR* PFNGLTEXSUBIMAGE1DPROC)(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const void* pixels);
	typedef void (GLAD_API_PTR* PFNGLTEXSUBIMAGE2DPROC)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void* pixels);
	typedef void (GLAD_API_PTR* PFNGLTEXSUBIMAGE3DPROC)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void* pixels);
	typedef void (GLAD_API_PTR* PFNGLTRANSFORMFEEDBACKVARYINGSPROC)(GLuint program, GLsizei count, const GLchar* const* varyings, GLenum bufferMode);
	typedef void (GLAD_API_PTR* PFNGLTRANSLATEDPROC)(GLdouble x, GLdouble y, GLdouble z);
	typedef void (GLAD_API_PTR* PFNGLTRANSLATEFPROC)(GLfloat x, GLfloat y, GLfloat z);
	typedef void (GLAD_API_PTR* PFNGLUNIFORM1FPROC)(GLint location, GLfloat v0);
	typedef void (GLAD_API_PTR* PFNGLUNIFORM1FVPROC)(GLint location, GLsizei count, const GLfloat* value);
	typedef void (GLAD_API_PTR* PFNGLUNIFORM1IPROC)(GLint location, GLint v0);
	typedef void (GLAD_API_PTR* PFNGLUNIFORM1IVPROC)(GLint location, GLsizei count, const GLint* value);
	typedef void (GLAD_API_PTR* PFNGLUNIFORM1UIPROC)(GLint location, GLuint v0);
	typedef void (GLAD_API_PTR* PFNGLUNIFORM1UIVPROC)(GLint location, GLsizei count, const GLuint* value);
	typedef void (GLAD_API_PTR* PFNGLUNIFORM2FPROC)(GLint location, GLfloat v0, GLfloat v1);
	typedef void (GLAD_API_PTR* PFNGLUNIFORM2FVPROC)(GLint location, GLsizei count, const GLfloat* value);
	typedef void (GLAD_API_PTR* PFNGLUNIFORM2IPROC)(GLint location, GLint v0, GLint v1);
	typedef void (GLAD_API_PTR* PFNGLUNIFORM2IVPROC)(GLint location, GLsizei count, const GLint* value);
	typedef void (GLAD_API_PTR* PFNGLUNIFORM2UIPROC)(GLint location, GLuint v0, GLuint v1);
	typedef void (GLAD_API_PTR* PFNGLUNIFORM2UIVPROC)(GLint location, GLsizei count, const GLuint* value);
	typedef void (GLAD_API_PTR* PFNGLUNIFORM3FPROC)(GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
	typedef void (GLAD_API_PTR* PFNGLUNIFORM3FVPROC)(GLint location, GLsizei count, const GLfloat* value);
	typedef void (GLAD_API_PTR* PFNGLUNIFORM3IPROC)(GLint location, GLint v0, GLint v1, GLint v2);
	typedef void (GLAD_API_PTR* PFNGLUNIFORM3IVPROC)(GLint location, GLsizei count, const GLint* value);
	typedef void (GLAD_API_PTR* PFNGLUNIFORM3UIPROC)(GLint location, GLuint v0, GLuint v1, GLuint v2);
	typedef void (GLAD_API_PTR* PFNGLUNIFORM3UIVPROC)(GLint location, GLsizei count, const GLuint* value);
	typedef void (GLAD_API_PTR* PFNGLUNIFORM4FPROC)(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
	typedef void (GLAD_API_PTR* PFNGLUNIFORM4FVPROC)(GLint location, GLsizei count, const GLfloat* value);
	typedef void (GLAD_API_PTR* PFNGLUNIFORM4IPROC)(GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
	typedef void (GLAD_API_PTR* PFNGLUNIFORM4IVPROC)(GLint location, GLsizei count, const GLint* value);
	typedef void (GLAD_API_PTR* PFNGLUNIFORM4UIPROC)(GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
	typedef void (GLAD_API_PTR* PFNGLUNIFORM4UIVPROC)(GLint location, GLsizei count, const GLuint* value);
	typedef void (GLAD_API_PTR* PFNGLUNIFORMBLOCKBINDINGPROC)(GLuint program, GLuint uniformBlockIndex, GLuint uniformBlockBinding);
	typedef void (GLAD_API_PTR* PFNGLUNIFORMMATRIX2FVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
	typedef void (GLAD_API_PTR* PFNGLUNIFORMMATRIX2X3FVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
	typedef void (GLAD_API_PTR* PFNGLUNIFORMMATRIX2X4FVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
	typedef void (GLAD_API_PTR* PFNGLUNIFORMMATRIX3FVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
	typedef void (GLAD_API_PTR* PFNGLUNIFORMMATRIX3X2FVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
	typedef void (GLAD_API_PTR* PFNGLUNIFORMMATRIX3X4FVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
	typedef void (GLAD_API_PTR* PFNGLUNIFORMMATRIX4FVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
	typedef void (GLAD_API_PTR* PFNGLUNIFORMMATRIX4X2FVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
	typedef void (GLAD_API_PTR* PFNGLUNIFORMMATRIX4X3FVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
	typedef GLboolean(GLAD_API_PTR* PFNGLUNMAPBUFFERPROC)(GLenum target);
	typedef void (GLAD_API_PTR* PFNGLUSEPROGRAMPROC)(GLuint program);
	typedef void (GLAD_API_PTR* PFNGLVALIDATEPROGRAMPROC)(GLuint program);
	typedef void (GLAD_API_PTR* PFNGLVERTEX2DPROC)(GLdouble x, GLdouble y);
	typedef void (GLAD_API_PTR* PFNGLVERTEX2DVPROC)(const GLdouble* v);
	typedef void (GLAD_API_PTR* PFNGLVERTEX2FPROC)(GLfloat x, GLfloat y);
	typedef void (GLAD_API_PTR* PFNGLVERTEX2FVPROC)(const GLfloat* v);
	typedef void (GLAD_API_PTR* PFNGLVERTEX2IPROC)(GLint x, GLint y);
	typedef void (GLAD_API_PTR* PFNGLVERTEX2IVPROC)(const GLint* v);
	typedef void (GLAD_API_PTR* PFNGLVERTEX2SPROC)(GLshort x, GLshort y);
	typedef void (GLAD_API_PTR* PFNGLVERTEX2SVPROC)(const GLshort* v);
	typedef void (GLAD_API_PTR* PFNGLVERTEX3DPROC)(GLdouble x, GLdouble y, GLdouble z);
	typedef void (GLAD_API_PTR* PFNGLVERTEX3DVPROC)(const GLdouble* v);
	typedef void (GLAD_API_PTR* PFNGLVERTEX3FPROC)(GLfloat x, GLfloat y, GLfloat z);
	typedef void (GLAD_API_PTR* PFNGLVERTEX3FVPROC)(const GLfloat* v);
	typedef void (GLAD_API_PTR* PFNGLVERTEX3IPROC)(GLint x, GLint y, GLint z);
	typedef void (GLAD_API_PTR* PFNGLVERTEX3IVPROC)(const GLint* v);
	typedef void (GLAD_API_PTR* PFNGLVERTEX3SPROC)(GLshort x, GLshort y, GLshort z);
	typedef void (GLAD_API_PTR* PFNGLVERTEX3SVPROC)(const GLshort* v);
	typedef void (GLAD_API_PTR* PFNGLVERTEX4DPROC)(GLdouble x, GLdouble y, GLdouble z, GLdouble w);
	typedef void (GLAD_API_PTR* PFNGLVERTEX4DVPROC)(const GLdouble* v);
	typedef void (GLAD_API_PTR* PFNGLVERTEX4FPROC)(GLfloat x, GLfloat y, GLfloat z, GLfloat w);
	typedef void (GLAD_API_PTR* PFNGLVERTEX4FVPROC)(const GLfloat* v);
	typedef void (GLAD_API_PTR* PFNGLVERTEX4IPROC)(GLint x, GLint y, GLint z, GLint w);
	typedef void (GLAD_API_PTR* PFNGLVERTEX4IVPROC)(const GLint* v);
	typedef void (GLAD_API_PTR* PFNGLVERTEX4SPROC)(GLshort x, GLshort y, GLshort z, GLshort w);
	typedef void (GLAD_API_PTR* PFNGLVERTEX4SVPROC)(const GLshort* v);
	typedef void (GLAD_API_PTR* PFNGLVERTEXATTRIB1DPROC)(GLuint index, GLdouble x);
	typedef void (GLAD_API_PTR* PFNGLVERTEXATTRIB1DVPROC)(GLuint index, const GLdouble* v);
	typedef void (GLAD_API_PTR* PFNGLVERTEXATTRIB1FPROC)(GLuint index, GLfloat x);
	typedef void (GLAD_API_PTR* PFNGLVERTEXATTRIB1FVPROC)(GLuint index, const GLfloat* v);
	typedef void (GLAD_API_PTR* PFNGLVERTEXATTRIB1SPROC)(GLuint index, GLshort x);
	typedef void (GLAD_API_PTR* PFNGLVERTEXATTRIB1SVPROC)(GLuint index, const GLshort* v);
	typedef void (GLAD_API_PTR* PFNGLVERTEXATTRIB2DPROC)(GLuint index, GLdouble x, GLdouble y);
	typedef void (GLAD_API_PTR* PFNGLVERTEXATTRIB2DVPROC)(GLuint index, const GLdouble* v);
	typedef void (GLAD_API_PTR* PFNGLVERTEXATTRIB2FPROC)(GLuint index, GLfloat x, GLfloat y);
	typedef void (GLAD_API_PTR* PFNGLVERTEXATTRIB2FVPROC)(GLuint index, const GLfloat* v);
	typedef void (GLAD_API_PTR* PFNGLVERTEXATTRIB2SPROC)(GLuint index, GLshort x, GLshort y);
	typedef void (GLAD_API_PTR* PFNGLVERTEXATTRIB2SVPROC)(GLuint index, const GLshort* v);
	typedef void (GLAD_API_PTR* PFNGLVERTEXATTRIB3DPROC)(GLuint index, GLdouble x, GLdouble y, GLdouble z);
	typedef void (GLAD_API_PTR* PFNGLVERTEXATTRIB3DVPROC)(GLuint index, const GLdouble* v);
	typedef void (GLAD_API_PTR* PFNGLVERTEXATTRIB3FPROC)(GLuint index, GLfloat x, GLfloat y, GLfloat z);
	typedef void (GLAD_API_PTR* PFNGLVERTEXATTRIB3FVPROC)(GLuint index, const GLfloat* v);
	typedef void (GLAD_API_PTR* PFNGLVERTEXATTRIB3SPROC)(GLuint index, GLshort x, GLshort y, GLshort z);
	typedef void (GLAD_API_PTR* PFNGLVERTEXATTRIB3SVPROC)(GLuint index, const GLshort* v);
	typedef void (GLAD_API_PTR* PFNGLVERTEXATTRIB4NBVPROC)(GLuint index, const GLbyte* v);
	typedef void (GLAD_API_PTR* PFNGLVERTEXATTRIB4NIVPROC)(GLuint index, const GLint* v);
	typedef void (GLAD_API_PTR* PFNGLVERTEXATTRIB4NSVPROC)(GLuint index, const GLshort* v);
	typedef void (GLAD_API_PTR* PFNGLVERTEXATTRIB4NUBPROC)(GLuint index, GLubyte x, GLubyte y, GLubyte z, GLubyte w);
	typedef void (GLAD_API_PTR* PFNGLVERTEXATTRIB4NUBVPROC)(GLuint index, const GLubyte* v);
	typedef void (GLAD_API_PTR* PFNGLVERTEXATTRIB4NUIVPROC)(GLuint index, const GLuint* v);
	typedef void (GLAD_API_PTR* PFNGLVERTEXATTRIB4NUSVPROC)(GLuint index, const GLushort* v);
	typedef void (GLAD_API_PTR* PFNGLVERTEXATTRIB4BVPROC)(GLuint index, const GLbyte* v);
	typedef void (GLAD_API_PTR* PFNGLVERTEXATTRIB4DPROC)(GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
	typedef void (GLAD_API_PTR* PFNGLVERTEXATTRIB4DVPROC)(GLuint index, const GLdouble* v);
	typedef void (GLAD_API_PTR* PFNGLVERTEXATTRIB4FPROC)(GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
	typedef void (GLAD_API_PTR* PFNGLVERTEXATTRIB4FVPROC)(GLuint index, const GLfloat* v);
	typedef void (GLAD_API_PTR* PFNGLVERTEXATTRIB4IVPROC)(GLuint index, const GLint* v);
	typedef void (GLAD_API_PTR* PFNGLVERTEXATTRIB4SPROC)(GLuint index, GLshort x, GLshort y, GLshort z, GLshort w);
	typedef void (GLAD_API_PTR* PFNGLVERTEXATTRIB4SVPROC)(GLuint index, const GLshort* v);
	typedef void (GLAD_API_PTR* PFNGLVERTEXATTRIB4UBVPROC)(GLuint index, const GLubyte* v);
	typedef void (GLAD_API_PTR* PFNGLVERTEXATTRIB4UIVPROC)(GLuint index, const GLuint* v);
	typedef void (GLAD_API_PTR* PFNGLVERTEXATTRIB4USVPROC)(GLuint index, const GLushort* v);
	typedef void (GLAD_API_PTR* PFNGLVERTEXATTRIBDIVISORPROC)(GLuint index, GLuint divisor);
	typedef void (GLAD_API_PTR* PFNGLVERTEXATTRIBI1IPROC)(GLuint index, GLint x);
	typedef void (GLAD_API_PTR* PFNGLVERTEXATTRIBI1IVPROC)(GLuint index, const GLint* v);
	typedef void (GLAD_API_PTR* PFNGLVERTEXATTRIBI1UIPROC)(GLuint index, GLuint x);
	typedef void (GLAD_API_PTR* PFNGLVERTEXATTRIBI1UIVPROC)(GLuint index, const GLuint* v);
	typedef void (GLAD_API_PTR* PFNGLVERTEXATTRIBI2IPROC)(GLuint index, GLint x, GLint y);
	typedef void (GLAD_API_PTR* PFNGLVERTEXATTRIBI2IVPROC)(GLuint index, const GLint* v);
	typedef void (GLAD_API_PTR* PFNGLVERTEXATTRIBI2UIPROC)(GLuint index, GLuint x, GLuint y);
	typedef void (GLAD_API_PTR* PFNGLVERTEXATTRIBI2UIVPROC)(GLuint index, const GLuint* v);
	typedef void (GLAD_API_PTR* PFNGLVERTEXATTRIBI3IPROC)(GLuint index, GLint x, GLint y, GLint z);
	typedef void (GLAD_API_PTR* PFNGLVERTEXATTRIBI3IVPROC)(GLuint index, const GLint* v);
	typedef void (GLAD_API_PTR* PFNGLVERTEXATTRIBI3UIPROC)(GLuint index, GLuint x, GLuint y, GLuint z);
	typedef void (GLAD_API_PTR* PFNGLVERTEXATTRIBI3UIVPROC)(GLuint index, const GLuint* v);
	typedef void (GLAD_API_PTR* PFNGLVERTEXATTRIBI4BVPROC)(GLuint index, const GLbyte* v);
	typedef void (GLAD_API_PTR* PFNGLVERTEXATTRIBI4IPROC)(GLuint index, GLint x, GLint y, GLint z, GLint w);
	typedef void (GLAD_API_PTR* PFNGLVERTEXATTRIBI4IVPROC)(GLuint index, const GLint* v);
	typedef void (GLAD_API_PTR* PFNGLVERTEXATTRIBI4SVPROC)(GLuint index, const GLshort* v);
	typedef void (GLAD_API_PTR* PFNGLVERTEXATTRIBI4UBVPROC)(GLuint index, const GLubyte* v);
	typedef void (GLAD_API_PTR* PFNGLVERTEXATTRIBI4UIPROC)(GLuint index, GLuint x, GLuint y, GLuint z, GLuint w);
	typedef void (GLAD_API_PTR* PFNGLVERTEXATTRIBI4UIVPROC)(GLuint index, const GLuint* v);
	typedef void (GLAD_API_PTR* PFNGLVERTEXATTRIBI4USVPROC)(GLuint index, const GLushort* v);
	typedef void (GLAD_API_PTR* PFNGLVERTEXATTRIBIPOINTERPROC)(GLuint index, GLint size, GLenum type, GLsizei stride, const void* pointer);
	typedef void (GLAD_API_PTR* PFNGLVERTEXATTRIBP1UIPROC)(GLuint index, GLenum type, GLboolean normalized, GLuint value);
	typedef void (GLAD_API_PTR* PFNGLVERTEXATTRIBP1UIVPROC)(GLuint index, GLenum type, GLboolean normalized, const GLuint* value);
	typedef void (GLAD_API_PTR* PFNGLVERTEXATTRIBP2UIPROC)(GLuint index, GLenum type, GLboolean normalized, GLuint value);
	typedef void (GLAD_API_PTR* PFNGLVERTEXATTRIBP2UIVPROC)(GLuint index, GLenum type, GLboolean normalized, const GLuint* value);
	typedef void (GLAD_API_PTR* PFNGLVERTEXATTRIBP3UIPROC)(GLuint index, GLenum type, GLboolean normalized, GLuint value);
	typedef void (GLAD_API_PTR* PFNGLVERTEXATTRIBP3UIVPROC)(GLuint index, GLenum type, GLboolean normalized, const GLuint* value);
	typedef void (GLAD_API_PTR* PFNGLVERTEXATTRIBP4UIPROC)(GLuint index, GLenum type, GLboolean normalized, GLuint value);
	typedef void (GLAD_API_PTR* PFNGLVERTEXATTRIBP4UIVPROC)(GLuint index, GLenum type, GLboolean normalized, const GLuint* value);
	typedef void (GLAD_API_PTR* PFNGLVERTEXATTRIBPOINTERPROC)(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer);
	typedef void (GLAD_API_PTR* PFNGLVERTEXP2UIPROC)(GLenum type, GLuint value);
	typedef void (GLAD_API_PTR* PFNGLVERTEXP2UIVPROC)(GLenum type, const GLuint* value);
	typedef void (GLAD_API_PTR* PFNGLVERTEXP3UIPROC)(GLenum type, GLuint value);
	typedef void (GLAD_API_PTR* PFNGLVERTEXP3UIVPROC)(GLenum type, const GLuint* value);
	typedef void (GLAD_API_PTR* PFNGLVERTEXP4UIPROC)(GLenum type, GLuint value);
	typedef void (GLAD_API_PTR* PFNGLVERTEXP4UIVPROC)(GLenum type, const GLuint* value);
	typedef void (GLAD_API_PTR* PFNGLVERTEXPOINTERPROC)(GLint size, GLenum type, GLsizei stride, const void* pointer);
	typedef void (GLAD_API_PTR* PFNGLVIEWPORTPROC)(GLint x, GLint y, GLsizei width, GLsizei height);
	typedef void (GLAD_API_PTR* PFNGLWAITSYNCPROC)(GLsync sync, GLbitfield flags, GLuint64 timeout);
	typedef void (GLAD_API_PTR* PFNGLWINDOWPOS2DPROC)(GLdouble x, GLdouble y);
	typedef void (GLAD_API_PTR* PFNGLWINDOWPOS2DVPROC)(const GLdouble* v);
	typedef void (GLAD_API_PTR* PFNGLWINDOWPOS2FPROC)(GLfloat x, GLfloat y);
	typedef void (GLAD_API_PTR* PFNGLWINDOWPOS2FVPROC)(const GLfloat* v);
	typedef void (GLAD_API_PTR* PFNGLWINDOWPOS2IPROC)(GLint x, GLint y);
	typedef void (GLAD_API_PTR* PFNGLWINDOWPOS2IVPROC)(const GLint* v);
	typedef void (GLAD_API_PTR* PFNGLWINDOWPOS2SPROC)(GLshort x, GLshort y);
	typedef void (GLAD_API_PTR* PFNGLWINDOWPOS2SVPROC)(const GLshort* v);
	typedef void (GLAD_API_PTR* PFNGLWINDOWPOS3DPROC)(GLdouble x, GLdouble y, GLdouble z);
	typedef void (GLAD_API_PTR* PFNGLWINDOWPOS3DVPROC)(const GLdouble* v);
	typedef void (GLAD_API_PTR* PFNGLWINDOWPOS3FPROC)(GLfloat x, GLfloat y, GLfloat z);
	typedef void (GLAD_API_PTR* PFNGLWINDOWPOS3FVPROC)(const GLfloat* v);
	typedef void (GLAD_API_PTR* PFNGLWINDOWPOS3IPROC)(GLint x, GLint y, GLint z);
	typedef void (GLAD_API_PTR* PFNGLWINDOWPOS3IVPROC)(const GLint* v);
	typedef void (GLAD_API_PTR* PFNGLWINDOWPOS3SPROC)(GLshort x, GLshort y, GLshort z);
	typedef void (GLAD_API_PTR* PFNGLWINDOWPOS3SVPROC)(const GLshort* v);

	GLAD_API_CALL PFNGLACCUMPROC glad_glAccum;
#define glAccum glad_glAccum
	GLAD_API_CALL PFNGLACTIVETEXTUREPROC glad_glActiveTexture;
#define glActiveTexture glad_glActiveTexture
	GLAD_API_CALL PFNGLALPHAFUNCPROC glad_glAlphaFunc;
#define glAlphaFunc glad_glAlphaFunc
	GLAD_API_CALL PFNGLARETEXTURESRESIDENTPROC glad_glAreTexturesResident;
#define glAreTexturesResident glad_glAreTexturesResident
	GLAD_API_CALL PFNGLARRAYELEMENTPROC glad_glArrayElement;
#define glArrayElement glad_glArrayElement
	GLAD_API_CALL PFNGLATTACHSHADERPROC glad_glAttachShader;
#define glAttachShader glad_glAttachShader
	GLAD_API_CALL PFNGLBEGINPROC glad_glBegin;
#define glBegin glad_glBegin
	GLAD_API_CALL PFNGLBEGINCONDITIONALRENDERPROC glad_glBeginConditionalRender;
#define glBeginConditionalRender glad_glBeginConditionalRender
	GLAD_API_CALL PFNGLBEGINQUERYPROC glad_glBeginQuery;
#define glBeginQuery glad_glBeginQuery
	GLAD_API_CALL PFNGLBEGINTRANSFORMFEEDBACKPROC glad_glBeginTransformFeedback;
#define glBeginTransformFeedback glad_glBeginTransformFeedback
	GLAD_API_CALL PFNGLBINDATTRIBLOCATIONPROC glad_glBindAttribLocation;
#define glBindAttribLocation glad_glBindAttribLocation
	GLAD_API_CALL PFNGLBINDBUFFERPROC glad_glBindBuffer;
#define glBindBuffer glad_glBindBuffer
	GLAD_API_CALL PFNGLBINDBUFFERBASEPROC glad_glBindBufferBase;
#define glBindBufferBase glad_glBindBufferBase
	GLAD_API_CALL PFNGLBINDBUFFERRANGEPROC glad_glBindBufferRange;
#define glBindBufferRange glad_glBindBufferRange
	GLAD_API_CALL PFNGLBINDFRAGDATALOCATIONPROC glad_glBindFragDataLocation;
#define glBindFragDataLocation glad_glBindFragDataLocation
	GLAD_API_CALL PFNGLBINDFRAGDATALOCATIONINDEXEDPROC glad_glBindFragDataLocationIndexed;
#define glBindFragDataLocationIndexed glad_glBindFragDataLocationIndexed
	GLAD_API_CALL PFNGLBINDFRAMEBUFFERPROC glad_glBindFramebuffer;
#define glBindFramebuffer glad_glBindFramebuffer
	GLAD_API_CALL PFNGLBINDRENDERBUFFERPROC glad_glBindRenderbuffer;
#define glBindRenderbuffer glad_glBindRenderbuffer
	GLAD_API_CALL PFNGLBINDSAMPLERPROC glad_glBindSampler;
#define glBindSampler glad_glBindSampler
	GLAD_API_CALL PFNGLBINDTEXTUREPROC glad_glBindTexture;
#define glBindTexture glad_glBindTexture
	GLAD_API_CALL PFNGLBINDVERTEXARRAYPROC glad_glBindVertexArray;
#define glBindVertexArray glad_glBindVertexArray
	GLAD_API_CALL PFNGLBITMAPPROC glad_glBitmap;
#define glBitmap glad_glBitmap
	GLAD_API_CALL PFNGLBLENDCOLORPROC glad_glBlendColor;
#define glBlendColor glad_glBlendColor
	GLAD_API_CALL PFNGLBLENDEQUATIONPROC glad_glBlendEquation;
#define glBlendEquation glad_glBlendEquation
	GLAD_API_CALL PFNGLBLENDEQUATIONSEPARATEPROC glad_glBlendEquationSeparate;
#define glBlendEquationSeparate glad_glBlendEquationSeparate
	GLAD_API_CALL PFNGLBLENDFUNCPROC glad_glBlendFunc;
#define glBlendFunc glad_glBlendFunc
	GLAD_API_CALL PFNGLBLENDFUNCSEPARATEPROC glad_glBlendFuncSeparate;
#define glBlendFuncSeparate glad_glBlendFuncSeparate
	GLAD_API_CALL PFNGLBLITFRAMEBUFFERPROC glad_glBlitFramebuffer;
#define glBlitFramebuffer glad_glBlitFramebuffer
	GLAD_API_CALL PFNGLBUFFERDATAPROC glad_glBufferData;
#define glBufferData glad_glBufferData
	GLAD_API_CALL PFNGLBUFFERSUBDATAPROC glad_glBufferSubData;
#define glBufferSubData glad_glBufferSubData
	GLAD_API_CALL PFNGLCALLLISTPROC glad_glCallList;
#define glCallList glad_glCallList
	GLAD_API_CALL PFNGLCALLLISTSPROC glad_glCallLists;
#define glCallLists glad_glCallLists
	GLAD_API_CALL PFNGLCHECKFRAMEBUFFERSTATUSPROC glad_glCheckFramebufferStatus;
#define glCheckFramebufferStatus glad_glCheckFramebufferStatus
	GLAD_API_CALL PFNGLCLAMPCOLORPROC glad_glClampColor;
#define glClampColor glad_glClampColor
	GLAD_API_CALL PFNGLCLEARPROC glad_glClear;
#define glClear glad_glClear
	GLAD_API_CALL PFNGLCLEARACCUMPROC glad_glClearAccum;
#define glClearAccum glad_glClearAccum
	GLAD_API_CALL PFNGLCLEARBUFFERFIPROC glad_glClearBufferfi;
#define glClearBufferfi glad_glClearBufferfi
	GLAD_API_CALL PFNGLCLEARBUFFERFVPROC glad_glClearBufferfv;
#define glClearBufferfv glad_glClearBufferfv
	GLAD_API_CALL PFNGLCLEARBUFFERIVPROC glad_glClearBufferiv;
#define glClearBufferiv glad_glClearBufferiv
	GLAD_API_CALL PFNGLCLEARBUFFERUIVPROC glad_glClearBufferuiv;
#define glClearBufferuiv glad_glClearBufferuiv
	GLAD_API_CALL PFNGLCLEARCOLORPROC glad_glClearColor;
#define glClearColor glad_glClearColor
	GLAD_API_CALL PFNGLCLEARDEPTHPROC glad_glClearDepth;
#define glClearDepth glad_glClearDepth
	GLAD_API_CALL PFNGLCLEARINDEXPROC glad_glClearIndex;
#define glClearIndex glad_glClearIndex
	GLAD_API_CALL PFNGLCLEARSTENCILPROC glad_glClearStencil;
#define glClearStencil glad_glClearStencil
	GLAD_API_CALL PFNGLCLIENTACTIVETEXTUREPROC glad_glClientActiveTexture;
#define glClientActiveTexture glad_glClientActiveTexture
	GLAD_API_CALL PFNGLCLIENTWAITSYNCPROC glad_glClientWaitSync;
#define glClientWaitSync glad_glClientWaitSync
	GLAD_API_CALL PFNGLCLIPPLANEPROC glad_glClipPlane;
#define glClipPlane glad_glClipPlane
	GLAD_API_CALL PFNGLCOLOR3BPROC glad_glColor3b;
#define glColor3b glad_glColor3b
	GLAD_API_CALL PFNGLCOLOR3BVPROC glad_glColor3bv;
#define glColor3bv glad_glColor3bv
	GLAD_API_CALL PFNGLCOLOR3DPROC glad_glColor3d;
#define glColor3d glad_glColor3d
	GLAD_API_CALL PFNGLCOLOR3DVPROC glad_glColor3dv;
#define glColor3dv glad_glColor3dv
	GLAD_API_CALL PFNGLCOLOR3FPROC glad_glColor3f;
#define glColor3f glad_glColor3f
	GLAD_API_CALL PFNGLCOLOR3FVPROC glad_glColor3fv;
#define glColor3fv glad_glColor3fv
	GLAD_API_CALL PFNGLCOLOR3IPROC glad_glColor3i;
#define glColor3i glad_glColor3i
	GLAD_API_CALL PFNGLCOLOR3IVPROC glad_glColor3iv;
#define glColor3iv glad_glColor3iv
	GLAD_API_CALL PFNGLCOLOR3SPROC glad_glColor3s;
#define glColor3s glad_glColor3s
	GLAD_API_CALL PFNGLCOLOR3SVPROC glad_glColor3sv;
#define glColor3sv glad_glColor3sv
	GLAD_API_CALL PFNGLCOLOR3UBPROC glad_glColor3ub;
#define glColor3ub glad_glColor3ub
	GLAD_API_CALL PFNGLCOLOR3UBVPROC glad_glColor3ubv;
#define glColor3ubv glad_glColor3ubv
	GLAD_API_CALL PFNGLCOLOR3UIPROC glad_glColor3ui;
#define glColor3ui glad_glColor3ui
	GLAD_API_CALL PFNGLCOLOR3UIVPROC glad_glColor3uiv;
#define glColor3uiv glad_glColor3uiv
	GLAD_API_CALL PFNGLCOLOR3USPROC glad_glColor3us;
#define glColor3us glad_glColor3us
	GLAD_API_CALL PFNGLCOLOR3USVPROC glad_glColor3usv;
#define glColor3usv glad_glColor3usv
	GLAD_API_CALL PFNGLCOLOR4BPROC glad_glColor4b;
#define glColor4b glad_glColor4b
	GLAD_API_CALL PFNGLCOLOR4BVPROC glad_glColor4bv;
#define glColor4bv glad_glColor4bv
	GLAD_API_CALL PFNGLCOLOR4DPROC glad_glColor4d;
#define glColor4d glad_glColor4d
	GLAD_API_CALL PFNGLCOLOR4DVPROC glad_glColor4dv;
#define glColor4dv glad_glColor4dv
	GLAD_API_CALL PFNGLCOLOR4FPROC glad_glColor4f;
#define glColor4f glad_glColor4f
	GLAD_API_CALL PFNGLCOLOR4FVPROC glad_glColor4fv;
#define glColor4fv glad_glColor4fv
	GLAD_API_CALL PFNGLCOLOR4IPROC glad_glColor4i;
#define glColor4i glad_glColor4i
	GLAD_API_CALL PFNGLCOLOR4IVPROC glad_glColor4iv;
#define glColor4iv glad_glColor4iv
	GLAD_API_CALL PFNGLCOLOR4SPROC glad_glColor4s;
#define glColor4s glad_glColor4s
	GLAD_API_CALL PFNGLCOLOR4SVPROC glad_glColor4sv;
#define glColor4sv glad_glColor4sv
	GLAD_API_CALL PFNGLCOLOR4UBPROC glad_glColor4ub;
#define glColor4ub glad_glColor4ub
	GLAD_API_CALL PFNGLCOLOR4UBVPROC glad_glColor4ubv;
#define glColor4ubv glad_glColor4ubv
	GLAD_API_CALL PFNGLCOLOR4UIPROC glad_glColor4ui;
#define glColor4ui glad_glColor4ui
	GLAD_API_CALL PFNGLCOLOR4UIVPROC glad_glColor4uiv;
#define glColor4uiv glad_glColor4uiv
	GLAD_API_CALL PFNGLCOLOR4USPROC glad_glColor4us;
#define glColor4us glad_glColor4us
	GLAD_API_CALL PFNGLCOLOR4USVPROC glad_glColor4usv;
#define glColor4usv glad_glColor4usv
	GLAD_API_CALL PFNGLCOLORMASKPROC glad_glColorMask;
#define glColorMask glad_glColorMask
	GLAD_API_CALL PFNGLCOLORMASKIPROC glad_glColorMaski;
#define glColorMaski glad_glColorMaski
	GLAD_API_CALL PFNGLCOLORMATERIALPROC glad_glColorMaterial;
#define glColorMaterial glad_glColorMaterial
	GLAD_API_CALL PFNGLCOLORP3UIPROC glad_glColorP3ui;
#define glColorP3ui glad_glColorP3ui
	GLAD_API_CALL PFNGLCOLORP3UIVPROC glad_glColorP3uiv;
#define glColorP3uiv glad_glColorP3uiv
	GLAD_API_CALL PFNGLCOLORP4UIPROC glad_glColorP4ui;
#define glColorP4ui glad_glColorP4ui
	GLAD_API_CALL PFNGLCOLORP4UIVPROC glad_glColorP4uiv;
#define glColorP4uiv glad_glColorP4uiv
	GLAD_API_CALL PFNGLCOLORPOINTERPROC glad_glColorPointer;
#define glColorPointer glad_glColorPointer
	GLAD_API_CALL PFNGLCOMPILESHADERPROC glad_glCompileShader;
#define glCompileShader glad_glCompileShader
	GLAD_API_CALL PFNGLCOMPRESSEDTEXIMAGE1DPROC glad_glCompressedTexImage1D;
#define glCompressedTexImage1D glad_glCompressedTexImage1D
	GLAD_API_CALL PFNGLCOMPRESSEDTEXIMAGE2DPROC glad_glCompressedTexImage2D;
#define glCompressedTexImage2D glad_glCompressedTexImage2D
	GLAD_API_CALL PFNGLCOMPRESSEDTEXIMAGE3DPROC glad_glCompressedTexImage3D;
#define glCompressedTexImage3D glad_glCompressedTexImage3D
	GLAD_API_CALL PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC glad_glCompressedTexSubImage1D;
#define glCompressedTexSubImage1D glad_glCompressedTexSubImage1D
	GLAD_API_CALL PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC glad_glCompressedTexSubImage2D;
#define glCompressedTexSubImage2D glad_glCompressedTexSubImage2D
	GLAD_API_CALL PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC glad_glCompressedTexSubImage3D;
#define glCompressedTexSubImage3D glad_glCompressedTexSubImage3D
	GLAD_API_CALL PFNGLCOPYBUFFERSUBDATAPROC glad_glCopyBufferSubData;
#define glCopyBufferSubData glad_glCopyBufferSubData
	GLAD_API_CALL PFNGLCOPYPIXELSPROC glad_glCopyPixels;
#define glCopyPixels glad_glCopyPixels
	GLAD_API_CALL PFNGLCOPYTEXIMAGE1DPROC glad_glCopyTexImage1D;
#define glCopyTexImage1D glad_glCopyTexImage1D
	GLAD_API_CALL PFNGLCOPYTEXIMAGE2DPROC glad_glCopyTexImage2D;
#define glCopyTexImage2D glad_glCopyTexImage2D
	GLAD_API_CALL PFNGLCOPYTEXSUBIMAGE1DPROC glad_glCopyTexSubImage1D;
#define glCopyTexSubImage1D glad_glCopyTexSubImage1D
	GLAD_API_CALL PFNGLCOPYTEXSUBIMAGE2DPROC glad_glCopyTexSubImage2D;
#define glCopyTexSubImage2D glad_glCopyTexSubImage2D
	GLAD_API_CALL PFNGLCOPYTEXSUBIMAGE3DPROC glad_glCopyTexSubImage3D;
#define glCopyTexSubImage3D glad_glCopyTexSubImage3D
	GLAD_API_CALL PFNGLCREATEPROGRAMPROC glad_glCreateProgram;
#define glCreateProgram glad_glCreateProgram
	GLAD_API_CALL PFNGLCREATESHADERPROC glad_glCreateShader;
#define glCreateShader glad_glCreateShader
	GLAD_API_CALL PFNGLCULLFACEPROC glad_glCullFace;
#define glCullFace glad_glCullFace
	GLAD_API_CALL PFNGLDELETEBUFFERSPROC glad_glDeleteBuffers;
#define glDeleteBuffers glad_glDeleteBuffers
	GLAD_API_CALL PFNGLDELETEFRAMEBUFFERSPROC glad_glDeleteFramebuffers;
#define glDeleteFramebuffers glad_glDeleteFramebuffers
	GLAD_API_CALL PFNGLDELETELISTSPROC glad_glDeleteLists;
#define glDeleteLists glad_glDeleteLists
	GLAD_API_CALL PFNGLDELETEPROGRAMPROC glad_glDeleteProgram;
#define glDeleteProgram glad_glDeleteProgram
	GLAD_API_CALL PFNGLDELETEQUERIESPROC glad_glDeleteQueries;
#define glDeleteQueries glad_glDeleteQueries
	GLAD_API_CALL PFNGLDELETERENDERBUFFERSPROC glad_glDeleteRenderbuffers;
#define glDeleteRenderbuffers glad_glDeleteRenderbuffers
	GLAD_API_CALL PFNGLDELETESAMPLERSPROC glad_glDeleteSamplers;
#define glDeleteSamplers glad_glDeleteSamplers
	GLAD_API_CALL PFNGLDELETESHADERPROC glad_glDeleteShader;
#define glDeleteShader glad_glDeleteShader
	GLAD_API_CALL PFNGLDELETESYNCPROC glad_glDeleteSync;
#define glDeleteSync glad_glDeleteSync
	GLAD_API_CALL PFNGLDELETETEXTURESPROC glad_glDeleteTextures;
#define glDeleteTextures glad_glDeleteTextures
	GLAD_API_CALL PFNGLDELETEVERTEXARRAYSPROC glad_glDeleteVertexArrays;
#define glDeleteVertexArrays glad_glDeleteVertexArrays
	GLAD_API_CALL PFNGLDEPTHFUNCPROC glad_glDepthFunc;
#define glDepthFunc glad_glDepthFunc
	GLAD_API_CALL PFNGLDEPTHMASKPROC glad_glDepthMask;
#define glDepthMask glad_glDepthMask
	GLAD_API_CALL PFNGLDEPTHRANGEPROC glad_glDepthRange;
#define glDepthRange glad_glDepthRange
	GLAD_API_CALL PFNGLDETACHSHADERPROC glad_glDetachShader;
#define glDetachShader glad_glDetachShader
	GLAD_API_CALL PFNGLDISABLEPROC glad_glDisable;
#define glDisable glad_glDisable
	GLAD_API_CALL PFNGLDISABLECLIENTSTATEPROC glad_glDisableClientState;
#define glDisableClientState glad_glDisableClientState
	GLAD_API_CALL PFNGLDISABLEVERTEXATTRIBARRAYPROC glad_glDisableVertexAttribArray;
#define glDisableVertexAttribArray glad_glDisableVertexAttribArray
	GLAD_API_CALL PFNGLDISABLEIPROC glad_glDisablei;
#define glDisablei glad_glDisablei
	GLAD_API_CALL PFNGLDRAWARRAYSPROC glad_glDrawArrays;
#define glDrawArrays glad_glDrawArrays
	GLAD_API_CALL PFNGLDRAWARRAYSINSTANCEDPROC glad_glDrawArraysInstanced;
#define glDrawArraysInstanced glad_glDrawArraysInstanced
	GLAD_API_CALL PFNGLDRAWBUFFERPROC glad_glDrawBuffer;
#define glDrawBuffer glad_glDrawBuffer
	GLAD_API_CALL PFNGLDRAWBUFFERSPROC glad_glDrawBuffers;
#define glDrawBuffers glad_glDrawBuffers
	GLAD_API_CALL PFNGLDRAWELEMENTSPROC glad_glDrawElements;
#define glDrawElements glad_glDrawElements
	GLAD_API_CALL PFNGLDRAWELEMENTSBASEVERTEXPROC glad_glDrawElementsBaseVertex;
#define glDrawElementsBaseVertex glad_glDrawElementsBaseVertex
	GLAD_API_CALL PFNGLDRAWELEMENTSINSTANCEDPROC glad_glDrawElementsInstanced;
#define glDrawElementsInstanced glad_glDrawElementsInstanced
	GLAD_API_CALL PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXPROC glad_glDrawElementsInstancedBaseVertex;
#define glDrawElementsInstancedBaseVertex glad_glDrawElementsInstancedBaseVertex
	GLAD_API_CALL PFNGLDRAWPIXELSPROC glad_glDrawPixels;
#define glDrawPixels glad_glDrawPixels
	GLAD_API_CALL PFNGLDRAWRANGEELEMENTSPROC glad_glDrawRangeElements;
#define glDrawRangeElements glad_glDrawRangeElements
	GLAD_API_CALL PFNGLDRAWRANGEELEMENTSBASEVERTEXPROC glad_glDrawRangeElementsBaseVertex;
#define glDrawRangeElementsBaseVertex glad_glDrawRangeElementsBaseVertex
	GLAD_API_CALL PFNGLEDGEFLAGPROC glad_glEdgeFlag;
#define glEdgeFlag glad_glEdgeFlag
	GLAD_API_CALL PFNGLEDGEFLAGPOINTERPROC glad_glEdgeFlagPointer;
#define glEdgeFlagPointer glad_glEdgeFlagPointer
	GLAD_API_CALL PFNGLEDGEFLAGVPROC glad_glEdgeFlagv;
#define glEdgeFlagv glad_glEdgeFlagv
	GLAD_API_CALL PFNGLENABLEPROC glad_glEnable;
#define glEnable glad_glEnable
	GLAD_API_CALL PFNGLENABLECLIENTSTATEPROC glad_glEnableClientState;
#define glEnableClientState glad_glEnableClientState
	GLAD_API_CALL PFNGLENABLEVERTEXATTRIBARRAYPROC glad_glEnableVertexAttribArray;
#define glEnableVertexAttribArray glad_glEnableVertexAttribArray
	GLAD_API_CALL PFNGLENABLEIPROC glad_glEnablei;
#define glEnablei glad_glEnablei
	GLAD_API_CALL PFNGLENDPROC glad_glEnd;
#define glEnd glad_glEnd
	GLAD_API_CALL PFNGLENDCONDITIONALRENDERPROC glad_glEndConditionalRender;
#define glEndConditionalRender glad_glEndConditionalRender
	GLAD_API_CALL PFNGLENDLISTPROC glad_glEndList;
#define glEndList glad_glEndList
	GLAD_API_CALL PFNGLENDQUERYPROC glad_glEndQuery;
#define glEndQuery glad_glEndQuery
	GLAD_API_CALL PFNGLENDTRANSFORMFEEDBACKPROC glad_glEndTransformFeedback;
#define glEndTransformFeedback glad_glEndTransformFeedback
	GLAD_API_CALL PFNGLEVALCOORD1DPROC glad_glEvalCoord1d;
#define glEvalCoord1d glad_glEvalCoord1d
	GLAD_API_CALL PFNGLEVALCOORD1DVPROC glad_glEvalCoord1dv;
#define glEvalCoord1dv glad_glEvalCoord1dv
	GLAD_API_CALL PFNGLEVALCOORD1FPROC glad_glEvalCoord1f;
#define glEvalCoord1f glad_glEvalCoord1f
	GLAD_API_CALL PFNGLEVALCOORD1FVPROC glad_glEvalCoord1fv;
#define glEvalCoord1fv glad_glEvalCoord1fv
	GLAD_API_CALL PFNGLEVALCOORD2DPROC glad_glEvalCoord2d;
#define glEvalCoord2d glad_glEvalCoord2d
	GLAD_API_CALL PFNGLEVALCOORD2DVPROC glad_glEvalCoord2dv;
#define glEvalCoord2dv glad_glEvalCoord2dv
	GLAD_API_CALL PFNGLEVALCOORD2FPROC glad_glEvalCoord2f;
#define glEvalCoord2f glad_glEvalCoord2f
	GLAD_API_CALL PFNGLEVALCOORD2FVPROC glad_glEvalCoord2fv;
#define glEvalCoord2fv glad_glEvalCoord2fv
	GLAD_API_CALL PFNGLEVALMESH1PROC glad_glEvalMesh1;
#define glEvalMesh1 glad_glEvalMesh1
	GLAD_API_CALL PFNGLEVALMESH2PROC glad_glEvalMesh2;
#define glEvalMesh2 glad_glEvalMesh2
	GLAD_API_CALL PFNGLEVALPOINT1PROC glad_glEvalPoint1;
#define glEvalPoint1 glad_glEvalPoint1
	GLAD_API_CALL PFNGLEVALPOINT2PROC glad_glEvalPoint2;
#define glEvalPoint2 glad_glEvalPoint2
	GLAD_API_CALL PFNGLFEEDBACKBUFFERPROC glad_glFeedbackBuffer;
#define glFeedbackBuffer glad_glFeedbackBuffer
	GLAD_API_CALL PFNGLFENCESYNCPROC glad_glFenceSync;
#define glFenceSync glad_glFenceSync
	GLAD_API_CALL PFNGLFINISHPROC glad_glFinish;
#define glFinish glad_glFinish
	GLAD_API_CALL PFNGLFLUSHPROC glad_glFlush;
#define glFlush glad_glFlush
	GLAD_API_CALL PFNGLFLUSHMAPPEDBUFFERRANGEPROC glad_glFlushMappedBufferRange;
#define glFlushMappedBufferRange glad_glFlushMappedBufferRange
	GLAD_API_CALL PFNGLFOGCOORDPOINTERPROC glad_glFogCoordPointer;
#define glFogCoordPointer glad_glFogCoordPointer
	GLAD_API_CALL PFNGLFOGCOORDDPROC glad_glFogCoordd;
#define glFogCoordd glad_glFogCoordd
	GLAD_API_CALL PFNGLFOGCOORDDVPROC glad_glFogCoorddv;
#define glFogCoorddv glad_glFogCoorddv
	GLAD_API_CALL PFNGLFOGCOORDFPROC glad_glFogCoordf;
#define glFogCoordf glad_glFogCoordf
	GLAD_API_CALL PFNGLFOGCOORDFVPROC glad_glFogCoordfv;
#define glFogCoordfv glad_glFogCoordfv
	GLAD_API_CALL PFNGLFOGFPROC glad_glFogf;
#define glFogf glad_glFogf
	GLAD_API_CALL PFNGLFOGFVPROC glad_glFogfv;
#define glFogfv glad_glFogfv
	GLAD_API_CALL PFNGLFOGIPROC glad_glFogi;
#define glFogi glad_glFogi
	GLAD_API_CALL PFNGLFOGIVPROC glad_glFogiv;
#define glFogiv glad_glFogiv
	GLAD_API_CALL PFNGLFRAMEBUFFERRENDERBUFFERPROC glad_glFramebufferRenderbuffer;
#define glFramebufferRenderbuffer glad_glFramebufferRenderbuffer
	GLAD_API_CALL PFNGLFRAMEBUFFERTEXTUREPROC glad_glFramebufferTexture;
#define glFramebufferTexture glad_glFramebufferTexture
	GLAD_API_CALL PFNGLFRAMEBUFFERTEXTURE1DPROC glad_glFramebufferTexture1D;
#define glFramebufferTexture1D glad_glFramebufferTexture1D
	GLAD_API_CALL PFNGLFRAMEBUFFERTEXTURE2DPROC glad_glFramebufferTexture2D;
#define glFramebufferTexture2D glad_glFramebufferTexture2D
	GLAD_API_CALL PFNGLFRAMEBUFFERTEXTURE3DPROC glad_glFramebufferTexture3D;
#define glFramebufferTexture3D glad_glFramebufferTexture3D
	GLAD_API_CALL PFNGLFRAMEBUFFERTEXTURELAYERPROC glad_glFramebufferTextureLayer;
#define glFramebufferTextureLayer glad_glFramebufferTextureLayer
	GLAD_API_CALL PFNGLFRONTFACEPROC glad_glFrontFace;
#define glFrontFace glad_glFrontFace
	GLAD_API_CALL PFNGLFRUSTUMPROC glad_glFrustum;
#define glFrustum glad_glFrustum
	GLAD_API_CALL PFNGLGENBUFFERSPROC glad_glGenBuffers;
#define glGenBuffers glad_glGenBuffers
	GLAD_API_CALL PFNGLGENFRAMEBUFFERSPROC glad_glGenFramebuffers;
#define glGenFramebuffers glad_glGenFramebuffers
	GLAD_API_CALL PFNGLGENLISTSPROC glad_glGenLists;
#define glGenLists glad_glGenLists
	GLAD_API_CALL PFNGLGENQUERIESPROC glad_glGenQueries;
#define glGenQueries glad_glGenQueries
	GLAD_API_CALL PFNGLGENRENDERBUFFERSPROC glad_glGenRenderbuffers;
#define glGenRenderbuffers glad_glGenRenderbuffers
	GLAD_API_CALL PFNGLGENSAMPLERSPROC glad_glGenSamplers;
#define glGenSamplers glad_glGenSamplers
	GLAD_API_CALL PFNGLGENTEXTURESPROC glad_glGenTextures;
#define glGenTextures glad_glGenTextures
	GLAD_API_CALL PFNGLGENVERTEXARRAYSPROC glad_glGenVertexArrays;
#define glGenVertexArrays glad_glGenVertexArrays
	GLAD_API_CALL PFNGLGENERATEMIPMAPPROC glad_glGenerateMipmap;
#define glGenerateMipmap glad_glGenerateMipmap
	GLAD_API_CALL PFNGLGETACTIVEATTRIBPROC glad_glGetActiveAttrib;
#define glGetActiveAttrib glad_glGetActiveAttrib
	GLAD_API_CALL PFNGLGETACTIVEUNIFORMPROC glad_glGetActiveUniform;
#define glGetActiveUniform glad_glGetActiveUniform
	GLAD_API_CALL PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC glad_glGetActiveUniformBlockName;
#define glGetActiveUniformBlockName glad_glGetActiveUniformBlockName
	GLAD_API_CALL PFNGLGETACTIVEUNIFORMBLOCKIVPROC glad_glGetActiveUniformBlockiv;
#define glGetActiveUniformBlockiv glad_glGetActiveUniformBlockiv
	GLAD_API_CALL PFNGLGETACTIVEUNIFORMNAMEPROC glad_glGetActiveUniformName;
#define glGetActiveUniformName glad_glGetActiveUniformName
	GLAD_API_CALL PFNGLGETACTIVEUNIFORMSIVPROC glad_glGetActiveUniformsiv;
#define glGetActiveUniformsiv glad_glGetActiveUniformsiv
	GLAD_API_CALL PFNGLGETATTACHEDSHADERSPROC glad_glGetAttachedShaders;
#define glGetAttachedShaders glad_glGetAttachedShaders
	GLAD_API_CALL PFNGLGETATTRIBLOCATIONPROC glad_glGetAttribLocation;
#define glGetAttribLocation glad_glGetAttribLocation
	GLAD_API_CALL PFNGLGETBOOLEANI_VPROC glad_glGetBooleani_v;
#define glGetBooleani_v glad_glGetBooleani_v
	GLAD_API_CALL PFNGLGETBOOLEANVPROC glad_glGetBooleanv;
#define glGetBooleanv glad_glGetBooleanv
	GLAD_API_CALL PFNGLGETBUFFERPARAMETERI64VPROC glad_glGetBufferParameteri64v;
#define glGetBufferParameteri64v glad_glGetBufferParameteri64v
	GLAD_API_CALL PFNGLGETBUFFERPARAMETERIVPROC glad_glGetBufferParameteriv;
#define glGetBufferParameteriv glad_glGetBufferParameteriv
	GLAD_API_CALL PFNGLGETBUFFERPOINTERVPROC glad_glGetBufferPointerv;
#define glGetBufferPointerv glad_glGetBufferPointerv
	GLAD_API_CALL PFNGLGETBUFFERSUBDATAPROC glad_glGetBufferSubData;
#define glGetBufferSubData glad_glGetBufferSubData
	GLAD_API_CALL PFNGLGETCLIPPLANEPROC glad_glGetClipPlane;
#define glGetClipPlane glad_glGetClipPlane
	GLAD_API_CALL PFNGLGETCOMPRESSEDTEXIMAGEPROC glad_glGetCompressedTexImage;
#define glGetCompressedTexImage glad_glGetCompressedTexImage
	GLAD_API_CALL PFNGLGETDOUBLEVPROC glad_glGetDoublev;
#define glGetDoublev glad_glGetDoublev
	GLAD_API_CALL PFNGLGETERRORPROC glad_glGetError;
#define glGetError glad_glGetError
	GLAD_API_CALL PFNGLGETFLOATVPROC glad_glGetFloatv;
#define glGetFloatv glad_glGetFloatv
	GLAD_API_CALL PFNGLGETFRAGDATAINDEXPROC glad_glGetFragDataIndex;
#define glGetFragDataIndex glad_glGetFragDataIndex
	GLAD_API_CALL PFNGLGETFRAGDATALOCATIONPROC glad_glGetFragDataLocation;
#define glGetFragDataLocation glad_glGetFragDataLocation
	GLAD_API_CALL PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC glad_glGetFramebufferAttachmentParameteriv;
#define glGetFramebufferAttachmentParameteriv glad_glGetFramebufferAttachmentParameteriv
	GLAD_API_CALL PFNGLGETINTEGER64I_VPROC glad_glGetInteger64i_v;
#define glGetInteger64i_v glad_glGetInteger64i_v
	GLAD_API_CALL PFNGLGETINTEGER64VPROC glad_glGetInteger64v;
#define glGetInteger64v glad_glGetInteger64v
	GLAD_API_CALL PFNGLGETINTEGERI_VPROC glad_glGetIntegeri_v;
#define glGetIntegeri_v glad_glGetIntegeri_v
	GLAD_API_CALL PFNGLGETINTEGERVPROC glad_glGetIntegerv;
#define glGetIntegerv glad_glGetIntegerv
	GLAD_API_CALL PFNGLGETLIGHTFVPROC glad_glGetLightfv;
#define glGetLightfv glad_glGetLightfv
	GLAD_API_CALL PFNGLGETLIGHTIVPROC glad_glGetLightiv;
#define glGetLightiv glad_glGetLightiv
	GLAD_API_CALL PFNGLGETMAPDVPROC glad_glGetMapdv;
#define glGetMapdv glad_glGetMapdv
	GLAD_API_CALL PFNGLGETMAPFVPROC glad_glGetMapfv;
#define glGetMapfv glad_glGetMapfv
	GLAD_API_CALL PFNGLGETMAPIVPROC glad_glGetMapiv;
#define glGetMapiv glad_glGetMapiv
	GLAD_API_CALL PFNGLGETMATERIALFVPROC glad_glGetMaterialfv;
#define glGetMaterialfv glad_glGetMaterialfv
	GLAD_API_CALL PFNGLGETMATERIALIVPROC glad_glGetMaterialiv;
#define glGetMaterialiv glad_glGetMaterialiv
	GLAD_API_CALL PFNGLGETMULTISAMPLEFVPROC glad_glGetMultisamplefv;
#define glGetMultisamplefv glad_glGetMultisamplefv
	GLAD_API_CALL PFNGLGETPIXELMAPFVPROC glad_glGetPixelMapfv;
#define glGetPixelMapfv glad_glGetPixelMapfv
	GLAD_API_CALL PFNGLGETPIXELMAPUIVPROC glad_glGetPixelMapuiv;
#define glGetPixelMapuiv glad_glGetPixelMapuiv
	GLAD_API_CALL PFNGLGETPIXELMAPUSVPROC glad_glGetPixelMapusv;
#define glGetPixelMapusv glad_glGetPixelMapusv
	GLAD_API_CALL PFNGLGETPOINTERVPROC glad_glGetPointerv;
#define glGetPointerv glad_glGetPointerv
	GLAD_API_CALL PFNGLGETPOLYGONSTIPPLEPROC glad_glGetPolygonStipple;
#define glGetPolygonStipple glad_glGetPolygonStipple
	GLAD_API_CALL PFNGLGETPROGRAMINFOLOGPROC glad_glGetProgramInfoLog;
#define glGetProgramInfoLog glad_glGetProgramInfoLog
	GLAD_API_CALL PFNGLGETPROGRAMIVPROC glad_glGetProgramiv;
#define glGetProgramiv glad_glGetProgramiv
	GLAD_API_CALL PFNGLGETQUERYOBJECTI64VPROC glad_glGetQueryObjecti64v;
#define glGetQueryObjecti64v glad_glGetQueryObjecti64v
	GLAD_API_CALL PFNGLGETQUERYOBJECTIVPROC glad_glGetQueryObjectiv;
#define glGetQueryObjectiv glad_glGetQueryObjectiv
	GLAD_API_CALL PFNGLGETQUERYOBJECTUI64VPROC glad_glGetQueryObjectui64v;
#define glGetQueryObjectui64v glad_glGetQueryObjectui64v
	GLAD_API_CALL PFNGLGETQUERYOBJECTUIVPROC glad_glGetQueryObjectuiv;
#define glGetQueryObjectuiv glad_glGetQueryObjectuiv
	GLAD_API_CALL PFNGLGETQUERYIVPROC glad_glGetQueryiv;
#define glGetQueryiv glad_glGetQueryiv
	GLAD_API_CALL PFNGLGETRENDERBUFFERPARAMETERIVPROC glad_glGetRenderbufferParameteriv;
#define glGetRenderbufferParameteriv glad_glGetRenderbufferParameteriv
	GLAD_API_CALL PFNGLGETSAMPLERPARAMETERIIVPROC glad_glGetSamplerParameterIiv;
#define glGetSamplerParameterIiv glad_glGetSamplerParameterIiv
	GLAD_API_CALL PFNGLGETSAMPLERPARAMETERIUIVPROC glad_glGetSamplerParameterIuiv;
#define glGetSamplerParameterIuiv glad_glGetSamplerParameterIuiv
	GLAD_API_CALL PFNGLGETSAMPLERPARAMETERFVPROC glad_glGetSamplerParameterfv;
#define glGetSamplerParameterfv glad_glGetSamplerParameterfv
	GLAD_API_CALL PFNGLGETSAMPLERPARAMETERIVPROC glad_glGetSamplerParameteriv;
#define glGetSamplerParameteriv glad_glGetSamplerParameteriv
	GLAD_API_CALL PFNGLGETSHADERINFOLOGPROC glad_glGetShaderInfoLog;
#define glGetShaderInfoLog glad_glGetShaderInfoLog
	GLAD_API_CALL PFNGLGETSHADERSOURCEPROC glad_glGetShaderSource;
#define glGetShaderSource glad_glGetShaderSource
	GLAD_API_CALL PFNGLGETSHADERIVPROC glad_glGetShaderiv;
#define glGetShaderiv glad_glGetShaderiv
	GLAD_API_CALL PFNGLGETSTRINGPROC glad_glGetString;
#define glGetString glad_glGetString
	GLAD_API_CALL PFNGLGETSTRINGIPROC glad_glGetStringi;
#define glGetStringi glad_glGetStringi
	GLAD_API_CALL PFNGLGETSYNCIVPROC glad_glGetSynciv;
#define glGetSynciv glad_glGetSynciv
	GLAD_API_CALL PFNGLGETTEXENVFVPROC glad_glGetTexEnvfv;
#define glGetTexEnvfv glad_glGetTexEnvfv
	GLAD_API_CALL PFNGLGETTEXENVIVPROC glad_glGetTexEnviv;
#define glGetTexEnviv glad_glGetTexEnviv
	GLAD_API_CALL PFNGLGETTEXGENDVPROC glad_glGetTexGendv;
#define glGetTexGendv glad_glGetTexGendv
	GLAD_API_CALL PFNGLGETTEXGENFVPROC glad_glGetTexGenfv;
#define glGetTexGenfv glad_glGetTexGenfv
	GLAD_API_CALL PFNGLGETTEXGENIVPROC glad_glGetTexGeniv;
#define glGetTexGeniv glad_glGetTexGeniv
	GLAD_API_CALL PFNGLGETTEXIMAGEPROC glad_glGetTexImage;
#define glGetTexImage glad_glGetTexImage
	GLAD_API_CALL PFNGLGETTEXLEVELPARAMETERFVPROC glad_glGetTexLevelParameterfv;
#define glGetTexLevelParameterfv glad_glGetTexLevelParameterfv
	GLAD_API_CALL PFNGLGETTEXLEVELPARAMETERIVPROC glad_glGetTexLevelParameteriv;
#define glGetTexLevelParameteriv glad_glGetTexLevelParameteriv
	GLAD_API_CALL PFNGLGETTEXPARAMETERIIVPROC glad_glGetTexParameterIiv;
#define glGetTexParameterIiv glad_glGetTexParameterIiv
	GLAD_API_CALL PFNGLGETTEXPARAMETERIUIVPROC glad_glGetTexParameterIuiv;
#define glGetTexParameterIuiv glad_glGetTexParameterIuiv
	GLAD_API_CALL PFNGLGETTEXPARAMETERFVPROC glad_glGetTexParameterfv;
#define glGetTexParameterfv glad_glGetTexParameterfv
	GLAD_API_CALL PFNGLGETTEXPARAMETERIVPROC glad_glGetTexParameteriv;
#define glGetTexParameteriv glad_glGetTexParameteriv
	GLAD_API_CALL PFNGLGETTRANSFORMFEEDBACKVARYINGPROC glad_glGetTransformFeedbackVarying;
#define glGetTransformFeedbackVarying glad_glGetTransformFeedbackVarying
	GLAD_API_CALL PFNGLGETUNIFORMBLOCKINDEXPROC glad_glGetUniformBlockIndex;
#define glGetUniformBlockIndex glad_glGetUniformBlockIndex
	GLAD_API_CALL PFNGLGETUNIFORMINDICESPROC glad_glGetUniformIndices;
#define glGetUniformIndices glad_glGetUniformIndices
	GLAD_API_CALL PFNGLGETUNIFORMLOCATIONPROC glad_glGetUniformLocation;
#define glGetUniformLocation glad_glGetUniformLocation
	GLAD_API_CALL PFNGLGETUNIFORMFVPROC glad_glGetUniformfv;
#define glGetUniformfv glad_glGetUniformfv
	GLAD_API_CALL PFNGLGETUNIFORMIVPROC glad_glGetUniformiv;
#define glGetUniformiv glad_glGetUniformiv
	GLAD_API_CALL PFNGLGETUNIFORMUIVPROC glad_glGetUniformuiv;
#define glGetUniformuiv glad_glGetUniformuiv
	GLAD_API_CALL PFNGLGETVERTEXATTRIBIIVPROC glad_glGetVertexAttribIiv;
#define glGetVertexAttribIiv glad_glGetVertexAttribIiv
	GLAD_API_CALL PFNGLGETVERTEXATTRIBIUIVPROC glad_glGetVertexAttribIuiv;
#define glGetVertexAttribIuiv glad_glGetVertexAttribIuiv
	GLAD_API_CALL PFNGLGETVERTEXATTRIBPOINTERVPROC glad_glGetVertexAttribPointerv;
#define glGetVertexAttribPointerv glad_glGetVertexAttribPointerv
	GLAD_API_CALL PFNGLGETVERTEXATTRIBDVPROC glad_glGetVertexAttribdv;
#define glGetVertexAttribdv glad_glGetVertexAttribdv
	GLAD_API_CALL PFNGLGETVERTEXATTRIBFVPROC glad_glGetVertexAttribfv;
#define glGetVertexAttribfv glad_glGetVertexAttribfv
	GLAD_API_CALL PFNGLGETVERTEXATTRIBIVPROC glad_glGetVertexAttribiv;
#define glGetVertexAttribiv glad_glGetVertexAttribiv
	GLAD_API_CALL PFNGLHINTPROC glad_glHint;
#define glHint glad_glHint
	GLAD_API_CALL PFNGLINDEXMASKPROC glad_glIndexMask;
#define glIndexMask glad_glIndexMask
	GLAD_API_CALL PFNGLINDEXPOINTERPROC glad_glIndexPointer;
#define glIndexPointer glad_glIndexPointer
	GLAD_API_CALL PFNGLINDEXDPROC glad_glIndexd;
#define glIndexd glad_glIndexd
	GLAD_API_CALL PFNGLINDEXDVPROC glad_glIndexdv;
#define glIndexdv glad_glIndexdv
	GLAD_API_CALL PFNGLINDEXFPROC glad_glIndexf;
#define glIndexf glad_glIndexf
	GLAD_API_CALL PFNGLINDEXFVPROC glad_glIndexfv;
#define glIndexfv glad_glIndexfv
	GLAD_API_CALL PFNGLINDEXIPROC glad_glIndexi;
#define glIndexi glad_glIndexi
	GLAD_API_CALL PFNGLINDEXIVPROC glad_glIndexiv;
#define glIndexiv glad_glIndexiv
	GLAD_API_CALL PFNGLINDEXSPROC glad_glIndexs;
#define glIndexs glad_glIndexs
	GLAD_API_CALL PFNGLINDEXSVPROC glad_glIndexsv;
#define glIndexsv glad_glIndexsv
	GLAD_API_CALL PFNGLINDEXUBPROC glad_glIndexub;
#define glIndexub glad_glIndexub
	GLAD_API_CALL PFNGLINDEXUBVPROC glad_glIndexubv;
#define glIndexubv glad_glIndexubv
	GLAD_API_CALL PFNGLINITNAMESPROC glad_glInitNames;
#define glInitNames glad_glInitNames
	GLAD_API_CALL PFNGLINTERLEAVEDARRAYSPROC glad_glInterleavedArrays;
#define glInterleavedArrays glad_glInterleavedArrays
	GLAD_API_CALL PFNGLISBUFFERPROC glad_glIsBuffer;
#define glIsBuffer glad_glIsBuffer
	GLAD_API_CALL PFNGLISENABLEDPROC glad_glIsEnabled;
#define glIsEnabled glad_glIsEnabled
	GLAD_API_CALL PFNGLISENABLEDIPROC glad_glIsEnabledi;
#define glIsEnabledi glad_glIsEnabledi
	GLAD_API_CALL PFNGLISFRAMEBUFFERPROC glad_glIsFramebuffer;
#define glIsFramebuffer glad_glIsFramebuffer
	GLAD_API_CALL PFNGLISLISTPROC glad_glIsList;
#define glIsList glad_glIsList
	GLAD_API_CALL PFNGLISPROGRAMPROC glad_glIsProgram;
#define glIsProgram glad_glIsProgram
	GLAD_API_CALL PFNGLISQUERYPROC glad_glIsQuery;
#define glIsQuery glad_glIsQuery
	GLAD_API_CALL PFNGLISRENDERBUFFERPROC glad_glIsRenderbuffer;
#define glIsRenderbuffer glad_glIsRenderbuffer
	GLAD_API_CALL PFNGLISSAMPLERPROC glad_glIsSampler;
#define glIsSampler glad_glIsSampler
	GLAD_API_CALL PFNGLISSHADERPROC glad_glIsShader;
#define glIsShader glad_glIsShader
	GLAD_API_CALL PFNGLISSYNCPROC glad_glIsSync;
#define glIsSync glad_glIsSync
	GLAD_API_CALL PFNGLISTEXTUREPROC glad_glIsTexture;
#define glIsTexture glad_glIsTexture
	GLAD_API_CALL PFNGLISVERTEXARRAYPROC glad_glIsVertexArray;
#define glIsVertexArray glad_glIsVertexArray
	GLAD_API_CALL PFNGLLIGHTMODELFPROC glad_glLightModelf;
#define glLightModelf glad_glLightModelf
	GLAD_API_CALL PFNGLLIGHTMODELFVPROC glad_glLightModelfv;
#define glLightModelfv glad_glLightModelfv
	GLAD_API_CALL PFNGLLIGHTMODELIPROC glad_glLightModeli;
#define glLightModeli glad_glLightModeli
	GLAD_API_CALL PFNGLLIGHTMODELIVPROC glad_glLightModeliv;
#define glLightModeliv glad_glLightModeliv
	GLAD_API_CALL PFNGLLIGHTFPROC glad_glLightf;
#define glLightf glad_glLightf
	GLAD_API_CALL PFNGLLIGHTFVPROC glad_glLightfv;
#define glLightfv glad_glLightfv
	GLAD_API_CALL PFNGLLIGHTIPROC glad_glLighti;
#define glLighti glad_glLighti
	GLAD_API_CALL PFNGLLIGHTIVPROC glad_glLightiv;
#define glLightiv glad_glLightiv
	GLAD_API_CALL PFNGLLINESTIPPLEPROC glad_glLineStipple;
#define glLineStipple glad_glLineStipple
	GLAD_API_CALL PFNGLLINEWIDTHPROC glad_glLineWidth;
#define glLineWidth glad_glLineWidth
	GLAD_API_CALL PFNGLLINKPROGRAMPROC glad_glLinkProgram;
#define glLinkProgram glad_glLinkProgram
	GLAD_API_CALL PFNGLLISTBASEPROC glad_glListBase;
#define glListBase glad_glListBase
	GLAD_API_CALL PFNGLLOADIDENTITYPROC glad_glLoadIdentity;
#define glLoadIdentity glad_glLoadIdentity
	GLAD_API_CALL PFNGLLOADMATRIXDPROC glad_glLoadMatrixd;
#define glLoadMatrixd glad_glLoadMatrixd
	GLAD_API_CALL PFNGLLOADMATRIXFPROC glad_glLoadMatrixf;
#define glLoadMatrixf glad_glLoadMatrixf
	GLAD_API_CALL PFNGLLOADNAMEPROC glad_glLoadName;
#define glLoadName glad_glLoadName
	GLAD_API_CALL PFNGLLOADTRANSPOSEMATRIXDPROC glad_glLoadTransposeMatrixd;
#define glLoadTransposeMatrixd glad_glLoadTransposeMatrixd
	GLAD_API_CALL PFNGLLOADTRANSPOSEMATRIXFPROC glad_glLoadTransposeMatrixf;
#define glLoadTransposeMatrixf glad_glLoadTransposeMatrixf
	GLAD_API_CALL PFNGLLOGICOPPROC glad_glLogicOp;
#define glLogicOp glad_glLogicOp
	GLAD_API_CALL PFNGLMAP1DPROC glad_glMap1d;
#define glMap1d glad_glMap1d
	GLAD_API_CALL PFNGLMAP1FPROC glad_glMap1f;
#define glMap1f glad_glMap1f
	GLAD_API_CALL PFNGLMAP2DPROC glad_glMap2d;
#define glMap2d glad_glMap2d
	GLAD_API_CALL PFNGLMAP2FPROC glad_glMap2f;
#define glMap2f glad_glMap2f
	GLAD_API_CALL PFNGLMAPBUFFERPROC glad_glMapBuffer;
#define glMapBuffer glad_glMapBuffer
	GLAD_API_CALL PFNGLMAPBUFFERRANGEPROC glad_glMapBufferRange;
#define glMapBufferRange glad_glMapBufferRange
	GLAD_API_CALL PFNGLMAPGRID1DPROC glad_glMapGrid1d;
#define glMapGrid1d glad_glMapGrid1d
	GLAD_API_CALL PFNGLMAPGRID1FPROC glad_glMapGrid1f;
#define glMapGrid1f glad_glMapGrid1f
	GLAD_API_CALL PFNGLMAPGRID2DPROC glad_glMapGrid2d;
#define glMapGrid2d glad_glMapGrid2d
	GLAD_API_CALL PFNGLMAPGRID2FPROC glad_glMapGrid2f;
#define glMapGrid2f glad_glMapGrid2f
	GLAD_API_CALL PFNGLMATERIALFPROC glad_glMaterialf;
#define glMaterialf glad_glMaterialf
	GLAD_API_CALL PFNGLMATERIALFVPROC glad_glMaterialfv;
#define glMaterialfv glad_glMaterialfv
	GLAD_API_CALL PFNGLMATERIALIPROC glad_glMateriali;
#define glMateriali glad_glMateriali
	GLAD_API_CALL PFNGLMATERIALIVPROC glad_glMaterialiv;
#define glMaterialiv glad_glMaterialiv
	GLAD_API_CALL PFNGLMATRIXMODEPROC glad_glMatrixMode;
#define glMatrixMode glad_glMatrixMode
	GLAD_API_CALL PFNGLMULTMATRIXDPROC glad_glMultMatrixd;
#define glMultMatrixd glad_glMultMatrixd
	GLAD_API_CALL PFNGLMULTMATRIXFPROC glad_glMultMatrixf;
#define glMultMatrixf glad_glMultMatrixf
	GLAD_API_CALL PFNGLMULTTRANSPOSEMATRIXDPROC glad_glMultTransposeMatrixd;
#define glMultTransposeMatrixd glad_glMultTransposeMatrixd
	GLAD_API_CALL PFNGLMULTTRANSPOSEMATRIXFPROC glad_glMultTransposeMatrixf;
#define glMultTransposeMatrixf glad_glMultTransposeMatrixf
	GLAD_API_CALL PFNGLMULTIDRAWARRAYSPROC glad_glMultiDrawArrays;
#define glMultiDrawArrays glad_glMultiDrawArrays
	GLAD_API_CALL PFNGLMULTIDRAWELEMENTSPROC glad_glMultiDrawElements;
#define glMultiDrawElements glad_glMultiDrawElements
	GLAD_API_CALL PFNGLMULTIDRAWELEMENTSBASEVERTEXPROC glad_glMultiDrawElementsBaseVertex;
#define glMultiDrawElementsBaseVertex glad_glMultiDrawElementsBaseVertex
	GLAD_API_CALL PFNGLMULTITEXCOORD1DPROC glad_glMultiTexCoord1d;
#define glMultiTexCoord1d glad_glMultiTexCoord1d
	GLAD_API_CALL PFNGLMULTITEXCOORD1DVPROC glad_glMultiTexCoord1dv;
#define glMultiTexCoord1dv glad_glMultiTexCoord1dv
	GLAD_API_CALL PFNGLMULTITEXCOORD1FPROC glad_glMultiTexCoord1f;
#define glMultiTexCoord1f glad_glMultiTexCoord1f
	GLAD_API_CALL PFNGLMULTITEXCOORD1FVPROC glad_glMultiTexCoord1fv;
#define glMultiTexCoord1fv glad_glMultiTexCoord1fv
	GLAD_API_CALL PFNGLMULTITEXCOORD1IPROC glad_glMultiTexCoord1i;
#define glMultiTexCoord1i glad_glMultiTexCoord1i
	GLAD_API_CALL PFNGLMULTITEXCOORD1IVPROC glad_glMultiTexCoord1iv;
#define glMultiTexCoord1iv glad_glMultiTexCoord1iv
	GLAD_API_CALL PFNGLMULTITEXCOORD1SPROC glad_glMultiTexCoord1s;
#define glMultiTexCoord1s glad_glMultiTexCoord1s
	GLAD_API_CALL PFNGLMULTITEXCOORD1SVPROC glad_glMultiTexCoord1sv;
#define glMultiTexCoord1sv glad_glMultiTexCoord1sv
	GLAD_API_CALL PFNGLMULTITEXCOORD2DPROC glad_glMultiTexCoord2d;
#define glMultiTexCoord2d glad_glMultiTexCoord2d
	GLAD_API_CALL PFNGLMULTITEXCOORD2DVPROC glad_glMultiTexCoord2dv;
#define glMultiTexCoord2dv glad_glMultiTexCoord2dv
	GLAD_API_CALL PFNGLMULTITEXCOORD2FPROC glad_glMultiTexCoord2f;
#define glMultiTexCoord2f glad_glMultiTexCoord2f
	GLAD_API_CALL PFNGLMULTITEXCOORD2FVPROC glad_glMultiTexCoord2fv;
#define glMultiTexCoord2fv glad_glMultiTexCoord2fv
	GLAD_API_CALL PFNGLMULTITEXCOORD2IPROC glad_glMultiTexCoord2i;
#define glMultiTexCoord2i glad_glMultiTexCoord2i
	GLAD_API_CALL PFNGLMULTITEXCOORD2IVPROC glad_glMultiTexCoord2iv;
#define glMultiTexCoord2iv glad_glMultiTexCoord2iv
	GLAD_API_CALL PFNGLMULTITEXCOORD2SPROC glad_glMultiTexCoord2s;
#define glMultiTexCoord2s glad_glMultiTexCoord2s
	GLAD_API_CALL PFNGLMULTITEXCOORD2SVPROC glad_glMultiTexCoord2sv;
#define glMultiTexCoord2sv glad_glMultiTexCoord2sv
	GLAD_API_CALL PFNGLMULTITEXCOORD3DPROC glad_glMultiTexCoord3d;
#define glMultiTexCoord3d glad_glMultiTexCoord3d
	GLAD_API_CALL PFNGLMULTITEXCOORD3DVPROC glad_glMultiTexCoord3dv;
#define glMultiTexCoord3dv glad_glMultiTexCoord3dv
	GLAD_API_CALL PFNGLMULTITEXCOORD3FPROC glad_glMultiTexCoord3f;
#define glMultiTexCoord3f glad_glMultiTexCoord3f
	GLAD_API_CALL PFNGLMULTITEXCOORD3FVPROC glad_glMultiTexCoord3fv;
#define glMultiTexCoord3fv glad_glMultiTexCoord3fv
	GLAD_API_CALL PFNGLMULTITEXCOORD3IPROC glad_glMultiTexCoord3i;
#define glMultiTexCoord3i glad_glMultiTexCoord3i
	GLAD_API_CALL PFNGLMULTITEXCOORD3IVPROC glad_glMultiTexCoord3iv;
#define glMultiTexCoord3iv glad_glMultiTexCoord3iv
	GLAD_API_CALL PFNGLMULTITEXCOORD3SPROC glad_glMultiTexCoord3s;
#define glMultiTexCoord3s glad_glMultiTexCoord3s
	GLAD_API_CALL PFNGLMULTITEXCOORD3SVPROC glad_glMultiTexCoord3sv;
#define glMultiTexCoord3sv glad_glMultiTexCoord3sv
	GLAD_API_CALL PFNGLMULTITEXCOORD4DPROC glad_glMultiTexCoord4d;
#define glMultiTexCoord4d glad_glMultiTexCoord4d
	GLAD_API_CALL PFNGLMULTITEXCOORD4DVPROC glad_glMultiTexCoord4dv;
#define glMultiTexCoord4dv glad_glMultiTexCoord4dv
	GLAD_API_CALL PFNGLMULTITEXCOORD4FPROC glad_glMultiTexCoord4f;
#define glMultiTexCoord4f glad_glMultiTexCoord4f
	GLAD_API_CALL PFNGLMULTITEXCOORD4FVPROC glad_glMultiTexCoord4fv;
#define glMultiTexCoord4fv glad_glMultiTexCoord4fv
	GLAD_API_CALL PFNGLMULTITEXCOORD4IPROC glad_glMultiTexCoord4i;
#define glMultiTexCoord4i glad_glMultiTexCoord4i
	GLAD_API_CALL PFNGLMULTITEXCOORD4IVPROC glad_glMultiTexCoord4iv;
#define glMultiTexCoord4iv glad_glMultiTexCoord4iv
	GLAD_API_CALL PFNGLMULTITEXCOORD4SPROC glad_glMultiTexCoord4s;
#define glMultiTexCoord4s glad_glMultiTexCoord4s
	GLAD_API_CALL PFNGLMULTITEXCOORD4SVPROC glad_glMultiTexCoord4sv;
#define glMultiTexCoord4sv glad_glMultiTexCoord4sv
	GLAD_API_CALL PFNGLMULTITEXCOORDP1UIPROC glad_glMultiTexCoordP1ui;
#define glMultiTexCoordP1ui glad_glMultiTexCoordP1ui
	GLAD_API_CALL PFNGLMULTITEXCOORDP1UIVPROC glad_glMultiTexCoordP1uiv;
#define glMultiTexCoordP1uiv glad_glMultiTexCoordP1uiv
	GLAD_API_CALL PFNGLMULTITEXCOORDP2UIPROC glad_glMultiTexCoordP2ui;
#define glMultiTexCoordP2ui glad_glMultiTexCoordP2ui
	GLAD_API_CALL PFNGLMULTITEXCOORDP2UIVPROC glad_glMultiTexCoordP2uiv;
#define glMultiTexCoordP2uiv glad_glMultiTexCoordP2uiv
	GLAD_API_CALL PFNGLMULTITEXCOORDP3UIPROC glad_glMultiTexCoordP3ui;
#define glMultiTexCoordP3ui glad_glMultiTexCoordP3ui
	GLAD_API_CALL PFNGLMULTITEXCOORDP3UIVPROC glad_glMultiTexCoordP3uiv;
#define glMultiTexCoordP3uiv glad_glMultiTexCoordP3uiv
	GLAD_API_CALL PFNGLMULTITEXCOORDP4UIPROC glad_glMultiTexCoordP4ui;
#define glMultiTexCoordP4ui glad_glMultiTexCoordP4ui
	GLAD_API_CALL PFNGLMULTITEXCOORDP4UIVPROC glad_glMultiTexCoordP4uiv;
#define glMultiTexCoordP4uiv glad_glMultiTexCoordP4uiv
	GLAD_API_CALL PFNGLNEWLISTPROC glad_glNewList;
#define glNewList glad_glNewList
	GLAD_API_CALL PFNGLNORMAL3BPROC glad_glNormal3b;
#define glNormal3b glad_glNormal3b
	GLAD_API_CALL PFNGLNORMAL3BVPROC glad_glNormal3bv;
#define glNormal3bv glad_glNormal3bv
	GLAD_API_CALL PFNGLNORMAL3DPROC glad_glNormal3d;
#define glNormal3d glad_glNormal3d
	GLAD_API_CALL PFNGLNORMAL3DVPROC glad_glNormal3dv;
#define glNormal3dv glad_glNormal3dv
	GLAD_API_CALL PFNGLNORMAL3FPROC glad_glNormal3f;
#define glNormal3f glad_glNormal3f
	GLAD_API_CALL PFNGLNORMAL3FVPROC glad_glNormal3fv;
#define glNormal3fv glad_glNormal3fv
	GLAD_API_CALL PFNGLNORMAL3IPROC glad_glNormal3i;
#define glNormal3i glad_glNormal3i
	GLAD_API_CALL PFNGLNORMAL3IVPROC glad_glNormal3iv;
#define glNormal3iv glad_glNormal3iv
	GLAD_API_CALL PFNGLNORMAL3SPROC glad_glNormal3s;
#define glNormal3s glad_glNormal3s
	GLAD_API_CALL PFNGLNORMAL3SVPROC glad_glNormal3sv;
#define glNormal3sv glad_glNormal3sv
	GLAD_API_CALL PFNGLNORMALP3UIPROC glad_glNormalP3ui;
#define glNormalP3ui glad_glNormalP3ui
	GLAD_API_CALL PFNGLNORMALP3UIVPROC glad_glNormalP3uiv;
#define glNormalP3uiv glad_glNormalP3uiv
	GLAD_API_CALL PFNGLNORMALPOINTERPROC glad_glNormalPointer;
#define glNormalPointer glad_glNormalPointer
	GLAD_API_CALL PFNGLORTHOPROC glad_glOrtho;
#define glOrtho glad_glOrtho
	GLAD_API_CALL PFNGLPASSTHROUGHPROC glad_glPassThrough;
#define glPassThrough glad_glPassThrough
	GLAD_API_CALL PFNGLPIXELMAPFVPROC glad_glPixelMapfv;
#define glPixelMapfv glad_glPixelMapfv
	GLAD_API_CALL PFNGLPIXELMAPUIVPROC glad_glPixelMapuiv;
#define glPixelMapuiv glad_glPixelMapuiv
	GLAD_API_CALL PFNGLPIXELMAPUSVPROC glad_glPixelMapusv;
#define glPixelMapusv glad_glPixelMapusv
	GLAD_API_CALL PFNGLPIXELSTOREFPROC glad_glPixelStoref;
#define glPixelStoref glad_glPixelStoref
	GLAD_API_CALL PFNGLPIXELSTOREIPROC glad_glPixelStorei;
#define glPixelStorei glad_glPixelStorei
	GLAD_API_CALL PFNGLPIXELTRANSFERFPROC glad_glPixelTransferf;
#define glPixelTransferf glad_glPixelTransferf
	GLAD_API_CALL PFNGLPIXELTRANSFERIPROC glad_glPixelTransferi;
#define glPixelTransferi glad_glPixelTransferi
	GLAD_API_CALL PFNGLPIXELZOOMPROC glad_glPixelZoom;
#define glPixelZoom glad_glPixelZoom
	GLAD_API_CALL PFNGLPOINTPARAMETERFPROC glad_glPointParameterf;
#define glPointParameterf glad_glPointParameterf
	GLAD_API_CALL PFNGLPOINTPARAMETERFVPROC glad_glPointParameterfv;
#define glPointParameterfv glad_glPointParameterfv
	GLAD_API_CALL PFNGLPOINTPARAMETERIPROC glad_glPointParameteri;
#define glPointParameteri glad_glPointParameteri
	GLAD_API_CALL PFNGLPOINTPARAMETERIVPROC glad_glPointParameteriv;
#define glPointParameteriv glad_glPointParameteriv
	GLAD_API_CALL PFNGLPOINTSIZEPROC glad_glPointSize;
#define glPointSize glad_glPointSize
	GLAD_API_CALL PFNGLPOLYGONMODEPROC glad_glPolygonMode;
#define glPolygonMode glad_glPolygonMode
	GLAD_API_CALL PFNGLPOLYGONOFFSETPROC glad_glPolygonOffset;
#define glPolygonOffset glad_glPolygonOffset
	GLAD_API_CALL PFNGLPOLYGONSTIPPLEPROC glad_glPolygonStipple;
#define glPolygonStipple glad_glPolygonStipple
	GLAD_API_CALL PFNGLPOPATTRIBPROC glad_glPopAttrib;
#define glPopAttrib glad_glPopAttrib
	GLAD_API_CALL PFNGLPOPCLIENTATTRIBPROC glad_glPopClientAttrib;
#define glPopClientAttrib glad_glPopClientAttrib
	GLAD_API_CALL PFNGLPOPMATRIXPROC glad_glPopMatrix;
#define glPopMatrix glad_glPopMatrix
	GLAD_API_CALL PFNGLPOPNAMEPROC glad_glPopName;
#define glPopName glad_glPopName
	GLAD_API_CALL PFNGLPRIMITIVERESTARTINDEXPROC glad_glPrimitiveRestartIndex;
#define glPrimitiveRestartIndex glad_glPrimitiveRestartIndex
	GLAD_API_CALL PFNGLPRIORITIZETEXTURESPROC glad_glPrioritizeTextures;
#define glPrioritizeTextures glad_glPrioritizeTextures
	GLAD_API_CALL PFNGLPROVOKINGVERTEXPROC glad_glProvokingVertex;
#define glProvokingVertex glad_glProvokingVertex
	GLAD_API_CALL PFNGLPUSHATTRIBPROC glad_glPushAttrib;
#define glPushAttrib glad_glPushAttrib
	GLAD_API_CALL PFNGLPUSHCLIENTATTRIBPROC glad_glPushClientAttrib;
#define glPushClientAttrib glad_glPushClientAttrib
	GLAD_API_CALL PFNGLPUSHMATRIXPROC glad_glPushMatrix;
#define glPushMatrix glad_glPushMatrix
	GLAD_API_CALL PFNGLPUSHNAMEPROC glad_glPushName;
#define glPushName glad_glPushName
	GLAD_API_CALL PFNGLQUERYCOUNTERPROC glad_glQueryCounter;
#define glQueryCounter glad_glQueryCounter
	GLAD_API_CALL PFNGLRASTERPOS2DPROC glad_glRasterPos2d;
#define glRasterPos2d glad_glRasterPos2d
	GLAD_API_CALL PFNGLRASTERPOS2DVPROC glad_glRasterPos2dv;
#define glRasterPos2dv glad_glRasterPos2dv
	GLAD_API_CALL PFNGLRASTERPOS2FPROC glad_glRasterPos2f;
#define glRasterPos2f glad_glRasterPos2f
	GLAD_API_CALL PFNGLRASTERPOS2FVPROC glad_glRasterPos2fv;
#define glRasterPos2fv glad_glRasterPos2fv
	GLAD_API_CALL PFNGLRASTERPOS2IPROC glad_glRasterPos2i;
#define glRasterPos2i glad_glRasterPos2i
	GLAD_API_CALL PFNGLRASTERPOS2IVPROC glad_glRasterPos2iv;
#define glRasterPos2iv glad_glRasterPos2iv
	GLAD_API_CALL PFNGLRASTERPOS2SPROC glad_glRasterPos2s;
#define glRasterPos2s glad_glRasterPos2s
	GLAD_API_CALL PFNGLRASTERPOS2SVPROC glad_glRasterPos2sv;
#define glRasterPos2sv glad_glRasterPos2sv
	GLAD_API_CALL PFNGLRASTERPOS3DPROC glad_glRasterPos3d;
#define glRasterPos3d glad_glRasterPos3d
	GLAD_API_CALL PFNGLRASTERPOS3DVPROC glad_glRasterPos3dv;
#define glRasterPos3dv glad_glRasterPos3dv
	GLAD_API_CALL PFNGLRASTERPOS3FPROC glad_glRasterPos3f;
#define glRasterPos3f glad_glRasterPos3f
	GLAD_API_CALL PFNGLRASTERPOS3FVPROC glad_glRasterPos3fv;
#define glRasterPos3fv glad_glRasterPos3fv
	GLAD_API_CALL PFNGLRASTERPOS3IPROC glad_glRasterPos3i;
#define glRasterPos3i glad_glRasterPos3i
	GLAD_API_CALL PFNGLRASTERPOS3IVPROC glad_glRasterPos3iv;
#define glRasterPos3iv glad_glRasterPos3iv
	GLAD_API_CALL PFNGLRASTERPOS3SPROC glad_glRasterPos3s;
#define glRasterPos3s glad_glRasterPos3s
	GLAD_API_CALL PFNGLRASTERPOS3SVPROC glad_glRasterPos3sv;
#define glRasterPos3sv glad_glRasterPos3sv
	GLAD_API_CALL PFNGLRASTERPOS4DPROC glad_glRasterPos4d;
#define glRasterPos4d glad_glRasterPos4d
	GLAD_API_CALL PFNGLRASTERPOS4DVPROC glad_glRasterPos4dv;
#define glRasterPos4dv glad_glRasterPos4dv
	GLAD_API_CALL PFNGLRASTERPOS4FPROC glad_glRasterPos4f;
#define glRasterPos4f glad_glRasterPos4f
	GLAD_API_CALL PFNGLRASTERPOS4FVPROC glad_glRasterPos4fv;
#define glRasterPos4fv glad_glRasterPos4fv
	GLAD_API_CALL PFNGLRASTERPOS4IPROC glad_glRasterPos4i;
#define glRasterPos4i glad_glRasterPos4i
	GLAD_API_CALL PFNGLRASTERPOS4IVPROC glad_glRasterPos4iv;
#define glRasterPos4iv glad_glRasterPos4iv
	GLAD_API_CALL PFNGLRASTERPOS4SPROC glad_glRasterPos4s;
#define glRasterPos4s glad_glRasterPos4s
	GLAD_API_CALL PFNGLRASTERPOS4SVPROC glad_glRasterPos4sv;
#define glRasterPos4sv glad_glRasterPos4sv
	GLAD_API_CALL PFNGLREADBUFFERPROC glad_glReadBuffer;
#define glReadBuffer glad_glReadBuffer
	GLAD_API_CALL PFNGLREADPIXELSPROC glad_glReadPixels;
#define glReadPixels glad_glReadPixels
	GLAD_API_CALL PFNGLRECTDPROC glad_glRectd;
#define glRectd glad_glRectd
	GLAD_API_CALL PFNGLRECTDVPROC glad_glRectdv;
#define glRectdv glad_glRectdv
	GLAD_API_CALL PFNGLRECTFPROC glad_glRectf;
#define glRectf glad_glRectf
	GLAD_API_CALL PFNGLRECTFVPROC glad_glRectfv;
#define glRectfv glad_glRectfv
	GLAD_API_CALL PFNGLRECTIPROC glad_glRecti;
#define glRecti glad_glRecti
	GLAD_API_CALL PFNGLRECTIVPROC glad_glRectiv;
#define glRectiv glad_glRectiv
	GLAD_API_CALL PFNGLRECTSPROC glad_glRects;
#define glRects glad_glRects
	GLAD_API_CALL PFNGLRECTSVPROC glad_glRectsv;
#define glRectsv glad_glRectsv
	GLAD_API_CALL PFNGLRENDERMODEPROC glad_glRenderMode;
#define glRenderMode glad_glRenderMode
	GLAD_API_CALL PFNGLRENDERBUFFERSTORAGEPROC glad_glRenderbufferStorage;
#define glRenderbufferStorage glad_glRenderbufferStorage
	GLAD_API_CALL PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC glad_glRenderbufferStorageMultisample;
#define glRenderbufferStorageMultisample glad_glRenderbufferStorageMultisample
	GLAD_API_CALL PFNGLROTATEDPROC glad_glRotated;
#define glRotated glad_glRotated
	GLAD_API_CALL PFNGLROTATEFPROC glad_glRotatef;
#define glRotatef glad_glRotatef
	GLAD_API_CALL PFNGLSAMPLECOVERAGEPROC glad_glSampleCoverage;
#define glSampleCoverage glad_glSampleCoverage
	GLAD_API_CALL PFNGLSAMPLEMASKIPROC glad_glSampleMaski;
#define glSampleMaski glad_glSampleMaski
	GLAD_API_CALL PFNGLSAMPLERPARAMETERIIVPROC glad_glSamplerParameterIiv;
#define glSamplerParameterIiv glad_glSamplerParameterIiv
	GLAD_API_CALL PFNGLSAMPLERPARAMETERIUIVPROC glad_glSamplerParameterIuiv;
#define glSamplerParameterIuiv glad_glSamplerParameterIuiv
	GLAD_API_CALL PFNGLSAMPLERPARAMETERFPROC glad_glSamplerParameterf;
#define glSamplerParameterf glad_glSamplerParameterf
	GLAD_API_CALL PFNGLSAMPLERPARAMETERFVPROC glad_glSamplerParameterfv;
#define glSamplerParameterfv glad_glSamplerParameterfv
	GLAD_API_CALL PFNGLSAMPLERPARAMETERIPROC glad_glSamplerParameteri;
#define glSamplerParameteri glad_glSamplerParameteri
	GLAD_API_CALL PFNGLSAMPLERPARAMETERIVPROC glad_glSamplerParameteriv;
#define glSamplerParameteriv glad_glSamplerParameteriv
	GLAD_API_CALL PFNGLSCALEDPROC glad_glScaled;
#define glScaled glad_glScaled
	GLAD_API_CALL PFNGLSCALEFPROC glad_glScalef;
#define glScalef glad_glScalef
	GLAD_API_CALL PFNGLSCISSORPROC glad_glScissor;
#define glScissor glad_glScissor
	GLAD_API_CALL PFNGLSECONDARYCOLOR3BPROC glad_glSecondaryColor3b;
#define glSecondaryColor3b glad_glSecondaryColor3b
	GLAD_API_CALL PFNGLSECONDARYCOLOR3BVPROC glad_glSecondaryColor3bv;
#define glSecondaryColor3bv glad_glSecondaryColor3bv
	GLAD_API_CALL PFNGLSECONDARYCOLOR3DPROC glad_glSecondaryColor3d;
#define glSecondaryColor3d glad_glSecondaryColor3d
	GLAD_API_CALL PFNGLSECONDARYCOLOR3DVPROC glad_glSecondaryColor3dv;
#define glSecondaryColor3dv glad_glSecondaryColor3dv
	GLAD_API_CALL PFNGLSECONDARYCOLOR3FPROC glad_glSecondaryColor3f;
#define glSecondaryColor3f glad_glSecondaryColor3f
	GLAD_API_CALL PFNGLSECONDARYCOLOR3FVPROC glad_glSecondaryColor3fv;
#define glSecondaryColor3fv glad_glSecondaryColor3fv
	GLAD_API_CALL PFNGLSECONDARYCOLOR3IPROC glad_glSecondaryColor3i;
#define glSecondaryColor3i glad_glSecondaryColor3i
	GLAD_API_CALL PFNGLSECONDARYCOLOR3IVPROC glad_glSecondaryColor3iv;
#define glSecondaryColor3iv glad_glSecondaryColor3iv
	GLAD_API_CALL PFNGLSECONDARYCOLOR3SPROC glad_glSecondaryColor3s;
#define glSecondaryColor3s glad_glSecondaryColor3s
	GLAD_API_CALL PFNGLSECONDARYCOLOR3SVPROC glad_glSecondaryColor3sv;
#define glSecondaryColor3sv glad_glSecondaryColor3sv
	GLAD_API_CALL PFNGLSECONDARYCOLOR3UBPROC glad_glSecondaryColor3ub;
#define glSecondaryColor3ub glad_glSecondaryColor3ub
	GLAD_API_CALL PFNGLSECONDARYCOLOR3UBVPROC glad_glSecondaryColor3ubv;
#define glSecondaryColor3ubv glad_glSecondaryColor3ubv
	GLAD_API_CALL PFNGLSECONDARYCOLOR3UIPROC glad_glSecondaryColor3ui;
#define glSecondaryColor3ui glad_glSecondaryColor3ui
	GLAD_API_CALL PFNGLSECONDARYCOLOR3UIVPROC glad_glSecondaryColor3uiv;
#define glSecondaryColor3uiv glad_glSecondaryColor3uiv
	GLAD_API_CALL PFNGLSECONDARYCOLOR3USPROC glad_glSecondaryColor3us;
#define glSecondaryColor3us glad_glSecondaryColor3us
	GLAD_API_CALL PFNGLSECONDARYCOLOR3USVPROC glad_glSecondaryColor3usv;
#define glSecondaryColor3usv glad_glSecondaryColor3usv
	GLAD_API_CALL PFNGLSECONDARYCOLORP3UIPROC glad_glSecondaryColorP3ui;
#define glSecondaryColorP3ui glad_glSecondaryColorP3ui
	GLAD_API_CALL PFNGLSECONDARYCOLORP3UIVPROC glad_glSecondaryColorP3uiv;
#define glSecondaryColorP3uiv glad_glSecondaryColorP3uiv
	GLAD_API_CALL PFNGLSECONDARYCOLORPOINTERPROC glad_glSecondaryColorPointer;
#define glSecondaryColorPointer glad_glSecondaryColorPointer
	GLAD_API_CALL PFNGLSELECTBUFFERPROC glad_glSelectBuffer;
#define glSelectBuffer glad_glSelectBuffer
	GLAD_API_CALL PFNGLSHADEMODELPROC glad_glShadeModel;
#define glShadeModel glad_glShadeModel
	GLAD_API_CALL PFNGLSHADERSOURCEPROC glad_glShaderSource;
#define glShaderSource glad_glShaderSource
	GLAD_API_CALL PFNGLSTENCILFUNCPROC glad_glStencilFunc;
#define glStencilFunc glad_glStencilFunc
	GLAD_API_CALL PFNGLSTENCILFUNCSEPARATEPROC glad_glStencilFuncSeparate;
#define glStencilFuncSeparate glad_glStencilFuncSeparate
	GLAD_API_CALL PFNGLSTENCILMASKPROC glad_glStencilMask;
#define glStencilMask glad_glStencilMask
	GLAD_API_CALL PFNGLSTENCILMASKSEPARATEPROC glad_glStencilMaskSeparate;
#define glStencilMaskSeparate glad_glStencilMaskSeparate
	GLAD_API_CALL PFNGLSTENCILOPPROC glad_glStencilOp;
#define glStencilOp glad_glStencilOp
	GLAD_API_CALL PFNGLSTENCILOPSEPARATEPROC glad_glStencilOpSeparate;
#define glStencilOpSeparate glad_glStencilOpSeparate
	GLAD_API_CALL PFNGLTEXBUFFERPROC glad_glTexBuffer;
#define glTexBuffer glad_glTexBuffer
	GLAD_API_CALL PFNGLTEXCOORD1DPROC glad_glTexCoord1d;
#define glTexCoord1d glad_glTexCoord1d
	GLAD_API_CALL PFNGLTEXCOORD1DVPROC glad_glTexCoord1dv;
#define glTexCoord1dv glad_glTexCoord1dv
	GLAD_API_CALL PFNGLTEXCOORD1FPROC glad_glTexCoord1f;
#define glTexCoord1f glad_glTexCoord1f
	GLAD_API_CALL PFNGLTEXCOORD1FVPROC glad_glTexCoord1fv;
#define glTexCoord1fv glad_glTexCoord1fv
	GLAD_API_CALL PFNGLTEXCOORD1IPROC glad_glTexCoord1i;
#define glTexCoord1i glad_glTexCoord1i
	GLAD_API_CALL PFNGLTEXCOORD1IVPROC glad_glTexCoord1iv;
#define glTexCoord1iv glad_glTexCoord1iv
	GLAD_API_CALL PFNGLTEXCOORD1SPROC glad_glTexCoord1s;
#define glTexCoord1s glad_glTexCoord1s
	GLAD_API_CALL PFNGLTEXCOORD1SVPROC glad_glTexCoord1sv;
#define glTexCoord1sv glad_glTexCoord1sv
	GLAD_API_CALL PFNGLTEXCOORD2DPROC glad_glTexCoord2d;
#define glTexCoord2d glad_glTexCoord2d
	GLAD_API_CALL PFNGLTEXCOORD2DVPROC glad_glTexCoord2dv;
#define glTexCoord2dv glad_glTexCoord2dv
	GLAD_API_CALL PFNGLTEXCOORD2FPROC glad_glTexCoord2f;
#define glTexCoord2f glad_glTexCoord2f
	GLAD_API_CALL PFNGLTEXCOORD2FVPROC glad_glTexCoord2fv;
#define glTexCoord2fv glad_glTexCoord2fv
	GLAD_API_CALL PFNGLTEXCOORD2IPROC glad_glTexCoord2i;
#define glTexCoord2i glad_glTexCoord2i
	GLAD_API_CALL PFNGLTEXCOORD2IVPROC glad_glTexCoord2iv;
#define glTexCoord2iv glad_glTexCoord2iv
	GLAD_API_CALL PFNGLTEXCOORD2SPROC glad_glTexCoord2s;
#define glTexCoord2s glad_glTexCoord2s
	GLAD_API_CALL PFNGLTEXCOORD2SVPROC glad_glTexCoord2sv;
#define glTexCoord2sv glad_glTexCoord2sv
	GLAD_API_CALL PFNGLTEXCOORD3DPROC glad_glTexCoord3d;
#define glTexCoord3d glad_glTexCoord3d
	GLAD_API_CALL PFNGLTEXCOORD3DVPROC glad_glTexCoord3dv;
#define glTexCoord3dv glad_glTexCoord3dv
	GLAD_API_CALL PFNGLTEXCOORD3FPROC glad_glTexCoord3f;
#define glTexCoord3f glad_glTexCoord3f
	GLAD_API_CALL PFNGLTEXCOORD3FVPROC glad_glTexCoord3fv;
#define glTexCoord3fv glad_glTexCoord3fv
	GLAD_API_CALL PFNGLTEXCOORD3IPROC glad_glTexCoord3i;
#define glTexCoord3i glad_glTexCoord3i
	GLAD_API_CALL PFNGLTEXCOORD3IVPROC glad_glTexCoord3iv;
#define glTexCoord3iv glad_glTexCoord3iv
	GLAD_API_CALL PFNGLTEXCOORD3SPROC glad_glTexCoord3s;
#define glTexCoord3s glad_glTexCoord3s
	GLAD_API_CALL PFNGLTEXCOORD3SVPROC glad_glTexCoord3sv;
#define glTexCoord3sv glad_glTexCoord3sv
	GLAD_API_CALL PFNGLTEXCOORD4DPROC glad_glTexCoord4d;
#define glTexCoord4d glad_glTexCoord4d
	GLAD_API_CALL PFNGLTEXCOORD4DVPROC glad_glTexCoord4dv;
#define glTexCoord4dv glad_glTexCoord4dv
	GLAD_API_CALL PFNGLTEXCOORD4FPROC glad_glTexCoord4f;
#define glTexCoord4f glad_glTexCoord4f
	GLAD_API_CALL PFNGLTEXCOORD4FVPROC glad_glTexCoord4fv;
#define glTexCoord4fv glad_glTexCoord4fv
	GLAD_API_CALL PFNGLTEXCOORD4IPROC glad_glTexCoord4i;
#define glTexCoord4i glad_glTexCoord4i
	GLAD_API_CALL PFNGLTEXCOORD4IVPROC glad_glTexCoord4iv;
#define glTexCoord4iv glad_glTexCoord4iv
	GLAD_API_CALL PFNGLTEXCOORD4SPROC glad_glTexCoord4s;
#define glTexCoord4s glad_glTexCoord4s
	GLAD_API_CALL PFNGLTEXCOORD4SVPROC glad_glTexCoord4sv;
#define glTexCoord4sv glad_glTexCoord4sv
	GLAD_API_CALL PFNGLTEXCOORDP1UIPROC glad_glTexCoordP1ui;
#define glTexCoordP1ui glad_glTexCoordP1ui
	GLAD_API_CALL PFNGLTEXCOORDP1UIVPROC glad_glTexCoordP1uiv;
#define glTexCoordP1uiv glad_glTexCoordP1uiv
	GLAD_API_CALL PFNGLTEXCOORDP2UIPROC glad_glTexCoordP2ui;
#define glTexCoordP2ui glad_glTexCoordP2ui
	GLAD_API_CALL PFNGLTEXCOORDP2UIVPROC glad_glTexCoordP2uiv;
#define glTexCoordP2uiv glad_glTexCoordP2uiv
	GLAD_API_CALL PFNGLTEXCOORDP3UIPROC glad_glTexCoordP3ui;
#define glTexCoordP3ui glad_glTexCoordP3ui
	GLAD_API_CALL PFNGLTEXCOORDP3UIVPROC glad_glTexCoordP3uiv;
#define glTexCoordP3uiv glad_glTexCoordP3uiv
	GLAD_API_CALL PFNGLTEXCOORDP4UIPROC glad_glTexCoordP4ui;
#define glTexCoordP4ui glad_glTexCoordP4ui
	GLAD_API_CALL PFNGLTEXCOORDP4UIVPROC glad_glTexCoordP4uiv;
#define glTexCoordP4uiv glad_glTexCoordP4uiv
	GLAD_API_CALL PFNGLTEXCOORDPOINTERPROC glad_glTexCoordPointer;
#define glTexCoordPointer glad_glTexCoordPointer
	GLAD_API_CALL PFNGLTEXENVFPROC glad_glTexEnvf;
#define glTexEnvf glad_glTexEnvf
	GLAD_API_CALL PFNGLTEXENVFVPROC glad_glTexEnvfv;
#define glTexEnvfv glad_glTexEnvfv
	GLAD_API_CALL PFNGLTEXENVIPROC glad_glTexEnvi;
#define glTexEnvi glad_glTexEnvi
	GLAD_API_CALL PFNGLTEXENVIVPROC glad_glTexEnviv;
#define glTexEnviv glad_glTexEnviv
	GLAD_API_CALL PFNGLTEXGENDPROC glad_glTexGend;
#define glTexGend glad_glTexGend
	GLAD_API_CALL PFNGLTEXGENDVPROC glad_glTexGendv;
#define glTexGendv glad_glTexGendv
	GLAD_API_CALL PFNGLTEXGENFPROC glad_glTexGenf;
#define glTexGenf glad_glTexGenf
	GLAD_API_CALL PFNGLTEXGENFVPROC glad_glTexGenfv;
#define glTexGenfv glad_glTexGenfv
	GLAD_API_CALL PFNGLTEXGENIPROC glad_glTexGeni;
#define glTexGeni glad_glTexGeni
	GLAD_API_CALL PFNGLTEXGENIVPROC glad_glTexGeniv;
#define glTexGeniv glad_glTexGeniv
	GLAD_API_CALL PFNGLTEXIMAGE1DPROC glad_glTexImage1D;
#define glTexImage1D glad_glTexImage1D
	GLAD_API_CALL PFNGLTEXIMAGE2DPROC glad_glTexImage2D;
#define glTexImage2D glad_glTexImage2D
	GLAD_API_CALL PFNGLTEXIMAGE2DMULTISAMPLEPROC glad_glTexImage2DMultisample;
#define glTexImage2DMultisample glad_glTexImage2DMultisample
	GLAD_API_CALL PFNGLTEXIMAGE3DPROC glad_glTexImage3D;
#define glTexImage3D glad_glTexImage3D
	GLAD_API_CALL PFNGLTEXIMAGE3DMULTISAMPLEPROC glad_glTexImage3DMultisample;
#define glTexImage3DMultisample glad_glTexImage3DMultisample
	GLAD_API_CALL PFNGLTEXPARAMETERIIVPROC glad_glTexParameterIiv;
#define glTexParameterIiv glad_glTexParameterIiv
	GLAD_API_CALL PFNGLTEXPARAMETERIUIVPROC glad_glTexParameterIuiv;
#define glTexParameterIuiv glad_glTexParameterIuiv
	GLAD_API_CALL PFNGLTEXPARAMETERFPROC glad_glTexParameterf;
#define glTexParameterf glad_glTexParameterf
	GLAD_API_CALL PFNGLTEXPARAMETERFVPROC glad_glTexParameterfv;
#define glTexParameterfv glad_glTexParameterfv
	GLAD_API_CALL PFNGLTEXPARAMETERIPROC glad_glTexParameteri;
#define glTexParameteri glad_glTexParameteri
	GLAD_API_CALL PFNGLTEXPARAMETERIVPROC glad_glTexParameteriv;
#define glTexParameteriv glad_glTexParameteriv
	GLAD_API_CALL PFNGLTEXSUBIMAGE1DPROC glad_glTexSubImage1D;
#define glTexSubImage1D glad_glTexSubImage1D
	GLAD_API_CALL PFNGLTEXSUBIMAGE2DPROC glad_glTexSubImage2D;
#define glTexSubImage2D glad_glTexSubImage2D
	GLAD_API_CALL PFNGLTEXSUBIMAGE3DPROC glad_glTexSubImage3D;
#define glTexSubImage3D glad_glTexSubImage3D
	GLAD_API_CALL PFNGLTRANSFORMFEEDBACKVARYINGSPROC glad_glTransformFeedbackVaryings;
#define glTransformFeedbackVaryings glad_glTransformFeedbackVaryings
	GLAD_API_CALL PFNGLTRANSLATEDPROC glad_glTranslated;
#define glTranslated glad_glTranslated
	GLAD_API_CALL PFNGLTRANSLATEFPROC glad_glTranslatef;
#define glTranslatef glad_glTranslatef
	GLAD_API_CALL PFNGLUNIFORM1FPROC glad_glUniform1f;
#define glUniform1f glad_glUniform1f
	GLAD_API_CALL PFNGLUNIFORM1FVPROC glad_glUniform1fv;
#define glUniform1fv glad_glUniform1fv
	GLAD_API_CALL PFNGLUNIFORM1IPROC glad_glUniform1i;
#define glUniform1i glad_glUniform1i
	GLAD_API_CALL PFNGLUNIFORM1IVPROC glad_glUniform1iv;
#define glUniform1iv glad_glUniform1iv
	GLAD_API_CALL PFNGLUNIFORM1UIPROC glad_glUniform1ui;
#define glUniform1ui glad_glUniform1ui
	GLAD_API_CALL PFNGLUNIFORM1UIVPROC glad_glUniform1uiv;
#define glUniform1uiv glad_glUniform1uiv
	GLAD_API_CALL PFNGLUNIFORM2FPROC glad_glUniform2f;
#define glUniform2f glad_glUniform2f
	GLAD_API_CALL PFNGLUNIFORM2FVPROC glad_glUniform2fv;
#define glUniform2fv glad_glUniform2fv
	GLAD_API_CALL PFNGLUNIFORM2IPROC glad_glUniform2i;
#define glUniform2i glad_glUniform2i
	GLAD_API_CALL PFNGLUNIFORM2IVPROC glad_glUniform2iv;
#define glUniform2iv glad_glUniform2iv
	GLAD_API_CALL PFNGLUNIFORM2UIPROC glad_glUniform2ui;
#define glUniform2ui glad_glUniform2ui
	GLAD_API_CALL PFNGLUNIFORM2UIVPROC glad_glUniform2uiv;
#define glUniform2uiv glad_glUniform2uiv
	GLAD_API_CALL PFNGLUNIFORM3FPROC glad_glUniform3f;
#define glUniform3f glad_glUniform3f
	GLAD_API_CALL PFNGLUNIFORM3FVPROC glad_glUniform3fv;
#define glUniform3fv glad_glUniform3fv
	GLAD_API_CALL PFNGLUNIFORM3IPROC glad_glUniform3i;
#define glUniform3i glad_glUniform3i
	GLAD_API_CALL PFNGLUNIFORM3IVPROC glad_glUniform3iv;
#define glUniform3iv glad_glUniform3iv
	GLAD_API_CALL PFNGLUNIFORM3UIPROC glad_glUniform3ui;
#define glUniform3ui glad_glUniform3ui
	GLAD_API_CALL PFNGLUNIFORM3UIVPROC glad_glUniform3uiv;
#define glUniform3uiv glad_glUniform3uiv
	GLAD_API_CALL PFNGLUNIFORM4FPROC glad_glUniform4f;
#define glUniform4f glad_glUniform4f
	GLAD_API_CALL PFNGLUNIFORM4FVPROC glad_glUniform4fv;
#define glUniform4fv glad_glUniform4fv
	GLAD_API_CALL PFNGLUNIFORM4IPROC glad_glUniform4i;
#define glUniform4i glad_glUniform4i
	GLAD_API_CALL PFNGLUNIFORM4IVPROC glad_glUniform4iv;
#define glUniform4iv glad_glUniform4iv
	GLAD_API_CALL PFNGLUNIFORM4UIPROC glad_glUniform4ui;
#define glUniform4ui glad_glUniform4ui
	GLAD_API_CALL PFNGLUNIFORM4UIVPROC glad_glUniform4uiv;
#define glUniform4uiv glad_glUniform4uiv
	GLAD_API_CALL PFNGLUNIFORMBLOCKBINDINGPROC glad_glUniformBlockBinding;
#define glUniformBlockBinding glad_glUniformBlockBinding
	GLAD_API_CALL PFNGLUNIFORMMATRIX2FVPROC glad_glUniformMatrix2fv;
#define glUniformMatrix2fv glad_glUniformMatrix2fv
	GLAD_API_CALL PFNGLUNIFORMMATRIX2X3FVPROC glad_glUniformMatrix2x3fv;
#define glUniformMatrix2x3fv glad_glUniformMatrix2x3fv
	GLAD_API_CALL PFNGLUNIFORMMATRIX2X4FVPROC glad_glUniformMatrix2x4fv;
#define glUniformMatrix2x4fv glad_glUniformMatrix2x4fv
	GLAD_API_CALL PFNGLUNIFORMMATRIX3FVPROC glad_glUniformMatrix3fv;
#define glUniformMatrix3fv glad_glUniformMatrix3fv
	GLAD_API_CALL PFNGLUNIFORMMATRIX3X2FVPROC glad_glUniformMatrix3x2fv;
#define glUniformMatrix3x2fv glad_glUniformMatrix3x2fv
	GLAD_API_CALL PFNGLUNIFORMMATRIX3X4FVPROC glad_glUniformMatrix3x4fv;
#define glUniformMatrix3x4fv glad_glUniformMatrix3x4fv
	GLAD_API_CALL PFNGLUNIFORMMATRIX4FVPROC glad_glUniformMatrix4fv;
#define glUniformMatrix4fv glad_glUniformMatrix4fv
	GLAD_API_CALL PFNGLUNIFORMMATRIX4X2FVPROC glad_glUniformMatrix4x2fv;
#define glUniformMatrix4x2fv glad_glUniformMatrix4x2fv
	GLAD_API_CALL PFNGLUNIFORMMATRIX4X3FVPROC glad_glUniformMatrix4x3fv;
#define glUniformMatrix4x3fv glad_glUniformMatrix4x3fv
	GLAD_API_CALL PFNGLUNMAPBUFFERPROC glad_glUnmapBuffer;
#define glUnmapBuffer glad_glUnmapBuffer
	GLAD_API_CALL PFNGLUSEPROGRAMPROC glad_glUseProgram;
#define glUseProgram glad_glUseProgram
	GLAD_API_CALL PFNGLVALIDATEPROGRAMPROC glad_glValidateProgram;
#define glValidateProgram glad_glValidateProgram
	GLAD_API_CALL PFNGLVERTEX2DPROC glad_glVertex2d;
#define glVertex2d glad_glVertex2d
	GLAD_API_CALL PFNGLVERTEX2DVPROC glad_glVertex2dv;
#define glVertex2dv glad_glVertex2dv
	GLAD_API_CALL PFNGLVERTEX2FPROC glad_glVertex2f;
#define glVertex2f glad_glVertex2f
	GLAD_API_CALL PFNGLVERTEX2FVPROC glad_glVertex2fv;
#define glVertex2fv glad_glVertex2fv
	GLAD_API_CALL PFNGLVERTEX2IPROC glad_glVertex2i;
#define glVertex2i glad_glVertex2i
	GLAD_API_CALL PFNGLVERTEX2IVPROC glad_glVertex2iv;
#define glVertex2iv glad_glVertex2iv
	GLAD_API_CALL PFNGLVERTEX2SPROC glad_glVertex2s;
#define glVertex2s glad_glVertex2s
	GLAD_API_CALL PFNGLVERTEX2SVPROC glad_glVertex2sv;
#define glVertex2sv glad_glVertex2sv
	GLAD_API_CALL PFNGLVERTEX3DPROC glad_glVertex3d;
#define glVertex3d glad_glVertex3d
	GLAD_API_CALL PFNGLVERTEX3DVPROC glad_glVertex3dv;
#define glVertex3dv glad_glVertex3dv
	GLAD_API_CALL PFNGLVERTEX3FPROC glad_glVertex3f;
#define glVertex3f glad_glVertex3f
	GLAD_API_CALL PFNGLVERTEX3FVPROC glad_glVertex3fv;
#define glVertex3fv glad_glVertex3fv
	GLAD_API_CALL PFNGLVERTEX3IPROC glad_glVertex3i;
#define glVertex3i glad_glVertex3i
	GLAD_API_CALL PFNGLVERTEX3IVPROC glad_glVertex3iv;
#define glVertex3iv glad_glVertex3iv
	GLAD_API_CALL PFNGLVERTEX3SPROC glad_glVertex3s;
#define glVertex3s glad_glVertex3s
	GLAD_API_CALL PFNGLVERTEX3SVPROC glad_glVertex3sv;
#define glVertex3sv glad_glVertex3sv
	GLAD_API_CALL PFNGLVERTEX4DPROC glad_glVertex4d;
#define glVertex4d glad_glVertex4d
	GLAD_API_CALL PFNGLVERTEX4DVPROC glad_glVertex4dv;
#define glVertex4dv glad_glVertex4dv
	GLAD_API_CALL PFNGLVERTEX4FPROC glad_glVertex4f;
#define glVertex4f glad_glVertex4f
	GLAD_API_CALL PFNGLVERTEX4FVPROC glad_glVertex4fv;
#define glVertex4fv glad_glVertex4fv
	GLAD_API_CALL PFNGLVERTEX4IPROC glad_glVertex4i;
#define glVertex4i glad_glVertex4i
	GLAD_API_CALL PFNGLVERTEX4IVPROC glad_glVertex4iv;
#define glVertex4iv glad_glVertex4iv
	GLAD_API_CALL PFNGLVERTEX4SPROC glad_glVertex4s;
#define glVertex4s glad_glVertex4s
	GLAD_API_CALL PFNGLVERTEX4SVPROC glad_glVertex4sv;
#define glVertex4sv glad_glVertex4sv
	GLAD_API_CALL PFNGLVERTEXATTRIB1DPROC glad_glVertexAttrib1d;
#define glVertexAttrib1d glad_glVertexAttrib1d
	GLAD_API_CALL PFNGLVERTEXATTRIB1DVPROC glad_glVertexAttrib1dv;
#define glVertexAttrib1dv glad_glVertexAttrib1dv
	GLAD_API_CALL PFNGLVERTEXATTRIB1FPROC glad_glVertexAttrib1f;
#define glVertexAttrib1f glad_glVertexAttrib1f
	GLAD_API_CALL PFNGLVERTEXATTRIB1FVPROC glad_glVertexAttrib1fv;
#define glVertexAttrib1fv glad_glVertexAttrib1fv
	GLAD_API_CALL PFNGLVERTEXATTRIB1SPROC glad_glVertexAttrib1s;
#define glVertexAttrib1s glad_glVertexAttrib1s
	GLAD_API_CALL PFNGLVERTEXATTRIB1SVPROC glad_glVertexAttrib1sv;
#define glVertexAttrib1sv glad_glVertexAttrib1sv
	GLAD_API_CALL PFNGLVERTEXATTRIB2DPROC glad_glVertexAttrib2d;
#define glVertexAttrib2d glad_glVertexAttrib2d
	GLAD_API_CALL PFNGLVERTEXATTRIB2DVPROC glad_glVertexAttrib2dv;
#define glVertexAttrib2dv glad_glVertexAttrib2dv
	GLAD_API_CALL PFNGLVERTEXATTRIB2FPROC glad_glVertexAttrib2f;
#define glVertexAttrib2f glad_glVertexAttrib2f
	GLAD_API_CALL PFNGLVERTEXATTRIB2FVPROC glad_glVertexAttrib2fv;
#define glVertexAttrib2fv glad_glVertexAttrib2fv
	GLAD_API_CALL PFNGLVERTEXATTRIB2SPROC glad_glVertexAttrib2s;
#define glVertexAttrib2s glad_glVertexAttrib2s
	GLAD_API_CALL PFNGLVERTEXATTRIB2SVPROC glad_glVertexAttrib2sv;
#define glVertexAttrib2sv glad_glVertexAttrib2sv
	GLAD_API_CALL PFNGLVERTEXATTRIB3DPROC glad_glVertexAttrib3d;
#define glVertexAttrib3d glad_glVertexAttrib3d
	GLAD_API_CALL PFNGLVERTEXATTRIB3DVPROC glad_glVertexAttrib3dv;
#define glVertexAttrib3dv glad_glVertexAttrib3dv
	GLAD_API_CALL PFNGLVERTEXATTRIB3FPROC glad_glVertexAttrib3f;
#define glVertexAttrib3f glad_glVertexAttrib3f
	GLAD_API_CALL PFNGLVERTEXATTRIB3FVPROC glad_glVertexAttrib3fv;
#define glVertexAttrib3fv glad_glVertexAttrib3fv
	GLAD_API_CALL PFNGLVERTEXATTRIB3SPROC glad_glVertexAttrib3s;
#define glVertexAttrib3s glad_glVertexAttrib3s
	GLAD_API_CALL PFNGLVERTEXATTRIB3SVPROC glad_glVertexAttrib3sv;
#define glVertexAttrib3sv glad_glVertexAttrib3sv
	GLAD_API_CALL PFNGLVERTEXATTRIB4NBVPROC glad_glVertexAttrib4Nbv;
#define glVertexAttrib4Nbv glad_glVertexAttrib4Nbv
	GLAD_API_CALL PFNGLVERTEXATTRIB4NIVPROC glad_glVertexAttrib4Niv;
#define glVertexAttrib4Niv glad_glVertexAttrib4Niv
	GLAD_API_CALL PFNGLVERTEXATTRIB4NSVPROC glad_glVertexAttrib4Nsv;
#define glVertexAttrib4Nsv glad_glVertexAttrib4Nsv
	GLAD_API_CALL PFNGLVERTEXATTRIB4NUBPROC glad_glVertexAttrib4Nub;
#define glVertexAttrib4Nub glad_glVertexAttrib4Nub
	GLAD_API_CALL PFNGLVERTEXATTRIB4NUBVPROC glad_glVertexAttrib4Nubv;
#define glVertexAttrib4Nubv glad_glVertexAttrib4Nubv
	GLAD_API_CALL PFNGLVERTEXATTRIB4NUIVPROC glad_glVertexAttrib4Nuiv;
#define glVertexAttrib4Nuiv glad_glVertexAttrib4Nuiv
	GLAD_API_CALL PFNGLVERTEXATTRIB4NUSVPROC glad_glVertexAttrib4Nusv;
#define glVertexAttrib4Nusv glad_glVertexAttrib4Nusv
	GLAD_API_CALL PFNGLVERTEXATTRIB4BVPROC glad_glVertexAttrib4bv;
#define glVertexAttrib4bv glad_glVertexAttrib4bv
	GLAD_API_CALL PFNGLVERTEXATTRIB4DPROC glad_glVertexAttrib4d;
#define glVertexAttrib4d glad_glVertexAttrib4d
	GLAD_API_CALL PFNGLVERTEXATTRIB4DVPROC glad_glVertexAttrib4dv;
#define glVertexAttrib4dv glad_glVertexAttrib4dv
	GLAD_API_CALL PFNGLVERTEXATTRIB4FPROC glad_glVertexAttrib4f;
#define glVertexAttrib4f glad_glVertexAttrib4f
	GLAD_API_CALL PFNGLVERTEXATTRIB4FVPROC glad_glVertexAttrib4fv;
#define glVertexAttrib4fv glad_glVertexAttrib4fv
	GLAD_API_CALL PFNGLVERTEXATTRIB4IVPROC glad_glVertexAttrib4iv;
#define glVertexAttrib4iv glad_glVertexAttrib4iv
	GLAD_API_CALL PFNGLVERTEXATTRIB4SPROC glad_glVertexAttrib4s;
#define glVertexAttrib4s glad_glVertexAttrib4s
	GLAD_API_CALL PFNGLVERTEXATTRIB4SVPROC glad_glVertexAttrib4sv;
#define glVertexAttrib4sv glad_glVertexAttrib4sv
	GLAD_API_CALL PFNGLVERTEXATTRIB4UBVPROC glad_glVertexAttrib4ubv;
#define glVertexAttrib4ubv glad_glVertexAttrib4ubv
	GLAD_API_CALL PFNGLVERTEXATTRIB4UIVPROC glad_glVertexAttrib4uiv;
#define glVertexAttrib4uiv glad_glVertexAttrib4uiv
	GLAD_API_CALL PFNGLVERTEXATTRIB4USVPROC glad_glVertexAttrib4usv;
#define glVertexAttrib4usv glad_glVertexAttrib4usv
	GLAD_API_CALL PFNGLVERTEXATTRIBDIVISORPROC glad_glVertexAttribDivisor;
#define glVertexAttribDivisor glad_glVertexAttribDivisor
	GLAD_API_CALL PFNGLVERTEXATTRIBI1IPROC glad_glVertexAttribI1i;
#define glVertexAttribI1i glad_glVertexAttribI1i
	GLAD_API_CALL PFNGLVERTEXATTRIBI1IVPROC glad_glVertexAttribI1iv;
#define glVertexAttribI1iv glad_glVertexAttribI1iv
	GLAD_API_CALL PFNGLVERTEXATTRIBI1UIPROC glad_glVertexAttribI1ui;
#define glVertexAttribI1ui glad_glVertexAttribI1ui
	GLAD_API_CALL PFNGLVERTEXATTRIBI1UIVPROC glad_glVertexAttribI1uiv;
#define glVertexAttribI1uiv glad_glVertexAttribI1uiv
	GLAD_API_CALL PFNGLVERTEXATTRIBI2IPROC glad_glVertexAttribI2i;
#define glVertexAttribI2i glad_glVertexAttribI2i
	GLAD_API_CALL PFNGLVERTEXATTRIBI2IVPROC glad_glVertexAttribI2iv;
#define glVertexAttribI2iv glad_glVertexAttribI2iv
	GLAD_API_CALL PFNGLVERTEXATTRIBI2UIPROC glad_glVertexAttribI2ui;
#define glVertexAttribI2ui glad_glVertexAttribI2ui
	GLAD_API_CALL PFNGLVERTEXATTRIBI2UIVPROC glad_glVertexAttribI2uiv;
#define glVertexAttribI2uiv glad_glVertexAttribI2uiv
	GLAD_API_CALL PFNGLVERTEXATTRIBI3IPROC glad_glVertexAttribI3i;
#define glVertexAttribI3i glad_glVertexAttribI3i
	GLAD_API_CALL PFNGLVERTEXATTRIBI3IVPROC glad_glVertexAttribI3iv;
#define glVertexAttribI3iv glad_glVertexAttribI3iv
	GLAD_API_CALL PFNGLVERTEXATTRIBI3UIPROC glad_glVertexAttribI3ui;
#define glVertexAttribI3ui glad_glVertexAttribI3ui
	GLAD_API_CALL PFNGLVERTEXATTRIBI3UIVPROC glad_glVertexAttribI3uiv;
#define glVertexAttribI3uiv glad_glVertexAttribI3uiv
	GLAD_API_CALL PFNGLVERTEXATTRIBI4BVPROC glad_glVertexAttribI4bv;
#define glVertexAttribI4bv glad_glVertexAttribI4bv
	GLAD_API_CALL PFNGLVERTEXATTRIBI4IPROC glad_glVertexAttribI4i;
#define glVertexAttribI4i glad_glVertexAttribI4i
	GLAD_API_CALL PFNGLVERTEXATTRIBI4IVPROC glad_glVertexAttribI4iv;
#define glVertexAttribI4iv glad_glVertexAttribI4iv
	GLAD_API_CALL PFNGLVERTEXATTRIBI4SVPROC glad_glVertexAttribI4sv;
#define glVertexAttribI4sv glad_glVertexAttribI4sv
	GLAD_API_CALL PFNGLVERTEXATTRIBI4UBVPROC glad_glVertexAttribI4ubv;
#define glVertexAttribI4ubv glad_glVertexAttribI4ubv
	GLAD_API_CALL PFNGLVERTEXATTRIBI4UIPROC glad_glVertexAttribI4ui;
#define glVertexAttribI4ui glad_glVertexAttribI4ui
	GLAD_API_CALL PFNGLVERTEXATTRIBI4UIVPROC glad_glVertexAttribI4uiv;
#define glVertexAttribI4uiv glad_glVertexAttribI4uiv
	GLAD_API_CALL PFNGLVERTEXATTRIBI4USVPROC glad_glVertexAttribI4usv;
#define glVertexAttribI4usv glad_glVertexAttribI4usv
	GLAD_API_CALL PFNGLVERTEXATTRIBIPOINTERPROC glad_glVertexAttribIPointer;
#define glVertexAttribIPointer glad_glVertexAttribIPointer
	GLAD_API_CALL PFNGLVERTEXATTRIBP1UIPROC glad_glVertexAttribP1ui;
#define glVertexAttribP1ui glad_glVertexAttribP1ui
	GLAD_API_CALL PFNGLVERTEXATTRIBP1UIVPROC glad_glVertexAttribP1uiv;
#define glVertexAttribP1uiv glad_glVertexAttribP1uiv
	GLAD_API_CALL PFNGLVERTEXATTRIBP2UIPROC glad_glVertexAttribP2ui;
#define glVertexAttribP2ui glad_glVertexAttribP2ui
	GLAD_API_CALL PFNGLVERTEXATTRIBP2UIVPROC glad_glVertexAttribP2uiv;
#define glVertexAttribP2uiv glad_glVertexAttribP2uiv
	GLAD_API_CALL PFNGLVERTEXATTRIBP3UIPROC glad_glVertexAttribP3ui;
#define glVertexAttribP3ui glad_glVertexAttribP3ui
	GLAD_API_CALL PFNGLVERTEXATTRIBP3UIVPROC glad_glVertexAttribP3uiv;
#define glVertexAttribP3uiv glad_glVertexAttribP3uiv
	GLAD_API_CALL PFNGLVERTEXATTRIBP4UIPROC glad_glVertexAttribP4ui;
#define glVertexAttribP4ui glad_glVertexAttribP4ui
	GLAD_API_CALL PFNGLVERTEXATTRIBP4UIVPROC glad_glVertexAttribP4uiv;
#define glVertexAttribP4uiv glad_glVertexAttribP4uiv
	GLAD_API_CALL PFNGLVERTEXATTRIBPOINTERPROC glad_glVertexAttribPointer;
#define glVertexAttribPointer glad_glVertexAttribPointer
	GLAD_API_CALL PFNGLVERTEXP2UIPROC glad_glVertexP2ui;
#define glVertexP2ui glad_glVertexP2ui
	GLAD_API_CALL PFNGLVERTEXP2UIVPROC glad_glVertexP2uiv;
#define glVertexP2uiv glad_glVertexP2uiv
	GLAD_API_CALL PFNGLVERTEXP3UIPROC glad_glVertexP3ui;
#define glVertexP3ui glad_glVertexP3ui
	GLAD_API_CALL PFNGLVERTEXP3UIVPROC glad_glVertexP3uiv;
#define glVertexP3uiv glad_glVertexP3uiv
	GLAD_API_CALL PFNGLVERTEXP4UIPROC glad_glVertexP4ui;
#define glVertexP4ui glad_glVertexP4ui
	GLAD_API_CALL PFNGLVERTEXP4UIVPROC glad_glVertexP4uiv;
#define glVertexP4uiv glad_glVertexP4uiv
	GLAD_API_CALL PFNGLVERTEXPOINTERPROC glad_glVertexPointer;
#define glVertexPointer glad_glVertexPointer
	GLAD_API_CALL PFNGLVIEWPORTPROC glad_glViewport;
#define glViewport glad_glViewport
	GLAD_API_CALL PFNGLWAITSYNCPROC glad_glWaitSync;
#define glWaitSync glad_glWaitSync
	GLAD_API_CALL PFNGLWINDOWPOS2DPROC glad_glWindowPos2d;
#define glWindowPos2d glad_glWindowPos2d
	GLAD_API_CALL PFNGLWINDOWPOS2DVPROC glad_glWindowPos2dv;
#define glWindowPos2dv glad_glWindowPos2dv
	GLAD_API_CALL PFNGLWINDOWPOS2FPROC glad_glWindowPos2f;
#define glWindowPos2f glad_glWindowPos2f
	GLAD_API_CALL PFNGLWINDOWPOS2FVPROC glad_glWindowPos2fv;
#define glWindowPos2fv glad_glWindowPos2fv
	GLAD_API_CALL PFNGLWINDOWPOS2IPROC glad_glWindowPos2i;
#define glWindowPos2i glad_glWindowPos2i
	GLAD_API_CALL PFNGLWINDOWPOS2IVPROC glad_glWindowPos2iv;
#define glWindowPos2iv glad_glWindowPos2iv
	GLAD_API_CALL PFNGLWINDOWPOS2SPROC glad_glWindowPos2s;
#define glWindowPos2s glad_glWindowPos2s
	GLAD_API_CALL PFNGLWINDOWPOS2SVPROC glad_glWindowPos2sv;
#define glWindowPos2sv glad_glWindowPos2sv
	GLAD_API_CALL PFNGLWINDOWPOS3DPROC glad_glWindowPos3d;
#define glWindowPos3d glad_glWindowPos3d
	GLAD_API_CALL PFNGLWINDOWPOS3DVPROC glad_glWindowPos3dv;
#define glWindowPos3dv glad_glWindowPos3dv
	GLAD_API_CALL PFNGLWINDOWPOS3FPROC glad_glWindowPos3f;
#define glWindowPos3f glad_glWindowPos3f
	GLAD_API_CALL PFNGLWINDOWPOS3FVPROC glad_glWindowPos3fv;
#define glWindowPos3fv glad_glWindowPos3fv
	GLAD_API_CALL PFNGLWINDOWPOS3IPROC glad_glWindowPos3i;
#define glWindowPos3i glad_glWindowPos3i
	GLAD_API_CALL PFNGLWINDOWPOS3IVPROC glad_glWindowPos3iv;
#define glWindowPos3iv glad_glWindowPos3iv
	GLAD_API_CALL PFNGLWINDOWPOS3SPROC glad_glWindowPos3s;
#define glWindowPos3s glad_glWindowPos3s
	GLAD_API_CALL PFNGLWINDOWPOS3SVPROC glad_glWindowPos3sv;
#define glWindowPos3sv glad_glWindowPos3sv





	GLAD_API_CALL int gladLoadGLUserPtr(GLADuserptrloadfunc load, void* userptr);
	GLAD_API_CALL int gladLoadGL(GLADloadfunc load);


#ifdef GLAD_GL

	GLAD_API_CALL int gladLoaderLoadGL(void);
	GLAD_API_CALL void gladLoaderUnloadGL(void);

#endif

#ifdef __cplusplus
}
#endif
#endif

/* Source */
#ifdef GLAD_GL_IMPLEMENTATION
/**
 * SPDX-License-Identifier: (WTFPL OR CC0-1.0) AND Apache-2.0
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef GLAD_IMPL_UTIL_C_
#define GLAD_IMPL_UTIL_C_

#ifdef _MSC_VER
#define GLAD_IMPL_UTIL_SSCANF sscanf_s
#else
#define GLAD_IMPL_UTIL_SSCANF sscanf
#endif

#endif /* GLAD_IMPL_UTIL_C_ */

#ifdef __cplusplus
extern "C" {
#endif



	int GLAD_GL_VERSION_1_0 = 0;
	int GLAD_GL_VERSION_1_1 = 0;
	int GLAD_GL_VERSION_1_2 = 0;
	int GLAD_GL_VERSION_1_3 = 0;
	int GLAD_GL_VERSION_1_4 = 0;
	int GLAD_GL_VERSION_1_5 = 0;
	int GLAD_GL_VERSION_2_0 = 0;
	int GLAD_GL_VERSION_2_1 = 0;
	int GLAD_GL_VERSION_3_0 = 0;
	int GLAD_GL_VERSION_3_1 = 0;
	int GLAD_GL_VERSION_3_2 = 0;
	int GLAD_GL_VERSION_3_3 = 0;



	PFNGLACCUMPROC glad_glAccum = NULL;
	PFNGLACTIVETEXTUREPROC glad_glActiveTexture = NULL;
	PFNGLALPHAFUNCPROC glad_glAlphaFunc = NULL;
	PFNGLARETEXTURESRESIDENTPROC glad_glAreTexturesResident = NULL;
	PFNGLARRAYELEMENTPROC glad_glArrayElement = NULL;
	PFNGLATTACHSHADERPROC glad_glAttachShader = NULL;
	PFNGLBEGINPROC glad_glBegin = NULL;
	PFNGLBEGINCONDITIONALRENDERPROC glad_glBeginConditionalRender = NULL;
	PFNGLBEGINQUERYPROC glad_glBeginQuery = NULL;
	PFNGLBEGINTRANSFORMFEEDBACKPROC glad_glBeginTransformFeedback = NULL;
	PFNGLBINDATTRIBLOCATIONPROC glad_glBindAttribLocation = NULL;
	PFNGLBINDBUFFERPROC glad_glBindBuffer = NULL;
	PFNGLBINDBUFFERBASEPROC glad_glBindBufferBase = NULL;
	PFNGLBINDBUFFERRANGEPROC glad_glBindBufferRange = NULL;
	PFNGLBINDFRAGDATALOCATIONPROC glad_glBindFragDataLocation = NULL;
	PFNGLBINDFRAGDATALOCATIONINDEXEDPROC glad_glBindFragDataLocationIndexed = NULL;
	PFNGLBINDFRAMEBUFFERPROC glad_glBindFramebuffer = NULL;
	PFNGLBINDRENDERBUFFERPROC glad_glBindRenderbuffer = NULL;
	PFNGLBINDSAMPLERPROC glad_glBindSampler = NULL;
	PFNGLBINDTEXTUREPROC glad_glBindTexture = NULL;
	PFNGLBINDVERTEXARRAYPROC glad_glBindVertexArray = NULL;
	PFNGLBITMAPPROC glad_glBitmap = NULL;
	PFNGLBLENDCOLORPROC glad_glBlendColor = NULL;
	PFNGLBLENDEQUATIONPROC glad_glBlendEquation = NULL;
	PFNGLBLENDEQUATIONSEPARATEPROC glad_glBlendEquationSeparate = NULL;
	PFNGLBLENDFUNCPROC glad_glBlendFunc = NULL;
	PFNGLBLENDFUNCSEPARATEPROC glad_glBlendFuncSeparate = NULL;
	PFNGLBLITFRAMEBUFFERPROC glad_glBlitFramebuffer = NULL;
	PFNGLBUFFERDATAPROC glad_glBufferData = NULL;
	PFNGLBUFFERSUBDATAPROC glad_glBufferSubData = NULL;
	PFNGLCALLLISTPROC glad_glCallList = NULL;
	PFNGLCALLLISTSPROC glad_glCallLists = NULL;
	PFNGLCHECKFRAMEBUFFERSTATUSPROC glad_glCheckFramebufferStatus = NULL;
	PFNGLCLAMPCOLORPROC glad_glClampColor = NULL;
	PFNGLCLEARPROC glad_glClear = NULL;
	PFNGLCLEARACCUMPROC glad_glClearAccum = NULL;
	PFNGLCLEARBUFFERFIPROC glad_glClearBufferfi = NULL;
	PFNGLCLEARBUFFERFVPROC glad_glClearBufferfv = NULL;
	PFNGLCLEARBUFFERIVPROC glad_glClearBufferiv = NULL;
	PFNGLCLEARBUFFERUIVPROC glad_glClearBufferuiv = NULL;
	PFNGLCLEARCOLORPROC glad_glClearColor = NULL;
	PFNGLCLEARDEPTHPROC glad_glClearDepth = NULL;
	PFNGLCLEARINDEXPROC glad_glClearIndex = NULL;
	PFNGLCLEARSTENCILPROC glad_glClearStencil = NULL;
	PFNGLCLIENTACTIVETEXTUREPROC glad_glClientActiveTexture = NULL;
	PFNGLCLIENTWAITSYNCPROC glad_glClientWaitSync = NULL;
	PFNGLCLIPPLANEPROC glad_glClipPlane = NULL;
	PFNGLCOLOR3BPROC glad_glColor3b = NULL;
	PFNGLCOLOR3BVPROC glad_glColor3bv = NULL;
	PFNGLCOLOR3DPROC glad_glColor3d = NULL;
	PFNGLCOLOR3DVPROC glad_glColor3dv = NULL;
	PFNGLCOLOR3FPROC glad_glColor3f = NULL;
	PFNGLCOLOR3FVPROC glad_glColor3fv = NULL;
	PFNGLCOLOR3IPROC glad_glColor3i = NULL;
	PFNGLCOLOR3IVPROC glad_glColor3iv = NULL;
	PFNGLCOLOR3SPROC glad_glColor3s = NULL;
	PFNGLCOLOR3SVPROC glad_glColor3sv = NULL;
	PFNGLCOLOR3UBPROC glad_glColor3ub = NULL;
	PFNGLCOLOR3UBVPROC glad_glColor3ubv = NULL;
	PFNGLCOLOR3UIPROC glad_glColor3ui = NULL;
	PFNGLCOLOR3UIVPROC glad_glColor3uiv = NULL;
	PFNGLCOLOR3USPROC glad_glColor3us = NULL;
	PFNGLCOLOR3USVPROC glad_glColor3usv = NULL;
	PFNGLCOLOR4BPROC glad_glColor4b = NULL;
	PFNGLCOLOR4BVPROC glad_glColor4bv = NULL;
	PFNGLCOLOR4DPROC glad_glColor4d = NULL;
	PFNGLCOLOR4DVPROC glad_glColor4dv = NULL;
	PFNGLCOLOR4FPROC glad_glColor4f = NULL;
	PFNGLCOLOR4FVPROC glad_glColor4fv = NULL;
	PFNGLCOLOR4IPROC glad_glColor4i = NULL;
	PFNGLCOLOR4IVPROC glad_glColor4iv = NULL;
	PFNGLCOLOR4SPROC glad_glColor4s = NULL;
	PFNGLCOLOR4SVPROC glad_glColor4sv = NULL;
	PFNGLCOLOR4UBPROC glad_glColor4ub = NULL;
	PFNGLCOLOR4UBVPROC glad_glColor4ubv = NULL;
	PFNGLCOLOR4UIPROC glad_glColor4ui = NULL;
	PFNGLCOLOR4UIVPROC glad_glColor4uiv = NULL;
	PFNGLCOLOR4USPROC glad_glColor4us = NULL;
	PFNGLCOLOR4USVPROC glad_glColor4usv = NULL;
	PFNGLCOLORMASKPROC glad_glColorMask = NULL;
	PFNGLCOLORMASKIPROC glad_glColorMaski = NULL;
	PFNGLCOLORMATERIALPROC glad_glColorMaterial = NULL;
	PFNGLCOLORP3UIPROC glad_glColorP3ui = NULL;
	PFNGLCOLORP3UIVPROC glad_glColorP3uiv = NULL;
	PFNGLCOLORP4UIPROC glad_glColorP4ui = NULL;
	PFNGLCOLORP4UIVPROC glad_glColorP4uiv = NULL;
	PFNGLCOLORPOINTERPROC glad_glColorPointer = NULL;
	PFNGLCOMPILESHADERPROC glad_glCompileShader = NULL;
	PFNGLCOMPRESSEDTEXIMAGE1DPROC glad_glCompressedTexImage1D = NULL;
	PFNGLCOMPRESSEDTEXIMAGE2DPROC glad_glCompressedTexImage2D = NULL;
	PFNGLCOMPRESSEDTEXIMAGE3DPROC glad_glCompressedTexImage3D = NULL;
	PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC glad_glCompressedTexSubImage1D = NULL;
	PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC glad_glCompressedTexSubImage2D = NULL;
	PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC glad_glCompressedTexSubImage3D = NULL;
	PFNGLCOPYBUFFERSUBDATAPROC glad_glCopyBufferSubData = NULL;
	PFNGLCOPYPIXELSPROC glad_glCopyPixels = NULL;
	PFNGLCOPYTEXIMAGE1DPROC glad_glCopyTexImage1D = NULL;
	PFNGLCOPYTEXIMAGE2DPROC glad_glCopyTexImage2D = NULL;
	PFNGLCOPYTEXSUBIMAGE1DPROC glad_glCopyTexSubImage1D = NULL;
	PFNGLCOPYTEXSUBIMAGE2DPROC glad_glCopyTexSubImage2D = NULL;
	PFNGLCOPYTEXSUBIMAGE3DPROC glad_glCopyTexSubImage3D = NULL;
	PFNGLCREATEPROGRAMPROC glad_glCreateProgram = NULL;
	PFNGLCREATESHADERPROC glad_glCreateShader = NULL;
	PFNGLCULLFACEPROC glad_glCullFace = NULL;
	PFNGLDELETEBUFFERSPROC glad_glDeleteBuffers = NULL;
	PFNGLDELETEFRAMEBUFFERSPROC glad_glDeleteFramebuffers = NULL;
	PFNGLDELETELISTSPROC glad_glDeleteLists = NULL;
	PFNGLDELETEPROGRAMPROC glad_glDeleteProgram = NULL;
	PFNGLDELETEQUERIESPROC glad_glDeleteQueries = NULL;
	PFNGLDELETERENDERBUFFERSPROC glad_glDeleteRenderbuffers = NULL;
	PFNGLDELETESAMPLERSPROC glad_glDeleteSamplers = NULL;
	PFNGLDELETESHADERPROC glad_glDeleteShader = NULL;
	PFNGLDELETESYNCPROC glad_glDeleteSync = NULL;
	PFNGLDELETETEXTURESPROC glad_glDeleteTextures = NULL;
	PFNGLDELETEVERTEXARRAYSPROC glad_glDeleteVertexArrays = NULL;
	PFNGLDEPTHFUNCPROC glad_glDepthFunc = NULL;
	PFNGLDEPTHMASKPROC glad_glDepthMask = NULL;
	PFNGLDEPTHRANGEPROC glad_glDepthRange = NULL;
	PFNGLDETACHSHADERPROC glad_glDetachShader = NULL;
	PFNGLDISABLEPROC glad_glDisable = NULL;
	PFNGLDISABLECLIENTSTATEPROC glad_glDisableClientState = NULL;
	PFNGLDISABLEVERTEXATTRIBARRAYPROC glad_glDisableVertexAttribArray = NULL;
	PFNGLDISABLEIPROC glad_glDisablei = NULL;
	PFNGLDRAWARRAYSPROC glad_glDrawArrays = NULL;
	PFNGLDRAWARRAYSINSTANCEDPROC glad_glDrawArraysInstanced = NULL;
	PFNGLDRAWBUFFERPROC glad_glDrawBuffer = NULL;
	PFNGLDRAWBUFFERSPROC glad_glDrawBuffers = NULL;
	PFNGLDRAWELEMENTSPROC glad_glDrawElements = NULL;
	PFNGLDRAWELEMENTSBASEVERTEXPROC glad_glDrawElementsBaseVertex = NULL;
	PFNGLDRAWELEMENTSINSTANCEDPROC glad_glDrawElementsInstanced = NULL;
	PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXPROC glad_glDrawElementsInstancedBaseVertex = NULL;
	PFNGLDRAWPIXELSPROC glad_glDrawPixels = NULL;
	PFNGLDRAWRANGEELEMENTSPROC glad_glDrawRangeElements = NULL;
	PFNGLDRAWRANGEELEMENTSBASEVERTEXPROC glad_glDrawRangeElementsBaseVertex = NULL;
	PFNGLEDGEFLAGPROC glad_glEdgeFlag = NULL;
	PFNGLEDGEFLAGPOINTERPROC glad_glEdgeFlagPointer = NULL;
	PFNGLEDGEFLAGVPROC glad_glEdgeFlagv = NULL;
	PFNGLENABLEPROC glad_glEnable = NULL;
	PFNGLENABLECLIENTSTATEPROC glad_glEnableClientState = NULL;
	PFNGLENABLEVERTEXATTRIBARRAYPROC glad_glEnableVertexAttribArray = NULL;
	PFNGLENABLEIPROC glad_glEnablei = NULL;
	PFNGLENDPROC glad_glEnd = NULL;
	PFNGLENDCONDITIONALRENDERPROC glad_glEndConditionalRender = NULL;
	PFNGLENDLISTPROC glad_glEndList = NULL;
	PFNGLENDQUERYPROC glad_glEndQuery = NULL;
	PFNGLENDTRANSFORMFEEDBACKPROC glad_glEndTransformFeedback = NULL;
	PFNGLEVALCOORD1DPROC glad_glEvalCoord1d = NULL;
	PFNGLEVALCOORD1DVPROC glad_glEvalCoord1dv = NULL;
	PFNGLEVALCOORD1FPROC glad_glEvalCoord1f = NULL;
	PFNGLEVALCOORD1FVPROC glad_glEvalCoord1fv = NULL;
	PFNGLEVALCOORD2DPROC glad_glEvalCoord2d = NULL;
	PFNGLEVALCOORD2DVPROC glad_glEvalCoord2dv = NULL;
	PFNGLEVALCOORD2FPROC glad_glEvalCoord2f = NULL;
	PFNGLEVALCOORD2FVPROC glad_glEvalCoord2fv = NULL;
	PFNGLEVALMESH1PROC glad_glEvalMesh1 = NULL;
	PFNGLEVALMESH2PROC glad_glEvalMesh2 = NULL;
	PFNGLEVALPOINT1PROC glad_glEvalPoint1 = NULL;
	PFNGLEVALPOINT2PROC glad_glEvalPoint2 = NULL;
	PFNGLFEEDBACKBUFFERPROC glad_glFeedbackBuffer = NULL;
	PFNGLFENCESYNCPROC glad_glFenceSync = NULL;
	PFNGLFINISHPROC glad_glFinish = NULL;
	PFNGLFLUSHPROC glad_glFlush = NULL;
	PFNGLFLUSHMAPPEDBUFFERRANGEPROC glad_glFlushMappedBufferRange = NULL;
	PFNGLFOGCOORDPOINTERPROC glad_glFogCoordPointer = NULL;
	PFNGLFOGCOORDDPROC glad_glFogCoordd = NULL;
	PFNGLFOGCOORDDVPROC glad_glFogCoorddv = NULL;
	PFNGLFOGCOORDFPROC glad_glFogCoordf = NULL;
	PFNGLFOGCOORDFVPROC glad_glFogCoordfv = NULL;
	PFNGLFOGFPROC glad_glFogf = NULL;
	PFNGLFOGFVPROC glad_glFogfv = NULL;
	PFNGLFOGIPROC glad_glFogi = NULL;
	PFNGLFOGIVPROC glad_glFogiv = NULL;
	PFNGLFRAMEBUFFERRENDERBUFFERPROC glad_glFramebufferRenderbuffer = NULL;
	PFNGLFRAMEBUFFERTEXTUREPROC glad_glFramebufferTexture = NULL;
	PFNGLFRAMEBUFFERTEXTURE1DPROC glad_glFramebufferTexture1D = NULL;
	PFNGLFRAMEBUFFERTEXTURE2DPROC glad_glFramebufferTexture2D = NULL;
	PFNGLFRAMEBUFFERTEXTURE3DPROC glad_glFramebufferTexture3D = NULL;
	PFNGLFRAMEBUFFERTEXTURELAYERPROC glad_glFramebufferTextureLayer = NULL;
	PFNGLFRONTFACEPROC glad_glFrontFace = NULL;
	PFNGLFRUSTUMPROC glad_glFrustum = NULL;
	PFNGLGENBUFFERSPROC glad_glGenBuffers = NULL;
	PFNGLGENFRAMEBUFFERSPROC glad_glGenFramebuffers = NULL;
	PFNGLGENLISTSPROC glad_glGenLists = NULL;
	PFNGLGENQUERIESPROC glad_glGenQueries = NULL;
	PFNGLGENRENDERBUFFERSPROC glad_glGenRenderbuffers = NULL;
	PFNGLGENSAMPLERSPROC glad_glGenSamplers = NULL;
	PFNGLGENTEXTURESPROC glad_glGenTextures = NULL;
	PFNGLGENVERTEXARRAYSPROC glad_glGenVertexArrays = NULL;
	PFNGLGENERATEMIPMAPPROC glad_glGenerateMipmap = NULL;
	PFNGLGETACTIVEATTRIBPROC glad_glGetActiveAttrib = NULL;
	PFNGLGETACTIVEUNIFORMPROC glad_glGetActiveUniform = NULL;
	PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC glad_glGetActiveUniformBlockName = NULL;
	PFNGLGETACTIVEUNIFORMBLOCKIVPROC glad_glGetActiveUniformBlockiv = NULL;
	PFNGLGETACTIVEUNIFORMNAMEPROC glad_glGetActiveUniformName = NULL;
	PFNGLGETACTIVEUNIFORMSIVPROC glad_glGetActiveUniformsiv = NULL;
	PFNGLGETATTACHEDSHADERSPROC glad_glGetAttachedShaders = NULL;
	PFNGLGETATTRIBLOCATIONPROC glad_glGetAttribLocation = NULL;
	PFNGLGETBOOLEANI_VPROC glad_glGetBooleani_v = NULL;
	PFNGLGETBOOLEANVPROC glad_glGetBooleanv = NULL;
	PFNGLGETBUFFERPARAMETERI64VPROC glad_glGetBufferParameteri64v = NULL;
	PFNGLGETBUFFERPARAMETERIVPROC glad_glGetBufferParameteriv = NULL;
	PFNGLGETBUFFERPOINTERVPROC glad_glGetBufferPointerv = NULL;
	PFNGLGETBUFFERSUBDATAPROC glad_glGetBufferSubData = NULL;
	PFNGLGETCLIPPLANEPROC glad_glGetClipPlane = NULL;
	PFNGLGETCOMPRESSEDTEXIMAGEPROC glad_glGetCompressedTexImage = NULL;
	PFNGLGETDOUBLEVPROC glad_glGetDoublev = NULL;
	PFNGLGETERRORPROC glad_glGetError = NULL;
	PFNGLGETFLOATVPROC glad_glGetFloatv = NULL;
	PFNGLGETFRAGDATAINDEXPROC glad_glGetFragDataIndex = NULL;
	PFNGLGETFRAGDATALOCATIONPROC glad_glGetFragDataLocation = NULL;
	PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC glad_glGetFramebufferAttachmentParameteriv = NULL;
	PFNGLGETINTEGER64I_VPROC glad_glGetInteger64i_v = NULL;
	PFNGLGETINTEGER64VPROC glad_glGetInteger64v = NULL;
	PFNGLGETINTEGERI_VPROC glad_glGetIntegeri_v = NULL;
	PFNGLGETINTEGERVPROC glad_glGetIntegerv = NULL;
	PFNGLGETLIGHTFVPROC glad_glGetLightfv = NULL;
	PFNGLGETLIGHTIVPROC glad_glGetLightiv = NULL;
	PFNGLGETMAPDVPROC glad_glGetMapdv = NULL;
	PFNGLGETMAPFVPROC glad_glGetMapfv = NULL;
	PFNGLGETMAPIVPROC glad_glGetMapiv = NULL;
	PFNGLGETMATERIALFVPROC glad_glGetMaterialfv = NULL;
	PFNGLGETMATERIALIVPROC glad_glGetMaterialiv = NULL;
	PFNGLGETMULTISAMPLEFVPROC glad_glGetMultisamplefv = NULL;
	PFNGLGETPIXELMAPFVPROC glad_glGetPixelMapfv = NULL;
	PFNGLGETPIXELMAPUIVPROC glad_glGetPixelMapuiv = NULL;
	PFNGLGETPIXELMAPUSVPROC glad_glGetPixelMapusv = NULL;
	PFNGLGETPOINTERVPROC glad_glGetPointerv = NULL;
	PFNGLGETPOLYGONSTIPPLEPROC glad_glGetPolygonStipple = NULL;
	PFNGLGETPROGRAMINFOLOGPROC glad_glGetProgramInfoLog = NULL;
	PFNGLGETPROGRAMIVPROC glad_glGetProgramiv = NULL;
	PFNGLGETQUERYOBJECTI64VPROC glad_glGetQueryObjecti64v = NULL;
	PFNGLGETQUERYOBJECTIVPROC glad_glGetQueryObjectiv = NULL;
	PFNGLGETQUERYOBJECTUI64VPROC glad_glGetQueryObjectui64v = NULL;
	PFNGLGETQUERYOBJECTUIVPROC glad_glGetQueryObjectuiv = NULL;
	PFNGLGETQUERYIVPROC glad_glGetQueryiv = NULL;
	PFNGLGETRENDERBUFFERPARAMETERIVPROC glad_glGetRenderbufferParameteriv = NULL;
	PFNGLGETSAMPLERPARAMETERIIVPROC glad_glGetSamplerParameterIiv = NULL;
	PFNGLGETSAMPLERPARAMETERIUIVPROC glad_glGetSamplerParameterIuiv = NULL;
	PFNGLGETSAMPLERPARAMETERFVPROC glad_glGetSamplerParameterfv = NULL;
	PFNGLGETSAMPLERPARAMETERIVPROC glad_glGetSamplerParameteriv = NULL;
	PFNGLGETSHADERINFOLOGPROC glad_glGetShaderInfoLog = NULL;
	PFNGLGETSHADERSOURCEPROC glad_glGetShaderSource = NULL;
	PFNGLGETSHADERIVPROC glad_glGetShaderiv = NULL;
	PFNGLGETSTRINGPROC glad_glGetString = NULL;
	PFNGLGETSTRINGIPROC glad_glGetStringi = NULL;
	PFNGLGETSYNCIVPROC glad_glGetSynciv = NULL;
	PFNGLGETTEXENVFVPROC glad_glGetTexEnvfv = NULL;
	PFNGLGETTEXENVIVPROC glad_glGetTexEnviv = NULL;
	PFNGLGETTEXGENDVPROC glad_glGetTexGendv = NULL;
	PFNGLGETTEXGENFVPROC glad_glGetTexGenfv = NULL;
	PFNGLGETTEXGENIVPROC glad_glGetTexGeniv = NULL;
	PFNGLGETTEXIMAGEPROC glad_glGetTexImage = NULL;
	PFNGLGETTEXLEVELPARAMETERFVPROC glad_glGetTexLevelParameterfv = NULL;
	PFNGLGETTEXLEVELPARAMETERIVPROC glad_glGetTexLevelParameteriv = NULL;
	PFNGLGETTEXPARAMETERIIVPROC glad_glGetTexParameterIiv = NULL;
	PFNGLGETTEXPARAMETERIUIVPROC glad_glGetTexParameterIuiv = NULL;
	PFNGLGETTEXPARAMETERFVPROC glad_glGetTexParameterfv = NULL;
	PFNGLGETTEXPARAMETERIVPROC glad_glGetTexParameteriv = NULL;
	PFNGLGETTRANSFORMFEEDBACKVARYINGPROC glad_glGetTransformFeedbackVarying = NULL;
	PFNGLGETUNIFORMBLOCKINDEXPROC glad_glGetUniformBlockIndex = NULL;
	PFNGLGETUNIFORMINDICESPROC glad_glGetUniformIndices = NULL;
	PFNGLGETUNIFORMLOCATIONPROC glad_glGetUniformLocation = NULL;
	PFNGLGETUNIFORMFVPROC glad_glGetUniformfv = NULL;
	PFNGLGETUNIFORMIVPROC glad_glGetUniformiv = NULL;
	PFNGLGETUNIFORMUIVPROC glad_glGetUniformuiv = NULL;
	PFNGLGETVERTEXATTRIBIIVPROC glad_glGetVertexAttribIiv = NULL;
	PFNGLGETVERTEXATTRIBIUIVPROC glad_glGetVertexAttribIuiv = NULL;
	PFNGLGETVERTEXATTRIBPOINTERVPROC glad_glGetVertexAttribPointerv = NULL;
	PFNGLGETVERTEXATTRIBDVPROC glad_glGetVertexAttribdv = NULL;
	PFNGLGETVERTEXATTRIBFVPROC glad_glGetVertexAttribfv = NULL;
	PFNGLGETVERTEXATTRIBIVPROC glad_glGetVertexAttribiv = NULL;
	PFNGLHINTPROC glad_glHint = NULL;
	PFNGLINDEXMASKPROC glad_glIndexMask = NULL;
	PFNGLINDEXPOINTERPROC glad_glIndexPointer = NULL;
	PFNGLINDEXDPROC glad_glIndexd = NULL;
	PFNGLINDEXDVPROC glad_glIndexdv = NULL;
	PFNGLINDEXFPROC glad_glIndexf = NULL;
	PFNGLINDEXFVPROC glad_glIndexfv = NULL;
	PFNGLINDEXIPROC glad_glIndexi = NULL;
	PFNGLINDEXIVPROC glad_glIndexiv = NULL;
	PFNGLINDEXSPROC glad_glIndexs = NULL;
	PFNGLINDEXSVPROC glad_glIndexsv = NULL;
	PFNGLINDEXUBPROC glad_glIndexub = NULL;
	PFNGLINDEXUBVPROC glad_glIndexubv = NULL;
	PFNGLINITNAMESPROC glad_glInitNames = NULL;
	PFNGLINTERLEAVEDARRAYSPROC glad_glInterleavedArrays = NULL;
	PFNGLISBUFFERPROC glad_glIsBuffer = NULL;
	PFNGLISENABLEDPROC glad_glIsEnabled = NULL;
	PFNGLISENABLEDIPROC glad_glIsEnabledi = NULL;
	PFNGLISFRAMEBUFFERPROC glad_glIsFramebuffer = NULL;
	PFNGLISLISTPROC glad_glIsList = NULL;
	PFNGLISPROGRAMPROC glad_glIsProgram = NULL;
	PFNGLISQUERYPROC glad_glIsQuery = NULL;
	PFNGLISRENDERBUFFERPROC glad_glIsRenderbuffer = NULL;
	PFNGLISSAMPLERPROC glad_glIsSampler = NULL;
	PFNGLISSHADERPROC glad_glIsShader = NULL;
	PFNGLISSYNCPROC glad_glIsSync = NULL;
	PFNGLISTEXTUREPROC glad_glIsTexture = NULL;
	PFNGLISVERTEXARRAYPROC glad_glIsVertexArray = NULL;
	PFNGLLIGHTMODELFPROC glad_glLightModelf = NULL;
	PFNGLLIGHTMODELFVPROC glad_glLightModelfv = NULL;
	PFNGLLIGHTMODELIPROC glad_glLightModeli = NULL;
	PFNGLLIGHTMODELIVPROC glad_glLightModeliv = NULL;
	PFNGLLIGHTFPROC glad_glLightf = NULL;
	PFNGLLIGHTFVPROC glad_glLightfv = NULL;
	PFNGLLIGHTIPROC glad_glLighti = NULL;
	PFNGLLIGHTIVPROC glad_glLightiv = NULL;
	PFNGLLINESTIPPLEPROC glad_glLineStipple = NULL;
	PFNGLLINEWIDTHPROC glad_glLineWidth = NULL;
	PFNGLLINKPROGRAMPROC glad_glLinkProgram = NULL;
	PFNGLLISTBASEPROC glad_glListBase = NULL;
	PFNGLLOADIDENTITYPROC glad_glLoadIdentity = NULL;
	PFNGLLOADMATRIXDPROC glad_glLoadMatrixd = NULL;
	PFNGLLOADMATRIXFPROC glad_glLoadMatrixf = NULL;
	PFNGLLOADNAMEPROC glad_glLoadName = NULL;
	PFNGLLOADTRANSPOSEMATRIXDPROC glad_glLoadTransposeMatrixd = NULL;
	PFNGLLOADTRANSPOSEMATRIXFPROC glad_glLoadTransposeMatrixf = NULL;
	PFNGLLOGICOPPROC glad_glLogicOp = NULL;
	PFNGLMAP1DPROC glad_glMap1d = NULL;
	PFNGLMAP1FPROC glad_glMap1f = NULL;
	PFNGLMAP2DPROC glad_glMap2d = NULL;
	PFNGLMAP2FPROC glad_glMap2f = NULL;
	PFNGLMAPBUFFERPROC glad_glMapBuffer = NULL;
	PFNGLMAPBUFFERRANGEPROC glad_glMapBufferRange = NULL;
	PFNGLMAPGRID1DPROC glad_glMapGrid1d = NULL;
	PFNGLMAPGRID1FPROC glad_glMapGrid1f = NULL;
	PFNGLMAPGRID2DPROC glad_glMapGrid2d = NULL;
	PFNGLMAPGRID2FPROC glad_glMapGrid2f = NULL;
	PFNGLMATERIALFPROC glad_glMaterialf = NULL;
	PFNGLMATERIALFVPROC glad_glMaterialfv = NULL;
	PFNGLMATERIALIPROC glad_glMateriali = NULL;
	PFNGLMATERIALIVPROC glad_glMaterialiv = NULL;
	PFNGLMATRIXMODEPROC glad_glMatrixMode = NULL;
	PFNGLMULTMATRIXDPROC glad_glMultMatrixd = NULL;
	PFNGLMULTMATRIXFPROC glad_glMultMatrixf = NULL;
	PFNGLMULTTRANSPOSEMATRIXDPROC glad_glMultTransposeMatrixd = NULL;
	PFNGLMULTTRANSPOSEMATRIXFPROC glad_glMultTransposeMatrixf = NULL;
	PFNGLMULTIDRAWARRAYSPROC glad_glMultiDrawArrays = NULL;
	PFNGLMULTIDRAWELEMENTSPROC glad_glMultiDrawElements = NULL;
	PFNGLMULTIDRAWELEMENTSBASEVERTEXPROC glad_glMultiDrawElementsBaseVertex = NULL;
	PFNGLMULTITEXCOORD1DPROC glad_glMultiTexCoord1d = NULL;
	PFNGLMULTITEXCOORD1DVPROC glad_glMultiTexCoord1dv = NULL;
	PFNGLMULTITEXCOORD1FPROC glad_glMultiTexCoord1f = NULL;
	PFNGLMULTITEXCOORD1FVPROC glad_glMultiTexCoord1fv = NULL;
	PFNGLMULTITEXCOORD1IPROC glad_glMultiTexCoord1i = NULL;
	PFNGLMULTITEXCOORD1IVPROC glad_glMultiTexCoord1iv = NULL;
	PFNGLMULTITEXCOORD1SPROC glad_glMultiTexCoord1s = NULL;
	PFNGLMULTITEXCOORD1SVPROC glad_glMultiTexCoord1sv = NULL;
	PFNGLMULTITEXCOORD2DPROC glad_glMultiTexCoord2d = NULL;
	PFNGLMULTITEXCOORD2DVPROC glad_glMultiTexCoord2dv = NULL;
	PFNGLMULTITEXCOORD2FPROC glad_glMultiTexCoord2f = NULL;
	PFNGLMULTITEXCOORD2FVPROC glad_glMultiTexCoord2fv = NULL;
	PFNGLMULTITEXCOORD2IPROC glad_glMultiTexCoord2i = NULL;
	PFNGLMULTITEXCOORD2IVPROC glad_glMultiTexCoord2iv = NULL;
	PFNGLMULTITEXCOORD2SPROC glad_glMultiTexCoord2s = NULL;
	PFNGLMULTITEXCOORD2SVPROC glad_glMultiTexCoord2sv = NULL;
	PFNGLMULTITEXCOORD3DPROC glad_glMultiTexCoord3d = NULL;
	PFNGLMULTITEXCOORD3DVPROC glad_glMultiTexCoord3dv = NULL;
	PFNGLMULTITEXCOORD3FPROC glad_glMultiTexCoord3f = NULL;
	PFNGLMULTITEXCOORD3FVPROC glad_glMultiTexCoord3fv = NULL;
	PFNGLMULTITEXCOORD3IPROC glad_glMultiTexCoord3i = NULL;
	PFNGLMULTITEXCOORD3IVPROC glad_glMultiTexCoord3iv = NULL;
	PFNGLMULTITEXCOORD3SPROC glad_glMultiTexCoord3s = NULL;
	PFNGLMULTITEXCOORD3SVPROC glad_glMultiTexCoord3sv = NULL;
	PFNGLMULTITEXCOORD4DPROC glad_glMultiTexCoord4d = NULL;
	PFNGLMULTITEXCOORD4DVPROC glad_glMultiTexCoord4dv = NULL;
	PFNGLMULTITEXCOORD4FPROC glad_glMultiTexCoord4f = NULL;
	PFNGLMULTITEXCOORD4FVPROC glad_glMultiTexCoord4fv = NULL;
	PFNGLMULTITEXCOORD4IPROC glad_glMultiTexCoord4i = NULL;
	PFNGLMULTITEXCOORD4IVPROC glad_glMultiTexCoord4iv = NULL;
	PFNGLMULTITEXCOORD4SPROC glad_glMultiTexCoord4s = NULL;
	PFNGLMULTITEXCOORD4SVPROC glad_glMultiTexCoord4sv = NULL;
	PFNGLMULTITEXCOORDP1UIPROC glad_glMultiTexCoordP1ui = NULL;
	PFNGLMULTITEXCOORDP1UIVPROC glad_glMultiTexCoordP1uiv = NULL;
	PFNGLMULTITEXCOORDP2UIPROC glad_glMultiTexCoordP2ui = NULL;
	PFNGLMULTITEXCOORDP2UIVPROC glad_glMultiTexCoordP2uiv = NULL;
	PFNGLMULTITEXCOORDP3UIPROC glad_glMultiTexCoordP3ui = NULL;
	PFNGLMULTITEXCOORDP3UIVPROC glad_glMultiTexCoordP3uiv = NULL;
	PFNGLMULTITEXCOORDP4UIPROC glad_glMultiTexCoordP4ui = NULL;
	PFNGLMULTITEXCOORDP4UIVPROC glad_glMultiTexCoordP4uiv = NULL;
	PFNGLNEWLISTPROC glad_glNewList = NULL;
	PFNGLNORMAL3BPROC glad_glNormal3b = NULL;
	PFNGLNORMAL3BVPROC glad_glNormal3bv = NULL;
	PFNGLNORMAL3DPROC glad_glNormal3d = NULL;
	PFNGLNORMAL3DVPROC glad_glNormal3dv = NULL;
	PFNGLNORMAL3FPROC glad_glNormal3f = NULL;
	PFNGLNORMAL3FVPROC glad_glNormal3fv = NULL;
	PFNGLNORMAL3IPROC glad_glNormal3i = NULL;
	PFNGLNORMAL3IVPROC glad_glNormal3iv = NULL;
	PFNGLNORMAL3SPROC glad_glNormal3s = NULL;
	PFNGLNORMAL3SVPROC glad_glNormal3sv = NULL;
	PFNGLNORMALP3UIPROC glad_glNormalP3ui = NULL;
	PFNGLNORMALP3UIVPROC glad_glNormalP3uiv = NULL;
	PFNGLNORMALPOINTERPROC glad_glNormalPointer = NULL;
	PFNGLORTHOPROC glad_glOrtho = NULL;
	PFNGLPASSTHROUGHPROC glad_glPassThrough = NULL;
	PFNGLPIXELMAPFVPROC glad_glPixelMapfv = NULL;
	PFNGLPIXELMAPUIVPROC glad_glPixelMapuiv = NULL;
	PFNGLPIXELMAPUSVPROC glad_glPixelMapusv = NULL;
	PFNGLPIXELSTOREFPROC glad_glPixelStoref = NULL;
	PFNGLPIXELSTOREIPROC glad_glPixelStorei = NULL;
	PFNGLPIXELTRANSFERFPROC glad_glPixelTransferf = NULL;
	PFNGLPIXELTRANSFERIPROC glad_glPixelTransferi = NULL;
	PFNGLPIXELZOOMPROC glad_glPixelZoom = NULL;
	PFNGLPOINTPARAMETERFPROC glad_glPointParameterf = NULL;
	PFNGLPOINTPARAMETERFVPROC glad_glPointParameterfv = NULL;
	PFNGLPOINTPARAMETERIPROC glad_glPointParameteri = NULL;
	PFNGLPOINTPARAMETERIVPROC glad_glPointParameteriv = NULL;
	PFNGLPOINTSIZEPROC glad_glPointSize = NULL;
	PFNGLPOLYGONMODEPROC glad_glPolygonMode = NULL;
	PFNGLPOLYGONOFFSETPROC glad_glPolygonOffset = NULL;
	PFNGLPOLYGONSTIPPLEPROC glad_glPolygonStipple = NULL;
	PFNGLPOPATTRIBPROC glad_glPopAttrib = NULL;
	PFNGLPOPCLIENTATTRIBPROC glad_glPopClientAttrib = NULL;
	PFNGLPOPMATRIXPROC glad_glPopMatrix = NULL;
	PFNGLPOPNAMEPROC glad_glPopName = NULL;
	PFNGLPRIMITIVERESTARTINDEXPROC glad_glPrimitiveRestartIndex = NULL;
	PFNGLPRIORITIZETEXTURESPROC glad_glPrioritizeTextures = NULL;
	PFNGLPROVOKINGVERTEXPROC glad_glProvokingVertex = NULL;
	PFNGLPUSHATTRIBPROC glad_glPushAttrib = NULL;
	PFNGLPUSHCLIENTATTRIBPROC glad_glPushClientAttrib = NULL;
	PFNGLPUSHMATRIXPROC glad_glPushMatrix = NULL;
	PFNGLPUSHNAMEPROC glad_glPushName = NULL;
	PFNGLQUERYCOUNTERPROC glad_glQueryCounter = NULL;
	PFNGLRASTERPOS2DPROC glad_glRasterPos2d = NULL;
	PFNGLRASTERPOS2DVPROC glad_glRasterPos2dv = NULL;
	PFNGLRASTERPOS2FPROC glad_glRasterPos2f = NULL;
	PFNGLRASTERPOS2FVPROC glad_glRasterPos2fv = NULL;
	PFNGLRASTERPOS2IPROC glad_glRasterPos2i = NULL;
	PFNGLRASTERPOS2IVPROC glad_glRasterPos2iv = NULL;
	PFNGLRASTERPOS2SPROC glad_glRasterPos2s = NULL;
	PFNGLRASTERPOS2SVPROC glad_glRasterPos2sv = NULL;
	PFNGLRASTERPOS3DPROC glad_glRasterPos3d = NULL;
	PFNGLRASTERPOS3DVPROC glad_glRasterPos3dv = NULL;
	PFNGLRASTERPOS3FPROC glad_glRasterPos3f = NULL;
	PFNGLRASTERPOS3FVPROC glad_glRasterPos3fv = NULL;
	PFNGLRASTERPOS3IPROC glad_glRasterPos3i = NULL;
	PFNGLRASTERPOS3IVPROC glad_glRasterPos3iv = NULL;
	PFNGLRASTERPOS3SPROC glad_glRasterPos3s = NULL;
	PFNGLRASTERPOS3SVPROC glad_glRasterPos3sv = NULL;
	PFNGLRASTERPOS4DPROC glad_glRasterPos4d = NULL;
	PFNGLRASTERPOS4DVPROC glad_glRasterPos4dv = NULL;
	PFNGLRASTERPOS4FPROC glad_glRasterPos4f = NULL;
	PFNGLRASTERPOS4FVPROC glad_glRasterPos4fv = NULL;
	PFNGLRASTERPOS4IPROC glad_glRasterPos4i = NULL;
	PFNGLRASTERPOS4IVPROC glad_glRasterPos4iv = NULL;
	PFNGLRASTERPOS4SPROC glad_glRasterPos4s = NULL;
	PFNGLRASTERPOS4SVPROC glad_glRasterPos4sv = NULL;
	PFNGLREADBUFFERPROC glad_glReadBuffer = NULL;
	PFNGLREADPIXELSPROC glad_glReadPixels = NULL;
	PFNGLRECTDPROC glad_glRectd = NULL;
	PFNGLRECTDVPROC glad_glRectdv = NULL;
	PFNGLRECTFPROC glad_glRectf = NULL;
	PFNGLRECTFVPROC glad_glRectfv = NULL;
	PFNGLRECTIPROC glad_glRecti = NULL;
	PFNGLRECTIVPROC glad_glRectiv = NULL;
	PFNGLRECTSPROC glad_glRects = NULL;
	PFNGLRECTSVPROC glad_glRectsv = NULL;
	PFNGLRENDERMODEPROC glad_glRenderMode = NULL;
	PFNGLRENDERBUFFERSTORAGEPROC glad_glRenderbufferStorage = NULL;
	PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC glad_glRenderbufferStorageMultisample = NULL;
	PFNGLROTATEDPROC glad_glRotated = NULL;
	PFNGLROTATEFPROC glad_glRotatef = NULL;
	PFNGLSAMPLECOVERAGEPROC glad_glSampleCoverage = NULL;
	PFNGLSAMPLEMASKIPROC glad_glSampleMaski = NULL;
	PFNGLSAMPLERPARAMETERIIVPROC glad_glSamplerParameterIiv = NULL;
	PFNGLSAMPLERPARAMETERIUIVPROC glad_glSamplerParameterIuiv = NULL;
	PFNGLSAMPLERPARAMETERFPROC glad_glSamplerParameterf = NULL;
	PFNGLSAMPLERPARAMETERFVPROC glad_glSamplerParameterfv = NULL;
	PFNGLSAMPLERPARAMETERIPROC glad_glSamplerParameteri = NULL;
	PFNGLSAMPLERPARAMETERIVPROC glad_glSamplerParameteriv = NULL;
	PFNGLSCALEDPROC glad_glScaled = NULL;
	PFNGLSCALEFPROC glad_glScalef = NULL;
	PFNGLSCISSORPROC glad_glScissor = NULL;
	PFNGLSECONDARYCOLOR3BPROC glad_glSecondaryColor3b = NULL;
	PFNGLSECONDARYCOLOR3BVPROC glad_glSecondaryColor3bv = NULL;
	PFNGLSECONDARYCOLOR3DPROC glad_glSecondaryColor3d = NULL;
	PFNGLSECONDARYCOLOR3DVPROC glad_glSecondaryColor3dv = NULL;
	PFNGLSECONDARYCOLOR3FPROC glad_glSecondaryColor3f = NULL;
	PFNGLSECONDARYCOLOR3FVPROC glad_glSecondaryColor3fv = NULL;
	PFNGLSECONDARYCOLOR3IPROC glad_glSecondaryColor3i = NULL;
	PFNGLSECONDARYCOLOR3IVPROC glad_glSecondaryColor3iv = NULL;
	PFNGLSECONDARYCOLOR3SPROC glad_glSecondaryColor3s = NULL;
	PFNGLSECONDARYCOLOR3SVPROC glad_glSecondaryColor3sv = NULL;
	PFNGLSECONDARYCOLOR3UBPROC glad_glSecondaryColor3ub = NULL;
	PFNGLSECONDARYCOLOR3UBVPROC glad_glSecondaryColor3ubv = NULL;
	PFNGLSECONDARYCOLOR3UIPROC glad_glSecondaryColor3ui = NULL;
	PFNGLSECONDARYCOLOR3UIVPROC glad_glSecondaryColor3uiv = NULL;
	PFNGLSECONDARYCOLOR3USPROC glad_glSecondaryColor3us = NULL;
	PFNGLSECONDARYCOLOR3USVPROC glad_glSecondaryColor3usv = NULL;
	PFNGLSECONDARYCOLORP3UIPROC glad_glSecondaryColorP3ui = NULL;
	PFNGLSECONDARYCOLORP3UIVPROC glad_glSecondaryColorP3uiv = NULL;
	PFNGLSECONDARYCOLORPOINTERPROC glad_glSecondaryColorPointer = NULL;
	PFNGLSELECTBUFFERPROC glad_glSelectBuffer = NULL;
	PFNGLSHADEMODELPROC glad_glShadeModel = NULL;
	PFNGLSHADERSOURCEPROC glad_glShaderSource = NULL;
	PFNGLSTENCILFUNCPROC glad_glStencilFunc = NULL;
	PFNGLSTENCILFUNCSEPARATEPROC glad_glStencilFuncSeparate = NULL;
	PFNGLSTENCILMASKPROC glad_glStencilMask = NULL;
	PFNGLSTENCILMASKSEPARATEPROC glad_glStencilMaskSeparate = NULL;
	PFNGLSTENCILOPPROC glad_glStencilOp = NULL;
	PFNGLSTENCILOPSEPARATEPROC glad_glStencilOpSeparate = NULL;
	PFNGLTEXBUFFERPROC glad_glTexBuffer = NULL;
	PFNGLTEXCOORD1DPROC glad_glTexCoord1d = NULL;
	PFNGLTEXCOORD1DVPROC glad_glTexCoord1dv = NULL;
	PFNGLTEXCOORD1FPROC glad_glTexCoord1f = NULL;
	PFNGLTEXCOORD1FVPROC glad_glTexCoord1fv = NULL;
	PFNGLTEXCOORD1IPROC glad_glTexCoord1i = NULL;
	PFNGLTEXCOORD1IVPROC glad_glTexCoord1iv = NULL;
	PFNGLTEXCOORD1SPROC glad_glTexCoord1s = NULL;
	PFNGLTEXCOORD1SVPROC glad_glTexCoord1sv = NULL;
	PFNGLTEXCOORD2DPROC glad_glTexCoord2d = NULL;
	PFNGLTEXCOORD2DVPROC glad_glTexCoord2dv = NULL;
	PFNGLTEXCOORD2FPROC glad_glTexCoord2f = NULL;
	PFNGLTEXCOORD2FVPROC glad_glTexCoord2fv = NULL;
	PFNGLTEXCOORD2IPROC glad_glTexCoord2i = NULL;
	PFNGLTEXCOORD2IVPROC glad_glTexCoord2iv = NULL;
	PFNGLTEXCOORD2SPROC glad_glTexCoord2s = NULL;
	PFNGLTEXCOORD2SVPROC glad_glTexCoord2sv = NULL;
	PFNGLTEXCOORD3DPROC glad_glTexCoord3d = NULL;
	PFNGLTEXCOORD3DVPROC glad_glTexCoord3dv = NULL;
	PFNGLTEXCOORD3FPROC glad_glTexCoord3f = NULL;
	PFNGLTEXCOORD3FVPROC glad_glTexCoord3fv = NULL;
	PFNGLTEXCOORD3IPROC glad_glTexCoord3i = NULL;
	PFNGLTEXCOORD3IVPROC glad_glTexCoord3iv = NULL;
	PFNGLTEXCOORD3SPROC glad_glTexCoord3s = NULL;
	PFNGLTEXCOORD3SVPROC glad_glTexCoord3sv = NULL;
	PFNGLTEXCOORD4DPROC glad_glTexCoord4d = NULL;
	PFNGLTEXCOORD4DVPROC glad_glTexCoord4dv = NULL;
	PFNGLTEXCOORD4FPROC glad_glTexCoord4f = NULL;
	PFNGLTEXCOORD4FVPROC glad_glTexCoord4fv = NULL;
	PFNGLTEXCOORD4IPROC glad_glTexCoord4i = NULL;
	PFNGLTEXCOORD4IVPROC glad_glTexCoord4iv = NULL;
	PFNGLTEXCOORD4SPROC glad_glTexCoord4s = NULL;
	PFNGLTEXCOORD4SVPROC glad_glTexCoord4sv = NULL;
	PFNGLTEXCOORDP1UIPROC glad_glTexCoordP1ui = NULL;
	PFNGLTEXCOORDP1UIVPROC glad_glTexCoordP1uiv = NULL;
	PFNGLTEXCOORDP2UIPROC glad_glTexCoordP2ui = NULL;
	PFNGLTEXCOORDP2UIVPROC glad_glTexCoordP2uiv = NULL;
	PFNGLTEXCOORDP3UIPROC glad_glTexCoordP3ui = NULL;
	PFNGLTEXCOORDP3UIVPROC glad_glTexCoordP3uiv = NULL;
	PFNGLTEXCOORDP4UIPROC glad_glTexCoordP4ui = NULL;
	PFNGLTEXCOORDP4UIVPROC glad_glTexCoordP4uiv = NULL;
	PFNGLTEXCOORDPOINTERPROC glad_glTexCoordPointer = NULL;
	PFNGLTEXENVFPROC glad_glTexEnvf = NULL;
	PFNGLTEXENVFVPROC glad_glTexEnvfv = NULL;
	PFNGLTEXENVIPROC glad_glTexEnvi = NULL;
	PFNGLTEXENVIVPROC glad_glTexEnviv = NULL;
	PFNGLTEXGENDPROC glad_glTexGend = NULL;
	PFNGLTEXGENDVPROC glad_glTexGendv = NULL;
	PFNGLTEXGENFPROC glad_glTexGenf = NULL;
	PFNGLTEXGENFVPROC glad_glTexGenfv = NULL;
	PFNGLTEXGENIPROC glad_glTexGeni = NULL;
	PFNGLTEXGENIVPROC glad_glTexGeniv = NULL;
	PFNGLTEXIMAGE1DPROC glad_glTexImage1D = NULL;
	PFNGLTEXIMAGE2DPROC glad_glTexImage2D = NULL;
	PFNGLTEXIMAGE2DMULTISAMPLEPROC glad_glTexImage2DMultisample = NULL;
	PFNGLTEXIMAGE3DPROC glad_glTexImage3D = NULL;
	PFNGLTEXIMAGE3DMULTISAMPLEPROC glad_glTexImage3DMultisample = NULL;
	PFNGLTEXPARAMETERIIVPROC glad_glTexParameterIiv = NULL;
	PFNGLTEXPARAMETERIUIVPROC glad_glTexParameterIuiv = NULL;
	PFNGLTEXPARAMETERFPROC glad_glTexParameterf = NULL;
	PFNGLTEXPARAMETERFVPROC glad_glTexParameterfv = NULL;
	PFNGLTEXPARAMETERIPROC glad_glTexParameteri = NULL;
	PFNGLTEXPARAMETERIVPROC glad_glTexParameteriv = NULL;
	PFNGLTEXSUBIMAGE1DPROC glad_glTexSubImage1D = NULL;
	PFNGLTEXSUBIMAGE2DPROC glad_glTexSubImage2D = NULL;
	PFNGLTEXSUBIMAGE3DPROC glad_glTexSubImage3D = NULL;
	PFNGLTRANSFORMFEEDBACKVARYINGSPROC glad_glTransformFeedbackVaryings = NULL;
	PFNGLTRANSLATEDPROC glad_glTranslated = NULL;
	PFNGLTRANSLATEFPROC glad_glTranslatef = NULL;
	PFNGLUNIFORM1FPROC glad_glUniform1f = NULL;
	PFNGLUNIFORM1FVPROC glad_glUniform1fv = NULL;
	PFNGLUNIFORM1IPROC glad_glUniform1i = NULL;
	PFNGLUNIFORM1IVPROC glad_glUniform1iv = NULL;
	PFNGLUNIFORM1UIPROC glad_glUniform1ui = NULL;
	PFNGLUNIFORM1UIVPROC glad_glUniform1uiv = NULL;
	PFNGLUNIFORM2FPROC glad_glUniform2f = NULL;
	PFNGLUNIFORM2FVPROC glad_glUniform2fv = NULL;
	PFNGLUNIFORM2IPROC glad_glUniform2i = NULL;
	PFNGLUNIFORM2IVPROC glad_glUniform2iv = NULL;
	PFNGLUNIFORM2UIPROC glad_glUniform2ui = NULL;
	PFNGLUNIFORM2UIVPROC glad_glUniform2uiv = NULL;
	PFNGLUNIFORM3FPROC glad_glUniform3f = NULL;
	PFNGLUNIFORM3FVPROC glad_glUniform3fv = NULL;
	PFNGLUNIFORM3IPROC glad_glUniform3i = NULL;
	PFNGLUNIFORM3IVPROC glad_glUniform3iv = NULL;
	PFNGLUNIFORM3UIPROC glad_glUniform3ui = NULL;
	PFNGLUNIFORM3UIVPROC glad_glUniform3uiv = NULL;
	PFNGLUNIFORM4FPROC glad_glUniform4f = NULL;
	PFNGLUNIFORM4FVPROC glad_glUniform4fv = NULL;
	PFNGLUNIFORM4IPROC glad_glUniform4i = NULL;
	PFNGLUNIFORM4IVPROC glad_glUniform4iv = NULL;
	PFNGLUNIFORM4UIPROC glad_glUniform4ui = NULL;
	PFNGLUNIFORM4UIVPROC glad_glUniform4uiv = NULL;
	PFNGLUNIFORMBLOCKBINDINGPROC glad_glUniformBlockBinding = NULL;
	PFNGLUNIFORMMATRIX2FVPROC glad_glUniformMatrix2fv = NULL;
	PFNGLUNIFORMMATRIX2X3FVPROC glad_glUniformMatrix2x3fv = NULL;
	PFNGLUNIFORMMATRIX2X4FVPROC glad_glUniformMatrix2x4fv = NULL;
	PFNGLUNIFORMMATRIX3FVPROC glad_glUniformMatrix3fv = NULL;
	PFNGLUNIFORMMATRIX3X2FVPROC glad_glUniformMatrix3x2fv = NULL;
	PFNGLUNIFORMMATRIX3X4FVPROC glad_glUniformMatrix3x4fv = NULL;
	PFNGLUNIFORMMATRIX4FVPROC glad_glUniformMatrix4fv = NULL;
	PFNGLUNIFORMMATRIX4X2FVPROC glad_glUniformMatrix4x2fv = NULL;
	PFNGLUNIFORMMATRIX4X3FVPROC glad_glUniformMatrix4x3fv = NULL;
	PFNGLUNMAPBUFFERPROC glad_glUnmapBuffer = NULL;
	PFNGLUSEPROGRAMPROC glad_glUseProgram = NULL;
	PFNGLVALIDATEPROGRAMPROC glad_glValidateProgram = NULL;
	PFNGLVERTEX2DPROC glad_glVertex2d = NULL;
	PFNGLVERTEX2DVPROC glad_glVertex2dv = NULL;
	PFNGLVERTEX2FPROC glad_glVertex2f = NULL;
	PFNGLVERTEX2FVPROC glad_glVertex2fv = NULL;
	PFNGLVERTEX2IPROC glad_glVertex2i = NULL;
	PFNGLVERTEX2IVPROC glad_glVertex2iv = NULL;
	PFNGLVERTEX2SPROC glad_glVertex2s = NULL;
	PFNGLVERTEX2SVPROC glad_glVertex2sv = NULL;
	PFNGLVERTEX3DPROC glad_glVertex3d = NULL;
	PFNGLVERTEX3DVPROC glad_glVertex3dv = NULL;
	PFNGLVERTEX3FPROC glad_glVertex3f = NULL;
	PFNGLVERTEX3FVPROC glad_glVertex3fv = NULL;
	PFNGLVERTEX3IPROC glad_glVertex3i = NULL;
	PFNGLVERTEX3IVPROC glad_glVertex3iv = NULL;
	PFNGLVERTEX3SPROC glad_glVertex3s = NULL;
	PFNGLVERTEX3SVPROC glad_glVertex3sv = NULL;
	PFNGLVERTEX4DPROC glad_glVertex4d = NULL;
	PFNGLVERTEX4DVPROC glad_glVertex4dv = NULL;
	PFNGLVERTEX4FPROC glad_glVertex4f = NULL;
	PFNGLVERTEX4FVPROC glad_glVertex4fv = NULL;
	PFNGLVERTEX4IPROC glad_glVertex4i = NULL;
	PFNGLVERTEX4IVPROC glad_glVertex4iv = NULL;
	PFNGLVERTEX4SPROC glad_glVertex4s = NULL;
	PFNGLVERTEX4SVPROC glad_glVertex4sv = NULL;
	PFNGLVERTEXATTRIB1DPROC glad_glVertexAttrib1d = NULL;
	PFNGLVERTEXATTRIB1DVPROC glad_glVertexAttrib1dv = NULL;
	PFNGLVERTEXATTRIB1FPROC glad_glVertexAttrib1f = NULL;
	PFNGLVERTEXATTRIB1FVPROC glad_glVertexAttrib1fv = NULL;
	PFNGLVERTEXATTRIB1SPROC glad_glVertexAttrib1s = NULL;
	PFNGLVERTEXATTRIB1SVPROC glad_glVertexAttrib1sv = NULL;
	PFNGLVERTEXATTRIB2DPROC glad_glVertexAttrib2d = NULL;
	PFNGLVERTEXATTRIB2DVPROC glad_glVertexAttrib2dv = NULL;
	PFNGLVERTEXATTRIB2FPROC glad_glVertexAttrib2f = NULL;
	PFNGLVERTEXATTRIB2FVPROC glad_glVertexAttrib2fv = NULL;
	PFNGLVERTEXATTRIB2SPROC glad_glVertexAttrib2s = NULL;
	PFNGLVERTEXATTRIB2SVPROC glad_glVertexAttrib2sv = NULL;
	PFNGLVERTEXATTRIB3DPROC glad_glVertexAttrib3d = NULL;
	PFNGLVERTEXATTRIB3DVPROC glad_glVertexAttrib3dv = NULL;
	PFNGLVERTEXATTRIB3FPROC glad_glVertexAttrib3f = NULL;
	PFNGLVERTEXATTRIB3FVPROC glad_glVertexAttrib3fv = NULL;
	PFNGLVERTEXATTRIB3SPROC glad_glVertexAttrib3s = NULL;
	PFNGLVERTEXATTRIB3SVPROC glad_glVertexAttrib3sv = NULL;
	PFNGLVERTEXATTRIB4NBVPROC glad_glVertexAttrib4Nbv = NULL;
	PFNGLVERTEXATTRIB4NIVPROC glad_glVertexAttrib4Niv = NULL;
	PFNGLVERTEXATTRIB4NSVPROC glad_glVertexAttrib4Nsv = NULL;
	PFNGLVERTEXATTRIB4NUBPROC glad_glVertexAttrib4Nub = NULL;
	PFNGLVERTEXATTRIB4NUBVPROC glad_glVertexAttrib4Nubv = NULL;
	PFNGLVERTEXATTRIB4NUIVPROC glad_glVertexAttrib4Nuiv = NULL;
	PFNGLVERTEXATTRIB4NUSVPROC glad_glVertexAttrib4Nusv = NULL;
	PFNGLVERTEXATTRIB4BVPROC glad_glVertexAttrib4bv = NULL;
	PFNGLVERTEXATTRIB4DPROC glad_glVertexAttrib4d = NULL;
	PFNGLVERTEXATTRIB4DVPROC glad_glVertexAttrib4dv = NULL;
	PFNGLVERTEXATTRIB4FPROC glad_glVertexAttrib4f = NULL;
	PFNGLVERTEXATTRIB4FVPROC glad_glVertexAttrib4fv = NULL;
	PFNGLVERTEXATTRIB4IVPROC glad_glVertexAttrib4iv = NULL;
	PFNGLVERTEXATTRIB4SPROC glad_glVertexAttrib4s = NULL;
	PFNGLVERTEXATTRIB4SVPROC glad_glVertexAttrib4sv = NULL;
	PFNGLVERTEXATTRIB4UBVPROC glad_glVertexAttrib4ubv = NULL;
	PFNGLVERTEXATTRIB4UIVPROC glad_glVertexAttrib4uiv = NULL;
	PFNGLVERTEXATTRIB4USVPROC glad_glVertexAttrib4usv = NULL;
	PFNGLVERTEXATTRIBDIVISORPROC glad_glVertexAttribDivisor = NULL;
	PFNGLVERTEXATTRIBI1IPROC glad_glVertexAttribI1i = NULL;
	PFNGLVERTEXATTRIBI1IVPROC glad_glVertexAttribI1iv = NULL;
	PFNGLVERTEXATTRIBI1UIPROC glad_glVertexAttribI1ui = NULL;
	PFNGLVERTEXATTRIBI1UIVPROC glad_glVertexAttribI1uiv = NULL;
	PFNGLVERTEXATTRIBI2IPROC glad_glVertexAttribI2i = NULL;
	PFNGLVERTEXATTRIBI2IVPROC glad_glVertexAttribI2iv = NULL;
	PFNGLVERTEXATTRIBI2UIPROC glad_glVertexAttribI2ui = NULL;
	PFNGLVERTEXATTRIBI2UIVPROC glad_glVertexAttribI2uiv = NULL;
	PFNGLVERTEXATTRIBI3IPROC glad_glVertexAttribI3i = NULL;
	PFNGLVERTEXATTRIBI3IVPROC glad_glVertexAttribI3iv = NULL;
	PFNGLVERTEXATTRIBI3UIPROC glad_glVertexAttribI3ui = NULL;
	PFNGLVERTEXATTRIBI3UIVPROC glad_glVertexAttribI3uiv = NULL;
	PFNGLVERTEXATTRIBI4BVPROC glad_glVertexAttribI4bv = NULL;
	PFNGLVERTEXATTRIBI4IPROC glad_glVertexAttribI4i = NULL;
	PFNGLVERTEXATTRIBI4IVPROC glad_glVertexAttribI4iv = NULL;
	PFNGLVERTEXATTRIBI4SVPROC glad_glVertexAttribI4sv = NULL;
	PFNGLVERTEXATTRIBI4UBVPROC glad_glVertexAttribI4ubv = NULL;
	PFNGLVERTEXATTRIBI4UIPROC glad_glVertexAttribI4ui = NULL;
	PFNGLVERTEXATTRIBI4UIVPROC glad_glVertexAttribI4uiv = NULL;
	PFNGLVERTEXATTRIBI4USVPROC glad_glVertexAttribI4usv = NULL;
	PFNGLVERTEXATTRIBIPOINTERPROC glad_glVertexAttribIPointer = NULL;
	PFNGLVERTEXATTRIBP1UIPROC glad_glVertexAttribP1ui = NULL;
	PFNGLVERTEXATTRIBP1UIVPROC glad_glVertexAttribP1uiv = NULL;
	PFNGLVERTEXATTRIBP2UIPROC glad_glVertexAttribP2ui = NULL;
	PFNGLVERTEXATTRIBP2UIVPROC glad_glVertexAttribP2uiv = NULL;
	PFNGLVERTEXATTRIBP3UIPROC glad_glVertexAttribP3ui = NULL;
	PFNGLVERTEXATTRIBP3UIVPROC glad_glVertexAttribP3uiv = NULL;
	PFNGLVERTEXATTRIBP4UIPROC glad_glVertexAttribP4ui = NULL;
	PFNGLVERTEXATTRIBP4UIVPROC glad_glVertexAttribP4uiv = NULL;
	PFNGLVERTEXATTRIBPOINTERPROC glad_glVertexAttribPointer = NULL;
	PFNGLVERTEXP2UIPROC glad_glVertexP2ui = NULL;
	PFNGLVERTEXP2UIVPROC glad_glVertexP2uiv = NULL;
	PFNGLVERTEXP3UIPROC glad_glVertexP3ui = NULL;
	PFNGLVERTEXP3UIVPROC glad_glVertexP3uiv = NULL;
	PFNGLVERTEXP4UIPROC glad_glVertexP4ui = NULL;
	PFNGLVERTEXP4UIVPROC glad_glVertexP4uiv = NULL;
	PFNGLVERTEXPOINTERPROC glad_glVertexPointer = NULL;
	PFNGLVIEWPORTPROC glad_glViewport = NULL;
	PFNGLWAITSYNCPROC glad_glWaitSync = NULL;
	PFNGLWINDOWPOS2DPROC glad_glWindowPos2d = NULL;
	PFNGLWINDOWPOS2DVPROC glad_glWindowPos2dv = NULL;
	PFNGLWINDOWPOS2FPROC glad_glWindowPos2f = NULL;
	PFNGLWINDOWPOS2FVPROC glad_glWindowPos2fv = NULL;
	PFNGLWINDOWPOS2IPROC glad_glWindowPos2i = NULL;
	PFNGLWINDOWPOS2IVPROC glad_glWindowPos2iv = NULL;
	PFNGLWINDOWPOS2SPROC glad_glWindowPos2s = NULL;
	PFNGLWINDOWPOS2SVPROC glad_glWindowPos2sv = NULL;
	PFNGLWINDOWPOS3DPROC glad_glWindowPos3d = NULL;
	PFNGLWINDOWPOS3DVPROC glad_glWindowPos3dv = NULL;
	PFNGLWINDOWPOS3FPROC glad_glWindowPos3f = NULL;
	PFNGLWINDOWPOS3FVPROC glad_glWindowPos3fv = NULL;
	PFNGLWINDOWPOS3IPROC glad_glWindowPos3i = NULL;
	PFNGLWINDOWPOS3IVPROC glad_glWindowPos3iv = NULL;
	PFNGLWINDOWPOS3SPROC glad_glWindowPos3s = NULL;
	PFNGLWINDOWPOS3SVPROC glad_glWindowPos3sv = NULL;


	static void glad_gl_load_GL_VERSION_1_0(GLADuserptrloadfunc load, void* userptr) {
		if(!GLAD_GL_VERSION_1_0) return;
		glad_glAccum = (PFNGLACCUMPROC)load(userptr, "glAccum");
		glad_glAlphaFunc = (PFNGLALPHAFUNCPROC)load(userptr, "glAlphaFunc");
		glad_glBegin = (PFNGLBEGINPROC)load(userptr, "glBegin");
		glad_glBitmap = (PFNGLBITMAPPROC)load(userptr, "glBitmap");
		glad_glBlendFunc = (PFNGLBLENDFUNCPROC)load(userptr, "glBlendFunc");
		glad_glCallList = (PFNGLCALLLISTPROC)load(userptr, "glCallList");
		glad_glCallLists = (PFNGLCALLLISTSPROC)load(userptr, "glCallLists");
		glad_glClear = (PFNGLCLEARPROC)load(userptr, "glClear");
		glad_glClearAccum = (PFNGLCLEARACCUMPROC)load(userptr, "glClearAccum");
		glad_glClearColor = (PFNGLCLEARCOLORPROC)load(userptr, "glClearColor");
		glad_glClearDepth = (PFNGLCLEARDEPTHPROC)load(userptr, "glClearDepth");
		glad_glClearIndex = (PFNGLCLEARINDEXPROC)load(userptr, "glClearIndex");
		glad_glClearStencil = (PFNGLCLEARSTENCILPROC)load(userptr, "glClearStencil");
		glad_glClipPlane = (PFNGLCLIPPLANEPROC)load(userptr, "glClipPlane");
		glad_glColor3b = (PFNGLCOLOR3BPROC)load(userptr, "glColor3b");
		glad_glColor3bv = (PFNGLCOLOR3BVPROC)load(userptr, "glColor3bv");
		glad_glColor3d = (PFNGLCOLOR3DPROC)load(userptr, "glColor3d");
		glad_glColor3dv = (PFNGLCOLOR3DVPROC)load(userptr, "glColor3dv");
		glad_glColor3f = (PFNGLCOLOR3FPROC)load(userptr, "glColor3f");
		glad_glColor3fv = (PFNGLCOLOR3FVPROC)load(userptr, "glColor3fv");
		glad_glColor3i = (PFNGLCOLOR3IPROC)load(userptr, "glColor3i");
		glad_glColor3iv = (PFNGLCOLOR3IVPROC)load(userptr, "glColor3iv");
		glad_glColor3s = (PFNGLCOLOR3SPROC)load(userptr, "glColor3s");
		glad_glColor3sv = (PFNGLCOLOR3SVPROC)load(userptr, "glColor3sv");
		glad_glColor3ub = (PFNGLCOLOR3UBPROC)load(userptr, "glColor3ub");
		glad_glColor3ubv = (PFNGLCOLOR3UBVPROC)load(userptr, "glColor3ubv");
		glad_glColor3ui = (PFNGLCOLOR3UIPROC)load(userptr, "glColor3ui");
		glad_glColor3uiv = (PFNGLCOLOR3UIVPROC)load(userptr, "glColor3uiv");
		glad_glColor3us = (PFNGLCOLOR3USPROC)load(userptr, "glColor3us");
		glad_glColor3usv = (PFNGLCOLOR3USVPROC)load(userptr, "glColor3usv");
		glad_glColor4b = (PFNGLCOLOR4BPROC)load(userptr, "glColor4b");
		glad_glColor4bv = (PFNGLCOLOR4BVPROC)load(userptr, "glColor4bv");
		glad_glColor4d = (PFNGLCOLOR4DPROC)load(userptr, "glColor4d");
		glad_glColor4dv = (PFNGLCOLOR4DVPROC)load(userptr, "glColor4dv");
		glad_glColor4f = (PFNGLCOLOR4FPROC)load(userptr, "glColor4f");
		glad_glColor4fv = (PFNGLCOLOR4FVPROC)load(userptr, "glColor4fv");
		glad_glColor4i = (PFNGLCOLOR4IPROC)load(userptr, "glColor4i");
		glad_glColor4iv = (PFNGLCOLOR4IVPROC)load(userptr, "glColor4iv");
		glad_glColor4s = (PFNGLCOLOR4SPROC)load(userptr, "glColor4s");
		glad_glColor4sv = (PFNGLCOLOR4SVPROC)load(userptr, "glColor4sv");
		glad_glColor4ub = (PFNGLCOLOR4UBPROC)load(userptr, "glColor4ub");
		glad_glColor4ubv = (PFNGLCOLOR4UBVPROC)load(userptr, "glColor4ubv");
		glad_glColor4ui = (PFNGLCOLOR4UIPROC)load(userptr, "glColor4ui");
		glad_glColor4uiv = (PFNGLCOLOR4UIVPROC)load(userptr, "glColor4uiv");
		glad_glColor4us = (PFNGLCOLOR4USPROC)load(userptr, "glColor4us");
		glad_glColor4usv = (PFNGLCOLOR4USVPROC)load(userptr, "glColor4usv");
		glad_glColorMask = (PFNGLCOLORMASKPROC)load(userptr, "glColorMask");
		glad_glColorMaterial = (PFNGLCOLORMATERIALPROC)load(userptr, "glColorMaterial");
		glad_glCopyPixels = (PFNGLCOPYPIXELSPROC)load(userptr, "glCopyPixels");
		glad_glCullFace = (PFNGLCULLFACEPROC)load(userptr, "glCullFace");
		glad_glDeleteLists = (PFNGLDELETELISTSPROC)load(userptr, "glDeleteLists");
		glad_glDepthFunc = (PFNGLDEPTHFUNCPROC)load(userptr, "glDepthFunc");
		glad_glDepthMask = (PFNGLDEPTHMASKPROC)load(userptr, "glDepthMask");
		glad_glDepthRange = (PFNGLDEPTHRANGEPROC)load(userptr, "glDepthRange");
		glad_glDisable = (PFNGLDISABLEPROC)load(userptr, "glDisable");
		glad_glDrawBuffer = (PFNGLDRAWBUFFERPROC)load(userptr, "glDrawBuffer");
		glad_glDrawPixels = (PFNGLDRAWPIXELSPROC)load(userptr, "glDrawPixels");
		glad_glEdgeFlag = (PFNGLEDGEFLAGPROC)load(userptr, "glEdgeFlag");
		glad_glEdgeFlagv = (PFNGLEDGEFLAGVPROC)load(userptr, "glEdgeFlagv");
		glad_glEnable = (PFNGLENABLEPROC)load(userptr, "glEnable");
		glad_glEnd = (PFNGLENDPROC)load(userptr, "glEnd");
		glad_glEndList = (PFNGLENDLISTPROC)load(userptr, "glEndList");
		glad_glEvalCoord1d = (PFNGLEVALCOORD1DPROC)load(userptr, "glEvalCoord1d");
		glad_glEvalCoord1dv = (PFNGLEVALCOORD1DVPROC)load(userptr, "glEvalCoord1dv");
		glad_glEvalCoord1f = (PFNGLEVALCOORD1FPROC)load(userptr, "glEvalCoord1f");
		glad_glEvalCoord1fv = (PFNGLEVALCOORD1FVPROC)load(userptr, "glEvalCoord1fv");
		glad_glEvalCoord2d = (PFNGLEVALCOORD2DPROC)load(userptr, "glEvalCoord2d");
		glad_glEvalCoord2dv = (PFNGLEVALCOORD2DVPROC)load(userptr, "glEvalCoord2dv");
		glad_glEvalCoord2f = (PFNGLEVALCOORD2FPROC)load(userptr, "glEvalCoord2f");
		glad_glEvalCoord2fv = (PFNGLEVALCOORD2FVPROC)load(userptr, "glEvalCoord2fv");
		glad_glEvalMesh1 = (PFNGLEVALMESH1PROC)load(userptr, "glEvalMesh1");
		glad_glEvalMesh2 = (PFNGLEVALMESH2PROC)load(userptr, "glEvalMesh2");
		glad_glEvalPoint1 = (PFNGLEVALPOINT1PROC)load(userptr, "glEvalPoint1");
		glad_glEvalPoint2 = (PFNGLEVALPOINT2PROC)load(userptr, "glEvalPoint2");
		glad_glFeedbackBuffer = (PFNGLFEEDBACKBUFFERPROC)load(userptr, "glFeedbackBuffer");
		glad_glFinish = (PFNGLFINISHPROC)load(userptr, "glFinish");
		glad_glFlush = (PFNGLFLUSHPROC)load(userptr, "glFlush");
		glad_glFogf = (PFNGLFOGFPROC)load(userptr, "glFogf");
		glad_glFogfv = (PFNGLFOGFVPROC)load(userptr, "glFogfv");
		glad_glFogi = (PFNGLFOGIPROC)load(userptr, "glFogi");
		glad_glFogiv = (PFNGLFOGIVPROC)load(userptr, "glFogiv");
		glad_glFrontFace = (PFNGLFRONTFACEPROC)load(userptr, "glFrontFace");
		glad_glFrustum = (PFNGLFRUSTUMPROC)load(userptr, "glFrustum");
		glad_glGenLists = (PFNGLGENLISTSPROC)load(userptr, "glGenLists");
		glad_glGetBooleanv = (PFNGLGETBOOLEANVPROC)load(userptr, "glGetBooleanv");
		glad_glGetClipPlane = (PFNGLGETCLIPPLANEPROC)load(userptr, "glGetClipPlane");
		glad_glGetDoublev = (PFNGLGETDOUBLEVPROC)load(userptr, "glGetDoublev");
		glad_glGetError = (PFNGLGETERRORPROC)load(userptr, "glGetError");
		glad_glGetFloatv = (PFNGLGETFLOATVPROC)load(userptr, "glGetFloatv");
		glad_glGetIntegerv = (PFNGLGETINTEGERVPROC)load(userptr, "glGetIntegerv");
		glad_glGetLightfv = (PFNGLGETLIGHTFVPROC)load(userptr, "glGetLightfv");
		glad_glGetLightiv = (PFNGLGETLIGHTIVPROC)load(userptr, "glGetLightiv");
		glad_glGetMapdv = (PFNGLGETMAPDVPROC)load(userptr, "glGetMapdv");
		glad_glGetMapfv = (PFNGLGETMAPFVPROC)load(userptr, "glGetMapfv");
		glad_glGetMapiv = (PFNGLGETMAPIVPROC)load(userptr, "glGetMapiv");
		glad_glGetMaterialfv = (PFNGLGETMATERIALFVPROC)load(userptr, "glGetMaterialfv");
		glad_glGetMaterialiv = (PFNGLGETMATERIALIVPROC)load(userptr, "glGetMaterialiv");
		glad_glGetPixelMapfv = (PFNGLGETPIXELMAPFVPROC)load(userptr, "glGetPixelMapfv");
		glad_glGetPixelMapuiv = (PFNGLGETPIXELMAPUIVPROC)load(userptr, "glGetPixelMapuiv");
		glad_glGetPixelMapusv = (PFNGLGETPIXELMAPUSVPROC)load(userptr, "glGetPixelMapusv");
		glad_glGetPolygonStipple = (PFNGLGETPOLYGONSTIPPLEPROC)load(userptr, "glGetPolygonStipple");
		glad_glGetString = (PFNGLGETSTRINGPROC)load(userptr, "glGetString");
		glad_glGetTexEnvfv = (PFNGLGETTEXENVFVPROC)load(userptr, "glGetTexEnvfv");
		glad_glGetTexEnviv = (PFNGLGETTEXENVIVPROC)load(userptr, "glGetTexEnviv");
		glad_glGetTexGendv = (PFNGLGETTEXGENDVPROC)load(userptr, "glGetTexGendv");
		glad_glGetTexGenfv = (PFNGLGETTEXGENFVPROC)load(userptr, "glGetTexGenfv");
		glad_glGetTexGeniv = (PFNGLGETTEXGENIVPROC)load(userptr, "glGetTexGeniv");
		glad_glGetTexImage = (PFNGLGETTEXIMAGEPROC)load(userptr, "glGetTexImage");
		glad_glGetTexLevelParameterfv = (PFNGLGETTEXLEVELPARAMETERFVPROC)load(userptr, "glGetTexLevelParameterfv");
		glad_glGetTexLevelParameteriv = (PFNGLGETTEXLEVELPARAMETERIVPROC)load(userptr, "glGetTexLevelParameteriv");
		glad_glGetTexParameterfv = (PFNGLGETTEXPARAMETERFVPROC)load(userptr, "glGetTexParameterfv");
		glad_glGetTexParameteriv = (PFNGLGETTEXPARAMETERIVPROC)load(userptr, "glGetTexParameteriv");
		glad_glHint = (PFNGLHINTPROC)load(userptr, "glHint");
		glad_glIndexMask = (PFNGLINDEXMASKPROC)load(userptr, "glIndexMask");
		glad_glIndexd = (PFNGLINDEXDPROC)load(userptr, "glIndexd");
		glad_glIndexdv = (PFNGLINDEXDVPROC)load(userptr, "glIndexdv");
		glad_glIndexf = (PFNGLINDEXFPROC)load(userptr, "glIndexf");
		glad_glIndexfv = (PFNGLINDEXFVPROC)load(userptr, "glIndexfv");
		glad_glIndexi = (PFNGLINDEXIPROC)load(userptr, "glIndexi");
		glad_glIndexiv = (PFNGLINDEXIVPROC)load(userptr, "glIndexiv");
		glad_glIndexs = (PFNGLINDEXSPROC)load(userptr, "glIndexs");
		glad_glIndexsv = (PFNGLINDEXSVPROC)load(userptr, "glIndexsv");
		glad_glInitNames = (PFNGLINITNAMESPROC)load(userptr, "glInitNames");
		glad_glIsEnabled = (PFNGLISENABLEDPROC)load(userptr, "glIsEnabled");
		glad_glIsList = (PFNGLISLISTPROC)load(userptr, "glIsList");
		glad_glLightModelf = (PFNGLLIGHTMODELFPROC)load(userptr, "glLightModelf");
		glad_glLightModelfv = (PFNGLLIGHTMODELFVPROC)load(userptr, "glLightModelfv");
		glad_glLightModeli = (PFNGLLIGHTMODELIPROC)load(userptr, "glLightModeli");
		glad_glLightModeliv = (PFNGLLIGHTMODELIVPROC)load(userptr, "glLightModeliv");
		glad_glLightf = (PFNGLLIGHTFPROC)load(userptr, "glLightf");
		glad_glLightfv = (PFNGLLIGHTFVPROC)load(userptr, "glLightfv");
		glad_glLighti = (PFNGLLIGHTIPROC)load(userptr, "glLighti");
		glad_glLightiv = (PFNGLLIGHTIVPROC)load(userptr, "glLightiv");
		glad_glLineStipple = (PFNGLLINESTIPPLEPROC)load(userptr, "glLineStipple");
		glad_glLineWidth = (PFNGLLINEWIDTHPROC)load(userptr, "glLineWidth");
		glad_glListBase = (PFNGLLISTBASEPROC)load(userptr, "glListBase");
		glad_glLoadIdentity = (PFNGLLOADIDENTITYPROC)load(userptr, "glLoadIdentity");
		glad_glLoadMatrixd = (PFNGLLOADMATRIXDPROC)load(userptr, "glLoadMatrixd");
		glad_glLoadMatrixf = (PFNGLLOADMATRIXFPROC)load(userptr, "glLoadMatrixf");
		glad_glLoadName = (PFNGLLOADNAMEPROC)load(userptr, "glLoadName");
		glad_glLogicOp = (PFNGLLOGICOPPROC)load(userptr, "glLogicOp");
		glad_glMap1d = (PFNGLMAP1DPROC)load(userptr, "glMap1d");
		glad_glMap1f = (PFNGLMAP1FPROC)load(userptr, "glMap1f");
		glad_glMap2d = (PFNGLMAP2DPROC)load(userptr, "glMap2d");
		glad_glMap2f = (PFNGLMAP2FPROC)load(userptr, "glMap2f");
		glad_glMapGrid1d = (PFNGLMAPGRID1DPROC)load(userptr, "glMapGrid1d");
		glad_glMapGrid1f = (PFNGLMAPGRID1FPROC)load(userptr, "glMapGrid1f");
		glad_glMapGrid2d = (PFNGLMAPGRID2DPROC)load(userptr, "glMapGrid2d");
		glad_glMapGrid2f = (PFNGLMAPGRID2FPROC)load(userptr, "glMapGrid2f");
		glad_glMaterialf = (PFNGLMATERIALFPROC)load(userptr, "glMaterialf");
		glad_glMaterialfv = (PFNGLMATERIALFVPROC)load(userptr, "glMaterialfv");
		glad_glMateriali = (PFNGLMATERIALIPROC)load(userptr, "glMateriali");
		glad_glMaterialiv = (PFNGLMATERIALIVPROC)load(userptr, "glMaterialiv");
		glad_glMatrixMode = (PFNGLMATRIXMODEPROC)load(userptr, "glMatrixMode");
		glad_glMultMatrixd = (PFNGLMULTMATRIXDPROC)load(userptr, "glMultMatrixd");
		glad_glMultMatrixf = (PFNGLMULTMATRIXFPROC)load(userptr, "glMultMatrixf");
		glad_glNewList = (PFNGLNEWLISTPROC)load(userptr, "glNewList");
		glad_glNormal3b = (PFNGLNORMAL3BPROC)load(userptr, "glNormal3b");
		glad_glNormal3bv = (PFNGLNORMAL3BVPROC)load(userptr, "glNormal3bv");
		glad_glNormal3d = (PFNGLNORMAL3DPROC)load(userptr, "glNormal3d");
		glad_glNormal3dv = (PFNGLNORMAL3DVPROC)load(userptr, "glNormal3dv");
		glad_glNormal3f = (PFNGLNORMAL3FPROC)load(userptr, "glNormal3f");
		glad_glNormal3fv = (PFNGLNORMAL3FVPROC)load(userptr, "glNormal3fv");
		glad_glNormal3i = (PFNGLNORMAL3IPROC)load(userptr, "glNormal3i");
		glad_glNormal3iv = (PFNGLNORMAL3IVPROC)load(userptr, "glNormal3iv");
		glad_glNormal3s = (PFNGLNORMAL3SPROC)load(userptr, "glNormal3s");
		glad_glNormal3sv = (PFNGLNORMAL3SVPROC)load(userptr, "glNormal3sv");
		glad_glOrtho = (PFNGLORTHOPROC)load(userptr, "glOrtho");
		glad_glPassThrough = (PFNGLPASSTHROUGHPROC)load(userptr, "glPassThrough");
		glad_glPixelMapfv = (PFNGLPIXELMAPFVPROC)load(userptr, "glPixelMapfv");
		glad_glPixelMapuiv = (PFNGLPIXELMAPUIVPROC)load(userptr, "glPixelMapuiv");
		glad_glPixelMapusv = (PFNGLPIXELMAPUSVPROC)load(userptr, "glPixelMapusv");
		glad_glPixelStoref = (PFNGLPIXELSTOREFPROC)load(userptr, "glPixelStoref");
		glad_glPixelStorei = (PFNGLPIXELSTOREIPROC)load(userptr, "glPixelStorei");
		glad_glPixelTransferf = (PFNGLPIXELTRANSFERFPROC)load(userptr, "glPixelTransferf");
		glad_glPixelTransferi = (PFNGLPIXELTRANSFERIPROC)load(userptr, "glPixelTransferi");
		glad_glPixelZoom = (PFNGLPIXELZOOMPROC)load(userptr, "glPixelZoom");
		glad_glPointSize = (PFNGLPOINTSIZEPROC)load(userptr, "glPointSize");
		glad_glPolygonMode = (PFNGLPOLYGONMODEPROC)load(userptr, "glPolygonMode");
		glad_glPolygonStipple = (PFNGLPOLYGONSTIPPLEPROC)load(userptr, "glPolygonStipple");
		glad_glPopAttrib = (PFNGLPOPATTRIBPROC)load(userptr, "glPopAttrib");
		glad_glPopMatrix = (PFNGLPOPMATRIXPROC)load(userptr, "glPopMatrix");
		glad_glPopName = (PFNGLPOPNAMEPROC)load(userptr, "glPopName");
		glad_glPushAttrib = (PFNGLPUSHATTRIBPROC)load(userptr, "glPushAttrib");
		glad_glPushMatrix = (PFNGLPUSHMATRIXPROC)load(userptr, "glPushMatrix");
		glad_glPushName = (PFNGLPUSHNAMEPROC)load(userptr, "glPushName");
		glad_glRasterPos2d = (PFNGLRASTERPOS2DPROC)load(userptr, "glRasterPos2d");
		glad_glRasterPos2dv = (PFNGLRASTERPOS2DVPROC)load(userptr, "glRasterPos2dv");
		glad_glRasterPos2f = (PFNGLRASTERPOS2FPROC)load(userptr, "glRasterPos2f");
		glad_glRasterPos2fv = (PFNGLRASTERPOS2FVPROC)load(userptr, "glRasterPos2fv");
		glad_glRasterPos2i = (PFNGLRASTERPOS2IPROC)load(userptr, "glRasterPos2i");
		glad_glRasterPos2iv = (PFNGLRASTERPOS2IVPROC)load(userptr, "glRasterPos2iv");
		glad_glRasterPos2s = (PFNGLRASTERPOS2SPROC)load(userptr, "glRasterPos2s");
		glad_glRasterPos2sv = (PFNGLRASTERPOS2SVPROC)load(userptr, "glRasterPos2sv");
		glad_glRasterPos3d = (PFNGLRASTERPOS3DPROC)load(userptr, "glRasterPos3d");
		glad_glRasterPos3dv = (PFNGLRASTERPOS3DVPROC)load(userptr, "glRasterPos3dv");
		glad_glRasterPos3f = (PFNGLRASTERPOS3FPROC)load(userptr, "glRasterPos3f");
		glad_glRasterPos3fv = (PFNGLRASTERPOS3FVPROC)load(userptr, "glRasterPos3fv");
		glad_glRasterPos3i = (PFNGLRASTERPOS3IPROC)load(userptr, "glRasterPos3i");
		glad_glRasterPos3iv = (PFNGLRASTERPOS3IVPROC)load(userptr, "glRasterPos3iv");
		glad_glRasterPos3s = (PFNGLRASTERPOS3SPROC)load(userptr, "glRasterPos3s");
		glad_glRasterPos3sv = (PFNGLRASTERPOS3SVPROC)load(userptr, "glRasterPos3sv");
		glad_glRasterPos4d = (PFNGLRASTERPOS4DPROC)load(userptr, "glRasterPos4d");
		glad_glRasterPos4dv = (PFNGLRASTERPOS4DVPROC)load(userptr, "glRasterPos4dv");
		glad_glRasterPos4f = (PFNGLRASTERPOS4FPROC)load(userptr, "glRasterPos4f");
		glad_glRasterPos4fv = (PFNGLRASTERPOS4FVPROC)load(userptr, "glRasterPos4fv");
		glad_glRasterPos4i = (PFNGLRASTERPOS4IPROC)load(userptr, "glRasterPos4i");
		glad_glRasterPos4iv = (PFNGLRASTERPOS4IVPROC)load(userptr, "glRasterPos4iv");
		glad_glRasterPos4s = (PFNGLRASTERPOS4SPROC)load(userptr, "glRasterPos4s");
		glad_glRasterPos4sv = (PFNGLRASTERPOS4SVPROC)load(userptr, "glRasterPos4sv");
		glad_glReadBuffer = (PFNGLREADBUFFERPROC)load(userptr, "glReadBuffer");
		glad_glReadPixels = (PFNGLREADPIXELSPROC)load(userptr, "glReadPixels");
		glad_glRectd = (PFNGLRECTDPROC)load(userptr, "glRectd");
		glad_glRectdv = (PFNGLRECTDVPROC)load(userptr, "glRectdv");
		glad_glRectf = (PFNGLRECTFPROC)load(userptr, "glRectf");
		glad_glRectfv = (PFNGLRECTFVPROC)load(userptr, "glRectfv");
		glad_glRecti = (PFNGLRECTIPROC)load(userptr, "glRecti");
		glad_glRectiv = (PFNGLRECTIVPROC)load(userptr, "glRectiv");
		glad_glRects = (PFNGLRECTSPROC)load(userptr, "glRects");
		glad_glRectsv = (PFNGLRECTSVPROC)load(userptr, "glRectsv");
		glad_glRenderMode = (PFNGLRENDERMODEPROC)load(userptr, "glRenderMode");
		glad_glRotated = (PFNGLROTATEDPROC)load(userptr, "glRotated");
		glad_glRotatef = (PFNGLROTATEFPROC)load(userptr, "glRotatef");
		glad_glScaled = (PFNGLSCALEDPROC)load(userptr, "glScaled");
		glad_glScalef = (PFNGLSCALEFPROC)load(userptr, "glScalef");
		glad_glScissor = (PFNGLSCISSORPROC)load(userptr, "glScissor");
		glad_glSelectBuffer = (PFNGLSELECTBUFFERPROC)load(userptr, "glSelectBuffer");
		glad_glShadeModel = (PFNGLSHADEMODELPROC)load(userptr, "glShadeModel");
		glad_glStencilFunc = (PFNGLSTENCILFUNCPROC)load(userptr, "glStencilFunc");
		glad_glStencilMask = (PFNGLSTENCILMASKPROC)load(userptr, "glStencilMask");
		glad_glStencilOp = (PFNGLSTENCILOPPROC)load(userptr, "glStencilOp");
		glad_glTexCoord1d = (PFNGLTEXCOORD1DPROC)load(userptr, "glTexCoord1d");
		glad_glTexCoord1dv = (PFNGLTEXCOORD1DVPROC)load(userptr, "glTexCoord1dv");
		glad_glTexCoord1f = (PFNGLTEXCOORD1FPROC)load(userptr, "glTexCoord1f");
		glad_glTexCoord1fv = (PFNGLTEXCOORD1FVPROC)load(userptr, "glTexCoord1fv");
		glad_glTexCoord1i = (PFNGLTEXCOORD1IPROC)load(userptr, "glTexCoord1i");
		glad_glTexCoord1iv = (PFNGLTEXCOORD1IVPROC)load(userptr, "glTexCoord1iv");
		glad_glTexCoord1s = (PFNGLTEXCOORD1SPROC)load(userptr, "glTexCoord1s");
		glad_glTexCoord1sv = (PFNGLTEXCOORD1SVPROC)load(userptr, "glTexCoord1sv");
		glad_glTexCoord2d = (PFNGLTEXCOORD2DPROC)load(userptr, "glTexCoord2d");
		glad_glTexCoord2dv = (PFNGLTEXCOORD2DVPROC)load(userptr, "glTexCoord2dv");
		glad_glTexCoord2f = (PFNGLTEXCOORD2FPROC)load(userptr, "glTexCoord2f");
		glad_glTexCoord2fv = (PFNGLTEXCOORD2FVPROC)load(userptr, "glTexCoord2fv");
		glad_glTexCoord2i = (PFNGLTEXCOORD2IPROC)load(userptr, "glTexCoord2i");
		glad_glTexCoord2iv = (PFNGLTEXCOORD2IVPROC)load(userptr, "glTexCoord2iv");
		glad_glTexCoord2s = (PFNGLTEXCOORD2SPROC)load(userptr, "glTexCoord2s");
		glad_glTexCoord2sv = (PFNGLTEXCOORD2SVPROC)load(userptr, "glTexCoord2sv");
		glad_glTexCoord3d = (PFNGLTEXCOORD3DPROC)load(userptr, "glTexCoord3d");
		glad_glTexCoord3dv = (PFNGLTEXCOORD3DVPROC)load(userptr, "glTexCoord3dv");
		glad_glTexCoord3f = (PFNGLTEXCOORD3FPROC)load(userptr, "glTexCoord3f");
		glad_glTexCoord3fv = (PFNGLTEXCOORD3FVPROC)load(userptr, "glTexCoord3fv");
		glad_glTexCoord3i = (PFNGLTEXCOORD3IPROC)load(userptr, "glTexCoord3i");
		glad_glTexCoord3iv = (PFNGLTEXCOORD3IVPROC)load(userptr, "glTexCoord3iv");
		glad_glTexCoord3s = (PFNGLTEXCOORD3SPROC)load(userptr, "glTexCoord3s");
		glad_glTexCoord3sv = (PFNGLTEXCOORD3SVPROC)load(userptr, "glTexCoord3sv");
		glad_glTexCoord4d = (PFNGLTEXCOORD4DPROC)load(userptr, "glTexCoord4d");
		glad_glTexCoord4dv = (PFNGLTEXCOORD4DVPROC)load(userptr, "glTexCoord4dv");
		glad_glTexCoord4f = (PFNGLTEXCOORD4FPROC)load(userptr, "glTexCoord4f");
		glad_glTexCoord4fv = (PFNGLTEXCOORD4FVPROC)load(userptr, "glTexCoord4fv");
		glad_glTexCoord4i = (PFNGLTEXCOORD4IPROC)load(userptr, "glTexCoord4i");
		glad_glTexCoord4iv = (PFNGLTEXCOORD4IVPROC)load(userptr, "glTexCoord4iv");
		glad_glTexCoord4s = (PFNGLTEXCOORD4SPROC)load(userptr, "glTexCoord4s");
		glad_glTexCoord4sv = (PFNGLTEXCOORD4SVPROC)load(userptr, "glTexCoord4sv");
		glad_glTexEnvf = (PFNGLTEXENVFPROC)load(userptr, "glTexEnvf");
		glad_glTexEnvfv = (PFNGLTEXENVFVPROC)load(userptr, "glTexEnvfv");
		glad_glTexEnvi = (PFNGLTEXENVIPROC)load(userptr, "glTexEnvi");
		glad_glTexEnviv = (PFNGLTEXENVIVPROC)load(userptr, "glTexEnviv");
		glad_glTexGend = (PFNGLTEXGENDPROC)load(userptr, "glTexGend");
		glad_glTexGendv = (PFNGLTEXGENDVPROC)load(userptr, "glTexGendv");
		glad_glTexGenf = (PFNGLTEXGENFPROC)load(userptr, "glTexGenf");
		glad_glTexGenfv = (PFNGLTEXGENFVPROC)load(userptr, "glTexGenfv");
		glad_glTexGeni = (PFNGLTEXGENIPROC)load(userptr, "glTexGeni");
		glad_glTexGeniv = (PFNGLTEXGENIVPROC)load(userptr, "glTexGeniv");
		glad_glTexImage1D = (PFNGLTEXIMAGE1DPROC)load(userptr, "glTexImage1D");
		glad_glTexImage2D = (PFNGLTEXIMAGE2DPROC)load(userptr, "glTexImage2D");
		glad_glTexParameterf = (PFNGLTEXPARAMETERFPROC)load(userptr, "glTexParameterf");
		glad_glTexParameterfv = (PFNGLTEXPARAMETERFVPROC)load(userptr, "glTexParameterfv");
		glad_glTexParameteri = (PFNGLTEXPARAMETERIPROC)load(userptr, "glTexParameteri");
		glad_glTexParameteriv = (PFNGLTEXPARAMETERIVPROC)load(userptr, "glTexParameteriv");
		glad_glTranslated = (PFNGLTRANSLATEDPROC)load(userptr, "glTranslated");
		glad_glTranslatef = (PFNGLTRANSLATEFPROC)load(userptr, "glTranslatef");
		glad_glVertex2d = (PFNGLVERTEX2DPROC)load(userptr, "glVertex2d");
		glad_glVertex2dv = (PFNGLVERTEX2DVPROC)load(userptr, "glVertex2dv");
		glad_glVertex2f = (PFNGLVERTEX2FPROC)load(userptr, "glVertex2f");
		glad_glVertex2fv = (PFNGLVERTEX2FVPROC)load(userptr, "glVertex2fv");
		glad_glVertex2i = (PFNGLVERTEX2IPROC)load(userptr, "glVertex2i");
		glad_glVertex2iv = (PFNGLVERTEX2IVPROC)load(userptr, "glVertex2iv");
		glad_glVertex2s = (PFNGLVERTEX2SPROC)load(userptr, "glVertex2s");
		glad_glVertex2sv = (PFNGLVERTEX2SVPROC)load(userptr, "glVertex2sv");
		glad_glVertex3d = (PFNGLVERTEX3DPROC)load(userptr, "glVertex3d");
		glad_glVertex3dv = (PFNGLVERTEX3DVPROC)load(userptr, "glVertex3dv");
		glad_glVertex3f = (PFNGLVERTEX3FPROC)load(userptr, "glVertex3f");
		glad_glVertex3fv = (PFNGLVERTEX3FVPROC)load(userptr, "glVertex3fv");
		glad_glVertex3i = (PFNGLVERTEX3IPROC)load(userptr, "glVertex3i");
		glad_glVertex3iv = (PFNGLVERTEX3IVPROC)load(userptr, "glVertex3iv");
		glad_glVertex3s = (PFNGLVERTEX3SPROC)load(userptr, "glVertex3s");
		glad_glVertex3sv = (PFNGLVERTEX3SVPROC)load(userptr, "glVertex3sv");
		glad_glVertex4d = (PFNGLVERTEX4DPROC)load(userptr, "glVertex4d");
		glad_glVertex4dv = (PFNGLVERTEX4DVPROC)load(userptr, "glVertex4dv");
		glad_glVertex4f = (PFNGLVERTEX4FPROC)load(userptr, "glVertex4f");
		glad_glVertex4fv = (PFNGLVERTEX4FVPROC)load(userptr, "glVertex4fv");
		glad_glVertex4i = (PFNGLVERTEX4IPROC)load(userptr, "glVertex4i");
		glad_glVertex4iv = (PFNGLVERTEX4IVPROC)load(userptr, "glVertex4iv");
		glad_glVertex4s = (PFNGLVERTEX4SPROC)load(userptr, "glVertex4s");
		glad_glVertex4sv = (PFNGLVERTEX4SVPROC)load(userptr, "glVertex4sv");
		glad_glViewport = (PFNGLVIEWPORTPROC)load(userptr, "glViewport");
	}
	static void glad_gl_load_GL_VERSION_1_1(GLADuserptrloadfunc load, void* userptr) {
		if(!GLAD_GL_VERSION_1_1) return;
		glad_glAreTexturesResident = (PFNGLARETEXTURESRESIDENTPROC)load(userptr, "glAreTexturesResident");
		glad_glArrayElement = (PFNGLARRAYELEMENTPROC)load(userptr, "glArrayElement");
		glad_glBindTexture = (PFNGLBINDTEXTUREPROC)load(userptr, "glBindTexture");
		glad_glColorPointer = (PFNGLCOLORPOINTERPROC)load(userptr, "glColorPointer");
		glad_glCopyTexImage1D = (PFNGLCOPYTEXIMAGE1DPROC)load(userptr, "glCopyTexImage1D");
		glad_glCopyTexImage2D = (PFNGLCOPYTEXIMAGE2DPROC)load(userptr, "glCopyTexImage2D");
		glad_glCopyTexSubImage1D = (PFNGLCOPYTEXSUBIMAGE1DPROC)load(userptr, "glCopyTexSubImage1D");
		glad_glCopyTexSubImage2D = (PFNGLCOPYTEXSUBIMAGE2DPROC)load(userptr, "glCopyTexSubImage2D");
		glad_glDeleteTextures = (PFNGLDELETETEXTURESPROC)load(userptr, "glDeleteTextures");
		glad_glDisableClientState = (PFNGLDISABLECLIENTSTATEPROC)load(userptr, "glDisableClientState");
		glad_glDrawArrays = (PFNGLDRAWARRAYSPROC)load(userptr, "glDrawArrays");
		glad_glDrawElements = (PFNGLDRAWELEMENTSPROC)load(userptr, "glDrawElements");
		glad_glEdgeFlagPointer = (PFNGLEDGEFLAGPOINTERPROC)load(userptr, "glEdgeFlagPointer");
		glad_glEnableClientState = (PFNGLENABLECLIENTSTATEPROC)load(userptr, "glEnableClientState");
		glad_glGenTextures = (PFNGLGENTEXTURESPROC)load(userptr, "glGenTextures");
		glad_glGetPointerv = (PFNGLGETPOINTERVPROC)load(userptr, "glGetPointerv");
		glad_glIndexPointer = (PFNGLINDEXPOINTERPROC)load(userptr, "glIndexPointer");
		glad_glIndexub = (PFNGLINDEXUBPROC)load(userptr, "glIndexub");
		glad_glIndexubv = (PFNGLINDEXUBVPROC)load(userptr, "glIndexubv");
		glad_glInterleavedArrays = (PFNGLINTERLEAVEDARRAYSPROC)load(userptr, "glInterleavedArrays");
		glad_glIsTexture = (PFNGLISTEXTUREPROC)load(userptr, "glIsTexture");
		glad_glNormalPointer = (PFNGLNORMALPOINTERPROC)load(userptr, "glNormalPointer");
		glad_glPolygonOffset = (PFNGLPOLYGONOFFSETPROC)load(userptr, "glPolygonOffset");
		glad_glPopClientAttrib = (PFNGLPOPCLIENTATTRIBPROC)load(userptr, "glPopClientAttrib");
		glad_glPrioritizeTextures = (PFNGLPRIORITIZETEXTURESPROC)load(userptr, "glPrioritizeTextures");
		glad_glPushClientAttrib = (PFNGLPUSHCLIENTATTRIBPROC)load(userptr, "glPushClientAttrib");
		glad_glTexCoordPointer = (PFNGLTEXCOORDPOINTERPROC)load(userptr, "glTexCoordPointer");
		glad_glTexSubImage1D = (PFNGLTEXSUBIMAGE1DPROC)load(userptr, "glTexSubImage1D");
		glad_glTexSubImage2D = (PFNGLTEXSUBIMAGE2DPROC)load(userptr, "glTexSubImage2D");
		glad_glVertexPointer = (PFNGLVERTEXPOINTERPROC)load(userptr, "glVertexPointer");
	}
	static void glad_gl_load_GL_VERSION_1_2(GLADuserptrloadfunc load, void* userptr) {
		if(!GLAD_GL_VERSION_1_2) return;
		glad_glCopyTexSubImage3D = (PFNGLCOPYTEXSUBIMAGE3DPROC)load(userptr, "glCopyTexSubImage3D");
		glad_glDrawRangeElements = (PFNGLDRAWRANGEELEMENTSPROC)load(userptr, "glDrawRangeElements");
		glad_glTexImage3D = (PFNGLTEXIMAGE3DPROC)load(userptr, "glTexImage3D");
		glad_glTexSubImage3D = (PFNGLTEXSUBIMAGE3DPROC)load(userptr, "glTexSubImage3D");
	}
	static void glad_gl_load_GL_VERSION_1_3(GLADuserptrloadfunc load, void* userptr) {
		if(!GLAD_GL_VERSION_1_3) return;
		glad_glActiveTexture = (PFNGLACTIVETEXTUREPROC)load(userptr, "glActiveTexture");
		glad_glClientActiveTexture = (PFNGLCLIENTACTIVETEXTUREPROC)load(userptr, "glClientActiveTexture");
		glad_glCompressedTexImage1D = (PFNGLCOMPRESSEDTEXIMAGE1DPROC)load(userptr, "glCompressedTexImage1D");
		glad_glCompressedTexImage2D = (PFNGLCOMPRESSEDTEXIMAGE2DPROC)load(userptr, "glCompressedTexImage2D");
		glad_glCompressedTexImage3D = (PFNGLCOMPRESSEDTEXIMAGE3DPROC)load(userptr, "glCompressedTexImage3D");
		glad_glCompressedTexSubImage1D = (PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC)load(userptr, "glCompressedTexSubImage1D");
		glad_glCompressedTexSubImage2D = (PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC)load(userptr, "glCompressedTexSubImage2D");
		glad_glCompressedTexSubImage3D = (PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC)load(userptr, "glCompressedTexSubImage3D");
		glad_glGetCompressedTexImage = (PFNGLGETCOMPRESSEDTEXIMAGEPROC)load(userptr, "glGetCompressedTexImage");
		glad_glLoadTransposeMatrixd = (PFNGLLOADTRANSPOSEMATRIXDPROC)load(userptr, "glLoadTransposeMatrixd");
		glad_glLoadTransposeMatrixf = (PFNGLLOADTRANSPOSEMATRIXFPROC)load(userptr, "glLoadTransposeMatrixf");
		glad_glMultTransposeMatrixd = (PFNGLMULTTRANSPOSEMATRIXDPROC)load(userptr, "glMultTransposeMatrixd");
		glad_glMultTransposeMatrixf = (PFNGLMULTTRANSPOSEMATRIXFPROC)load(userptr, "glMultTransposeMatrixf");
		glad_glMultiTexCoord1d = (PFNGLMULTITEXCOORD1DPROC)load(userptr, "glMultiTexCoord1d");
		glad_glMultiTexCoord1dv = (PFNGLMULTITEXCOORD1DVPROC)load(userptr, "glMultiTexCoord1dv");
		glad_glMultiTexCoord1f = (PFNGLMULTITEXCOORD1FPROC)load(userptr, "glMultiTexCoord1f");
		glad_glMultiTexCoord1fv = (PFNGLMULTITEXCOORD1FVPROC)load(userptr, "glMultiTexCoord1fv");
		glad_glMultiTexCoord1i = (PFNGLMULTITEXCOORD1IPROC)load(userptr, "glMultiTexCoord1i");
		glad_glMultiTexCoord1iv = (PFNGLMULTITEXCOORD1IVPROC)load(userptr, "glMultiTexCoord1iv");
		glad_glMultiTexCoord1s = (PFNGLMULTITEXCOORD1SPROC)load(userptr, "glMultiTexCoord1s");
		glad_glMultiTexCoord1sv = (PFNGLMULTITEXCOORD1SVPROC)load(userptr, "glMultiTexCoord1sv");
		glad_glMultiTexCoord2d = (PFNGLMULTITEXCOORD2DPROC)load(userptr, "glMultiTexCoord2d");
		glad_glMultiTexCoord2dv = (PFNGLMULTITEXCOORD2DVPROC)load(userptr, "glMultiTexCoord2dv");
		glad_glMultiTexCoord2f = (PFNGLMULTITEXCOORD2FPROC)load(userptr, "glMultiTexCoord2f");
		glad_glMultiTexCoord2fv = (PFNGLMULTITEXCOORD2FVPROC)load(userptr, "glMultiTexCoord2fv");
		glad_glMultiTexCoord2i = (PFNGLMULTITEXCOORD2IPROC)load(userptr, "glMultiTexCoord2i");
		glad_glMultiTexCoord2iv = (PFNGLMULTITEXCOORD2IVPROC)load(userptr, "glMultiTexCoord2iv");
		glad_glMultiTexCoord2s = (PFNGLMULTITEXCOORD2SPROC)load(userptr, "glMultiTexCoord2s");
		glad_glMultiTexCoord2sv = (PFNGLMULTITEXCOORD2SVPROC)load(userptr, "glMultiTexCoord2sv");
		glad_glMultiTexCoord3d = (PFNGLMULTITEXCOORD3DPROC)load(userptr, "glMultiTexCoord3d");
		glad_glMultiTexCoord3dv = (PFNGLMULTITEXCOORD3DVPROC)load(userptr, "glMultiTexCoord3dv");
		glad_glMultiTexCoord3f = (PFNGLMULTITEXCOORD3FPROC)load(userptr, "glMultiTexCoord3f");
		glad_glMultiTexCoord3fv = (PFNGLMULTITEXCOORD3FVPROC)load(userptr, "glMultiTexCoord3fv");
		glad_glMultiTexCoord3i = (PFNGLMULTITEXCOORD3IPROC)load(userptr, "glMultiTexCoord3i");
		glad_glMultiTexCoord3iv = (PFNGLMULTITEXCOORD3IVPROC)load(userptr, "glMultiTexCoord3iv");
		glad_glMultiTexCoord3s = (PFNGLMULTITEXCOORD3SPROC)load(userptr, "glMultiTexCoord3s");
		glad_glMultiTexCoord3sv = (PFNGLMULTITEXCOORD3SVPROC)load(userptr, "glMultiTexCoord3sv");
		glad_glMultiTexCoord4d = (PFNGLMULTITEXCOORD4DPROC)load(userptr, "glMultiTexCoord4d");
		glad_glMultiTexCoord4dv = (PFNGLMULTITEXCOORD4DVPROC)load(userptr, "glMultiTexCoord4dv");
		glad_glMultiTexCoord4f = (PFNGLMULTITEXCOORD4FPROC)load(userptr, "glMultiTexCoord4f");
		glad_glMultiTexCoord4fv = (PFNGLMULTITEXCOORD4FVPROC)load(userptr, "glMultiTexCoord4fv");
		glad_glMultiTexCoord4i = (PFNGLMULTITEXCOORD4IPROC)load(userptr, "glMultiTexCoord4i");
		glad_glMultiTexCoord4iv = (PFNGLMULTITEXCOORD4IVPROC)load(userptr, "glMultiTexCoord4iv");
		glad_glMultiTexCoord4s = (PFNGLMULTITEXCOORD4SPROC)load(userptr, "glMultiTexCoord4s");
		glad_glMultiTexCoord4sv = (PFNGLMULTITEXCOORD4SVPROC)load(userptr, "glMultiTexCoord4sv");
		glad_glSampleCoverage = (PFNGLSAMPLECOVERAGEPROC)load(userptr, "glSampleCoverage");
	}
	static void glad_gl_load_GL_VERSION_1_4(GLADuserptrloadfunc load, void* userptr) {
		if(!GLAD_GL_VERSION_1_4) return;
		glad_glBlendColor = (PFNGLBLENDCOLORPROC)load(userptr, "glBlendColor");
		glad_glBlendEquation = (PFNGLBLENDEQUATIONPROC)load(userptr, "glBlendEquation");
		glad_glBlendFuncSeparate = (PFNGLBLENDFUNCSEPARATEPROC)load(userptr, "glBlendFuncSeparate");
		glad_glFogCoordPointer = (PFNGLFOGCOORDPOINTERPROC)load(userptr, "glFogCoordPointer");
		glad_glFogCoordd = (PFNGLFOGCOORDDPROC)load(userptr, "glFogCoordd");
		glad_glFogCoorddv = (PFNGLFOGCOORDDVPROC)load(userptr, "glFogCoorddv");
		glad_glFogCoordf = (PFNGLFOGCOORDFPROC)load(userptr, "glFogCoordf");
		glad_glFogCoordfv = (PFNGLFOGCOORDFVPROC)load(userptr, "glFogCoordfv");
		glad_glMultiDrawArrays = (PFNGLMULTIDRAWARRAYSPROC)load(userptr, "glMultiDrawArrays");
		glad_glMultiDrawElements = (PFNGLMULTIDRAWELEMENTSPROC)load(userptr, "glMultiDrawElements");
		glad_glPointParameterf = (PFNGLPOINTPARAMETERFPROC)load(userptr, "glPointParameterf");
		glad_glPointParameterfv = (PFNGLPOINTPARAMETERFVPROC)load(userptr, "glPointParameterfv");
		glad_glPointParameteri = (PFNGLPOINTPARAMETERIPROC)load(userptr, "glPointParameteri");
		glad_glPointParameteriv = (PFNGLPOINTPARAMETERIVPROC)load(userptr, "glPointParameteriv");
		glad_glSecondaryColor3b = (PFNGLSECONDARYCOLOR3BPROC)load(userptr, "glSecondaryColor3b");
		glad_glSecondaryColor3bv = (PFNGLSECONDARYCOLOR3BVPROC)load(userptr, "glSecondaryColor3bv");
		glad_glSecondaryColor3d = (PFNGLSECONDARYCOLOR3DPROC)load(userptr, "glSecondaryColor3d");
		glad_glSecondaryColor3dv = (PFNGLSECONDARYCOLOR3DVPROC)load(userptr, "glSecondaryColor3dv");
		glad_glSecondaryColor3f = (PFNGLSECONDARYCOLOR3FPROC)load(userptr, "glSecondaryColor3f");
		glad_glSecondaryColor3fv = (PFNGLSECONDARYCOLOR3FVPROC)load(userptr, "glSecondaryColor3fv");
		glad_glSecondaryColor3i = (PFNGLSECONDARYCOLOR3IPROC)load(userptr, "glSecondaryColor3i");
		glad_glSecondaryColor3iv = (PFNGLSECONDARYCOLOR3IVPROC)load(userptr, "glSecondaryColor3iv");
		glad_glSecondaryColor3s = (PFNGLSECONDARYCOLOR3SPROC)load(userptr, "glSecondaryColor3s");
		glad_glSecondaryColor3sv = (PFNGLSECONDARYCOLOR3SVPROC)load(userptr, "glSecondaryColor3sv");
		glad_glSecondaryColor3ub = (PFNGLSECONDARYCOLOR3UBPROC)load(userptr, "glSecondaryColor3ub");
		glad_glSecondaryColor3ubv = (PFNGLSECONDARYCOLOR3UBVPROC)load(userptr, "glSecondaryColor3ubv");
		glad_glSecondaryColor3ui = (PFNGLSECONDARYCOLOR3UIPROC)load(userptr, "glSecondaryColor3ui");
		glad_glSecondaryColor3uiv = (PFNGLSECONDARYCOLOR3UIVPROC)load(userptr, "glSecondaryColor3uiv");
		glad_glSecondaryColor3us = (PFNGLSECONDARYCOLOR3USPROC)load(userptr, "glSecondaryColor3us");
		glad_glSecondaryColor3usv = (PFNGLSECONDARYCOLOR3USVPROC)load(userptr, "glSecondaryColor3usv");
		glad_glSecondaryColorPointer = (PFNGLSECONDARYCOLORPOINTERPROC)load(userptr, "glSecondaryColorPointer");
		glad_glWindowPos2d = (PFNGLWINDOWPOS2DPROC)load(userptr, "glWindowPos2d");
		glad_glWindowPos2dv = (PFNGLWINDOWPOS2DVPROC)load(userptr, "glWindowPos2dv");
		glad_glWindowPos2f = (PFNGLWINDOWPOS2FPROC)load(userptr, "glWindowPos2f");
		glad_glWindowPos2fv = (PFNGLWINDOWPOS2FVPROC)load(userptr, "glWindowPos2fv");
		glad_glWindowPos2i = (PFNGLWINDOWPOS2IPROC)load(userptr, "glWindowPos2i");
		glad_glWindowPos2iv = (PFNGLWINDOWPOS2IVPROC)load(userptr, "glWindowPos2iv");
		glad_glWindowPos2s = (PFNGLWINDOWPOS2SPROC)load(userptr, "glWindowPos2s");
		glad_glWindowPos2sv = (PFNGLWINDOWPOS2SVPROC)load(userptr, "glWindowPos2sv");
		glad_glWindowPos3d = (PFNGLWINDOWPOS3DPROC)load(userptr, "glWindowPos3d");
		glad_glWindowPos3dv = (PFNGLWINDOWPOS3DVPROC)load(userptr, "glWindowPos3dv");
		glad_glWindowPos3f = (PFNGLWINDOWPOS3FPROC)load(userptr, "glWindowPos3f");
		glad_glWindowPos3fv = (PFNGLWINDOWPOS3FVPROC)load(userptr, "glWindowPos3fv");
		glad_glWindowPos3i = (PFNGLWINDOWPOS3IPROC)load(userptr, "glWindowPos3i");
		glad_glWindowPos3iv = (PFNGLWINDOWPOS3IVPROC)load(userptr, "glWindowPos3iv");
		glad_glWindowPos3s = (PFNGLWINDOWPOS3SPROC)load(userptr, "glWindowPos3s");
		glad_glWindowPos3sv = (PFNGLWINDOWPOS3SVPROC)load(userptr, "glWindowPos3sv");
	}
	static void glad_gl_load_GL_VERSION_1_5(GLADuserptrloadfunc load, void* userptr) {
		if(!GLAD_GL_VERSION_1_5) return;
		glad_glBeginQuery = (PFNGLBEGINQUERYPROC)load(userptr, "glBeginQuery");
		glad_glBindBuffer = (PFNGLBINDBUFFERPROC)load(userptr, "glBindBuffer");
		glad_glBufferData = (PFNGLBUFFERDATAPROC)load(userptr, "glBufferData");
		glad_glBufferSubData = (PFNGLBUFFERSUBDATAPROC)load(userptr, "glBufferSubData");
		glad_glDeleteBuffers = (PFNGLDELETEBUFFERSPROC)load(userptr, "glDeleteBuffers");
		glad_glDeleteQueries = (PFNGLDELETEQUERIESPROC)load(userptr, "glDeleteQueries");
		glad_glEndQuery = (PFNGLENDQUERYPROC)load(userptr, "glEndQuery");
		glad_glGenBuffers = (PFNGLGENBUFFERSPROC)load(userptr, "glGenBuffers");
		glad_glGenQueries = (PFNGLGENQUERIESPROC)load(userptr, "glGenQueries");
		glad_glGetBufferParameteriv = (PFNGLGETBUFFERPARAMETERIVPROC)load(userptr, "glGetBufferParameteriv");
		glad_glGetBufferPointerv = (PFNGLGETBUFFERPOINTERVPROC)load(userptr, "glGetBufferPointerv");
		glad_glGetBufferSubData = (PFNGLGETBUFFERSUBDATAPROC)load(userptr, "glGetBufferSubData");
		glad_glGetQueryObjectiv = (PFNGLGETQUERYOBJECTIVPROC)load(userptr, "glGetQueryObjectiv");
		glad_glGetQueryObjectuiv = (PFNGLGETQUERYOBJECTUIVPROC)load(userptr, "glGetQueryObjectuiv");
		glad_glGetQueryiv = (PFNGLGETQUERYIVPROC)load(userptr, "glGetQueryiv");
		glad_glIsBuffer = (PFNGLISBUFFERPROC)load(userptr, "glIsBuffer");
		glad_glIsQuery = (PFNGLISQUERYPROC)load(userptr, "glIsQuery");
		glad_glMapBuffer = (PFNGLMAPBUFFERPROC)load(userptr, "glMapBuffer");
		glad_glUnmapBuffer = (PFNGLUNMAPBUFFERPROC)load(userptr, "glUnmapBuffer");
	}
	static void glad_gl_load_GL_VERSION_2_0(GLADuserptrloadfunc load, void* userptr) {
		if(!GLAD_GL_VERSION_2_0) return;
		glad_glAttachShader = (PFNGLATTACHSHADERPROC)load(userptr, "glAttachShader");
		glad_glBindAttribLocation = (PFNGLBINDATTRIBLOCATIONPROC)load(userptr, "glBindAttribLocation");
		glad_glBlendEquationSeparate = (PFNGLBLENDEQUATIONSEPARATEPROC)load(userptr, "glBlendEquationSeparate");
		glad_glCompileShader = (PFNGLCOMPILESHADERPROC)load(userptr, "glCompileShader");
		glad_glCreateProgram = (PFNGLCREATEPROGRAMPROC)load(userptr, "glCreateProgram");
		glad_glCreateShader = (PFNGLCREATESHADERPROC)load(userptr, "glCreateShader");
		glad_glDeleteProgram = (PFNGLDELETEPROGRAMPROC)load(userptr, "glDeleteProgram");
		glad_glDeleteShader = (PFNGLDELETESHADERPROC)load(userptr, "glDeleteShader");
		glad_glDetachShader = (PFNGLDETACHSHADERPROC)load(userptr, "glDetachShader");
		glad_glDisableVertexAttribArray = (PFNGLDISABLEVERTEXATTRIBARRAYPROC)load(userptr, "glDisableVertexAttribArray");
		glad_glDrawBuffers = (PFNGLDRAWBUFFERSPROC)load(userptr, "glDrawBuffers");
		glad_glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC)load(userptr, "glEnableVertexAttribArray");
		glad_glGetActiveAttrib = (PFNGLGETACTIVEATTRIBPROC)load(userptr, "glGetActiveAttrib");
		glad_glGetActiveUniform = (PFNGLGETACTIVEUNIFORMPROC)load(userptr, "glGetActiveUniform");
		glad_glGetAttachedShaders = (PFNGLGETATTACHEDSHADERSPROC)load(userptr, "glGetAttachedShaders");
		glad_glGetAttribLocation = (PFNGLGETATTRIBLOCATIONPROC)load(userptr, "glGetAttribLocation");
		glad_glGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC)load(userptr, "glGetProgramInfoLog");
		glad_glGetProgramiv = (PFNGLGETPROGRAMIVPROC)load(userptr, "glGetProgramiv");
		glad_glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)load(userptr, "glGetShaderInfoLog");
		glad_glGetShaderSource = (PFNGLGETSHADERSOURCEPROC)load(userptr, "glGetShaderSource");
		glad_glGetShaderiv = (PFNGLGETSHADERIVPROC)load(userptr, "glGetShaderiv");
		glad_glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC)load(userptr, "glGetUniformLocation");
		glad_glGetUniformfv = (PFNGLGETUNIFORMFVPROC)load(userptr, "glGetUniformfv");
		glad_glGetUniformiv = (PFNGLGETUNIFORMIVPROC)load(userptr, "glGetUniformiv");
		glad_glGetVertexAttribPointerv = (PFNGLGETVERTEXATTRIBPOINTERVPROC)load(userptr, "glGetVertexAttribPointerv");
		glad_glGetVertexAttribdv = (PFNGLGETVERTEXATTRIBDVPROC)load(userptr, "glGetVertexAttribdv");
		glad_glGetVertexAttribfv = (PFNGLGETVERTEXATTRIBFVPROC)load(userptr, "glGetVertexAttribfv");
		glad_glGetVertexAttribiv = (PFNGLGETVERTEXATTRIBIVPROC)load(userptr, "glGetVertexAttribiv");
		glad_glIsProgram = (PFNGLISPROGRAMPROC)load(userptr, "glIsProgram");
		glad_glIsShader = (PFNGLISSHADERPROC)load(userptr, "glIsShader");
		glad_glLinkProgram = (PFNGLLINKPROGRAMPROC)load(userptr, "glLinkProgram");
		glad_glShaderSource = (PFNGLSHADERSOURCEPROC)load(userptr, "glShaderSource");
		glad_glStencilFuncSeparate = (PFNGLSTENCILFUNCSEPARATEPROC)load(userptr, "glStencilFuncSeparate");
		glad_glStencilMaskSeparate = (PFNGLSTENCILMASKSEPARATEPROC)load(userptr, "glStencilMaskSeparate");
		glad_glStencilOpSeparate = (PFNGLSTENCILOPSEPARATEPROC)load(userptr, "glStencilOpSeparate");
		glad_glUniform1f = (PFNGLUNIFORM1FPROC)load(userptr, "glUniform1f");
		glad_glUniform1fv = (PFNGLUNIFORM1FVPROC)load(userptr, "glUniform1fv");
		glad_glUniform1i = (PFNGLUNIFORM1IPROC)load(userptr, "glUniform1i");
		glad_glUniform1iv = (PFNGLUNIFORM1IVPROC)load(userptr, "glUniform1iv");
		glad_glUniform2f = (PFNGLUNIFORM2FPROC)load(userptr, "glUniform2f");
		glad_glUniform2fv = (PFNGLUNIFORM2FVPROC)load(userptr, "glUniform2fv");
		glad_glUniform2i = (PFNGLUNIFORM2IPROC)load(userptr, "glUniform2i");
		glad_glUniform2iv = (PFNGLUNIFORM2IVPROC)load(userptr, "glUniform2iv");
		glad_glUniform3f = (PFNGLUNIFORM3FPROC)load(userptr, "glUniform3f");
		glad_glUniform3fv = (PFNGLUNIFORM3FVPROC)load(userptr, "glUniform3fv");
		glad_glUniform3i = (PFNGLUNIFORM3IPROC)load(userptr, "glUniform3i");
		glad_glUniform3iv = (PFNGLUNIFORM3IVPROC)load(userptr, "glUniform3iv");
		glad_glUniform4f = (PFNGLUNIFORM4FPROC)load(userptr, "glUniform4f");
		glad_glUniform4fv = (PFNGLUNIFORM4FVPROC)load(userptr, "glUniform4fv");
		glad_glUniform4i = (PFNGLUNIFORM4IPROC)load(userptr, "glUniform4i");
		glad_glUniform4iv = (PFNGLUNIFORM4IVPROC)load(userptr, "glUniform4iv");
		glad_glUniformMatrix2fv = (PFNGLUNIFORMMATRIX2FVPROC)load(userptr, "glUniformMatrix2fv");
		glad_glUniformMatrix3fv = (PFNGLUNIFORMMATRIX3FVPROC)load(userptr, "glUniformMatrix3fv");
		glad_glUniformMatrix4fv = (PFNGLUNIFORMMATRIX4FVPROC)load(userptr, "glUniformMatrix4fv");
		glad_glUseProgram = (PFNGLUSEPROGRAMPROC)load(userptr, "glUseProgram");
		glad_glValidateProgram = (PFNGLVALIDATEPROGRAMPROC)load(userptr, "glValidateProgram");
		glad_glVertexAttrib1d = (PFNGLVERTEXATTRIB1DPROC)load(userptr, "glVertexAttrib1d");
		glad_glVertexAttrib1dv = (PFNGLVERTEXATTRIB1DVPROC)load(userptr, "glVertexAttrib1dv");
		glad_glVertexAttrib1f = (PFNGLVERTEXATTRIB1FPROC)load(userptr, "glVertexAttrib1f");
		glad_glVertexAttrib1fv = (PFNGLVERTEXATTRIB1FVPROC)load(userptr, "glVertexAttrib1fv");
		glad_glVertexAttrib1s = (PFNGLVERTEXATTRIB1SPROC)load(userptr, "glVertexAttrib1s");
		glad_glVertexAttrib1sv = (PFNGLVERTEXATTRIB1SVPROC)load(userptr, "glVertexAttrib1sv");
		glad_glVertexAttrib2d = (PFNGLVERTEXATTRIB2DPROC)load(userptr, "glVertexAttrib2d");
		glad_glVertexAttrib2dv = (PFNGLVERTEXATTRIB2DVPROC)load(userptr, "glVertexAttrib2dv");
		glad_glVertexAttrib2f = (PFNGLVERTEXATTRIB2FPROC)load(userptr, "glVertexAttrib2f");
		glad_glVertexAttrib2fv = (PFNGLVERTEXATTRIB2FVPROC)load(userptr, "glVertexAttrib2fv");
		glad_glVertexAttrib2s = (PFNGLVERTEXATTRIB2SPROC)load(userptr, "glVertexAttrib2s");
		glad_glVertexAttrib2sv = (PFNGLVERTEXATTRIB2SVPROC)load(userptr, "glVertexAttrib2sv");
		glad_glVertexAttrib3d = (PFNGLVERTEXATTRIB3DPROC)load(userptr, "glVertexAttrib3d");
		glad_glVertexAttrib3dv = (PFNGLVERTEXATTRIB3DVPROC)load(userptr, "glVertexAttrib3dv");
		glad_glVertexAttrib3f = (PFNGLVERTEXATTRIB3FPROC)load(userptr, "glVertexAttrib3f");
		glad_glVertexAttrib3fv = (PFNGLVERTEXATTRIB3FVPROC)load(userptr, "glVertexAttrib3fv");
		glad_glVertexAttrib3s = (PFNGLVERTEXATTRIB3SPROC)load(userptr, "glVertexAttrib3s");
		glad_glVertexAttrib3sv = (PFNGLVERTEXATTRIB3SVPROC)load(userptr, "glVertexAttrib3sv");
		glad_glVertexAttrib4Nbv = (PFNGLVERTEXATTRIB4NBVPROC)load(userptr, "glVertexAttrib4Nbv");
		glad_glVertexAttrib4Niv = (PFNGLVERTEXATTRIB4NIVPROC)load(userptr, "glVertexAttrib4Niv");
		glad_glVertexAttrib4Nsv = (PFNGLVERTEXATTRIB4NSVPROC)load(userptr, "glVertexAttrib4Nsv");
		glad_glVertexAttrib4Nub = (PFNGLVERTEXATTRIB4NUBPROC)load(userptr, "glVertexAttrib4Nub");
		glad_glVertexAttrib4Nubv = (PFNGLVERTEXATTRIB4NUBVPROC)load(userptr, "glVertexAttrib4Nubv");
		glad_glVertexAttrib4Nuiv = (PFNGLVERTEXATTRIB4NUIVPROC)load(userptr, "glVertexAttrib4Nuiv");
		glad_glVertexAttrib4Nusv = (PFNGLVERTEXATTRIB4NUSVPROC)load(userptr, "glVertexAttrib4Nusv");
		glad_glVertexAttrib4bv = (PFNGLVERTEXATTRIB4BVPROC)load(userptr, "glVertexAttrib4bv");
		glad_glVertexAttrib4d = (PFNGLVERTEXATTRIB4DPROC)load(userptr, "glVertexAttrib4d");
		glad_glVertexAttrib4dv = (PFNGLVERTEXATTRIB4DVPROC)load(userptr, "glVertexAttrib4dv");
		glad_glVertexAttrib4f = (PFNGLVERTEXATTRIB4FPROC)load(userptr, "glVertexAttrib4f");
		glad_glVertexAttrib4fv = (PFNGLVERTEXATTRIB4FVPROC)load(userptr, "glVertexAttrib4fv");
		glad_glVertexAttrib4iv = (PFNGLVERTEXATTRIB4IVPROC)load(userptr, "glVertexAttrib4iv");
		glad_glVertexAttrib4s = (PFNGLVERTEXATTRIB4SPROC)load(userptr, "glVertexAttrib4s");
		glad_glVertexAttrib4sv = (PFNGLVERTEXATTRIB4SVPROC)load(userptr, "glVertexAttrib4sv");
		glad_glVertexAttrib4ubv = (PFNGLVERTEXATTRIB4UBVPROC)load(userptr, "glVertexAttrib4ubv");
		glad_glVertexAttrib4uiv = (PFNGLVERTEXATTRIB4UIVPROC)load(userptr, "glVertexAttrib4uiv");
		glad_glVertexAttrib4usv = (PFNGLVERTEXATTRIB4USVPROC)load(userptr, "glVertexAttrib4usv");
		glad_glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC)load(userptr, "glVertexAttribPointer");
	}
	static void glad_gl_load_GL_VERSION_2_1(GLADuserptrloadfunc load, void* userptr) {
		if(!GLAD_GL_VERSION_2_1) return;
		glad_glUniformMatrix2x3fv = (PFNGLUNIFORMMATRIX2X3FVPROC)load(userptr, "glUniformMatrix2x3fv");
		glad_glUniformMatrix2x4fv = (PFNGLUNIFORMMATRIX2X4FVPROC)load(userptr, "glUniformMatrix2x4fv");
		glad_glUniformMatrix3x2fv = (PFNGLUNIFORMMATRIX3X2FVPROC)load(userptr, "glUniformMatrix3x2fv");
		glad_glUniformMatrix3x4fv = (PFNGLUNIFORMMATRIX3X4FVPROC)load(userptr, "glUniformMatrix3x4fv");
		glad_glUniformMatrix4x2fv = (PFNGLUNIFORMMATRIX4X2FVPROC)load(userptr, "glUniformMatrix4x2fv");
		glad_glUniformMatrix4x3fv = (PFNGLUNIFORMMATRIX4X3FVPROC)load(userptr, "glUniformMatrix4x3fv");
	}
	static void glad_gl_load_GL_VERSION_3_0(GLADuserptrloadfunc load, void* userptr) {
		if(!GLAD_GL_VERSION_3_0) return;
		glad_glBeginConditionalRender = (PFNGLBEGINCONDITIONALRENDERPROC)load(userptr, "glBeginConditionalRender");
		glad_glBeginTransformFeedback = (PFNGLBEGINTRANSFORMFEEDBACKPROC)load(userptr, "glBeginTransformFeedback");
		glad_glBindBufferBase = (PFNGLBINDBUFFERBASEPROC)load(userptr, "glBindBufferBase");
		glad_glBindBufferRange = (PFNGLBINDBUFFERRANGEPROC)load(userptr, "glBindBufferRange");
		glad_glBindFragDataLocation = (PFNGLBINDFRAGDATALOCATIONPROC)load(userptr, "glBindFragDataLocation");
		glad_glBindFramebuffer = (PFNGLBINDFRAMEBUFFERPROC)load(userptr, "glBindFramebuffer");
		glad_glBindRenderbuffer = (PFNGLBINDRENDERBUFFERPROC)load(userptr, "glBindRenderbuffer");
		glad_glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC)load(userptr, "glBindVertexArray");
		glad_glBlitFramebuffer = (PFNGLBLITFRAMEBUFFERPROC)load(userptr, "glBlitFramebuffer");
		glad_glCheckFramebufferStatus = (PFNGLCHECKFRAMEBUFFERSTATUSPROC)load(userptr, "glCheckFramebufferStatus");
		glad_glClampColor = (PFNGLCLAMPCOLORPROC)load(userptr, "glClampColor");
		glad_glClearBufferfi = (PFNGLCLEARBUFFERFIPROC)load(userptr, "glClearBufferfi");
		glad_glClearBufferfv = (PFNGLCLEARBUFFERFVPROC)load(userptr, "glClearBufferfv");
		glad_glClearBufferiv = (PFNGLCLEARBUFFERIVPROC)load(userptr, "glClearBufferiv");
		glad_glClearBufferuiv = (PFNGLCLEARBUFFERUIVPROC)load(userptr, "glClearBufferuiv");
		glad_glColorMaski = (PFNGLCOLORMASKIPROC)load(userptr, "glColorMaski");
		glad_glDeleteFramebuffers = (PFNGLDELETEFRAMEBUFFERSPROC)load(userptr, "glDeleteFramebuffers");
		glad_glDeleteRenderbuffers = (PFNGLDELETERENDERBUFFERSPROC)load(userptr, "glDeleteRenderbuffers");
		glad_glDeleteVertexArrays = (PFNGLDELETEVERTEXARRAYSPROC)load(userptr, "glDeleteVertexArrays");
		glad_glDisablei = (PFNGLDISABLEIPROC)load(userptr, "glDisablei");
		glad_glEnablei = (PFNGLENABLEIPROC)load(userptr, "glEnablei");
		glad_glEndConditionalRender = (PFNGLENDCONDITIONALRENDERPROC)load(userptr, "glEndConditionalRender");
		glad_glEndTransformFeedback = (PFNGLENDTRANSFORMFEEDBACKPROC)load(userptr, "glEndTransformFeedback");
		glad_glFlushMappedBufferRange = (PFNGLFLUSHMAPPEDBUFFERRANGEPROC)load(userptr, "glFlushMappedBufferRange");
		glad_glFramebufferRenderbuffer = (PFNGLFRAMEBUFFERRENDERBUFFERPROC)load(userptr, "glFramebufferRenderbuffer");
		glad_glFramebufferTexture1D = (PFNGLFRAMEBUFFERTEXTURE1DPROC)load(userptr, "glFramebufferTexture1D");
		glad_glFramebufferTexture2D = (PFNGLFRAMEBUFFERTEXTURE2DPROC)load(userptr, "glFramebufferTexture2D");
		glad_glFramebufferTexture3D = (PFNGLFRAMEBUFFERTEXTURE3DPROC)load(userptr, "glFramebufferTexture3D");
		glad_glFramebufferTextureLayer = (PFNGLFRAMEBUFFERTEXTURELAYERPROC)load(userptr, "glFramebufferTextureLayer");
		glad_glGenFramebuffers = (PFNGLGENFRAMEBUFFERSPROC)load(userptr, "glGenFramebuffers");
		glad_glGenRenderbuffers = (PFNGLGENRENDERBUFFERSPROC)load(userptr, "glGenRenderbuffers");
		glad_glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC)load(userptr, "glGenVertexArrays");
		glad_glGenerateMipmap = (PFNGLGENERATEMIPMAPPROC)load(userptr, "glGenerateMipmap");
		glad_glGetBooleani_v = (PFNGLGETBOOLEANI_VPROC)load(userptr, "glGetBooleani_v");
		glad_glGetFragDataLocation = (PFNGLGETFRAGDATALOCATIONPROC)load(userptr, "glGetFragDataLocation");
		glad_glGetFramebufferAttachmentParameteriv = (PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC)load(userptr, "glGetFramebufferAttachmentParameteriv");
		glad_glGetIntegeri_v = (PFNGLGETINTEGERI_VPROC)load(userptr, "glGetIntegeri_v");
		glad_glGetRenderbufferParameteriv = (PFNGLGETRENDERBUFFERPARAMETERIVPROC)load(userptr, "glGetRenderbufferParameteriv");
		glad_glGetStringi = (PFNGLGETSTRINGIPROC)load(userptr, "glGetStringi");
		glad_glGetTexParameterIiv = (PFNGLGETTEXPARAMETERIIVPROC)load(userptr, "glGetTexParameterIiv");
		glad_glGetTexParameterIuiv = (PFNGLGETTEXPARAMETERIUIVPROC)load(userptr, "glGetTexParameterIuiv");
		glad_glGetTransformFeedbackVarying = (PFNGLGETTRANSFORMFEEDBACKVARYINGPROC)load(userptr, "glGetTransformFeedbackVarying");
		glad_glGetUniformuiv = (PFNGLGETUNIFORMUIVPROC)load(userptr, "glGetUniformuiv");
		glad_glGetVertexAttribIiv = (PFNGLGETVERTEXATTRIBIIVPROC)load(userptr, "glGetVertexAttribIiv");
		glad_glGetVertexAttribIuiv = (PFNGLGETVERTEXATTRIBIUIVPROC)load(userptr, "glGetVertexAttribIuiv");
		glad_glIsEnabledi = (PFNGLISENABLEDIPROC)load(userptr, "glIsEnabledi");
		glad_glIsFramebuffer = (PFNGLISFRAMEBUFFERPROC)load(userptr, "glIsFramebuffer");
		glad_glIsRenderbuffer = (PFNGLISRENDERBUFFERPROC)load(userptr, "glIsRenderbuffer");
		glad_glIsVertexArray = (PFNGLISVERTEXARRAYPROC)load(userptr, "glIsVertexArray");
		glad_glMapBufferRange = (PFNGLMAPBUFFERRANGEPROC)load(userptr, "glMapBufferRange");
		glad_glRenderbufferStorage = (PFNGLRENDERBUFFERSTORAGEPROC)load(userptr, "glRenderbufferStorage");
		glad_glRenderbufferStorageMultisample = (PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC)load(userptr, "glRenderbufferStorageMultisample");
		glad_glTexParameterIiv = (PFNGLTEXPARAMETERIIVPROC)load(userptr, "glTexParameterIiv");
		glad_glTexParameterIuiv = (PFNGLTEXPARAMETERIUIVPROC)load(userptr, "glTexParameterIuiv");
		glad_glTransformFeedbackVaryings = (PFNGLTRANSFORMFEEDBACKVARYINGSPROC)load(userptr, "glTransformFeedbackVaryings");
		glad_glUniform1ui = (PFNGLUNIFORM1UIPROC)load(userptr, "glUniform1ui");
		glad_glUniform1uiv = (PFNGLUNIFORM1UIVPROC)load(userptr, "glUniform1uiv");
		glad_glUniform2ui = (PFNGLUNIFORM2UIPROC)load(userptr, "glUniform2ui");
		glad_glUniform2uiv = (PFNGLUNIFORM2UIVPROC)load(userptr, "glUniform2uiv");
		glad_glUniform3ui = (PFNGLUNIFORM3UIPROC)load(userptr, "glUniform3ui");
		glad_glUniform3uiv = (PFNGLUNIFORM3UIVPROC)load(userptr, "glUniform3uiv");
		glad_glUniform4ui = (PFNGLUNIFORM4UIPROC)load(userptr, "glUniform4ui");
		glad_glUniform4uiv = (PFNGLUNIFORM4UIVPROC)load(userptr, "glUniform4uiv");
		glad_glVertexAttribI1i = (PFNGLVERTEXATTRIBI1IPROC)load(userptr, "glVertexAttribI1i");
		glad_glVertexAttribI1iv = (PFNGLVERTEXATTRIBI1IVPROC)load(userptr, "glVertexAttribI1iv");
		glad_glVertexAttribI1ui = (PFNGLVERTEXATTRIBI1UIPROC)load(userptr, "glVertexAttribI1ui");
		glad_glVertexAttribI1uiv = (PFNGLVERTEXATTRIBI1UIVPROC)load(userptr, "glVertexAttribI1uiv");
		glad_glVertexAttribI2i = (PFNGLVERTEXATTRIBI2IPROC)load(userptr, "glVertexAttribI2i");
		glad_glVertexAttribI2iv = (PFNGLVERTEXATTRIBI2IVPROC)load(userptr, "glVertexAttribI2iv");
		glad_glVertexAttribI2ui = (PFNGLVERTEXATTRIBI2UIPROC)load(userptr, "glVertexAttribI2ui");
		glad_glVertexAttribI2uiv = (PFNGLVERTEXATTRIBI2UIVPROC)load(userptr, "glVertexAttribI2uiv");
		glad_glVertexAttribI3i = (PFNGLVERTEXATTRIBI3IPROC)load(userptr, "glVertexAttribI3i");
		glad_glVertexAttribI3iv = (PFNGLVERTEXATTRIBI3IVPROC)load(userptr, "glVertexAttribI3iv");
		glad_glVertexAttribI3ui = (PFNGLVERTEXATTRIBI3UIPROC)load(userptr, "glVertexAttribI3ui");
		glad_glVertexAttribI3uiv = (PFNGLVERTEXATTRIBI3UIVPROC)load(userptr, "glVertexAttribI3uiv");
		glad_glVertexAttribI4bv = (PFNGLVERTEXATTRIBI4BVPROC)load(userptr, "glVertexAttribI4bv");
		glad_glVertexAttribI4i = (PFNGLVERTEXATTRIBI4IPROC)load(userptr, "glVertexAttribI4i");
		glad_glVertexAttribI4iv = (PFNGLVERTEXATTRIBI4IVPROC)load(userptr, "glVertexAttribI4iv");
		glad_glVertexAttribI4sv = (PFNGLVERTEXATTRIBI4SVPROC)load(userptr, "glVertexAttribI4sv");
		glad_glVertexAttribI4ubv = (PFNGLVERTEXATTRIBI4UBVPROC)load(userptr, "glVertexAttribI4ubv");
		glad_glVertexAttribI4ui = (PFNGLVERTEXATTRIBI4UIPROC)load(userptr, "glVertexAttribI4ui");
		glad_glVertexAttribI4uiv = (PFNGLVERTEXATTRIBI4UIVPROC)load(userptr, "glVertexAttribI4uiv");
		glad_glVertexAttribI4usv = (PFNGLVERTEXATTRIBI4USVPROC)load(userptr, "glVertexAttribI4usv");
		glad_glVertexAttribIPointer = (PFNGLVERTEXATTRIBIPOINTERPROC)load(userptr, "glVertexAttribIPointer");
	}
	static void glad_gl_load_GL_VERSION_3_1(GLADuserptrloadfunc load, void* userptr) {
		if(!GLAD_GL_VERSION_3_1) return;
		glad_glBindBufferBase = (PFNGLBINDBUFFERBASEPROC)load(userptr, "glBindBufferBase");
		glad_glBindBufferRange = (PFNGLBINDBUFFERRANGEPROC)load(userptr, "glBindBufferRange");
		glad_glCopyBufferSubData = (PFNGLCOPYBUFFERSUBDATAPROC)load(userptr, "glCopyBufferSubData");
		glad_glDrawArraysInstanced = (PFNGLDRAWARRAYSINSTANCEDPROC)load(userptr, "glDrawArraysInstanced");
		glad_glDrawElementsInstanced = (PFNGLDRAWELEMENTSINSTANCEDPROC)load(userptr, "glDrawElementsInstanced");
		glad_glGetActiveUniformBlockName = (PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC)load(userptr, "glGetActiveUniformBlockName");
		glad_glGetActiveUniformBlockiv = (PFNGLGETACTIVEUNIFORMBLOCKIVPROC)load(userptr, "glGetActiveUniformBlockiv");
		glad_glGetActiveUniformName = (PFNGLGETACTIVEUNIFORMNAMEPROC)load(userptr, "glGetActiveUniformName");
		glad_glGetActiveUniformsiv = (PFNGLGETACTIVEUNIFORMSIVPROC)load(userptr, "glGetActiveUniformsiv");
		glad_glGetIntegeri_v = (PFNGLGETINTEGERI_VPROC)load(userptr, "glGetIntegeri_v");
		glad_glGetUniformBlockIndex = (PFNGLGETUNIFORMBLOCKINDEXPROC)load(userptr, "glGetUniformBlockIndex");
		glad_glGetUniformIndices = (PFNGLGETUNIFORMINDICESPROC)load(userptr, "glGetUniformIndices");
		glad_glPrimitiveRestartIndex = (PFNGLPRIMITIVERESTARTINDEXPROC)load(userptr, "glPrimitiveRestartIndex");
		glad_glTexBuffer = (PFNGLTEXBUFFERPROC)load(userptr, "glTexBuffer");
		glad_glUniformBlockBinding = (PFNGLUNIFORMBLOCKBINDINGPROC)load(userptr, "glUniformBlockBinding");
	}
	static void glad_gl_load_GL_VERSION_3_2(GLADuserptrloadfunc load, void* userptr) {
		if(!GLAD_GL_VERSION_3_2) return;
		glad_glClientWaitSync = (PFNGLCLIENTWAITSYNCPROC)load(userptr, "glClientWaitSync");
		glad_glDeleteSync = (PFNGLDELETESYNCPROC)load(userptr, "glDeleteSync");
		glad_glDrawElementsBaseVertex = (PFNGLDRAWELEMENTSBASEVERTEXPROC)load(userptr, "glDrawElementsBaseVertex");
		glad_glDrawElementsInstancedBaseVertex = (PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXPROC)load(userptr, "glDrawElementsInstancedBaseVertex");
		glad_glDrawRangeElementsBaseVertex = (PFNGLDRAWRANGEELEMENTSBASEVERTEXPROC)load(userptr, "glDrawRangeElementsBaseVertex");
		glad_glFenceSync = (PFNGLFENCESYNCPROC)load(userptr, "glFenceSync");
		glad_glFramebufferTexture = (PFNGLFRAMEBUFFERTEXTUREPROC)load(userptr, "glFramebufferTexture");
		glad_glGetBufferParameteri64v = (PFNGLGETBUFFERPARAMETERI64VPROC)load(userptr, "glGetBufferParameteri64v");
		glad_glGetInteger64i_v = (PFNGLGETINTEGER64I_VPROC)load(userptr, "glGetInteger64i_v");
		glad_glGetInteger64v = (PFNGLGETINTEGER64VPROC)load(userptr, "glGetInteger64v");
		glad_glGetMultisamplefv = (PFNGLGETMULTISAMPLEFVPROC)load(userptr, "glGetMultisamplefv");
		glad_glGetSynciv = (PFNGLGETSYNCIVPROC)load(userptr, "glGetSynciv");
		glad_glIsSync = (PFNGLISSYNCPROC)load(userptr, "glIsSync");
		glad_glMultiDrawElementsBaseVertex = (PFNGLMULTIDRAWELEMENTSBASEVERTEXPROC)load(userptr, "glMultiDrawElementsBaseVertex");
		glad_glProvokingVertex = (PFNGLPROVOKINGVERTEXPROC)load(userptr, "glProvokingVertex");
		glad_glSampleMaski = (PFNGLSAMPLEMASKIPROC)load(userptr, "glSampleMaski");
		glad_glTexImage2DMultisample = (PFNGLTEXIMAGE2DMULTISAMPLEPROC)load(userptr, "glTexImage2DMultisample");
		glad_glTexImage3DMultisample = (PFNGLTEXIMAGE3DMULTISAMPLEPROC)load(userptr, "glTexImage3DMultisample");
		glad_glWaitSync = (PFNGLWAITSYNCPROC)load(userptr, "glWaitSync");
	}
	static void glad_gl_load_GL_VERSION_3_3(GLADuserptrloadfunc load, void* userptr) {
		if(!GLAD_GL_VERSION_3_3) return;
		glad_glBindFragDataLocationIndexed = (PFNGLBINDFRAGDATALOCATIONINDEXEDPROC)load(userptr, "glBindFragDataLocationIndexed");
		glad_glBindSampler = (PFNGLBINDSAMPLERPROC)load(userptr, "glBindSampler");
		glad_glColorP3ui = (PFNGLCOLORP3UIPROC)load(userptr, "glColorP3ui");
		glad_glColorP3uiv = (PFNGLCOLORP3UIVPROC)load(userptr, "glColorP3uiv");
		glad_glColorP4ui = (PFNGLCOLORP4UIPROC)load(userptr, "glColorP4ui");
		glad_glColorP4uiv = (PFNGLCOLORP4UIVPROC)load(userptr, "glColorP4uiv");
		glad_glDeleteSamplers = (PFNGLDELETESAMPLERSPROC)load(userptr, "glDeleteSamplers");
		glad_glGenSamplers = (PFNGLGENSAMPLERSPROC)load(userptr, "glGenSamplers");
		glad_glGetFragDataIndex = (PFNGLGETFRAGDATAINDEXPROC)load(userptr, "glGetFragDataIndex");
		glad_glGetQueryObjecti64v = (PFNGLGETQUERYOBJECTI64VPROC)load(userptr, "glGetQueryObjecti64v");
		glad_glGetQueryObjectui64v = (PFNGLGETQUERYOBJECTUI64VPROC)load(userptr, "glGetQueryObjectui64v");
		glad_glGetSamplerParameterIiv = (PFNGLGETSAMPLERPARAMETERIIVPROC)load(userptr, "glGetSamplerParameterIiv");
		glad_glGetSamplerParameterIuiv = (PFNGLGETSAMPLERPARAMETERIUIVPROC)load(userptr, "glGetSamplerParameterIuiv");
		glad_glGetSamplerParameterfv = (PFNGLGETSAMPLERPARAMETERFVPROC)load(userptr, "glGetSamplerParameterfv");
		glad_glGetSamplerParameteriv = (PFNGLGETSAMPLERPARAMETERIVPROC)load(userptr, "glGetSamplerParameteriv");
		glad_glIsSampler = (PFNGLISSAMPLERPROC)load(userptr, "glIsSampler");
		glad_glMultiTexCoordP1ui = (PFNGLMULTITEXCOORDP1UIPROC)load(userptr, "glMultiTexCoordP1ui");
		glad_glMultiTexCoordP1uiv = (PFNGLMULTITEXCOORDP1UIVPROC)load(userptr, "glMultiTexCoordP1uiv");
		glad_glMultiTexCoordP2ui = (PFNGLMULTITEXCOORDP2UIPROC)load(userptr, "glMultiTexCoordP2ui");
		glad_glMultiTexCoordP2uiv = (PFNGLMULTITEXCOORDP2UIVPROC)load(userptr, "glMultiTexCoordP2uiv");
		glad_glMultiTexCoordP3ui = (PFNGLMULTITEXCOORDP3UIPROC)load(userptr, "glMultiTexCoordP3ui");
		glad_glMultiTexCoordP3uiv = (PFNGLMULTITEXCOORDP3UIVPROC)load(userptr, "glMultiTexCoordP3uiv");
		glad_glMultiTexCoordP4ui = (PFNGLMULTITEXCOORDP4UIPROC)load(userptr, "glMultiTexCoordP4ui");
		glad_glMultiTexCoordP4uiv = (PFNGLMULTITEXCOORDP4UIVPROC)load(userptr, "glMultiTexCoordP4uiv");
		glad_glNormalP3ui = (PFNGLNORMALP3UIPROC)load(userptr, "glNormalP3ui");
		glad_glNormalP3uiv = (PFNGLNORMALP3UIVPROC)load(userptr, "glNormalP3uiv");
		glad_glQueryCounter = (PFNGLQUERYCOUNTERPROC)load(userptr, "glQueryCounter");
		glad_glSamplerParameterIiv = (PFNGLSAMPLERPARAMETERIIVPROC)load(userptr, "glSamplerParameterIiv");
		glad_glSamplerParameterIuiv = (PFNGLSAMPLERPARAMETERIUIVPROC)load(userptr, "glSamplerParameterIuiv");
		glad_glSamplerParameterf = (PFNGLSAMPLERPARAMETERFPROC)load(userptr, "glSamplerParameterf");
		glad_glSamplerParameterfv = (PFNGLSAMPLERPARAMETERFVPROC)load(userptr, "glSamplerParameterfv");
		glad_glSamplerParameteri = (PFNGLSAMPLERPARAMETERIPROC)load(userptr, "glSamplerParameteri");
		glad_glSamplerParameteriv = (PFNGLSAMPLERPARAMETERIVPROC)load(userptr, "glSamplerParameteriv");
		glad_glSecondaryColorP3ui = (PFNGLSECONDARYCOLORP3UIPROC)load(userptr, "glSecondaryColorP3ui");
		glad_glSecondaryColorP3uiv = (PFNGLSECONDARYCOLORP3UIVPROC)load(userptr, "glSecondaryColorP3uiv");
		glad_glTexCoordP1ui = (PFNGLTEXCOORDP1UIPROC)load(userptr, "glTexCoordP1ui");
		glad_glTexCoordP1uiv = (PFNGLTEXCOORDP1UIVPROC)load(userptr, "glTexCoordP1uiv");
		glad_glTexCoordP2ui = (PFNGLTEXCOORDP2UIPROC)load(userptr, "glTexCoordP2ui");
		glad_glTexCoordP2uiv = (PFNGLTEXCOORDP2UIVPROC)load(userptr, "glTexCoordP2uiv");
		glad_glTexCoordP3ui = (PFNGLTEXCOORDP3UIPROC)load(userptr, "glTexCoordP3ui");
		glad_glTexCoordP3uiv = (PFNGLTEXCOORDP3UIVPROC)load(userptr, "glTexCoordP3uiv");
		glad_glTexCoordP4ui = (PFNGLTEXCOORDP4UIPROC)load(userptr, "glTexCoordP4ui");
		glad_glTexCoordP4uiv = (PFNGLTEXCOORDP4UIVPROC)load(userptr, "glTexCoordP4uiv");
		glad_glVertexAttribDivisor = (PFNGLVERTEXATTRIBDIVISORPROC)load(userptr, "glVertexAttribDivisor");
		glad_glVertexAttribP1ui = (PFNGLVERTEXATTRIBP1UIPROC)load(userptr, "glVertexAttribP1ui");
		glad_glVertexAttribP1uiv = (PFNGLVERTEXATTRIBP1UIVPROC)load(userptr, "glVertexAttribP1uiv");
		glad_glVertexAttribP2ui = (PFNGLVERTEXATTRIBP2UIPROC)load(userptr, "glVertexAttribP2ui");
		glad_glVertexAttribP2uiv = (PFNGLVERTEXATTRIBP2UIVPROC)load(userptr, "glVertexAttribP2uiv");
		glad_glVertexAttribP3ui = (PFNGLVERTEXATTRIBP3UIPROC)load(userptr, "glVertexAttribP3ui");
		glad_glVertexAttribP3uiv = (PFNGLVERTEXATTRIBP3UIVPROC)load(userptr, "glVertexAttribP3uiv");
		glad_glVertexAttribP4ui = (PFNGLVERTEXATTRIBP4UIPROC)load(userptr, "glVertexAttribP4ui");
		glad_glVertexAttribP4uiv = (PFNGLVERTEXATTRIBP4UIVPROC)load(userptr, "glVertexAttribP4uiv");
		glad_glVertexP2ui = (PFNGLVERTEXP2UIPROC)load(userptr, "glVertexP2ui");
		glad_glVertexP2uiv = (PFNGLVERTEXP2UIVPROC)load(userptr, "glVertexP2uiv");
		glad_glVertexP3ui = (PFNGLVERTEXP3UIPROC)load(userptr, "glVertexP3ui");
		glad_glVertexP3uiv = (PFNGLVERTEXP3UIVPROC)load(userptr, "glVertexP3uiv");
		glad_glVertexP4ui = (PFNGLVERTEXP4UIPROC)load(userptr, "glVertexP4ui");
		glad_glVertexP4uiv = (PFNGLVERTEXP4UIVPROC)load(userptr, "glVertexP4uiv");
	}



#if defined(GL_ES_VERSION_3_0) || defined(GL_VERSION_3_0)
#define GLAD_GL_IS_SOME_NEW_VERSION 1
#else
#define GLAD_GL_IS_SOME_NEW_VERSION 0
#endif

	static int glad_gl_get_extensions(int version, const char** out_exts, unsigned int* out_num_exts_i, char*** out_exts_i) {
#if GLAD_GL_IS_SOME_NEW_VERSION
		if(GLAD_VERSION_MAJOR(version) < 3) {
#else
		GLAD_UNUSED(version);
		GLAD_UNUSED(out_num_exts_i);
		GLAD_UNUSED(out_exts_i);
#endif
		if(glad_glGetString == NULL) {
			return 0;
		}
		*out_exts = (const char*)glad_glGetString(GL_EXTENSIONS);
#if GLAD_GL_IS_SOME_NEW_VERSION
		} else {
		unsigned int index = 0;
		unsigned int num_exts_i = 0;
		char** exts_i = NULL;
		if(glad_glGetStringi == NULL || glad_glGetIntegerv == NULL) {
			return 0;
		}
		glad_glGetIntegerv(GL_NUM_EXTENSIONS, (int*)&num_exts_i);
		if(num_exts_i > 0) {
			exts_i = (char**)malloc(num_exts_i * (sizeof * exts_i));
		}
		if(exts_i == NULL) {
			return 0;
		}
		for(index = 0; index < num_exts_i; index++) {
			const char* gl_str_tmp = (const char*)glad_glGetStringi(GL_EXTENSIONS, index);
			size_t len = strlen(gl_str_tmp) + 1;

			char* local_str = (char*)malloc(len * sizeof(char));
			if(local_str != NULL) {
				memcpy(local_str, gl_str_tmp, len * sizeof(char));
			}

			exts_i[index] = local_str;
		}

		*out_num_exts_i = num_exts_i;
		*out_exts_i = exts_i;
	}
#endif
	return 1;
	}
static void glad_gl_free_extensions(char** exts_i, unsigned int num_exts_i) {
	if(exts_i != NULL) {
		unsigned int index;
		for(index = 0; index < num_exts_i; index++) {
			free((void*)(exts_i[index]));
		}
		free((void*)exts_i);
		exts_i = NULL;
	}
}
static int glad_gl_has_extension(int version, const char* exts, unsigned int num_exts_i, char** exts_i, const char* ext) {
	if(GLAD_VERSION_MAJOR(version) < 3 || !GLAD_GL_IS_SOME_NEW_VERSION) {
		const char* extensions;
		const char* loc;
		const char* terminator;
		extensions = exts;
		if(extensions == NULL || ext == NULL) {
			return 0;
		}
		while(1) {
			loc = strstr(extensions, ext);
			if(loc == NULL) {
				return 0;
			}
			terminator = loc + strlen(ext);
			if((loc == extensions || *(loc - 1) == ' ') &&
			   (*terminator == ' ' || *terminator == '\0')) {
				return 1;
			}
			extensions = terminator;
		}
	} else {
		unsigned int index;
		for(index = 0; index < num_exts_i; index++) {
			const char* e = exts_i[index];
			if(strcmp(e, ext) == 0) {
				return 1;
			}
		}
	}
	return 0;
}

static GLADapiproc glad_gl_get_proc_from_userptr(void* userptr, const char* name) {
	return (GLAD_GNUC_EXTENSION(GLADapiproc(*)(const char* name)) userptr)(name);
}

static int glad_gl_find_extensions_gl(int version) {
	const char* exts = NULL;
	unsigned int num_exts_i = 0;
	char** exts_i = NULL;
	if(!glad_gl_get_extensions(version, &exts, &num_exts_i, &exts_i)) return 0;

	GLAD_UNUSED(glad_gl_has_extension);

	glad_gl_free_extensions(exts_i, num_exts_i);

	return 1;
}

static int glad_gl_find_core_gl(void) {
	int i;
	const char* version;
	const char* prefixes[] = {
		"OpenGL ES-CM ",
		"OpenGL ES-CL ",
		"OpenGL ES ",
		"OpenGL SC ",
		NULL
	};
	int major = 0;
	int minor = 0;
	version = (const char*)glad_glGetString(GL_VERSION);
	if(!version) return 0;
	for(i = 0; prefixes[i]; i++) {
		const size_t length = strlen(prefixes[i]);
		if(strncmp(version, prefixes[i], length) == 0) {
			version += length;
			break;
		}
	}

	GLAD_IMPL_UTIL_SSCANF(version, "%d.%d", &major, &minor);

	GLAD_GL_VERSION_1_0 = (major == 1 && minor >= 0) || major > 1;
	GLAD_GL_VERSION_1_1 = (major == 1 && minor >= 1) || major > 1;
	GLAD_GL_VERSION_1_2 = (major == 1 && minor >= 2) || major > 1;
	GLAD_GL_VERSION_1_3 = (major == 1 && minor >= 3) || major > 1;
	GLAD_GL_VERSION_1_4 = (major == 1 && minor >= 4) || major > 1;
	GLAD_GL_VERSION_1_5 = (major == 1 && minor >= 5) || major > 1;
	GLAD_GL_VERSION_2_0 = (major == 2 && minor >= 0) || major > 2;
	GLAD_GL_VERSION_2_1 = (major == 2 && minor >= 1) || major > 2;
	GLAD_GL_VERSION_3_0 = (major == 3 && minor >= 0) || major > 3;
	GLAD_GL_VERSION_3_1 = (major == 3 && minor >= 1) || major > 3;
	GLAD_GL_VERSION_3_2 = (major == 3 && minor >= 2) || major > 3;
	GLAD_GL_VERSION_3_3 = (major == 3 && minor >= 3) || major > 3;

	return GLAD_MAKE_VERSION(major, minor);
}

int gladLoadGLUserPtr(GLADuserptrloadfunc load, void* userptr) {
	int version;

	glad_glGetString = (PFNGLGETSTRINGPROC)load(userptr, "glGetString");
	if(glad_glGetString == NULL) return 0;
	if(glad_glGetString(GL_VERSION) == NULL) return 0;
	version = glad_gl_find_core_gl();

	glad_gl_load_GL_VERSION_1_0(load, userptr);
	glad_gl_load_GL_VERSION_1_1(load, userptr);
	glad_gl_load_GL_VERSION_1_2(load, userptr);
	glad_gl_load_GL_VERSION_1_3(load, userptr);
	glad_gl_load_GL_VERSION_1_4(load, userptr);
	glad_gl_load_GL_VERSION_1_5(load, userptr);
	glad_gl_load_GL_VERSION_2_0(load, userptr);
	glad_gl_load_GL_VERSION_2_1(load, userptr);
	glad_gl_load_GL_VERSION_3_0(load, userptr);
	glad_gl_load_GL_VERSION_3_1(load, userptr);
	glad_gl_load_GL_VERSION_3_2(load, userptr);
	glad_gl_load_GL_VERSION_3_3(load, userptr);

	if(!glad_gl_find_extensions_gl(version)) return 0;



	return version;
}


int gladLoadGL(GLADloadfunc load) {
	return gladLoadGLUserPtr(glad_gl_get_proc_from_userptr, GLAD_GNUC_EXTENSION(void*) load);
}





#ifdef GLAD_GL

#ifndef GLAD_LOADER_LIBRARY_C_
#define GLAD_LOADER_LIBRARY_C_

#include <stddef.h>
#include <stdlib.h>

#if GLAD_PLATFORM_WIN32
#include <windows.h>
#else
#include <dlfcn.h>
#endif


static void* glad_get_dlopen_handle(const char* lib_names[], int length) {
	void* handle = NULL;
	int i;

	for(i = 0; i < length; ++i) {
#if GLAD_PLATFORM_WIN32
#if GLAD_PLATFORM_UWP
		size_t buffer_size = (strlen(lib_names[i]) + 1) * sizeof(WCHAR);
		LPWSTR buffer = (LPWSTR)malloc(buffer_size);
		if(buffer != NULL) {
			int ret = MultiByteToWideChar(CP_ACP, 0, lib_names[i], -1, buffer, buffer_size);
			if(ret != 0) {
				handle = (void*)LoadPackagedLibrary(buffer, 0);
			}
			free((void*)buffer);
		}
#else
		handle = (void*)LoadLibraryA(lib_names[i]);
#endif
#else
		handle = dlopen(lib_names[i], RTLD_LAZY | RTLD_LOCAL);
#endif
		if(handle != NULL) {
			return handle;
		}
	}

	return NULL;
}

static void glad_close_dlopen_handle(void* handle) {
	if(handle != NULL) {
#if GLAD_PLATFORM_WIN32
		FreeLibrary((HMODULE)handle);
#else
		dlclose(handle);
#endif
	}
}

static GLADapiproc glad_dlsym_handle(void* handle, const char* name) {
	if(handle == NULL) {
		return NULL;
	}

#if GLAD_PLATFORM_WIN32
	return (GLADapiproc)GetProcAddress((HMODULE)handle, name);
#else
	return GLAD_GNUC_EXTENSION(GLADapiproc) dlsym(handle, name);
#endif
}

#endif /* GLAD_LOADER_LIBRARY_C_ */

typedef void* (GLAD_API_PTR* GLADglprocaddrfunc)(const char*);
struct _glad_gl_userptr {
	void* handle;
	GLADglprocaddrfunc gl_get_proc_address_ptr;
};

static GLADapiproc glad_gl_get_proc(void* vuserptr, const char* name) {
	struct _glad_gl_userptr userptr = *(struct _glad_gl_userptr*)vuserptr;
	GLADapiproc result = NULL;

	if(userptr.gl_get_proc_address_ptr != NULL) {
		result = GLAD_GNUC_EXTENSION(GLADapiproc) userptr.gl_get_proc_address_ptr(name);
	}
	if(result == NULL) {
		result = glad_dlsym_handle(userptr.handle, name);
	}

	return result;
}

static void* _glad_GL_loader_handle = NULL;

static void* glad_gl_dlopen_handle(void) {
#if GLAD_PLATFORM_APPLE
	static const char* NAMES[] = {
		"../Frameworks/OpenGL.framework/OpenGL",
		"/Library/Frameworks/OpenGL.framework/OpenGL",
		"/System/Library/Frameworks/OpenGL.framework/OpenGL",
		"/System/Library/Frameworks/OpenGL.framework/Versions/Current/OpenGL"
	};
#elif GLAD_PLATFORM_WIN32
	static const char* NAMES[] = { "opengl32.dll" };
#else
	static const char* NAMES[] = {
  #if defined(__CYGWIN__)
		"libGL-1.so",
  #endif
		"libGL.so.1",
		"libGL.so"
	};
#endif

	if(_glad_GL_loader_handle == NULL) {
		_glad_GL_loader_handle = glad_get_dlopen_handle(NAMES, sizeof(NAMES) / sizeof(NAMES[0]));
	}

	return _glad_GL_loader_handle;
}

static struct _glad_gl_userptr glad_gl_build_userptr(void* handle) {
	struct _glad_gl_userptr userptr;

	userptr.handle = handle;
#if GLAD_PLATFORM_APPLE || defined(__HAIKU__)
	userptr.gl_get_proc_address_ptr = NULL;
#elif GLAD_PLATFORM_WIN32
	userptr.gl_get_proc_address_ptr =
		(GLADglprocaddrfunc)glad_dlsym_handle(handle, "wglGetProcAddress");
#else
	userptr.gl_get_proc_address_ptr =
		(GLADglprocaddrfunc)glad_dlsym_handle(handle, "glXGetProcAddressARB");
#endif

	return userptr;
}

int gladLoaderLoadGL(void) {
	int version = 0;
	void* handle;
	int did_load = 0;
	struct _glad_gl_userptr userptr;

	did_load = _glad_GL_loader_handle == NULL;
	handle = glad_gl_dlopen_handle();
	if(handle) {
		userptr = glad_gl_build_userptr(handle);

		version = gladLoadGLUserPtr(glad_gl_get_proc, &userptr);

		if(did_load) {
			gladLoaderUnloadGL();
		}
	}

	return version;
}



void gladLoaderUnloadGL(void) {
	if(_glad_GL_loader_handle != NULL) {
		glad_close_dlopen_handle(_glad_GL_loader_handle);
		_glad_GL_loader_handle = NULL;
	}
}

#endif /* GLAD_GL */

#ifdef __cplusplus
}
#endif

#endif /* GLAD_GL_IMPLEMENTATION */
#pragma endregion

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


#pragma region /* rge::macosx */
//********************************************//
//* MacOS X Platform Class                   *//
//********************************************//
#ifdef SYS_MACOSX
/*
This is just a interface to the macosx platform.
Actual implementation is contained in 'macosx.mm'.
*/
#include "macosx.hpp"
#endif /* SYS_MACOSX */
//********************************************//
//* MacOS X Platform Class                   *//
//********************************************//
#pragma endregion


#define LOG_MISSING_DEP(OP, LIB) rge::log::error("Operation '"#OP"' failed! Dependancy not installed: "#LIB);


namespace rge {


#pragma region /* rge::rect */
//********************************************//
//* Rectangle Struct                         *//
//********************************************//
rect::rect() {
	this->x = 0;
	this->y = 0;
	this->w = 0;
	this->h = 0;
}

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
//* Rectangle Struct                         *//
//********************************************//
#pragma endregion


#pragma region /* rge::vec2 */
//********************************************//
//* Vector2 Struct                           *//
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

vec2 vec2::move_towards(vec2 current, vec2 target, float max_delta) {
	current.x = math::move_towards(current.x, target.x, max_delta);
	current.y = math::move_towards(current.y, target.y, max_delta);
	return current;
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
//* Vector2 Struct                           *//
//********************************************//
#pragma endregion


#pragma region /* rge::vec3 */
//********************************************//
//* Vector3 Struct                           *//
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

vec3 vec3::move_towards(vec3 current, vec3 target, float max_delta) {
	current.x = math::move_towards(current.x, target.x, max_delta);
	current.y = math::move_towards(current.y, target.y, max_delta);
	current.z = math::move_towards(current.z, target.z, max_delta);
	return current;
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
//* Vector3 Struct                           *//
//********************************************//
#pragma endregion


#pragma region /* rge::vec4 */
//********************************************//
//* Vector4 Struct                           *//
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
//* Vector4 Struct                           *//
//********************************************//
#pragma endregion


#pragma region /* rge::quaternion */
//********************************************//
//* Quaternion Struct                        *//
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
//* Quaternion Struct                        *//
//********************************************//
#pragma endregion


#pragma region /* rge::mat4 */
//********************************************//
//* Matrix 4x4 Struct                        *//
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

mat4 mat4::inverse(const mat4& m) {
	float coef_00 = m.m[2][2] * m.m[3][3] - m.m[2][3] * m.m[3][2];
	float coef_02 = m.m[2][1] * m.m[3][3] - m.m[2][3] * m.m[3][1];
	float coef_03 = m.m[2][1] * m.m[3][2] - m.m[2][2] * m.m[3][1];
	float coef_04 = m.m[1][2] * m.m[3][3] - m.m[1][3] * m.m[3][2];
	float coef_06 = m.m[1][1] * m.m[3][3] - m.m[1][3] * m.m[3][1];
	float coef_07 = m.m[1][1] * m.m[3][2] - m.m[1][2] * m.m[3][1];
	float coef_08 = m.m[1][2] * m.m[2][3] - m.m[1][3] * m.m[2][2];
	float coef_10 = m.m[1][1] * m.m[2][3] - m.m[1][3] * m.m[2][1];
	float coef_11 = m.m[1][1] * m.m[2][2] - m.m[1][2] * m.m[2][1];
	float coef_12 = m.m[0][2] * m.m[3][3] - m.m[0][3] * m.m[3][2];
	float coef_14 = m.m[0][1] * m.m[3][3] - m.m[0][3] * m.m[3][1];
	float coef_15 = m.m[0][1] * m.m[3][2] - m.m[0][2] * m.m[3][1];
	float coef_16 = m.m[0][2] * m.m[2][3] - m.m[0][3] * m.m[2][2];
	float coef_18 = m.m[0][1] * m.m[2][3] - m.m[0][3] * m.m[2][1];
	float coef_19 = m.m[0][1] * m.m[2][2] - m.m[0][2] * m.m[2][1];
	float coef_20 = m.m[0][2] * m.m[1][3] - m.m[0][3] * m.m[1][2];
	float coef_22 = m.m[0][1] * m.m[1][3] - m.m[0][3] * m.m[1][1];
	float coef_23 = m.m[0][1] * m.m[1][2] - m.m[0][2] * m.m[1][1];

	vec4 Fac0(coef_00, coef_00, coef_02, coef_03);
	vec4 Fac1(coef_04, coef_04, coef_06, coef_07);
	vec4 Fac2(coef_08, coef_08, coef_10, coef_11);
	vec4 Fac3(coef_12, coef_12, coef_14, coef_15);
	vec4 Fac4(coef_16, coef_16, coef_18, coef_19);
	vec4 Fac5(coef_20, coef_20, coef_22, coef_23);

	vec4 Vec0(m.m[0][1], m.m[0][0], m.m[0][0], m.m[0][0]);
	vec4 Vec1(m.m[1][1], m.m[1][0], m.m[1][0], m.m[1][0]);
	vec4 Vec2(m.m[2][1], m.m[2][0], m.m[2][0], m.m[2][0]);
	vec4 Vec3(m.m[3][1], m.m[3][0], m.m[3][0], m.m[3][0]);

	vec4 Inv0(Vec1 * Fac0 - Vec2 * Fac1 + Vec3 * Fac2);
	vec4 Inv1(Vec0 * Fac0 - Vec2 * Fac3 + Vec3 * Fac4);
	vec4 Inv2(Vec0 * Fac1 - Vec1 * Fac3 + Vec3 * Fac5);
	vec4 Inv3(Vec0 * Fac2 - Vec1 * Fac4 + Vec2 * Fac5);

	vec4 SignA(+1, -1, +1, -1);
	vec4 SignB(-1, +1, -1, +1);
	mat4 Inverse(Inv0 * SignA, Inv1 * SignB, Inv2 * SignA, Inv3 * SignB);

	vec4 Row0(Inverse.m[0][0], Inverse.m[0][1], Inverse.m[0][2], Inverse.m[0][3]);

	vec4 Dot0(m.get_col(0) * Row0);
	float Dot1 = (Dot0.x + Dot0.y) + (Dot0.z + Dot0.w);

	float OneOverDeterminant = 1.0F / Dot1;

	return Inverse * OneOverDeterminant;
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
//* Matrix 4x4 Struct                        *//
//********************************************//
#pragma endregion


#pragma region /* rge::color */
//********************************************//
//* Color Struct                             *//
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
//* Color Struct                             *//
//********************************************//
#pragma endregion


#pragma region /* rge::math */
//********************************************//
//* Math Module                              *//
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

float math::move_towards(float current, float target, float max_delta) {
	if(current < target) {
		current += max_delta;
		if(current > target)
			current = target;
	} else if(current > target) {
		current -= max_delta;
		if(current < target)
			current = target;
	}

	return current;
}
//********************************************//
//* Math Module                              *//
//********************************************//
#pragma endregion


#pragma region /* rge::log */
//********************************************//
//* Logging Module                           *//
//********************************************//
namespace log { const int BUFFER_SIZE = 512; }

void log::info(const char* msg, ...) {
	char buffer[log::BUFFER_SIZE];
    va_list args;
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
    va_list args;
    va_start(args, msg);
    #ifdef SYS_WINDOWS
	vsprintf_s(buffer, log::BUFFER_SIZE, msg, args);
	#else
	vsprintf(buffer, msg, args);
	#endif
    va_end(args);
	std::cout << "[WARNING] " << buffer << std::endl;
}

void log::error(const char* msg, ...) {
	char buffer[log::BUFFER_SIZE];
    va_list args;
    va_start(args, msg);
    #ifdef SYS_WINDOWS
	vsprintf_s(buffer, log::BUFFER_SIZE, msg, args);
	#else
	vsprintf(buffer, msg, args);
	#endif
    va_end(args);
	std::cout << "[ERROR] " << buffer << std::endl;
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
	const code KY_BUT_FIRST = KEY_A;
	const code KY_BUT_LAST = KEY_ESC;
	const code MS_BUT_FIRST = MOUSE_LEFT;
	const code MS_BUT_LAST = MOUSE_MIDDLE;
	const code GP_BUT_FIRST = GAMEPAD_UP;
	const code GP_BUT_LAST = GAMEPAD_RIGHT_STICK_RIGHT;
	const code GP_AXS_FIRST = GAMEPAD_LEFT_TRIGGER;
	const code GP_AXS_LAST = GAMEPAD_RIGHT_STICK_Y;

	typedef uint8_t button;
	const int NUM_KEYBOARD_BUTTONS = 60;
	const int NUM_MOUSE_BUTTONS = 3;
	const int NUM_GAMEPAD_BUTTONS = 24;
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

	static bool has_axis(input::code input_code) {
		if(input_code == MOUSE_SCROLL) {
			return true;
		}

		if(input_code >= GP_AXS_FIRST && input_code <= GP_AXS_LAST) {
			return true;
		}

		return false;
	}

	void action::add_binding(input::code binding, float value) {
		bindings.push_back(entry(binding, value));
	}

	void action::remove_binding(input::code binding) {
		std::vector<entry>::iterator it;
		for(it = bindings.begin(); it != bindings.end(); it++) {
			if(it->first == binding) {
				bindings.erase(it);
			}
		}
	}

	void action::clear_bindings() {
		bindings.clear();
	}

	bool is_down(const input::action& input_action, int user) {
		std::vector<action::entry> b = input_action.bindings;
		std::vector<action::entry>::iterator it;
		for(it = b.begin(); it != b.end(); it++) {
			if(is_down(it->first, user)) return true;
		}
		return false;
	}

	bool is_up(const input::action& input_action, int user) {
		return !is_down(input_action, user);
	}

	bool was_pressed(const input::action& input_action, int user) {
		std::vector<action::entry> b = input_action.bindings;
		std::vector<action::entry>::iterator it;
		for(it = b.begin(); it != b.end(); it++) {
			if(was_pressed(it->first, user)) return true;
		}
		return false;
	}

	bool was_released(const input::action& input_action, int user) {
		std::vector<action::entry> b = input_action.bindings;
		std::vector<action::entry>::iterator it;
		for(it = b.begin(); it != b.end(); it++) {
			if(was_released(it->first, user)) return true;
		}
		return false;
	}

	float get_axis(const input::action& input_action, int user) {
		float value = 0;

		std::vector<action::entry> b = input_action.bindings;
		std::vector<action::entry>::iterator it;
		for(it = b.begin(); it != b.end(); it++) {
			if(has_axis(it->first)) {
				value += get_axis(it->first, user);
			} else if(is_down(it->first)) {
				value += it->second;
			}
		}

		if(value < -1.0F) value = -1.0F;
		if(value > 1.0F) value = 1.0F;

		return value;
	}

	bool is_down(input::code input_code, int user) {
		if(input_code >= KY_BUT_FIRST && input_code <= KY_BUT_LAST) {
			return get(&keyboard_buttons[input_code - KY_BUT_FIRST], 0);
		}

		if(input_code >= MS_BUT_FIRST && input_code <= MS_BUT_LAST) {
			return get(&mouse_buttons[input_code - MS_BUT_FIRST], 0);
		}

		if(input_code >= GP_BUT_FIRST && input_code <= GP_BUT_LAST && user >= 0 && user < MAX_GAMEPAD_COUNT) {
			return get(&gamepad_buttons[input_code - GP_BUT_FIRST][user], 0);
		}

		if(input_code == GAMEPAD_LEFT_TRIGGER) {
			return get(&gamepad_buttons[22][user], 0);
		}

		if(input_code == GAMEPAD_RIGHT_TRIGGER) {
			return get(&gamepad_buttons[23][user], 0);
		}

		if(input_code == ANY) {
			for(int i = 0; i < NUM_KEYBOARD_BUTTONS; i++)
				if(get(&keyboard_buttons[i], 0)) return true;
			
			for(int i = 0; i < NUM_MOUSE_BUTTONS; i++)
				if(get(&mouse_buttons[i], 0)) return true;

			for(int i = 0; i < NUM_GAMEPAD_BUTTONS; i++)
				for(int j = 0; j < MAX_GAMEPAD_COUNT; j++)
					if(get(&gamepad_buttons[i][j], 0)) return true;
		}

		return false;
	}

	bool is_up(input::code input_code, int user) {
		return !is_down(input_code, user);
	}

	bool was_pressed(input::code input_code, int user) {
		if(input_code >= KY_BUT_FIRST && input_code <= KY_BUT_LAST) {
			return get(&keyboard_buttons[input_code - KY_BUT_FIRST], 1);
		}

		if(input_code >= MS_BUT_FIRST && input_code <= MS_BUT_LAST) {
			return get(&mouse_buttons[input_code - MS_BUT_FIRST], 1);
		}

		if(input_code >= GP_BUT_FIRST && input_code <= GP_BUT_LAST && user >= 0 && user < MAX_GAMEPAD_COUNT) {
			return get(&gamepad_buttons[input_code - GP_BUT_FIRST][user], 1);
		}

		if(input_code == GAMEPAD_LEFT_TRIGGER) {
			return get(&gamepad_buttons[22][user], 1);
		}

		if(input_code == GAMEPAD_RIGHT_TRIGGER) {
			return get(&gamepad_buttons[23][user], 1);
		}

		if(input_code == ANY) {
			for(int i = 0; i < NUM_KEYBOARD_BUTTONS; i++)
				if(get(&keyboard_buttons[i], 1)) return true;

			for(int i = 0; i < NUM_MOUSE_BUTTONS; i++)
				if(get(&mouse_buttons[i], 1)) return true;

			for(int i = 0; i < NUM_GAMEPAD_BUTTONS; i++)
				for(int j = 0; j < MAX_GAMEPAD_COUNT; j++)
					if(get(&gamepad_buttons[i][j], 1)) return true;
		}

		return false;
	}

	bool was_released(rge::input::code input_code, int user) {
		if(input_code >= KY_BUT_FIRST && input_code <= KY_BUT_LAST) {
			return get(&keyboard_buttons[input_code - KY_BUT_FIRST], 2);
		}

		if(input_code >= MS_BUT_FIRST && input_code <= MS_BUT_LAST) {
			return get(&mouse_buttons[input_code - MS_BUT_FIRST], 2);
		}

		if(input_code >= GP_BUT_FIRST && input_code <= GP_BUT_LAST && user >= 0 && user < MAX_GAMEPAD_COUNT) {
			return get(&gamepad_buttons[input_code - GP_BUT_FIRST][user], 2);
		}

		if(input_code == GAMEPAD_LEFT_TRIGGER) {
			return get(&gamepad_buttons[22][user], 2);
		}

		if(input_code == GAMEPAD_RIGHT_TRIGGER) {
			return get(&gamepad_buttons[23][user], 2);
		}

		if(input_code == ANY) {
			for(int i = 0; i < NUM_KEYBOARD_BUTTONS; i++)
				if(get(&keyboard_buttons[i], 2)) return true;

			for(int i = 0; i < NUM_MOUSE_BUTTONS; i++)
				if(get(&mouse_buttons[i], 2)) return true;

			for(int i = 0; i < NUM_GAMEPAD_BUTTONS; i++)
				for(int j = 0; j < MAX_GAMEPAD_COUNT; j++)
					if(get(&gamepad_buttons[i][j], 2)) return true;
		}

		return false;
	}

	float get_axis(input::code input_code, int user) {
		if(input_code == MOUSE_SCROLL) {
			return mouse_scroll;
		}

		if(input_code >= GP_AXS_FIRST && input_code <= GP_AXS_LAST && user >= 0 && user < MAX_GAMEPAD_COUNT) {
			return gamepad_axis[input_code - GP_AXS_FIRST][user];
		}

		return 0;
	}

	vec2 get_mouse_position() {
		return mouse_position;
	}

	bool on_key_pressed(const key_pressed_event& e) {
		set(&keyboard_buttons[e.input_code - KY_BUT_FIRST], 1);
		set(&keyboard_buttons[e.input_code - KY_BUT_FIRST], 0);
		return false; // Do not consume event. Let it propagate through higher layers.
	}

	bool on_key_released(const key_released_event& e) {
		set(&keyboard_buttons[e.input_code - KY_BUT_FIRST], 2);
		clear(&keyboard_buttons[e.input_code - KY_BUT_FIRST], 0);
		return false; // Do not consume event. Let it propagate through higher layers.
	}

	bool on_mouse_pressed(const mouse_pressed_event& e) {
		set(&mouse_buttons[e.input_code - MS_BUT_FIRST], 1);
		set(&mouse_buttons[e.input_code - MS_BUT_FIRST], 0);
		return false; // Do not consume event. Let it propagate through higher layers.
	}

	bool on_mouse_released(const mouse_released_event& e) {
		set(&mouse_buttons[e.input_code - MS_BUT_FIRST], 2);
		clear(&mouse_buttons[e.input_code - MS_BUT_FIRST], 0);
		return false; // Do not consume event. Let it propagate through higher layers.
	}

	bool on_mouse_moved(const mouse_moved_event& e) {
		mouse_position = vec2(float(e.x), float(e.y));
		return false; // Do not consume event. Let it propagate through higher layers.
	}

	bool on_mouse_scrolled(const mouse_scrolled_event& e) {
		mouse_scroll = float(e.scroll);
		return false; // Do not consume event. Let it propagate through higher layers.
	}

	bool on_gamepad_pressed(const gamepad_pressed_event& e) {
		if(e.input_code >= GP_BUT_FIRST && e.input_code <= GP_BUT_LAST) {
			set(&gamepad_buttons[e.input_code - GP_BUT_FIRST][e.user], 1);
			set(&gamepad_buttons[e.input_code - GP_BUT_FIRST][e.user], 0);
		} else if(e.input_code == GAMEPAD_LEFT_TRIGGER) {
			set(&gamepad_buttons[22][e.user], 1);
			set(&gamepad_buttons[22][e.user], 0);
		} else if(e.input_code == GAMEPAD_RIGHT_TRIGGER) {
			set(&gamepad_buttons[23][e.user], 1);
			set(&gamepad_buttons[23][e.user], 0);
		}
		return false; // Do not consume event. Let it propagate through higher layers.
	}

	bool on_gamepad_released(const gamepad_released_event& e) {
		if(e.input_code >= GP_BUT_FIRST && e.input_code <= GP_BUT_LAST) {
			set(&gamepad_buttons[e.input_code - GP_BUT_FIRST][e.user], 2);
			clear(&gamepad_buttons[e.input_code - GP_BUT_FIRST][e.user], 0);
		} else if(e.input_code == GAMEPAD_LEFT_TRIGGER) {
			set(&gamepad_buttons[22][e.user], 2);
			clear(&gamepad_buttons[22][e.user], 0);
		} else if(e.input_code == GAMEPAD_RIGHT_TRIGGER) {
			set(&gamepad_buttons[23][e.user], 2);
			clear(&gamepad_buttons[23][e.user], 0);
		}
		return false; // Do not consume event. Let it propagate through higher layers.
	}

	static void gen_gp_axis_to_but_event(bool was, bool on, code c, int u) {
		if(on && !was) {
			gamepad_pressed_event e;
			e.input_code = c;
			e.user = u;
			engine::get_instance()->post_event(e);
		} else if(!on && was) {
			gamepad_released_event e;
			e.input_code = c;
			e.user = u;
			engine::get_instance()->post_event(e);
		}
	}

	bool on_gamepad_axis(const gamepad_axis_event& e) {
		switch(e.input_code) {
		case GAMEPAD_LEFT_TRIGGER:
			gen_gp_axis_to_but_event(get_axis(GAMEPAD_LEFT_TRIGGER, e.user) > 0.5F, e.value > 0.5F, GAMEPAD_LEFT_TRIGGER, e.user);
			break;

		case GAMEPAD_RIGHT_TRIGGER:
			gen_gp_axis_to_but_event(get_axis(GAMEPAD_RIGHT_TRIGGER, e.user) > 0.5F, e.value > 0.5F, GAMEPAD_RIGHT_TRIGGER, e.user);
			break;

		case GAMEPAD_LEFT_STICK_X:
			gen_gp_axis_to_but_event(get_axis(GAMEPAD_LEFT_STICK_X, e.user) < -0.5F, e.value < -0.5F, GAMEPAD_LEFT_STICK_LEFT, e.user);
			gen_gp_axis_to_but_event(get_axis(GAMEPAD_LEFT_STICK_X, e.user) > 0.5F, e.value > 0.5F, GAMEPAD_LEFT_STICK_RIGHT, e.user);
			break;

		case GAMEPAD_LEFT_STICK_Y:
			gen_gp_axis_to_but_event(get_axis(GAMEPAD_LEFT_STICK_Y, e.user) < -0.5F, e.value < -0.5F, GAMEPAD_LEFT_STICK_DOWN, e.user);
			gen_gp_axis_to_but_event(get_axis(GAMEPAD_LEFT_STICK_Y, e.user) > 0.5F, e.value > 0.5F, GAMEPAD_LEFT_STICK_UP, e.user);
			break;

		case GAMEPAD_RIGHT_STICK_X:
			gen_gp_axis_to_but_event(get_axis(GAMEPAD_RIGHT_STICK_X, e.user) < -0.5F, e.value < -0.5F, GAMEPAD_RIGHT_STICK_LEFT, e.user);
			gen_gp_axis_to_but_event(get_axis(GAMEPAD_RIGHT_STICK_X, e.user) > 0.5F, e.value > 0.5F, GAMEPAD_RIGHT_STICK_RIGHT, e.user);
			break;

		case GAMEPAD_RIGHT_STICK_Y:
			gen_gp_axis_to_but_event(get_axis(GAMEPAD_RIGHT_STICK_Y, e.user) < -0.5F, e.value < -0.5F, GAMEPAD_RIGHT_STICK_DOWN, e.user);
			gen_gp_axis_to_but_event(get_axis(GAMEPAD_RIGHT_STICK_Y, e.user) > 0.5F, e.value > 0.5F, GAMEPAD_RIGHT_STICK_UP, e.user);
			break;

		default:
			break;
		}

		gamepad_axis[e.input_code - GP_AXS_FIRST][e.user] = e.value;

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
			clear(&mouse_buttons[i], 1);
			clear(&mouse_buttons[i], 2);
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


#pragma region /* rge::random */
//********************************************//
//* Random Number Generator                  *//
//********************************************//
random::random(uint64_t seed) {
	this->seed = seed;
	this->state = seed;
}

random::random() {
	std::time_t t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	this->seed = t;
	this->state = t;
}

float random::range(float min, float max) {
	float t = next_f32();
	return min * (1 - t) + max * t;
}

double random::range(double min, double max) {
	double t = next_f64();
	return min * (1 - t) + max * t;
}

int random::range(int min, int max) {
	double t = next_f64();
	int i = int(min * (1 - t) + max * t);
	if(i == max) i--;
	return i;
}

float random::next_f32() {
	return float(next_u16()) / float(0xFFFF);
}

double random::next_f64() {
	return double(next_u32()) / double(0xFFFFFFFF);
}

uint8_t random::next_u8() {
	return next_u64() % 0xFF;
}

uint16_t random::next_u16() {
	return next_u64() % 0xFFFF;
}

uint32_t random::next_u32() {
	return next_u64() % 0xFFFFFFFF;
}

uint64_t random::next_u64() {
	state ^= state << 13;
	state ^= state >> 7;
	state ^= state << 17;
	return state;
}

int8_t random::next_i8() {
	return (int8_t)next_u8();
}

int16_t random::next_i16() {
	return (int16_t)next_u16();
}

int32_t random::next_i32() {
	return (int32_t)next_u32();
}

int64_t random::next_i64() {
	return (int64_t)next_u64();
}
//********************************************//
//* Random Number Generator                  *//
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
		typename std::vector<std::function<bool(const T&)>>::iterator it;
		for(it = handlers.begin(); it != handlers.end(); it++) {
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
//* Event Manager                            *//
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

			default:
				return false;
		}
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
//* Event Manager                            *//
//********************************************//
#pragma endregion


#pragma region /* rge::asset_manager */
//********************************************//
//* Asset Manager                            *//
//********************************************//
class asset_manager {

};
//********************************************//
//* Asset Manager                            *//
//********************************************//
#pragma endregion


#pragma region /* rge::engine */
//********************************************//
//* Core Engine                              *//
//********************************************//
const float RESOURCES_FLUSH_INTERVAL = 20.0F;

engine* engine::instance = nullptr;

bool engine::can_create_instance() {
	return instance == nullptr;
}

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
	resources_flush_counter = 0;
}

engine::~engine() {
	instance = nullptr;
	delete renderer_impl;
	delete platform_impl;
}

void engine::run(bool wait_until_exit) {
	if(is_running) return;

	if(wait_until_exit) {
		procedure();
	} else {
		multi_threaded = true;
		thread = std::thread(&engine::procedure, this);
		while(!is_running) continue;
	}
}

void engine::procedure() {
	if(start() != rge::OK) return;
	while(is_running) loop();
}

rge::result engine::init() {
	configure();

	if(has_init) {
		log::error("RGE core has already been initialised!");
		return rge::FAIL;
	}

	log::info("Initialising RGE...");

	instance = this;

	if(platform_impl == nullptr || renderer_impl == nullptr) return rge::FAIL;

	if(platform_impl->init(this) != rge::OK) {
		log::error("Failed to initialise platform module!");
		return rge::FAIL;
	}

	std::string window_title = "Retro Game Engine";
	int window_width = 800;
	int window_height = 600;
	bool fullscreen = false;

	get_default_window_params(window_title, window_width, window_height, fullscreen);
	if(window_width < 1) window_width = 1;
	if(window_height < 1) window_height = 1;

	if(platform_impl->create_window(window_title, window_width, window_height, fullscreen) != rge::OK) {
		log::error("Failed to create window!");
		return rge::FAIL;
	}

	if(renderer_impl->init(platform_impl) != rge::OK) {
		log::error("Failed to initialise renderer module!");
		return rge::FAIL;
	}

	events_impl->on_window_close_requested.add_handler(RGE_BIND_EVENT_HANDLER(on_window_close_requested, window_close_requested_event));
	events_impl->on_window_resized.add_handler(RGE_BIND_EVENT_HANDLER(renderer_impl->on_window_resized, window_resized_event));
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
	
	on_start();
	
	is_running = true;
	
	return rge::OK;
}

void engine::loop() {
	// Handle all events (except gamepad, that is polled jsut before main loop update call).
	platform_impl->poll_events();
	events_impl->process();

	// In case exit() was called during event handling.
	if(!is_running) return;

	// Calculate the elapsed time since last frame.
	time_stamp_2 = std::chrono::system_clock::now();
	std::chrono::duration<float> elapsed_time = time_stamp_2 - time_stamp_1;
	time_stamp_1 = time_stamp_2;
	float delta_time = elapsed_time.count();

	if(get_platform()->skip_next_frame) {
		get_platform()->skip_next_frame = false;
		return;
	}
		
	// Tick the update routine.
	update_counter += delta_time;
	if(update_counter > update_interval) {
		platform_impl->poll_gamepads();
		on_update(update_counter);
		update_counter -= update_interval;
		input::flush_presses_and_releases();
	}
		
	// Tick the physics routine.
	physics_counter += delta_time;
	if(physics_counter > physics_interval) {
		on_physics(physics_counter);
		physics_counter -= physics_interval;
	}
		
	// Tick the rendering routine.
	render_counter += delta_time;
	if(render_counter > render_interval) {
		renderer_impl->prepare_render();
		on_render();
		renderer_impl->display();
		platform_impl->refresh_window();
		render_counter -= render_interval;
	}

	resources_flush_counter += delta_time;
	if(resources_flush_counter >= RESOURCES_FLUSH_INTERVAL) {
		texture::flush_registry();
		resources_flush_counter -= RESOURCES_FLUSH_INTERVAL;
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

	platform_impl->clean_up();
	return rge::OK;
}

int engine::get_frame_rate() const {
	return frame_rate;
}

bool engine::get_is_running() const {
	return is_running;
}

engine* engine::get_instance() {
	return instance;
}

platform* engine::get_platform() {
	return instance->platform_impl;
}

renderer* engine::get_renderer() {
	return instance->renderer_impl;
}

void engine::wait_for_exit() {
	if(multi_threaded)
		thread.join();
}
//********************************************//
//* Core Engine                              *//
//********************************************//
#pragma endregion


#pragma region /* rge::transform */
//********************************************//
//* Transform Class                          *//
//********************************************//
transform::ptr transform::create() {
	return std::make_shared<transform>();
}

transform::ptr transform::create(transform::ptr parent) {
	return std::make_shared<transform>(parent);
}

transform::ptr transform::create(vec3 position, quaternion rotation, vec3 scale) {
	return std::make_shared<transform>(position, rotation, scale);
}

transform::ptr transform::create(vec3 position, quaternion rotation, vec3 scale, transform::ptr parent) {
	return std::make_shared<transform>(position, rotation, scale, parent);
}

transform::transform() {
	parent = nullptr;
	this->position = vec3();
	this->rotation = quaternion::identity();
	this->scale = vec3(1, 1, 1);
}

transform::transform(transform::ptr parent) {
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

transform::transform(vec3 position, quaternion rotation, vec3 scale, transform::ptr parent) {
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
	if(parent != nullptr){
		this->position = mat4::inverse(parent->get_global_matrix()).multiply_point_3x4(position);
	} else {
		this->position = position;
	}
}

void transform::set_global_rotation(const quaternion& rotation) {
	if(parent != nullptr) {
		// TODO
		// this->rotation = mat4::inverse(parent->get_global_matrix()).extract_rotation() * rotation;
	} else {
		this->rotation = rotation;
	}
}
//********************************************//
//* Transform Class                          *//
//********************************************//
#pragma endregion


#pragma region /* rge::camera */
//********************************************//
//* Camera Class                             *//
//********************************************//
camera::ptr camera::create() {
	return std::make_shared<camera>();
}

camera::camera() {
	transform = rge::transform::create();
	auto_width = true;
}

camera::~camera() {
	
}

mat4 camera::get_view_matrix() const {
	if(transform == nullptr) return mat4::identity();
	mat4 m = transform->get_global_matrix();
	return mat4::inverse(m);
}

void camera::set_perspective(float fov, float near_plane, float far_plane) {
	if(near_plane <= 0.0F) near_plane = 0.001F;

	type = projection_type::PERSPECTIVE;
	this->near_plane = near_plane;
	this->far_plane = far_plane;
	this->fov = fov;
	this->auto_width = true;
}

void camera::set_perspective(float fov, float near_plane, float far_plane, float aspect) {
	if(near_plane <= 0.0F) near_plane = 0.001F;

	type = projection_type::PERSPECTIVE;
	this->near_plane = near_plane;
	this->far_plane = far_plane;
	this->fov = fov;
	this->aspect = aspect;
	this->auto_width = false;
}

void camera::set_orthographic(float near_plane, float far_plane, float vertical_size) {
	type = projection_type::ORTHOGRAPHIC;
	this->near_plane = near_plane;
	this->far_plane = far_plane;
	this->top_plane = vertical_size;
	this->bottom_plane = -vertical_size;
	this->auto_width = true;
}

void camera::set_orthographic(float near_plane, float far_plane, float left_plane, float right_plane, float top_plane, float bottom_plane) {
	type = projection_type::ORTHOGRAPHIC;
	this->left_plane = left_plane;
	this->right_plane = right_plane;
	this->top_plane = top_plane;
	this->bottom_plane = bottom_plane;
	this->near_plane = near_plane;
	this->far_plane = far_plane;
	this->auto_width = false;
}

mat4 camera::calculate_projection_matrix() {
	mat4 projection = mat4::zero();

	if(type == projection_type::ORTHOGRAPHIC) {
		if(auto_width) {
			aspect = float(engine::get_renderer()->get_width()) / float(engine::get_renderer()->get_height());
			left_plane = -top_plane * aspect;
			right_plane = top_plane * aspect;
		}

		projection.m[0][0] = 2.0F / (right_plane - left_plane);
		projection.m[1][1] = 2.0F / (top_plane - bottom_plane);
		projection.m[2][2] = 2.0F / (far_plane - near_plane);

		projection.m[0][3] = -((right_plane + left_plane) / (right_plane - left_plane));
		projection.m[1][3] = -((top_plane + bottom_plane) / (top_plane - bottom_plane));
		projection.m[2][3] = -((far_plane + near_plane) / (far_plane - near_plane));

		projection.m[3][3] = 1.0F;
	} else if(type == projection_type::PERSPECTIVE) {
		if(auto_width) {
			aspect = float(engine::get_renderer()->get_height()) / float(engine::get_renderer()->get_width());
		}

		float fov_rad = fov * DEG_TO_RAD;

		projection.m[0][0] = aspect / tanf(fov_rad / 2.0F);
		projection.m[1][1] = 1.0F / tanf(fov_rad / 2.0F);
		projection.m[2][2] = -(far_plane + near_plane) / (far_plane - near_plane);
		projection.m[2][3] = (2 * far_plane * near_plane) / (far_plane - near_plane);
		projection.m[3][2] = 1.0F;
	}

	return projection;
}

void camera::set_auto_width_adjust(bool auto_width_adjust) {
	auto_width = auto_width_adjust;
}
//********************************************//
//* Camera Class                             *//
//********************************************//
#pragma endregion


#pragma region /* rge::light */
//********************************************//
//* Light Class                              *//
//********************************************//
light::ptr light::create() {
	return std::make_shared<light>();
}

light::light() {
	tint = color(1, 1, 1);
	intensity = 1.0F;
	range = 10;
	type = light_mode::POINT;
}

light::~light() {

}
//********************************************//
//* Light Class                              *//
//********************************************//
#pragma endregion


#pragma region /* rge::mesh */
//********************************************//
//* Mesh Class                               *//
//********************************************//
mesh::ptr mesh::create() {
	return std::make_shared<mesh>();
}

mesh::mesh() {

}

mesh::~mesh() {

}
//********************************************//
//* Mesh Class                               *//
//********************************************//
#pragma endregion


#pragma region /* rge::texture */
//********************************************//
//* Texture Class                            *//
//********************************************//
texture::table texture::registry;

texture::ptr texture::create(int width, int height) {
	ptr texture;
	texture.reset(new rge::texture(width, height));
	return texture;
}

texture::ptr texture::copy(const texture::ptr& original) {
	texture::ptr texture = create(original->get_width(), original->get_height());
	texture->filter = original->filter;

	if(original->is_on_cpu()) {
		texture->allocate();
		int n = texture->get_width() * texture->get_height();
		for(int i = 0; i < n; i++) {
			texture->data[i] = original->data[i];
		}
	}

	return texture;
}

texture::texture(int width, int height) {
	this->width = width;
	this->height = height;

	filter = texture_filter::NEAREST;
	data = nullptr;
	handle = 0;
}

texture::~texture() {
	if(is_on_gpu()) {
		if(engine::get_instance() && engine::get_instance()->get_renderer())
			engine::get_instance()->get_renderer()->free_texture(*this);
	}
	if(is_on_cpu()) delete[] data;
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

		float ix = math::inverse_lerp(float(fui), float(cui), uw);
		float iy = math::inverse_lerp(float(fvi), float(cvi), vh);

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

void texture::allocate() {
	if(data) return;
	data = new color[width * height];
}

void texture::flush_registry() {
	/* TODO: rework whole reference system & garbage collection.
	
	for(auto it = registry.begin(); it != registry.end(); it++) {
		if(it->second.use_count() <= 1) {
			// Last ref texture is in table itself, therefore we free the memory.
			registry.erase(it);
		}
	}
	*/
}

texture::ptr texture::load(const std::string& path, bool load_to_gpu) {
	if(registry.count(path) > 0) {
		texture::ptr t = registry.find(path)->second;
		if(load_to_gpu && !t->is_on_gpu())
			engine::get_renderer()->upload_texture(*t);
		return t;
	}

	#ifdef RGE_USE_STB_IMAGE

	int i, w, h, ch;
	uint8_t* input_buffer = stbi_load(path.c_str(), &w, &h, &ch, 4);

	if(!input_buffer) {
		rge::log::error("Could not load texture: %s", path.c_str());
		return nullptr;
	}

	if(ch != 3 && ch != 4) {
		rge::log::error("Texture file read failed: only RGB & RGBA formats supported!");
		stbi_image_free(input_buffer);
		return nullptr;
	}

	texture::ptr texture = create(w, h);
	texture->allocate();
	
	color* tex_data = texture->get_data();
	color c;
	for(i = 0; i < w * h; ++i) {
		if(ch == 3) {
			c = color(
				input_buffer[i * 3] / 255.0F,
				input_buffer[i * 3 + 1] / 255.0F,
				input_buffer[i * 3 + 2] / 255.0F
			);
		} else if(ch == 4) {
			c = color(
				input_buffer[i * 4] / 255.0F,
				input_buffer[i * 4 + 1] / 255.0F,
				input_buffer[i * 4 + 2] / 255.0F,
				input_buffer[i * 4 + 3] / 255.0F
			);
		}

		tex_data[i] = c;
	}

	stbi_image_free(input_buffer);

	registry.insert(std::pair<std::string, texture::ptr>(path, texture));

	if(load_to_gpu)
		engine::get_renderer()->upload_texture(*texture);

	return texture;
	#else
	LOG_MISSING_DEP(read_texture_from_disk, stb_image.h)
	return nullptr;
	#endif
}
//********************************************//
//* Texture Class                            *//
//********************************************//
#pragma endregion


#pragma region /* rge::sound */
//********************************************//
//* Sound Class                              *//
//********************************************//
sound::ptr sound::load(const std::string& path) {

	sound::ptr sp = std::make_shared<sound>();

	return sp;
}
//********************************************//
//* Sound Class                              *//
//********************************************//
#pragma endregion


#pragma region /* rge::material */
//********************************************//
//* Material Class                           *//
//********************************************//
material::ptr material::create() {
	return std::make_shared<material>();
}

material::material() {
	diffuse = color(1, 1, 1);
	specular = color(1, 1, 1);
	emission = color(0, 0, 0);
	shininess = 0;
}

material::~material() {
	
}
//********************************************//
//* Material Class                           *//
//********************************************//
#pragma endregion


#pragma region /* rge::sprite */
//********************************************//
//* Sprite Class                             *//
//********************************************//
sprite::ptr sprite::create() {
	return std::make_shared<sprite>();
}

sprite::ptr sprite::create(const rge::texture::ptr& texture) {
	return std::make_shared<sprite>(texture);
}

sprite::sprite() {
	transform = rge::transform::create();
	sub_sprite = false;
	centered = false;
	billboard = false;
	pixels_per_unit = 32;
	section = rect(0, 0, pixels_per_unit, pixels_per_unit);
}

sprite::sprite(const rge::texture::ptr& texture) : sprite() {
	this->texture = texture;
}

sprite::~sprite() {

}
//********************************************//
//* Sprite Class                             *//
//********************************************//
#pragma endregion


#pragma region /* rge::render_target */
//********************************************//
//* Render Target Class                      *//
//********************************************//
render_target::ptr render_target::create(renderer* renderer, int width, int height) {
	if(renderer == nullptr) return nullptr;
	if(width < 1) return nullptr;
	if(height < 1) return nullptr;

	return std::make_shared<render_target>(renderer, width, height);
}

rge::result render_target::resize(int width, int height) {
	if(width < 1) return rge::FAIL;
	if(height < 1) return rge::FAIL;

	this->width = width;
	this->height = height;

	if(frame_buffer) renderer_instance->free_texture(*frame_buffer);
	if(depth_buffer) renderer_instance->free_texture(*depth_buffer);

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
	return frame_buffer.get();
}

texture* render_target::get_depth_buffer() const {
	return depth_buffer.get();
}

render_target::~render_target() {
	frame_buffer.reset();
	depth_buffer.reset();
}

render_target::render_target(renderer* renderer, int width, int height) {
	renderer_instance = renderer;
	resize(width, height);
}
//********************************************//
//* Render Target Class                      *//
//********************************************//
#pragma endregion


#pragma region /* rge::renderer */
//********************************************//
//* Renderer Class                           *//
//********************************************//
renderer::renderer() {
	input_camera = nullptr;
	output_render = nullptr;
	ambient_color = color(0,0,0);
}

void renderer::set_camera(camera::ptr camera) {
	input_camera = camera;
}

void renderer::set_ambience(const color& ambient_color) {
	this->ambient_color = ambient_color;
}

rge::result renderer::set_target(render_target::ptr target) {
	output_render = target;
	return rge::OK;
}

render_target::ptr renderer::get_target() const {
	return output_render;
}

void renderer::prepare_render() {
	
}
//********************************************//
//* Renderer Class                           *//
//********************************************//
#pragma endregion


#pragma region /* rge::windows */
//********************************************//
//* Windows Platform Class                   *//
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


	static windows* get_instance() {
		return (windows*)engine::get_platform();
	}

	windows() {
		has_init = false;
		has_window = false;
		has_focus = false;

		frame.buffer = nullptr;
	}

public:
	rge::result init(rge::engine* engine) override {
		if(has_init) return rge::FAIL;

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

		frame.bitmap_info.bmiHeader.biSize = sizeof(frame.bitmap_info.bmiHeader);
		frame.bitmap_info.bmiHeader.biPlanes = 1;
		frame.bitmap_info.bmiHeader.biBitCount = 32;
		frame.bitmap_info.bmiHeader.biCompression = BI_RGB;
		#endif /* SYS_SOFTWARE_GL */
		
		has_init = true;
		return rge::OK;
	}

	rge::result create_window(const std::string& title, int width, int height, bool fullscreen) override {
		if(!has_init) return rge::FAIL;
		if(has_window) return rge::FAIL;

		DWORD style_ex = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
		DWORD style = WS_CAPTION | WS_SYSMENU | WS_VISIBLE | WS_THICKFRAME;

		RECT rWndRect = { 0, 0, width, height };
		AdjustWindowRectEx(&rWndRect, style, FALSE, style_ex);
		window_width = rWndRect.right - rWndRect.left;
		window_height = rWndRect.bottom - rWndRect.top;

		handle = CreateWindowEx(
			style_ex,
			CLASS_NAME,
			convert_str_to_wstr(title).c_str(),
			style,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			window_width,
			window_height,
			nullptr,
			nullptr,
			config.hInstance,
			0
		);

		if(handle == nullptr) {
			rge::log::error("Failed to create window (winapi).");
			return rge::FAIL;
		}

		// TODO: Add fullscreen

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

	void set_window_size(int width, int height) override {
		// TODO: Test
		if(width < 1) width = 1;
		if(height < 1) height = 1;
		window_width = width;
		window_height = height;
		SetWindowPos(handle, NULL, 0, 0, width, height, SWP_NOMOVE | SWP_NOZORDER);
	}

	void set_fullscreen(bool fullscreen) override {
		// TODO
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
		#elif SYS_OPENGL_1_0
		// TODO
		// SwapBuffers();
		#endif
	}

	static LRESULT CALLBACK on_event(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
		switch(msg) {
			case WM_CLOSE: {
				window_close_requested_event e;
				engine::get_instance()->post_event(e);
				get_instance()->skip_next_frame = true;
				break;
			}

			case WM_DESTROY: {
				PostQuitMessage(0);
				DestroyWindow(hwnd);
				break;
			}

			case WM_PAINT: {
				PAINTSTRUCT ps;
				HDC hdc = BeginPaint(hwnd, &ps);

				if(wParam == 1) {
					// Clears screen.
					BitBlt(hdc, 0, 0, get_instance()->window_width, get_instance()->window_height, 0, 0, 0, BLACKNESS);
				} else {
					// Copies frame buffer to GDI.
					int w = get_instance()->window_width;
					int h = get_instance()->window_height;

					StretchBlt(
						hdc,
						0,
						0 + h,
						w,
						-h,
						get_instance()->device_context,
						0,
						0,
						w,
						h,
						SRCCOPY
					);
				}

				EndPaint(hwnd, &ps);
				break;
			}

			case WM_SIZE: {
				window_resized_event e;
				e.width = LOWORD(lParam);
				e.height = HIWORD(lParam);
				rge::log::info("New window dimensions [%u, %u]", e.width, e.height);
				get_instance()->create_frame(e.width, e.height);
				engine::get_instance()->post_event(e);
				get_instance()->skip_next_frame = true;
				break;
			}

			case WM_MOVE: {
				window_moved_event e;
				e.x = (int)(short)LOWORD(lParam); // Horizontal position.
				e.y = (int)(short)HIWORD(lParam); // Vertical position.
				engine::get_instance()->post_event(e);
				get_instance()->skip_next_frame = true;
				break;
			}

			case WM_KILLFOCUS: {
				get_instance()->has_focus = false;
				window_unfocused_event e;
				engine::get_instance()->post_event(e);
				break;
			}

			case WM_SETFOCUS: {
				get_instance()->has_focus = true;
				window_focused_event e;
				engine::get_instance()->post_event(e);
				break;
			}
			
			case WM_KEYUP: {
				key_released_event e;
				e.input_code = convert_sys_key_to_rge_key((uint8_t)wParam);
				engine::get_instance()->post_event(e);
				break;
			}

			case WM_KEYDOWN: {
				bool key_was_down = ((lParam & (1 << 30)) != 0);
				if(!key_was_down) {
					key_pressed_event e;
					e.input_code = convert_sys_key_to_rge_key((uint8_t)wParam);
					engine::get_instance()->post_event(e);
				}
				break;
			}

			case WM_LBUTTONDOWN: {
				mouse_pressed_event e;
				e.input_code = rge::input::MOUSE_LEFT;
				engine::get_instance()->post_event(e);
				break;
			}

			case WM_RBUTTONDOWN: {
				mouse_pressed_event e;
				e.input_code = rge::input::MOUSE_RIGHT;
				engine::get_instance()->post_event(e);
				break;
			}

			case WM_MBUTTONDOWN: {
				mouse_pressed_event e;
				e.input_code = rge::input::MOUSE_MIDDLE;
				engine::get_instance()->post_event(e);
				break;
			}

			case WM_LBUTTONUP: {
				mouse_released_event e;
				e.input_code = rge::input::MOUSE_LEFT;
				engine::get_instance()->post_event(e);
				break;
			}

			case WM_RBUTTONUP: {
				mouse_released_event e;
				e.input_code = rge::input::MOUSE_RIGHT;
				engine::get_instance()->post_event(e);
				break;
			}

			case WM_MBUTTONUP: {
				mouse_released_event e;
				e.input_code = rge::input::MOUSE_MIDDLE;
				engine::get_instance()->post_event(e);
				break;
			}

			case WM_MOUSEMOVE: {
				mouse_moved_event e;
				e.x = (int)(short)LOWORD(lParam); // Horizontal position.
				e.y = (int)(short)HIWORD(lParam); // Vertical position.
				engine::get_instance()->post_event(e);
				break;
			}

			case WM_MOUSEWHEEL: {
				mouse_scrolled_event e;
				e.scroll = (short)HIWORD(wParam) / 120;
				engine::get_instance()->post_event(e);
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
		engine::get_instance()->post_event(e);
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
					engine::get_instance()->post_event(e);
				} else if(!is_pressed && was_pressed) {
					gamepad_released_event e;
					e.input_code = (input::code)i;
					e.user = u;
					engine::get_instance()->post_event(e);
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

		frame.bitmap = CreateDIBSection(NULL, &frame.bitmap_info, DIB_RGB_COLORS, &(frame.buffer), 0, 0);
		if(frame.bitmap == NULL) {
			rge::log::error("Failed to create win32 frame buffer.");
			return;
		}

		SelectObject(device_context, frame.bitmap);
		#endif /* SYS_SOFTWARE_GL */
	}

	uint8_t* get_frame_buffer() {
		return (uint8_t*)frame.buffer;
	}

	bool is_focused() const override {
		return has_focus;
	}

	void clean_up() override {

	}
};
#endif /* SYS_WINDOWS */
//********************************************//
//* Windows Platform Class                   *//
//********************************************//
#pragma endregion


#pragma region /* rge::linux */
//********************************************//
//* Linux Platform Class                     *//
//********************************************//
#ifdef SYS_LINUX
class linux : public platform {

};
#endif /* SYS_LINUX */
//********************************************//
//* Linux Platform Class                     *//
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
	render_target::ptr output_window;
	platform* platform_instance;

	render_target::ptr get_real_target() const {
		return output_render != nullptr ? output_render : output_window;
	}

public:
	software_gl() : renderer() {}

public:
	rge::result init(platform* platform) override {
		platform_instance = platform;
		output_window = render_target::create(this, 800, 600);
		return rge::OK;
	}

	texture::ptr create_texture(int width, int height) override {
		texture::ptr texture = texture::create(width, height);

		texture->allocate();

		return texture;
	}

	void alloc_texture(texture& texture) override {
		if(!texture.is_on_cpu())
			texture.allocate();
	}

	void upload_texture(texture& texture) override {
		// NOTE: N/A to software renderer.
	}

	void free_texture(texture& texture) override {
		// TODO: Deallocate cpu
	}

	int get_width() const override {
		return get_real_target()->get_width();
	}

	int get_height() const override {
		return get_real_target()->get_height();
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
		uint8_t* to_buffer = winapi->get_frame_buffer();
		color* from_buffer = output_window->get_frame_buffer()->get_data();
		if(to_buffer == nullptr) {
			rge::log::error("no frame buffer win32");
			return;
		}

		int n = output_window->get_frame_buffer()->get_width() * output_window->get_frame_buffer()->get_height();
		for(int i = 0; i < n; i++) {
			color c = from_buffer[i];
			if(c.r > 1.0F) c.r = 1.0F;
			if(c.g > 1.0F) c.g = 1.0F;
			if(c.b > 1.0F) c.b = 1.0F;
			if(c.a > 1.0F) c.a = 1.0F;
			if(c.r < 0.0F) c.r = 0.0F;
			if(c.g < 0.0F) c.g = 0.0F;
			if(c.b < 0.0F) c.b = 0.0F;
			if(c.a < 0.0F) c.a = 0.0F;
			to_buffer[i * 4] = (uint8_t)(c.b * 255);
			to_buffer[i * 4 + 1] = (uint8_t)(c.g * 255);
			to_buffer[i * 4 + 2] = (uint8_t)(c.r * 255);
			to_buffer[i * 4 + 3] = (uint8_t)(c.a * 255);
		}

		winapi->refresh_window();
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
		if(input_camera == nullptr || get_real_target() == nullptr) return rge::FAIL;

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
		mat4 world_to_projection = input_camera->calculate_projection_matrix() * input_camera->get_view_matrix();

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

			if(/* Check if all three projected vertices are within homogeneous clip bounds. */
			   (proj_v1.x >= -1 && proj_v1.x <= 1) || (proj_v1.y >= -1 && proj_v1.y <= 1) ||
			   (proj_v2.x >= -1 && proj_v2.x <= 1) || (proj_v2.y >= -1 && proj_v2.y <= 1) ||
			   (proj_v3.x >= -1 && proj_v3.x <= 1) || (proj_v3.y >= -1 && proj_v3.y <= 1)
			   ) {
				// Calculate the normal of the projected triangle from the cross
				// product of two of its edges.
				proj_tri_normal = vec3::cross(proj_v2 - proj_v1, proj_v3 - proj_v1);

				// Calculate the centre of the projected triangle.
				proj_tri_center = (proj_v1 + proj_v2 + proj_v3) / 3;

				// Check the dot project of the projected triangle normal and
				// the camera to triangle centre vector - if the dot product is
				// <= 0, the normal and vector point at each other, and the triangle
				// must be facing the camera, so we should render it. If the dot
				// product is >0, they are facing the same direction, therefore
				// the triangle is facing away from the camera - don't render it.
				float d = vec3::dot(proj_tri_normal, proj_tri_center - camera_position);

				if(d <= 0) {
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

	// Draw a 2D sprite onto camera space.
	void draw(const sprite& sprite) override {
		// TODO
	}

	// Draw a 2D texture onto (dest)[0, 1] view space, from (src)[0, 1] uv space.
	void draw(
		const texture& texture,
		vec2 dest_min,
		vec2 dest_max,
		vec2 src_min,
		vec2 src_max
	) override {
		// TODO
	}

	// Draw a 2D texture onto (dest)[0, w/h] frame space, from (src)[0, w/h] texel space.
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
		for(y = y_min; y < y_max; y++) {
			for(x = x_min; x < x_max; x++) {
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
					ptr = x + ((get_real_target()->get_height() - 1 - y) * get_real_target()->get_width());

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
class opengl_1_0 : public renderer {
private:
	#ifdef SYS_WINDOWS
	gl_device_context_t device = 0;
	gl_render_context_t render = 0;
	#endif

	int window_width;
	int window_height;

public:
	opengl_1_0() : renderer() {

	}

	static void load_default_draw_params() {
		glEnable(GL_LIGHTING);
		// glEnable(GL_LIGHT0);

		glEnable(GL_TEXTURE_2D);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_DEPTH_TEST);
		glDepthMask(GL_TRUE);
		glDepthFunc(GL_LESS);
		glDepthRange(-1.0F, 1.0F);

		glEnable(GL_COLOR_MATERIAL);
		glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
		glColor4f(1, 1, 1, 1);

		glEnable(GL_CULL_FACE);
		glFrontFace(GL_CCW);
		glCullFace(GL_BACK);
	}

	result init(platform* platform) override {
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

		

		return OK;
	}

	texture::ptr create_texture(int width, int height) override {
		texture::ptr texture = texture::create(width, height);

		glGenTextures(1, &texture->handle);

		return texture;
	}

	void alloc_texture(texture& texture) override {
		if(!texture.is_on_gpu())
			glGenTextures(1, &texture.handle);
	}

	void upload_texture(texture& texture) override {
		alloc_texture(texture);

		if(!texture.is_on_cpu()) return;
		glBindTexture(GL_TEXTURE_2D, texture.handle);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		if(texture.filter == texture_filter::NEAREST) {
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		} else if(texture.filter == texture_filter::BILINEAR) {
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}

		glTexImage2D(GL_TEXTURE_2D, 0, 4, texture.get_width(), texture.get_height(), 0, GL_RGBA, GL_FLOAT, texture.get_data());
	}

	void free_texture(texture& texture) override {
		if(texture.is_on_gpu())
			glDeleteTextures(1, &texture.handle);
	}

	int get_width() const override {
		return window_width;
	}

	int get_height() const override {
		return window_height;
	}

	void clear(color background) override {
		glClearColor(
			float(background.r),
			float(background.g),
			float(background.b),
			float(background.a)
		);
		glClearDepth(2.0F);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	static void convert_matrix(GLfloat* gl, const mat4& m) {
		for(int i = 0; i < 16; ++i) gl[i] = m.m[i % 4][i / 4];
	}

	void display() override {
		glFlush();

		#ifdef SYS_WINDOWS
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

	static void apply_material(const rge::material& material) {
		if(material.texture != nullptr && material.texture->is_on_gpu()) {
			glBindTexture(GL_TEXTURE_2D, material.texture->handle);
		} else {
			glDisable(GL_TEXTURE_2D);
		}

		glShadeModel(GL_SMOOTH);

		GLfloat ambient[] = { ambient_color.r, ambient_color.g, ambient_color.b, ambient_color.a };
		glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
		
		GLfloat diffuse[] = { material.diffuse.r, material.diffuse.g, material.diffuse.b, material.diffuse.a };
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);

		GLfloat specular[] = { material.specular.r, material.specular.g, material.specular.b, material.specular.a };
		glMaterialfv(GL_FRONT, GL_SPECULAR, specular);

		GLfloat emission[] = { material.emission.r, material.emission.g, material.emission.b, material.emission.a };
		glMaterialfv(GL_FRONT, GL_EMISSION, emission);

		GLint mask[] = { 1, 1, 1 };
		glMaterialiv(GL_FRONT, GL_COLOR_INDEXES, mask);

		glMaterialf(GL_FRONT, GL_SHININESS, material.shininess);

		//glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);
		//glColor4f(material.diffuse.r, material.diffuse.g, material.diffuse.b, material.diffuse.a);

		glColorMaterial(GL_FRONT, GL_DIFFUSE);
		glEnable(GL_COLOR_MATERIAL);
		//glEnable(GL_LIGHTING);
	}

	// Draw 3D geometry, using model space data.
	result draw(
		const mat4& local_to_world,
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

		if(input_camera == nullptr) return FAIL;
		
		convert_matrix(gl_m, input_camera->get_view_matrix());
		glMatrixMode(GL_MODELVIEW);
		glLoadMatrixf(gl_m);

		convert_matrix(gl_m, input_camera->calculate_projection_matrix());
		glMatrixMode(GL_PROJECTION);
		glLoadMatrixf(gl_m);

		load_default_draw_params();
		apply_material(material);
		glDepthRange(1.0F, -1.0F);
		
		// glEnable(GL_LIGHT0);
		float lpos[4] = { 0, 1, 0, 1.0 };
		// glLightfv(GL_LIGHT0, GL_POSITION, lpos);

		glBegin(GL_TRIANGLES); {
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
		} glEnd();

		return OK;
	}

	// Draw a 2D sprite onto camera space.
	void draw(const sprite& sprite) override {
		if(input_camera == nullptr) return;
		if(sprite.texture == nullptr) return;

		GLfloat gl_m[16];
		mat4 sprite_matrix = sprite.transform->get_global_matrix();
		mat4 camera_matrix = input_camera->transform->get_global_matrix();

		vec2 tex_size = vec2(sprite.texture->get_width(), sprite.texture->get_height());

		float w;
		float h;

		if(sprite.sub_sprite) {
			w = sprite.section.w;
			h = sprite.section.h;
		} else {
			w = tex_size.x;
			h = tex_size.y;
		}

		w /= sprite.pixels_per_unit;
		h /= sprite.pixels_per_unit;

		vec3 p = vec2(0, 0);
		vec3 r = vec2(w, 0);
		vec3 u = vec2(0, h);

		if(sprite.centered) {
			p.x -= w / 2.0F;
			p.y -= h / 2.0F;
		}
		
		vec3 n;
		vec3 p_bl;
		vec3 p_br;
		vec3 p_tl;
		vec3 p_tr;

		if(sprite.billboard) {
			n = camera_matrix.multiply_vector(vec3(0, 0, -1));
			p_bl = sprite_matrix.multiply_point_3x4(p);
			p_br = p_bl + camera_matrix.multiply_vector(r);
			p_tl = p_bl + camera_matrix.multiply_vector(u);
			p_tr = p_bl + camera_matrix.multiply_vector(u + r);
		} else {
			n = sprite_matrix.multiply_vector(vec3(0, 0, -1));
			p_bl = sprite_matrix.multiply_point_3x4(p);
			p_br = sprite_matrix.multiply_point_3x4(p + r);
			p_tl = sprite_matrix.multiply_point_3x4(p + u);
			p_tr = sprite_matrix.multiply_point_3x4(p + r + u);
		}

		vec2 t_bl;
		vec2 t_br;
		vec2 t_tl;
		vec2 t_tr;

		if(sprite.sub_sprite) {
			t_bl = vec2(sprite.section.x / tex_size.x, sprite.section.y / tex_size.y);
			t_br = t_bl + vec2(sprite.section.w / tex_size.x, 0);
			t_tl = t_bl + vec2(0, sprite.section.h / tex_size.y);
			t_tr = t_bl + t_br + t_tl;
		} else {
			t_bl = vec2(0, 0);
			t_br = t_bl + vec2(1, 0);
			t_tl = t_bl + vec2(0, 1);
			t_tr = t_bl + t_br + t_tl;
		}

		color diffuse = color();
		if(sprite.material) diffuse = sprite.material->diffuse;

		convert_matrix(gl_m, input_camera->get_view_matrix());
		glMatrixMode(GL_MODELVIEW);
		glLoadMatrixf(gl_m);

		convert_matrix(gl_m, input_camera->calculate_projection_matrix());
		glMatrixMode(GL_PROJECTION);
		glLoadMatrixf(gl_m);

		load_default_draw_params();
		glDisable(GL_LIGHTING);
		glColor4f(diffuse.r, diffuse.g, diffuse.b, diffuse.a);

		if(sprite.texture->is_on_gpu()) {
			glBindTexture(GL_TEXTURE_2D, sprite.texture->handle);
		} else {
			glDisable(GL_TEXTURE_2D);
		}

		glBegin(GL_QUADS); {
			glTexCoord2f(t_bl.x, 1.0F - t_bl.y);
			glVertex3f(p_bl.x, p_bl.y, p_bl.z);
			glNormal3f(n.x, n.y, n.z);

			glTexCoord2f(t_br.x, 1.0F - t_br.y);
			glVertex3f(p_br.x, p_br.y, p_br.z);
			glNormal3f(n.x, n.y, n.z);

			glTexCoord2f(t_tr.x, 1.0F - t_tr.y);
			glVertex3f(p_tr.x, p_tr.y, p_tr.z);
			glNormal3f(n.x, n.y, n.z);

			glTexCoord2f(t_tl.x, 1.0F - t_tl.y);
			glVertex3f(p_tl.x, p_tl.y, p_tl.z);
			glNormal3f(n.x, n.y, n.z);
		} glEnd();
	}

	// Draw a 2D texture onto (dest)[0, 1] view space, from (src)[0, 1] uv space.
	void draw(const texture& texture, vec2 dest_min, vec2 dest_max, vec2 src_min, vec2 src_max) override {
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		dest_min.x = (dest_min.x * 2.0F) - 1.0F;
		dest_min.y = (dest_min.y * 2.0F) - 1.0F;
		dest_max.x = (dest_max.x * 2.0F) - 1.0F;
		dest_max.y = (dest_max.y * 2.0F) - 1.0F;

		// Check if completely out of bounds.
		if(dest_min.x > 1.0F) {
			return;
		} else if(dest_max.x < -1.0F) {
			return;
		} else if(dest_min.y > 1.0F) {
			return;
		} else if(dest_max.y < -1.0F) {
			return;
		}

		load_default_draw_params();
		glDisable(GL_LIGHTING);
		glDisable(GL_DEPTH_TEST);

		if(texture.is_on_gpu()) {
			glBindTexture(GL_TEXTURE_2D, texture.handle);
		} else {
			glDisable(GL_TEXTURE_2D);
		}

		glBegin(GL_QUADS);

		glTexCoord2f(src_min.x, 1.0F - src_min.y);
		glVertex3f(dest_min.x, dest_min.y, 0.0F);
		glNormal3f(0, 0, -1);

		glTexCoord2f(src_max.x, 1.0F - src_min.y);
		glVertex3f(dest_max.x, dest_min.y, 0.0F);
		glNormal3f(0, 0, -1);

		glTexCoord2f(src_max.x, 1.0F - src_max.y);
		glVertex3f(dest_max.x, dest_max.y, 0.0F);
		glNormal3f(0, 0, -1);

		glTexCoord2f(src_min.x, 1.0F - src_max.y);
		glVertex3f(dest_min.x, dest_max.y, 0.0F);
		glNormal3f(0, 0, -1);

		glEnd();
	}

	// Draw a 2D texture onto (dest)[0, w/h] frame space, from (src)[0, w/h] texel space.
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

class opengl_3_3 : public rge::renderer {
private:
	#ifdef SYS_WINDOWS
	gl_device_context_t device = 0;
	gl_render_context_t render = 0;
	#endif

	int window_width;
	int window_height;

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

		if(!(render = wglCreateContext(device))) {
			rge::log::error("Failed to create OpenGL context!");
			return rge::FAIL;
		}

		wglMakeCurrent(device, render);

		if(!gladLoaderLoadGL()) {
			rge::log::error("Failed to load OpenGL 3.3 functions!");
			return rge::FAIL;
		}

		rge::log::info("OpenGL driver version: %s", glGetString(GL_VERSION));
		rge::log::info("OpenGL spec version: 3.3");

		// Remove Frame cap
		/*
		wglSwapInterval = (wglSwapInterval_t*)wglGetProcAddress("wglSwapIntervalEXT");
		if(wglSwapInterval && !bVSYNC) wglSwapInterval(0);
		bSync = false;
		*/
		#endif
		
		#ifdef SYS_LINUX
		// TODO
		#endif
		
		#ifdef SYS_MACOSX
		// TODO
		#endif

		/*
		glBindBuffer = OPENGL_LOAD(locBindBuffer_t, glBindBuffer);
		glBufferData = OPENGL_LOAD(locBufferData_t, glBufferData);
		glGenBuffers = OPENGL_LOAD(locGenBuffers_t, glGenBuffers);
		glVertexAttribPointer = OPENGL_LOAD(locVertexAttribPointer_t, glVertexAttribPointer);
		glEnableVertexAttribArray = OPENGL_LOAD(locEnableVertexAttribArray_t, glEnableVertexAttribArray);
		glUseProgram = OPENGL_LOAD(locUseProgram_t, glUseProgram);
		glGetShaderInfoLog = OPENGL_LOAD(locGetShaderInfoLog_t, glGetShaderInfoLog);
		*/
		
		return rge::OK;
	}

	static void load_default_draw_params() {
		// glEnable(GL_LIGHTING);
		// glEnable(GL_LIGHT0);

		glEnable(GL_TEXTURE_2D);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_DEPTH_TEST);
		glDepthMask(GL_TRUE);
		glDepthFunc(GL_LESS);
		glDepthRange(-1.0F, 1.0F);

		glEnable(GL_COLOR_MATERIAL);
		glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
		glColor4f(1, 1, 1, 1);

		glEnable(GL_CULL_FACE);
		glFrontFace(GL_CCW);
		glCullFace(GL_BACK);
	}

	texture::ptr create_texture(int width, int height) override {
		texture::ptr texture = texture::create(width, height);

		glGenTextures(1, &texture->handle);
		glBindTexture(GL_TEXTURE_2D, texture->handle);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);

		return texture;
	}

	void alloc_texture(texture& texture) override {
		if(!texture.is_on_gpu()) {
			glGenTextures(1, &texture.handle);
			glBindTexture(GL_TEXTURE_2D, texture.handle);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture.get_width(), texture.get_height(), 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
		}
	}

	void upload_texture(texture& texture) override {
		alloc_texture(texture);

		if(!texture.is_on_cpu()) return;
		glBindTexture(GL_TEXTURE_2D, texture.handle);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		if(texture.filter == texture_filter::NEAREST) {
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		} else if(texture.filter == texture_filter::BILINEAR) {
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}

		glTexImage2D(GL_TEXTURE_2D, 0, 4, texture.get_width(), texture.get_height(), 0, GL_RGBA, GL_FLOAT, texture.get_data());
	}

	void free_texture(texture& texture) override {
		if(texture.is_on_gpu())
			glDeleteTextures(1, &texture.handle);
	}

	render_target::ptr create_render_target(int width, int height) {
		render_target::ptr render_target = render_target::create(this, width, height);

		// The frame buffer (container).
		GLuint frame_buffer_id = 0;
		glGenFramebuffers(1, &frame_buffer_id);
		glBindFramebuffer(GL_FRAMEBUFFER, frame_buffer_id);

		// The depth buffer.
		GLuint depth_buffer_id = 0;
		glGenRenderbuffers(1, &depth_buffer_id);
		glBindRenderbuffer(GL_RENDERBUFFER, depth_buffer_id);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depth_buffer_id);
		
		// The texture buffer.
		GLuint texture_buffer_id = 0;
		glGenTextures(1, &texture_buffer_id);
		glBindTexture(GL_TEXTURE_2D, texture_buffer_id);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, texture_buffer_id, 0);

		// Set the list of draw buffers.
		GLenum DrawBuffers[2] = { GL_COLOR_ATTACHMENT0, GL_DEPTH_ATTACHMENT };
		glDrawBuffers(2, DrawBuffers);

		// TODO: Set data to render_target...

		return render_target;
	}

	void clear(color background) override {
		glClearColor(
			float(background.r),
			float(background.g),
			float(background.b),
			float(background.a)
		);

		glClearDepth(2.0F);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	static void convert_matrix(GLfloat* gl, const mat4& m) {
		for(int i = 0; i < 16; ++i) gl[i] = m.m[i % 4][i / 4];
	}

	void display() override {
		glFlush();

		#ifdef SYS_WINDOWS
		SwapBuffers(device);
		// if(bSync) DwmFlush();
		#endif
		
		#ifdef SYS_LINUX
		// TODO
		#endif
		
		#ifdef SYS_MACOSX
		// TODO
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
		// NOTE: Not implemented. For future...
		return rge::OK;
	}

	void draw(const sprite& sprite) override {
		if(input_camera == nullptr) return;
		if(sprite.texture == nullptr) return;

		// Get geometric & texture data needed for transforming sprite into render space.
		GLfloat gl_m[16];
		mat4 sprite_matrix = sprite.transform->get_global_matrix();
		mat4 camera_matrix = input_camera->transform->get_global_matrix();
		vec2 tex_size = vec2(sprite.texture->get_width(), sprite.texture->get_height());

		// Calculate object-space dimensions.
		float w;
		float h;
		if(sprite.sub_sprite) {
			w = sprite.section.w;
			h = sprite.section.h;
		} else {
			w = tex_size.x;
			h = tex_size.y;
		}
		// Scale to fit 'x' amount of pixels (texels) in 1 world unit.
		w /= sprite.pixels_per_unit;
		h /= sprite.pixels_per_unit;

		// Calculate object-space vectors.
		vec3 p = vec2(0, 0);  // Origin point.
		vec3 r = vec2(w, 0);  // Horizontal vector.
		vec3 u = vec2(0, h);  // Vertical vector.
		if(sprite.centered) {
			// Offset origin to pivot sprite around its center.
			p.x -= w / 2.0F;
			p.y -= h / 2.0F;
		}
		
		// Calculate world-space geometry coordinates.
		vec3 n;      // Normal of quad.
		vec3 p_bl;   // Bottom left point of quad.
		vec3 p_br;   // Bottom right point of quad.
		vec3 p_tl;   // Top left point of quad.
		vec3 p_tr;   // Top right point of quad.
		if(sprite.billboard) {
			n = camera_matrix.multiply_vector(vec3(0, 0, -1));
			p_bl = sprite_matrix.multiply_point_3x4(p);
			p_br = p_bl + camera_matrix.multiply_vector(r);
			p_tl = p_bl + camera_matrix.multiply_vector(u);
			p_tr = p_bl + camera_matrix.multiply_vector(u + r);
		} else {
			n = sprite_matrix.multiply_vector(vec3(0, 0, -1));
			p_bl = sprite_matrix.multiply_point_3x4(p);
			p_br = sprite_matrix.multiply_point_3x4(p + r);
			p_tl = sprite_matrix.multiply_point_3x4(p + u);
			p_tr = sprite_matrix.multiply_point_3x4(p + r + u);
		}

		// Calculate texture coordinates.
		vec2 t_bl;
		vec2 t_br;
		vec2 t_tl;
		vec2 t_tr;
		if(sprite.sub_sprite) {
			t_bl = vec2(sprite.section.x / tex_size.x, sprite.section.y / tex_size.y);
			t_br = t_bl + vec2(sprite.section.w / tex_size.x, 0);
			t_tl = t_bl + vec2(0, sprite.section.h / tex_size.y);
			t_tr = t_bl + t_br + t_tl;
		} else {
			t_bl = vec2(0, 0);
			t_br = t_bl + vec2(1, 0);
			t_tl = t_bl + vec2(0, 1);
			t_tr = t_bl + t_br + t_tl;
		}

		// Get diffuse color, defaults to white.
		color diffuse = color();
		if(sprite.material) diffuse = sprite.material->diffuse;

		// Set camera view matrix.
		convert_matrix(gl_m, input_camera->get_view_matrix());
		glMatrixMode(GL_MODELVIEW);
		glLoadMatrixf(gl_m);

		// Calculate & set projection matrix.
		convert_matrix(gl_m, input_camera->calculate_projection_matrix());
		glMatrixMode(GL_PROJECTION);
		glLoadMatrixf(gl_m);

		// Set rendering options.
		load_default_draw_params();
		glDisable(GL_LIGHTING);
		glColor4f(diffuse.r, diffuse.g, diffuse.b, diffuse.a);

		// Apply texture if located on gpu.
		if(sprite.texture->is_on_gpu()) {
			glBindTexture(GL_TEXTURE_2D, sprite.texture->handle);
		} else {
			glDisable(GL_TEXTURE_2D);
		}

		// Draw quad.
		glBegin(GL_QUADS); {
			glTexCoord2f(t_bl.x, 1.0F - t_bl.y);
			glVertex3f(p_bl.x, p_bl.y, p_bl.z);
			glNormal3f(n.x, n.y, n.z);

			glTexCoord2f(t_br.x, 1.0F - t_br.y);
			glVertex3f(p_br.x, p_br.y, p_br.z);
			glNormal3f(n.x, n.y, n.z);

			glTexCoord2f(t_tr.x, 1.0F - t_tr.y);
			glVertex3f(p_tr.x, p_tr.y, p_tr.z);
			glNormal3f(n.x, n.y, n.z);

			glTexCoord2f(t_tl.x, 1.0F - t_tl.y);
			glVertex3f(p_tl.x, p_tl.y, p_tl.z);
			glNormal3f(n.x, n.y, n.z);
		} glEnd();
	}

	void draw(const texture& texture, vec2 dest_min, vec2 dest_max, vec2 src_min, vec2 src_max) override {
		// Clear view matrix.
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		
		// Clear projection matrix.
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		// Transform coordinates to fit viewport.
		dest_min.x = (dest_min.x * 2.0F) - 1.0F;
		dest_min.y = (dest_min.y * 2.0F) - 1.0F;
		dest_max.x = (dest_max.x * 2.0F) - 1.0F;
		dest_max.y = (dest_max.y * 2.0F) - 1.0F;

		// Check if completely out of bounds.
		if(dest_min.x > 1.0F) {
			return;
		} else if(dest_max.x < -1.0F) {
			return;
		} else if(dest_min.y > 1.0F) {
			return;
		} else if(dest_max.y < -1.0F) {
			return;
		}

		// Set rendering options.
		load_default_draw_params();
		glDisable(GL_LIGHTING);
		glDisable(GL_DEPTH_TEST);

		// Apply texture if located on gpu.
		if(texture.is_on_gpu()) {
			glBindTexture(GL_TEXTURE_2D, texture.handle);
		} else {
			glDisable(GL_TEXTURE_2D);
		}

		// Draw quad.
		glBegin(GL_QUADS); {
			glTexCoord2f(src_min.x, 1.0F - src_min.y);
			glVertex3f(dest_min.x, dest_min.y, 0.0F);
			glNormal3f(0, 0, -1);

			glTexCoord2f(src_max.x, 1.0F - src_min.y);
			glVertex3f(dest_max.x, dest_min.y, 0.0F);
			glNormal3f(0, 0, -1);

			glTexCoord2f(src_max.x, 1.0F - src_max.y);
			glVertex3f(dest_max.x, dest_max.y, 0.0F);
			glNormal3f(0, 0, -1);

			glTexCoord2f(src_min.x, 1.0F - src_max.y);
			glVertex3f(dest_min.x, dest_max.y, 0.0F);
			glNormal3f(0, 0, -1);
		} glEnd();
	}

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

		// Convert destination pixel coordinates to view coordinates.
		dest_min.x = float(dest_min_x) / window_width;
		dest_min.y = float(dest_min_y) / window_height;
		dest_max.x = float(dest_max_x) / window_width;
		dest_max.y = float(dest_max_y) / window_height;

		// Convert source pixel coordinates to view coordinates.
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

	rge::result set_target(render_target::ptr target) {
		output_render = target;
	}

	render_target::ptr get_target() const {
		return output_render;
	}

	int get_width() const {
		return window_width;
	}

	int get_height() const {
		return window_height;
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