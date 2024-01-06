#include "pch.h"

#include "mock_cpu.h"

extern "C" {
	#include "../../../dmg-emulator/src/cpu/cpu.h"
	#include "../../../dmg-emulator/src/cpu/8_bit_load_instructions.h"
}

TEST(eight_bit_load_instruction_tests, ld_r_r) {
	Cpu* cpu = SetUpMockCpu(NULL, 0);

	cpu->registers[REGISTER_A] = 5;
	cpu->registers[REGISTER_B] = 9;
	ld_r_r(cpu, REGISTER_A, REGISTER_B);

	EXPECT_EQ(cpu->registers[REGISTER_A], 9);
	EXPECT_EQ(cpu->registers[REGISTER_B], 9);

	FreeMockCpu(cpu);
}

TEST(eight_bit_load_instruction_tests, ld_r_n) {
	uint8_t program[] = { 0x43 };
	Cpu* cpu = SetUpMockCpu(program, 1);

	ld_r_n(cpu, REGISTER_A);

	EXPECT_EQ(cpu->registers[REGISTER_A], 0x43);

	FreeMockCpu(cpu);
}

TEST(eight_bit_load_instruction_tests, ld_r_hl) {
	uint8_t program[] = { 0x00, 0x00, 0x87 };
	Cpu* cpu = SetUpMockCpu(program, 3);

	write_register_pair(cpu, REGISTER_PAIR_HL, 0xc002);
	ld_r_hl(cpu, REGISTER_A);

	EXPECT_EQ(cpu->registers[REGISTER_A], 0x87);

	FreeMockCpu(cpu);
}

TEST(eight_bit_load_instruction_tests, ld_hl_r) {
	Cpu* cpu = SetUpMockCpu(NULL, 0);

	write_register_pair(cpu, REGISTER_PAIR_HL, 0xc002);
	cpu->registers[REGISTER_B] = 0x69;
	ld_hl_r(cpu, REGISTER_B);

	EXPECT_EQ(cpu->bus->ram[0x2], 0x69);

	FreeMockCpu(cpu);
}

TEST(eight_bit_load_instruction_tests, ld_hl_n) {
	uint8_t program[] = { 0x33 };
	Cpu* cpu = SetUpMockCpu(program, 1);

	write_register_pair(cpu, REGISTER_PAIR_HL, 0xc043);
	cpu->registers[REGISTER_B] = 0x69;
	ld_hl_n(cpu);

	EXPECT_EQ(cpu->bus->ram[0x43], 0x33);

	FreeMockCpu(cpu);
}

TEST(eight_bit_load_instruction_tests, ld_a_bc) {
	uint8_t program[] = { 0x0, 0x0, 0x0, 0x45 };
	Cpu* cpu = SetUpMockCpu(program, 4);

	write_register_pair(cpu, REGISTER_PAIR_BC, 0xc003);
	ld_a_bc(cpu);

	EXPECT_EQ(cpu->registers[REGISTER_A], 0x45);

	FreeMockCpu(cpu);
}

TEST(eight_bit_load_instruction_tests, ld_a_de) {
	uint8_t program[] = { 0x0, 0x0, 0x0, 0x98 };
	Cpu* cpu = SetUpMockCpu(program, 4);

	write_register_pair(cpu, REGISTER_PAIR_DE, 0xc003);
	ld_a_de(cpu);

	EXPECT_EQ(cpu->registers[REGISTER_A], 0x98);

	FreeMockCpu(cpu);
}

//TEST(eight_bit_load_instruction_tests, ld_a_c) {
//	Cpu* cpu = SetUpMockCpu(program, 4);
//
//	//TODO - Implement when port register, or mode register stuff is implemented
//
//	FreeMockCpu(cpu);
//}

//TEST(eight_bit_load_instruction_tests, ld_c_a) {
//	uint8_t program[] = { 0x0, 0x0, 0x0, 0x98 };
//	Cpu* cpu = SetUpMockCpu(program, 4);
//
//	//TODO - Implement when port register, or mode register stuff is implemented
//
//	EXPECT_EQ(cpu->registers[REGISTER_A], 0x98);
//
//	FreeMockCpu(cpu);
//}

