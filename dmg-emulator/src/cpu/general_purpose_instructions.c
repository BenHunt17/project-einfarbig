#include "general_purpose_instructions.h"

int daa(Cpu* cpu) {
	uint8_t a = cpu->registers[REGISTER_A];
	bool n = get_flag(cpu, SUBTRACTION_FLAG_BIT);
	bool c = get_flag(cpu, CARRY_FLAG_BIT);
	bool h = get_flag(cpu, HALF_CARRY_FLAG_BIT);

	if (!n) {
		if (c || a > 0x99) {
			cpu->registers[REGISTER_A] += 0x60;
			set_flag(cpu, CARRY_FLAG_BIT, true);
		}
		if (h || (a & 0x0f) > 0x9) {
			cpu->registers[REGISTER_A] += 0x06;
		}
	}
	else {
		//The gameboy leaves A as is if an "illegal" bcd subtraction takes place. i.e a digit is greater than 9 despite no carry taking place. Therefore can get away with just checking the flags
		if (c) {
			cpu->registers[REGISTER_A] -= 0x60;
		}
		if (h) {
			cpu->registers[REGISTER_A] -= 0x06;
		}
	}

	set_flag(cpu, ZERO_FLAG_BIT, cpu->registers[REGISTER_A] == 0x0);
	set_flag(cpu, HALF_CARRY_FLAG_BIT, false);

	return 4;
}