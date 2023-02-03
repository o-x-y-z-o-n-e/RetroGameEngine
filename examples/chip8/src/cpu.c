/*
   https://en.wikipedia.org/wiki/CHIP-8
*/

#include "rge.h"
#include <stdio.h>

#define KEYS_OFFSET 0x000
#define FONT_OFFSET 0x00F
#define STACK_OFFSET 0xEA0
#define DISPLAY_OFFSET 0xF00
#define START_OFFSET 0x200


static uint8_t memory[0x1000];
static uint8_t* keys = memory + KEYS_OFFSET;
static uint8_t* font = memory + FONT_OFFSET;
static uint16_t* stack = memory + STACK_OFFSET;
static uint8_t* display = memory + DISPLAY_OFFSET;


static uint16_t pc;
static uint8_t sc;

static uint16_t I = START_OFFSET;
static uint8_t V[16];

static uint8_t delay;
static uint8_t sound;

static float ms_counter;

static bool get_pixel(uint8_t x, uint8_t y) {
	uint8_t s = x / 8;
	uint16_t o = y * 64;
	uint8_t b = (0x80 >> (x % 8));

	return display[o + s] & b;
}

static void set_pixel(uint8_t x, uint8_t y, bool set) {
	uint8_t s = x / 8;
	uint16_t o = y * 64;
	uint8_t b = (0x80 >> (x % 8));

	if(set) {
		display[o + s] |= b;
	} else {
		display[o + s] &= ~b;
	}
}

static void display_screen() {
	for(int x = 0; x < 64; x++) {
		for(int y = 0; y < 32; y++) {
			if(get_pixel(x, y)) {
				rge_renderer_set_pixel(x, y, COLOR_RGB(255, 255, 255));
			} else {
				rge_renderer_set_pixel(x, y, COLOR_RGB(60, 60, 60));
			}
		}
	}

	rge_window_refresh();
}

// Calls machine code routine (RCA 1802 for COSMAC VIP) at address NNN. Not necessary for most ROMs.
static void op_0NNN(uint16_t nnn) {
	return;
}

// Clears the screen.
static void op_00E0() {
	for(int i = 0; i < 256; i++)
		display[i] = 0;

	display_screen();
}

// Returns from a subroutine.
static void op_00EE() {
	sc--;
	pc = stack[sc];
	stack[sc] = 0;
}

// Jumps to address NNN.
static void op_1NNN(uint16_t nnn) {
	pc = nnn;
}

// Calls subroutine at NNN.
static void op_2NNN(uint16_t nnn) {
	stack[sc] = pc;
	sc++;
	pc = nnn;
}

// Skips the next instruction if VX equals NN (usually the next instruction is a jump to skip a code block).
static void op_3XNN(uint8_t x, uint8_t nn) {
	if(V[x] == nn) pc += 2;
}

// Skips the next instruction if VX does not equal NN (usually the next instruction is a jump to skip a code block).
static void op_4XNN(uint8_t x, uint8_t nn) {
	if(V[x] != nn) pc += 2;
}

// Skips the next instruction if VX equals VY (usually the next instruction is a jump to skip a code block).
static void op_5XY0(uint8_t x, uint8_t y) {
	if(V[x] == V[y]) pc += 2;
}

// Sets VX to NN.
static void op_6XNN(uint8_t x, uint8_t nn) {
	V[x] = nn;
}

// Adds NN to VX (carry flag is not changed).
static void op_7XNN(uint8_t x, uint8_t nn) {
	V[x] += nn;
}

// Sets VX to the value of VY.
static void op_8XY0(uint8_t x, uint8_t y) {
	V[x] = V[y];
}

// Sets VX to VX or VY. (bitwise OR operation)
static void op_8XY1(uint8_t x, uint8_t y) {
	V[x] |= V[y];
}

// Sets VX to VX and VY. (bitwise AND operation)
static void op_8XY2(uint8_t x, uint8_t y) {
	V[x] &= V[y];
}

