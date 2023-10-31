#include <stdlib.h>

#include "cpu.h"

void initialise_cpu_state(CpuState* cpu_state) {
	cpu_state->pc = 0x100;
	cpu_state->sp = 0xfffe;
	cpu_state->elapsedInstructionCycles = 0;
	cpu_state->instructionCycleCount = 0;
}

void free_cpu_state(CpuState* cpu_state) {
	free(cpu_state);
}

uint8_t fetch8(Bus* bus) {
	uint8_t byte = read_byte(bus, bus->cpu->pc);
	bus->cpu->pc++;

	return byte;
}

uint16_t fetch16(Bus* bus) {
	uint8_t low_byte = fetch8(bus);
	uint8_t high_byte = fetch8(bus);

	return (high_byte << 8) | low_byte;
}

bool get_flag(CpuState* state, uint8_t flag_bit) {
	return (state->registers[1] >> flag_bit) & 0x1;
}

void set_flag(CpuState* state, uint8_t flag_bit, bool is_set) {
	if (is_set) {
		state->registers[1] |= (0x1 << flag_bit);
	}
	else {
		state->registers[1] &= ~(0x1 << flag_bit);
	}
}

void cpu_cycle(Bus* bus) {
	CpuState* cpu_state = bus->cpu;

	if (cpu_state->elapsedInstructionCycles == 0) {
		uint8_t opcode = fetch8(bus);

		int cycles;
		switch (opcode) {
			//TODO - there are apprently more clever ways of decoding the opcode. maybe look into once I'm more confident around this instruction set [https://www.reddit.com/r/EmuDev/comments/scps99/gameboy_is_it_necessary_to_implement_the/]
			case 0x00:
				cycles = nop();
				break;
			case 0x06:
				cycles = ld_r_n(bus, REGISTER_B);
				break;
			case 0x0E:
				cycles = ld_r_n(bus, REGISTER_C);
				break;
			case 0x16:
				cycles = ld_r_n(bus, REGISTER_D);
				break;
			case 0x1E:
				cycles = ld_r_n(bus, REGISTER_E);
				break;
			case 0x26:
				cycles = ld_r_n(bus, REGISTER_H);
				break;
			case 0x2E:
				cycles = ld_r_n(bus, REGISTER_L);
				break;
			case 0x3E:
				cycles = ld_r_n(bus, REGISTER_A);
				break;
			case 0x40:
				cycles = ld_r_r(bus, REGISTER_B, REGISTER_B);
				break;
			case 0x41:
				cycles = ld_r_r(bus, REGISTER_B, REGISTER_C);
				break;
			case 0x42:
				cycles = ld_r_r(bus, REGISTER_B, REGISTER_D);
				break;
			case 0x43:
				cycles = ld_r_r(bus, REGISTER_B, REGISTER_E);
				break;
			case 0x44:
				cycles = ld_r_r(bus, REGISTER_B, REGISTER_H);
				break;
			case 0x45:
				cycles = ld_r_r(bus, REGISTER_B, REGISTER_L);
				break;
			case 0x47:
				cycles = ld_r_r(bus, REGISTER_B, REGISTER_A);
				break;
			case 0x48:
				cycles = ld_r_r(bus, REGISTER_C, REGISTER_B);
				break;
			case 0x49:
				cycles = ld_r_r(bus, REGISTER_C, REGISTER_C);
				break;
			case 0x4A:
				cycles = ld_r_r(bus, REGISTER_C, REGISTER_D);
				break;
			case 0x4B:
				cycles = ld_r_r(bus, REGISTER_C, REGISTER_E);
				break;
			case 0x4C:
				cycles = ld_r_r(bus, REGISTER_C, REGISTER_H);
				break;
			case 0x4D:
				cycles = ld_r_r(bus, REGISTER_C, REGISTER_L);
				break;
			case 0x4F:
				cycles = ld_r_r(bus, REGISTER_C, REGISTER_A);
				break;
			case 0x50:
				cycles = ld_r_r(bus, REGISTER_D, REGISTER_B);
				break;
			case 0x51:
				cycles = ld_r_r(bus, REGISTER_D, REGISTER_C);
				break;
			case 0x52:
				cycles = ld_r_r(bus, REGISTER_D, REGISTER_D);
				break;
			case 0x53:
				cycles = ld_r_r(bus, REGISTER_D, REGISTER_E);
				break;
			case 0x54:
				cycles = ld_r_r(bus, REGISTER_D, REGISTER_H);
				break;
			case 0x55:
				cycles = ld_r_r(bus, REGISTER_D, REGISTER_L);
				break;
			case 0x57:
				cycles = ld_r_r(bus, REGISTER_D, REGISTER_A);
				break;
			case 0x58:
				cycles = ld_r_r(bus, REGISTER_E, REGISTER_B);
				break;
			case 0x59:
				cycles = ld_r_r(bus, REGISTER_E, REGISTER_C);
				break;
			case 0x5A:
				cycles = ld_r_r(bus, REGISTER_E, REGISTER_D);
				break;
			case 0x5B:
				cycles = ld_r_r(bus, REGISTER_E, REGISTER_E);
				break;
			case 0x5C:
				cycles = ld_r_r(bus, REGISTER_E, REGISTER_H);
				break;
			case 0x5D:
				cycles = ld_r_r(bus, REGISTER_E, REGISTER_L);
				break;
			case 0x5F:
				cycles = ld_r_r(bus, REGISTER_E, REGISTER_A);
				break;
			case 0x60:
				cycles = ld_r_r(bus, REGISTER_H, REGISTER_B);
				break;
			case 0x61:
				cycles = ld_r_r(bus, REGISTER_H, REGISTER_C);
				break;
			case 0x62:
				cycles = ld_r_r(bus, REGISTER_H, REGISTER_D);
				break;
			case 0x63:
				cycles = ld_r_r(bus, REGISTER_H, REGISTER_E);
				break;
			case 0x64:
				cycles = ld_r_r(bus, REGISTER_H, REGISTER_H);
				break;
			case 0x65:
				cycles = ld_r_r(bus, REGISTER_H, REGISTER_L);
				break;
			case 0x67:
				cycles = ld_r_r(bus, REGISTER_H, REGISTER_A);
				break;
			case 0x68:
				cycles = ld_r_r(bus, REGISTER_L, REGISTER_B);
				break;
			case 0x69:
				cycles = ld_r_r(bus, REGISTER_L, REGISTER_C);
				break;
			case 0x6A:
				cycles = ld_r_r(bus, REGISTER_L, REGISTER_D);
				break;
			case 0x6B:
				cycles = ld_r_r(bus, REGISTER_L, REGISTER_E);
				break;
			case 0x6C:
				cycles = ld_r_r(bus, REGISTER_L, REGISTER_H);
				break;
			case 0x6D:
				cycles = ld_r_r(bus, REGISTER_L, REGISTER_L);
				break;
			case 0x6F:
				cycles = ld_r_r(bus, REGISTER_L, REGISTER_A);
				break;
			case 0x78:
				cycles = ld_r_r(bus, REGISTER_A, REGISTER_B);
				break;
			case 0x79:
				cycles = ld_r_r(bus, REGISTER_A, REGISTER_C);
				break;
			case 0x7A:
				cycles = ld_r_r(bus, REGISTER_A, REGISTER_D);
				break;
			case 0x7B:
				cycles = ld_r_r(bus, REGISTER_A, REGISTER_E);
				break;
			case 0x7C:
				cycles = ld_r_r(bus, REGISTER_A, REGISTER_H);
				break;
			case 0x7D:
				cycles = ld_r_r(bus, REGISTER_A, REGISTER_L);
				break;
			case 0x7F:
				cycles = ld_r_r(bus, REGISTER_A, REGISTER_A);
				break;
			//TODO - implement all
		}

		cpu_state->instructionCycleCount = cycles;
		cpu_state->elapsedInstructionCycles++;
	}
	else {
		cpu_state->elapsedInstructionCycles++;
		if (cpu_state->elapsedInstructionCycles >= cpu_state->instructionCycleCount) {
			cpu_state->elapsedInstructionCycles = 0;
		}
	}
}

int nop() {
	//Do nothing
	return 4;
}

int ld_r_r(Bus* bus, uint8_t r1, uint8_t r2) {
	bus->cpu->registers[r1] = bus->cpu->registers[r2];
	return 4;
}

int ld_r_n(Bus* bus, uint8_t r1) {
	bus->cpu->registers[r1] = fetch8(bus);
	return 8;
}