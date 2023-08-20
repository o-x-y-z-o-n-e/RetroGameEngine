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
	struct matrix4x4;
	struct color;
	class engine;
	class event;
	class camera;
	class light;
	class texture;
	class material;
	class render_target;
	class renderer;
	class renderer2d;
	class renderer3d;
	namespace platform { class window; }

    enum result { FAIL = 0, OK = 1 };

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
		rect(float x, float y, float w, float h) : x(x), y(y), w(w), h(h) {}
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
		vec2() : x(0), y(0) {}
		vec2(float x, float y) : x(x), y(y) {}

		vec2 operator + (const vec2& rhs) const { return vec2(this->x + rhs.x, this->y + rhs.y); }
		vec2 operator - (const vec2& rhs) const { return vec2(this->x - rhs.x, this->y - rhs.y); }
		vec2 operator * (const float& rhs) const { return vec2(this->x * rhs, this->y * rhs); }
		vec2 operator * (const vec2& rhs) const { return vec2(this->x * rhs.x, this->y * rhs.y); }
		vec2 operator / (const float& rhs) const { return vec2(this->x / rhs, this->y / rhs); }
		vec2 operator / (const vec2& rhs) const { return vec2(this->x / rhs.x, this->y / rhs.y); }

		vec2& operator += (const vec2& rhs) { this->x += rhs.x; this->y += rhs.y; return *this; }
		vec2& operator -= (const vec2& rhs) { this->x -= rhs.x; this->y -= rhs.y; return *this; }
		vec2& operator *= (const float& rhs) { this->x *= rhs;  this->y *= rhs;return *this; }
		vec2& operator *= (const vec2& rhs) { this->x *= rhs.x; this->y *= rhs.y; return *this; }
		vec2& operator /= (const float& rhs) { this->x /= rhs;  this->y /= rhs; return *this; }
		vec2& operator /= (const vec2& rhs) { this->x /= rhs.x; this->y /= rhs.y; return *this; }

		vec2 operator + () const { return { +x, +y }; }
		vec2 operator - () const { return { -x, -y }; }

		bool operator == (const vec2& rhs) const { return (this->x == rhs.x && this->y == rhs.y); }
		bool operator != (const vec2& rhs) const { return (this->x != rhs.x || this->y != rhs.y); }

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

		vec3() : x(0), y(0), z(0) {}
		vec3(float x, float y, float z) : x(x), y(y), z(z) {}

		static float dot(const rge::vec3& v1, const rge::vec3& v2);
		static rge::vec3 cross(const rge::vec3& v1, const rge::vec3& v2);

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
		vec4() : x(0), y(0), z(0), w(0) {}
		vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

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
	};
	//********************************************//
	//* Vector4 struct.                          *//
	//********************************************//
	#pragma endregion

	#pragma region /* rge::matrix4x4 */
	//********************************************//
	//* Matrix 4x4 struct.                       *//
	//********************************************//
	struct matrix4x4 {
 
		float v[4][4];
		// Row>-^  ^-<Column

		matrix4x4() {
			//v = {{0, 0, 0, 0}, {0,0,0,0}, {0,0,0,0}, {0,0,0,0}};
			for(int x = 0; x < 4; x++)
				for(int y = 0; y < 4; y++)
					v[x][y] = 0;
		}

		static rge::matrix4x4 identity() {
			matrix4x4 m = matrix4x4();
			// TODO
			return m;
		}

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

	public:
		color() : r(1), g(1), b(1), a(1) {}
		color(float r, float g, float b) : r(r), g(g), b(b), a(1) {}
		color(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) {}

		color operator * (const color& rhs) const { return color(this->r * rhs.r, this->g * rhs.g, this->b * rhs.b, this->a * rhs.a); }
		color& operator *= (const color& rhs) { this->r *= rhs.r; this->g *= rhs.g; this->b *= rhs.b; this->a *= rhs.a; return *this; }

	public:
		float r, g, b, a;

	public:
		static color lerp(const color& a, const color& b, float t);

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

    public:
        virtual void on_init();
        virtual bool on_command(const std::string& cmd);
        virtual void on_start();
        virtual void on_update(float delta_time);
        virtual void on_physics(float delta_time);
        virtual void on_draw();
        virtual void on_exit();

    public:
        int get_frame_rate() const;
        bool get_is_running() const;

    public:
        float update_interval;
        float physics_interval;
        float draw_interval;

    private:
        void loop();

    private:
        bool is_running;
        std::thread thread;
		rge::platform::window* window;
        float update_counter;
        float physics_counter;
        float draw_counter;
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
	#define EVENT_ENUM_TYPE(type) \
	static event_type get_static_type() { return event_type::type; } \
	virtual event_type get_event_type() const override { return get_static_type(); } \
	//----------------------------------------------
	class event {
	public:
		event() {
			handled = false;
		}

	public:
		template<typename T>
		bool dispatch(std::function<bool(const T&)> func) {
			if(get_event_type() == T::get_static_type()) {
				handled |= func(static_cast<const T&>(*this));
				return true;
			}
			return false;
		}
		bool get_handled() const { return handled; }
		virtual event_type get_event_type() const = 0;


	private:
		bool handled;
	};
	//----------------------------------------------
	class key_event : public rge::event {
	public:
		rge::key::code get_key_code() const { return key_code; }

	protected:
		key_event(rge::key::code key_code) : rge::event() {
			this->key_code = key_code;
		}

	protected:
		rge::key::code key_code;
	};
	//----------------------------------------------
	class key_pressed_event : public rge::key_event {
		EVENT_ENUM_TYPE(KEY_PRESSED)
	public:
		key_pressed_event(rge::key::code key_code) : key_event(key_code) {

		}
	};
	//********************************************//
	//* Event class.                             *//
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
		rge::vec3 get_world_position() const;

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
		rge::vec3 get_world_position() const;

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
		int get_width() const { return width; }
		int get_height() const { return height; }
		bool get_on_disk() const { return on_disk; }
		bool get_on_cpu() const { return on_cpu; }
		bool get_on_gpu() const { return on_gpu; }
		rge::color sample(float u, float v);

	private:
		bool on_disk, on_cpu, on_gpu;
		int width;
		int height;

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
		rge::texture* texture;
		rge::color diffuse;
		rge::color specular;
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
		rge::result set_target(rge::render_target* target);
		rge::render_target* get_target();
		virtual void clear(rge::color color);

	protected:
		rge::render_target* target;

	};
	//********************************************//
	//* Renderer class.                          *//
	//********************************************//
	#pragma endregion

	#pragma region /* rge::renderer2d */
	//********************************************//
	//* Software Renderer 2D class.              *//
	//********************************************//
	class renderer2d : public rge::renderer {

	public:
		renderer2d();
		virtual ~renderer2d();

	public:
		void Draw(const rge::texture& texture, const rge::rect& dest);
		void Draw(const rge::texture& texture, const rge::rect& dest, const rge::rect& src);


	};
	//********************************************//
	//* Software Renderer 2D class.              *//
	//********************************************//
	#pragma endregion

	#pragma region /* rge::renderer3d */
	//********************************************//
	//* Software Renderer 3D class.              *//
	//********************************************//
	class renderer3d : public rge::renderer {

	public:
		renderer3d();
		virtual ~renderer3d();

	public:
		void set_view(const rge::matrix4x4& view_matrix);
		void set_projection(const rge::matrix4x4& projection_matrix);

		void draw(
			const std::vector<rge::vec3>& vertices,
			const std::vector<int>& triangles,
			const std::vector<rge::vec3>& normals,
			const std::vector<rge::vec2>& uvs,
			const rge::material& material,
			const rge::camera& camera
		);

	private:
		rge::vec4 project_vertex(const rge::vec3& vertex);
		void draw_interpolated_triangle(
			const rge::vec4& r_v1,
			const rge::vec4& r_v2,
			const rge::vec4& r_v3,
			const rge::vec3& w_v1,
			const rge::vec3& w_v2,
			const rge::vec3& w_v3,
			const rge::vec3& w_n1,
			const rge::vec3& w_n2,
			const rge::vec3& w_n3,
			const rge::vec2& t_uv1,
			const rge::vec2& t_uv2,
			const rge::vec2& t_uv3,
			const rge::material& material,
			const rge::vec3& camera_position
		);
		static rge::color calculate_blinn_phong(
			const rge::vec3& position,
			const rge::vec3& normal,
			const rge::color& diffuse,
			const rge::color& specular,
			float shininess,
			const rge::vec3& camera_position,
			const std::vector<rge::light*>& lights
		);

	private:
		rge::matrix4x4 view;
		rge::matrix4x4 projection;
		std::vector<rge::light*> lights;

	};
	//********************************************//
	//* Software Renderer 3D class.              *//
	//********************************************//
	#pragma endregion

	namespace platform {

		#pragma region /* rge::platform::window */
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
			
			class window_impl* impl;
			// TODO: bool is_fullscreen;

		};
		//********************************************//
		//* Window class.                            *//
		//********************************************//
		#pragma endregion

	}

}

