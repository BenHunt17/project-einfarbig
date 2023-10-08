#include <stdint.h>

#define NUMBER_OF_GENERAL_REGISTERS 8

#define ZERO_FLAG_BIT        7
#define SUBTRACTION_FLAG_BIT 6
#define HALF_CARRY_FLAG_BIT  5
#define CARRY_FLAG_BIT       4

typedef struct {
	uint16_t pc;
	uint8_t registers[NUMBER_OF_GENERAL_REGISTERS];
	uint16_t sp;
} CpuState;

bool getFlag(CpuState* state, uint8_t flagBit);

void setFlag(CpuState* state, uint8_t flagBit, bool isSet);

void cpuCycle(CpuState* state);