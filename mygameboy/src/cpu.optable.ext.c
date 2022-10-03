#include "gb/core.h"


// (0x00)
void RLC_B() {
	RLC(&registers.B);
}

// (0x01)
void RLC_C() {
	RLC(&registers.C);
}

// (0x02)
void RLC_D() {
	RLC(&registers.D);
}

// (0x03)
void RLC_E() {
	RLC(&registers.E);
}

// (0x04)
void RLC_H() {
	RLC(&registers.H);
}

// (0x05)
void RLC_L() {
	RLC(&registers.L);
}

// (0x06)
void RLC_0xHL() {
	RLC(gb_mmu_location(registers.HL));
}

// (0x07)
void RLC_A() {
	RLC(&registers.A);
}

// (0x08)
void RRC_B() {
	RRC(&registers.B);
}

// (0x09)
void RRC_C() {
	RRC(&registers.C);
}

// (0x0A)
void RRC_D() {
	RRC(&registers.D);
}

// (0x0B)
void RRC_E() {
	RRC(&registers.E);
}

// (0x0C)
void RRC_H() {
	RRC(&registers.H);
}

// (0x0D)
void RRC_L() {
	RRC(&registers.L);
}

// (0x0E)
void RRC_0xHL() {
	RRC(gb_mmu_location(registers.HL));
}

// (0x0F)
void RRC_A() {
	RRC(&registers.A);
}

// (0x10)
void RL_B() {
	RL(&registers.B);
}

// (0x11)
void RL_C() {
	RL(&registers.C);
}

// (0x12)
void RL_D() {
	RL(&registers.D);
}

// (0x13)
void RL_E() {
	RL(&registers.E);
}

// (0x14)
void RL_H() {
	RL(&registers.H);
}

// (0x15)
void RL_L() {
	RL(&registers.L);
}

// (0x16)
void RL_0xHL() {
	RL(gb_mmu_location(registers.HL));
}

// (0x17)
void RL_A() {
	RL(&registers.A);
}

// (0x18)
void RR_B() {
	RR(&registers.B);
}

// (0x19)
void RR_C() {
	RR(&registers.C);
}

// (0x1A)
void RR_D() {
	RR(&registers.D);
}

// (0x1B)
void RR_E() {
	RR(&registers.E);
}

// (0x1C)
void RR_H() {
	RR(&registers.H);
}

// (0x1D)
void RR_L() {
	RR(&registers.L);
}

// (0x1E)
void RR_0xHL() {
	RR(gb_mmu_location(registers.HL));
}

// (0x1F)
void RR_A() {
	RR(&registers.A);
}

// (0x20)
void SLA_B() {
	SLA(&registers.B);
}

// (0x21)
void SLA_C() {
	SLA(&registers.C);
}

// (0x22)
void SLA_D() {
	SLA(&registers.D);
}

// (0x23)
void SLA_E() {
	SLA(&registers.E);
}

// (0x24)
void SLA_H() {
	SLA(&registers.H);
}

// (0x25)
void SLA_L() {
	SLA(&registers.L);
}

// (0x26)
void SLA_0xHL() {
	SLA(gb_mmu_location(registers.HL));
}

// (0x27)
void SLA_A() {
	SLA(&registers.A);
}

// (0x28)
void SRA_B() {
	SRA(&registers.B);
}

// (0x29)
void SRA_C() {
	SRA(&registers.C);
}

// (0x2A)
void SRA_D() {
	SRA(&registers.D);
}

// (0x2B)
void SRA_E() {
	SRA(&registers.E);
}

// (0x2C)
void SRA_H() {
	SRA(&registers.H);
}

// (0x2D)
void SRA_L() {
	SRA(&registers.L);
}

// (0x2E)
void SRA_0xHL() {
	SRA(gb_mmu_location(registers.HL));
}

// (0x2F)
void SRA_A() {
	SRA(&registers.A);
}