#endif /* RGE_DEF */

#ifdef RGE_IMPL
#undef RGE_IMPL

namespace rge {

	#pragma region /* rge::rect */
	//********************************************//
	//* Rectangle struct.                        *//
	//********************************************//
	
	//********************************************//
	//* Rectangle struct.                        *//
	//********************************************//
	#pragma endregion

	#pragma region /* rge::vec2 */
	//********************************************//
	//* Vector2 struct.                          *//
	//********************************************//
	
	//********************************************//
	//* Vector2 struct.                          *//
	//********************************************//
	#pragma endregion

	#pragma region /* rge::vec3 */
	//********************************************//
	//* Vector3 struct.                          *//
	//********************************************//
	float vec3::dot(const rge::vec3& v1, const rge::vec3& v2) {
		return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	}

	rge::vec3 vec3::cross(const rge::vec3& v1, const rge::vec3& v2) {
		return rge::vec3(
			v1.y * v2.z - v1.z * v2.y,
			v1.z * v2.x - v1.x * v2.z,
			v1.x * v2.y - v1.y * v2.x
		);
	}
	//********************************************//
	//* Vector3 struct.                          *//
	//********************************************//
	#pragma endregion

	#pragma region /* rge::vec4 */
	//********************************************//
	//* Vector4 struct.                          *//
	//********************************************//
	
