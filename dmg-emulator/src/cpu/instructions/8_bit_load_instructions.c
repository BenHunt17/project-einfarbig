#include "8_bit_load_instructions.h"

int ld_r_r(Cpu* cpu, uint8_t r1, uint8_t r2) {
	cpu->registers[r1] = cpu->registers[r2];
	return 4;
}

int ld_r_n(Cpu* cpu, uint8_t r1) {
	cpu->registers[r1] = fetch8(cpu);
	return 8;
}

int ld_r_hl(Cpu* cpu, uint8_t r1) {
	uint16_t address = read_register_pair(cpu, REGISTER_PAIR_HL);
	cpu->registers[r1] = read_byte(cpu->bus, address);
	return 8;
}

int ld_hl_r(Cpu* cpu, uint8_t r1) {
	uint8_t data = cpu->registers[r1];
	uint16_t address = read_register_pair(cpu, REGISTER_PAIR_HL);
	write_byte(cpu->bus, address, data);
	return 8;
}

int ld_hl_n(Cpu* cpu) {
	uint8_t data = fetch8(cpu);
	uint16_t address = read_register_pair(cpu, REGISTER_PAIR_HL);
	write_byte(cpu->bus, address, data);
	return 12;
}

int ld_a_bc(Cpu* cpu) {
	uint16_t address = read_register_pair(cpu, REGISTER_PAIR_BC);
	cpu->registers[REGISTER_A] = read_byte(cpu->bus, address);
	return 8;
}

int ld_a_de(Cpu* cpu) {
	uint16_t address = read_register_pair(cpu, REGISTER_PAIR_DE);
	cpu->registers[REGISTER_A] = read_byte(cpu->bus, address);
	return 8;
}

int ld_a_c(Cpu* cpu) {
	uint16_t address = 0xff00 | cpu->registers[REGISTER_C];
	cpu->registers[REGISTER_A] = read_byte(cpu->bus, address);
	return 8;
}

int ld_c_a(Cpu* cpu) {
	uint8_t data = cpu->registers[REGISTER_A];
	uint16_t address = 0xff00 | cpu->registers[REGISTER_C];
	write_byte(cpu->bus, address, data);
	return 8;
}

int ld_a_n(Cpu* cpu) {
	uint16_t address = 0xff00 | fetch8(cpu);
	cpu->registers[REGISTER_A] = read_byte(cpu->bus, address);
	return 12;
}

int ld_n_a(Cpu* cpu) {
	uint8_t data = cpu->registers[REGISTER_A];
	uint16_t address = 0xff00 | fetch8(cpu);
	write_byte(cpu->bus, address, data);
	return 12;
}

int ld_a_nn(Cpu* cpu) {
	uint16_t address = fetch16(cpu);
	cpu->registers[REGISTER_A] = read_byte(cpu->bus, address);
	return 16;
}

int ld_nn_a(Cpu* cpu) {
	uint8_t data = cpu->registers[REGISTER_A];
	uint16_t address = fetch16(cpu);
	write_byte(cpu->bus, address, data);
	return 16;
}

int ldi_a_hl(Cpu* cpu) {
	uint16_t address = read_register_pair(cpu, REGISTER_PAIR_HL);
	cpu->registers[REGISTER_A] = read_byte(cpu->bus, address);
	write_register_pair(cpu, REGISTER_PAIR_HL, address + 1);
	return 8;
}

int ldd_a_hl(Cpu* cpu) {
	uint16_t address = read_register_pair(cpu, REGISTER_PAIR_HL);
	cpu->registers[REGISTER_A] = read_byte(cpu->bus, address);
	write_register_pair(cpu, REGISTER_PAIR_HL, address - 1);
	return 8;
}

int ld_bc_a(Cpu* cpu) {
	uint8_t data = cpu->registers[REGISTER_A];
	uint16_t address = read_register_pair(cpu, REGISTER_PAIR_BC);
	write_byte(cpu->bus, address, data);
	return 8;
}

int ld_de_a(Cpu* cpu) {
	uint8_t data = cpu->registers[REGISTER_A];
	uint16_t address = read_register_pair(cpu, REGISTER_PAIR_DE);
	write_byte(cpu->bus, address, data);
	return 8;
}

int ldi_hl_a(Cpu* cpu) {
	uint8_t data = cpu->registers[REGISTER_A];
	uint16_t address = read_register_pair(cpu, REGISTER_PAIR_HL);
	write_byte(cpu->bus, address, data);
	write_register_pair(cpu, REGISTER_PAIR_HL, address + 1);
	return 8;
}

int ldd_hl_a(Cpu* cpu) {
	uint8_t data = cpu->registers[REGISTER_A];
	uint16_t address = read_register_pair(cpu, REGISTER_PAIR_HL);
	write_byte(cpu->bus, address, data);
	write_register_pair(cpu, REGISTER_PAIR_HL, address - 1);
	return 8;
}