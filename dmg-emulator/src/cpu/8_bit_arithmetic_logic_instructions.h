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

int xor_a_r(Cpu* cpu, uint8_t r1);

int xor_a_hl(Cpu* cpu);

int xor_a_n(Cpu* cpu);