#include <stdlib.h>
#include <stdio.h>

#include "bus.h"

void initialise_bus(Bus* bus) {
	//TODO - review
}

void free_bus(Bus* bus) {
}

uint8_t read_byte(Bus* bus, uint16_t address) {
	if (address > 0xc000 && address <= 0xdfff) {
		uint16_t mapped_address = address - 0xc000;
		return bus->ram[mapped_address];
	}
	if (address == 0xff01 || address == 0xff02) {
		return bus->serial_data[(address & 0xf) - 1];
	}
	if (address == 0xff44) {
		return 0x90;
	}
	if (address == 0xffff) {
		return bus->interupt_enable_register;
	}
	return bus->mock_memory_mapper[address];
}

void write_byte(Bus* bus, uint16_t address, uint8_t data) {
	if (address < 0x8000) {
		//Block ROM writes
		return;
	}

	if (address > 0xc000 && address <= 0xdfff) {
		uint16_t mapped_address = address - 0xc000;
		bus->ram[mapped_address] = data;
	}
	else if (address == 0xff01 || address == 0xff02) {
		bus->serial_data[(address & 0xf) - 1] = data;
	}
	else if (address == 0xffff) {
		bus->interupt_enable_register = data;
	}
	else {
		bus->mock_memory_mapper[address] = data;
	}
}

uint16_t read_word(Bus* bus, uint16_t address) {
	uint8_t lo = read_byte(bus, address);
	uint8_t hi = read_byte(bus, address + 1);
	return (hi << 8) | lo;
}

void write_word(Bus* bus, uint16_t address, uint16_t data) {
	uint8_t lo = (uint8_t)(data & 0xff);
	uint8_t hi = (uint8_t)((data >> 8) & 0xff);
	write_byte(bus, address, lo);
	write_byte(bus, address + 1, hi);
}