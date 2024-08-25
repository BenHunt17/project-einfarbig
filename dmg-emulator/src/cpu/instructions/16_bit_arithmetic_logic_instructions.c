#include "16_bit_arithmetic_logic_instructions.h"

int add_hl_rr(Cpu* cpu, RegisterPair rp) {
	uint16_t hl = read_register_pair(cpu, REGISTER_PAIR_HL);
	uint16_t data = read_register_pair(cpu, rp);

	uint16_t result = hl + data;

	write_register_pair(cpu, REGISTER_PAIR_HL, result);

	set_flag(cpu, HALF_CARRY_FLAG_BIT, ((hl & 0xfff) + (data & 0xfff)) > 0xfff);
	set_flag(cpu, SUBTRACTION_FLAG_BIT, 0x0);
	set_flag(cpu, CARRY_FLAG_BIT, hl + data > 0xffff);

	return 8;
}

int add_sp_e(Cpu* cpu) {
	int8_t data = fetch8(cpu);
	int16_t sp = read_register_pair(cpu, REGISTER_PAIR_SP);

	write_register_pair(cpu, REGISTER_PAIR_SP, sp + data);

	set_flag(cpu, HALF_CARRY_FLAG_BIT, ((data & 0xfff) + (sp & 0xfff)) > 0xfff);
	set_flag(cpu, SUBTRACTION_FLAG_BIT, 0x0);
	set_flag(cpu, CARRY_FLAG_BIT, sp + data > 0xffff);
	set_flag(cpu, ZERO_FLAG_BIT, 0x0);

	return 16;
}

int inc_rr(Cpu* cpu, RegisterPair rp) {
	uint16_t data = read_register_pair(cpu, rp);
	write_register_pair(cpu, rp, data + 1);

	return 8;
}

int dec_rr(Cpu* cpu, RegisterPair rp) {
	uint16_t data = read_register_pair(cpu, rp);
	write_register_pair(cpu, rp, data - 1);

	return 8;
}