// Sets VX to VX xor VY. (bitwise XOR operation)
static void op_8XY3(uint8_t x, uint8_t y) {
	V[x] ^= V[y];
}

// Adds VY to VX. VF is set to 1 when there's a carry, and to 0 when there is not.
static void op_8XY4(uint8_t x, uint8_t y) {
	uint16_t h = V[x] + V[y];

	V[0xF] = h > 255;
	V[x] += V[y];
}

// VY is subtracted from VX. VF is set to 0 when there's a borrow, and 1 when there is not.
static void op_8XY5(uint8_t x, uint8_t y) {
	V[0xF] = V[y] <= V[x];
	V[x] -= V[y];
}

// Stores the least significant bit of VX in VF and then shifts VX to the right by 1.
static void op_8XY6(uint8_t x, uint8_t y) {
	V[0xF] = V[x] & 0x01;
	V[x] >>= 1;
}

// Sets VX to VY minus VX. VF is set to 0 when there's a borrow, and 1 when there is not.
static void op_8XY7(uint8_t x, uint8_t y) {
	V[0xF] = V[y] >= V[x];
	V[x] = V[y] - V[x];
}

// Stores the most significant bit of VX in VF and then shifts VX to the left by 1.
static void op_8XYE(uint8_t x, uint8_t y) {
	V[0xF] = V[x] >> 7;
	V[x] <<= 1;
}

// Skips the next instruction if VX does not equal VY. (Usually the next instruction is a jump to skip a code block);
static void op_9XY0(uint8_t x, uint8_t y) {
	if(V[x] != V[y]) pc += 2;
}

// Sets I to the address NNN.
static void op_ANNN(uint16_t nnn) {
	I = nnn;
}

// Jumps to the address NNN plus V0.
static void op_BNNN(uint16_t nnn) {
	pc = nnn + V[0];
}

// Sets VX to the result of a bitwise and operation on a random number (Typically: 0 to 255) and NN.
static void op_CXNN(uint8_t x, uint8_t nn) {
	// TODO: rand()
	V[x] = 0 & nn;
}

/* Draws a sprite at coordinate(VX, VY) that has a width of 8 pixels and a height of N pixels.
   Each row of 8 pixels is read as bit - coded starting from memory location I; I value does not change after the execution of this instruction.
   As described above, VF is set to 1 if any screen pixels are flipped from set to unset when the sprite is drawn, and to 0 if that does not happen.
*/
static void op_DXYN(uint8_t x, uint8_t y, uint8_t n) {
	uint8_t px = V[x];
	uint8_t py = V[y];

	V[0xF] = 0;

	for(int r = 0; r < n; r++) {
		uint8_t sy = (py + r) % 32;

		for(int c = 0; c < 8; c++) {
			// If pixel is set in sprite..
			if(memory[I + r] & (0x80 >> c)) {
				uint8_t sx = (px + c) % 64;
				
				if(get_pixel(sx, sy)) {
					V[0xF] = 1;
					set_pixel(sx, sy, 0);
				} else {
					set_pixel(sx, sy, 1);
				}
			}
		}
	}

	display_screen();
}

// Skips the next instruction if the key stored in VX is pressed (usually the next instruction is a jump to skip a code block).
static void op_EX9E(uint8_t x) {
	if(keys[V[x]]) pc += 2;
}

// Skips the next instruction if the key stored in VX is not pressed (usually the next instruction is a jump to skip a code block).
static void op_EXA1(uint8_t x) {
	if(!keys[V[x]]) pc += 2;
}

// Sets VX to the value of the delay timer.
static void op_FX07(uint8_t x) {
	V[x] = delay;
}

// A key press is awaited, and then stored in VX (blocking operation, all instruction halted until next key event).
static void op_FX0A(uint8_t x) {
	for(int i = 0; i < 16; i++) {
		if(keys[i]) {
			V[x] = i;
			return;
		}
	}

	// Halt.
	pc -= 2;
}

