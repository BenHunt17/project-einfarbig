#include "pch.h"

#include "mock_cpu.h"

extern "C" {
#include "../../../dmg-emulator/src/cpu/cpu.h"
#include "../../../dmg-emulator/src/cpu/instructions/8_bit_arithmetic_logic_instructions.h"
}

namespace cpu_unit_tests {
	TEST(eight_bit_arithmetic_logic_instruction_tests, add_a_r) {
		Cpu* cpu = SetUpMockCpu(NULL, 0);

		cpu->registers[REGISTER_A] = 0x3a;
		cpu->registers[REGISTER_B] = 0xc6;
		add_a_r(cpu, REGISTER_B);

		EXPECT_EQ(cpu->registers[REGISTER_A], 0);
		EXPECT_EQ(get_flag(cpu, ZERO_FLAG_BIT), 1);
		EXPECT_EQ(get_flag(cpu, HALF_CARRY_FLAG_BIT), 1);
		EXPECT_EQ(get_flag(cpu, SUBTRACTION_FLAG_BIT), 0);
		EXPECT_EQ(get_flag(cpu, CARRY_FLAG_BIT), 1);

		cpu->registers[REGISTER_A] = 0x2d;
		cpu->registers[REGISTER_C] = 0xa8;

		add_a_r(cpu, REGISTER_C);

		EXPECT_EQ(cpu->registers[REGISTER_A], 0xd5);
		EXPECT_EQ(get_flag(cpu, ZERO_FLAG_BIT), 0);
		EXPECT_EQ(get_flag(cpu, HALF_CARRY_FLAG_BIT), 1);
		EXPECT_EQ(get_flag(cpu, SUBTRACTION_FLAG_BIT), 0);
		EXPECT_EQ(get_flag(cpu, CARRY_FLAG_BIT), 0);

		FreeMockCpu(cpu);
	}

	TEST(eight_bit_arithmetic_logic_instruction_tests, add_a_n) {
		uint8_t program[] = { 0xff, 0x00 };
		Cpu* cpu = SetUpMockCpu(program, 2);

		cpu->registers[REGISTER_A] = 0x3c;

		add_a_n(cpu);

		EXPECT_EQ(cpu->registers[REGISTER_A], 0x3b);
		EXPECT_EQ(get_flag(cpu, ZERO_FLAG_BIT), 0);
		EXPECT_EQ(get_flag(cpu, HALF_CARRY_FLAG_BIT), 1);
		EXPECT_EQ(get_flag(cpu, SUBTRACTION_FLAG_BIT), 0);
		EXPECT_EQ(get_flag(cpu, CARRY_FLAG_BIT), 1);

		FreeMockCpu(cpu);
	}

	TEST(eight_bit_arithmetic_logic_instruction_tests, add_a_hl) {
		uint8_t program[] = { 0x00, 0x00, 0x00, 0x00, 0x12, 0x00 };
		Cpu* cpu = SetUpMockCpu(program, 6);

		cpu->registers[REGISTER_A] = 0x3c;
		write_register_pair(cpu, REGISTER_PAIR_HL, 0xc004);

		add_a_hl(cpu);

		EXPECT_EQ(cpu->registers[REGISTER_A], 0x4e);
		EXPECT_EQ(get_flag(cpu, ZERO_FLAG_BIT), 0);
		EXPECT_EQ(get_flag(cpu, HALF_CARRY_FLAG_BIT), 0);
		EXPECT_EQ(get_flag(cpu, SUBTRACTION_FLAG_BIT), 0);
		EXPECT_EQ(get_flag(cpu, CARRY_FLAG_BIT), 0);

		FreeMockCpu(cpu);
	}

	TEST(eight_bit_arithmetic_logic_instruction_tests, adc_a_r) {
		Cpu* cpu = SetUpMockCpu(NULL, 0);

		cpu->registers[REGISTER_A] = 0xe1;
		cpu->registers[REGISTER_B] = 0x0f;
		set_flag(cpu, CARRY_FLAG_BIT, true);

		adc_a_r(cpu, REGISTER_B);

		EXPECT_EQ(cpu->registers[REGISTER_A], 0xf1);
		EXPECT_EQ(get_flag(cpu, ZERO_FLAG_BIT), 0);
		EXPECT_EQ(get_flag(cpu, HALF_CARRY_FLAG_BIT), 1);
		EXPECT_EQ(get_flag(cpu, SUBTRACTION_FLAG_BIT), 0);
		EXPECT_EQ(get_flag(cpu, CARRY_FLAG_BIT), 0);

		FreeMockCpu(cpu);
	}

