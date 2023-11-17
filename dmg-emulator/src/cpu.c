#include <stdlib.h>

#include "cpu.h"

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
	cpu->registers[register_pair] = (uint8_t)((data >> 8) | 0x00FF);
	cpu->registers[register_pair + 1] = (uint8_t)(data | 0x00FF);
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
			case 0x0A:
				cycles = ld_a_bc(cpu);
				break;
			case 0x0E:
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
			case 0x1A:
				cycles = ld_a_de(cpu);
				break;
			case 0x1E:
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
			case 0x2A:
				cycles = ldi_a_hl(cpu);
				break;
			case 0x2E:
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
			case 0x3A:
				cycles = ldd_a_hl(cpu);
				break;
			case 0x3E:
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
			case 0x4A:
				cycles = ld_r_r(cpu, REGISTER_C, REGISTER_D);
				break;
			case 0x4B:
				cycles = ld_r_r(cpu, REGISTER_C, REGISTER_E);
				break;
			case 0x4C:
				cycles = ld_r_r(cpu, REGISTER_C, REGISTER_H);
				break;
			case 0x4D:
				cycles = ld_r_r(cpu, REGISTER_C, REGISTER_L);
				break;
			case 0x4E:
				cycles = ld_r_hl(cpu, REGISTER_C);
				break;
			case 0x4F:
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
			case 0x5A:
				cycles = ld_r_r(cpu, REGISTER_E, REGISTER_D);
				break;
			case 0x5B:
				cycles = ld_r_r(cpu, REGISTER_E, REGISTER_E);
				break;
			case 0x5C:
				cycles = ld_r_r(cpu, REGISTER_E, REGISTER_H);
				break;
			case 0x5D:
				cycles = ld_r_r(cpu, REGISTER_E, REGISTER_L);
				break;
			case 0x5E:
				cycles = ld_r_hl(cpu, REGISTER_E);
				break;
			case 0x5F:
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
			case 0x6A:
				cycles = ld_r_r(cpu, REGISTER_L, REGISTER_D);
				break;
			case 0x6B:
				cycles = ld_r_r(cpu, REGISTER_L, REGISTER_E);
				break;
			case 0x6C:
				cycles = ld_r_r(cpu, REGISTER_L, REGISTER_H);
				break;
			case 0x6D:
				cycles = ld_r_r(cpu, REGISTER_L, REGISTER_L);
				break;
			case 0x6E:
				cycles = ld_r_hl(cpu, REGISTER_L);
				break;
			case 0x6F:
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
			case 0x7A:
				cycles = ld_r_r(cpu, REGISTER_A, REGISTER_D);
				break;
			case 0x7B:
				cycles = ld_r_r(cpu, REGISTER_A, REGISTER_E);
				break;
			case 0x7C:
				cycles = ld_r_r(cpu, REGISTER_A, REGISTER_H);
				break;
			case 0x7D:
				cycles = ld_r_r(cpu, REGISTER_A, REGISTER_L);
				break;
			case 0x7E:
				cycles = ld_r_hl(cpu, REGISTER_A);
				break;
			case 0x7F:
				cycles = ld_r_r(cpu, REGISTER_A, REGISTER_A);
				break;
			case 0xC5:
				cycles = push_rr(cpu, REGISTER_PAIR_BC);
				break;
			case 0xD5:
				cycles = push_rr(cpu, REGISTER_PAIR_DE);
				break;
			case 0xE0:
				cycles = ld_n_a(cpu);
				break;
			case 0xE2:
				cycles = ld_c_a(cpu);
				break;
			case 0xE5:
				cycles = push_rr(cpu, REGISTER_PAIR_HL);
				break;
			case 0xEA:
				cycles = ld_nn_a(cpu);
				break;
			case 0xF0:
				cycles = ld_a_n(cpu);
				break;
			case 0xF2:
				cycles = ld_a_c(cpu);
				break;
			case 0xF5:
				cycles = push_rr(cpu, REGISTER_PAIR_AF);
				break;
			case 0xF9:
				cycles = ld_sp_hl(cpu);
				break;
			case 0xFA:
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

int nop() {
	//Do nothing
	return 4;
}

int ld_r_r(Cpu* cpu, uint8_t r1, uint8_t r2) {
	cpu->registers[r1] = cpu->registers[r2];
	return 4;
}

int ld_r_n(Cpu* cpu, uint8_t r1) {
	cpu->registers[r1] = fetch8(cpu);
	return 8;
}

int ld_r_hl(Cpu* cpu, uint8_t r1) {
	uint16_t address = read_register_pair(cpu, REGISTER_PAIR_HL);
	cpu->registers[r1] = read_byte(cpu->bus, address);
	return 8;
}

