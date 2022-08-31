#ifndef ENGINE_H
#define ENGINE_H

#include <stdint.h>


// Windows entry point stuff.
#ifdef _WIN32
#include <windows.h>

// Forward declaration of the real main() function.
int main(int argc, char** argv);

// win32 entry point for release mode (DesktopApp).
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nShowCmd) {
	return main(0, NULL);
}

#endif


// Data types.
typedef struct registry_t registry_t;
typedef struct entity_t entity_t;
typedef struct sprite_t sprite_t;
typedef struct texture_t texture_t;
typedef struct point_t { int32_t x, y; } point_t;
typedef struct transform_t { point_t location; } transform_t;
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

// Defines.
#define TYPE_TRANSFORM 0
#define TYPE_SPRITE 1

#define COLOR_RGB(R, G, B) (pixel_t){R, G, B, 255}
#define COLOR_RGBA(R, G, B, A) (pixel_t){R, G, B, A}


// Core functions.
int init_core();
void start_core();
void close_core();
void set_on_core_update(void (*func)(float delta));


// Debug functions.
void log_info(const char* format, ...);
void log_warning(const char* format, ...);
void log_error(const char* format, ...);


// Window functions.
void set_viewport_size(uint16_t width, uint16_t height);
uint16_t get_view_width();
uint16_t get_view_height();


// Rendering functions.
void set_camera_location(point_t location);
point_t get_camera_location();
void set_clear_color(pixel_t color);


// Texture functions.
texture_t* load_texture(const char* path);
void get_texture_size(const texture_t* texture, uint16_t* w, uint16_t* h);
uint16_t get_texture_width(const texture_t* texture);
uint16_t get_texture_height(const texture_t* texture);


// Entity functions.
uint8_t get_component_count(const entity_t* entity);
entity_t* create_entity();
void free_entity(entity_t* entity);


// Registry functions.
registry_t* create_registry(uint8_t type, size_t element_size);
registry_t* get_registry_of_type(uint8_t type);
void set_on_add(registry_t* registry, void (*func)(void* cmp, entity_t* entity));
void set_on_update(registry_t* registry, void (*func)(void* cmp, float delta));


// Component functions.
void* create_component(entity_t* entity, registry_t* registry);
void remove_component(entity_t* entity, uint8_t i);
uint8_t get_component_index(const entity_t* entity, void* component);
void* get_component_of_type(const entity_t* entity, uint8_t type);
void* get_component(const entity_t* entity, uint8_t i);


// Sprite functions.
sprite_t* create_sprite(entity_t* entity, uint8_t layer);
void set_texture(sprite_t* sprite, texture_t* texture);
texture_t* get_texture(const sprite_t* sprite);
void set_sprite_section(sprite_t* sprite, rect_t section);


// Transform functions.
transform_t* create_transform(entity_t* entity);

#endif