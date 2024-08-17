#include "jump_instructions.h"

bool condition_matches(Cpu* cpu, Condition cc) {
	return 
		(cc == CONDITION_NZ && get_flag(cpu, ZERO_FLAG_BIT) == 0x0) ||
		(cc == CONDITION_Z && get_flag(cpu, ZERO_FLAG_BIT) == 0x1) ||
		(cc == CONDITION_NC && get_flag(cpu, CARRY_FLAG_BIT) == 0x0) ||
		(cc == CONDITION_C && get_flag(cpu, CARRY_FLAG_BIT) == 0x1);
}

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
	cpu->pc += (int8_t)fetch8(cpu);

	return 12;
}

int jr_cc_e(Cpu* cpu, Condition cc) {
	if (condition_matches(cpu, cc)) {
		cpu->pc += (int8_t)fetch8(cpu);
		return 12;
	}

	return 8;
}

int jp_hl(Cpu* cpu) {
	cpu->pc = read_register_pair(cpu, REGISTER_PAIR_HL);

	return 4;
}