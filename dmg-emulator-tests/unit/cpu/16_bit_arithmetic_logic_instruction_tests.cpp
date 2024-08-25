#include "pch.h"

#include "mock_cpu.h"

extern "C" {
#include "../../../dmg-emulator/src/cpu/cpu.h"
#include "../../../dmg-emulator/src/cpu/instructions/16_bit_arithmetic_logic_instructions.h"
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

TEST(sixteen_bit_arithmetic_logic_instruction_tests, add_sp_e) {
	uint8_t program[] = { 0x02, 0x00, 0x00 };
	Cpu* cpu = SetUpMockCpu(program, 3);

	cpu->sp = 0xfff8;

	add_sp_e(cpu);

	EXPECT_EQ(cpu->sp, 0xfffa);
	EXPECT_EQ(get_flag(cpu, HALF_CARRY_FLAG_BIT), 0x0);
	EXPECT_EQ(get_flag(cpu, SUBTRACTION_FLAG_BIT), 0x0);
	EXPECT_EQ(get_flag(cpu, CARRY_FLAG_BIT), 0x0);
	EXPECT_EQ(get_flag(cpu, ZERO_FLAG_BIT), 0x0);

	FreeMockCpu(cpu);
}

TEST(sixteen_bit_arithmetic_logic_instruction_tests, inc_rr) {
	Cpu* cpu = SetUpMockCpu(NULL, 0);

	write_register_pair(cpu, REGISTER_PAIR_DE, 0x235f);

	inc_rr(cpu, REGISTER_PAIR_DE);

	EXPECT_EQ(read_register_pair(cpu, REGISTER_PAIR_DE), 0x2360);

	FreeMockCpu(cpu);
}

TEST(sixteen_bit_arithmetic_logic_instruction_tests, dec_rr) {
	Cpu* cpu = SetUpMockCpu(NULL, 0);

	write_register_pair(cpu, REGISTER_PAIR_DE, 0x235f);

	dec_rr(cpu, REGISTER_PAIR_DE);

	EXPECT_EQ(read_register_pair(cpu, REGISTER_PAIR_DE), 0x235e);

	FreeMockCpu(cpu);
}