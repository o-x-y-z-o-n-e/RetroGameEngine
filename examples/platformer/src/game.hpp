#ifndef _GAME_HPP_
#define _GAME_HPP_

// Libraries.
#include "rge.hpp"

// Structure.
#include "world.hpp"
#include "level.hpp"
#include "area.hpp"
#include "tile_set.hpp"
#include "tile_map.hpp"

// Entities.
#include "entity.hpp"
#include "pawn.hpp"
#include "player.hpp"

// Render settings.
#define PPU 1
#define FRAME_WIDTH 320
#define FRAME_HEIGHT 180
#define BACKGROUND rge::color(0.063F, 0.071F, 0.11F)

// Game declaration.
class game : public rge::engine {
public:
	game();

	void get_default_window_params(std::string& title, int& width, int& height, bool& fullscreen) override;
	void on_init() override;
	void on_start() override;
	void on_update(float delta_time) override;
	void on_render() override;

	static inline game* get() { return (game*)get_instance(); }
	static inline world* get_world() { return get()->world_obj; }

private:
	world* world_obj;
	rge::camera::ptr camera;
	rge::render_target::ptr render;
};

#define WORLD_EXISTS (game::get_world() != nullptr)

#endif /* _GAME_HPP_ */