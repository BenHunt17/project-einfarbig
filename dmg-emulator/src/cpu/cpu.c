#include <stdlib.h>

#include "cpu.h"

#include "8_bit_load_instructions.h"
#include "16_bit_load_instructions.h"
#include "8_bit_arithmetic_logic_instructions.h"
#include "control_instructions.h"

void initialise_cpu(Cpu* cpu) {
	cpu->pc = 0x100;
	cpu->sp = 0xfffe;

	initialise_bus(cpu->bus); //TODO - review

	cpu->elapsedInstructionCycles = 0;
	cpu->instructionCycleCount = 0;
}

void free_cpu(Cpu* cpu) {
	free_bus(cpu->bus);
	free(cpu);
}

uint8_t fetch8(Cpu* cpu) {
	uint8_t byte = read_byte(cpu->bus, cpu->pc);
	cpu->pc++;
	return byte;
}

uint16_t fetch16(Cpu* cpu) {
	uint8_t low_byte = fetch8(cpu);
	uint8_t high_byte = fetch8(cpu);
	return (high_byte << 8) | low_byte;
}

uint16_t read_register_pair(Cpu* cpu, RegisterPair register_pair) {
	return (cpu->registers[register_pair] << 8) | cpu->registers[register_pair + 1];
}

void write_register_pair(Cpu* cpu, RegisterPair register_pair, uint16_t data) {
	cpu->registers[register_pair] = (uint8_t)((data >> 8) & 0xff);
	cpu->registers[register_pair + 1] = (uint8_t)(data & 0xff);
}

bool get_flag(Cpu* state, uint8_t flag_bit) {
	return (state->registers[1] >> flag_bit) & 0x1;
}

void set_flag(Cpu* state, uint8_t flag_bit, bool is_set) {
	if (is_set) {
		state->registers[1] |= (0x1 << flag_bit);
	}
	else {
		state->registers[1] &= ~(0x1 << flag_bit);
	}
}

