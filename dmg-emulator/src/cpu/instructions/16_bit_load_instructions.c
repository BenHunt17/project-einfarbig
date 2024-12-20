#include "16_bit_load_instructions.h"

int ld_rr_nn(Cpu* cpu, RegisterPair rp) {
	uint16_t data = fetch16(cpu);
	write_register_pair(cpu, rp, data);
	
	return 12;
}

int ld_sp_hl(Cpu* cpu) {
	cpu->sp = read_register_pair(cpu, REGISTER_PAIR_HL);
	return 8;
}

int push_rr(Cpu* cpu, RegisterPair rp) {
	uint16_t data = read_register_pair(cpu, rp);

	if (rp == REGISTER_PAIR_AF) {
		//Turns out the lower four bits of the F register should always be cleared. This wasn't obvious when I started this and I 
		//don't want to re-engineer my registers code, therefore I just intercept writes to F in the push instruction since in theory
		//only this instruction directly modifies the F register. Also this fixes the error found by blargg's test
		data = data & 0xfff0;
	}

	write_word(cpu->bus, cpu->sp - 2, data);
	cpu->sp -= 2;
	return 16;
}

int pop_rr(Cpu* cpu, RegisterPair rp) {
	uint16_t data = read_word(cpu->bus, cpu->sp);

	write_register_pair(cpu, rp, data);
	cpu->sp += 2;
	return 12;
}

int ld_hl_sp_e(Cpu* cpu) {
	int8_t data = fetch8(cpu);
	write_register_pair(cpu, REGISTER_PAIR_HL, data + cpu->sp);

	set_flag(cpu, ZERO_FLAG_BIT, 0x0);
	set_flag(cpu, HALF_CARRY_FLAG_BIT, ((data & 0xf) + (cpu->sp & 0xf)) > 0xf);
	set_flag(cpu, SUBTRACTION_FLAG_BIT, 0x0);
	set_flag(cpu, CARRY_FLAG_BIT, (data & 0xff) + (cpu->sp & 0xff) > 0xff);

	return 12;
}

int ld_nn_sp(Cpu* cpu) {
	uint16_t data = cpu->sp;
	uint16_t address = fetch16(cpu);
	write_word(cpu->bus, address, data);
	return 20;
}