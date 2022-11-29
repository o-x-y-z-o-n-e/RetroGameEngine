#include "api/rge.h"
#include "ecs/sprite.h"
#include "ecs/scene.h"
#include "assets/texture.h"
#include "core/renderer.h"
#include "util/bit_flags.h"

#include <stdlib.h>

#define SPRITE_FLAG_CENTERED 0

#define MAX_LAYERS 10
#define START_SPRITES_COUNT 100
#define INCREASE_SPRITES_STEP 100

typedef struct layer_t layer_t;
typedef struct layer_t {
	int16_t level;
	registry_t* sprites;
	layer_t* next;
} layer_t;


static layer_t* layers_head;


//------------------------------------------------------------------------------


static void on_sprite_add(void* cmp, entity_t* entity) {
	((sprite_t*)(cmp))->owner = entity;
}


//------------------------------------------------------------------------------


static void rge_sprite_draw(void* component, float delta) {
	sprite_t* sprite = (sprite_t*)component;
	point_t location = rge_transform_get_global(sprite->owner);

	rge_renderer_draw_atlas(sprite->texture, location.x + sprite->offset.x, location.y - sprite->offset.y, sprite->section);
}


//------------------------------------------------------------------------------


static layer_t* init_layer(int16_t level) {
	layer_t* layer = malloc(sizeof(layer_t));
	if(layer == NULL)
		return NULL;

	layer->level = level;
	layer->sprites = rge_registry_init(TYPE_SPRITE, sizeof(sprite_t), START_SPRITES_COUNT, INCREASE_SPRITES_STEP);
	layer->next = NULL;

	rge_registry_set_on_add(layer->sprites, on_sprite_add);
	rge_registry_set_on_update(layer->sprites, rge_sprite_draw);

	return layer;
}


//------------------------------------------------------------------------------


static layer_t* create_layer(int16_t level) {
	// Insert at head.
	if(level < layers_head->level) {
		layer_t* layer = init_layer(level);
		layer->next = layers_head;
		layers_head = layer;
		return layer;
	}

	layer_t* previous = NULL;
	layer_t* current = layers_head;
	while(current != NULL) {
		if(level == current->level)
			return current;

		if(previous == NULL)
			goto next;

		// Insert in between.
		if(level > previous->level && level < current->level) {
			layer_t* layer = init_layer(level);
			layer->next = previous->next;
			previous->next = layer;
			return layer;
		}

	next:
		previous = current;
		current = current->next;
	}

	// Insert at tail.
	layer_t* layer = init_layer(level);
	previous->next = layer;
	return layer;
}


//------------------------------------------------------------------------------


static layer_t* get_layer(int16_t level) {
	layer_t* current = layers_head;
	while(current != NULL) {
		if(current->level == level)
			return current;

		current = current->next;
	}
	return create_layer(level);
}


//------------------------------------------------------------------------------


int rge_sprite_init() {
	layers_head = init_layer(0);

	return 1;
}


//------------------------------------------------------------------------------


void rge_sprite_draw_all() {
	layer_t* current = layers_head;
	while(current != NULL) {
		rge_registry_update(current->sprites, 0);
		current = current->next;
	}
}


//------------------------------------------------------------------------------


void rge_sprite_set_texture(sprite_t* sprite, texture_t* texture) {
	if(texture == NULL) {
		sprite->texture = NULL;
		sprite->section = (rect_t){ 0, 0, 0, 0 };
		return;
	}

	sprite->texture = texture;

	rge_sprite_set_section(
		sprite,
		(rect_t) {
			0,
			0,
			texture->width,
			texture->height
		}
	);
}


//------------------------------------------------------------------------------


sprite_t* rge_sprite_create(entity_t* entity, int16_t layer) {
	if(entity == NULL) {
		rge_log_error("No entity passed");
		return NULL;
	}

	registry_t* registry = get_layer(layer)->sprites;
	if(registry == NULL)
		return NULL;

	return (sprite_t*)rge_component_create(entity, registry);
}


//------------------------------------------------------------------------------


texture_t* rge_sprite_get_texture(const sprite_t* sprite) {
	if(sprite == NULL)
		return NULL;

	return sprite->texture;
}


//------------------------------------------------------------------------------


void rge_sprite_set_section(sprite_t* sprite, rect_t section) {
	if(sprite == NULL)
		return;

	if(sprite->texture == NULL) {
		sprite->section = (rect_t){ 0,0,0,0 };
		return;
	}

	if(section.x < 0)
		section.x = 0;

	if(section.y < 0)
		section.y = 0;

	if(section.x + section.width > sprite->texture->width)
		section.width = sprite->texture->width - section.x;

	if(section.y + section.height > sprite->texture->height)
		section.height = sprite->texture->height - section.y;

	sprite->section = section;

	// Re-center sprite, if needed.
	if(rge_bit_get(sprite->flags, SPRITE_FLAG_CENTERED))
		rge_sprite_set_centered(sprite, true);
}


//------------------------------------------------------------------------------


void rge_sprite_set_centered(sprite_t* sprite, bool centered) {
	if(centered) {
		sprite->flags = rge_bit_set(sprite->flags, SPRITE_FLAG_CENTERED);
		sprite->offset.x = -sprite->section.width / 2;
		sprite->offset.y = -sprite->section.height / 2;
	} else {
		sprite->flags = rge_bit_clear(sprite->flags, SPRITE_FLAG_CENTERED);
		sprite->offset = (point_t){ 0, 0 };
	}
}


//------------------------------------------------------------------------------


void rge_sprite_set_offset(sprite_t* sprite, point_t offset) {
	sprite->flags = rge_bit_clear(sprite->flags, SPRITE_FLAG_CENTERED);
	sprite->offset = offset;
}


//------------------------------------------------------------------------------


rect_t rge_sprite_get_section(const sprite_t* sprite) {
	return sprite->section;
}


//------------------------------------------------------------------------------


bool rge_sprite_is_centered(const sprite_t* sprite) {
	return rge_bit_get(sprite->flags, SPRITE_FLAG_CENTERED);
}


//------------------------------------------------------------------------------


point_t rge_sprite_get_offset(const sprite_t* sprite) {
	return sprite->offset;
}