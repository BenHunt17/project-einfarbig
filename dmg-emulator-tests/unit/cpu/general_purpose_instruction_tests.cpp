#include "pch.h"

#include "mock_cpu.h"

extern "C" {
#include "../../../dmg-emulator/src/cpu/cpu.h"
#include "../../../dmg-emulator/src/cpu/instructions/general_purpose_instructions.h"
}

TEST(general_purpose_instructions, daa) {
	Cpu* cpu = SetUpMockCpu(NULL, 0);

	//Simulate an addition
	cpu->registers[REGISTER_A] = 0x7d;
	set_flag(cpu, SUBTRACTION_FLAG_BIT, false);

	daa(cpu);

	EXPECT_EQ(cpu->registers[REGISTER_A], 0x83);
	EXPECT_EQ(get_flag(cpu, HALF_CARRY_FLAG_BIT), false);
	EXPECT_EQ(get_flag(cpu, ZERO_FLAG_BIT), false);
	EXPECT_EQ(get_flag(cpu, CARRY_FLAG_BIT), false);

	//Simulate a subtraction
	cpu->registers[REGISTER_A] = 0x4b;
	set_flag(cpu, SUBTRACTION_FLAG_BIT, true);
	set_flag(cpu, HALF_CARRY_FLAG_BIT, true);
	set_flag(cpu, CARRY_FLAG_BIT, false);

	daa(cpu);

	EXPECT_EQ(cpu->registers[REGISTER_A], 0x45);
	EXPECT_EQ(get_flag(cpu, HALF_CARRY_FLAG_BIT), false);
	EXPECT_EQ(get_flag(cpu, ZERO_FLAG_BIT), false);
	EXPECT_EQ(get_flag(cpu, CARRY_FLAG_BIT), false);
}

TEST(general_purpose_instructions, cpl) {
	Cpu* cpu = SetUpMockCpu(NULL, 0);

	cpu->registers[REGISTER_A] = 0x35;

	cpl(cpu);

	EXPECT_EQ(cpu->registers[REGISTER_A], 0xca);
	EXPECT_EQ(get_flag(cpu, HALF_CARRY_FLAG_BIT), true);
	EXPECT_EQ(get_flag(cpu, SUBTRACTION_FLAG_BIT), true);
}

TEST(general_purpose_instructions, ccf) {
	Cpu* cpu = SetUpMockCpu(NULL, 0);

	set_flag(cpu, CARRY_FLAG_BIT, true);

	ccf(cpu);

	EXPECT_EQ(get_flag(cpu, CARRY_FLAG_BIT), false);
	EXPECT_EQ(get_flag(cpu, HALF_CARRY_FLAG_BIT), false);
	EXPECT_EQ(get_flag(cpu, SUBTRACTION_FLAG_BIT), false);
}

TEST(general_purpose_instructions, scf) {
	Cpu* cpu = SetUpMockCpu(NULL, 0);

	set_flag(cpu, CARRY_FLAG_BIT, false);

	scf(cpu);

	EXPECT_EQ(get_flag(cpu, CARRY_FLAG_BIT), true);
	EXPECT_EQ(get_flag(cpu, HALF_CARRY_FLAG_BIT), false);
	EXPECT_EQ(get_flag(cpu, SUBTRACTION_FLAG_BIT), false);
}

TEST(general_purpose_instructions, di) {
	Cpu* cpu = SetUpMockCpu(NULL, 0);
	cpu->ime = true;

	di(cpu);

	EXPECT_EQ(cpu->ime, false);
}

TEST(general_purpose_instructions, ei) {
	Cpu* cpu = SetUpMockCpu(NULL, 0);

	ei(cpu);

	EXPECT_EQ(cpu->next_ime, true);
}
