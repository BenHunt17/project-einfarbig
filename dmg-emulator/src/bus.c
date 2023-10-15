#include <stdlib.h>
#include <stdio.h>

#include "bus.h"

void initialiseBus(Bus* bus) {
	CpuState* cpuState = malloc(sizeof(CpuState));
	if (cpuState == NULL) {
		printf("Error: Could not allocate memory for the cpuState");
		exit(EXIT_FAILURE);
	}

	initialiseCpuState(cpuState);

	bus->cpu = cpuState;
}

void freeBus(Bus* bus) {
	freeCpuState(bus->cpu);
	free(bus);
}

uint8_t readByte(Bus* bus, uint16_t address) {

}

void writeByte(Bus* bus, uint16_t address, uint8_t data) {

}