#include "gb/core.h"

// ==(8-Bit ALU)==
void ADD(uint8_t value) {
	uint16_t sum = registers.A + value;

	gb_cpu_flag_set(FLAGS_ZERO, (sum & 0x00FF) == 0);
	gb_cpu_flag_set(FLAGS_SUBTRACT, false);
	// <-
	gb_cpu_flag_set(FLAGS_CARRY, sum & 0xFF00);

	registers.A = (uint8_t)(sum & 0x00FF);

	// \/
	gb_cpu_flag_set(FLAGS_HALF_CARRY, ((registers.A & 0x0F) + (value & 0x0F)) > 0x0F);
}

void ADC(uint8_t value) {
	uint8_t carry = (gb_cpu_flag_get(FLAGS_CARRY) ? 1 : 0);
	uint16_t sum = registers.A + value + carry;

	gb_cpu_flag_set(FLAGS_ZERO, (sum & 0x00FF) == 0);
	gb_cpu_flag_set(FLAGS_SUBTRACT, false);
	gb_cpu_flag_set(FLAGS_HALF_CARRY, ((registers.A & 0x0F) + ((value + carry) & 0x0F)) & 0xF0);
	gb_cpu_flag_set(FLAGS_CARRY, sum & 0xFF00);

	registers.A = (uint8_t)(sum & 0x00FF);
}

void SUB(uint8_t value) {
	gb_cpu_flag_set(FLAGS_HALF_CARRY, (registers.A & 0x0F) < (value & 0x0F));
	gb_cpu_flag_set(FLAGS_CARRY, registers.A < value);

	registers.A -= value;

	gb_cpu_flag_set(FLAGS_ZERO, registers.A == 0);
	gb_cpu_flag_set(FLAGS_SUBTRACT, true);
}

void SBC(uint8_t value) {
	uint8_t carry = (gb_cpu_flag_get(FLAGS_CARRY) ? 1 : 0);

	gb_cpu_flag_set(FLAGS_HALF_CARRY, (registers.A & 0x0F) < ((value + carry) & 0x0F));
	gb_cpu_flag_set(FLAGS_CARRY, registers.A < value + carry);

	registers.A -= (value + carry);

	gb_cpu_flag_set(FLAGS_ZERO, registers.A == 0);
	gb_cpu_flag_set(FLAGS_SUBTRACT, true);
}

void AND(uint8_t value) {
	registers.A &= value;
	gb_cpu_flag_set(FLAGS_ZERO, registers.A == 0);
	gb_cpu_flag_set(FLAGS_HALF_CARRY, true);
	gb_cpu_flag_set(FLAGS_SUBTRACT | FLAGS_CARRY, false);
}

void OR(uint8_t value) {
	registers.A |= value;
	gb_cpu_flag_set(FLAGS_ZERO, registers.A == 0);
	gb_cpu_flag_set(FLAGS_SUBTRACT | FLAGS_HALF_CARRY | FLAGS_CARRY, false);
}

void XOR(uint8_t value) {
	registers.A ^= value;
	gb_cpu_flag_set(FLAGS_ZERO, registers.A == 0);
	gb_cpu_flag_set(FLAGS_SUBTRACT | FLAGS_HALF_CARRY | FLAGS_CARRY, false);
}

void CP(uint8_t value) {
	gb_cpu_flag_set(FLAGS_ZERO, registers.A == value);
	gb_cpu_flag_set(FLAGS_SUBTRACT, true);
	gb_cpu_flag_set(FLAGS_HALF_CARRY, (registers.A & 0x0F) < (value & 0x0F));
	gb_cpu_flag_set(FLAGS_CARRY, registers.A < value);
}

void INC(uint8_t* reg) {
	gb_cpu_flag_set(FLAGS_HALF_CARRY, (*reg & 0x0F) == 0x0F);

	(*reg)++;

	gb_cpu_flag_set(FLAGS_ZERO, *reg == 0);
	gb_cpu_flag_set(FLAGS_SUBTRACT, false);
}

void DEC(uint8_t* reg) {
	gb_cpu_flag_set(FLAGS_HALF_CARRY, (*reg & 0x0F) == 0x00);

	(*reg)--;

	gb_cpu_flag_set(FLAGS_ZERO, *reg == 0);
	gb_cpu_flag_set(FLAGS_SUBTRACT, true);

}
// ==(8-Bit ALU)==


// ==(16-Bit Arithmetic)==
void ADD_HL(uint16_t value) {
	uint32_t sum = registers.HL + value;

	gb_cpu_flag_set(FLAGS_CARRY, sum & 0xFFFF0000);

	registers.HL = (uint16_t)(sum & 0xFFFF);

	gb_cpu_flag_set(FLAGS_HALF_CARRY, (registers.HL & 0x0F) + (value & 0x0F) > 0x0F);

	gb_cpu_flag_set(FLAGS_SUBTRACT, false);
}

