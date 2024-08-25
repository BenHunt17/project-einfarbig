#include "decoder.h"

int decode_execute(Cpu* cpu) {
	//0xcb Indicates that a second set of instructions comprising of shift, rotate and bit instructions should be decoded.
	//The cycles taken to fetch the next opcode are accounted for in the resulting instruction's cycles
	//TODO - when i get to interupts, reread this: https://www.reddit.com/r/EmuDev/comments/7qf352/game_boy_is_0xcb_a_separate_instruction_are/
}