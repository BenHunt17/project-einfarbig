#pragma once

#include "cpu.h"

int rlca(Cpu* cpu);

int rla(Cpu* cpu);

int rrca(Cpu* cpu);

int rra(Cpu* cpu);

int rlc_r(Cpu* cpu, uint8_t r1);

int rlc_hl(Cpu* cpu);

int rl_r(Cpu* cpu, uint8_t r1);

int rl_hl(Cpu* cpu);