// (0x30)
void SWAP_B() {
	SWAP(&registers.B);
}

// (0x31)
void SWAP_C() {
	SWAP(&registers.C);
}

// (0x32)
void SWAP_D() {
	SWAP(&registers.D);
}

// (0x33)
void SWAP_E() {
	SWAP(&registers.E);
}

// (0x34)
void SWAP_H() {
	SWAP(&registers.H);
}

// (0x35)
void SWAP_L() {
	SWAP(&registers.L);
}

// (0x36)
void SWAP_0xHL() {
	SWAP(gb_mmu_location(registers.HL));
}

// (0x37)
void SWAP_A() {
	SWAP(&registers.A);
}

// (0x38)
void SRL_B() {
	SRL(&registers.B);
}

// (0x39)
void SRL_C() {
	SRL(&registers.C);
}

// (0x3A)
void SRL_D() {
	SRL(&registers.D);
}

// (0x3B)
void SRL_E() {
	SRL(&registers.E);
}

// (0x3C)
void SRL_H() {
	SRL(&registers.H);
}

// (0x3D)
void SRL_L() {
	SRL(&registers.L);
}

// (0x3E)
void SRL_0xHL() {
	SRL(gb_mmu_location(registers.HL));
}

// (0x3F)
void SRL_A() {
	SRL(&registers.A);
}

// (0xF0)
void BIT_0_B() {
	BIT(&registers.B, 0);
}

// (0xF1)
void BIT_0_C() {
	BIT(&registers.C, 0);
}

// (0xF2)
void BIT_0_D() {
	BIT(&registers.D, 0);
}

// (0xF3)
void BIT_0_E() {
	BIT(&registers.E, 0);
}

// (0xF4)
void BIT_0_H() {
	BIT(&registers.H, 0);
}

// (0xF5)
void BIT_0_L() {
	BIT(&registers.L, 0);
}

// (0xF6)
void BIT_0_0xHL() {
	BIT(gb_mmu_location(registers.HL), 0);
}

// (0xF7)
void BIT_0_A() {
	BIT(&registers.A, 0);
}

// (0xF8)
void BIT_1_B() {
	BIT(&registers.B, 1);
}

// (0xF9)
void BIT_1_C() {
	BIT(&registers.C, 1);
}

// (0xFA)
void BIT_1_D() {
	BIT(&registers.D, 1);
}

// (0xFB)
void BIT_1_E() {
	BIT(&registers.E, 1);
}

// (0xFC)
void BIT_1_H() {
	BIT(&registers.H, 1);
}

// (0xFD)
void BIT_1_L() {
	BIT(&registers.L, 1);
}

// (0xFE)
void BIT_1_0xHL() {
	BIT(gb_mmu_location(registers.HL), 1);
}

// (0xFF)
void BIT_1_A() {
	BIT(&registers.A, 1);
}

// (0x50)
void BIT_2_B() {
	BIT(&registers.B, 2);
}

// (0x51)
void BIT_2_C() {
	BIT(&registers.C, 2);
}

// (0x52)
void BIT_2_D() {
	BIT(&registers.D, 2);
}

// (0x53)
void BIT_2_E() {
	BIT(&registers.E, 2);
}

// (0x54)
void BIT_2_H() {
	BIT(&registers.H, 2);
}

// (0x55)
void BIT_2_L() {
	BIT(&registers.L, 2);
}

// (0x56)
void BIT_2_0xHL() {
	BIT(gb_mmu_location(registers.HL), 2);
}

// (0x57)
void BIT_2_A() {
	BIT(&registers.A, 2);
}

// (0x58)
void BIT_3_B() {
	BIT(&registers.B, 3);
}

// (0x59)
void BIT_3_C() {
	BIT(&registers.C, 3);
}

// (0x5A)
void BIT_3_D() {
	BIT(&registers.D, 3);
}

// (0x5B)
void BIT_3_E() {
	BIT(&registers.E, 3);
}

