#include "8_bit_arithmetic_logic_instructions.h"

void add_update_flags(Cpu* cpu, uint8_t n1, uint8_t n2, uint8_t n3, uint8_t true_result) {
	//Helper function since the flag setting logic is same for addition instructions
	set_flag(cpu, ZERO_FLAG_BIT, true_result == 0x0);

	bool half_carry_bit = ((n1 & 0xf) + (n2 & 0xf) + (n3 & 0xf)) > 0xf;
	set_flag(cpu, HALF_CARRY_FLAG_BIT, half_carry_bit);

	set_flag(cpu, SUBTRACTION_FLAG_BIT, 0);

	set_flag(cpu, CARRY_FLAG_BIT, (n1 + n2 + n3) > 0xff); //Doesn't use true result as I don't want to it roll back if overflow occurs here
}

void sub_update_flags(Cpu* cpu, uint8_t n1, uint8_t n2, uint8_t n3, uint8_t true_result) {
	set_flag(cpu, ZERO_FLAG_BIT, true_result == 0x0);

	bool half_borrow_bit = ((n1 & 0xf) - (n2 & 0xf) - (n3 & 0xf)) < 0x0;
	set_flag(cpu, HALF_CARRY_FLAG_BIT, half_borrow_bit);

	set_flag(cpu, SUBTRACTION_FLAG_BIT, 1);

	set_flag(cpu, CARRY_FLAG_BIT, (n1 - n2 - n3) < 0x0); 
}

void and_update_flags(Cpu* cpu, uint8_t result) {
	set_flag(cpu, ZERO_FLAG_BIT, result == 0x0);
	set_flag(cpu, HALF_CARRY_FLAG_BIT, 0x1);
	set_flag(cpu, SUBTRACTION_FLAG_BIT, 0x0);
	set_flag(cpu, CARRY_FLAG_BIT, 0x0);
}

void or_update_flags(Cpu* cpu, uint8_t result) {
	//Same logic for xor too
	set_flag(cpu, ZERO_FLAG_BIT, result == 0x0);
	set_flag(cpu, HALF_CARRY_FLAG_BIT, 0x0);
	set_flag(cpu, SUBTRACTION_FLAG_BIT, 0x0);
	set_flag(cpu, CARRY_FLAG_BIT, 0x0);
}

int add_a_r(Cpu* cpu, uint8_t r1) {
	uint8_t a = cpu->registers[REGISTER_A];
    uint8_t r = cpu->registers[r1];

	uint8_t result = a + r;
	cpu->registers[REGISTER_A] = result;

	add_update_flags(cpu, a, r, 0, result);

	return 4;
}

int add_a_n(Cpu* cpu) {
	uint8_t a = cpu->registers[REGISTER_A];
	uint8_t data = fetch8(cpu);
	
	uint8_t result = a + data;
	cpu->registers[REGISTER_A] = result;

	add_update_flags(cpu, a, data, 0, result);

	return 8;
}

int add_a_hl(Cpu* cpu) {
	uint8_t a = cpu->registers[REGISTER_A];
	uint16_t address = read_register_pair(cpu, REGISTER_PAIR_HL);
	uint8_t data = read_byte(cpu->bus, address);

	uint8_t result = a + data;
	cpu->registers[REGISTER_A] = result;

	add_update_flags(cpu, a, data, 0, result);

	return 8;
}

int adc_a_r(Cpu* cpu, uint8_t r1) {
	uint8_t a = cpu->registers[REGISTER_A];
	uint8_t r = cpu->registers[r1];
	uint8_t cy = get_flag(cpu, CARRY_FLAG_BIT);

	uint8_t result = a + r + cy;
	cpu->registers[REGISTER_A] = result;

	add_update_flags(cpu, a, r, cy, result);

	return 4;
}

int adc_a_n(Cpu* cpu) {
	uint8_t a = cpu->registers[REGISTER_A];
	uint8_t data = fetch8(cpu);
	uint8_t cy = get_flag(cpu, CARRY_FLAG_BIT);

	uint8_t result = a + data + cy;
	cpu->registers[REGISTER_A] = result;

	add_update_flags(cpu, a, data, cy, result);

	return 8;
}

int adc_a_hl(Cpu* cpu) {
	uint8_t a = cpu->registers[REGISTER_A];
	uint16_t address = read_register_pair(cpu, REGISTER_PAIR_HL);
	uint8_t data = read_byte(cpu->bus, address);
	uint8_t cy = get_flag(cpu, CARRY_FLAG_BIT);

	uint8_t result = a + data + cy;
	cpu->registers[REGISTER_A] = result;

	add_update_flags(cpu, a, data, cy, result);

	return 8;
}

int sub_a_r(Cpu* cpu, uint8_t r1) {
	uint8_t a = cpu->registers[REGISTER_A];
	uint8_t r = cpu->registers[r1];

	uint8_t result = a - r;
	cpu->registers[REGISTER_A] = result;

	sub_update_flags(cpu, a, r, 0, result);

	return 4;
}

