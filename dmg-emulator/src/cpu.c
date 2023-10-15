#include <stdlib.h>

#include "cpu.h"

void initialiseCpuState(CpuState* cpuState) {
	cpuState->pc = 0x0;
	cpuState->sp = 0x0;
}

void freeCpuState(CpuState* cpuState) {
	free(cpuState);
}

void cpuCycle(CpuState* state) {
	//TODO - fetch, execute
}