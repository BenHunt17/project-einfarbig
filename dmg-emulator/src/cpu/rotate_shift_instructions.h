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

int sla_r(Cpu* cpu, uint8_t r1);

int sla_hl(Cpu* cpu);

int sra_r(Cpu* cpu, uint8_t r1);

int sra_hl(Cpu* cpu);

int srl_r(Cpu* cpu, uint8_t);

int srl_hl(Cpu* cpu);

int swap_r(Cpu* cpu, uint8_t r1);

int swap_hl(Cpu* cpu);