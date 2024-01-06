#pragma once

extern "C" {
	#include "../../../dmg-emulator/src/cpu/cpu.h"
}

Cpu* SetUpMockCpu(uint8_t* program, int programSize);

void FreeMockCpu(Cpu* cpu);