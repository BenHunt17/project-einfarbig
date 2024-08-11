#pragma once

#include "cpu.h"

int add_hl_rr(Cpu* cpu, RegisterPair rp);

int add_sp_e(Cpu* cpu);

int inc_rr(Cpu* cpu, RegisterPair rp);

int dec_rr(Cpu* cpu, RegisterPair rp);