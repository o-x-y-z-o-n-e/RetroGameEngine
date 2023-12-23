 #ifndef _SPACESHIP_HPP_
#define _SPACESHIP_HPP_

#include "rge.hpp"

class spaceship {

public:
	spaceship();
	~spaceship();
	void reset();
	void draw();
	void update(float delta_time);

	float get_radius() { return 0.5F; }
	rge::vec2 get_position() { return transform->get_global_position(); }

	void damage(int amount);

	float get_cooldown() const;

private:
	rge::input::action shoot_action;
	rge::input::action horizontal_action;
	rge::input::action vertical_action;
	int shoot_side;
	float shoot_counter;
	float shoot_cooldown;
	float flame_counter;
	int flame_index;
	int dmg_count;
	float dmg_t;
	int health;
	std::vector<rge::texture::ptr> textures;
	std::vector<rge::texture::ptr> flames;
	std::vector<rge::texture::ptr> health_textures;
	rge::sprite::ptr health_sprite;
	rge::sprite::ptr flame_sprite;
	rge::transform::ptr transform;
	rge::sprite::ptr sprite;
	rge::vec2 velocity;
	rge::vec2 move_input;
};

#endif /* _SPACESHIP_HPP_ */