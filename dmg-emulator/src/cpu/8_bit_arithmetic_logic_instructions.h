#pragma once

#include "cpu.h"

int add_a_r(Cpu* cpu, uint8_t r1);

int add_a_n(Cpu* cpu);

int add_a_hl(Cpu* cpu);

int adc_a_r(Cpu* cpu, uint8_t r1);

int adc_a_n(Cpu* cpu);

int adc_a_hl(Cpu* cpu);

int sub_a_r(Cpu* cpu, uint8_t r1);

int sub_a_n(Cpu* cpu);

int sub_a_hl(Cpu* cpu);

int sbc_a_r(Cpu* cpu, uint8_t r1);

int sbc_a_n(Cpu* cpu);

int sbc_a_hl(Cpu* cpu);

int and_a_r(Cpu* cpu, uint8_t r1);

int and_a_hl(Cpu* cpu);

int and_a_n(Cpu* cpu);

int or_a_r(Cpu* cpu, uint8_t r1);

int or_a_hl(Cpu* cpu);

int or_a_n(Cpu* cpu);

int ld_hl_sp_dd(Cpu* cpu); //TODO - This is grouped with the load instructions in the manual. THe pan docs specifies them in arithmetic so I will too. Just a reminder to look back to ld when I get to this