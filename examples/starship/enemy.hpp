#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "rge.hpp"

class enemy {
public:
	typedef std::pair<enemy*, bool> entry;
	typedef std::vector<entry> table;

public:
	enemy();

	void gen_starting_params();
	void reset();
	void update(float delta_time);
	void draw();

	bool overlap(rge::vec2 point) const;
	void take_damage();

	static enemy* create();
	static void destroy(enemy* ins);
	static void destroy_all();
	static void update_all(float delta_time);
	static void draw_all();
	static bool overlap_all(rge::vec2 point, std::function<void(enemy& e)> on_overlap);

private:
	int type;
	int health;
	int dmg_count;
	float dmg_t;
	float anim_counter;
	rge::transform::ptr transform;
	rge::sprite::ptr sprite;
	static table pool;
};

#endif /* ENEMY_HPP */