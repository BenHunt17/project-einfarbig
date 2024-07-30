#include "pch.h"

#include "mock_cpu.h"

extern "C" {
#include "../../../dmg-emulator/src/cpu/cpu.h"
#include "../../../dmg-emulator/src/cpu/16_bit_arithmetic_logic_instructions.h"
}

TEST(sixteen_bit_arithmetic_logic_instruction_tests, add_hl_rr) {
	Cpu* cpu = SetUpMockCpu(NULL, 0);

	write_register_pair(cpu, REGISTER_PAIR_HL, 0x8a23);
	write_register_pair(cpu, REGISTER_PAIR_BC, 0x0605);

	add_hl_rr(cpu, REGISTER_PAIR_BC);

	EXPECT_EQ(read_register_pair(cpu, REGISTER_PAIR_HL), 0x9028);
	EXPECT_EQ(get_flag(cpu, HALF_CARRY_FLAG_BIT), 0x1);
	EXPECT_EQ(get_flag(cpu, SUBTRACTION_FLAG_BIT), 0x0);
	EXPECT_EQ(get_flag(cpu, CARRY_FLAG_BIT), 0x0);

	write_register_pair(cpu, REGISTER_PAIR_HL, 0x8a23);

	add_hl_rr(cpu, REGISTER_PAIR_HL);

	EXPECT_EQ(read_register_pair(cpu, REGISTER_PAIR_HL), 0x1446);
	EXPECT_EQ(get_flag(cpu, HALF_CARRY_FLAG_BIT), 0x1);
	EXPECT_EQ(get_flag(cpu, SUBTRACTION_FLAG_BIT), 0x0);
	EXPECT_EQ(get_flag(cpu, CARRY_FLAG_BIT), 0x1);

	FreeMockCpu(cpu);
}