void ADD_SP(int8_t value) {
	uint32_t sum = registers.SP + value;

	gb_cpu_flag_set(FLAGS_CARRY, sum & 0xFFFF0000);

	registers.SP = (uint16_t)(sum & 0xFFFF);

	gb_cpu_flag_set(FLAGS_HALF_CARRY, (registers.SP & 0x0F) + (value & 0x0F) > 0x0F);

	gb_cpu_flag_set(FLAGS_ZERO | FLAGS_SUBTRACT, false);
}

void INC_16(uint16_t* reg) {
	(*reg)++;
}

void DEC_16(uint16_t* reg) {
	(*reg)--;
}
// ==(16-Bit Arithmetic)==


// ==(0xCB Bit Functions)==
void RLC(uint8_t* reg) {
	int carry = *reg & 0x80;

	gb_cpu_flag_set(FLAGS_CARRY, carry);

	*reg <<= 1;
	*reg |= carry >> 7;

	gb_cpu_flag_set(FLAGS_ZERO, *reg == 0);
	gb_cpu_flag_set(FLAGS_SUBTRACT | FLAGS_HALF_CARRY, false);
}

void RRC(uint8_t* reg) {
	int carry = *reg & 0x01;

	gb_cpu_flag_set(FLAGS_CARRY, carry);

	*reg >>= 1;
	*reg |= carry << 7;

	gb_cpu_flag_set(FLAGS_ZERO, *reg == 0);
	gb_cpu_flag_set(FLAGS_SUBTRACT | FLAGS_HALF_CARRY, false);
}

void RL(uint8_t* reg) {
	int carry = gb_cpu_flag_get(FLAGS_CARRY) ? 0x01 : 0x00;

	gb_cpu_flag_set(FLAGS_CARRY, *reg & 0x80);

	*reg <<= 1;
	*reg |= carry;

	gb_cpu_flag_set(FLAGS_ZERO, *reg == 0);
	gb_cpu_flag_set(FLAGS_SUBTRACT | FLAGS_HALF_CARRY, false);
}

void RR(uint8_t* reg) {
	int carry = gb_cpu_flag_get(FLAGS_CARRY) ? 0x80 : 0x00;

	gb_cpu_flag_set(FLAGS_CARRY, *reg & 0x01);

	*reg >>= 1;
	*reg |= carry;

	gb_cpu_flag_set(FLAGS_ZERO, *reg == 0);
	gb_cpu_flag_set(FLAGS_SUBTRACT | FLAGS_HALF_CARRY, false);
}

void SLA(uint8_t* reg) {
	gb_cpu_flag_set(FLAGS_CARRY, *reg & 0x80);

	*reg <<= 1;

	gb_cpu_flag_set(FLAGS_ZERO, *reg == 0);
	gb_cpu_flag_set(FLAGS_SUBTRACT | FLAGS_HALF_CARRY, false);
}

void SRA(uint8_t* reg) {
	gb_cpu_flag_set(FLAGS_CARRY, *reg & 0x01);

	int sign = *reg & 0x80;

	*reg >>= 1;
	*reg |= sign;

	gb_cpu_flag_set(FLAGS_ZERO, *reg == 0);
	gb_cpu_flag_set(FLAGS_SUBTRACT | FLAGS_HALF_CARRY, false);
}

void SWAP(uint8_t* reg) {
	uint8_t swap = (*reg << 4);
	swap += (*reg >> 4);
	*reg = swap;

	gb_cpu_flag_set(FLAGS_ZERO, swap == 0);
	gb_cpu_flag_set(FLAGS_SUBTRACT | FLAGS_HALF_CARRY | FLAGS_CARRY, false);
}

void SRL(uint8_t* reg) {
	gb_cpu_flag_set(FLAGS_CARRY, *reg & 0x01);

	*reg >>= 1;

	gb_cpu_flag_set(FLAGS_ZERO, *reg == 0);
	gb_cpu_flag_set(FLAGS_SUBTRACT | FLAGS_HALF_CARRY, false);
}

void BIT(uint8_t* reg, int pos) {
	gb_cpu_flag_set(FLAGS_ZERO, ~(*reg & (0x01 << pos)));
	gb_cpu_flag_set(FLAGS_SUBTRACT, false);
	gb_cpu_flag_set(FLAGS_HALF_CARRY, true);
}

void RES(uint8_t* reg, int pos) {
	*reg &= ~(0x01 << pos);
}

void SET(uint8_t* reg, int pos) {
	*reg |= (0x01 << pos);
}
// ==(0xCB Bit Functions)==