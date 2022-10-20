#include "rge.h"
#include "scene.h"

static entity_t* bkg_0;
static transform_t* bkg_0_t;
static sprite_t* bkg_0_s;

static entity_t* bkg_1;
static transform_t* bkg_1_t;
static sprite_t* bkg_1_s;

static entity_t* bkg_2;
static transform_t* bkg_2_t;
static sprite_t* bkg_2_s;

static entity_t* flr;
static transform_t* flr_t;
static sprite_t* flr_s;

static float hor = 0;

void setup_my_scene() {
	bkg_0 = rge_entity_create();
	bkg_0_t = rge_transform_create(bkg_0);
	bkg_0_s = rge_sprite_create(bkg_0, 0);
	
	bkg_1 = rge_entity_create();
	bkg_1_t = rge_transform_create(bkg_1);
	bkg_1_s = rge_sprite_create(bkg_1, 0);

	bkg_2 = rge_entity_create();
	bkg_2_t = rge_transform_create(bkg_2);
	bkg_2_s = rge_sprite_create(bkg_2, 1);

	flr = rge_entity_create();
	flr_t = rge_transform_create(flr);
	flr_s = rge_sprite_create(flr, 2);

	rge_sprite_set_texture(bkg_0_s, rge_texture_load("res/background_0.png"));
	bkg_0_t->location.y = 100;
	bkg_0_t->location.x = -256;
	
	rge_sprite_set_texture(bkg_1_s, rge_texture_load("res/background_1.png"));
	bkg_1_t->location.y = 36;
	bkg_1_t->location.x = -256;

	rge_sprite_set_texture(bkg_2_s, rge_texture_load("res/background_2.png"));
	bkg_2_t->location.y = 100;
	bkg_2_t->location.x = -256;

	rge_sprite_set_texture(flr_s, rge_texture_load("res/layer_0.png"));
	flr_t->location.y = 100;
	flr_t->location.x = -256;
	
}


void update_my_scene(float delta) {
	point_t cam_pos = rge_camera_get_location();

	if(rge_input_is_press(KEY_LEFT)) {
		hor -= delta*1.5F;
	}

	if(rge_input_is_press(KEY_RIGHT)) {
		hor += delta*1.5F;
	}

	flr_t->location.x = -256 - rge_float_to_point(hor * 25, 0).x;
	bkg_2_t->location.x = -256 - rge_float_to_point(hor * 10, 0).x;
	bkg_0_t->location.x = -256 - rge_float_to_point(hor * 5, 0).x;
	bkg_1_t->location.x = -256 - rge_float_to_point(hor * 1, 0).x;
}