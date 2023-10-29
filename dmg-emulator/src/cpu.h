#pragma once

#include <stdint.h>
#include <stdbool.h>

#include "bus.h"

#define NUMBER_OF_GENERAL_REGISTERS 8

#define ZERO_FLAG_BIT        7
#define SUBTRACTION_FLAG_BIT 6
#define HALF_CARRY_FLAG_BIT  5
#define CARRY_FLAG_BIT       4

typedef enum {
	OPERAND_NONE,
	OPERAND_N8,
	OPERAND_N16,
	OPERAND_A8,
	OPERAND_A16,
	OPERAND_E8,
	OPERAND_A,
	OPERAND_B,
	OPERAND_C,
	OPERAND_D,
	OPERAND_E,
	OPERAND_H,
	OPERAND_L,
	OPERAND_BC,
	OPERAND_DE,
	OPERAND_HL,
	OPERAND_SP,
} Operand;

typedef struct {
	uint16_t pc;
	uint8_t registers[NUMBER_OF_GENERAL_REGISTERS];
	uint16_t sp;

	uint8_t instructionCycleCount;
	uint8_t elapsedInstructionCycles;
	uint16_t operandA;
	uint16_t operandB;
} CpuState;

typedef struct {
	void (*execute)(Bus* bus);
	uint8_t clockCycles;
	Operand operandA;
	Operand operandB;
} Instruction;

void initialiseCpuState(CpuState* cpuState);

void freeCpuState(CpuState* cpuState);

uint8_t fetch8(Bus* bus);

uint16_t fetch16(Bus* bus); //Little endian format

bool getFlag(CpuState* state, uint8_t flagBit);

void setFlag(CpuState* state, uint8_t flagBit, bool isSet);

void cpuCycle(Bus* bus);

void nop(Bus* bus);

void ld(Bus* bus);