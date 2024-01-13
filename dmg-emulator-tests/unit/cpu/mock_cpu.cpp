#include "pch.h"

#include "mock_cpu.h"

Cpu* SetUpMockCpu(uint8_t* program, int programSize) {
	Cpu* cpu = new Cpu();
	Bus* bus = new Bus();

	if (programSize) {
		memcpy(bus->ram, program, programSize);
	}
	cpu->bus = bus;
	cpu->pc = 0xc000;
	cpu->sp = 0xce00;

	return cpu;
}

void FreeMockCpu(Cpu* cpu) {
	delete cpu->bus;
	delete cpu;
}