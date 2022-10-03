#include "rge.h"
#include "gb/core.h"

// (0x00)
void NOP() {
	return;
}

// (0x01)
void LD_BC_U16() {
	registers.BC = gb_mmu_fetch_u16();
}

// (0x02)
void LD_0xBC_A() {
	gb_mmu_write(registers.BC, registers.A);
}

// (0x03)
void INC_BC() {
	INC_16(&registers.BC);
}

// (0x04)
void INC_B() {
	INC(&registers.B);
}

// (0x05)
void DEC_B() {
	DEC(&registers.B);
}

// (0x06)
void LD_B_U8() {
	registers.B = gb_mmu_fetch();
}

// (0x07)
void RLCA() {
	int carry = registers.A & 0x80;

	gb_cpu_flag_set(FLAGS_CARRY, carry);

	registers.A <<= 1;
	registers.A |= (carry >> 7);

	gb_cpu_flag_set(FLAGS_ZERO | FLAGS_SUBTRACT | FLAGS_HALF_CARRY, false);
}

// (0x08)
void LD_0xU16_SP() {
	uint16_t addr = gb_mmu_fetch_u16();

	gb_mmu_write(addr, (uint8_t)(registers.SP & 0x00FF));
	gb_mmu_write(addr + 1, (uint8_t)((registers.SP & 0xFF00) >> 8));
}

// (0x09)
void ADD_HL_BC() {
	ADD_HL(registers.BC);
}

// (0x0A)
void LD_A_0xBC() {
	registers.A = gb_mmu_read(registers.BC);
}

// (0x0B)
void DEC_BC() {
	DEC_16(&registers.BC);
}

// (0x0C)
void INC_C() {
	INC(&registers.C);
}

// (0x0D)
void DEC_C() {
	DEC(&registers.C);
}

// (0x0E)
void LD_C_U8() {
	registers.C = gb_mmu_fetch();
}

// (0x0F)
void RRCA() {
	int carry = registers.A & 0x01;

	gb_cpu_flag_set(FLAGS_CARRY, carry);

	registers.A >>= 1;
	registers.A |= carry << 7;

	gb_cpu_flag_set(FLAGS_ZERO | FLAGS_SUBTRACT | FLAGS_HALF_CARRY, false);
}

// (0x10)
void STOP() {
	rge_log_info("Game stopping");
	rge_core_close();
}

// (0x11)
void LD_DE_U16() {
	registers.DE = gb_mmu_fetch_u16();
}

// (0x12)
void LD_0xDE_A() {
	gb_mmu_write(registers.DE, registers.A);
}

// (0x13)
void INC_DE() {
	INC_16(&registers.DE);
}

// (0x14)
void INC_D() {
	INC(&registers.D);
}

// (0x15)
void DEC_D() {
	DEC(&registers.D);
}

// (0x16)
void LD_D_U8() {
	registers.D = gb_mmu_fetch();
}

// (0x17)
void RLA() {
	int carry = gb_cpu_flag_get(FLAGS_CARRY) ? 0x01 : 0x00;

	gb_cpu_flag_set(FLAGS_CARRY, registers.A & 0x80);

	registers.A <<= 1;
	registers.A |= carry;

	gb_cpu_flag_set(FLAGS_ZERO | FLAGS_SUBTRACT | FLAGS_HALF_CARRY, false);
}

// (0x18)
void JR_I8() {
	registers.PC += (int8_t)gb_mmu_fetch();
}

// (0x19)
void ADD_HL_DE() {
	ADD_HL(registers.DE);
}

// (0x1A)
void LD_A_0xDE() {
	registers.A = gb_mmu_read(registers.DE);
}

// (0x1B)
void DEC_DE() {
	DEC_16(&registers.DE);
}

// (0x1C)
void INC_E() {
	INC(&registers.E);
}

// (0x1D)
void DEC_E() {
	DEC(&registers.E);
}

// (0x1E)
void LD_E_U8() {
	registers.E = gb_mmu_fetch();
}

// (0x1F)
void RRA() {
	int carry = gb_cpu_flag_get(FLAGS_CARRY) ? 0x80 : 0x00;

	gb_cpu_flag_set(FLAGS_CARRY, registers.A & 0x01);

	registers.A >>= 1;
	registers.A |= carry;

	gb_cpu_flag_set(FLAGS_ZERO | FLAGS_SUBTRACT | FLAGS_HALF_CARRY, false);
}

