#include "pch.h"

#include "mock_cpu.h"

extern "C" {
#include "../../../dmg-emulator/src/cpu/cpu.h"
#include "../../../dmg-emulator/src/cpu/instructions/rotate_shift_instructions.h"
}

namespace cpu_unit_tests {
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

	TEST(rotate_shift_instruction_tests, rl_r) {
		Cpu* cpu = SetUpMockCpu(NULL, 0);

		cpu->registers[REGISTER_L] = 0x80;

		rl_r(cpu, REGISTER_L);

		EXPECT_EQ(cpu->registers[REGISTER_L], 0x0);
		EXPECT_EQ(get_flag(cpu, HALF_CARRY_FLAG_BIT), 0x0);
		EXPECT_EQ(get_flag(cpu, SUBTRACTION_FLAG_BIT), 0x0);
		EXPECT_EQ(get_flag(cpu, CARRY_FLAG_BIT), 0x1);
		EXPECT_EQ(get_flag(cpu, ZERO_FLAG_BIT), 0x1);

		FreeMockCpu(cpu);
	}

	TEST(rotate_shift_instruction_tests, rl_hl) {
		uint8_t program[] = { 0x00, 0x11, 0x00 };
		Cpu* cpu = SetUpMockCpu(program, 3);

		write_register_pair(cpu, REGISTER_PAIR_HL, 0xc001);

		rl_hl(cpu);

		EXPECT_EQ(read_byte(cpu->bus, 0xc001), 0x22);
		EXPECT_EQ(get_flag(cpu, HALF_CARRY_FLAG_BIT), 0x0);
		EXPECT_EQ(get_flag(cpu, SUBTRACTION_FLAG_BIT), 0x0);
		EXPECT_EQ(get_flag(cpu, CARRY_FLAG_BIT), 0x0);
		EXPECT_EQ(get_flag(cpu, ZERO_FLAG_BIT), 0x0);

		FreeMockCpu(cpu);
	}

	TEST(rotate_shift_instruction_tests, rrc_r) {
		Cpu* cpu = SetUpMockCpu(NULL, 0);

		cpu->registers[REGISTER_C] = 0x1;

		rrc_r(cpu, REGISTER_C);

		EXPECT_EQ(cpu->registers[REGISTER_C], 0x80);
		EXPECT_EQ(get_flag(cpu, HALF_CARRY_FLAG_BIT), 0x0);
		EXPECT_EQ(get_flag(cpu, SUBTRACTION_FLAG_BIT), 0x0);
		EXPECT_EQ(get_flag(cpu, CARRY_FLAG_BIT), 0x1);
		EXPECT_EQ(get_flag(cpu, ZERO_FLAG_BIT), 0x0);

		FreeMockCpu(cpu);
	}

	TEST(rotate_shift_instruction_tests, rrc_hl) {
		uint8_t program[] = { 0x00, 0x00, 0x00 };
		Cpu* cpu = SetUpMockCpu(program, 3);

		write_register_pair(cpu, REGISTER_PAIR_HL, 0xc001);

		rrc_hl(cpu);

		EXPECT_EQ(read_byte(cpu->bus, 0xc001), 0x0);
		EXPECT_EQ(get_flag(cpu, HALF_CARRY_FLAG_BIT), 0x0);
		EXPECT_EQ(get_flag(cpu, SUBTRACTION_FLAG_BIT), 0x0);
		EXPECT_EQ(get_flag(cpu, CARRY_FLAG_BIT), 0x0);
		EXPECT_EQ(get_flag(cpu, ZERO_FLAG_BIT), 0x1);

		FreeMockCpu(cpu);
	}

