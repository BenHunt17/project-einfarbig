#include <stdlib.h>

#include "cpu.h"

void initialiseCpuState(CpuState* cpuState) {
	cpuState->pc = 0x100;
	cpuState->sp = 0xfffe;
	cpuState->elapsedInstructionCycles = 0;
	cpuState->instructionCycleCount = 0;
}

void freeCpuState(CpuState* cpuState) {
	free(cpuState);
}

uint8_t fetch8(Bus* bus) {
	uint8_t byte = readByte(bus, bus->cpu->pc);
	bus->cpu->pc++;

	return byte;
}

uint16_t fetch16(Bus* bus) {
	uint8_t lowByte = fetch8(bus);
	uint8_t highByte = fetch8(bus);

	return (highByte << 8) | lowByte;
}

bool getFlag(CpuState* state, uint8_t flagBit) {
	return (state->registers[1] >> flagBit) & 0x1;
}

void setFlag(CpuState* state, uint8_t flagBit, bool isSet) {
	if (isSet) {
		state->registers[1] |= (0x1 << flagBit);
	}
	else {
		state->registers[1] &= ~(0x1 << flagBit);
	}
}

Instruction instructionSet[256] = {
	{ nop, 4, OPERAND_NONE, OPERAND_NONE }, { ld, 12, OPERAND_BC, OPERAND_N16 }
};

void cpuCycle(Bus* bus) {
	CpuState* cpuState = bus->cpu;

	if (cpuState->elapsedInstructionCycles == 0) {
		Instruction instruction = instructionSet[readByte(bus, cpuState->pc)];
		cpuState->pc++;

		cpuState->operandA = instruction.operandA;
		cpuState->operandB = instruction.operandB;
		instruction.execute(bus);

		cpuState->instructionCycleCount = instruction.clockCycles;
		cpuState->elapsedInstructionCycles++;
	}
	else {
		cpuState->elapsedInstructionCycles++;
		if (cpuState->elapsedInstructionCycles >= cpuState->instructionCycleCount) {
			cpuState->elapsedInstructionCycles = 0;
		}
	}
}

void nop(Bus* bus) {
	//Do nothing
}

void ld(Bus* bus) {
	//TODO - implement
}