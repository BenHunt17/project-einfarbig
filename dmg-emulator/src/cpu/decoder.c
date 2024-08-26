#include "decoder.h"

#include "instructions/8_bit_load_instructions.h"
#include "instructions/16_bit_load_instructions.h"
#include "instructions/8_bit_arithmetic_logic_instructions.h"
#include "instructions/16_bit_arithmetic_logic_instructions.h"
#include "instructions/rotate_shift_instructions.h"
#include "instructions/general_purpose_instructions.h"
#include "instructions/bit_instructions.h"
#include "instructions/jump_instructions.h"
#include "instructions/call_return_instructions.h"

RegisterPair decode_register_pair_sp(uint8_t opcode_fragment) {
	switch (opcode_fragment) {
		case 0x0:
			return REGISTER_PAIR_BC;
		case 0x1:
			return REGISTER_PAIR_DE;
		case 0x2:
			return REGISTER_PAIR_HL;
		default:
			return REGISTER_PAIR_SP;
	}
}

RegisterPair decode_register_pair_af(uint8_t opcode_fragment) {
	switch (opcode_fragment) {
		case 0x0:
			return REGISTER_PAIR_BC;
		case 0x1:
			return REGISTER_PAIR_DE;
		case 0x2:
			return REGISTER_PAIR_HL;
		default:
			return REGISTER_PAIR_AF;
	}
}

uint8_t decode_register(uint8_t opcode_fragment) {
	switch (opcode_fragment) {
		case 0x0:
			return REGISTER_B;
		case 0x1:
			return REGISTER_C;
		case 0x2:
			return REGISTER_D;
		case 0x3:
			return REGISTER_E;
		case 0x4:
			return REGISTER_H;
		case 0x5:
			return REGISTER_L;
		default:
			return REGISTER_A;
	}
}

