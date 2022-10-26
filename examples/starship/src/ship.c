#include "rge.h"
#include "game.h"
#include "ship.h"

#define MOVE_INTERVAL 0.0075F


//------------------------------------------------------------------------------


static registry_t* reg;
static ship_t* ship;


//------------------------------------------------------------------------------


void ship_init() {
	reg = rge_registry_create(SHIP_COMP, sizeof(ship_t));

	entity_t* entity = rge_entity_create();
	ship = (ship_t*)rge_component_create(entity, reg);
	ship->entity = entity;
	ship->transform = rge_transform_create(entity);
	ship->sprite = rge_sprite_create(entity, 10);

	rge_sprite_set_texture(ship->sprite, rge_texture_load("res/ship.png"));
	rge_sprite_set_centered(ship->sprite, true);

	entity_t* sub_e = rge_entity_create();
	transform_t* sub_t = rge_transform_create(sub_e);
	sprite_t* sub_s = rge_sprite_create(sub_e, 12);

	rge_sprite_set_texture(sub_s, rge_texture_load("res/ship.png"));
	rge_sprite_set_centered(sub_s, true);
	sub_t->location.x = 64;

	rge_entity_set_parent(sub_e, entity);
}


//------------------------------------------------------------------------------


static void ship_move() {
	point_t position = ship->transform->location;

	if(rge_input_is_press(RGE_KEY_RIGHT))
		position.x += 1;
	
	if(rge_input_is_press(RGE_KEY_LEFT))
		position.x -= 1;

	if(rge_input_is_press(RGE_KEY_UP))
		position.y += 1;

	if(rge_input_is_press(RGE_KEY_DOWN))
		position.y -= 1;

	if(rge_input_get_axis(RGE_PAD_LS_AXIS_X) > 0.5F)
		position.x += 1;

	if(rge_input_get_axis(RGE_PAD_LS_AXIS_X) < -0.5F)
		position.x -= 1;

	if(rge_input_get_axis(RGE_PAD_LS_AXIS_Y) > 0.5F)
		position.y += 1;

	if(rge_input_get_axis(RGE_PAD_LS_AXIS_Y) < -0.5F)
		position.y -= 1;

	if(position.x - 8 < -WINDOW_WIDTH / 2)
		position.x = -WINDOW_WIDTH / 2 + 8;
	else if(position.x + 8 > WINDOW_WIDTH / 2)
		position.x = WINDOW_WIDTH / 2 - 8;

	if(position.y - 8 < -WINDOW_HEIGHT / 2)
		position.y = -WINDOW_HEIGHT / 2 + 8;
	else if(position.y + 8 > WINDOW_HEIGHT / 2)
		position.y = WINDOW_HEIGHT / 2 - 8;

	ship->transform->location = position;
}


//------------------------------------------------------------------------------


void ship_update(float delta) {
	ship->move_counter += delta;

	if(ship->move_counter > MOVE_INTERVAL) {
		ship->move_counter -= MOVE_INTERVAL;
		ship_move();
	}

	if(rge_input_is_click(RGE_PAD_SOUTH))
		rge_log_info("shoot");
}