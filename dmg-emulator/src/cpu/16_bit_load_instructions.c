#include "16_bit_load_instructions.h"

int ld_rr_nn(Cpu* cpu, uint8_t rp) {
	uint16_t data = fetch16(cpu);
	if (rp != NULL) {
		write_register_pair(cpu, rp, data);
	}
	else {
		//Assume null register pair value means SP
		cpu->sp = data;
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