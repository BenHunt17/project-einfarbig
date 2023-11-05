#include <stdlib.h>
#include <stdio.h>

#include "bus.h"

void initialise_bus(Bus* bus) {
	CpuState* cpu_state = malloc(sizeof(CpuState));
	if (cpu_state == NULL) {
		printf("Error: Could not allocate memory for the cpuState");
		exit(EXIT_FAILURE);
	}

	initialise_cpu_state(cpu_state);

	bus->cpu = cpu_state;
}

void free_bus(Bus* bus) {
	free_cpu_state(bus->cpu);
	free(bus);
}

uint8_t read_byte(Bus* bus, uint16_t address) {
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
		uint16_t mapped_address = address - 0xa000;
		return bus->ram[mapped_address];
	}
	//TODO - implement rest of memory map
}

void write_byte(Bus* bus, uint16_t address, uint8_t data) {
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
		uint16_t mapped_address = address - 0xa000;
		bus->ram[mapped_address] = data;
	}
	//TODO - implement rest of memory map
}

uint16_t read_word(Bus* bus, uint16_t address) {
	//TODO - implement when needed
	return 0;
}

void write_word(Bus* bus, uint16_t address, uint16_t data) {
	//TODO - implement when needed
}