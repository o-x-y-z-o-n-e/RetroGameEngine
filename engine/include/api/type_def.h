#include <stdint.h>

// Abstract types.
typedef struct registry_t registry_t;
typedef struct entity_t entity_t;
typedef struct sprite_t sprite_t;
typedef struct texture_t texture_t;


// Data types.
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


// Component type ID.
#define TYPE_TRANSFORM 0
#define TYPE_SPRITE 1