#include "rotate_shift_instructions.h"

void update_shift_rotate_a_flags(Cpu* cpu, uint8_t carry_flag) {
	set_flag(cpu, CARRY_FLAG_BIT, carry_flag);
	set_flag(cpu, HALF_CARRY_FLAG_BIT, 0x0);
	set_flag(cpu, SUBTRACTION_FLAG_BIT, 0x0);
	set_flag(cpu, ZERO_FLAG_BIT, 0x0);
}

void update_shift_rotate_flags(Cpu* cpu, uint8_t carry_flag, uint8_t result) {
	set_flag(cpu, CARRY_FLAG_BIT, carry_flag);
	set_flag(cpu, HALF_CARRY_FLAG_BIT, 0x0);
	set_flag(cpu, SUBTRACTION_FLAG_BIT, 0x0);
	set_flag(cpu, ZERO_FLAG_BIT, result == 0x0);
}

int rlca(Cpu* cpu) {
	uint8_t bit7 = (cpu->registers[REGISTER_A] >> 7) & 0x1;
	cpu->registers[REGISTER_A] = (cpu->registers[REGISTER_A] << 1) | bit7;

	update_shift_rotate_a_flags(cpu, bit7);

	return 4;
}

int rla(Cpu* cpu) {
	uint8_t bit7 = (cpu->registers[REGISTER_A] >> 7) & 0x1;
	cpu->registers[REGISTER_A] = (cpu->registers[REGISTER_A] << 1) | get_flag(cpu, CARRY_FLAG_BIT);

	update_shift_rotate_a_flags(cpu, bit7);

	return 4;
}

int rrca(Cpu* cpu) {
	uint8_t bit0 = cpu->registers[REGISTER_A] & 0x1;
	cpu->registers[REGISTER_A] = (bit0 << 7) | (cpu->registers[REGISTER_A] >> 1);

	update_shift_rotate_a_flags(cpu, bit0);

	return 4;
}

int rra(Cpu* cpu) {
	uint8_t bit0 = cpu->registers[REGISTER_A] & 0x1;
	cpu->registers[REGISTER_A] = get_flag(cpu, CARRY_FLAG_BIT) | (cpu->registers[REGISTER_A] >> 1);

	update_shift_rotate_a_flags(cpu, bit0);

	return 4;
}

int rlc_r(Cpu* cpu, uint8_t r1) {
	uint8_t bit7 = (cpu->registers[r1] >> 7) & 0x1;
	cpu->registers[r1] = (cpu->registers[r1] << 1) | bit7;

	update_shift_rotate_flags(cpu, bit7, cpu->registers[r1]);

	return 8;
}

int rlc_hl(Cpu* cpu) {
	uint16_t address = read_register_pair(cpu, REGISTER_PAIR_HL);
	uint8_t bit7 = (read_byte(cpu->bus, address) >> 7) & 0x1;
	write_byte(cpu->bus, address, (read_byte(cpu->bus, address) << 1) | bit7);
	
	update_shift_rotate_flags(cpu, bit7, read_byte(cpu->bus, address));

	return 16;
}

int rl_r(Cpu* cpu, uint8_t r1) {
	uint8_t bit7 = (cpu->registers[r1] >> 7) & 0x1;
	cpu->registers[r1] = (cpu->registers[r1] << 1) | get_flag(cpu, CARRY_FLAG_BIT);

	update_shift_rotate_flags(cpu, bit7, cpu->registers[r1]);

	return 8;
}

int rl_hl(Cpu* cpu) {
	uint16_t address = read_register_pair(cpu, REGISTER_PAIR_HL);
	uint8_t bit7 = (read_byte(cpu->bus, address) >> 7) & 0x1;
	write_byte(cpu->bus, address, (read_byte(cpu->bus, address) << 1) | get_flag(cpu, CARRY_FLAG_BIT));

	update_shift_rotate_flags(cpu, bit7, read_byte(cpu->bus, address));

	return 16;
}

int rrc_r(Cpu* cpu, uint8_t r1) {
	uint8_t bit0 = cpu->registers[r1] & 0x1;
	cpu->registers[r1] = (bit0 << 7) | (cpu->registers[r1] >> 1);

	update_shift_rotate_flags(cpu, bit0, cpu->registers[r1]);

	return 8;
}

