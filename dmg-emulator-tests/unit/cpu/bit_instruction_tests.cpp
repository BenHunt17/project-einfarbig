#include "pch.h"

#include "mock_cpu.h"

extern "C" {
#include "../../../dmg-emulator/src/cpu/cpu.h"
#include "../../../dmg-emulator/src/cpu/instructions/bit_instructions.h"
}

TEST(bit_instruction_tests, bit_b_r) {
	Cpu* cpu = SetUpMockCpu(NULL, 0);

	cpu->registers[REGISTER_A] = 0x80;
	cpu->registers[REGISTER_L] = 0xef;

	bit_b_r(cpu, 7, REGISTER_A);

	EXPECT_EQ(get_flag(cpu, HALF_CARRY_FLAG_BIT), 0x1);
	EXPECT_EQ(get_flag(cpu, SUBTRACTION_FLAG_BIT), 0x0);
	EXPECT_EQ(get_flag(cpu, ZERO_FLAG_BIT), 0x0);

	bit_b_r(cpu, 4, REGISTER_L);

	EXPECT_EQ(get_flag(cpu, HALF_CARRY_FLAG_BIT), 0x1);
	EXPECT_EQ(get_flag(cpu, SUBTRACTION_FLAG_BIT), 0x0);
	EXPECT_EQ(get_flag(cpu, ZERO_FLAG_BIT), 0x1);


	FreeMockCpu(cpu);
}

TEST(bit_instruction_tests, bit_b_hl) {
	uint8_t program[] = { 0x00, 0xfe, 0x00 };
	Cpu* cpu = SetUpMockCpu(program, 3);

	write_register_pair(cpu, REGISTER_PAIR_HL, 0xc001);

	bit_b_hl(cpu, 0);

	EXPECT_EQ(get_flag(cpu, HALF_CARRY_FLAG_BIT), 0x1);
	EXPECT_EQ(get_flag(cpu, SUBTRACTION_FLAG_BIT), 0x0);
	EXPECT_EQ(get_flag(cpu, ZERO_FLAG_BIT), 0x1);

	bit_b_hl(cpu, 1);

	EXPECT_EQ(get_flag(cpu, HALF_CARRY_FLAG_BIT), 0x1);
	EXPECT_EQ(get_flag(cpu, SUBTRACTION_FLAG_BIT), 0x0);
	EXPECT_EQ(get_flag(cpu, ZERO_FLAG_BIT), 0x0);


	FreeMockCpu(cpu);
}

TEST(bit_instruction_tests, set_b_r) {
	Cpu* cpu = SetUpMockCpu(NULL, 0);

	cpu->registers[REGISTER_A] = 0x80;
	cpu->registers[REGISTER_L] = 0x3b;

	set_b_r(cpu, 3, REGISTER_A);

	EXPECT_EQ(cpu->registers[REGISTER_A], 0x88);

	set_b_r(cpu, 7, REGISTER_L);

	EXPECT_EQ(cpu->registers[REGISTER_L], 0xbb);


	FreeMockCpu(cpu);
}

TEST(bit_instruction_tests, set_b_hl) {
	uint8_t program[] = { 0x00, 0x00, 0x00 };
	Cpu* cpu = SetUpMockCpu(program, 3);

	write_register_pair(cpu, REGISTER_PAIR_HL, 0xc001);

	set_b_hl(cpu, 3);

	EXPECT_EQ(read_byte(cpu->bus, 0xc001), 0x8);


	FreeMockCpu(cpu);
}

TEST(bit_instruction_tests, res_b_r) {
	Cpu* cpu = SetUpMockCpu(NULL, 0);

	cpu->registers[REGISTER_A] = 0x80;
	cpu->registers[REGISTER_L] = 0x3b;

	res_b_r(cpu, 7, REGISTER_A);

	EXPECT_EQ(cpu->registers[REGISTER_A], 0x0);

	res_b_r(cpu, 1, REGISTER_L);

	EXPECT_EQ(cpu->registers[REGISTER_L], 0x39);


	FreeMockCpu(cpu);
}

TEST(bit_instruction_tests, res_b_hl) {
	uint8_t program[] = { 0x00, 0xff, 0x00 };
	Cpu* cpu = SetUpMockCpu(program, 3);

	write_register_pair(cpu, REGISTER_PAIR_HL, 0xc001);

	res_b_hl(cpu, 3);

	EXPECT_EQ(read_byte(cpu->bus, 0xc001), 0xf7);


	FreeMockCpu(cpu);
}