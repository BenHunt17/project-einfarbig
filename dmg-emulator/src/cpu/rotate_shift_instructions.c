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

int rlc_r(Cpu* cpu, uint8_t r1) {
	uint8_t bit7 = (cpu->registers[r1] >> 7) & 0x1;
	cpu->registers[r1] = (cpu->registers[r1] << 1) | bit7;

	set_flag(cpu, CARRY_FLAG_BIT, bit7);
	set_flag(cpu, HALF_CARRY_FLAG_BIT, 0x0);
	set_flag(cpu, SUBTRACTION_FLAG_BIT, 0x0);
	set_flag(cpu, ZERO_FLAG_BIT, cpu->registers[r1] == 0x0);

	return 8;
}

int rlc_hl(Cpu* cpu) {
	uint16_t address = read_register_pair(cpu, REGISTER_PAIR_HL);
	uint8_t bit7 = (read_byte(cpu->bus, address) >> 7) & 0x1;
	write_byte(cpu->bus, address, (read_byte(cpu->bus, address) << 1) | bit7);
	
	set_flag(cpu, CARRY_FLAG_BIT, bit7);
	set_flag(cpu, HALF_CARRY_FLAG_BIT, 0x0);
	set_flag(cpu, SUBTRACTION_FLAG_BIT, 0x0);
	set_flag(cpu, ZERO_FLAG_BIT, read_byte(cpu->bus, address) == 0x0);

	return 16;
}