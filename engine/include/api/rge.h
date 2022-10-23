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
	RGE_KEY_A = 1,
	RGE_KEY_B = 2,
	RGE_KEY_C = 3,
	RGE_KEY_D = 4,
	RGE_KEY_E = 5,
	RGE_KEY_F = 6,
	RGE_KEY_G = 7,
	RGE_KEY_H = 8,
	RGE_KEY_I = 9,
	RGE_KEY_J = 10,
	RGE_KEY_K = 11,
	RGE_KEY_L = 12,
	RGE_KEY_M = 13,
	RGE_KEY_N = 14,
	RGE_KEY_O = 15,
	RGE_KEY_P = 16,
	RGE_KEY_Q = 17,
	RGE_KEY_R = 18,
	RGE_KEY_S = 19,
	RGE_KEY_T = 20,
	RGE_KEY_U = 21,
	RGE_KEY_V = 22,
	RGE_KEY_W = 23,
	RGE_KEY_X = 24,
	RGE_KEY_Y = 25,
	RGE_KEY_Z = 26,
	
	RGE_KEY_SPACE = 27,
	RGE_KEY_CAPS = 28,
	RGE_KEY_RETURN = 29,
	
	RGE_KEY_0 = 30,
	RGE_KEY_1 = 31,
	RGE_KEY_2 = 32,
	RGE_KEY_3 = 33,
	RGE_KEY_4 = 34,
	RGE_KEY_5 = 35,
	RGE_KEY_6 = 36,
	RGE_KEY_7 = 37,
	RGE_KEY_8 = 38,
	RGE_KEY_9 = 39,
	
	RGE_KEY_LEFT = 40,
	RGE_KEY_UP = 41,
	RGE_KEY_RIGHT = 42,
	RGE_KEY_DOWN = 43,
	
	RGE_KEY_LSHIFT = 44,
	RGE_KEY_LCTRL = 45,
	RGE_KEY_LALT = 46,
	
	RGE_KEY_RSHIFT = 47,
	RGE_KEY_RCTRL = 48,
	RGE_KEY_RALT = 49,
	
	RGE_KEY_TAB = 50,
	RGE_KEY_BACKSPACE = 51,
	
	RGE_KEY_ESC = 60
} rge_key_t;


// ==Component Type ID===
#define TYPE_TRANSFORM 0
#define TYPE_SPRITE 1


// ===Core===
int rge_core_init();
void rge_core_start();
void rge_core_close();
void rge_core_set_on_update(void (*func)(float delta));
void rge_core_set_on_tick(void (*func)(int delta));


// ===Camera===
void rge_camera_set_location(point_t location);
point_t rge_camera_get_location();


// ===Window===
void rge_window_set_title(const char* title);
void rge_window_refresh();


// ===View===
void rge_view_get_size(uint16_t* w, uint16_t* h);
uint16_t rge_view_get_width();
uint16_t rge_view_get_height();
void rge_view_set_size(uint16_t w, uint16_t h);
void rge_view_set_background(pixel_t color);


// ===Renderer===
bool rge_renderer_auto_get();
void rge_renderer_auto_set(bool auto_render);
void rge_renderer_clear();
void rge_renderer_set_pixel(uint16_t x, uint16_t y, pixel_t color);


// ===Log===
void rge_log_info(char* format, ...);
void rge_log_warning(char* format, ...);
void rge_log_error(char* format, ...);


// ===Input===
bool rge_input_is_press(rge_key_t key);
bool rge_input_is_click(rge_key_t key);
void rge_input_set_on_down(void(*func)(rge_key_t key));


// ===Scene===
void rge_scene_clear();


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