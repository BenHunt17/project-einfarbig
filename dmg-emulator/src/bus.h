#pragma once

#include <stdint.h>

#define RAM_CAPACITY 8192

#define IO_REGISTERS_SIZE 127

typedef struct { 
	uint8_t mock_memory_mapper[0xffff]; //TODO - remove when I properly implement the memory mapper

	uint8_t ram[RAM_CAPACITY];

	uint8_t interupt_enable_register;

	uint8_t serial_data[2];
} Bus;

void initialise_bus(Bus* bus);

void free_bus(Bus* bus);

uint8_t read_byte(Bus* bus, uint16_t address);

void write_byte(Bus* bus, uint16_t address, uint8_t data);

uint16_t read_word(Bus* bus, uint16_t address);

void write_word(Bus* bus, uint16_t address, uint16_t data);