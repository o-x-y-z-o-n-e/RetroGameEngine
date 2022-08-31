#ifndef TYPES_H
#define TYPES_H

#include <stdint.h>

typedef struct point_t {
    int32_t x, y;
} point_t;

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

#endif