// (0x20)
void JR_NZ_I8() {
	int8_t i8 = (int8_t)gb_mmu_fetch();

	if (!gb_cpu_flag_get(FLAGS_ZERO)) {
		registers.PC += i8;
		gb_cpu_delay(1);
	}
}

// (0x21)
void LD_HL_U16() {
	registers.HL = gb_mmu_fetch_u16();
}

// (0x22)
void LD_0xHLI_A() {
	gb_mmu_write(registers.HL, registers.A);
	INC_16(&registers.HL);
}

// (0x23)
void INC_HL() {
	INC_16(&registers.HL);
}

// (0x24)
void INC_H() {
	INC(&registers.H);
}

// (0x25)
void DEC_H() {
	DEC(&registers.H);
}

// (0x26)
void LD_H_U8() {
	registers.H = gb_mmu_fetch();
}

// (0x27)
void DAA() {
	if (gb_cpu_flag_get(FLAGS_SUBTRACT)) {
		if (gb_cpu_flag_get(FLAGS_CARRY)) registers.A -= 0x60;
		if (gb_cpu_flag_get(FLAGS_HALF_CARRY)) registers.A -= 0x06;
		
	} else {
		if (gb_cpu_flag_get(FLAGS_CARRY) || (registers.A & 0xF0) > 0x90) {
			registers.A += 0x60;
			gb_cpu_flag_set(FLAGS_CARRY, true);
		}
		if (gb_cpu_flag_get(FLAGS_HALF_CARRY) || (registers.A & 0x0F) > 0x09) {
			registers.A += 0x06;
		}
	}

	gb_cpu_flag_set(FLAGS_ZERO, registers.A == 0);
	gb_cpu_flag_set(FLAGS_HALF_CARRY, false);
}

// (0x28)
void JR_Z_I8() {
	int8_t i8 = (int8_t)gb_mmu_fetch();
	if (gb_cpu_flag_get(FLAGS_ZERO)) {
		registers.PC += i8;
		gb_cpu_delay(1);
	}
}

// (0x29)
void ADD_HL_HL() {
	ADD_HL(registers.HL);
}

// (0x2A)
void LD_A_0xHLI() {
	registers.A = gb_mmu_read(registers.HL);
	INC_16(&registers.HL);
}

// (0x2B)
void DEC_HL() {
	DEC_16(&registers.HL);
}

// (0x2C)
void INC_L() {
	INC(&registers.L);
}

// (0x2D)
void DEC_L() {
	DEC(&registers.L);
}

// (0x2E)
void LD_L_U8() {
	registers.L = gb_mmu_fetch();
}

// (0x2F)
void CPL() {
	registers.A = ~registers.A;
	gb_cpu_flag_set(FLAGS_SUBTRACT | FLAGS_HALF_CARRY, true);
}

// (0x30)
void JR_NC_I8() {
	int8_t i8 = (int8_t)gb_mmu_fetch();
	if (!gb_cpu_flag_get(FLAGS_CARRY)) {
		registers.PC += i8;
		gb_cpu_delay(1);
	}
}

// (0x31)
void LD_SP_U16() {
	registers.SP = gb_mmu_fetch_u16();
}

// (0x32)
void LD_0xHLD_A() {
	gb_mmu_write(registers.HL, registers.A);
	registers.HL--;
}

// (0x33)
void INC_SP() {
	INC_16(&registers.SP);
}

// (0x34)
void INC_0xHL() {
	INC(gb_mmu_location(registers.HL));
}

// (0x35)
void DEC_0xHL() {
	DEC(gb_mmu_location(registers.HL));
}

// (0x36)
void LD_0xHL_U8() {
	gb_mmu_write(registers.HL, gb_mmu_fetch());
}

// (0x37)
void SCF() {
	gb_cpu_flag_set(FLAGS_SUBTRACT | FLAGS_HALF_CARRY, false);
	gb_cpu_flag_set(FLAGS_CARRY, true);
}

// (0x38)
void JR_C_I8() {
	int8_t i8 = (int8_t)gb_mmu_fetch();
	if (gb_cpu_flag_get(FLAGS_CARRY)) {
		registers.PC += i8;
		gb_cpu_delay(1);
	}
}

