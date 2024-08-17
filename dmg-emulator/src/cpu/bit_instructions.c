#include "bit_instructions.h"

int bit_b_r(Cpu* cpu, uint8_t bit, uint8_t r1) {
	set_flag(cpu, ZERO_FLAG_BIT, (~cpu->registers[r1] >> bit) & 0x1);
	set_flag(cpu, HALF_CARRY_FLAG_BIT, 0x1);
	set_flag(cpu, SUBTRACTION_FLAG_BIT, 0x0);

	return 8;
}

int bit_b_hl(Cpu* cpu, uint8_t bit) {
	uint16_t address = read_register_pair(cpu, REGISTER_PAIR_HL);
	uint8_t data = read_byte(cpu->bus, address);

	set_flag(cpu, ZERO_FLAG_BIT, (~data >> bit) & 0x1);
	set_flag(cpu, HALF_CARRY_FLAG_BIT, 0x1);
	set_flag(cpu, SUBTRACTION_FLAG_BIT, 0x0);
}

int set_b_r(Cpu* cpu, uint8_t bit, uint8_t r1) {
	cpu->registers[r1] |= (0x1 << bit);

	return 8;
}

int set_b_hl(Cpu* cpu, uint8_t bit) {
	uint16_t address = read_register_pair(cpu, REGISTER_PAIR_HL);
	uint8_t data = read_byte(cpu->bus, address);

	write_byte(cpu->bus, address, data | (0x1 << bit));

	return 16;
}

int res_b_r(Cpu* cpu, uint8_t bit, uint8_t r1) {
	cpu->registers[r1] &= ~(0x1 << bit);

	return 8;
}

int res_b_hl(Cpu* cpu, uint8_t bit) {
	uint16_t address = read_register_pair(cpu, REGISTER_PAIR_HL);
	uint8_t data = read_byte(cpu->bus, address);

	write_byte(cpu->bus, address, data & ~(0x1 << bit));

	return 16;
}