// (0x5C)
void BIT_3_H() {
	BIT(&registers.H, 3);
}

// (0x5D)
void BIT_3_L() {
	BIT(&registers.L, 3);
}

// (0x5E)
void BIT_3_0xHL() {
	BIT(gb_mmu_location(registers.HL), 3);
}

// (0x5F)
void BIT_3_A() {
	BIT(&registers.A, 3);
}

// (0x60)
void BIT_4_B() {
	BIT(&registers.B, 4);
}

// (0x61)
void BIT_4_C() {
	BIT(&registers.C, 4);
}

// (0x62)
void BIT_4_D() {
	BIT(&registers.D, 4);
}

// (0x63)
void BIT_4_E() {
	BIT(&registers.E, 4);
}

// (0x64)
void BIT_4_H() {
	BIT(&registers.H, 4);
}

// (0x65)
void BIT_4_L() {
	BIT(&registers.L, 4);
}

// (0x66)
void BIT_4_0xHL() {
	BIT(gb_mmu_location(registers.HL), 4);
}

// (0x67)
void BIT_4_A() {
	BIT(&registers.A, 4);
}

// (0x68)
void BIT_5_B() {
	BIT(&registers.B, 5);
}

// (0x69)
void BIT_5_C() {
	BIT(&registers.C, 5);
}

// (0x6A)
void BIT_5_D() {
	BIT(&registers.D, 5);
}

// (0x6B)
void BIT_5_E() {
	BIT(&registers.E, 5);
}

// (0x6C)
void BIT_5_H() {
	BIT(&registers.H, 5);
}

// (0x6D)
void BIT_5_L() {
	BIT(&registers.L, 5);
}

// (0x6E)
void BIT_5_0xHL() {
	BIT(gb_mmu_location(registers.HL), 5);
}

// (0x6F)
void BIT_5_A() {
	BIT(&registers.A, 5);
}

// (0x70)
void BIT_6_B() {
	BIT(&registers.B, 6);
}

// (0x71)
void BIT_6_C() {
	BIT(&registers.C, 6);
}

// (0x72)
void BIT_6_D() {
	BIT(&registers.D, 6);
}

// (0x73)
void BIT_6_E() {
	BIT(&registers.E, 6);
}

// (0x74)
void BIT_6_H() {
	BIT(&registers.H, 6);
}

// (0x75)
void BIT_6_L() {
	BIT(&registers.L, 6);
}

// (0x76)
void BIT_6_0xHL() {
	BIT(gb_mmu_location(registers.HL), 6);
}

// (0x77)
void BIT_6_A() {
	BIT(&registers.A, 6);
}

// (0x78)
void BIT_7_B() {
	BIT(&registers.B, 7);
}

// (0x79)
void BIT_7_C() {
	BIT(&registers.C, 7);
}

// (0x7A)
void BIT_7_D() {
	BIT(&registers.D, 7);
}

// (0x7B)
void BIT_7_E() {
	BIT(&registers.E, 7);
}

// (0x7C)
void BIT_7_H() {
	BIT(&registers.H, 7);
}

// (0x7D)
void BIT_7_L() {
	BIT(&registers.L, 7);
}

// (0x7E)
void BIT_7_0xHL() {
	BIT(gb_mmu_location(registers.HL), 7);
}

// (0x7F)
void BIT_7_A() {
	BIT(&registers.A, 7);
}

// (0x80)
void RES_0_B() {
	RES(&registers.B, 0);
}

// (0x81)
void RES_0_C() {
	RES(&registers.C, 0);
}

// (0x82)
void RES_0_D() {
	RES(&registers.D, 0);
}

// (0x83)
void RES_0_E() {
	RES(&registers.E, 0);
}

// (0x84)
void RES_0_H() {
	RES(&registers.H, 0);
}

// (0x85)
void RES_0_L() {
	RES(&registers.L, 0);
}

