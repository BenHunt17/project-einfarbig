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