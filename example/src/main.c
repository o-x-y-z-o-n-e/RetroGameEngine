#include "engine.h"

#include <math.h>
#include <stdio.h>

#define TEST_COMP 100


static registry_t* test_reg;
static entity_t* test_entity;

// TEST
static float test_counter = 0;


typedef struct test_t {
	entity_t* owner;
	float counter;
} test_t;


//------------------------------------------------------------------------------


static void on_add_test(void* cmp, entity_t* entity) {
	test_t* data = (test_t*)cmp;

	data->owner = entity;
	data->counter = 0;
}


//------------------------------------------------------------------------------


static void on_update_test(void* cmp, float delta) {
	test_t* data = (test_t*)cmp;

	data->counter += delta;

	transform_t* t = (transform_t*)get_component_of_type(data->owner, TYPE_TRANSFORM);
	
	t->location.y = (int32_t)(sinf(data->counter) * 64);
	t->location.x = (int32_t)(cosf(data->counter) * 64);
}


//------------------------------------------------------------------------------


static void on_core_update(float delta) {
	test_counter += delta;
	uint8_t c = (uint8_t)(((sinf(test_counter) + 1.0F) / 2.0F) * 255);
	set_clear_color(COLOR_RGB(255 - c, c, 255 - c));
}


//------------------------------------------------------------------------------


static void button_pressed(rge_key_t key) {
	if(key == KEY_A) {
		log_info("%f", test_counter);
	}
}


//------------------------------------------------------------------------------


int main() {
	log_info("Example Starting...");

	if(!init_core()) {
		log_error("Could not initialize core!");
		return 0;
	}

	set_title_window("Example App");
	set_on_button_down(button_pressed);
	set_on_core_update(on_core_update);

	test_reg = create_registry(TEST_COMP, sizeof(test_t));
	set_on_add(test_reg, on_add_test);
	set_on_update(test_reg, on_update_test);

	test_entity = create_entity();
	create_component(test_entity, test_reg);

	sprite_t* test_sprite = create_sprite(test_entity, 0);
	set_texture(test_sprite, load_texture("res/test.png"));
	set_sprite_centered(test_sprite, true);

	create_transform(test_entity);

	start_core();

	return 0;
}