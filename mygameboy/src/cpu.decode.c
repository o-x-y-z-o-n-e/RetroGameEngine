#include "rge.h"
#include "gb/core.h"
#include "gb/optable.h"

op_func gb_cpu_decode(uint8_t opcode) {
	switch (opcode) {
		// (0x0_)
		case 0x00: return NOP;
		case 0x01: return LD_BC_U16;
		case 0x02: return LD_0xBC_A;
		case 0x03: return INC_BC;
		case 0x04: return INC_B;
		case 0x05: return DEC_B;
		case 0x06: return LD_B_U8;
		case 0x07: return RLCA;
		case 0x08: return LD_0xU16_SP;
		case 0x09: return ADD_HL_BC;
		case 0x0A: return LD_A_0xBC;
		case 0x0B: return DEC_BC;
		case 0x0C: return INC_C;
		case 0x0D: return DEC_C;
		case 0x0E: return LD_C_U8;
		case 0x0F: return RRCA;

		// (0x1_)
		case 0x10: return STOP;
		case 0x11: return LD_DE_U16;
		case 0x12: return LD_0xDE_A;
		case 0x13: return INC_DE;
		case 0x14: return INC_D;
		case 0x15: return DEC_D;
		case 0x16: return LD_D_U8;
		case 0x17: return RLA;
		case 0x18: return JR_I8;
		case 0x19: return ADD_HL_DE;
		case 0x1A: return LD_A_0xDE;
		case 0x1B: return DEC_DE;
		case 0x1C: return INC_E;
		case 0x1D: return DEC_E;
		case 0x1E: return LD_E_U8;
		case 0x1F: return RRA;

		// (0x2_)
		case 0x20: return JR_NZ_I8;
		case 0x21: return LD_HL_U16;
		case 0x22: return LD_0xHLI_A;
		case 0x23: return INC_HL;
		case 0x24: return INC_H;
		case 0x25: return DEC_H;
		case 0x26: return LD_H_U8;
		case 0x27: return DAA;
		case 0x28: return JR_Z_I8;
		case 0x29: return ADD_HL_HL;
		case 0x2A: return LD_A_0xHLI;
		case 0x2B: return DEC_HL;
		case 0x2C: return INC_L;
		case 0x2D: return DEC_L;
		case 0x2E: return LD_L_U8;
		case 0x2F: return CPL;
		
		// (0x3_)
		case 0x30: return JR_NC_I8;
		case 0x31: return LD_SP_U16;
		case 0x32: return LD_0xHLD_A;
		case 0x33: return INC_SP;
		case 0x34: return INC_0xHL;
		case 0x35: return DEC_0xHL;
		case 0x36: return LD_0xHL_U8;
		case 0x37: return SCF;
		case 0x38: return JR_C_I8;
		case 0x39: return ADD_HL_SP;
		case 0x3A: return LD_A_0xHLD;
		case 0x3B: return DEC_SP;
		case 0x3C: return INC_A;
		case 0x3D: return DEC_A;
		case 0x3E: return LD_A_U8;
		case 0x3F: return CCF;

		// (0x4_)
		case 0x40: return LD_B_B;
		case 0x41: return LD_B_C;
		case 0x42: return LD_B_D;
		case 0x43: return LD_B_E;
		case 0x44: return LD_B_H;
		case 0x45: return LD_B_L;
		case 0x46: return LD_B_0xHL;
		case 0x47: return LD_B_A;
		case 0x48: return LD_C_B;
		case 0x49: return LD_C_C;
		case 0x4A: return LD_C_D;
		case 0x4B: return LD_C_E;
		case 0x4C: return LD_C_H;
		case 0x4D: return LD_C_L;
		case 0x4E: return LD_C_0xHL;
		case 0x4F: return LD_C_A;

		// (0x5_)
		case 0x50: return LD_D_B;
		case 0x51: return LD_D_C;
		case 0x52: return LD_D_D;
		case 0x53: return LD_D_E;
		case 0x54: return LD_D_H;
		case 0x55: return LD_D_L;
		case 0x56: return LD_D_0xHL;
		case 0x57: return LD_D_A;
		case 0x58: return LD_E_B;
		case 0x59: return LD_E_C;
		case 0x5A: return LD_E_D;
		case 0x5B: return LD_E_E;
		case 0x5C: return LD_E_H;
		case 0x5D: return LD_E_L;
		case 0x5E: return LD_E_0xHL;
		case 0x5F: return LD_E_A;

		// (0x6_)
		case 0x60: return LD_H_B;
		case 0x61: return LD_H_C;
		case 0x62: return LD_H_D;
		case 0x63: return LD_H_E;
		case 0x64: return LD_H_H;
		case 0x65: return LD_H_L;
		case 0x66: return LD_H_0xHL;
		case 0x67: return LD_H_A;
		case 0x68: return LD_L_B;
		case 0x69: return LD_L_C;
		case 0x6A: return LD_L_D;
		case 0x6B: return LD_L_E;
		case 0x6C: return LD_L_H;
		case 0x6D: return LD_L_L;
		case 0x6E: return LD_L_0xHL;
		case 0x6F: return LD_L_A;

		// (0x7_)
		case 0x70: return LD_0xHL_B;
		case 0x71: return LD_0xHL_C;
		case 0x72: return LD_0xHL_D;
		case 0x73: return LD_0xHL_E;
		case 0x74: return LD_0xHL_H;
		case 0x75: return LD_0xHL_L;
		case 0x76: return HALT;
		case 0x77: return LD_0xHL_A;
		case 0x78: return LD_A_B;
		case 0x79: return LD_A_C;
		case 0x7A: return LD_A_D;
		case 0x7B: return LD_A_E;
		case 0x7C: return LD_A_H;
		case 0x7D: return LD_A_L;
		case 0x7E: return LD_A_0xHL;
		case 0x7F: return LD_A_A;
		
		// (0x8_)
		case 0x80: return ADD_A_B;
		case 0x81: return ADD_A_C;
		case 0x82: return ADD_A_D;
		case 0x83: return ADD_A_E;
		case 0x84: return ADD_A_H;
		case 0x85: return ADD_A_L;
		case 0x86: return ADD_A_0xHL;
		case 0x87: return ADD_A_A;
		case 0x88: return ADC_A_B;
		case 0x89: return ADC_A_C;
		case 0x8A: return ADC_A_D;
		case 0x8B: return ADC_A_E;
		case 0x8C: return ADC_A_H;
		case 0x8D: return ADC_A_L;
		case 0x8E: return ADC_A_0xHL;
		case 0x8F: return ADC_A_A;

		// (0x9_)
		case 0x90: return SUB_A_B;
		case 0x91: return SUB_A_C;
		case 0x92: return SUB_A_D;
		case 0x93: return SUB_A_E;
		case 0x94: return SUB_A_H;
		case 0x95: return SUB_A_L;
		case 0x96: return SUB_A_0xHL;
		case 0x97: return SUB_A_A;
		case 0x98: return SBC_A_B;
		case 0x99: return SBC_A_C;
		case 0x9A: return SBC_A_D;
		case 0x9B: return SBC_A_E;
		case 0x9C: return SBC_A_H;
		case 0x9D: return SBC_A_L;
		case 0x9E: return SBC_A_0xHL;
		case 0x9F: return SBC_A_A;

		// (0xA_)
		case 0xA0: return AND_A_B;
		case 0xA1: return AND_A_C;
		case 0xA2: return AND_A_D;
		case 0xA3: return AND_A_E;
		case 0xA4: return AND_A_H;
		case 0xA5: return AND_A_L;
		case 0xA6: return AND_A_0xHL;
		case 0xA7: return AND_A_A;
		case 0xA8: return XOR_A_B;
		case 0xA9: return XOR_A_C;
		case 0xAA: return XOR_A_D;
		case 0xAB: return XOR_A_E;
		case 0xAC: return XOR_A_H;
		case 0xAD: return XOR_A_L;
		case 0xAE: return XOR_A_0xHL;
		case 0xAF: return XOR_A_A;

		// (0xB_)
		case 0xB0: return OR_A_B;
		case 0xB1: return OR_A_C;
		case 0xB2: return OR_A_D;
		case 0xB3: return OR_A_E;
		case 0xB4: return OR_A_H;
		case 0xB5: return OR_A_L;
		case 0xB6: return OR_A_0xHL;
		case 0xB7: return OR_A_A;
		case 0xB8: return CP_A_B;
		case 0xB9: return CP_A_C;
		case 0xBA: return CP_A_D;
		case 0xBB: return CP_A_E;
		case 0xBC: return CP_A_H;
		case 0xBD: return CP_A_L;
		case 0xBE: return CP_A_0xHL;
		case 0xBF: return CP_A_A;

		// (0xC_)
		case 0xC0: return RET_NZ;
		case 0xC1: return POP_BC;
		case 0xC2: return JP_NZ_U16;
		case 0xC3: return JP_U16;
		case 0xC4: return CALL_NZ_U16;
		case 0xC5: return PUSH_BC;
		case 0xC6: return ADD_A_U8;
		case 0xC7: return RST_00H;
		case 0xC8: return RET_Z;
		case 0xC9: return RET;
		case 0xCA: return JP_Z_U16;
		case 0xCB: return PREFIX_CB;
		case 0xCC: return CALL_Z_U16;
		case 0xCD: return CALL_U16;
		case 0xCE: return ADC_A_U8;
		case 0xCF: return RST_08H;

		// (0xD_)
		case 0xD0: return RET_NC;
		case 0xD1: return POP_DE;
		case 0xD2: return JP_NC_U16;
		// case 0xD3: return NULL;
		case 0xD4: return CALL_NC_U16;
		case 0xD5: return PUSH_DE;
		case 0xD6: return SUB_A_U8;
		case 0xD7: return RST_10H;
		case 0xD8: return RET_C;
		case 0xD9: return RETI;
		case 0xDA: return JP_C_U16;
		// case 0xDB: return NULL;
		case 0xDC: return CALL_C_U16;
		// case 0xDD: return NULL;
		case 0xDE: return SBC_A_U8;
		case 0xDF: return RST_18H;

		// (0xE_)
		case 0xE0: return LDH_0xU8_A;
		case 0xE1: return POP_HL;
		case 0xE2: return LDH_0xC_A;
		// case 0xE3: return NULL;
		// case 0xE4: return NULL;
		case 0xE5: return PUSH_HL;
		case 0xE6: return AND_A_U8;
		case 0xE7: return RST_20H;
		case 0xE8: return ADD_SP_I8;
		case 0xE9: return JP_HL;
		case 0xEA: return LD_0xU16_A;
		// case 0xEB: return NULL;
		// case 0xEC: return NULL;
		// case 0xED: return NULL;
		case 0xEE: return XOR_A_U8;
		case 0xEF: return RST_28H;

		// (0xF_)
		case 0xF0: return LDH_A_0xU8;
		case 0xF1: return POP_AF;
		case 0xF2: return LDH_A_0xC;
		case 0xF3: return DI;
		// case 0xF4: return NULL;
		case 0xF5: return PUSH_AF;
		case 0xF6: return OR_A_U8;
		case 0xF7: return RST_30H;
		case 0xF8: return LD_HL_SP_I8;
		case 0xF9: return LD_SP_HL;
		case 0xFA: return LD_A_0xU16;
		case 0xFB: return EI;
		// case 0xFC: return NULL;
		// case 0xFD: return NULL;
		case 0xFE: return CP_A_U8;
		case 0xFF: return RST_38H;
		
	}
	
	//opcode not yet implemented
	rge_log_error("Missing opcode: %x", opcode);
	rge_core_close();
}




