#ifndef RGE_H
#define RGE_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>


// ===Windows Entry-Point Stuff===
#ifdef _WIN32
#ifdef WIN_MAIN
#include <windows.h>


// Forward declaration of the real main() function.
int main(int argc, char** argv);

// win32 entry point for release mode (DesktopApp).
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nShowCmd) {
	return main(0, NULL);
}
#endif
#endif


// ===Defines===
#define COLOR_RGB(R, G, B) (pixel_t){R, G, B, 255}
#define COLOR_RGBA(R, G, B, A) (pixel_t){R, G, B, A}


// ===Abstract Types===
typedef struct registry_t registry_t;
typedef struct entity_t entity_t;
typedef struct sprite_t sprite_t;
typedef struct texture_t texture_t;
typedef struct audio_t audio_t;


// ===Data Types===
typedef struct point_t {
	int32_t x, y;
} point_t;

typedef struct transform_t {
	point_t location;
} transform_t;

typedef struct rect_t {
	union {
		struct {
			int32_t x;
			int32_t y;
		};
		point_t origin;
	};
	union {
		struct {
			int32_t width;
			int32_t height;
		};
		point_t size;
	};
} rect_t;

typedef struct pixel_t {
	union {
		struct {
			uint8_t r, g, b, a;
		};
		uint32_t p;
	};
} pixel_t;

typedef enum {
	KEY_A = 1,
	KEY_B = 2,
	KEY_C = 3,
	KEY_D = 4,
	KEY_E = 5,
	KEY_F = 6,
	KEY_G = 7,
	KEY_H = 8,
	KEY_I = 9,
	KEY_J = 10,
	KEY_K = 11,
	KEY_L = 12,
	KEY_M = 13,
	KEY_N = 14,
	KEY_O = 15,
	KEY_P = 16,
	KEY_Q = 17,
	KEY_R = 18,
	KEY_S = 19,
	KEY_T = 20,
	KEY_U = 21,
	KEY_V = 22,
	KEY_W = 23,
	KEY_X = 24,
	KEY_Y = 25,
	KEY_Z = 26,

	KEY_SPACE = 27,
	KEY_CAPS = 28,
	KEY_RETURN = 29,
	
	KEY_0 = 30,
	KEY_1 = 31,
	KEY_2 = 32,
	KEY_3 = 33,
	KEY_4 = 34,
	KEY_5 = 35,
	KEY_6 = 36,
	KEY_7 = 37,
	KEY_8 = 38,
	KEY_9 = 39,

	KEY_LEFT = 40,
	KEY_UP = 41,
	KEY_RIGHT = 42,
	KEY_DOWN = 43,

	KEY_LSHIFT = 44,
	KEY_LCTRL = 45,
	KEY_LALT = 46,

	KEY_RSHIFT = 47,
	KEY_RCTRL = 48,
	KEY_RALT = 49,

	KEY_TAB = 50,
	KEY_BACKSPACE = 51,

	KEY_ESC = 60
} rge_key_t;


// ==Component Type ID===
#define TYPE_TRANSFORM 0
#define TYPE_SPRITE 1


// ===Core===
int rge_core_init();
void rge_core_start();
void rge_core_close();
void rge_core_set_on_update(void (*func)(float delta));


// ===Camera===
void rge_camera_set_location(point_t location);
point_t rge_camera_get_location();


// ===Window===
void rge_window_set_title(const char* title);


// ===View===
void rge_view_get_size(uint16_t* w, uint16_t* h);
uint16_t rge_view_get_width();
uint16_t rge_view_get_height();
void rge_view_set_size(uint16_t w, uint16_t h);
void rge_view_set_background(pixel_t color);


// ===Log===
void rge_log_info(char* format, ...);
void rge_log_warning(char* format, ...);
void rge_log_error(char* format, ...);


// ===Input===
bool rge_input_is_press(rge_key_t key);
bool rge_input_is_click(rge_key_t key);
void rge_input_set_on_down(void(*func)(rge_key_t key));


// ===Entity===
entity_t* rge_entity_create();
void rge_entity_free(entity_t* entity);
entity_t* rge_entity_get_child(const entity_t* entity, uint32_t index);
uint32_t rge_entity_get_child_count(const entity_t* entity);
uint32_t rge_entity_get_child_index(const entity_t* entity, const entity_t* child);
bool rge_entity_add_child(entity_t* entity, entity_t* child);
bool rge_entity_remove_child(entity_t* entity, entity_t* child);
bool rge_entity_set_parent(entity_t* entity, entity_t* parent);


// ===Component===
void* rge_component_create(entity_t* entity, registry_t* registry);
void rge_component_remove(entity_t* entity, uint8_t index);
void* rge_component_get(const entity_t* entity, uint8_t index);
uint8_t rge_component_get_count(const entity_t* entity);
uint8_t rge_component_get_index(const entity_t* entity, const void* component);
void* rge_component_get_from_type(const entity_t* entity, uint8_t type);


// ===Texture===
texture_t* rge_texture_load(const char* path);
/* TODO: IMPLEMENT */ void rge_texture_free(texture_t* texture);
void rge_texture_get_size(const texture_t* texture, uint16_t* w, uint16_t* h);
uint16_t rge_texture_get_width(const texture_t* texture);
uint16_t rge_texture_get_height(const texture_t* texture);


// ===Audio===
audio_t* rge_audio_load(const char* path);
void rge_audio_free(audio_t* clip);
float rge_audio_get_length(const audio_t* clip);
void rge_audio_play(const audio_t* clip);
void rge_audio_stop_all();


// ===Registry===
registry_t* rge_registry_create(uint8_t type, size_t element_size);
registry_t* rge_registry_get_from_type(uint8_t type);
void rge_registry_set_on_add(registry_t* registry, void (*func)(void* cmp, entity_t* entity));
void rge_registry_set_on_update(registry_t* registry, void (*func)(void* cmp, float delta));
void rge_registry_set_on_dispose(registry_t* registry, void (*func)(void* cmp));


// ===Sprite===
sprite_t* rge_sprite_create(entity_t* entity, int16_t layer);
void rge_sprite_set_texture(sprite_t* sprite, texture_t* texture);
texture_t* rge_sprite_get_texture(const sprite_t* sprite);
void rge_sprite_set_section(sprite_t* sprite, rect_t section);
void rge_sprite_set_centered(sprite_t* sprite, bool centered);
void rge_sprite_set_offset(sprite_t* sprite, point_t offset);
rect_t rge_sprite_get_section(const sprite_t* sprite);
bool rge_sprite_is_centered(const sprite_t* sprite);
point_t rge_sprite_get_offset(const sprite_t* sprite);


// ===Transform===
transform_t* rge_transform_create(entity_t* entity);


// ===Misc===
point_t rge_float_to_point(float x, float y);

#endif