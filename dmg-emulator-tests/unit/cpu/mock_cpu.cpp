#include "pch.h"

#include "mock_cpu.h"

Cpu* SetUpMockCpu() {
	Cpu* cpu = new Cpu();
	initialise_cpu(cpu);

	return cpu;
}

void FreeMockCpu(Cpu* cpu) {
	delete cpu;
}