// (0x39)
void ADD_HL_SP() {
	ADD_HL(registers.SP);
}

// (0x3A)
void LD_A_0xHLD() {
	registers.A = gb_mmu_read(registers.HL);
	DEC_16(&registers.HL);
}

// (0x3B)
void DEC_SP() {
	DEC_16(&registers.SP);
}

// (0x3C)
void INC_A() {
	INC(&registers.A);
}

// (0x3D)
void DEC_A() {
	DEC(&registers.A);
}

// (0x3E)
void LD_A_U8() {
	registers.A = gb_mmu_fetch();
}

// (0x3F)
void CCF() {
	gb_cpu_flag_set(FLAGS_SUBTRACT | FLAGS_HALF_CARRY, false);

	if (gb_cpu_flag_get(FLAGS_CARRY))
		gb_cpu_flag_set(FLAGS_CARRY, false);
	else
		gb_cpu_flag_set(FLAGS_CARRY, true);

	//gb_cpu_flag_set(FLAGS_CARRY, !gb_cpu_flag_get(FLAGS_CARRY));
}

// (0x40)
void LD_B_B() {
	registers.B = registers.B;
}

// (0x41)
void LD_B_C() {
	registers.B = registers.C;
}

// (0x42)
void LD_B_D() {
	registers.B = registers.D;
}

// (0x43)
void LD_B_E() {
	registers.B = registers.E;
}

// (0x44)
void LD_B_H() {
	registers.B = registers.H;
}

// (0x45)
void LD_B_L() {
	registers.B = registers.L;
}

// (0x46)
void LD_B_0xHL() {
	registers.B = gb_mmu_read(registers.HL);
}

// (0x47)
void LD_B_A() {
	registers.B = registers.A;
}

// (0x48)
void LD_C_B() {
	registers.C = registers.B;
}

// (0x49)
void LD_C_C() {
	registers.C = registers.C;
}

// (0x4A)
void LD_C_D() {
	registers.C = registers.D;
}

// (0x4B)
void LD_C_E() {
	registers.C = registers.E;
}

// (0x4C)
void LD_C_H() {
	registers.C = registers.H;
}

// (0x4D)
void LD_C_L() {
	registers.C = registers.L;
}

// (0x4E)
void LD_C_0xHL() {
	registers.C = gb_mmu_read(registers.HL);
}

// (0x4F)
void LD_C_A() {
	registers.C = registers.A;
}

// (0x50)
void LD_D_B() {
	registers.D = registers.B;
}

// (0x51)
void LD_D_C() {
	registers.D = registers.C;
}

// (0x52)
void LD_D_D() {
	registers.D = registers.D;
}

// (0x53)
void LD_D_E() {
	registers.D = registers.E;
}

// (0x54)
void LD_D_H() {
	registers.D = registers.H;
}

// (0x55)
void LD_D_L() {
	registers.D = registers.L;
}

// (0x56)
void LD_D_0xHL() {
	registers.D = gb_mmu_read(registers.HL);
}

// (0x57)
void LD_D_A() {
	registers.D = registers.A;
}

// (0x58)
void LD_E_B() {
	registers.E = registers.B;
}

// (0x59)
void LD_E_C() {
	registers.E = registers.C;
}

// (0x5A)
void LD_E_D() {
	registers.E = registers.D;
}

// (0x5B)
void LD_E_E() {
	registers.E = registers.E;
}

// (0x5C)
void LD_E_H() {
	registers.E = registers.H;
}

// (0x5D)
void LD_E_L() {
	registers.E = registers.L;
}

// (0x5E)
void LD_E_0xHL() {
	registers.E = gb_mmu_read(registers.HL);
}

// (0x5F)
void LD_E_A() {
	registers.E = registers.A;
}

// (0x60)
void LD_H_B() {
	registers.H = registers.B;
}

// (0x61)
void LD_H_C() {
	registers.H = registers.C;
}

// (0x62)
void LD_H_D() {
	registers.H = registers.D;
}

// (0x63)
void LD_H_E() {
	registers.H = registers.E;
}

// (0x64)
void LD_H_H() {
	registers.H = registers.H;
}

// (0x65)
void LD_H_L() {
	registers.H = registers.L;
}