// Sets the delay timer to VX.
static void op_FX15(uint8_t x) {
	delay = V[x];
}

// Sets the sound timer to VX.
static void op_FX18(uint8_t x) {
	sound = V[x];
}

// Adds VX to I. VF is not affected.
static void op_FX1E(uint8_t x) {
	I += V[x];
}

// Sets I to the location of the sprite for the character in VX. Characters 0-F (in hexadecimal) are represented by a 4x5 font.
static void op_FX29(uint8_t x) {
	I = FONT_OFFSET + (V[x] & 0x0F) * 5;
}

// Stores the binary-coded decimal representation of VX, with the hundreds digit in memory at location in I, the tens digit at location I+1, and the ones digit at location I+2.
static void op_FX33(uint8_t x) {
	memory[I] = V[x] / 100;
	memory[I + 1] = (V[x] / 10) % 10;
	memory[I + 2] = V[x] % 10;
}

// Stores from V0 to VX (including VX) in memory, starting at address I. The offset from I is increased by 1 for each value written, but I itself is left unmodified.
static void op_FX55(uint8_t x) {
	for(int i = 0; i <= x; i++)
		memory[I + i] = V[i];
}

// Fills from V0 to VX (including VX) with values from memory, starting at address I. The offset from I is increased by 1 for each value read, but I itself is left unmodified.
static void op_FX65(uint8_t x) {
	for(int i = 0; i <= x; i++)
		V[i] = memory[I + i];
}

static void decode_0XXX(uint16_t op) {
	uint16_t NNN = op & 0x0FFF;

	switch(op & 0x0FFF) {
		case 0x00E0:
			op_00E0();
			break;

		case 0x00EE:
			op_00EE();
			break;

		default:
			op_0NNN(NNN);
			break;
	}
}

static void decode_8XXX(uint16_t op) {
	uint8_t X = (op & 0x0F00) >> 8;
	uint8_t Y = (op & 0x00F0) >> 4;

	switch(op & 0x000F) {
		case 0x0000:
			op_8XY0(X, Y);
			break;

		case 0x0001:
			op_8XY1(X, Y);
			break;

		case 0x0002:
			op_8XY2(X, Y);
			break;

		case 0x0003:
			op_8XY3(X, Y);
			break;

		case 0x0004:
			op_8XY4(X, Y);
			break;

		case 0x0005:
			op_8XY5(X, Y);
			break;

		case 0x0006:
			op_8XY6(X, Y);
			break;

		case 0x0007:
			op_8XY7(X, Y);
			break;

		case 0x000E:
			op_8XYE(X, Y);
			break;
	}
}

static void decode_EXXX(uint16_t op) {
	uint8_t X = (op & 0x0F00) >> 8;

	switch(op & 0x00FF) {
		case 0x009E:
			op_EX9E(X);
			break;

		case 0x00A1:
			op_EXA1(X);
			break;
	}
}

static void decode_FXXX(uint16_t op) {
	uint8_t X = (op & 0x0F00) >> 8;

	switch(op & 0x00FF) {
		case 0x0007:
			op_FX07(X);
			break;

		case 0x000A:
			op_FX0A(X);
			break;

		case 0x0015:
			op_FX15(X);
			break;

		case 0x0018:
			op_FX18(X);
			break;

		case 0x001E:
			op_FX1E(X);
			break;

		case 0x0029:
			op_FX29(X);
			break;

		case 0x0033:
			op_FX33(X);
			break;

		case 0x0055:
			op_FX55(X);
			break;

		case 0x0065:
			op_FX65(X);
			break;
	}
}

