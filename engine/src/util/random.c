#include "api/rge.h"

const int A = 48271;
const int M = 2147483647; // 2^31 - 1

#define F(X) ((A*X)%M)


//------------------------------------------------------------------------------


typedef struct random_t {
	uint32_t x;
} random_t;


//------------------------------------------------------------------------------


random_t rge_random_create(uint32_t seed) {
	return (random_t) {
		seed
	};
}


//------------------------------------------------------------------------------


int32_t rge_random_next_i32(random_t* rng) {
	rng->x = F(rng->x);
	return rng->x % 65536;
}


//------------------------------------------------------------------------------


int16_t rge_random_next_i32(random_t* rng) {
	rng->x = F(rng->x);
	return rng->x % 256;
}


//------------------------------------------------------------------------------


int8_t rge_random_next_i32(random_t* rng) {
	rng->x = F(rng->x);
	return (int8_t)rng->x;
}


//------------------------------------------------------------------------------


uint32_t rge_random_next_u32(random_t* rng) {
	rng->x = F(rng->x);
	return rng->x;
}


//------------------------------------------------------------------------------


uint16_t rge_random_next_u16(random_t* rng) {
	rng->x = F(rng->x);
	return rng->x % 65536;
}


//------------------------------------------------------------------------------


uint8_t rge_random_next_u8(random_t* rng) {
	rng->x = F(rng->x);
	return rng->x % 256;
}


//------------------------------------------------------------------------------


float rge_random_next_f(random_t* rng) {
	uint16_t i = rge_random_next_u16(rng);
	return (float)i / 65535.0F;
}