int ld_hl_r(Cpu* cpu, uint8_t r1) {
	uint8_t data = cpu->registers[r1];
	uint16_t address = read_register_pair(cpu, REGISTER_PAIR_HL);
	write_byte(cpu->bus, address, data);
	return 8;
}

int ld_hl_n(Cpu* cpu) {
	uint8_t data = fetch8(cpu);
	uint16_t address = read_register_pair(cpu, REGISTER_PAIR_HL);
	write_byte(cpu->bus, address, data);
	return 12;
}

int ld_a_bc(Cpu* cpu) {
	uint16_t address = read_register_pair(cpu, REGISTER_PAIR_BC);
	cpu->registers[REGISTER_A] = read_byte(cpu->bus, address);
	return 8;
}

int ld_a_de(Cpu* cpu) {
	uint16_t address = read_register_pair(cpu, REGISTER_PAIR_DE);
	cpu->registers[REGISTER_A] = read_byte(cpu->bus, address);
	return 8;
}

int ld_a_c(Cpu* cpu) {
	uint16_t address = 0xFF00 & cpu->registers[REGISTER_C];
	cpu->registers[REGISTER_A] = read_byte(cpu->bus, address);
	return 8;
}

int ld_c_a(Cpu* cpu) {
	uint8_t data = cpu->registers[REGISTER_A];
	uint16_t address = 0xFF00 & cpu->registers[REGISTER_C];
	write_byte(cpu->bus, address, data);
	return 8;
}

int ld_a_n(Cpu* cpu) {
	uint16_t address = 0xFF00 & fetch8(cpu);
	cpu->registers[REGISTER_A] = read_byte(cpu->bus, address);
	return 12;
}

int ld_n_a(Cpu* cpu) {
	uint8_t data = cpu->registers[REGISTER_A];
	uint16_t address = 0xFF00 & fetch8(cpu);
	write_byte(cpu->bus, address, data);
	return 12;
}

int ld_a_nn(Cpu* cpu) {
	uint16_t address = fetch16(cpu);
	cpu->registers[REGISTER_A] = read_byte(cpu->bus, address);
	return 16;
}

int ld_nn_a(Cpu* cpu) {
	uint8_t data = cpu->registers[REGISTER_A];
	uint16_t address = fetch16(cpu);
	write_byte(cpu->bus, address, data);
	return 16;
}

int ldi_a_hl(Cpu* cpu) {
	uint16_t address = read_register_pair(cpu, REGISTER_PAIR_HL);
	cpu->registers[REGISTER_A] = read_byte(cpu->bus, address);
	write_register_pair(cpu, REGISTER_PAIR_HL, address + 1);
	return 8;
}

int ldd_a_hl(Cpu* cpu) {
	uint16_t address = read_register_pair(cpu, REGISTER_PAIR_HL);
	cpu->registers[REGISTER_A] = read_byte(cpu->bus, address);
	write_register_pair(cpu, REGISTER_PAIR_HL, address - 1);
	return 8;
}

int ld_bc_a(Cpu* cpu) {
	uint8_t data = cpu->registers[REGISTER_A];
	uint16_t address = read_register_pair(cpu, REGISTER_PAIR_BC);
	write_byte(cpu->bus, address, data);
	return 8;
}

int ld_de_a(Cpu* cpu) {
	uint8_t data = cpu->registers[REGISTER_A];
	uint16_t address = read_register_pair(cpu, REGISTER_PAIR_DE);
	write_byte(cpu->bus, address, data);
	return 8;
}

int ldi_hl_a(Cpu* cpu) {
	uint8_t data = cpu->registers[REGISTER_A];
	uint16_t address = read_register_pair(cpu, REGISTER_PAIR_HL);
	write_byte(cpu->bus, address, data);
	write_register_pair(cpu, REGISTER_PAIR_HL, address + 1);
	return 8;
}

int ldd_hl_a(Cpu* cpu) {
	uint8_t data = cpu->registers[REGISTER_A];
	uint16_t address = read_register_pair(cpu, REGISTER_PAIR_HL);
	write_byte(cpu->bus, address, data);
	write_register_pair(cpu, REGISTER_PAIR_HL, address - 1);
	return 8;
}

int ld_rr_nn(Cpu* cpu, uint8_t rp) {
	uint16_t data = fetch16(cpu);
	if (rp != NULL) {
		write_register_pair(cpu, rp, data);
	}
	else {
		//Assume null register pair value means SP
		cpu->sp = data;
	}
	return 12;
}

int ld_sp_hl(Cpu* cpu) {
	cpu->sp = read_register_pair(cpu, REGISTER_PAIR_HL);
	return 8;
}

int push_rr(Cpu* cpu, uint8_t rp) {
	uint16_t data = read_register_pair(cpu, rp);
	write_word(cpu->bus, cpu->sp - 2, data);
	cpu->sp -= 2;
	return 16;
}