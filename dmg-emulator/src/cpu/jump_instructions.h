#pragma once

#include "cpu.h"

typedef enum {
	CONDITION_NZ = 0,
	CONDITION_Z = 1,
	CONDITION_NC = 2,
	CONDITION_C = 3,
} Condition;

int jp_nn(Cpu* cpu);

int jp_cc_nn(Cpu* cpu, Condition cc); //TODO - remmeber cc is decoded by the middle three bits in the opcode

int jr_e(Cpu* cpu);

int jr_cc_e(Cpu* cpu, Condition cc);

int jp_hl(Cpu* cpu);