#pragma once

#include "cpu.h"

int call_nn(Cpu* cpu);

int call_cc_nn(Cpu* cpu, Condition cc);

int ret(Cpu* cpu);

int reti(Cpu* cpu);

int ret_cc(Cpu* cpu, Condition cc);

int rst_t(Cpu* cpu, uint8_t t);