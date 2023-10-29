#include <stdlib.h>

#include "cpu.h"

Instruction instructionSet[256] = {
	{ ld, 4, NULL }
};

void initialiseCpuState(CpuState* cpuState) {
	cpuState->pc = 0x100;
	cpuState->sp = 0xfffe;
	cpuState->elapsedInstructionCycles = 0;
	cpuState->instructionCycleCount = 0;
}

void freeCpuState(CpuState* cpuState) {
	free(cpuState);
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

void cpuCycle(Bus* bus) {
	CpuState* cpuState = bus->cpu;

	if (cpuState->elapsedInstructionCycles == 0) {
		Instruction instruction = instructionSet[readByte(bus, cpuState->pc)];
		cpuState->pc++;

		instruction.getOperands(bus);
		instruction.function(bus);

		cpuState->instructionCycleCount = instruction.clockCycles;
	}
	else {
		cpuState->elapsedInstructionCycles++;
		if (cpuState->elapsedInstructionCycles >= cpuState->instructionCycleCount) {
			cpuState->elapsedInstructionCycles = 0;
		}
	}
}

