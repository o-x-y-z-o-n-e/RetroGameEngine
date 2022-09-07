#ifndef ENGINE_H
#define ENGINE_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>


// Windows entry point stuff.
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


// Defines.
#define COLOR_RGB(R, G, B) (pixel_t){R, G, B, 255}
#define COLOR_RGBA(R, G, B, A) (pixel_t){R, G, B, A}


#include "type_def.h"
#include "input_def.h"
#include "entity_def.h"


// Misc functions.
int init_core();
void start_core();
void close_core();
void set_on_core_update(void (*func)(float delta));
void log_info(const char* format, ...);
void log_warning(const char* format, ...);
void log_error(const char* format, ...);
bool is_button_press(rge_key_t key);
bool is_button_click(rge_key_t key);
void set_on_button_down(void(*func)(rge_key_t key));
void set_viewport_size(uint16_t width, uint16_t height);
uint16_t get_view_width();
uint16_t get_view_height();
void set_title_window(const char* title);
void set_camera_location(point_t location);
point_t get_camera_location();
void set_clear_color(pixel_t color);
texture_t* load_texture(const char* path);
void get_texture_size(const texture_t* texture, uint16_t* w, uint16_t* h);
uint16_t get_texture_width(const texture_t* texture);
uint16_t get_texture_height(const texture_t* texture);
registry_t* create_registry(uint8_t type, size_t element_size);
registry_t* get_registry_of_type(uint8_t type);
void set_on_add(registry_t* registry, void (*func)(void* cmp, entity_t* entity));
void set_on_update(registry_t* registry, void (*func)(void* cmp, float delta));
sprite_t* create_sprite(entity_t* entity, int16_t layer);
void set_texture(sprite_t* sprite, texture_t* texture);
texture_t* get_texture(const sprite_t* sprite);
void set_sprite_section(sprite_t* sprite, rect_t section);
void set_sprite_centered(sprite_t* sprite, bool centered);
void set_sprite_offset(sprite_t* sprite, point_t offset);
transform_t* create_transform(entity_t* entity);
point_t float_to_point(float x, float y);

#endif