int decode_execute(Cpu* cpu, uint8_t opcode) {
	int cycles = 0;

	switch (opcode) {
		case 0x40: case 0x42: case 0x43: case 0x44: case 0x45: case 0x47: case 0x48: case 0x49: case 0x4a: case 0x4b: case 0x4c: case 0x4d: case 0x4f:
		case 0x50: case 0x52: case 0x53: case 0x54: case 0x55: case 0x57: case 0x58: case 0x59: case 0x5a: case 0x5b: case 0x5c: case 0x5d: case 0x5f:
		case 0x60: case 0x62: case 0x63: case 0x64: case 0x65: case 0x67: case 0x68: case 0x69: case 0x6a: case 0x6b: case 0x6c: case 0x6d: case 0x6f:
		case 0x78: case 0x79: case 0x7a: case 0x7b: case 0x7c: case 0x7d: case 0x7f:
			cycles = ld_r_r(cpu,
				decode_register(opcode & 7),
				decode_register((opcode >> 3) & 7));
			break;

		case 0x06: case 0x16: case 0x26: case 0x0e: case 0x1e: case 0x2e: case 0x3e:
			cycles = ld_r_n(cpu,
				decode_register((opcode >> 3) & 7));
			break;

		case 0x46: case 0x56: case 0x66: case 0x4e: case 0x5e: case 0x6e: case 0x7e:
			cycles = ld_r_hl(cpu,
				decode_register((opcode >> 3) & 7));
			break;

		case 0x70: case 0x71:case 0x72:case 0x73:case 0x74:case 0x75:case 0x77:
			cycles = ld_hl_r(cpu, decode_register(opcode & 7));
			break;

		case 0x36:
			cycles = ld_hl_n(cpu);
			break;

		case 0x0a:
			cycles = ld_a_bc(cpu);
			break;

		case 0x1a:
			cycles = ld_a_de(cpu);
			break;

		case 0xf2:
			cycles = ld_a_c(cpu);
			break;

		case 0xe2:
			cycles = ld_c_a(cpu);
			break;

		case 0xf0:
			cycles = ld_a_n(cpu);
			break;

		case 0xe0:
			cycles = ld_n_a(cpu);
			break;

		case 0xfa:
			cycles = ld_a_nn(cpu);
			break;

		case 0xea:
			cycles = ld_nn_a(cpu);
			break;

		case 0x2a:
			cycles = ldi_a_hl(cpu);
			break;

		case 0x3a:
			cycles = ldd_a_hl(cpu);
			break;

		case 0x02:
			cycles = ld_bc_a(cpu);
			break;

		case 0x12:
			cycles = ld_de_a(cpu);
			break;

		case 0x22:
			cycles = ldi_hl_a(cpu);
			break;

		case 0x32:
			cycles = ldd_hl_a(cpu);
			break;

		case 0x01: case 0x11: case 0x21: case 0x31:
			cycles = ld_rr_nn(cpu,
				decode_register_pair_sp((opcode >> 4) & 3));
			break;

		case 0xf9:
			cycles = ld_sp_hl(cpu);
			break;

		case 0xc5: case 0xd5: case 0xe5: case 0xf5:
			cycles = push_rr(cpu,
				decode_register_pair_af((opcode >> 4) & 3));
			break;

		case 0xc1: case 0xd1: case 0xe1: case 0xf1:
			cycles = pop_rr(cpu,
				decode_register_pair_af((opcode >> 4) & 3));
			break;

		case 0xf8:
			cycles = ld_hl_sp_e(cpu);
			break;

		case 0x08:
			cycles = ld_nn_sp(cpu);
			break;

		case 0x80: case 0x81: case 0x82: case 0x84: case 0x85: case 0x87:
			cycles = add_a_r(cpu, decode_register(opcode & 7));
			break;

		case 0xc6:
			cycles = add_a_n(cpu);
			break;

		case 0x86:
			cycles = add_a_hl(cpu);
			break;

		case 0x88: case 0x89: case 0x8a: case 0x8b: case 0x8c: case 0x8d: case 0x8f:
			cycles = adc_a_r(cpu, decode_register(opcode & 7));
			break;

		case 0xce:
			cycles = adc_a_n(cpu);
			break;

		case 0x8e:
			cycles = adc_a_hl(cpu);
			break;

		case 0x90: case 0x91: case 0x92: case 0x93: case 0x94: case 0x95: case 0x97:
			cycles = sub_a_r(cpu, decode_register(opcode & 7));
			break;

		case 0xd6:
			cycles = sub_a_n(cpu);
			break;

		case 0x96:
			cycles = sub_a_hl(cpu);
			break;

		case 0x98: case 0x99: case 0x9a: case 0x9b: case 0x9c: case 0x9d: case 0x9f:
			cycles = sbc_a_r(cpu, decode_register(opcode & 7));

		case 0xde:
			cycles = sbc_a_n(cpu);
			break;

		case 0x9e:
			cycles = sbc_a_hl(cpu);
			break;

		case 0xa0: case 0xa1: case 0xa2: case 0xa3: case 0xa4: case 0xa5: case 0xa7:
			cycles = and_a_r(cpu, decode_register(opcode & 7));

		case 0xe6:
			cycles = and_a_n(cpu);
			break;

		case 0xa6:
			cycles = and_a_hl(cpu);
			break;

		case 0xb0: case 0xb1: case 0xb2: case 0xb3: case 0xb4: case 0xb5: case 0xb7:
			cycles = or_a_r(cpu, decode_register(opcode & 7));

		case 0xf6:
			cycles = or_a_n(cpu);
			break;

		case 0xb6:
			cycles = or_a_hl(cpu);
			break;

		case 0xa8: case 0xa9: case 0xaa: case 0xab: case 0xac: case 0xad: case 0xaf:
			cycles = xor_a_r(cpu, decode_register(opcode & 7));

		case 0xee:
			cycles = xor_a_n(cpu);
			break;

		case 0xae:
			cycles = xor_a_hl(cpu);
			break;

		case 0xb8: case 0xb9: case 0xba: case 0xbb: case 0xbc: case 0xbd: case 0xbf:
			cycles = cp_a_r(cpu, decode_register(opcode & 7));

		case 0xfe:
			cycles = cp_a_n(cpu);
			break;

		case 0xbe:
			cycles = cp_a_hl(cpu);
			break;

		case 0x04: case 0x0c: case 0x14: case 0x1c: case 0x24: case 0x2c: case 0x3c:
			cycles = inc_r(cpu,
				decode_register((opcode >> 3) & 7));
			break;

		case 0x34:
			cycles = inc_hl(cpu);
			break;

		case 0x05: case 0x0d: case 0x15: case 0x1d: case 0x25: case 0x2d: case 0x3d:
			cycles = dec_r(cpu,
				decode_register((opcode >> 3) & 7));
			break;

		case 0x35:
			cycles = dec_hl(cpu);
			break;

		case 0x09: case 0x19: case 0x29: case 0x39:
			cycles = add_hl_rr(cpu,
				decode_register_pair_sp((opcode >> 4) & 3));
			break;

		case 0xe8:
			cycles = add_sp_e(cpu);
			break;

		case 0x03: case 0x13: case 0x23: case 0x33:
			cycles = inc_rr(cpu,
				decode_register_pair_sp((opcode >> 4) & 3));
			break;

		case 0x0b: case 0x1b: case 0x2b: case 0x3b:
			cycles = dec_rr(cpu,
				decode_register_pair_sp((opcode >> 4) & 3));
			break;

		case 0x07:
			cycles = rlca(cpu);
			break;

		case 0x17:
			cycles = rla(cpu);
			break;

		case 0x0f:
			cycles = rrca(cpu);
			break;

		case 0x1f:
			cycles = rra(cpu);
			break;
	}

	return cycles;
}