// (0x66)
void LD_H_0xHL() {
	registers.H = gb_mmu_read(registers.HL);
}

// (0x67)
void LD_H_A() {
	registers.H = registers.A;
}

// (0x68)
void LD_L_B() {
	registers.L = registers.B;
}

// (0x69)
void LD_L_C() {
	registers.L = registers.C;
}

// (0x6A)
void LD_L_D() {
	registers.L = registers.D;
}

// (0x6B)
void LD_L_E() {
	registers.L = registers.E;
}

// (0x6C)
void LD_L_H() {
	registers.L = registers.H;
}

// (0x6D)
void LD_L_L() {
	registers.L = registers.L;
}

// (0x6E)
void LD_L_0xHL() {
	registers.L = gb_mmu_read(registers.HL);
}

// (0x6F)
void LD_L_A() {
	registers.L = registers.A;
}

// (0x70)
void LD_0xHL_B() {
	gb_mmu_write(registers.HL, registers.B);
}

// (0x71)
void LD_0xHL_C() {
	gb_mmu_write(registers.HL, registers.C);
}

// (0x72)
void LD_0xHL_D() {
	gb_mmu_write(registers.HL, registers.D);
}

// (0x73)
void LD_0xHL_E() {
	gb_mmu_write(registers.HL, registers.E);
}

// (0x74)
void LD_0xHL_H() {
	gb_mmu_write(registers.HL, registers.H);
}

// (0x75)
void LD_0xHL_L() {
	gb_mmu_write(registers.HL, registers.L);
}

// (0x76)
void HALT() {
	if (registers.IME) registers.PC--;
	else gb_cpu_delay(1);
}

// (0x77)
void LD_0xHL_A() {
	gb_mmu_write(registers.HL, registers.A);
}

// (0x78)
void LD_A_B() {
	registers.A = registers.B;
}

// (0x79)
void LD_A_C() {
	registers.A = registers.C;
}

// (0x7A)
void LD_A_D() {
	registers.A = registers.D;
}

// (0x7B)
void LD_A_E() {
	registers.A = registers.E;
}

// (0x7C)
void LD_A_H() {
	registers.A = registers.H;
}

// (0x7D)
void LD_A_L() {
	registers.A = registers.L;
}

// (0x7E)
void LD_A_0xHL() {
	registers.A = gb_mmu_read(registers.HL);
}

// (0x7F)
void LD_A_A() {
	registers.A = registers.A;
}

// (0x80)
void ADD_A_B() {
	ADD(registers.B);
}

// (0x81)
void ADD_A_C() {
	ADD(registers.C);
}

// (0x82)
void ADD_A_D() {
	ADD(registers.D);
}

// (0x83)
void ADD_A_E() {
	ADD(registers.E);
}

// (0x84)
void ADD_A_H() {
	ADD(registers.H);
}

// (0x85)
void ADD_A_L() {
	ADD(registers.L);
}

// (0x86)
void ADD_A_0xHL() {
	ADD(gb_mmu_read(registers.HL));
}

// (0x87)
void ADD_A_A() {
	ADD(registers.A);
}

// (0x88)
void ADC_A_B() {
	ADC(registers.B);
}

// (0x89)
void ADC_A_C() {
	ADC(registers.C);
}

// (0x8A)
void ADC_A_D() {
	ADC(registers.D);
}

// (0x8B)
void ADC_A_E() {
	ADC(registers.E);
}

// (0x8C)
void ADC_A_H() {
	ADC(registers.H);
}

// (0x8D)
void ADC_A_L() {
	ADC(registers.L);
}

// (0x8E)
void ADC_A_0xHL() {
	ADC(gb_mmu_read(registers.HL));
}

// (0x8F)
void ADC_A_A() {
	ADC(registers.A);
}

// (0x90)
void SUB_A_B() {
	SUB(registers.B);
}

// (0x91)
void SUB_A_C() {
	SUB(registers.C);
}

// (0x92)
void SUB_A_D() {
	SUB(registers.D);
}

// (0x93)
void SUB_A_E() {
	SUB(registers.E);
}

// (0x94)
void SUB_A_H() {
	SUB(registers.H);
}

// (0x95)
void SUB_A_L() {
	SUB(registers.L);
}

// (0x96)
void SUB_A_0xHL() {
	SUB(gb_mmu_read(registers.HL));
}

