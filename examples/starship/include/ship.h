#ifndef SHIP_H
#define SHIP_H

#include "rge.h"

typedef struct ship_t {
	entity_t* entity;
	transform_t* transform;
	sprite_t* sprite;

	int health;
	float move_counter;
} ship_t;

void ship_init();
void ship_update(float delta);

#endif