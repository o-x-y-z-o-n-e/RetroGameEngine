#ifndef _GAME_HPP_
#define _GAME_HPP_

#include "rge.hpp"
#include "platformer.hpp"

#define PPU 16

enum class game_state {
	MAIN_MENU,
	IN_GAME,
	PAUSED,
	END_SCREEN
};

class game : public platformer {
public:
	game();

	void get_default_window_params(std::string& title, int& width, int& height, bool& fullscreen) override;
	void on_init() override;
	void on_start() override;
	void on_update(float delta_time) override;
	void on_render() override;

	static game* get() { return (game*)get_instance(); }
};

#endif /* _GAME_HPP_ */