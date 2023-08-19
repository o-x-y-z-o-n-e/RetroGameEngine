#ifndef RGE_DEF
#define RGE_DEF

#define RGE_VERSION 0001

#include <cstdint>
#include <cstring>
#include <string>
#include <chrono>
#include <thread>
#include <iostream>
#include <functional>

namespace rge {
	class engine;
	class texture;
	namespace platform {
		class window;
	}

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
				handled |= func(static_cast<const T&>(&(*this)));
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

	#pragma region /* rge::math */
	//********************************************//
	//* Math Module.                             *//
	//********************************************//
	namespace math {

		float lerp(float a, float b, float t);

	}
	//********************************************//
	//* Math Module.                             *//
	//********************************************//
	#pragma endregion

	#pragma region /* rge::color */
	//********************************************//
	//* Color struct.                            *//
	//********************************************//
	struct color {

	public:
		color(float r, float g, float b);
		color(float r, float g, float b, float a);

	public:
		float r, g, b, a;

	public:
		static color lerp(const color& a, const color& b, float t);

	};
	//********************************************//
	//* Color struct.                            *//
	//********************************************//
	#pragma endregion

	#pragma region /* rge::texture */
	//********************************************//
	//* Texture class.                           *//
	//********************************************//
	class texture {

	public:
		texture();
		~texture();

	private:
		int width;
		int height;

	};
	//********************************************//
	//* Texture class.                           *//
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

	};
	//********************************************//
	//* Renderer class.                          *//
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

	#pragma region /* rge::texture */
	//********************************************//
	//* Texture class.                           *//
	//********************************************//
	
	texture::texture() {

	}

	texture::~texture() {

	}

	//********************************************//
	//* Texture class.                           *//
	//********************************************//
	#pragma endregion

	#pragma region /* rge::renderer */
	//********************************************//
	//* Renderer class.                          *//
	//********************************************//
	
	renderer::renderer() {

	}

	renderer::~renderer() {

	}

	//********************************************//
	//* Renderer class.                          *//
	//********************************************//
	#pragma endregion

	namespace platform {

		#pragma region /* rge::platform::window */
		//********************************************//
		//* Window class.                            *//
		//********************************************//
		#ifdef SYS_WINDOWS
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