//TEST(eight_bit_load_instruction_tests, ld_a_n) {
//	uint8_t program[] = { 0x0, 0x0, 0x0, 0x98 };
//	Cpu* cpu = SetUpMockCpu(program, 4);
//
//	//TODO - Implement when port register, or mode register stuff is implemented
//
//	EXPECT_EQ(cpu->registers[REGISTER_A], 0x98);
//
//	FreeMockCpu(cpu);
//}

//TEST(eight_bit_load_instruction_tests, ld_n_a) {
//	uint8_t program[] = { 0x0, 0x0, 0x0, 0x98 };
//	Cpu* cpu = SetUpMockCpu(program, 4);
//
//	//TODO - Implement when port register, or mode register stuff is implemented
//
//	EXPECT_EQ(cpu->registers[REGISTER_A], 0x98);
//
//	FreeMockCpu(cpu);
//}

TEST(eight_bit_load_instruction_tests, ld_a_nn) {
	uint8_t program[] = { 0x03, 0xc0, 0x0, 0x99 };
	Cpu* cpu = SetUpMockCpu(program, 4);

	ld_a_nn(cpu);

	EXPECT_EQ(cpu->registers[REGISTER_A], 0x99);

	FreeMockCpu(cpu);
}

TEST(eight_bit_load_instruction_tests, ld_nn_a) {
	uint8_t program[] = { 0x43, 0xc1 };
	Cpu* cpu = SetUpMockCpu(program, 2);

	cpu->registers[REGISTER_A] = 0xf7;
	ld_nn_a(cpu);

	EXPECT_EQ(cpu->bus->ram[0x143], 0xf7);

	FreeMockCpu(cpu);
}

TEST(eight_bit_load_instruction_tests, ldi_a_hl) {
	uint8_t program[] = { 0x0, 0x0, 0x0, 0x0, 0x80 };
	Cpu* cpu = SetUpMockCpu(program, 5);

	write_register_pair(cpu, REGISTER_PAIR_HL, 0xc004);
	ldi_a_hl(cpu);

	EXPECT_EQ(cpu->registers[REGISTER_A], 0x80);
	EXPECT_EQ(read_register_pair(cpu, REGISTER_PAIR_HL), 0xc005);

	FreeMockCpu(cpu);
}

TEST(eight_bit_load_instruction_tests, ldd_a_hl) {
	uint8_t program[] = { 0x0, 0x0, 0x0, 0x0, 0x88 };
	Cpu* cpu = SetUpMockCpu(program, 5);

	write_register_pair(cpu, REGISTER_PAIR_HL, 0xc004);
	ldd_a_hl(cpu);

	EXPECT_EQ(cpu->registers[REGISTER_A], 0x88);
	EXPECT_EQ(read_register_pair(cpu, REGISTER_PAIR_HL), 0xc003);

	FreeMockCpu(cpu);
}

TEST(eight_bit_load_instruction_tests, ld_bc_a) {
	Cpu* cpu = SetUpMockCpu(NULL, 0);

	cpu->registers[REGISTER_A] = 0x077;
	write_register_pair(cpu, REGISTER_PAIR_BC, 0xc006);
	ld_bc_a(cpu);

	EXPECT_EQ(cpu->bus->ram[0x6], 0x77);

	FreeMockCpu(cpu);
}

TEST(eight_bit_load_instruction_tests, ld_de_a) {
	Cpu* cpu = SetUpMockCpu(NULL, 0);

	cpu->registers[REGISTER_A] = 0x021;
	write_register_pair(cpu, REGISTER_PAIR_DE, 0xc079);
	ld_de_a(cpu);

	EXPECT_EQ(cpu->bus->ram[0x79], 0x21);

	FreeMockCpu(cpu);
}

//TEST(eight_bit_load_instruction_tests, ldi_hl_a) {
//	Cpu* cpu = SetUpMockCpu(NULL, 0);
//
//	//TODO - Implement when port register, or mode register stuff is implemented
//	ldi_hl_a(cpu);
//
//	EXPECT_EQ(cpu->bus->ram[0x79], 0x21);
//
//	FreeMockCpu(cpu);
//}
//
//TEST(eight_bit_load_instruction_tests, ldd_hl_a) {
//	Cpu* cpu = SetUpMockCpu(NULL, 0);
//
//	//TODO - Implement when port register, or mode register stuff is implemented
//	ldd_hl_a(cpu);
//
//	EXPECT_EQ(cpu->bus->ram[0x79], 0x21);
//
//	FreeMockCpu(cpu);
//}