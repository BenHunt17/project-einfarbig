#pragma once

#include "cpu.h"

int add_a_r(Cpu* cpu, uint8_t r1);

int ld_hl_sp_dd(Cpu* cpu); //TODO - This is grouped with the load instructions in the manual. THe pan docs specifies them in arithmetic so I will too. Just a reminder to look back to ld when I get to this