	TEST(eight_bit_arithmetic_logic_instruction_tests, adc_a_n) {
		uint8_t program[] = { 0x3b, 0x00 };
		Cpu* cpu = SetUpMockCpu(program, 2);

		cpu->registers[REGISTER_A] = 0xe1;
		set_flag(cpu, CARRY_FLAG_BIT, true);

		adc_a_n(cpu);

		EXPECT_EQ(cpu->registers[REGISTER_A], 0x1d);
		EXPECT_EQ(get_flag(cpu, ZERO_FLAG_BIT), 0);
		EXPECT_EQ(get_flag(cpu, HALF_CARRY_FLAG_BIT), 0);
		EXPECT_EQ(get_flag(cpu, SUBTRACTION_FLAG_BIT), 0);
		EXPECT_EQ(get_flag(cpu, CARRY_FLAG_BIT), 1);

		FreeMockCpu(cpu);
	}

	TEST(eight_bit_arithmetic_logic_instruction_tests, adc_a_hl) {
		uint8_t program[] = { 0x00, 0x00, 0x00, 0x00, 0x1e, 0x00 };
		Cpu* cpu = SetUpMockCpu(program, 6);

		cpu->registers[REGISTER_A] = 0xe1;
		write_register_pair(cpu, REGISTER_PAIR_HL, 0xc004);
		set_flag(cpu, CARRY_FLAG_BIT, true);

		adc_a_hl(cpu);

		EXPECT_EQ(cpu->registers[REGISTER_A], 0x0);
		EXPECT_EQ(get_flag(cpu, ZERO_FLAG_BIT), 1);
		EXPECT_EQ(get_flag(cpu, HALF_CARRY_FLAG_BIT), 1);
		EXPECT_EQ(get_flag(cpu, SUBTRACTION_FLAG_BIT), 0);
		EXPECT_EQ(get_flag(cpu, CARRY_FLAG_BIT), 1);

		FreeMockCpu(cpu);
	}

	TEST(eight_bit_arithmetic_logic_instruction_tests, sub_a_r) {
		Cpu* cpu = SetUpMockCpu(NULL, 0);

		cpu->registers[REGISTER_A] = 0x3e;
		cpu->registers[REGISTER_B] = 0x3e;

		sub_a_r(cpu, REGISTER_B);

		EXPECT_EQ(cpu->registers[REGISTER_A], 0);
		EXPECT_EQ(get_flag(cpu, ZERO_FLAG_BIT), 1);
		EXPECT_EQ(get_flag(cpu, HALF_CARRY_FLAG_BIT), 0);
		EXPECT_EQ(get_flag(cpu, SUBTRACTION_FLAG_BIT), 1);
		EXPECT_EQ(get_flag(cpu, CARRY_FLAG_BIT), 0);

		FreeMockCpu(cpu);
	}

	TEST(eight_bit_arithmetic_logic_instruction_tests, sub_a_n) {
		uint8_t program[] = { 0x0f, 0x0 };
		Cpu* cpu = SetUpMockCpu(program, 2);

		cpu->registers[REGISTER_A] = 0x3e;

		sub_a_n(cpu);

		EXPECT_EQ(cpu->registers[REGISTER_A], 0x2f);
		EXPECT_EQ(get_flag(cpu, ZERO_FLAG_BIT), 0);
		EXPECT_EQ(get_flag(cpu, HALF_CARRY_FLAG_BIT), 1);
		EXPECT_EQ(get_flag(cpu, SUBTRACTION_FLAG_BIT), 1);
		EXPECT_EQ(get_flag(cpu, CARRY_FLAG_BIT), 0);

		FreeMockCpu(cpu);
	}