	TEST(rotate_shift_instruction_tests, rr_r) {
		Cpu* cpu = SetUpMockCpu(NULL, 0);

		cpu->registers[REGISTER_A] = 0x1;

		rr_r(cpu, REGISTER_A);

		EXPECT_EQ(cpu->registers[REGISTER_A], 0x0);
		EXPECT_EQ(get_flag(cpu, HALF_CARRY_FLAG_BIT), 0x0);
		EXPECT_EQ(get_flag(cpu, SUBTRACTION_FLAG_BIT), 0x0);
		EXPECT_EQ(get_flag(cpu, CARRY_FLAG_BIT), 0x1);
		EXPECT_EQ(get_flag(cpu, ZERO_FLAG_BIT), 0x1);

		FreeMockCpu(cpu);
	}

	TEST(rotate_shift_instruction_tests, rr_hl) {
		uint8_t program[] = { 0x00, 0x8a, 0x00 };
		Cpu* cpu = SetUpMockCpu(program, 3);

		write_register_pair(cpu, REGISTER_PAIR_HL, 0xc001);

		rr_hl(cpu);

		EXPECT_EQ(read_byte(cpu->bus, 0xc001), 0x45);
		EXPECT_EQ(get_flag(cpu, HALF_CARRY_FLAG_BIT), 0x0);
		EXPECT_EQ(get_flag(cpu, SUBTRACTION_FLAG_BIT), 0x0);
		EXPECT_EQ(get_flag(cpu, CARRY_FLAG_BIT), 0x0);
		EXPECT_EQ(get_flag(cpu, ZERO_FLAG_BIT), 0x0);

		FreeMockCpu(cpu);
	}

	TEST(rotate_shift_instruction_tests, sla_r) {
		Cpu* cpu = SetUpMockCpu(NULL, 0);

		cpu->registers[REGISTER_D] = 0x80;

		sla_r(cpu, REGISTER_D);

		EXPECT_EQ(cpu->registers[REGISTER_D], 0x0);
		EXPECT_EQ(get_flag(cpu, HALF_CARRY_FLAG_BIT), 0x0);
		EXPECT_EQ(get_flag(cpu, SUBTRACTION_FLAG_BIT), 0x0);
		EXPECT_EQ(get_flag(cpu, CARRY_FLAG_BIT), 0x1);
		EXPECT_EQ(get_flag(cpu, ZERO_FLAG_BIT), 0x1);

		FreeMockCpu(cpu);
	}

	TEST(rotate_shift_instruction_tests, sla_hl) {
		uint8_t program[] = { 0x00, 0xff, 0x00 };
		Cpu* cpu = SetUpMockCpu(program, 3);

		write_register_pair(cpu, REGISTER_PAIR_HL, 0xc001);

		sla_hl(cpu);

		EXPECT_EQ(read_byte(cpu->bus, 0xc001), 0xfe);
		EXPECT_EQ(get_flag(cpu, HALF_CARRY_FLAG_BIT), 0x0);
		EXPECT_EQ(get_flag(cpu, SUBTRACTION_FLAG_BIT), 0x0);
		EXPECT_EQ(get_flag(cpu, CARRY_FLAG_BIT), 0x1);
		EXPECT_EQ(get_flag(cpu, ZERO_FLAG_BIT), 0x0);

		FreeMockCpu(cpu);
	}

	TEST(rotate_shift_instruction_tests, sra_r) {
		Cpu* cpu = SetUpMockCpu(NULL, 0);

		cpu->registers[REGISTER_A] = 0x8a;

		sra_r(cpu, REGISTER_A);

		EXPECT_EQ(cpu->registers[REGISTER_A], 0xc5);
		EXPECT_EQ(get_flag(cpu, HALF_CARRY_FLAG_BIT), 0x0);
		EXPECT_EQ(get_flag(cpu, SUBTRACTION_FLAG_BIT), 0x0);
		EXPECT_EQ(get_flag(cpu, CARRY_FLAG_BIT), 0x0);
		EXPECT_EQ(get_flag(cpu, ZERO_FLAG_BIT), 0x0);

		FreeMockCpu(cpu);
	}

