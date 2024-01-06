#pragma once

#include "cpu.h"

int ld_r_r(Cpu* cpu, uint8_t r1, uint8_t r2);

int ld_r_n(Cpu* cpu, uint8_t r1);

int ld_r_hl(Cpu* cpu, uint8_t r1);

int ld_hl_r(Cpu* cpu, uint8_t r1);

int ld_hl_n(Cpu* cpu);

int ld_a_bc(Cpu* cpu);

int ld_a_de(Cpu* cpu);

int ld_a_c(Cpu* cpu);

int ld_c_a(Cpu* cpu);

int ld_a_n(Cpu* cpu);

int ld_n_a(Cpu* cpu);

int ld_a_nn(Cpu* cpu);

int ld_nn_a(Cpu* cpu);

int ldi_a_hl(Cpu* cpu);

int ldd_a_hl(Cpu* cpu);

int ld_bc_a(Cpu* cpu);

int ld_de_a(Cpu* cpu);

int ldi_hl_a(Cpu* cpu);

int ldd_hl_a(Cpu* cpu);