	TEST(eight_bit_arithmetic_logic_instruction_tests, sub_a_hl) {
		uint8_t program[] = { 0x00, 0x00, 0x00, 0x00, 0x40, 0x00 };
		Cpu* cpu = SetUpMockCpu(program, 6);

		cpu->registers[REGISTER_A] = 0x3e;
		write_register_pair(cpu, REGISTER_PAIR_HL, 0xc004);

		sub_a_hl(cpu);

		EXPECT_EQ(cpu->registers[REGISTER_A], 0xfe);
		EXPECT_EQ(get_flag(cpu, ZERO_FLAG_BIT), 0);
		EXPECT_EQ(get_flag(cpu, HALF_CARRY_FLAG_BIT), 0);
		EXPECT_EQ(get_flag(cpu, SUBTRACTION_FLAG_BIT), 1);
		EXPECT_EQ(get_flag(cpu, CARRY_FLAG_BIT), 1);

		FreeMockCpu(cpu);
	}

	TEST(eight_bit_arithmetic_logic_instruction_tests, sbc_a_r) {
		Cpu* cpu = SetUpMockCpu(NULL, 0);

		cpu->registers[REGISTER_A] = 0x3b;
		cpu->registers[REGISTER_B] = 0x2a;
		set_flag(cpu, CARRY_FLAG_BIT, true);

		sbc_a_r(cpu, REGISTER_B);

		EXPECT_EQ(cpu->registers[REGISTER_A], 0x10);
		EXPECT_EQ(get_flag(cpu, ZERO_FLAG_BIT), 0);
		EXPECT_EQ(get_flag(cpu, HALF_CARRY_FLAG_BIT), 0);
		EXPECT_EQ(get_flag(cpu, SUBTRACTION_FLAG_BIT), 1);
		EXPECT_EQ(get_flag(cpu, CARRY_FLAG_BIT), 0);

		FreeMockCpu(cpu);
	}

	TEST(eight_bit_arithmetic_logic_instruction_tests, sbc_a_n) {
		uint8_t program[] = { 0x3a, 0x00 };
		Cpu* cpu = SetUpMockCpu(program, 2);

		cpu->registers[REGISTER_A] = 0x3b;
		set_flag(cpu, CARRY_FLAG_BIT, true);

		sbc_a_n(cpu);

		EXPECT_EQ(cpu->registers[REGISTER_A], 0x0);
		EXPECT_EQ(get_flag(cpu, ZERO_FLAG_BIT), 1);
		EXPECT_EQ(get_flag(cpu, HALF_CARRY_FLAG_BIT), 0);
		EXPECT_EQ(get_flag(cpu, SUBTRACTION_FLAG_BIT), 1);
		EXPECT_EQ(get_flag(cpu, CARRY_FLAG_BIT), 0);

		FreeMockCpu(cpu);
	}

	TEST(eight_bit_arithmetic_logic_instruction_tests, sbc_a_hl) {
		uint8_t program[] = { 0x00, 0x00, 0x00, 0x00, 0x4f, 0x00 };
		Cpu* cpu = SetUpMockCpu(program, 6);

		cpu->registers[REGISTER_A] = 0x3b;
		write_register_pair(cpu, REGISTER_PAIR_HL, 0xc004);
		set_flag(cpu, CARRY_FLAG_BIT, true);

		sbc_a_hl(cpu);

		EXPECT_EQ(cpu->registers[REGISTER_A], 0xeb);
		EXPECT_EQ(get_flag(cpu, ZERO_FLAG_BIT), 0);
		EXPECT_EQ(get_flag(cpu, HALF_CARRY_FLAG_BIT), 1);
		EXPECT_EQ(get_flag(cpu, SUBTRACTION_FLAG_BIT), 1);
		EXPECT_EQ(get_flag(cpu, CARRY_FLAG_BIT), 1);

		FreeMockCpu(cpu);
	}

	TEST(eight_bit_arithmetic_logic_instruction_tests, and_a_r) {
		Cpu* cpu = SetUpMockCpu(NULL, 0);

		cpu->registers[REGISTER_A] = 0x5a;
		cpu->registers[REGISTER_B] = 0x3f;

		and_a_r(cpu, REGISTER_B);

		EXPECT_EQ(cpu->registers[REGISTER_A], 0x1a);
		EXPECT_EQ(get_flag(cpu, ZERO_FLAG_BIT), 0);
		EXPECT_EQ(get_flag(cpu, HALF_CARRY_FLAG_BIT), 1);
		EXPECT_EQ(get_flag(cpu, SUBTRACTION_FLAG_BIT), 0);
		EXPECT_EQ(get_flag(cpu, CARRY_FLAG_BIT), 0);

		FreeMockCpu(cpu);
	}

