#include "pch.h"

#include "mock_cpu.h"

extern "C" {
#include "../../../dmg-emulator/src/cpu/cpu.h"
#include "../../../dmg-emulator/src/cpu/8_bit_arithmetic_logic_instructions.h"
}

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