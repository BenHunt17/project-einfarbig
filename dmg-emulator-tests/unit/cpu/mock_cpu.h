#pragma once

extern "C" {
	#include "../../../dmg-emulator/src/cpu/cpu.h"
}

Cpu* SetUpMockCpu();

void FreeMockCpu(Cpu* cpu);