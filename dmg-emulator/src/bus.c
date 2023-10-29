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
	if (address <= 0x3fff) {
		//TODO - implement cartidge
	}
	else if (address <= 0x7fff) {
		//TODO - implement cartidge
	}
	else if (address <= 0x9fff) {
		//TODO - implement video ram
	}
	else if (address <= 0xbfff) {
		uint16_t mappedAddress = address - 0xa000;
		return bus->ram[mappedAddress];
	}
	//TODO - implement rest of memory map
}

void writeByte(Bus* bus, uint16_t address, uint8_t data) {
	if (address <= 0x3fff) {
		//TODO - implement cartidge
	}
	else if (address <= 0x7fff) {
		//TODO - implement cartidge
	}
	else if (address <= 0x9fff) {
		//TODO - implement video ram
	}
	else if (address <= 0xbfff) {
		uint16_t mappedAddress = address - 0xa000;
		bus->ram[mappedAddress] = data;
	}
	//TODO - implement rest of memory map
}