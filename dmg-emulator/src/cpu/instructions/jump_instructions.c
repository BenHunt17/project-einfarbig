#include "jump_instructions.h"

int jp_nn(Cpu* cpu) {
	cpu->pc = fetch16(cpu);

	return 16;
}

int jp_cc_nn(Cpu* cpu, Condition cc) {
	if (condition_matches(cpu, cc)) {
		cpu->pc = fetch16(cpu);
		return 16;
	}

	return 12;
}

int jr_e(Cpu* cpu) {
	cpu->pc += (int8_t)fetch8(cpu) - 2;

	return 12;
}

int jr_cc_e(Cpu* cpu, Condition cc) {
	if (condition_matches(cpu, cc)) {
		cpu->pc += (int8_t)fetch8(cpu) - 2;
		return 12;
	}

	return 8;
}

int jp_hl(Cpu* cpu) {
	cpu->pc = read_register_pair(cpu, REGISTER_PAIR_HL);

	return 4;
}