// (0x86)
void RES_0_0xHL() {
	RES(gb_mmu_location(registers.HL), 0);
}

// (0x87)
void RES_0_A() {
	RES(&registers.A, 0);
}

// (0x88)
void RES_1_B() {
	RES(&registers.B, 1);
}

// (0x89)
void RES_1_C() {
	RES(&registers.C, 1);
}

// (0x8A)
void RES_1_D() {
	RES(&registers.D, 1);
}

// (0x8B)
void RES_1_E() {
	RES(&registers.E, 1);
}

// (0x8C)
void RES_1_H() {
	RES(&registers.H, 1);
}

// (0x8D)
void RES_1_L() {
	RES(&registers.L, 1);
}

// (0x8E)
void RES_1_0xHL() {
	RES(gb_mmu_location(registers.HL), 1);
}

// (0x8F)
void RES_1_A() {
	RES(&registers.A, 1);
}

// (0x90)
void RES_2_B() {
	RES(&registers.B, 2);
}

// (0x91)
void RES_2_C() {
	RES(&registers.C, 2);
}

// (0x92)
void RES_2_D() {
	RES(&registers.D, 2);
}

// (0x93)
void RES_2_E() {
	RES(&registers.E, 2);
}

// (0x94)
void RES_2_H() {
	RES(&registers.H, 2);
}

// (0x95)
void RES_2_L() {
	RES(&registers.L, 2);
}

// (0x96)
void RES_2_0xHL() {
	RES(gb_mmu_location(registers.HL), 2);
}

// (0x97)
void RES_2_A() {
	RES(&registers.A, 2);
}

// (0x98)
void RES_3_B() {
	RES(&registers.B, 3);
}

// (0x99)
void RES_3_C() {
	RES(&registers.C, 3);
}

// (0x9A)
void RES_3_D() {
	RES(&registers.D, 3);
}

// (0x9B)
void RES_3_E() {
	RES(&registers.E, 3);
}

// (0x9C)
void RES_3_H() {
	RES(&registers.H, 3);
}

// (0x9D)
void RES_3_L() {
	RES(&registers.L, 3);
}

// (0x9E)
void RES_3_0xHL() {
	RES(gb_mmu_location(registers.HL), 3);
}

// (0x9F)
void RES_3_A() {
	RES(&registers.A, 3);
}

// (0xA0)
void RES_4_B() {
	RES(&registers.B, 4);
}

// (0xA1)
void RES_4_C() {
	RES(&registers.C, 4);
}

// (0xA2)
void RES_4_D() {
	RES(&registers.D, 4);
}

// (0xA3)
void RES_4_E() {
	RES(&registers.E, 4);
}

// (0xA4)
void RES_4_H() {
	RES(&registers.H, 4);
}

// (0xA5)
void RES_4_L() {
	RES(&registers.L, 4);
}

// (0xA6)
void RES_4_0xHL() {
	RES(gb_mmu_location(registers.HL), 4);
}

// (0xA7)
void RES_4_A() {
	RES(&registers.A, 4);
}

// (0xA8)
void RES_5_B() {
	RES(&registers.B, 5);
}

// (0xA9)
void RES_5_C() {
	RES(&registers.C, 5);
}

// (0xAA)
void RES_5_D() {
	RES(&registers.D, 5);
}

// (0xAB)
void RES_5_E() {
	RES(&registers.E, 5);
}

// (0xAC)
void RES_5_H() {
	RES(&registers.H, 5);
}

// (0xAD)
void RES_5_L() {
	RES(&registers.L, 5);
}

// (0xAE)
void RES_5_0xHL() {
	RES(gb_mmu_location(registers.HL), 5);
}

// (0xAF)
void RES_5_A() {
	RES(&registers.A, 5);
}

// (0xB0)
void RES_6_B() {
	RES(&registers.B, 6);
}

// (0xB1)
void RES_6_C() {
	RES(&registers.C, 6);
}

