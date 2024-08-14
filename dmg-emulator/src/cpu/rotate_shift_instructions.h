#pragma once

#include "cpu.h"

int rlca(Cpu* cpu);

int rla(Cpu* cpu);

int rrca(Cpu* cpu);

int rra(Cpu* cpu); //TODO - evaluate if i need these first 4? could just use the generic register versions

int rlc_r(Cpu* cpu, uint8_t r1);

int rlc_hl(Cpu* cpu);

int rl_r(Cpu* cpu, uint8_t r1);

int rl_hl(Cpu* cpu);

int rrc_r(Cpu* cpu, uint8_t r1);

int rrc_hl(Cpu* cpu);

int rr_r(Cpu* cpu, uint8_t r1);

int rr_hl(Cpu* cpu);