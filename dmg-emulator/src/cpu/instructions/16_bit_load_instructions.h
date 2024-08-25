#pragma once

#include "../cpu.h"

int ld_rr_nn(Cpu* cpu, RegisterPair rp);

int ld_sp_hl(Cpu* cpu);

int push_rr(Cpu* cpu, RegisterPair rp);

int pop_rr(Cpu* cpu, RegisterPair rp);

int ld_nn_sp(Cpu* cpu);

int ld_hl_sp_e(Cpu* cpu);