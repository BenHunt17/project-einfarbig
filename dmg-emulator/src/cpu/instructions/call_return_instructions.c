#include "call_return_instructions.h"

int call_nn(Cpu* cpu) {
	uint16_t subroutine_address = fetch16(cpu);

	write_word(cpu->bus, cpu->sp - 2, cpu->pc);
	cpu->sp -= 2;

	cpu->pc = subroutine_address;

	return 24;
}

int call_cc_nn(Cpu* cpu, Condition cc) {
	if (condition_matches(cpu, cc)) {
		uint16_t subroutine_address = fetch16(cpu);

		write_word(cpu->bus, cpu->sp - 2, cpu->pc);
		cpu->sp -= 2;

		cpu->pc = subroutine_address;

		return 24;
	}

	cpu->pc += 2;

	return 12;
}

int ret(Cpu* cpu) {
	cpu->pc = read_word(cpu->bus, cpu->sp);
	cpu->sp += 2;

	return 16;
}

int reti(Cpu* cpu) {
	cpu->ime = true;

	cpu->pc = read_word(cpu->bus, cpu->sp);
	cpu->sp += 2;

	return 16;
}

int ret_cc(Cpu* cpu, Condition cc) {
	if (condition_matches(cpu, cc)) {
		cpu->pc = read_word(cpu->bus, cpu->sp);
		cpu->sp += 2;

		return 20;
	}

	return 8;
}

int rst_t(Cpu* cpu, uint8_t t) {
	write_word(cpu->bus, cpu->sp - 2, cpu->pc);
	cpu->sp -= 2;

	cpu->pc = 0x0000 | (t * 0x8);

	return 16;
}