	//********************************************//
	//* Vector4 struct.                          *//
	//********************************************//
	#pragma endregion

	#pragma region /* rge::matrix4x4 */
	//********************************************//
	//* Matrix 4x4 struct.                       *//
	//********************************************//
	
	//********************************************//
	//* Matrix 4x4 struct.                       *//
	//********************************************//
	#pragma endregion

	#pragma region /* rge::color */
	//********************************************//
	//* Color struct.                            *//
	//********************************************//
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
		draw_counter = 0;
		update_interval = 1.0F / 60.0F;
		physics_interval = 1.0F / 60.0F;
		draw_interval = 1.0F / 60.0F;
		frame_counter = 0;
		frame_timer = 0;
		frame_rate = 0;

		time_stamp_1 = std::chrono::system_clock::now();
		time_stamp_2 = std::chrono::system_clock::now();
	}

    engine::~engine() {
		delete window;
	}

    rge::result engine::init() {
        log::info("Initialising RGE...");
        // TODO

		window = new rge::platform::window;
        
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
            draw_counter += delta_time;
            if(draw_counter > draw_interval) {
                on_draw();
                draw_counter = 0;
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
    void engine::on_draw() {}
    void engine::on_init() {}
	bool engine::on_command(const std::string& cmd) { return false; }
    void engine::on_start() {}
    void engine::on_exit() {}

	//********************************************//
	//* Core Engine class.                       *//
	//********************************************//
	#pragma endregion

	// rge::event

	#pragma region /* rge::camera */
	//********************************************//
	//* Camera class.                            *//
	//********************************************//
	camera::camera() {

	}

	camera::~camera() {

	}

	rge::vec3 camera::get_world_position() const {
		return rge::vec3(0, 0, 0); // TODO
	}
	//********************************************//
	//* Camera class.                            *//
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
	}

	texture::~texture() {

	}

	rge::color texture::sample(float u, float v) {
		// TODO
		return color();
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

	}

	material::~material() {

	}
	//********************************************//
	//* Texture class.                           *//
	//********************************************//
	#pragma endregion

	#pragma region /* rge::render_target */
	//********************************************//
	//* Render Target class.                     *//
	//********************************************//
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

	rge::result renderer::set_target(rge::render_target* target) {
		this->target = target;
		return rge::OK;
	}

	rge::render_target* renderer::get_target() {
		return target;
	}

	void renderer::clear(rge::color color) {
		// TODO
	}
	//********************************************//
	//* Renderer class.                          *//
	//********************************************//
	#pragma endregion

	#pragma region /* rge::renderer2d */
	//********************************************//
	//* Software Renderer 2D class.              *//
	//********************************************//
	renderer2d::renderer2d() {

	}

	renderer2d::~renderer2d() {

	}

	void renderer2d::Draw(const rge::texture& texture, const rge::rect& dest) {
		if(!texture.get_on_cpu()) return;
		
	}

	void renderer2d::Draw(const rge::texture& texture, const rge::rect& dest, const rge::rect& src) {
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
	renderer3d::renderer3d() {
		view = matrix4x4::identity();
		projection = matrix4x4::identity();
	}

	renderer3d::~renderer3d() {

	}

	void renderer3d::set_view(const rge::matrix4x4& view_matrix) {
		view = view_matrix;
	}

	void renderer3d::set_projection(const rge::matrix4x4& projection_matrix) {
		projection = projection_matrix;
	}

	rge::vec4 renderer3d::project_vertex(const rge::vec3& v) {
		// TODO
		return vec4();
	}

	void renderer3d::draw(
		const std::vector<rge::vec3>& vertices,
		const std::vector<int>& triangles,
		const std::vector<rge::vec3>& normals,
		const std::vector<rge::vec2>& uvs,
		const rge::material& material,
		const rge::camera& camera)
	{
		for(int i = 0; i < triangles.size(); i += 3) {
			rge::vec4 proj_v1 = project_vertex(vertices[triangles[i]]);
			rge::vec4 proj_v2 = project_vertex(vertices[triangles[i+1]]);
			rge::vec4 proj_v3 = project_vertex(vertices[triangles[i+2]]);

			if(/* Check if all three projected vertices are within homogeneous clip bounds. */
				proj_v1.x >= -1 && proj_v1.x <= 1 && proj_v1.y >= -1 && proj_v1.y <= 1 &&
				proj_v2.x >= -1 && proj_v2.x <= 1 && proj_v2.y >= -1 && proj_v2.y <= 1 &&
				proj_v3.x >= -1 && proj_v3.x <= 1 && proj_v3.y >= -1 && proj_v3.y <= 1
			) {
				rge::vec3 proj_tri_normal = rge::vec3::cross(proj_v2 - proj_v1, proj_v3 - proj_v1);
				rge::vec3 proj_tri_center = (proj_v1 + proj_v2 + proj_v3) / 3;

				if(rge::vec3::dot(proj_tri_normal, proj_tri_center - camera.get_world_position()) <= 0) {
					// Normalize our projected vertices so that they are in the range
					// Between 0 and 1 (instead of -1 and 1).
					rge::vec2 normalized_v1 = rge::vec2((proj_v1.x + 1) / 2.0F, (proj_v1.y + 1) / 2.0F);
					rge::vec2 normalized_v2 = rge::vec2((proj_v2.x + 1) / 2.0F, (proj_v2.y + 1) / 2.0F);
					rge::vec2 normalized_v3 = rge::vec2((proj_v3.x + 1) / 2.0F, (proj_v3.y + 1) / 2.0F);

					// Multiply our normalized vertex positions by the render target size
					// to get their position in texture space (or if we were rendering
					// to the screen - screen space).
					float w = (float)get_target()->get_width();
					float h = (float)get_target()->get_height();
					rge::vec4 texturespace_v1 = rge::vec4(normalized_v1.x * w, normalized_v1.y * h, proj_v1.z, proj_v1.w);
					rge::vec4 texturespace_v2 = rge::vec4(normalized_v2.x * w, normalized_v2.y * h, proj_v2.z, proj_v2.w);
					rge::vec4 texturespace_v3 = rge::vec4(normalized_v3.x * w, normalized_v3.y * h, proj_v3.z, proj_v3.w);

					// Draw the triangle interpolated between the three vertices,
					// using the colours calculated for these vertices based
					// on the triangle indices.
					draw_interpolated_triangle(
						texturespace_v1,
						texturespace_v2,
						texturespace_v3,
						vertices[triangles[i]],
						vertices[triangles[i+1]],
						vertices[triangles[i+2]],
						normals[triangles[i]],
						normals[triangles[i+1]],
						normals[triangles[i+2]],
						uvs[triangles[i]],
						uvs[triangles[i+1]],
						uvs[triangles[i+2]],
						material,
						camera.get_world_position()
					);
				}
			}
		}
	}

	void renderer3d::draw_interpolated_triangle(
		const rge::vec4& r_v1,
		const rge::vec4& r_v2,
		const rge::vec4& r_v3,
		const rge::vec3& w_v1,
		const rge::vec3& w_v2,
		const rge::vec3& w_v3,
		const rge::vec3& w_n1,
		const rge::vec3& w_n2,
		const rge::vec3& w_n3,
		const rge::vec2& t_uv1,
		const rge::vec2& t_uv2,
		const rge::vec2& t_uv3,
		const rge::material& material,
		const rge::vec3& camera_position
	) {
		int x, y, p;
		float denom;
		float weight_v1, weight_v2, weight_v3;
		float depth;
		rge::vec3 v;
		rge::vec3 n;
		rge::vec2 uv;
		rge::color diffuse;
		rge::color source;
		rge::color destination;

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

		// Loop through every pixel in the bounding rect.
		for(y = y_min; y <= y_max; ++y) {
			for(x = x_min; x <= x_max; ++x) {
				// Calculate the weights w1, w2 and w3 for the barycentric
				// coordinates based on the positions of the three vertices.
				denom = (r_v2.y - r_v3.y) * (r_v1.x - r_v3.x) + (r_v3.x - r_v2.x) * (r_v1.y - r_v3.y);
				weight_v1 = ((r_v2.y - r_v3.y) * (x - r_v3.x) + (r_v3.x - r_v2.x) * (y - r_v3.y)) / denom;
				weight_v2 = ((r_v3.y - r_v1.y) * (x - r_v3.x) + (r_v1.x - r_v3.x) * (y - r_v3.y)) / denom;
				weight_v3 = 1 - weight_v1 - weight_v2;

				// If w1, w2 and w3 are >= 0, we are inside the triangle (or
				// on an edge, but either way, render the pixel).
				if(weight_v1 >= 0 && weight_v2 >= 0 && weight_v3 >= 0) {
					// Calculate the position in our buffer based on our x and y values.
					p = x + (y * get_target()->get_width());

					// Calculate the depth value of this pixel.
					depth = r_v1.z * weight_v1 + r_v2.z * weight_v2 + r_v3.z * weight_v3;

					// If the depth value is less than what is currently in the
					// depth buffer for this pixel.
					if(depth < 1000) { // TODO: Depth buffer
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
						source = calculate_blinn_phong(v, n, diffuse, material.specular, material.shininess, camera_position, lights);
						source.a = diffuse.a;

						// Write color to render target.
						// TODO: frameBuffer[bufferPosition] = sourcePixelColour;

						// Update the depth buffer with this depth value.
						// TODO
					}
				}
			}
		}
	}

	rge::color renderer3d::calculate_blinn_phong(
		const rge::vec3& position,
		const rge::vec3& normal,
		const rge::color& diffuse,
		const rge::color& specular,
		float shininess,
		const rge::vec3& camera_position,
		const std::vector<rge::light*>& lights
	) {
		rge::color color;

		return color;
	}
	//********************************************//
	//* Software Renderer 3D class.              *//
	//********************************************//
	#pragma endregion

	namespace platform {

		#pragma region /* rge::platform::window */
		//********************************************//
		//* Window class.                            *//
		//********************************************//
		#ifdef SYS_WINDOWS
		#include <windows.h>
		class window_impl {
		public:
			window_impl(rge::platform::window* window) {
				this->window = window;
			}

			~window_impl() {

			}

		public:
			int width, height;
			rge::platform::window* window;
		};
		#elif SYS_LINUX
		class window_impl {
		public:
			window_impl(rge::platform::window* window) {
				this->window = window;
			}

			~window_impl() {

			}

		public:
			int width, height;
			rge::platform::window* window;
		};
		#elif SYS_MACOSX
		class window_impl {
		public:
			window_impl(rge::platform::window* window) {
				this->window = window;
			}

			~window_impl() {

			}

		public:
			int width, height;
			rge::platform::window* window;
		};
		#endif

		window::window() {
			impl = new window_impl(this);
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
}

#endif /* RGE_IMPL */