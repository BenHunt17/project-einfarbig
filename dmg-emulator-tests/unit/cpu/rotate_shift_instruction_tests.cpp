#include "pch.h"

#include "mock_cpu.h"

extern "C" {
#include "../../../dmg-emulator/src/cpu/cpu.h"
#include "../../../dmg-emulator/src/cpu/rotate_shift_instructions.h"
}

TEST(rotate_shift_instruction_tests, rlca) {
	Cpu* cpu = SetUpMockCpu(NULL, 0);

	cpu->registers[REGISTER_A] = 0x85;

	rlca(cpu);

	EXPECT_EQ(cpu->registers[REGISTER_A], 0x0b);
	EXPECT_EQ(get_flag(cpu, HALF_CARRY_FLAG_BIT), 0x0);
	EXPECT_EQ(get_flag(cpu, SUBTRACTION_FLAG_BIT), 0x0);
	EXPECT_EQ(get_flag(cpu, CARRY_FLAG_BIT), 0x1);
	EXPECT_EQ(get_flag(cpu, ZERO_FLAG_BIT), 0x0);

	FreeMockCpu(cpu);
}

TEST(rotate_shift_instruction_tests, rla) {
	Cpu* cpu = SetUpMockCpu(NULL, 0);

	cpu->registers[REGISTER_A] = 0x95;
	set_flag(cpu, CARRY_FLAG_BIT, 0x1);

	rla(cpu);

	EXPECT_EQ(cpu->registers[REGISTER_A], 0x2b);
	EXPECT_EQ(get_flag(cpu, HALF_CARRY_FLAG_BIT), 0x0);
	EXPECT_EQ(get_flag(cpu, SUBTRACTION_FLAG_BIT), 0x0);
	EXPECT_EQ(get_flag(cpu, CARRY_FLAG_BIT), 0x1);
	EXPECT_EQ(get_flag(cpu, ZERO_FLAG_BIT), 0x0);

	FreeMockCpu(cpu);
}

TEST(rotate_shift_instruction_tests, rrca) {
	Cpu* cpu = SetUpMockCpu(NULL, 0);

	cpu->registers[REGISTER_A] = 0x3b;

	rrca(cpu);

	EXPECT_EQ(cpu->registers[REGISTER_A], 0x9d);
	EXPECT_EQ(get_flag(cpu, HALF_CARRY_FLAG_BIT), 0x0);
	EXPECT_EQ(get_flag(cpu, SUBTRACTION_FLAG_BIT), 0x0);
	EXPECT_EQ(get_flag(cpu, CARRY_FLAG_BIT), 0x1);
	EXPECT_EQ(get_flag(cpu, ZERO_FLAG_BIT), 0x0);

	FreeMockCpu(cpu);
}

TEST(rotate_shift_instruction_tests, rra) {
	Cpu* cpu = SetUpMockCpu(NULL, 0);

	cpu->registers[REGISTER_A] = 0x81;
	set_flag(cpu, CARRY_FLAG_BIT, 0x0);

	rra(cpu);

	EXPECT_EQ(cpu->registers[REGISTER_A], 0x40);
	EXPECT_EQ(get_flag(cpu, HALF_CARRY_FLAG_BIT), 0x0);
	EXPECT_EQ(get_flag(cpu, SUBTRACTION_FLAG_BIT), 0x0);
	EXPECT_EQ(get_flag(cpu, CARRY_FLAG_BIT), 0x1);
	EXPECT_EQ(get_flag(cpu, ZERO_FLAG_BIT), 0x0);

	FreeMockCpu(cpu);
}

TEST(rotate_shift_instruction_tests, rlc_r) {
	Cpu* cpu = SetUpMockCpu(NULL, 0);

	cpu->registers[REGISTER_B] = 0x85;

	rlc_r(cpu, REGISTER_B);

	EXPECT_EQ(cpu->registers[REGISTER_B], 0x0b);
	EXPECT_EQ(get_flag(cpu, HALF_CARRY_FLAG_BIT), 0x0);
	EXPECT_EQ(get_flag(cpu, SUBTRACTION_FLAG_BIT), 0x0);
	EXPECT_EQ(get_flag(cpu, CARRY_FLAG_BIT), 0x1);
	EXPECT_EQ(get_flag(cpu, ZERO_FLAG_BIT), 0x0);

	FreeMockCpu(cpu);
}

TEST(rotate_shift_instruction_tests, rlc_hl) {
	uint8_t program[] = { 0x00, 0x00, 0x00 };
	Cpu* cpu = SetUpMockCpu(program, 3);

	write_register_pair(cpu, REGISTER_PAIR_HL, 0xc001);

	rlc_hl(cpu);

	EXPECT_EQ(read_byte(cpu->bus, 0xc001), 0x0);
	EXPECT_EQ(get_flag(cpu, HALF_CARRY_FLAG_BIT), 0x0);
	EXPECT_EQ(get_flag(cpu, SUBTRACTION_FLAG_BIT), 0x0);
	EXPECT_EQ(get_flag(cpu, CARRY_FLAG_BIT), 0x0);
	EXPECT_EQ(get_flag(cpu, ZERO_FLAG_BIT), 0x1);

	FreeMockCpu(cpu);
}