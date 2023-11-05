#pragma once

#include <stdint.h>

#define RAM_CAPACITY 8192

typedef struct { 
	uint8_t ram[RAM_CAPACITY];
} Bus;

void initialise_bus(Bus* bus);

void free_bus(Bus* bus);

uint8_t read_byte(Bus* bus, uint16_t address);

void write_byte(Bus* bus, uint16_t address, uint8_t data);

uint16_t read_word(Bus* bus, uint16_t address);

void write_word(Bus* bus, uint16_t address, uint16_t data);