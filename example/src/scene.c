#include "engine.h"
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
	bkg_0 = create_entity();
	bkg_0_t = create_transform(bkg_0);
	bkg_0_s = create_sprite(bkg_0, 0);

	bkg_1 = create_entity();
	bkg_1_t = create_transform(bkg_1);
	bkg_1_s = create_sprite(bkg_1, 0);

	bkg_2 = create_entity();
	bkg_2_t = create_transform(bkg_2);
	bkg_2_s = create_sprite(bkg_2, 1);

	flr = create_entity();
	flr_t = create_transform(flr);
	flr_s = create_sprite(flr, 2);

	set_texture(bkg_0_s, load_texture("res/background_0.png"));
	bkg_0_t->location.y = 100;
	bkg_0_t->location.x = -256;

	set_texture(bkg_1_s, load_texture("res/background_1.png"));
	bkg_1_t->location.y = 36;
	bkg_1_t->location.x = -256;

	set_texture(bkg_2_s, load_texture("res/background_2.png"));
	bkg_2_t->location.y = 100;
	bkg_2_t->location.x = -256;

	set_texture(flr_s, load_texture("res/layer_0.png"));
	flr_t->location.y = 100;
	flr_t->location.x = -256;
}


void update_my_scene(float delta) {
	point_t cam_pos = get_camera_location();

	if(is_button_press(KEY_LEFT)) {
		hor -= delta*1.5F;
	}

	if(is_button_press(KEY_RIGHT)) {
		hor += delta*1.5F;
	}

	flr_t->location.x = -256 - float_to_point(hor * 25, 0).x;
	bkg_2_t->location.x = -256 - float_to_point(hor * 10, 0).x;
	bkg_0_t->location.x = -256 - float_to_point(hor * 5, 0).x;
	bkg_1_t->location.x = -256 - float_to_point(hor * 1, 0).x;
}