#pragma once

#include <stdint.h>

#include "cpu.h"

#define RAM_CAPACITY 8192

typedef struct { 
	CpuState* cpu;
	uint8_t ram[RAM_CAPACITY];
} Bus;

void initialiseBus(Bus* bus);

uint8_t readByte(Bus* bus, uint16_t address);

void writeByte(Bus* bus, uint16_t address, uint8_t data);