int rrc_hl(Cpu* cpu) {
	uint16_t address = read_register_pair(cpu, REGISTER_PAIR_HL);
	uint8_t bit0 = read_byte(cpu->bus, address) & 0x1;
	write_byte(cpu->bus, address, (bit0 << 7) | read_byte(cpu->bus, address) >> 1);

	update_shift_rotate_flags(cpu, bit0, read_byte(cpu->bus, address));

	return 16;
}

int rr_r(Cpu* cpu, uint8_t r1) {
	uint8_t bit0 = cpu->registers[r1] & 0x1;
	cpu->registers[r1] = (get_flag(cpu, CARRY_FLAG_BIT) << 7) | (cpu->registers[r1] >> 1);

	update_shift_rotate_flags(cpu, bit0, cpu->registers[r1]);

	return 8;
}

int rr_hl(Cpu* cpu) {
	uint16_t address = read_register_pair(cpu, REGISTER_PAIR_HL);
	uint8_t bit0 = read_byte(cpu->bus, address) & 0x1;
	write_byte(cpu->bus, address, (get_flag(cpu, CARRY_FLAG_BIT) << 7) | read_byte(cpu->bus, address) >> 1);

	update_shift_rotate_flags(cpu, bit0, read_byte(cpu->bus, address));

	return 16;
}

int sla_r(Cpu* cpu, uint8_t r1) {
	uint8_t bit7 = (cpu->registers[r1] >> 7) & 0x1;
	cpu->registers[r1] <<= 1;

	update_shift_rotate_flags(cpu, bit7, cpu->registers[r1]);

	return 8;
}

int sla_hl(Cpu* cpu) {
	uint16_t address = read_register_pair(cpu, REGISTER_PAIR_HL);
	uint8_t bit7 = (read_byte(cpu->bus, address) >> 7) & 0x1;
	write_byte(cpu->bus, address, read_byte(cpu->bus, address) << 1);

	update_shift_rotate_flags(cpu, bit7, read_byte(cpu->bus, address));

	return 16;
}

int sra_r(Cpu* cpu, uint8_t r1) {
	uint8_t bit0 = cpu->registers[r1] & 0x1;
	cpu->registers[r1] = (cpu->registers[r1] & 0x80) | (cpu->registers[r1] >> 1);

	update_shift_rotate_flags(cpu, bit0, cpu->registers[r1]);

	return 8;
}

int sra_hl(Cpu* cpu) {
	uint16_t address = read_register_pair(cpu, REGISTER_PAIR_HL);
	uint8_t bit0 = read_byte(cpu->bus, address) & 0x1;
	write_byte(cpu->bus, address, (read_byte(cpu->bus, address) & 0x80) | (read_byte(cpu->bus, address) >> 1));

	update_shift_rotate_flags(cpu, bit0, read_byte(cpu->bus, address));

	return 16;
}

int srl_r(Cpu* cpu, uint8_t r1) {
	uint8_t bit0 = cpu->registers[r1] & 0x1;
	cpu->registers[r1] >>= 1;

	update_shift_rotate_flags(cpu, bit0, cpu->registers[r1]);

	return 8;
}

int srl_hl(Cpu* cpu) {
	uint16_t address = read_register_pair(cpu, REGISTER_PAIR_HL);
	uint8_t bit0 = read_byte(cpu->bus, address) & 0x1;
	write_byte(cpu->bus, address, read_byte(cpu->bus, address) >> 1);

	update_shift_rotate_flags(cpu, bit0, read_byte(cpu->bus, address));

	return 16;
}

int swap_r(Cpu* cpu, uint8_t r1) {
	cpu->registers[r1] = (cpu->registers[r1] << 4) | (cpu->registers[r1] >> 4);

	update_shift_rotate_flags(cpu, 0x0, cpu->registers[r1]);

	return 8;
}

int swap_hl(Cpu* cpu) {
	uint16_t address = read_register_pair(cpu, REGISTER_PAIR_HL);
	uint8_t data = read_byte(cpu->bus, address);
	write_byte(cpu->bus, address, (data << 4) | (data >> 4));

	update_shift_rotate_flags(cpu, 0x0, read_byte(cpu->bus, address));

	return 16;
}