int decode_execute_extended_set(Cpu* cpu, uint8_t opcode) {
	//TODO - when i get to interupts, reread this: https://www.reddit.com/r/EmuDev/comments/7qf352/game_boy_is_0xcb_a_separate_instruction_are/
	int cycles = 0;

	switch (opcode) {
		case 0x00: case 0x01: case 0x02: case 0x03: case 0x04: case 0x05: case 0x07:
			cycles = rlc_r(cpu, decode_register(opcode & 7));
			break;

		case 0x06:
			cycles = rlc_hl(cpu);
			break;

		case 0x10: case 0x11: case 0x12: case 0x13: case 0x14: case 0x15: case 0x17:
			cycles = rl_r(cpu, decode_register(opcode & 7));
			break;

		case 0x16:
			cycles = rl_hl(cpu);
			break;

		case 0x08: case 0x09: case 0x0a: case 0x0b: case 0x0c: case 0x0d: case 0x0f:
			cycles = rrc_r(cpu, decode_register(opcode & 7));
			break;

		case 0x0e:
			cycles = rrc_hl(cpu);
			break;

		case 0x18: case 0x19: case 0x1a: case 0x1b: case 0x1c: case 0x1d: case 0x1f:
			cycles = rr_r(cpu, decode_register(opcode & 7));
			break;

		case 0x1e:
			cycles = rr_hl(cpu);
			break;

		case 0x20: case 0x21: case 0x22: case 0x23: case 0x24: case 0x25: case 0x27:
			cycles = sla_r(cpu, decode_register(opcode & 7));
			break;

		case 0x26:
			cycles = sla_hl(cpu);
			break;

		case 0x28: case 0x29: case 0x2a: case 0x2b: case 0x2c: case 0x2d: case 0x2f:
			cycles = sra_r(cpu, decode_register(opcode & 7));
			break;

		case 0x2e:
			cycles = sra_hl(cpu);
			break;

		case 0x38: case 0x39: case 0x3a: case 0x3b: case 0x3c: case 0x3d: case 0x3f:
			cycles = srl_r(cpu, decode_register(opcode & 7));
			break;

		case 0x3e:
			cycles = srl_hl(cpu);
			break;

		case 0x30: case 0x31: case 0x32: case 0x33: case 0x34: case 0x35: case 0x37:
			cycles = swap_r(cpu, decode_register(opcode & 7));
			break;

		case 0x36:
			cycles = swap_hl(cpu);
			break;

		case 0x40: case 0x41: case 0x42: case 0x43: case 0x44: case 0x45: case 0x47: case 0x48: case 0x49: case 0x4a: case 0x4b: case 0x4c: case 0x4d: case 0x4f:
		case 0x50: case 0x51: case 0x52: case 0x53: case 0x54: case 0x55: case 0x57: case 0x58: case 0x59: case 0x5a: case 0x5b: case 0x5c: case 0x5d: case 0x5f:
		case 0x60: case 0x61: case 0x62: case 0x63: case 0x64: case 0x65: case 0x67: case 0x68: case 0x69: case 0x6a: case 0x6b: case 0x6c: case 0x6d: case 0x6f:
		case 0x70: case 0x71: case 0x72: case 0x73: case 0x74: case 0x75: case 0x77: case 0x78: case 0x79: case 0x7a: case 0x7b: case 0x7c: case 0x7d: case 0x7f:
			cycles = bit_b_r(cpu,
				(opcode >> 3) & 7,
				decode_register(opcode & 7));
			break;

		case 0x46: case 0x56: case 0x66: case 0x76: case 0x4e: case 0x5e: case 0x6e: case 0x7e:
			cycles = bit_b_hl(cpu, (opcode >> 3) & 7);
			break;

		case 0xc0: case 0xc1: case 0xc2: case 0xc3: case 0xc4: case 0xc5: case 0xc7: case 0xc8: case 0xc9: case 0xca: case 0xcb: case 0xcc: case 0xcd: case 0xcf:
		case 0xd0: case 0xd1: case 0xd2: case 0xd3: case 0xd4: case 0xd5: case 0xd7: case 0xd8: case 0xd9: case 0xda: case 0xdb: case 0xdc: case 0xdd: case 0xdf:
		case 0xe0: case 0xe1: case 0xe2: case 0xe3: case 0xe4: case 0xe5: case 0xe7: case 0xe8: case 0xe9: case 0xea: case 0xeb: case 0xec: case 0xed: case 0xef:
		case 0xf0: case 0xf1: case 0xf2: case 0xf3: case 0xf4: case 0xf5: case 0xf7: case 0xf8: case 0xf9: case 0xfa: case 0xfb: case 0xfc: case 0xfd: case 0xff:
			cycles = set_b_r(cpu,
				(opcode >> 3) & 7,
				decode_register(opcode & 7));
			break;

		case 0xc6: case 0xd6: case 0xe6: case 0xf6: case 0xce: case 0xde: case 0xee: case 0xfe:
			cycles = set_b_hl(cpu, (opcode >> 3) & 7);
			break;

		case 0x80: case 0x81: case 0x82: case 0x83: case 0x84: case 0x85: case 0x87: case 0x88: case 0x89: case 0x8a: case 0x8b: case 0x8c: case 0x8d: case 0x8f:
		case 0x90: case 0x91: case 0x92: case 0x93: case 0x94: case 0x95: case 0x97: case 0x98: case 0x99: case 0x9a: case 0x9b: case 0x9c: case 0x9d: case 0x9f: 
		case 0xa0: case 0xa1: case 0xa2: case 0xa3: case 0xa4: case 0xa5: case 0xa7: case 0xa8: case 0xa9: case 0xaa: case 0xab: case 0xac: case 0xad: case 0xaf: 
		case 0xb0: case 0xb1: case 0xb2: case 0xb3: case 0xb4: case 0xb5: case 0xb7: case 0xb8: case 0xb9: case 0xba: case 0xbb: case 0xbc: case 0xbd: case 0xbf:
			cycles = res_b_r(cpu,
				(opcode >> 3) & 7,
				decode_register(opcode & 7));
			break;

		case 0x86: case 0x96: case 0xa6: case 0xb6: case 0x8e: case 0x9e: case 0xae: case 0xbe:
			cycles = res_b_hl(cpu, (opcode >> 3) & 7);
			break;
	}

	return cycles;
}