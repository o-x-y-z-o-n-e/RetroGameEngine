#ifndef RGE_DEF
#define RGE_DEF

#define RGE_VERSION 0001

#include <cstdint>
#include <cstring>
#include <string>
#include <chrono>
#include <thread>
#include <iostream>

namespace rge {

    enum result { FAIL = 0, OK = 1 };

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
        int get_frame_rate();
        bool get_is_running();

    public:
        float update_interval;
        float physics_interval;
        float draw_interval;

    private:
        void loop();

    private:
        bool is_running;
        std::thread thread;
        float update_counter;
        float physics_counter;
        float draw_counter;
        std::chrono::time_point<std::chrono::system_clock> time_stamp_1, time_stamp_2;
        int frame_counter;
        int frame_rate;
        float frame_timer;

    };
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

    engine::~engine() {}

    rge::result engine::init() {
        log::info("Initialising RGE...");
        // TODO
        
        on_init();
        return OK;
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

        return OK;
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
            return OK;
        
        if(cmd == "exit" || cmd == "quit") {
            exit();
        } else if(cmd == "rge_version") {
			log::info("RGE VERSION: 0.00.1");
		} else {
			return FAIL;
		}

        return OK;
    }

    rge::result engine::exit() {
        is_running = false;

        // TODO
        
        on_exit();
        return OK;
    }

    int engine::get_frame_rate() {
        return frame_rate;
    }

    bool engine::get_is_running() {
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

}

#endif /* RGE_IMPL */