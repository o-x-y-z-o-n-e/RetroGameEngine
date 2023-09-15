#ifndef _GAME_HPP_
#define _GAME_HPP_

#include "rge.hpp"
#include "spaceship.hpp"
#include "asteroid.hpp"
#include "laser.hpp"
#include "explode.hpp"

#define BACKGROUND_LAYER -1.0F
#define SPACESHIP_LAYER 0.0F
#define ASTEROID_LAYER 0.5F
#define LASER_LAYER 0.75F
#define UI_LAYER 0.9F

enum class game_state {
	MAIN_MENU,
	IN_GAME,
	PAUSED,
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

	void start_game();
	void end(bool win);

	rge::random* get_random() { return &random; }
	static game* get() { return (game*)get_instance(); }

	spaceship* get_ship();

private:
	void scroll_bg(float delta_time);
	void set_rand_asteroid_wait();

private:
	rge::random random;
	rge::sprite::ptr title_sprite;
	rge::sprite::ptr win_sprite;
	rge::sprite::ptr lose_sprite;
	rge::sprite::ptr pause_sprite;
	rge::sprite::ptr press_key_sprite_0;
	rge::sprite::ptr press_key_sprite_1;
	rge::sprite::ptr bg_sprite_0;
	rge::sprite::ptr bg_sprite_1;
	rge::texture::ptr meter;
	float bg_scroll_0;
	float bg_scroll_1;
	float asteroid_countdown;
	game_state state;
	rge::camera::ptr camera;
	spaceship* ship;
	float progress;
	bool did_win;
};

#endif /* _GAME_HPP_ */