// (0xB2)
void RES_6_D() {
	RES(&registers.D, 6);
}

// (0xB3)
void RES_6_E() {
	RES(&registers.E, 6);
}

// (0xB4)
void RES_6_H() {
	RES(&registers.H, 6);
}

// (0xB5)
void RES_6_L() {
	RES(&registers.L, 6);
}

// (0xB6)
void RES_6_0xHL() {
	RES(gb_mmu_location(registers.HL), 6);
}

// (0xB7)
void RES_6_A() {
	RES(&registers.A, 6);
}

// (0xB8)
void RES_7_B() {
	RES(&registers.B, 7);
}

// (0xB9)
void RES_7_C() {
	RES(&registers.C, 7);
}

// (0xBA)
void RES_7_D() {
	RES(&registers.D, 7);
}

// (0xBB)
void RES_7_E() {
	RES(&registers.E, 7);
}

// (0xBC)
void RES_7_H() {
	RES(&registers.H, 7);
}

// (0xBD)
void RES_7_L() {
	RES(&registers.L, 7);
}

// (0xBE)
void RES_7_0xHL() {
	RES(gb_mmu_location(registers.HL), 7);
}

// (0xBF)
void RES_7_A() {
	RES(&registers.A, 7);
}

// (0xC0)
void SET_0_B() {
	SET(&registers.B, 0);
}

// (0xC1)
void SET_0_C() {
	SET(&registers.C, 0);
}

// (0xC2)
void SET_0_D() {
	SET(&registers.D, 0);
}

// (0xC3)
void SET_0_E() {
	SET(&registers.E, 0);
}

// (0xC4)
void SET_0_H() {
	SET(&registers.H, 0);
}

// (0xC5)
void SET_0_L() {
	SET(&registers.L, 0);
}

// (0xC6)
void SET_0_0xHL() {
	SET(gb_mmu_location(registers.HL), 0);
}

// (0xC7)
void SET_0_A() {
	SET(&registers.A, 0);
}

// (0xC8)
void SET_1_B() {
	SET(&registers.B, 1);
}

// (0xC9)
void SET_1_C() {
	SET(&registers.C, 1);
}

// (0xCA)
void SET_1_D() {
	SET(&registers.D, 1);
}

// (0xCB)
void SET_1_E() {
	SET(&registers.E, 1);
}

// (0xCC)
void SET_1_H() {
	SET(&registers.H, 1);
}

// (0xCD)
void SET_1_L() {
	SET(&registers.L, 1);
}

// (0xCE)
void SET_1_0xHL() {
	SET(gb_mmu_location(registers.HL), 1);
}

// (0xCF)
void SET_1_A() {
	SET(&registers.A, 1);
}

// (0xD0)
void SET_2_B() {
	SET(&registers.B, 2);
}

// (0xD1)
void SET_2_C() {
	SET(&registers.C, 2);
}

// (0xD2)
void SET_2_D() {
	SET(&registers.D, 2);
}

// (0xD3)
void SET_2_E() {
	SET(&registers.E, 2);
}

// (0xD4)
void SET_2_H() {
	SET(&registers.H, 2);
}

// (0xD5)
void SET_2_L() {
	SET(&registers.L, 2);
}

// (0xD6)
void SET_2_0xHL() {
	SET(gb_mmu_location(registers.HL), 2);
}

// (0xD7)
void SET_2_A() {
	SET(&registers.A, 2);
}

// (0xD8)
void SET_3_B() {
	SET(&registers.B, 3);
}

// (0xD9)
void SET_3_C() {
	SET(&registers.C, 3);
}

// (0xDA)
void SET_3_D() {
	SET(&registers.D, 3);
}

// (0xDB)
void SET_3_E() {
	SET(&registers.E, 3);
}

// (0xDC)
void SET_3_H() {
	SET(&registers.H, 3);
}

// (0xDD)
void SET_3_L() {
	SET(&registers.L, 3);
}

