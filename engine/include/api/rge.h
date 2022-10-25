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
	
	RGE_KEY_ESC = 60,

	RGE_PAD_D_LEFT = 200,
	RGE_PAD_D_UP = 201,
	RGE_PAD_D_RIGHT = 202,
	RGE_PAD_D_DOWN = 203,

	RGE_PAD_WEST = 204,
	RGE_PAD_NORTH = 205,
	RGE_PAD_EAST = 206,
	RGE_PAD_SOUTH = 207,

	RGE_PAD_LS_LEFT = 208,
	RGE_PAD_LS_UP = 209,
	RGE_PAD_LS_RIGHT = 210,
	RGE_PAD_LS_DOWN = 211,

	RGE_PAD_RS_LEFT = 212,
	RGE_PAD_RS_UP = 213,
	RGE_PAD_RS_RIGHT = 214,
	RGE_PAD_RS_DOWN = 215,

	RGE_PAD_LS_AXIS_X = 216,
	RGE_PAD_LS_AXIS_Y = 217,
	RGE_PAD_RS_AXIS_X = 218,
	RGE_PAD_RS_AXIS_Y = 219,

	RGE_PAD_LB = 220,
	RGE_PAD_RB = 221,

	RGE_PAD_LT = 222,
	RGE_PAD_RT = 223,

	RGE_PAD_L3 = 224,
	RGE_PAD_R3 = 225,

	RGE_PAD_OPTIONS = 226,
	RGE_PAD_START = 227
} rge_input_t;


// ===Component Type ID===
#define TYPE_TRANSFORM 0
#define TYPE_SPRITE 1


// ===Core===
/* Initializes RetroGameEngine. This needs to be called before any other api function. */
int rge_core_init();
/* Starts the main game loop. This is a blocking function and will only return once the game loop stops. */
void rge_core_start();
/* Stops the game loop and uninitializes RetroGameEngine. */
void rge_core_close();
/* Set a callback function that is called every game frame. */
void rge_core_set_on_update(void (*func)(float delta));
/* Set a callback function that is called every program loop iteration. (Normally runs more often than on_update). */
void rge_core_set_on_tick(void (*func)(int delta));


// ===Camera===
/* Set the location (x, y) of the camera. */
void rge_camera_set_location(point_t location);
/* Get the location (x, y) of the camera. */
point_t rge_camera_get_location();


// ===Window===
/* Set the display text at the top of the window. */
void rge_window_set_title(const char* title);
/* Force the window to refresh the frame buffer. */
void rge_window_refresh();


// ===View===
/* TODO: Write Description. */
void rge_view_get_size(uint16_t* w, uint16_t* h);
/* TODO: Write Description. */
uint16_t rge_view_get_width();
/* TODO: Write Description. */
uint16_t rge_view_get_height();
/* TODO: Write Description. */
void rge_view_set_size(uint16_t w, uint16_t h);
/* TODO: Write Description. */
void rge_view_set_background(pixel_t color);


// ===Renderer===
/* TODO: Write Description. */
bool rge_renderer_auto_get();
/* TODO: Write Description. */
void rge_renderer_auto_set(bool auto_render);
/* TODO: Write Description. */
void rge_renderer_clear();
/* TODO: Write Description. */
void rge_renderer_set_pixel(uint16_t x, uint16_t y, pixel_t color);


// ===Log===
/* TODO: Write Description. */
void rge_log_info(char* format, ...);
/* TODO: Write Description. */
void rge_log_warning(char* format, ...);
/* TODO: Write Description. */
void rge_log_error(char* format, ...);


// ===Input===
/* TODO: Write Description. */
bool rge_input_is_press(rge_input_t binding);
/* TODO: Write Description. */
bool rge_input_is_click(rge_input_t binding);
/* TODO: Write Description. */
float rge_input_get_axis(rge_input_t binding);
/* TODO: Write Description. */
void rge_input_set_on_down(void(*func)(rge_input_t binding));


// ===Scene===
/* Destroys all entities & components. All registries will be cleared & reset. */
void rge_scene_clear();


