#include <stdlib.h>
#include <stdio.h>

#include "bus.h"

void initialise_bus(Bus* bus) {
	//TODO - review
}

void free_bus(Bus* bus) {
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
		//TODO - impelement external ram
	}
	else if (address <= 0xdfff) {
		uint16_t mapped_address = address - 0xc000;
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
		//TODO - impelement external ram
	}
	else if (address <= 0xdfff) {
		uint16_t mapped_address = address - 0xc000;
		bus->ram[mapped_address] = data;
	}
	//TODO - implement rest of memory map
}

uint16_t read_word(Bus* bus, uint16_t address) {
	//TODO - memory map logic. for now assume address is in main memory
	uint16_t tempMappedAddress = address - 0xc000;

	uint8_t lo = bus->ram[tempMappedAddress];
	uint8_t hi = bus->ram[tempMappedAddress + 1];
	return (hi << 8) | lo;
}

void write_word(Bus* bus, uint16_t address, uint16_t data) {
	//TODO - memory map logic. for now assume address is in main memory
	uint16_t tempMappedAddress = address - 0xc000;

	uint8_t lo = (uint8_t)(data & 0xff);
	uint8_t hi = (uint8_t)((data >> 8) & 0xff);
	bus->ram[tempMappedAddress] = lo;
	bus->ram[tempMappedAddress + 1] = hi;
}