	TEST(rotate_shift_instruction_tests, sra_hl) {
		uint8_t program[] = { 0x00, 0x01, 0x00 };
		Cpu* cpu = SetUpMockCpu(program, 3);

		write_register_pair(cpu, REGISTER_PAIR_HL, 0xc001);

		sra_hl(cpu);

		EXPECT_EQ(read_byte(cpu->bus, 0xc001), 0x0);
		EXPECT_EQ(get_flag(cpu, HALF_CARRY_FLAG_BIT), 0x0);
		EXPECT_EQ(get_flag(cpu, SUBTRACTION_FLAG_BIT), 0x0);
		EXPECT_EQ(get_flag(cpu, CARRY_FLAG_BIT), 0x1);
		EXPECT_EQ(get_flag(cpu, ZERO_FLAG_BIT), 0x1);

		FreeMockCpu(cpu);
	}

	TEST(rotate_shift_instruction_tests, srl_r) {
		Cpu* cpu = SetUpMockCpu(NULL, 0);

		cpu->registers[REGISTER_A] = 0x01;

		srl_r(cpu, REGISTER_A);

		EXPECT_EQ(cpu->registers[REGISTER_A], 0x0);
		EXPECT_EQ(get_flag(cpu, HALF_CARRY_FLAG_BIT), 0x0);
		EXPECT_EQ(get_flag(cpu, SUBTRACTION_FLAG_BIT), 0x0);
		EXPECT_EQ(get_flag(cpu, CARRY_FLAG_BIT), 0x1);
		EXPECT_EQ(get_flag(cpu, ZERO_FLAG_BIT), 0x1);

		FreeMockCpu(cpu);
	}

	TEST(rotate_shift_instruction_tests, srl_hl) {
		uint8_t program[] = { 0x00, 0xff, 0x00 };
		Cpu* cpu = SetUpMockCpu(program, 3);

		write_register_pair(cpu, REGISTER_PAIR_HL, 0xc001);

		srl_hl(cpu);

		EXPECT_EQ(read_byte(cpu->bus, 0xc001), 0x7f);
		EXPECT_EQ(get_flag(cpu, HALF_CARRY_FLAG_BIT), 0x0);
		EXPECT_EQ(get_flag(cpu, SUBTRACTION_FLAG_BIT), 0x0);
		EXPECT_EQ(get_flag(cpu, CARRY_FLAG_BIT), 0x1);
		EXPECT_EQ(get_flag(cpu, ZERO_FLAG_BIT), 0x0);

		FreeMockCpu(cpu);
	}

	TEST(rotate_shift_instruction_tests, swap_r) {
		Cpu* cpu = SetUpMockCpu(NULL, 0);

		cpu->registers[REGISTER_A] = 0x0;

		swap_r(cpu, REGISTER_A);

		EXPECT_EQ(cpu->registers[REGISTER_A], 0x0);
		EXPECT_EQ(get_flag(cpu, HALF_CARRY_FLAG_BIT), 0x0);
		EXPECT_EQ(get_flag(cpu, SUBTRACTION_FLAG_BIT), 0x0);
		EXPECT_EQ(get_flag(cpu, CARRY_FLAG_BIT), 0x0);
		EXPECT_EQ(get_flag(cpu, ZERO_FLAG_BIT), 0x1);

		FreeMockCpu(cpu);
	}

	TEST(rotate_shift_instruction_tests, swap_hl) {
		uint8_t program[] = { 0x00, 0xf0, 0x00 };
		Cpu* cpu = SetUpMockCpu(program, 3);

		write_register_pair(cpu, REGISTER_PAIR_HL, 0xc001);

		swap_hl(cpu);

		EXPECT_EQ(read_byte(cpu->bus, 0xc001), 0x0f);
		EXPECT_EQ(get_flag(cpu, HALF_CARRY_FLAG_BIT), 0x0);
		EXPECT_EQ(get_flag(cpu, SUBTRACTION_FLAG_BIT), 0x0);
		EXPECT_EQ(get_flag(cpu, CARRY_FLAG_BIT), 0x0);
		EXPECT_EQ(get_flag(cpu, ZERO_FLAG_BIT), 0x0);

		FreeMockCpu(cpu);
	}
}