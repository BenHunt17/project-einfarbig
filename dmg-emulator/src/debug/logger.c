#include "logger.h"

#include "../cpu/cpu.h"

#include <stdio.h>

void log_cpu_state(Cpu* cpu, FILE* file) {
	if (DEBUG_ENABLED) {
		fprintf(file, "A:%04X F:%04X B:%04X C:%04X D:%X E:%04X H:%04X L:%04X SP:%04X PC:%04X\n",
			cpu->registers[REGISTER_A], cpu->registers[REGISTER_F], cpu->registers[REGISTER_B], cpu->registers[REGISTER_C],
			cpu->registers[REGISTER_D], cpu->registers[REGISTER_E], cpu->registers[REGISTER_H], cpu->registers[REGISTER_L],
			cpu->sp, cpu->pc);
	}
}