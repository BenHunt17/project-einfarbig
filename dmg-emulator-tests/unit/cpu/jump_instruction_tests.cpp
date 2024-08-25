#include "pch.h"

#include "mock_cpu.h"

extern "C" {
#include "../../../dmg-emulator/src/cpu/cpu.h"
#include "../../../dmg-emulator/src/cpu/instructions/jump_instructions.h"
}

TEST(jump_instruction_tests, jp_nn) {
	uint8_t program[] = { 0x00, 0x80 };
	Cpu* cpu = SetUpMockCpu(program, 2);

	jp_nn(cpu);

	EXPECT_EQ(cpu->pc, 0x8000);
}

TEST(jump_instruction_tests, jp_cc_nn) {
	uint8_t program[] = { 0x00, 0x80 };
	Cpu* cpu = SetUpMockCpu(program, 2);

	set_flag(cpu, ZERO_FLAG_BIT, 0x1);

	uint16_t initial_pc = cpu->pc;

	jp_cc_nn(cpu, CONDITION_NZ);

	EXPECT_EQ(cpu->pc, initial_pc);

	jp_cc_nn(cpu, CONDITION_Z);

	EXPECT_EQ(cpu->pc, 0x8000);

	cpu->pc = initial_pc;

	jp_cc_nn(cpu, CONDITION_C);

	EXPECT_EQ(cpu->pc, initial_pc);

	jp_cc_nn(cpu, CONDITION_NC);

	EXPECT_EQ(cpu->pc, 0x8000);
}

TEST(jump_instruction_tests, jr_e) {
	uint8_t program[] = { 0x58 };
	Cpu* cpu = SetUpMockCpu(program, 1);

	uint16_t initial_pc = cpu->pc;

	jr_e(cpu);

	EXPECT_EQ(cpu->pc, initial_pc + 0x59); //Add one because the instruction increments the pc to fetch the offset
}

TEST(jump_instruction_tests, jr_cc_e) {
	uint8_t program[] = { 0x58 };
	Cpu* cpu = SetUpMockCpu(program, 1);

	uint16_t initial_pc = cpu->pc;
	set_flag(cpu, CARRY_FLAG_BIT, 0x1);

	jr_cc_e(cpu, CONDITION_Z);

	EXPECT_EQ(cpu->pc, initial_pc);

	jr_cc_e(cpu, CONDITION_C);

	EXPECT_EQ(cpu->pc, initial_pc + 0x59);
}

TEST(jump_instruction_tests, jp_hl) {
	Cpu* cpu = SetUpMockCpu(NULL, 0);

	write_register_pair(cpu, REGISTER_PAIR_HL, 0x8000);

	jp_hl(cpu);

	EXPECT_EQ(cpu->pc, 0x8000);
}