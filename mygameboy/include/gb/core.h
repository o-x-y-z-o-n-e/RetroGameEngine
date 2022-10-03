#ifndef CORE_H
#define CORE_H

#include <stdbool.h>
#include <stdint.h>

#define LITTLE_ENDIAN

#define FLAGS_ZERO        0b10000000
#define FLAGS_SUBTRACT    0b01000000
#define FLAGS_HALF_CARRY  0b00100000
#define FLAGS_CARRY       0b00010000
#define INTERRUPT_V_BLANK 0b00001
#define INTERRUPT_LCD     0b00010
#define INTERRUPT_TIMER   0b00100
#define INTERRUPT_SERIAL  0b01000
#define INTERRUPT_JOYPAD  0b10000

#define SCREEN_WIDTH 160
#define SCREEN_HEIGHT 144

typedef void (*op_func)();

struct registers_t {
	struct {
		union {
			struct {
			#ifdef LITTLE_ENDIAN
				uint8_t F;
				uint8_t A;
			#else
				uint8_t A;
				uint8_t F;
			#endif
			};
			uint16_t AF;
		};
	};

	struct {
		union {
			struct {
			#ifdef LITTLE_ENDIAN
				uint8_t C;
				uint8_t B;
			#else
				uint8_t B;
				uint8_t C;
			#endif
			};
			uint16_t BC;
		};
	};

	struct {
		union {
			struct {
			#ifdef LITTLE_ENDIAN
				uint8_t E;
				uint8_t D;
			#else
				uint8_t D;
				uint8_t E;
			#endif
			};
			uint16_t DE;
		};
	};

	struct {
		union {
			struct {
			#ifdef LITTLE_ENDIAN
				uint8_t L;
				uint8_t H;
			#else
				uint8_t H;
				uint8_t L;
			#endif
			};
			uint16_t HL;
		};
	};

	uint16_t PC;
	uint16_t SP;

	uint8_t* IF;
	uint8_t  IE;
	bool     IME;

} extern registers;


// ==(CPU)==
void       gb_cpu_delay(int cycles);
int        gb_cpu_delay_get(uint8_t opcode);
int        gb_cpu_delay_ext_get(uint8_t opcode);
op_func    gb_cpu_decode(uint8_t);
op_func    gb_cpu_decode_ext(uint8_t);
void       gb_cpu_flag_set(int flag, bool state);
bool       gb_cpu_flag_get(int flag);
void       gb_cpu_int_flag_set(int interrupt, bool state);
bool       gb_cpu_int_flag_get(int interrupt);
void       gb_cpu_ime_set(bool enabled);
// ==(CPU)==


// ==(PPU - Pixel Processing)==
void       gb_ppu_init();
void       gb_ppu_step(int ms_tick_delta);
void       gb_ppu_close();
// ==(PPU - Pixel Processing)==


// ==(MMU - Memory Access/Mapping)==
void       gb_mmu_init();
void       gb_mmu_close();
void       gb_mmu_load_bank(int i);
uint8_t    gb_mmu_fetch();
uint16_t   gb_mmu_fetch_u16();
void       gb_mmu_write(uint16_t address, uint8_t value);
uint8_t    gb_mmu_read(uint16_t address);
uint8_t*   gb_mmu_location(uint16_t address);
void       gb_mmu_call(uint16_t address);
void       gb_mmu_return();
void       gb_mmu_push(uint16_t value);
void       gb_mmu_pop(uint16_t* reg);
void       gb_mmu_restart(uint8_t value);
// ==(MMU - Memory Access/Mapping)==


// ==(ALU)== (TODO: rename to gb_alu_xx)
//8-Bit Arithmetic
void ADD(uint8_t value);
void ADC(uint8_t value);
void SUB(uint8_t value);
void SBC(uint8_t value);
void AND(uint8_t value);
void OR(uint8_t value);
void XOR(uint8_t value);
void CP(uint8_t value);
void INC(uint8_t* reg);
void DEC(uint8_t* reg);

//16-Bit Arithmetic
void ADD_HL(uint16_t value);
void ADD_SP(int8_t value);
void INC_16(uint16_t* reg);
void DEC_16(uint16_t* reg);

//Extended Bit Operations
void RLC(uint8_t* reg);
void RRC(uint8_t* reg);
void RL(uint8_t* reg);
void RR(uint8_t* reg);
void SLA(uint8_t* reg);
void SRA(uint8_t* reg);
void SWAP(uint8_t* reg);
void SRL(uint8_t* reg);
void BIT(uint8_t* reg, int pos);
void RES(uint8_t* reg, int pos);
void SET(uint8_t* reg, int pos);
// ==(ALU)==

#endif