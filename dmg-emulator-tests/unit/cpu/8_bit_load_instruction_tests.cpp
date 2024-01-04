#include "pch.h"

#include "mock_cpu.h"

extern "C" {
	#include "../../../dmg-emulator/src/cpu/cpu.h"
	#include "../../../dmg-emulator/src/cpu/8_bit_load_instructions.h"
}

TEST(eight_bit_load_instruction_tests, ld_r_r) {
	Cpu* cpu = SetUpMockCpu();

	cpu->registers[REGISTER_A] = 5;
	cpu->registers[REGISTER_B] = 9;
	ld_r_r(cpu, REGISTER_A, REGISTER_B);

	EXPECT_EQ(cpu->registers[REGISTER_A], cpu->registers[REGISTER_B]);

	cpu->registers[REGISTER_C] = 3;
	cpu->registers[REGISTER_D] = 56;
	ld_r_r(cpu, REGISTER_C, REGISTER_D);

	EXPECT_EQ(cpu->registers[REGISTER_C], cpu->registers[REGISTER_D]);

	FreeMockCpu(cpu);
}