// (0x97)
void SUB_A_A() {
	SUB(registers.A);
}

// (0x98)
void SBC_A_B() {
	SBC(registers.B);
}

// (0x99)
void SBC_A_C() {
	SBC(registers.C);
}

// (0x9A)
void SBC_A_D() {
	SBC(registers.D);
}

// (0x9B)
void SBC_A_E() {
	SBC(registers.E);
}

// (0x9C)
void SBC_A_H() {
	SBC(registers.H);
}

// (0x9D)
void SBC_A_L() {
	SBC(registers.L);
}

// (0x9E)
void SBC_A_0xHL() {
	SBC(gb_mmu_read(registers.HL));
}

// (0x9F)
void SBC_A_A() {
	SBC(registers.A);
}

// (0xA0)
void AND_A_B() {
	AND(registers.B);
}

// (0xA1)
void AND_A_C() {
	AND(registers.C);
}

// (0xA2)
void AND_A_D() {
	AND(registers.D);
}

// (0xA3)
void AND_A_E() {
	AND(registers.E);
}

// (0xA4)
void AND_A_H() {
	AND(registers.H);
}

// (0xA5)
void AND_A_L() {
	AND(registers.L);
}

// (0xA6)
void AND_A_0xHL() {
	AND(gb_mmu_read(registers.HL));
}

// (0xA7)
void AND_A_A() {
	AND(registers.A);
}

// (0xA8)
void XOR_A_B() {
	XOR(registers.B);
}

// (0xA9)
void XOR_A_C() {
	XOR(registers.C);
}

// (0xAA)
void XOR_A_D() {
	XOR(registers.D);
}

// (0xAB)
void XOR_A_E() {
	XOR(registers.E);
}

// (0xAC)
void XOR_A_H() {
	XOR(registers.H);
}

// (0xAD)
void XOR_A_L() {
	XOR(registers.L);
}

// (0xAE)
void XOR_A_0xHL() {
	XOR(gb_mmu_read(registers.HL));
}

// (0xAF)
void XOR_A_A() {
	XOR(registers.A);
}

// (0xB0)
void OR_A_B() {
	OR(registers.B);
}

// (0xB1)
void OR_A_C() {
	OR(registers.C);
}

// (0xB2)
void OR_A_D() {
	OR(registers.D);
}

// (0xB3)
void OR_A_E() {
	OR(registers.E);
}

// (0xB4)
void OR_A_H() {
	OR(registers.H);
}

// (0xB5)
void OR_A_L() {
	OR(registers.L);
}

// (0xB6)
void OR_A_0xHL() {
	OR(gb_mmu_read(registers.HL));
}

// (0xB7)
void OR_A_A() {
	OR(registers.A);
}

// (0xB8)
void CP_A_B() {
	CP(registers.B);
}

// (0xB9)
void CP_A_C() {
	CP(registers.C);
}

// (0xBA)
void CP_A_D() {
	CP(registers.D);
}

// (0xBB)
void CP_A_E() {
	CP(registers.E);
}

// (0xBC)
void CP_A_H() {
	CP(registers.H);
}

// (0xBD)
void CP_A_L() {
	CP(registers.L);
}

// (0xBE)
void CP_A_0xHL() {
	CP(gb_mmu_read(registers.HL));
}

// (0xBF)
void CP_A_A() {
	CP(registers.A);
}

// (0xC0)
void RET_NZ() {
	if (!gb_cpu_flag_get(FLAGS_ZERO)) {
		gb_mmu_return();
		gb_cpu_delay(3);
	}
}

// (0xC1)
void POP_BC() {
	gb_mmu_pop(&registers.BC);
}

// (0xC2)
void JP_NZ_U16() {
	uint16_t u16 = gb_mmu_fetch_u16();
	if (!gb_cpu_flag_get(FLAGS_ZERO)) {
		registers.PC = u16;
		gb_cpu_delay(1);
	}
}

// (0xC3)
void JP_U16() {
	registers.PC = gb_mmu_fetch_u16();
}

// (0xC4)
void CALL_NZ_U16() {
	uint16_t address = gb_mmu_fetch_u16();
	if (!gb_cpu_flag_get(FLAGS_ZERO)) {
		gb_mmu_call(address);
		gb_cpu_delay(3);
	}
}

