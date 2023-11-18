#pragma once

#include "cpu.h"

int ld_rr_nn(Cpu* cpu, uint8_t rp);

int ld_sp_hl(Cpu* cpu);

int push_rr(Cpu* cpu, uint8_t rp);

int pop_rr(Cpu* cpu, uint8_t rp);

int ld_nn_sp(Cpu* cpu);