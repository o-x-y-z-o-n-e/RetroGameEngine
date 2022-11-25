#include "api/rge.h"
#include "ecs/sprite.h"
#include "assets/texture.h"
#include "core/renderer.h"
#include "util/bit_flags.h"

#define SPRITE_FLAG_CENTERED 0


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

	registry_t* registry = rge_renderer_get_layer(layer)->sprites;
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