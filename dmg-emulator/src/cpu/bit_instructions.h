#pragma once

#include "cpu.h"

int bit_b_r(Cpu* cpu, uint8_t bit, uint8_t r1);

int bit_b_hl(Cpu* cpu, uint8_t bit);

int set_b_r(Cpu* cpu, uint8_t bit, uint8_t r1);

int set_b_hl(Cpu* cpu, uint8_t bit);

int res_b_r(Cpu* cpu, uint8_t bit, uint8_t r1);

int res_b_hl(Cpu* cpu, uint8_t bit);