int sub_a_n(Cpu* cpu) {
	uint8_t a = cpu->registers[REGISTER_A];
	uint8_t data = fetch8(cpu);

	uint8_t result = a - data;
	cpu->registers[REGISTER_A] = result;

	sub_update_flags(cpu, a, data, 0, result);

	return 8;
}

int sub_a_hl(Cpu* cpu) {
	uint8_t a = cpu->registers[REGISTER_A];
	uint16_t address = read_register_pair(cpu, REGISTER_PAIR_HL);
	uint8_t data = read_byte(cpu->bus, address);

	uint8_t result = a - data;
	cpu->registers[REGISTER_A] = result;

	sub_update_flags(cpu, a, data, 0, result);

	return 8;
}

int sbc_a_r(Cpu* cpu, uint8_t r1) {
	uint8_t a = cpu->registers[REGISTER_A];
	uint8_t r = cpu->registers[r1];
	uint8_t cy = get_flag(cpu, CARRY_FLAG_BIT);

	uint8_t result = a - r - cy;
	cpu->registers[REGISTER_A] = result;

	sub_update_flags(cpu, a, r, cy, result);

	return 4;
}

int sbc_a_n(Cpu* cpu) {
	uint8_t a = cpu->registers[REGISTER_A];
	uint8_t data = fetch8(cpu);
	uint8_t cy = get_flag(cpu, CARRY_FLAG_BIT);

	uint8_t result = a - data - cy;
	cpu->registers[REGISTER_A] = result;

	sub_update_flags(cpu, a, data, cy, result);

	return 8;
}

int sbc_a_hl(Cpu* cpu) {
	uint8_t a = cpu->registers[REGISTER_A];
	uint16_t address = read_register_pair(cpu, REGISTER_PAIR_HL);
	uint8_t data = read_byte(cpu->bus, address);
	uint8_t cy = get_flag(cpu, CARRY_FLAG_BIT);

	uint8_t result = a - data - cy;
	cpu->registers[REGISTER_A] = result;

	sub_update_flags(cpu, a, data, cy, result);

	return 8;
}

int and_a_r(Cpu* cpu, uint8_t r1) {
	uint8_t a = cpu->registers[REGISTER_A];
	uint8_t r = cpu->registers[r1];

	uint8_t result = a & r;
	cpu->registers[REGISTER_A] = result;

	and_update_flags(cpu, result);

	return 4;
}

int and_a_hl(Cpu* cpu) {
	uint8_t a = cpu->registers[REGISTER_A];
	uint16_t address = read_register_pair(cpu, REGISTER_PAIR_HL);
	uint8_t data = read_byte(cpu->bus, address);

	uint8_t result = a & data;
	cpu->registers[REGISTER_A] = result;

	and_update_flags(cpu, result);

	return 8;
}

int and_a_n(Cpu* cpu) {
	uint8_t a = cpu->registers[REGISTER_A];
	uint8_t data = fetch8(cpu);

	uint8_t result = a & data;
	cpu->registers[REGISTER_A] = result;

	and_update_flags(cpu, result);

	return 8;
}

int or_a_r(Cpu* cpu, uint8_t r1) {
	uint8_t a = cpu->registers[REGISTER_A];
	uint8_t r = cpu->registers[r1];

	uint8_t result = a | r;
	cpu->registers[REGISTER_A] = result;

	or_update_flags(cpu, result);

	return 4;
}

int or_a_hl(Cpu* cpu) {
	uint8_t a = cpu->registers[REGISTER_A];
	uint16_t address = read_register_pair(cpu, REGISTER_PAIR_HL);
	uint8_t data = read_byte(cpu->bus, address);

	uint8_t result = a | data;
	cpu->registers[REGISTER_A] = result;

	or_update_flags(cpu, result);

	return 8;
}

int or_a_n(Cpu* cpu) {
	uint8_t a = cpu->registers[REGISTER_A];
	uint8_t data = fetch8(cpu);

	uint8_t result = a | data;
	cpu->registers[REGISTER_A] = result;

	or_update_flags(cpu, result);

	return 8;
}

int xor_a_r(Cpu* cpu, uint8_t r1) {
	uint8_t a = cpu->registers[REGISTER_A];
	uint8_t r = cpu->registers[r1];

	uint8_t result = a ^ r;
	cpu->registers[REGISTER_A] = result;

	or_update_flags(cpu, result);

	return 4;
}

int xor_a_hl(Cpu* cpu) {
	uint8_t a = cpu->registers[REGISTER_A];
	uint16_t address = read_register_pair(cpu, REGISTER_PAIR_HL);
	uint8_t data = read_byte(cpu->bus, address);

	uint8_t result = a ^ data;
	cpu->registers[REGISTER_A] = result;

	or_update_flags(cpu, result);

	return 8;
}

int xor_a_n(Cpu* cpu) {
	uint8_t a = cpu->registers[REGISTER_A];
	uint8_t data = fetch8(cpu);

	uint8_t result = a ^ data;
	cpu->registers[REGISTER_A] = result;

	or_update_flags(cpu, result);

	return 8;
}