// (0xDE)
void SET_3_0xHL() {
	SET(gb_mmu_location(registers.HL), 3);
}

// (0xDF)
void SET_3_A() {
	SET(&registers.A, 3);
}

// (0xE0)
void SET_4_B() {
	SET(&registers.B, 4);
}

// (0xE1)
void SET_4_C() {
	SET(&registers.C, 4);
}

// (0xE2)
void SET_4_D() {
	SET(&registers.D, 4);
}

// (0xE3)
void SET_4_E() {
	SET(&registers.E, 4);
}

// (0xE4)
void SET_4_H() {
	SET(&registers.H, 4);
}

// (0xE5)
void SET_4_L() {
	SET(&registers.L, 4);
}

// (0xE6)
void SET_4_0xHL() {
	SET(gb_mmu_location(registers.HL), 4);
}

// (0xE7)
void SET_4_A() {
	SET(&registers.A, 4);
}

// (0xE8)
void SET_5_B() {
	SET(&registers.B, 5);
}

// (0xE9)
void SET_5_C() {
	SET(&registers.C, 5);
}

// (0xEA)
void SET_5_D() {
	SET(&registers.D, 5);
}

// (0xEB)
void SET_5_E() {
	SET(&registers.E, 5);
}

// (0xEC)
void SET_5_H() {
	SET(&registers.H, 5);
}

// (0xED)
void SET_5_L() {
	SET(&registers.L, 5);
}

// (0xEE)
void SET_5_0xHL() {
	SET(gb_mmu_location(registers.HL), 5);
}

// (0xEF)
void SET_5_A() {
	SET(&registers.A, 5);
}

// (0xF0)
void SET_6_B() {
	SET(&registers.B, 6);
}

// (0xF1)
void SET_6_C() {
	SET(&registers.C, 6);
}

// (0xF2)
void SET_6_D() {
	SET(&registers.D, 6);
}

// (0xF3)
void SET_6_E() {
	SET(&registers.E, 6);
}

// (0xF4)
void SET_6_H() {
	SET(&registers.H, 6);
}

// (0xF5)
void SET_6_L() {
	SET(&registers.L, 6);
}

// (0xF6)
void SET_6_0xHL() {
	SET(gb_mmu_location(registers.HL), 6);
}

// (0xF7)
void SET_6_A() {
	SET(&registers.A, 6);
}

// (0xF8)
void SET_7_B() {
	SET(&registers.B, 7);
}

// (0xF9)
void SET_7_C() {
	SET(&registers.C, 7);
}

// (0xFA)
void SET_7_D() {
	SET(&registers.D, 7);
}

// (0xFB)
void SET_7_E() {
	SET(&registers.E, 7);
}

// (0xFC)
void SET_7_H() {
	SET(&registers.H, 7);
}

// (0xFD)
void SET_7_L() {
	SET(&registers.L, 7);
}

// (0xFE)
void SET_7_0xHL() {
	SET(gb_mmu_location(registers.HL), 7);
}

// (0xFF)
void SET_7_A() {
	SET(&registers.A, 7);
}


//TIMINGS
const int TIMINGS_EXT[] = {
	/*      0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F */
	/* 0 */ 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 3, 1,
	/* 1 */ 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 3, 1,
	/* 2 */ 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 3, 1,
	/* 3 */ 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 3, 1,
	/* 4 */ 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1,
	/* 5 */ 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1,
	/* 6 */ 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1,
	/* 7 */ 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1,
	/* 8 */ 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 3, 1,
	/* 9 */ 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 3, 1,
	/* A */ 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 3, 1,
	/* B */ 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 3, 1,
	/* C */ 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 3, 1,
	/* D */ 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 3, 1,
	/* E */ 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 3, 1,
	/* F */ 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 3, 1,
};


int gb_cpu_delay_ext_get(uint8_t opcode) {
	return TIMINGS_EXT[opcode];
}