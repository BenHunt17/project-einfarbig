#include "16_bit_arithmetic_logic_instructions.h"

int add_hl_rr(Cpu* cpu, uint8_t rp) {
	uint16_t hl = read_register_pair(cpu, REGISTER_PAIR_HL);
	uint16_t data = read_register_pair(cpu, rp);

	uint16_t result = hl + data;

	write_register_pair(cpu, REGISTER_PAIR_HL, result);

	auto x = hl + data;

	set_flag(cpu, HALF_CARRY_FLAG_BIT, ((hl & 0xfff) + (data & 0xfff)) > 0xfff);
	set_flag(cpu, SUBTRACTION_FLAG_BIT, 0x0);
	set_flag(cpu, CARRY_FLAG_BIT, hl + data > 0xffff);

	return 8;
}