	TEST(eight_bit_arithmetic_logic_instruction_tests, and_a_n) {
		uint8_t program[] = { 0x38, 0x0 };
		Cpu* cpu = SetUpMockCpu(program, 2);

		cpu->registers[REGISTER_A] = 0x5a;

		and_a_n(cpu);

		EXPECT_EQ(cpu->registers[REGISTER_A], 0x18);
		EXPECT_EQ(get_flag(cpu, ZERO_FLAG_BIT), 0);
		EXPECT_EQ(get_flag(cpu, HALF_CARRY_FLAG_BIT), 1);
		EXPECT_EQ(get_flag(cpu, SUBTRACTION_FLAG_BIT), 0);
		EXPECT_EQ(get_flag(cpu, CARRY_FLAG_BIT), 0);

		FreeMockCpu(cpu);
	}

	TEST(eight_bit_arithmetic_logic_instruction_tests, and_a_hl) {
		uint8_t program[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
		Cpu* cpu = SetUpMockCpu(program, 6);

		cpu->registers[REGISTER_A] = 0x5a;
		write_register_pair(cpu, REGISTER_PAIR_HL, 0xc004);

		and_a_hl(cpu);

		EXPECT_EQ(cpu->registers[REGISTER_A], 0x00);
		EXPECT_EQ(get_flag(cpu, ZERO_FLAG_BIT), 1);
		EXPECT_EQ(get_flag(cpu, HALF_CARRY_FLAG_BIT), 1);
		EXPECT_EQ(get_flag(cpu, SUBTRACTION_FLAG_BIT), 0);
		EXPECT_EQ(get_flag(cpu, CARRY_FLAG_BIT), 0);
	}

	TEST(eight_bit_arithmetic_logic_instruction_tests, or_a_r) {
		Cpu* cpu = SetUpMockCpu(NULL, 0);

		cpu->registers[REGISTER_A] = 0x5a;
		cpu->registers[REGISTER_B] = 0x5a;

		or_a_r(cpu, REGISTER_B);

		EXPECT_EQ(cpu->registers[REGISTER_A], 0x5a);
		EXPECT_EQ(get_flag(cpu, ZERO_FLAG_BIT), 0);
		EXPECT_EQ(get_flag(cpu, HALF_CARRY_FLAG_BIT), 0);
		EXPECT_EQ(get_flag(cpu, SUBTRACTION_FLAG_BIT), 0);
		EXPECT_EQ(get_flag(cpu, CARRY_FLAG_BIT), 0);

		FreeMockCpu(cpu);
	}

	TEST(eight_bit_arithmetic_logic_instruction_tests, or_a_n) {
		uint8_t program[] = { 0x03, 0x0 };
		Cpu* cpu = SetUpMockCpu(program, 2);

		cpu->registers[REGISTER_A] = 0x5a;

		or_a_n(cpu);

		EXPECT_EQ(cpu->registers[REGISTER_A], 0x5b);
		EXPECT_EQ(get_flag(cpu, ZERO_FLAG_BIT), 0);
		EXPECT_EQ(get_flag(cpu, HALF_CARRY_FLAG_BIT), 0);
		EXPECT_EQ(get_flag(cpu, SUBTRACTION_FLAG_BIT), 0);
		EXPECT_EQ(get_flag(cpu, CARRY_FLAG_BIT), 0);

		FreeMockCpu(cpu);
	}

	TEST(eight_bit_arithmetic_logic_instruction_tests, or_a_hl) {
		uint8_t program[] = { 0x00, 0x00, 0x00, 0x00, 0x0f, 0x00 };
		Cpu* cpu = SetUpMockCpu(program, 6);

		cpu->registers[REGISTER_A] = 0x5a;
		write_register_pair(cpu, REGISTER_PAIR_HL, 0xc004);

		or_a_hl(cpu);

		EXPECT_EQ(cpu->registers[REGISTER_A], 0x5f);
		EXPECT_EQ(get_flag(cpu, ZERO_FLAG_BIT), 0);
		EXPECT_EQ(get_flag(cpu, HALF_CARRY_FLAG_BIT), 0);
		EXPECT_EQ(get_flag(cpu, SUBTRACTION_FLAG_BIT), 0);
		EXPECT_EQ(get_flag(cpu, CARRY_FLAG_BIT), 0);
	}

	TEST(eight_bit_arithmetic_logic_instruction_tests, xor_a_r) {
		Cpu* cpu = SetUpMockCpu(NULL, 0);

		cpu->registers[REGISTER_A] = 0xff;
		cpu->registers[REGISTER_B] = 0xff;

		xor_a_r(cpu, REGISTER_B);

		EXPECT_EQ(cpu->registers[REGISTER_A], 0x0);
		EXPECT_EQ(get_flag(cpu, ZERO_FLAG_BIT), 1);
		EXPECT_EQ(get_flag(cpu, HALF_CARRY_FLAG_BIT), 0);
		EXPECT_EQ(get_flag(cpu, SUBTRACTION_FLAG_BIT), 0);
		EXPECT_EQ(get_flag(cpu, CARRY_FLAG_BIT), 0);

		FreeMockCpu(cpu);
	}

	TEST(eight_bit_arithmetic_logic_instruction_tests, xor_a_n) {
		uint8_t program[] = { 0x0f, 0x0 };
		Cpu* cpu = SetUpMockCpu(program, 2);

		cpu->registers[REGISTER_A] = 0xff;

		xor_a_n(cpu);

		EXPECT_EQ(cpu->registers[REGISTER_A], 0xf0);
		EXPECT_EQ(get_flag(cpu, ZERO_FLAG_BIT), 0);
		EXPECT_EQ(get_flag(cpu, HALF_CARRY_FLAG_BIT), 0);
		EXPECT_EQ(get_flag(cpu, SUBTRACTION_FLAG_BIT), 0);
		EXPECT_EQ(get_flag(cpu, CARRY_FLAG_BIT), 0);

		FreeMockCpu(cpu);
	}

	TEST(eight_bit_arithmetic_logic_instruction_tests, xor_a_hl) {
		uint8_t program[] = { 0x00, 0x00, 0x00, 0x00, 0x8a, 0x00 };
		Cpu* cpu = SetUpMockCpu(program, 6);

		cpu->registers[REGISTER_A] = 0xff;
		write_register_pair(cpu, REGISTER_PAIR_HL, 0xc004);

		xor_a_hl(cpu);

		EXPECT_EQ(cpu->registers[REGISTER_A], 0x75);
		EXPECT_EQ(get_flag(cpu, ZERO_FLAG_BIT), 0);
		EXPECT_EQ(get_flag(cpu, HALF_CARRY_FLAG_BIT), 0);
		EXPECT_EQ(get_flag(cpu, SUBTRACTION_FLAG_BIT), 0);
		EXPECT_EQ(get_flag(cpu, CARRY_FLAG_BIT), 0);
	}

	TEST(eight_bit_arithmetic_logic_instruction_tests, cp_a_r) {
		Cpu* cpu = SetUpMockCpu(NULL, 0);

		cpu->registers[REGISTER_A] = 0x3c;
		cpu->registers[REGISTER_B] = 0x2f;

		cp_a_r(cpu, REGISTER_B);

		EXPECT_EQ(get_flag(cpu, ZERO_FLAG_BIT), 0x0);
		EXPECT_EQ(get_flag(cpu, HALF_CARRY_FLAG_BIT), 0x1);
		EXPECT_EQ(get_flag(cpu, SUBTRACTION_FLAG_BIT), 0x1);
		EXPECT_EQ(get_flag(cpu, CARRY_FLAG_BIT), 0x0);

		FreeMockCpu(cpu);
	}

	TEST(eight_bit_arithmetic_logic_instruction_tests, cp_a_n) {
		uint8_t program[] = { 0x3c, 0x0 };
		Cpu* cpu = SetUpMockCpu(program, 2);

		cpu->registers[REGISTER_A] = 0x3c;

		cp_a_n(cpu);

		EXPECT_EQ(get_flag(cpu, ZERO_FLAG_BIT), 0x1);
		EXPECT_EQ(get_flag(cpu, HALF_CARRY_FLAG_BIT), 0x0);
		EXPECT_EQ(get_flag(cpu, SUBTRACTION_FLAG_BIT), 0x1);
		EXPECT_EQ(get_flag(cpu, CARRY_FLAG_BIT), 0x0);

		FreeMockCpu(cpu);
	}

	TEST(eight_bit_arithmetic_logic_instruction_tests, cp_a_hl) {
		uint8_t program[] = { 0x00, 0x00, 0x00, 0x00, 0x40, 0x00 };
		Cpu* cpu = SetUpMockCpu(program, 6);

		cpu->registers[REGISTER_A] = 0x3c;
		write_register_pair(cpu, REGISTER_PAIR_HL, 0xc004);

		cp_a_hl(cpu);

		EXPECT_EQ(get_flag(cpu, ZERO_FLAG_BIT), 0x0);
		EXPECT_EQ(get_flag(cpu, HALF_CARRY_FLAG_BIT), 0x0);
		EXPECT_EQ(get_flag(cpu, SUBTRACTION_FLAG_BIT), 0x1);
		EXPECT_EQ(get_flag(cpu, CARRY_FLAG_BIT), 0x1);

		FreeMockCpu(cpu);
	}

	TEST(eight_bit_arithmetic_logic_instruction_tests, inc_r) {
		Cpu* cpu = SetUpMockCpu(NULL, 0);

		cpu->registers[REGISTER_A] = 0xff;

		inc_r(cpu, REGISTER_A);

		EXPECT_EQ(cpu->registers[REGISTER_A], 0x0);
		EXPECT_EQ(get_flag(cpu, ZERO_FLAG_BIT), 0x1);
		EXPECT_EQ(get_flag(cpu, SUBTRACTION_FLAG_BIT), 0x0);
		EXPECT_EQ(get_flag(cpu, HALF_CARRY_FLAG_BIT), 0x1);

		FreeMockCpu(cpu);
	}

	TEST(eight_bit_arithmetic_logic_instruction_tests, inc_hl) {
		uint8_t program[] = { 0x00, 0x00, 0x00, 0x00, 0x50, 0x00 };
		Cpu* cpu = SetUpMockCpu(program, 6);

		write_register_pair(cpu, REGISTER_PAIR_HL, 0xc004);

		inc_hl(cpu);

		EXPECT_EQ(read_byte(cpu->bus, 0xc004), 0x51);
		EXPECT_EQ(get_flag(cpu, ZERO_FLAG_BIT), 0x0);
		EXPECT_EQ(get_flag(cpu, SUBTRACTION_FLAG_BIT), 0x0);
		EXPECT_EQ(get_flag(cpu, HALF_CARRY_FLAG_BIT), 0x0);

		FreeMockCpu(cpu);
	}

	TEST(eight_bit_arithmetic_logic_instruction_tests, dec_r) {
		Cpu* cpu = SetUpMockCpu(NULL, 0);

		cpu->registers[REGISTER_L] = 0x01;

		dec_r(cpu, REGISTER_L);

		EXPECT_EQ(cpu->registers[REGISTER_A], 0x0);
		EXPECT_EQ(get_flag(cpu, ZERO_FLAG_BIT), 0x1);
		EXPECT_EQ(get_flag(cpu, SUBTRACTION_FLAG_BIT), 0x1);
		EXPECT_EQ(get_flag(cpu, HALF_CARRY_FLAG_BIT), 0x0);

		FreeMockCpu(cpu);
	}

	TEST(eight_bit_arithmetic_logic_instruction_tests, dec_hl) {
		uint8_t program[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
		Cpu* cpu = SetUpMockCpu(program, 6);

		write_register_pair(cpu, REGISTER_PAIR_HL, 0xc004);

		dec_hl(cpu);

		EXPECT_EQ(read_byte(cpu->bus, 0xc004), 0xff);
		EXPECT_EQ(get_flag(cpu, ZERO_FLAG_BIT), 0x0);
		EXPECT_EQ(get_flag(cpu, SUBTRACTION_FLAG_BIT), 0x1);
		EXPECT_EQ(get_flag(cpu, HALF_CARRY_FLAG_BIT), 0x1);

		FreeMockCpu(cpu);
	}
}