#include "pch.h"

#include "mock_cpu.h"

extern "C" {
#include "../../../dmg-emulator/src/cpu/cpu.h"
#include "../../../dmg-emulator/src/cpu/16_bit_load_instructions.h"
}

TEST(sixteen_bit_load_instruction_tests, ld_rr_nn) {
	uint8_t program[] = { 0x45, 0xa9 };
	Cpu* cpu = SetUpMockCpu(program, 2);

	ld_rr_nn(cpu, REGISTER_PAIR_BC);

	EXPECT_EQ(cpu->registers[REGISTER_B], 0xa9);
	EXPECT_EQ(cpu->registers[REGISTER_C], 0x45);

	FreeMockCpu(cpu);
}

TEST(sixteen_bit_load_instruction_tests, ld_sp_hl) {
	Cpu* cpu = SetUpMockCpu(NULL, 0);

	write_register_pair(cpu, REGISTER_PAIR_HL, 0x5a2b);
	ld_sp_hl(cpu);

	EXPECT_EQ(cpu->sp, 0x5a2b);

	FreeMockCpu(cpu);
}

TEST(sixteen_bit_load_instruction_tests, push_rr) {
	Cpu* cpu = SetUpMockCpu(NULL, 0);

	uint16_t sp_before = cpu->sp;

	write_register_pair(cpu, REGISTER_PAIR_BC, 0xa0c6);
	push_rr(cpu, REGISTER_PAIR_BC);

	EXPECT_EQ(cpu->sp, sp_before - 2);
	EXPECT_EQ(cpu->bus->ram[cpu->sp - 0xc000], 0xc6);
	EXPECT_EQ(cpu->bus->ram[cpu->sp - 0xc000 + 1], 0xa0);

	FreeMockCpu(cpu);
}

TEST(sixteen_bit_load_instruction_tests, pop_rr) {
	Cpu* cpu = SetUpMockCpu(NULL, 0);

	write_register_pair(cpu, REGISTER_PAIR_BC, 0xa0c6);
	push_rr(cpu, REGISTER_PAIR_BC);
	uint16_t sp_before = cpu->sp;

	pop_rr(cpu, REGISTER_PAIR_AF);

	EXPECT_EQ(cpu->sp, sp_before + 2);
	EXPECT_EQ(cpu->registers[REGISTER_A], 0xa0);
	EXPECT_EQ(cpu->registers[REGISTER_F], 0xc6);

	FreeMockCpu(cpu);
}

TEST(sixteen_bit_load_instruction_tests, ld_nn_sp) {
	uint8_t program[] = { 0x04, 0xc0, 0x00, 0x00, 0x00, 0x00 };
	Cpu* cpu = SetUpMockCpu(program, 6);

	cpu->sp = 0x67bc;
	ld_nn_sp(cpu);

	EXPECT_EQ(cpu->bus->ram[0x4], 0xbc);
	EXPECT_EQ(cpu->bus->ram[0x5], 0x67);

	FreeMockCpu(cpu);
}

TEST(sixteen_bit_load_instruction_tests, ld_hl_sp_e) {
	uint8_t program[] = { 0x02, 0xc0, 0x00, 0x00, 0x00, 0x00 };
	Cpu* cpu = SetUpMockCpu(program, 6);

	cpu->sp = 0xfff8;
	ld_hl_sp_e(cpu);

	EXPECT_EQ(cpu->registers[REGISTER_H], 0xff);
	EXPECT_EQ(cpu->registers[REGISTER_L], 0xfa);
	EXPECT_EQ(get_flag(cpu, ZERO_FLAG_BIT), 0x0);
	EXPECT_EQ(get_flag(cpu, HALF_CARRY_FLAG_BIT), 0x0);
	EXPECT_EQ(get_flag(cpu, SUBTRACTION_FLAG_BIT), 0x0);
	EXPECT_EQ(get_flag(cpu, CARRY_FLAG_BIT), 0x0);

	FreeMockCpu(cpu);
}