// (0xC5)
void PUSH_BC() {
	gb_mmu_push(registers.BC);
}

// (0xC6)
void ADD_A_U8() {
	ADD(gb_mmu_fetch());
}

// (0xC7)
void RST_00H() {
	gb_mmu_restart(0x00);
}

// (0xC8)
void RET_Z() {
	if (gb_cpu_flag_get(FLAGS_ZERO)) {
		gb_mmu_return();
		gb_cpu_delay(3);
	}
}

// (0xC9)
void RET() {
	gb_mmu_return();
}

// (0xCA)
void JP_Z_U16() {
	uint16_t u16 = gb_mmu_fetch_u16();
	if (gb_cpu_flag_get(FLAGS_ZERO)) {
		registers.PC = u16;
		gb_cpu_delay(1);
	}
}

// (0xCB)
void PREFIX_CB() {
	uint8_t opcode = gb_mmu_fetch();

	void (*func)() = gb_cpu_decode_ext(opcode);

	func();

	gb_cpu_delay(gb_cpu_delay_ext_get(opcode));
}

// (0xCC)
void CALL_Z_U16() {
	uint16_t address = gb_mmu_fetch_u16();
	if (gb_cpu_flag_get(FLAGS_ZERO)) {
		gb_mmu_call(address);
		gb_cpu_delay(3);
	}
}

// (0xCD)
void CALL_U16() {
	gb_mmu_call(gb_mmu_fetch_u16());
}

// (0xCE)
void ADC_A_U8() {
	ADC(gb_mmu_fetch());
}

// (0xCF)
void RST_08H() {
	gb_mmu_restart(0x08);
}

// (0xD0)
void RET_NC() {
	if (!gb_cpu_flag_get(FLAGS_CARRY)) {
		gb_mmu_return();
		gb_cpu_delay(3);
	}
}

// (0xD1)
void POP_DE() {
	gb_mmu_pop(&registers.DE);
}

// (0xD2)
void JP_NC_U16() {
	uint16_t u16 = gb_mmu_fetch_u16();
	if (!gb_cpu_flag_get(FLAGS_CARRY)) {
		registers.PC = u16;
		gb_cpu_delay(1);
	}
}

// NULL

// (0xD4)
void CALL_NC_U16() {
	uint16_t address = gb_mmu_fetch_u16();
	if (!gb_cpu_flag_get(FLAGS_CARRY)) {
		gb_mmu_call(address);
		gb_cpu_delay(3);
	}
}

// (0xD5)
void PUSH_DE() {
	gb_mmu_push(registers.DE);
}

// (0xD6)
void SUB_A_U8() {
	SUB(gb_mmu_fetch());
}

// (0xD7)
void RST_10H() {
	gb_mmu_restart(0x10);
}

// (0xD8)
void RET_C() {
	if (gb_cpu_flag_get(FLAGS_CARRY)) {
		gb_mmu_return();
		gb_cpu_delay(3);
	}
}

// (0xD9)
void RETI() {
	gb_cpu_ime_set(true);
	gb_mmu_return();
}

// (0xDA)
void JP_C_U16() {
	uint16_t u16 = gb_mmu_fetch_u16();
	if (gb_cpu_flag_get(FLAGS_CARRY)) {
		registers.PC = u16;
		gb_cpu_delay(1);
	}
}

// NULL

// (0xDC)
void CALL_C_U16() {
	uint16_t address = gb_mmu_fetch_u16();
	if (gb_cpu_flag_get(FLAGS_CARRY)) {
		gb_mmu_call(address);
		gb_cpu_delay(3);
	}
}

// NULL

// (0xDE)
void SBC_A_U8() {
	SBC(gb_mmu_fetch());
}

// (0xDF)
void RST_18H() {
	gb_mmu_restart(0x18);
}

// (0xE0)
void LDH_0xU8_A() {
	gb_mmu_write(0xFF00 + gb_mmu_fetch(), registers.A);
}

// (0xE1)
void POP_HL() {
	gb_mmu_pop(&registers.HL);
}

// (0xE2)
void LDH_0xC_A() {
	gb_mmu_write(0xFF00 + registers.C, registers.A);
}

// NULL

// NULL

// (0xE5)
void PUSH_HL() {
	gb_mmu_push(registers.HL);
}

