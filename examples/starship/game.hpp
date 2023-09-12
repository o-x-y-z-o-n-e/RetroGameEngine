#ifndef _GAME_HPP_
#define _GAME_HPP_

#include "rge.hpp"
#include "spaceship.hpp"

enum class game_state {
	MAIN_MENU,
	IN_GAME,
	END_SCREEN
};

class game : public rge::engine {
public:
	game();

	void get_default_window_params(std::string& title, int& width, int& height, bool& fullscreen) override;
	void on_init() override;
	void on_start() override;
	void on_update(float delta_time) override;
	void on_render() override;

private:
	void scroll_bg(float delta_time);

private:
	rge::texture::ptr bg_texture;
	rge::sprite::ptr bg_sprite_0;
	rge::sprite::ptr bg_sprite_1;
	float bg_scroll_0;
	float bg_scroll_1;
	game_state state;
	rge::camera::ptr camera;
	spaceship* ship;
};

#endif /* _GAME_HPP_ */