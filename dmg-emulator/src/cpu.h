#pragma once

#include <stdint.h>
#include <stdbool.h>

#include "bus.h"

#define NUMBER_OF_GENERAL_REGISTERS 8

#define REGISTER_A 0
#define REGISTER_F 1
#define REGISTER_B 2
#define REGISTER_C 3
#define REGISTER_D 4
#define REGISTER_E 5
#define REGISTER_H 6
#define REGISTER_L 7

#define ZERO_FLAG_BIT        7
#define SUBTRACTION_FLAG_BIT 6
#define HALF_CARRY_FLAG_BIT  5
#define CARRY_FLAG_BIT       4

typedef enum {
	REGISTER_PAIR_AF = REGISTER_A,
	REGISTER_PAIR_BC = REGISTER_B,
	REGISTER_PAIR_DE = REGISTER_D,
	REGISTER_PAIR_HL = REGISTER_H
} RegisterPair;

typedef struct {
	uint16_t pc;
	uint8_t registers[NUMBER_OF_GENERAL_REGISTERS];
	uint16_t sp;

	Bus* bus;

	uint8_t instructionCycleCount;
	uint8_t elapsedInstructionCycles;
} Cpu;

void initialise_cpu(Cpu* cpu);

void free_cpu(Cpu* cpu);

uint8_t fetch8(Cpu* cpu);

uint16_t fetch16(Cpu* bcpuus); //Little endian format

uint16_t read_register_pair(Cpu* cpu, RegisterPair register_pair);

void write_register_pair(Cpu* cpu, RegisterPair register_pair, uint16_t data);

bool get_flag(Cpu* cpu, uint8_t flag_bit);

void set_flag(Cpu* cpu, uint8_t flag_bit, bool is_set);

void cpu_cycle(Cpu* cpu);

int nop();

int ld_r_r(Cpu* cpu_state, uint8_t r1, uint8_t r2);

int ld_r_n(Cpu* cpu_state, uint8_t r1);

int ld_r_hl(Cpu* cpu_state, uint8_t r1);

int ld_hl_r(Cpu* cpu_state, uint8_t r1);

int ld_hl_n(Cpu* cpu);