static void decode(uint16_t op) {
	uint16_t NNN = op & 0x0FFF;
	uint8_t NN = op & 0x00FF;
	uint8_t N = op & 0x000F;
	uint8_t X = (op & 0x0F00) >> 8;
	uint8_t Y = (op & 0x00F0) >> 4;

	switch(op & 0xF000) {

		case 0x0000:
			decode_0XXX(op);
			break;

		case 0x1000:
			op_1NNN(NNN);
			break;

		case 0x2000:
			op_2NNN(NNN);
			break;

		case 0x3000:
			op_3XNN(X, NN);
			break;

		case 0x4000:
			op_4XNN(X, NN);
			break;

		case 0x5000:
			op_5XY0(X, Y);
			break;

		case 0x6000:
			op_6XNN(X, NN);
			break;

		case 0x7000:
			op_7XNN(X, NN);
			break;

		case 0x8000:
			decode_8XXX(op);
			break;

		case 0x9000:
			op_9XY0(X, Y);
			break;

		case 0xA000:
			op_ANNN(NNN);
			break;

		case 0xB000:
			op_BNNN(NNN);
			break;

		case 0xC000:
			op_CXNN(X, NN);
			break;

		case 0xD000:
			op_DXYN(X, Y, N);
			break;

		case 0xE000:
			decode_EXXX(op);
			break;

		case 0xF000:
			decode_FXXX(op);
			break;
	}
}

int cpu_init() {
	//font (in hex, aka. 0 to F). 4x5 characters.
	const uint8_t FONT[] = {
		0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
		0x20, 0x60, 0x20, 0x20, 0x70, // 1
		0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
		0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
		0x90, 0x90, 0xF0, 0x10, 0x10, // 4
		0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
		0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
		0xF0, 0x10, 0x20, 0x40, 0x40, // 7
		0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
		0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
		0xF0, 0x90, 0xF0, 0x90, 0x90, // A
		0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
		0xF0, 0x80, 0x80, 0x80, 0xF0, // C
		0xE0, 0x90, 0x90, 0x90, 0xE0, // D
		0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
		0xF0, 0x80, 0xF0, 0x80, 0x80  // F
	};

	for(int l = 0; l < 5 * 0xF; l++)
		font = FONT[l];
	

	FILE* file = fopen("res/IBM Logo.ch8", "rb");
	if(file == NULL) {
		rge_log_info("Cannot access file!");
		return 0;
	}

	fseek(file, 0, SEEK_END);
	int size = ftell(file);
	rewind(file);

	if(size > 4096 - START_OFFSET) {
		rge_log_info("ERROR: File is too large!");
		fclose(file);
		return 0;
	}

	fread(&memory[START_OFFSET], 1, size, file);

	fclose(file);

	return 1;
}

void cpu_tick(int ms_delta) {
	keys[0x0] = rge_input_is_press(RGE_KEY_X);
	keys[0x1] = rge_input_is_press(RGE_KEY_1);
	keys[0x2] = rge_input_is_press(RGE_KEY_2);
	keys[0x3] = rge_input_is_press(RGE_KEY_3);
	keys[0x4] = rge_input_is_press(RGE_KEY_Q);
	keys[0x5] = rge_input_is_press(RGE_KEY_W);
	keys[0x6] = rge_input_is_press(RGE_KEY_E);
	keys[0x7] = rge_input_is_press(RGE_KEY_A);
	keys[0x8] = rge_input_is_press(RGE_KEY_S);
	keys[0x9] = rge_input_is_press(RGE_KEY_D);
	keys[0xA] = rge_input_is_press(RGE_KEY_Z);
	keys[0xB] = rge_input_is_press(RGE_KEY_C);
	keys[0xC] = rge_input_is_press(RGE_KEY_4);
	keys[0xD] = rge_input_is_press(RGE_KEY_R);
	keys[0xE] = rge_input_is_press(RGE_KEY_F);
	keys[0xF] = rge_input_is_press(RGE_KEY_V);

	ms_counter += ms_delta;
	if(ms_counter > 16.66F) {
		ms_counter -= 16.66F;

		if(delay > 0)
			delay--;

		if(sound > 0)
			sound--;
	}

	uint16_t op = ((uint16_t)memory[pc] << 8) | memory[pc + 1];
	pc += 2;

	decode(op);
}