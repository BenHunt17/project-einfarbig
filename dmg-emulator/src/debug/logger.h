#pragma once

#include <stdlib.h>

#include <stdio.h>

#include "../cpu/cpu.h"

#define DEBUG_ENABLED 0

void log_cpu_state(Cpu* cpu, FILE* file);