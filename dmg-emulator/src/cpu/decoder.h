#pragma once

#include "Cpu.h"

int decode_execute(Cpu* cpu, uint8_t opcode);

int decode_execute_extended_set(Cpu* cpu, uint8_t opcode);