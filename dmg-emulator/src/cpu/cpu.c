#include <stdlib.h>

#include "cpu.h"
#include "decoder.h"

void initialise_cpu(Cpu* cpu) {
	cpu->pc = 0x100;
	cpu->sp = 0xfffe;

	cpu->next_ime = false;
	cpu->ime = false;

	cpu->is_halted = false;
	cpu->is_stopped = false;

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
	if (register_pair == REGISTER_PAIR_SP) {
		return cpu->sp;
	}
	return (cpu->registers[register_pair] << 8) | cpu->registers[register_pair + 1];
}

void write_register_pair(Cpu* cpu, RegisterPair register_pair, uint16_t data) {
	if (register_pair == REGISTER_PAIR_SP) {
		cpu->sp = data;
	}
	else {
		cpu->registers[register_pair] = (uint8_t)((data >> 8) & 0xff);
		cpu->registers[register_pair + 1] = (uint8_t)(data & 0xff);
	}
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

bool condition_matches(Cpu* cpu, Condition cc) {
	return
		(cc == CONDITION_NZ && get_flag(cpu, ZERO_FLAG_BIT) == 0x0) ||
		(cc == CONDITION_Z && get_flag(cpu, ZERO_FLAG_BIT) == 0x1) ||
		(cc == CONDITION_NC && get_flag(cpu, CARRY_FLAG_BIT) == 0x0) ||
		(cc == CONDITION_C && get_flag(cpu, CARRY_FLAG_BIT) == 0x1);
}

void cpu_cycle(Cpu* cpu) {
	if (cpu->elapsedInstructionCycles == 0) {
		uint8_t opcode = fetch8(cpu);

		int cycles = decode_execute(cpu);

		cpu->instructionCycleCount = cycles;
	}
	else {
		if (cpu->elapsedInstructionCycles >= cpu->instructionCycleCount) {
			cpu->elapsedInstructionCycles = 0;
		}
	}

	cpu->elapsedInstructionCycles++;
}