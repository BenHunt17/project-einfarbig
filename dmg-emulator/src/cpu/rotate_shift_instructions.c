#include "rotate_shift_instructions.h"

int rlca(Cpu* cpu) {
	uint8_t bit7 = (cpu->registers[REGISTER_A] >> 7) & 0x1;
	cpu->registers[REGISTER_A] = (cpu->registers[REGISTER_A] << 1) | bit7;

	set_flag(cpu, CARRY_FLAG_BIT, bit7);
	set_flag(cpu, HALF_CARRY_FLAG_BIT, 0x0);
	set_flag(cpu, SUBTRACTION_FLAG_BIT, 0x0);
	set_flag(cpu, ZERO_FLAG_BIT, 0x0);

	return 4;
}

int rla(Cpu* cpu) {
	uint8_t bit7 = (cpu->registers[REGISTER_A] >> 7) & 0x1;
	cpu->registers[REGISTER_A] = (cpu->registers[REGISTER_A] << 1) | get_flag(cpu, CARRY_FLAG_BIT);

	set_flag(cpu, CARRY_FLAG_BIT, bit7);
	set_flag(cpu, HALF_CARRY_FLAG_BIT, 0x0);
	set_flag(cpu, SUBTRACTION_FLAG_BIT, 0x0);
	set_flag(cpu, ZERO_FLAG_BIT, 0x0);

	return 4;
}

int rrca(Cpu* cpu) {
	uint8_t bit0 = cpu->registers[REGISTER_A] & 0x1;
	cpu->registers[REGISTER_A] = (bit0 << 7) | (cpu->registers[REGISTER_A] >> 1);

	set_flag(cpu, CARRY_FLAG_BIT, bit0);
	set_flag(cpu, HALF_CARRY_FLAG_BIT, 0x0);
	set_flag(cpu, SUBTRACTION_FLAG_BIT, 0x0);
	set_flag(cpu, ZERO_FLAG_BIT, 0x0);

	return 4;
}

int rra(Cpu* cpu) {
	uint8_t bit0 = cpu->registers[REGISTER_A] & 0x1;
	cpu->registers[REGISTER_A] = get_flag(cpu, CARRY_FLAG_BIT) | (cpu->registers[REGISTER_A] >> 1);

	set_flag(cpu, CARRY_FLAG_BIT, bit0);
	set_flag(cpu, HALF_CARRY_FLAG_BIT, 0x0);
	set_flag(cpu, SUBTRACTION_FLAG_BIT, 0x0);
	set_flag(cpu, ZERO_FLAG_BIT, 0x0);

	return 4;
}