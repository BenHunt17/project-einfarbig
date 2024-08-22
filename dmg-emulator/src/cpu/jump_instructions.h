#pragma once

#include "cpu.h"

int jp_nn(Cpu* cpu);

int jp_cc_nn(Cpu* cpu, Condition cc); //TODO - remmeber cc is decoded by the middle three bits in the opcode

int jr_e(Cpu* cpu);

int jr_cc_e(Cpu* cpu, Condition cc);

int jp_hl(Cpu* cpu);