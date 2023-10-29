#pragma once

#include <stdint.h>
#include <stdbool.h>

#include "bus.h"

#define NUMBER_OF_GENERAL_REGISTERS 8

#define ZERO_FLAG_BIT        7
#define SUBTRACTION_FLAG_BIT 6
#define HALF_CARRY_FLAG_BIT  5
#define CARRY_FLAG_BIT       4

typedef struct {
	uint16_t pc;
	uint8_t registers[NUMBER_OF_GENERAL_REGISTERS];
	uint16_t sp;

	uint8_t instructionCycleCount;
	uint8_t elapsedInstructionCycles;
} CpuState;

typedef struct {
	void (*function)(Bus* bus);
	uint8_t clockCycles;
	void (*getOperands)(Bus* bus);
} Instruction;

void initialiseCpuState(CpuState* cpuState);

void freeCpuState(CpuState* cpuState);

bool getFlag(CpuState* state, uint8_t flagBit);

void setFlag(CpuState* state, uint8_t flagBit, bool isSet);

void cpuCycle(Bus* bus);

void ld(Bus* bus);