// ===Entity===
/* TODO: Write Description. */
entity_t* rge_entity_create();
/* TODO: Write Description. */
void rge_entity_free(entity_t* entity);
/* TODO: Implement & Write Description. */
entity_t* rge_entity_get_child(const entity_t* entity, uint32_t index);
/* TODO: Implement & Write Description. */
uint32_t rge_entity_get_child_count(const entity_t* entity);
/* TODO: Implement & Write Description. */
uint32_t rge_entity_get_child_index(const entity_t* entity, const entity_t* child);
/* TODO: Implement & Write Description. */
bool rge_entity_add_child(entity_t* entity, entity_t* child);
/* TODO: Implement & Write Description. */
bool rge_entity_remove_child(entity_t* entity, entity_t* child);
/* TODO: Implement & Write Description. */
bool rge_entity_set_parent(entity_t* entity, entity_t* parent);


// ===Component===
/* TODO: Write Description. */
void* rge_component_create(entity_t* entity, registry_t* registry);
/* TODO: Write Description. */
void rge_component_remove(entity_t* entity, uint8_t index);
/* TODO: Write Description. */
void* rge_component_get(const entity_t* entity, uint8_t index);
/* TODO: Write Description. */
uint8_t rge_component_get_count(const entity_t* entity);
/* TODO: Write Description. */
uint8_t rge_component_get_index(const entity_t* entity, const void* component);
/* TODO: Write Description. */
void* rge_component_get_from_type(const entity_t* entity, uint8_t type);


// ===Texture===
/* TODO: Write Description. */
texture_t* rge_texture_load(const char* path);
/* TODO: Implement & Write Description. */
void rge_texture_free(texture_t* texture);
/* TODO: Write Description. */
void rge_texture_get_size(const texture_t* texture, uint16_t* w, uint16_t* h);
/* TODO: Write Description. */
uint16_t rge_texture_get_width(const texture_t* texture);
/* TODO: Write Description. */
uint16_t rge_texture_get_height(const texture_t* texture);


// ===Audio===
/* TODO: Write Description. */
audio_t* rge_audio_load(const char* path);
/* TODO: Write Description. */
void rge_audio_free(audio_t* clip);
/* TODO: Write Description. */
float rge_audio_get_length(const audio_t* clip);
/* TODO: Write Description. */
void rge_audio_play(const audio_t* clip);
/* TODO: Write Description. */
void rge_audio_stop_all();


// ===Registry===
/* TODO: Write Description. */
registry_t* rge_registry_create(uint8_t type, size_t element_size);
/* TODO: Write Description. */
registry_t* rge_registry_get_from_type(uint8_t type);
/* TODO: Write Description. */
void rge_registry_set_on_add(registry_t* registry, void (*func)(void* cmp, entity_t* entity));
/* TODO: Write Description. */
void rge_registry_set_on_update(registry_t* registry, void (*func)(void* cmp, float delta));
/* TODO: Write Description. */
void rge_registry_set_on_dispose(registry_t* registry, void (*func)(void* cmp));


// ===Sprite===
/* TODO: Write Description. */
sprite_t* rge_sprite_create(entity_t* entity, int16_t layer);
/* TODO: Write Description. */
void rge_sprite_set_texture(sprite_t* sprite, texture_t* texture);
/* TODO: Write Description. */
texture_t* rge_sprite_get_texture(const sprite_t* sprite);
/* TODO: Write Description. */
void rge_sprite_set_section(sprite_t* sprite, rect_t section);
/* TODO: Write Description. */
void rge_sprite_set_centered(sprite_t* sprite, bool centered);
/* TODO: Write Description. */
void rge_sprite_set_offset(sprite_t* sprite, point_t offset);
/* TODO: Write Description. */
rect_t rge_sprite_get_section(const sprite_t* sprite);
/* TODO: Write Description. */
bool rge_sprite_is_centered(const sprite_t* sprite);
/* TODO: Write Description. */
point_t rge_sprite_get_offset(const sprite_t* sprite);


// ===Transform===
/* Creates a transform component & associates it with the given entity. */
transform_t* rge_transform_create(entity_t* entity);


// ===Misc===
/* Quantizes & converts the x, y coordinates to a point_t struct. */
point_t rge_float_to_point(float x, float y);

#endif