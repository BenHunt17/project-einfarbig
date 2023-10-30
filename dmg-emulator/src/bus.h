#pragma once

#include <stdint.h>

#include "cpu.h"

#define RAM_CAPACITY 8192

typedef struct { 
	CpuState* cpu;
	uint8_t ram[RAM_CAPACITY];
} Bus;

void initialise_bus(Bus* bus);

uint8_t read_byte(Bus* bus, uint16_t address);

void write_byte(Bus* bus, uint16_t address, uint8_t data);