// (0xE6)
void AND_A_U8() {
	AND(gb_mmu_fetch());
}

// (0xE7)
void RST_20H() {
	gb_mmu_restart(0x20);
}

// (0xE8)
void ADD_SP_I8() {
	ADD_SP((int8_t)gb_mmu_fetch());
}

// (0xE9)
void JP_HL() {
	registers.PC = registers.HL;
}

// (0xEA)
void LD_0xU16_A() {
	gb_mmu_write(gb_mmu_fetch_u16(), registers.A);
}

// NULL

// NULL

// NULL

// (0xEE)
void XOR_A_U8() {
	XOR(gb_mmu_fetch());
}

// (0xEF)
void RST_28H() {
	gb_mmu_restart(0x28);
}

// (0xF0)
void LDH_A_0xU8() {
	registers.A = gb_mmu_read(0xFF00 + gb_mmu_fetch());
}

// (0xF1)
void POP_AF() {
	gb_mmu_pop(&registers.AF);
}

// (0xF2)
void LDH_A_0xC() {
	registers.A = gb_mmu_read(0xFF00 + registers.C);
}

// (0xF3)
void DI() {
	gb_cpu_ime_set(false);
}

// NULL

// (0xF5)
void PUSH_AF() {
	gb_mmu_push(registers.AF);
}

// (0xF6)
void OR_A_U8() {
	OR(gb_mmu_fetch());
}

// (0xF7)
void RST_30H() {
	gb_mmu_restart(0x30);
}

// (0xF8)
void LD_HL_SP_I8() {
	int8_t i8 = (int8_t)gb_mmu_fetch();
	uint32_t sum = registers.SP + i8;

	gb_cpu_flag_set(FLAGS_CARRY, sum & 0xFFFF0000);

	//<-
	
	gb_cpu_flag_set(FLAGS_HALF_CARRY, (registers.SP & 0x0F) + (i8 & 0x0F) > 0x0F);

	gb_cpu_flag_set(FLAGS_ZERO | FLAGS_SUBTRACT, false);

	// \/
	registers.HL = (uint16_t)(sum & 0xFFFF);
}

// (0xF9)
void LD_SP_HL() {
	registers.SP = registers.HL;
}

// (0xFA)
void LD_A_0xU16() {
	registers.A = gb_mmu_read(gb_mmu_fetch_u16());
}

// (0xFB)
void EI() {
	gb_cpu_ime_set(true);
}

// NULL

// NULL

// (0xFE)
void CP_A_U8() {
	CP(gb_mmu_fetch());
}

// (0xFF)
void RST_38H() {
	gb_mmu_restart(0x38);
}



//TIMINGS
const int TIMINGS[] = {
	/*      0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F */
	/* 0 */ 1, 3, 2, 2, 1, 1, 2, 1, 5, 2, 2, 2, 1, 1, 2, 1,
	/* 1 */ 1, 3, 2, 2, 1, 1, 2, 1, 3, 2, 2, 2, 1, 1, 2, 1,
	/* 2 */ 2, 3, 2, 2, 1, 1, 2, 1, 2, 2, 2, 2, 1, 1, 2, 1,
	/* 3 */ 2, 3, 2, 2, 3, 3, 3, 1, 2, 2, 2, 2, 1, 1, 2, 1,
	/* 4 */ 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1,
	/* 5 */ 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1,
	/* 6 */ 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1,
	/* 7 */ 2, 2, 2, 2, 2, 2, 0, 2, 1, 1, 1, 1, 1, 1, 2, 1,
	/* 8 */ 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1,
	/* 9 */ 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1,
	/* A */ 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1,
	/* B */ 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1,
	/* C */ 2, 3, 3, 4, 3, 4, 2, 4, 2, 4, 3, 1, 3, 6, 2, 4,
	/* D */ 2, 3, 3, 0, 3, 4, 2, 4, 2, 4, 3, 0, 3, 0, 2, 4,
	/* E */ 3, 3, 1, 0, 0, 4, 2, 4, 4, 1, 4, 0, 0, 0, 2, 4,
	/* F */ 3, 3, 1, 1, 0, 4, 2, 4, 3, 2, 4, 1, 0, 0, 2, 4,
};


int gb_cpu_delay_get(uint8_t opcode) {
	return TIMINGS[opcode];
}