//========================================================================




op_func gb_cpu_decode_ext(uint8_t opcode) {
	switch (opcode) {
		// (0x0_)
		case 0x00: return RLC_B;
		case 0x01: return RLC_C;
		case 0x02: return RLC_D;
		case 0x03: return RLC_E;
		case 0x04: return RLC_H;
		case 0x05: return RLC_L;
		case 0x06: return RLC_0xHL;
		case 0x07: return RLC_A;
		case 0x08: return RRC_B;
		case 0x09: return RRC_C;
		case 0x0A: return RRC_D;
		case 0x0B: return RRC_E;
		case 0x0C: return RRC_H;
		case 0x0D: return RRC_L;
		case 0x0E: return RRC_0xHL;
		case 0x0F: return RRC_A;
		
		// (0x1_)
		case 0x10: return RL_B;
		case 0x11: return RL_C;
		case 0x12: return RL_D;
		case 0x13: return RL_E;
		case 0x14: return RL_H;
		case 0x15: return RL_L;
		case 0x16: return RL_0xHL;
		case 0x17: return RL_A;
		case 0x18: return RR_B;
		case 0x19: return RR_C;
		case 0x1A: return RR_D;
		case 0x1B: return RR_E;
		case 0x1C: return RR_H;
		case 0x1D: return RR_L;
		case 0x1E: return RR_0xHL;
		case 0x1F: return RR_A;
		
		// (0x2_)
		case 0x20: return SLA_B;
		case 0x21: return SLA_C;
		case 0x22: return SLA_D;
		case 0x23: return SLA_E;
		case 0x24: return SLA_H;
		case 0x25: return SLA_L;
		case 0x26: return SLA_0xHL;
		case 0x27: return SLA_A;
		case 0x28: return SRA_B;
		case 0x29: return SRA_C;
		case 0x2A: return SRA_D;
		case 0x2B: return SRA_E;
		case 0x2C: return SRA_H;
		case 0x2D: return SRA_L;
		case 0x2E: return SRA_0xHL;
		case 0x2F: return SRA_A;
		
		// (0x3_)
		case 0x30: return SWAP_B;
		case 0x31: return SWAP_C;
		case 0x32: return SWAP_D;
		case 0x33: return SWAP_E;
		case 0x34: return SWAP_H;
		case 0x35: return SWAP_L;
		case 0x36: return SWAP_0xHL;
		case 0x37: return SWAP_A;
		case 0x38: return SRL_B;
		case 0x39: return SRL_C;
		case 0x3A: return SRL_D;
		case 0x3B: return SRL_E;
		case 0x3C: return SRL_H;
		case 0x3D: return SRL_L;
		case 0x3E: return SRL_0xHL;
		case 0x3F: return SRL_A;
		
		// (0x4_)
		case 0x40: return BIT_0_B;
		case 0x41: return BIT_0_C;
		case 0x42: return BIT_0_D;
		case 0x43: return BIT_0_E;
		case 0x44: return BIT_0_H;
		case 0x45: return BIT_0_L;
		case 0x46: return BIT_0_0xHL;
		case 0x47: return BIT_0_A;
		case 0x48: return BIT_1_B;
		case 0x49: return BIT_1_C;
		case 0x4A: return BIT_1_D;
		case 0x4B: return BIT_1_E;
		case 0x4C: return BIT_1_H;
		case 0x4D: return BIT_1_L;
		case 0x4E: return BIT_1_0xHL;
		case 0x4F: return BIT_1_A;
		
		// (0x5_)
		case 0x50: return BIT_2_B;
		case 0x51: return BIT_2_C;
		case 0x52: return BIT_2_D;
		case 0x53: return BIT_2_E;
		case 0x54: return BIT_2_H;
		case 0x55: return BIT_2_L;
		case 0x56: return BIT_2_0xHL;
		case 0x57: return BIT_2_A;
		case 0x58: return BIT_3_B;
		case 0x59: return BIT_3_C;
		case 0x5A: return BIT_3_D;
		case 0x5B: return BIT_3_E;
		case 0x5C: return BIT_3_H;
		case 0x5D: return BIT_3_L;
		case 0x5E: return BIT_3_0xHL;
		case 0x5F: return BIT_3_A;
		
		// (0x6_)
		case 0x60: return BIT_4_B;
		case 0x61: return BIT_4_C;
		case 0x62: return BIT_4_D;
		case 0x63: return BIT_4_E;
		case 0x64: return BIT_4_H;
		case 0x65: return BIT_4_L;
		case 0x66: return BIT_4_0xHL;
		case 0x67: return BIT_4_A;
		case 0x68: return BIT_5_B;
		case 0x69: return BIT_5_C;
		case 0x6A: return BIT_5_D;
		case 0x6B: return BIT_5_E;
		case 0x6C: return BIT_5_H;
		case 0x6D: return BIT_5_L;
		case 0x6E: return BIT_5_0xHL;
		case 0x6F: return BIT_5_A;
		
		// (0x7_)
		case 0x70: return BIT_6_B;
		case 0x71: return BIT_6_C;
		case 0x72: return BIT_6_D;
		case 0x73: return BIT_6_E;
		case 0x74: return BIT_6_H;
		case 0x75: return BIT_6_L;
		case 0x76: return BIT_6_0xHL;
		case 0x77: return BIT_6_A;
		case 0x78: return BIT_7_B;
		case 0x79: return BIT_7_C;
		case 0x7A: return BIT_7_D;
		case 0x7B: return BIT_7_E;
		case 0x7C: return BIT_7_H;
		case 0x7D: return BIT_7_L;
		case 0x7E: return BIT_7_0xHL;
		case 0x7F: return BIT_7_A;
		
		// (0x8_)
		case 0x80: return RES_0_B;
		case 0x81: return RES_0_C;
		case 0x82: return RES_0_D;
		case 0x83: return RES_0_E;
		case 0x84: return RES_0_H;
		case 0x85: return RES_0_L;
		case 0x86: return RES_0_0xHL;
		case 0x87: return RES_0_A;
		case 0x88: return RES_1_B;
		case 0x89: return RES_1_C;
		case 0x8A: return RES_1_D;
		case 0x8B: return RES_1_E;
		case 0x8C: return RES_1_H;
		case 0x8D: return RES_1_L;
		case 0x8E: return RES_1_0xHL;
		case 0x8F: return RES_1_A;
		
		// (0x9_)
		case 0x90: return RES_2_B;
		case 0x91: return RES_2_C;
		case 0x92: return RES_2_D;
		case 0x93: return RES_2_E;
		case 0x94: return RES_2_H;
		case 0x95: return RES_2_L;
		case 0x96: return RES_2_0xHL;
		case 0x97: return RES_2_A;
		case 0x98: return RES_3_B;
		case 0x99: return RES_3_C;
		case 0x9A: return RES_3_D;
		case 0x9B: return RES_3_E;
		case 0x9C: return RES_3_H;
		case 0x9D: return RES_3_L;
		case 0x9E: return RES_3_0xHL;
		case 0x9F: return RES_3_A;
		
		// (0xA_)
		case 0xA0: return RES_4_B;
		case 0xA1: return RES_4_C;
		case 0xA2: return RES_4_D;
		case 0xA3: return RES_4_E;
		case 0xA4: return RES_4_H;
		case 0xA5: return RES_4_L;
		case 0xA6: return RES_4_0xHL;
		case 0xA7: return RES_4_A;
		case 0xA8: return RES_5_B;
		case 0xA9: return RES_5_C;
		case 0xAA: return RES_5_D;
		case 0xAB: return RES_5_E;
		case 0xAC: return RES_5_H;
		case 0xAD: return RES_5_L;
		case 0xAE: return RES_5_0xHL;
		case 0xAF: return RES_5_A;
		
		// (0xB_)
		case 0xB0: return RES_6_B;
		case 0xB1: return RES_6_C;
		case 0xB2: return RES_6_D;
		case 0xB3: return RES_6_E;
		case 0xB4: return RES_6_H;
		case 0xB5: return RES_6_L;
		case 0xB6: return RES_6_0xHL;
		case 0xB7: return RES_6_A;
		case 0xB8: return RES_7_B;
		case 0xB9: return RES_7_C;
		case 0xBA: return RES_7_D;
		case 0xBB: return RES_7_E;
		case 0xBC: return RES_7_H;
		case 0xBD: return RES_7_L;
		case 0xBE: return RES_7_0xHL;
		case 0xBF: return RES_7_A;
		
		// (0xC_)
		case 0xC0: return SET_0_B;
		case 0xC1: return SET_0_C;
		case 0xC2: return SET_0_D;
		case 0xC3: return SET_0_E;
		case 0xC4: return SET_0_H;
		case 0xC5: return SET_0_L;
		case 0xC6: return SET_0_0xHL;
		case 0xC7: return SET_0_A;
		case 0xC8: return SET_1_B;
		case 0xC9: return SET_1_C;
		case 0xCA: return SET_1_D;
		case 0xCB: return SET_1_E;
		case 0xCC: return SET_1_H;
		case 0xCD: return SET_1_L;
		case 0xCE: return SET_1_0xHL;
		case 0xCF: return SET_1_A;
		
		// (0xD_)
		case 0xD0: return SET_2_B;
		case 0xD1: return SET_2_C;
		case 0xD2: return SET_2_D;
		case 0xD3: return SET_2_E;
		case 0xD4: return SET_2_H;
		case 0xD5: return SET_2_L;
		case 0xD6: return SET_2_0xHL;
		case 0xD7: return SET_2_A;
		case 0xD8: return SET_3_B;
		case 0xD9: return SET_3_C;
		case 0xDA: return SET_3_D;
		case 0xDB: return SET_3_E;
		case 0xDC: return SET_3_H;
		case 0xDD: return SET_3_L;
		case 0xDE: return SET_3_0xHL;
		case 0xDF: return SET_3_A;
		
		// (0xE_)
		case 0xE0: return SET_4_B;
		case 0xE1: return SET_4_C;
		case 0xE2: return SET_4_D;
		case 0xE3: return SET_4_E;
		case 0xE4: return SET_4_H;
		case 0xE5: return SET_4_L;
		case 0xE6: return SET_4_0xHL;
		case 0xE7: return SET_4_A;
		case 0xE8: return SET_5_B;
		case 0xE9: return SET_5_C;
		case 0xEA: return SET_5_D;
		case 0xEB: return SET_5_E;
		case 0xEC: return SET_5_H;
		case 0xED: return SET_5_L;
		case 0xEE: return SET_5_0xHL;
		case 0xEF: return SET_5_A;
		
		// (0xF_)
		case 0xF0: return SET_6_B;
		case 0xF1: return SET_6_C;
		case 0xF2: return SET_6_D;
		case 0xF3: return SET_6_E;
		case 0xF4: return SET_6_H;
		case 0xF5: return SET_6_L;
		case 0xF6: return SET_6_0xHL;
		case 0xF7: return SET_6_A;
		case 0xF8: return SET_7_B;
		case 0xF9: return SET_7_C;
		case 0xFA: return SET_7_D;
		case 0xFB: return SET_7_E;
		case 0xFC: return SET_7_H;
		case 0xFD: return SET_7_L;
		case 0xFE: return SET_7_0xHL;
		case 0xFF: return SET_7_A;
	}

	//opcode not yet implemented
	rge_log_error("Missing opcode: 0xCB -> %x", opcode);
	rge_core_close();
}