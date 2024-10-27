#include "logger.h"

#include "../cpu/cpu.h"

#include <stdio.h>

void log_cpu_state(Cpu* cpu) {
	if (DEBUG_ENABLED) {
		printf("PC: %d, SP: %d\n \
				A: %d, F: %d, B: %d, C: %d, D: %d, E: %d, H: %d, L: %d\n \
				ime: %d \
				\n\n",
			cpu->pc, cpu->sp,
			cpu->registers[REGISTER_A], cpu->registers[REGISTER_F], cpu->registers[REGISTER_B], cpu->registers[REGISTER_C],
			cpu->registers[REGISTER_D], cpu->registers[REGISTER_E], cpu->registers[REGISTER_H], cpu->registers[REGISTER_L],
			cpu->ime);
	}
}