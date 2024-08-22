#include "pch.h"

#include "mock_cpu.h"

extern "C" {
#include "../../../dmg-emulator/src/cpu/cpu.h"
#include "../../../dmg-emulator/src/cpu/call_return_instructions.h"
}

TEST(call_return_instruction_tests, call_nn) {
	uint8_t program[8192] = { 0 };
	program[1] = 0x34;
	program[2] = 0x12;

	Cpu* cpu = SetUpMockCpu(program, 8192);

	cpu->pc = 0xc001;
	cpu->sp = 0xc0fe;

	call_nn(cpu);

	EXPECT_EQ(cpu->pc, 0x1234);
	EXPECT_EQ(cpu->sp, 0xc0fc);
	EXPECT_EQ(read_byte(cpu->bus, 0xc0fd), 0xc0);
	EXPECT_EQ(read_byte(cpu->bus, 0xc0fc), 0x03);
}

TEST(call_return_instruction_tests, call_cc_nn) {
	uint8_t program[8192] = { 0 };
	program[3] = 0x34;
	program[4] = 0x12;

	Cpu* cpu = SetUpMockCpu(program, 8192);

	cpu->pc = 0xc001;
	cpu->sp = 0xc0fe;

	set_flag(cpu, ZERO_FLAG_BIT, 0x1);

	call_cc_nn(cpu, CONDITION_NZ);

	EXPECT_EQ(cpu->pc, 0xc003);

	call_cc_nn(cpu, CONDITION_Z);

	EXPECT_EQ(cpu->pc, 0x1234);
	EXPECT_EQ(cpu->sp, 0xc0fc);
	EXPECT_EQ(read_byte(cpu->bus, 0xc0fd), 0xc0);
	EXPECT_EQ(read_byte(cpu->bus, 0xc0fc), 0x05);
}

TEST(call_return_instruction_tests, ret) {
	uint8_t program[8192] = { 0 };
	program[1] = 0x34;
	program[2] = 0x12;

	Cpu* cpu = SetUpMockCpu(program, 8192);

	cpu->pc = 0xc001;
	cpu->sp = 0xc0fe;

	call_nn(cpu);

	EXPECT_EQ(cpu->pc, 0x1234);
	EXPECT_EQ(cpu->sp, 0xc0fc);

	ret(cpu);

	EXPECT_EQ(cpu->pc, 0xc003);
	EXPECT_EQ(cpu->sp, 0xc0fe);
}

TEST(call_return_instruction_tests, reti) {
	uint8_t program[8192] = { 0 };
	program[1] = 0x34;
	program[2] = 0x12;

	Cpu* cpu = SetUpMockCpu(program, 8192);

	cpu->pc = 0xc001;
	cpu->sp = 0xc0fe;

	call_nn(cpu); //Assume this was an interup pushing the current pc because I haven't implemented yet and probably won't come back to this when I do

	EXPECT_EQ(cpu->pc, 0x1234);
	EXPECT_EQ(cpu->sp, 0xc0fc);

	reti(cpu);

	EXPECT_EQ(cpu->pc, 0xc003);
	EXPECT_EQ(cpu->sp, 0xc0fe);
	EXPECT_EQ(cpu->ime, true);
}

TEST(call_return_instruction_tests, ret_cc) {
	uint8_t program[8192] = { 0 };
	program[1] = 0x34;
	program[2] = 0x12;

	Cpu* cpu = SetUpMockCpu(program, 8192);

	cpu->pc = 0xc001;
	cpu->sp = 0xc0fe;

	set_flag(cpu, ZERO_FLAG_BIT, 0x1);

	call_nn(cpu);

	EXPECT_EQ(cpu->pc, 0x1234);

	ret_cc(cpu, CONDITION_NZ);

	EXPECT_EQ(cpu->pc, 0x1236);

	ret_cc(cpu, CONDITION_Z);

	EXPECT_EQ(cpu->pc, 0xc003);
}

TEST(call_return_instruction_tests, rst_t) {
	uint8_t program[8192] = { 0 };

	Cpu* cpu = SetUpMockCpu(program, 8192);

	cpu->pc = 0xc001;
	cpu->sp = 0xc0fe;

	rst_t(cpu, 0x5);

	EXPECT_EQ(cpu->pc, 0x0028);
	EXPECT_EQ(cpu->sp, 0xc0fc);
	EXPECT_EQ(read_byte(cpu->bus, 0xc0fd), 0xc0);
	EXPECT_EQ(read_byte(cpu->bus, 0xc0fc), 0x01);
}