void cpu_cycle(Cpu* cpu) {
	if (cpu->elapsedInstructionCycles == 0) {
		uint8_t opcode = fetch8(cpu);

		int cycles;
		switch (opcode) {
			//TODO - there are apprently more clever ways of decoding the opcode. maybe look into once I'm more confident around this instruction set [https://www.reddit.com/r/EmuDev/comments/scps99/gameboy_is_it_necessary_to_implement_the/]
			case 0x00:
				cycles = nop();
				break;
			case 0x01:
				cycles = ld_rr_nn(cpu, REGISTER_PAIR_BC);
				break;
			case 0x02:
				cycles = ld_bc_a(cpu);
				break;
			case 0x06:
				cycles = ld_r_n(cpu, REGISTER_B);
				break;
			case 0x08:
				cycles = ld_nn_sp(cpu);
				break;
			case 0x0a:
				cycles = ld_a_bc(cpu);
				break;
			case 0x0e:
				cycles = ld_r_n(cpu, REGISTER_C);
				break;
			case 0x11:
				cycles = ld_rr_nn(cpu, REGISTER_PAIR_DE);
				break;
			case 0x12:
				cycles = ld_de_a(cpu);
				break;
			case 0x16:
				cycles = ld_r_n(cpu, REGISTER_D);
				break;
			case 0x1a:
				cycles = ld_a_de(cpu);
				break;
			case 0x1e:
				cycles = ld_r_n(cpu, REGISTER_E);
				break;
			case 0x21:
				cycles = ld_rr_nn(cpu, REGISTER_PAIR_HL);
				break;
			case 0x22:
				cycles = ldi_hl_a(cpu);
				break;
			case 0x26:
				cycles = ld_r_n(cpu, REGISTER_H);
				break;
			case 0x2a:
				cycles = ldi_a_hl(cpu);
				break;
			case 0x2e:
				cycles = ld_r_n(cpu, REGISTER_L);
				break;
			case 0x31:
				cycles = ld_rr_nn(cpu, NULL);
				break;
			case 0x32:
				cycles = ldd_hl_a(cpu);
				break;
			case 0x36:
				cycles = ld_hl_n(cpu);
				break;
			case 0x3a:
				cycles = ldd_a_hl(cpu);
				break;
			case 0x3e:
				cycles = ld_r_n(cpu, REGISTER_A);
				break;
			case 0x40:
				cycles = ld_r_r(cpu, REGISTER_B, REGISTER_B);
				break;
			case 0x41:
				cycles = ld_r_r(cpu, REGISTER_B, REGISTER_C);
				break;
			case 0x42:
				cycles = ld_r_r(cpu, REGISTER_B, REGISTER_D);
				break;
			case 0x43:
				cycles = ld_r_r(cpu, REGISTER_B, REGISTER_E);
				break;
			case 0x44:
				cycles = ld_r_r(cpu, REGISTER_B, REGISTER_H);
				break;
			case 0x45:
				cycles = ld_r_r(cpu, REGISTER_B, REGISTER_L);
				break;
			case 0x46:
				cycles = ld_r_hl(cpu, REGISTER_B);
				break;
			case 0x47:
				cycles = ld_r_r(cpu, REGISTER_B, REGISTER_A);
				break;
			case 0x48:
				cycles = ld_r_r(cpu, REGISTER_C, REGISTER_B);
				break;
			case 0x49:
				cycles = ld_r_r(cpu, REGISTER_C, REGISTER_C);
				break;
			case 0x4a:
				cycles = ld_r_r(cpu, REGISTER_C, REGISTER_D);
				break;
			case 0x4b:
				cycles = ld_r_r(cpu, REGISTER_C, REGISTER_E);
				break;
			case 0x4c:
				cycles = ld_r_r(cpu, REGISTER_C, REGISTER_H);
				break;
			case 0x4d:
				cycles = ld_r_r(cpu, REGISTER_C, REGISTER_L);
				break;
			case 0x4e:
				cycles = ld_r_hl(cpu, REGISTER_C);
				break;
			case 0x4f:
				cycles = ld_r_r(cpu, REGISTER_C, REGISTER_A);
				break;
			case 0x50:
				cycles = ld_r_r(cpu, REGISTER_D, REGISTER_B);
				break;
			case 0x51:
				cycles = ld_r_r(cpu, REGISTER_D, REGISTER_C);
				break;
			case 0x52:
				cycles = ld_r_r(cpu, REGISTER_D, REGISTER_D);
				break;
			case 0x53:
				cycles = ld_r_r(cpu, REGISTER_D, REGISTER_E);
				break;
			case 0x54:
				cycles = ld_r_r(cpu, REGISTER_D, REGISTER_H);
				break;
			case 0x55:
				cycles = ld_r_r(cpu, REGISTER_D, REGISTER_L);
				break;
			case 0x56:
				cycles = ld_r_hl(cpu, REGISTER_D);
				break;
			case 0x57:
				cycles = ld_r_r(cpu, REGISTER_D, REGISTER_A);
				break;
			case 0x58:
				cycles = ld_r_r(cpu, REGISTER_E, REGISTER_B);
				break;
			case 0x59:
				cycles = ld_r_r(cpu, REGISTER_E, REGISTER_C);
				break;
			case 0x5a:
				cycles = ld_r_r(cpu, REGISTER_E, REGISTER_D);
				break;
			case 0x5b:
				cycles = ld_r_r(cpu, REGISTER_E, REGISTER_E);
				break;
			case 0x5c:
				cycles = ld_r_r(cpu, REGISTER_E, REGISTER_H);
				break;
			case 0x5d:
				cycles = ld_r_r(cpu, REGISTER_E, REGISTER_L);
				break;
			case 0x5e:
				cycles = ld_r_hl(cpu, REGISTER_E);
				break;
			case 0x5f:
				cycles = ld_r_r(cpu, REGISTER_E, REGISTER_A);
				break;
			case 0x60:
				cycles = ld_r_r(cpu, REGISTER_H, REGISTER_B);
				break;
			case 0x61:
				cycles = ld_r_r(cpu, REGISTER_H, REGISTER_C);
				break;
			case 0x62:
				cycles = ld_r_r(cpu, REGISTER_H, REGISTER_D);
				break;
			case 0x63:
				cycles = ld_r_r(cpu, REGISTER_H, REGISTER_E);
				break;
			case 0x64:
				cycles = ld_r_r(cpu, REGISTER_H, REGISTER_H);
				break;
			case 0x65:
				cycles = ld_r_r(cpu, REGISTER_H, REGISTER_L);
				break;
			case 0x66:
				cycles = ld_r_hl(cpu, REGISTER_H);
				break;
			case 0x67:
				cycles = ld_r_r(cpu, REGISTER_H, REGISTER_A);
				break;
			case 0x68:
				cycles = ld_r_r(cpu, REGISTER_L, REGISTER_B);
				break;
			case 0x69:
				cycles = ld_r_r(cpu, REGISTER_L, REGISTER_C);
				break;
			case 0x6a:
				cycles = ld_r_r(cpu, REGISTER_L, REGISTER_D);
				break;
			case 0x6b:
				cycles = ld_r_r(cpu, REGISTER_L, REGISTER_E);
				break;
			case 0x6c:
				cycles = ld_r_r(cpu, REGISTER_L, REGISTER_H);
				break;
			case 0x6d:
				cycles = ld_r_r(cpu, REGISTER_L, REGISTER_L);
				break;
			case 0x6e:
				cycles = ld_r_hl(cpu, REGISTER_L);
				break;
			case 0x6f:
				cycles = ld_r_r(cpu, REGISTER_L, REGISTER_A);
				break;
			case 0x70:
				cycles = ld_hl_r(cpu, REGISTER_B);
				break;
			case 0x71:
				cycles = ld_hl_r(cpu, REGISTER_C);
				break;
			case 0x72:
				cycles = ld_hl_r(cpu, REGISTER_D);
				break;
			case 0x73:
				cycles = ld_hl_r(cpu, REGISTER_E);
				break;
			case 0x74:
				cycles = ld_hl_r(cpu, REGISTER_H);
				break;
			case 0x75:
				cycles = ld_hl_r(cpu, REGISTER_L);
				break;
			case 0x77:
				cycles = ld_hl_r(cpu, REGISTER_A);
				break;
			case 0x78:
				cycles = ld_r_r(cpu, REGISTER_A, REGISTER_B);
				break;
			case 0x79:
				cycles = ld_r_r(cpu, REGISTER_A, REGISTER_C);
				break;
			case 0x7a:
				cycles = ld_r_r(cpu, REGISTER_A, REGISTER_D);
				break;
			case 0x7b:
				cycles = ld_r_r(cpu, REGISTER_A, REGISTER_E);
				break;
			case 0x7c:
				cycles = ld_r_r(cpu, REGISTER_A, REGISTER_H);
				break;
			case 0x7d:
				cycles = ld_r_r(cpu, REGISTER_A, REGISTER_L);
				break;
			case 0x7e:
				cycles = ld_r_hl(cpu, REGISTER_A);
				break;
			case 0x7f:
				cycles = ld_r_r(cpu, REGISTER_A, REGISTER_A);
				break;
			case 0x80:
				cycles = add_a_r(cpu, REGISTER_B);
				break;
			case 0x81:
				cycles = add_a_r(cpu, REGISTER_C);
				break;
			case 0x82:
				cycles = add_a_r(cpu, REGISTER_D);
				break;
			case 0x83:
				cycles = add_a_r(cpu, REGISTER_E);
				break;
			case 0x84:
				cycles = add_a_r(cpu, REGISTER_H);
				break;
			case 0x85:
				cycles = add_a_r(cpu, REGISTER_L);
				break;
			case 0x86:
				cycles = add_a_hl(cpu);
				break;
			case 0x87:
				cycles = add_a_r(cpu, REGISTER_A);
				break;
			case 0x88:
				cycles = adc_a_r(cpu, REGISTER_B);
				break;
			case 0x89:
				cycles = adc_a_r(cpu, REGISTER_C);
				break;
			case 0x8a:
				cycles = adc_a_r(cpu, REGISTER_D);
				break;
			case 0x8b:
				cycles = adc_a_r(cpu, REGISTER_E);
				break;
			case 0x8c:
				cycles = adc_a_r(cpu, REGISTER_H);
				break;
			case 0x8d:
				cycles = adc_a_r(cpu, REGISTER_L);
				break;
			case 0x8e:
				cycles = adc_a_hl(cpu);
				break;
			case 0x8f:
				cycles = adc_a_r(cpu, REGISTER_A);
				break;
			case 0x90:
				cycles = sub_a_r(cpu, REGISTER_B);
				break;
			case 0x91:
				cycles = sub_a_r(cpu, REGISTER_C);
				break;
			case 0x92:
				cycles = sub_a_r(cpu, REGISTER_D);
				break;
			case 0x93:
				cycles = sub_a_r(cpu, REGISTER_E);
				break;
			case 0x94:
				cycles = sub_a_r(cpu, REGISTER_H);
				break;
			case 0x95:
				cycles = sub_a_r(cpu, REGISTER_L);
				break;
			case 0x96:
				cycles = sub_a_hl(cpu);
				break;
			case 0x97:
				cycles = sub_a_r(cpu, REGISTER_A);
				break;
			case 0x98:
				cycles = sbc_a_r(cpu, REGISTER_B);
				break;
			case 0x99:
				cycles = sbc_a_r(cpu, REGISTER_C);
				break;
			case 0x9a:
				cycles = sbc_a_r(cpu, REGISTER_D);
				break;
			case 0x9b:
				cycles = sbc_a_r(cpu, REGISTER_E);
				break;
			case 0x9c:
				cycles = sbc_a_r(cpu, REGISTER_H);
				break;
			case 0x9d:
				cycles = sbc_a_r(cpu, REGISTER_L);
				break;
			case 0x9e:
				cycles = sbc_a_hl(cpu);
				break;
			case 0x9f:
				cycles = sbc_a_r(cpu, REGISTER_A);
				break;
			case 0xa0:
				cycles = and_a_r(cpu, REGISTER_B);
				break;
			case 0xa1:
				cycles = and_a_r(cpu, REGISTER_C);
				break;
			case 0xa2:
				cycles = and_a_r(cpu, REGISTER_D);
				break;
			case 0xa3:
				cycles = and_a_r(cpu, REGISTER_E);
				break;
			case 0xa4:
				cycles = and_a_r(cpu, REGISTER_H);
				break;
			case 0xa5:
				cycles = and_a_r(cpu, REGISTER_L);
				break;
			case 0xa6:
				cycles = and_a_hl(cpu);
				break;
			case 0xa7:
				cycles = and_a_r(cpu, REGISTER_A);
				break;
			case 0xb0:
				cycles = or_a_r(cpu, REGISTER_B);
				break;
			case 0xb1:
				cycles = or_a_r(cpu, REGISTER_C);
				break;
			case 0xb2:
				cycles = or_a_r(cpu, REGISTER_D);
				break;
			case 0xb3:
				cycles = or_a_r(cpu, REGISTER_E);
				break;
			case 0xb4:
				cycles = or_a_r(cpu, REGISTER_H);
				break;
			case 0xb5:
				cycles = or_a_r(cpu, REGISTER_L);
				break;
			case 0xb6:
				cycles = or_a_hl(cpu);
				break;
			case 0xb7:
				cycles = or_a_r(cpu, REGISTER_A);
				break;
			case 0xc1:
				cycles = pop_rr(cpu, REGISTER_PAIR_BC);
				break;
			case 0xc5:
				cycles = push_rr(cpu, REGISTER_PAIR_BC);
				break;
			case 0xc6:
				cycles = add_a_n(cpu);
				break;
			case 0xce:
				cycles = adc_a_n(cpu);
				break;
			case 0xd1:
				cycles = pop_rr(cpu, REGISTER_PAIR_DE);
				break;
			case 0xd5:
				cycles = push_rr(cpu, REGISTER_PAIR_DE);
				break;
			case 0xd6:
				cycles = sub_a_n(cpu);
				break;
			case 0xde:
				cycles = sbc_a_n(cpu);
				break;
			case 0xe0:
				cycles = ld_n_a(cpu);
				break;
			case 0xe1:
				cycles = pop_rr(cpu, REGISTER_PAIR_HL);
				break;
			case 0xe2:
				cycles = ld_c_a(cpu);
				break;
			case 0xe5:
				cycles = push_rr(cpu, REGISTER_PAIR_HL);
				break;
			case 0xe6:
				cycles = and_a_n(cpu);
				break;
			case 0xeA:
				cycles = ld_nn_a(cpu);
				break;
			case 0xf0:
				cycles = ld_a_n(cpu);
				break;
			case 0xf1:
				cycles = pop_rr(cpu, REGISTER_PAIR_AF);
				break;
			case 0xf2:
				cycles = ld_a_c(cpu);
				break;
			case 0xf5:
				cycles = push_rr(cpu, REGISTER_PAIR_AF);
				break;
			case 0xf6:
				cycles = or_a_n(cpu);
				break;
			case 0xf9:
				cycles = ld_sp_hl(cpu);
				break;
			case 0xfA:
				cycles = ld_a_nn(cpu);
				break;
			//TODO - implement all
		}

		cpu->instructionCycleCount = cycles;
		cpu->elapsedInstructionCycles++;
	}
	else {
		cpu->elapsedInstructionCycles++;
		if (cpu->elapsedInstructionCycles >= cpu->instructionCycleCount) {
			cpu->elapsedInstructionCycles = 0;
		}
	}
}