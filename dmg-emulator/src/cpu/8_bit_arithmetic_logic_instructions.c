#include "8_bit_arithmetic_logic_instructions.h"

int add_a_r(Cpu* cpu, uint8_t r1) {
	uint8_t a = cpu->registers[REGISTER_A];
    uint8_t r = cpu->registers[r1];

	uint8_t result = a + r;
	cpu->registers[REGISTER_A] = result;

	set_flag(cpu, ZERO_FLAG_BIT, result == 0);

	//Handy trick for determining half carry bit which I read from here: https://gist.github.com/meganesu/9e228b6b587decc783aa9be34ae27841#file-half-carry-flag-md
	bool half_carry_bit = (((a & 0xf) + (r & 0xf)) & 0x10) == 0x10;
	set_flag(cpu, HALF_CARRY_FLAG_BIT, half_carry_bit);

	set_flag(cpu, SUBTRACTION_FLAG_BIT, false);

	set_flag(cpu, CARRY_FLAG_BIT, (a + r) > 0xff);

	return 4;
}