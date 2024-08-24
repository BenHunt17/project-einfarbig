#pragma once

#include "cpu.h"

int daa(Cpu* cpu);

int cpl(Cpu* cpu);

int nop();

int ccf(Cpu* cpu);

int scf(Cpu* cpu);

int di(Cpu* cpu);

int ei(Cpu* cpu);

int halt(Cpu* cpu);

int stop(Cpu* cpu);