#include "16_bit_load_instructions.h"

int ld_rr_nn(Cpu* cpu, uint8_t rp) {
	uint16_t data = fetch16(cpu);
	if (rp == REGISTER_PAIR_SP) {
		cpu->sp = data;
	}
	else {
		write_register_pair(cpu, rp, data);
	}
	return 12;
}

int ld_sp_hl(Cpu* cpu) {
	cpu->sp = read_register_pair(cpu, REGISTER_PAIR_HL);
	return 8;
}

int push_rr(Cpu* cpu, uint8_t rp) {
	uint16_t data = read_register_pair(cpu, rp);
	write_word(cpu->bus, cpu->sp - 2, data);
	cpu->sp -= 2;
	return 16;
}

int pop_rr(Cpu* cpu, uint8_t rp) {
	uint16_t data = read_word(cpu->bus, cpu->sp);
	write_register_pair(cpu, rp, data);
	cpu->sp += 2;
	return 12;
}

int ld_nn_sp(Cpu* cpu) {
	uint16_t data = cpu->sp;
	uint16_t address = fetch16(cpu);
	write_word(cpu->bus, address, data);
	return 20;
}

int ld_hl_sp_e(Cpu* cpu) {
	int8_t data = fetch8(cpu);
	write_register_pair(cpu, REGISTER_PAIR_HL, data + cpu->sp);

	set_flag(cpu, ZERO_FLAG_BIT, 0x0);
	set_flag(cpu, HALF_CARRY_FLAG_BIT, ((data & 0xfff) + (cpu->sp & 0xfff)) > 0xfff);
	set_flag(cpu, SUBTRACTION_FLAG_BIT, 0x0);
	set_flag(cpu, CARRY_FLAG_BIT, data + cpu->sp > 0xffff);

	return 12;
}