#include <stdlib.h>

#include "cpu.h"
#include "decoder.h"
#include "../debug/logger.h"

void push_pc_on_stack(Cpu* cpu) {
	write_word(cpu->bus, cpu->sp - 2, cpu->pc);
	cpu->sp -= 2;
}

bool handle_interupts(Cpu* cpu) {
	if (!cpu->ime) {
		return false;
	}
		
	uint8_t interupt_flags = read_byte(cpu->bus, 0xff0f);
	uint8_t enabled_interupt_flags = read_byte(cpu->bus, 0xffff) & interupt_flags;

	if (enabled_interupt_flags == 0x0) {
		return false;
	}

	cpu->ime = false;

	if (enabled_interupt_flags & 0x1 == 0x1) {
		//VBlank
		push_pc_on_stack(cpu);
		cpu->pc = 0x40;
		write_byte(cpu->bus, 0xff0f, interupt_flags ^ 0x1);
	}
	else if ((enabled_interupt_flags >> 1) & 0x1 == 0x1) {
		//LCD
		push_pc_on_stack(cpu);
		cpu->pc = 0x48;
		write_byte(cpu->bus, 0xff0f, interupt_flags ^ 0x10);
	}
	else if ((enabled_interupt_flags >> 2) & 0x1 == 0x1) {
		//Timer
		push_pc_on_stack(cpu);
		cpu->pc = 0x50;
		write_byte(cpu->bus, 0xff0f, interupt_flags ^ 0x100);
	}
	else if ((enabled_interupt_flags >> 3) & 0x1 == 0x1) {
		//Serial
		push_pc_on_stack(cpu);
		cpu->pc = 0x58;
		write_byte(cpu->bus, 0xff0f, interupt_flags ^ 0x1000);
	}
	else if ((enabled_interupt_flags >> 4) & 0x1 == 0x1) {
		//Joypad
		push_pc_on_stack(cpu);
		cpu->pc = 0x60;
		write_byte(cpu->bus, 0xff0f, interupt_flags ^ 0x10000);
	}

	return true;
}

void initialise_cpu(Cpu* cpu, Bus* bus) {
	cpu->pc = 0x100;
	cpu->sp = 0xfffe;

	cpu->registers[REGISTER_A] = 0x01;
	cpu->registers[REGISTER_F] = 0xb0;
	cpu->registers[REGISTER_B] = 0x00;
	cpu->registers[REGISTER_C] = 0x13;
	cpu->registers[REGISTER_D] = 0x00;
	cpu->registers[REGISTER_E] = 0xd8;
	cpu->registers[REGISTER_H] = 0x01;
	cpu->registers[REGISTER_L] = 0x4d;

	cpu->ime = false;

	cpu->is_halted = false;
	cpu->is_stopped = false;

	cpu->bus = bus;
}

void free_cpu(Cpu* cpu) {
	//TODO - do i need these?
}

uint8_t fetch8(Cpu* cpu) {
	uint8_t byte = read_byte(cpu->bus, cpu->pc);
	cpu->pc++;
	return byte;
}

uint16_t fetch16(Cpu* cpu) {
	uint8_t low_byte = fetch8(cpu);
	uint8_t high_byte = fetch8(cpu);
	return (high_byte << 8) | low_byte;
}

uint16_t read_register_pair(Cpu* cpu, RegisterPair register_pair) {
	if (register_pair == REGISTER_PAIR_SP) {
		return cpu->sp;
	}
	return (cpu->registers[register_pair + 1] << 8) | (cpu->registers[register_pair]);
}

void write_register_pair(Cpu* cpu, RegisterPair register_pair, uint16_t data) {
	if (register_pair == REGISTER_PAIR_SP) {
		cpu->sp = data;
	}
	else {
		cpu->registers[register_pair] = (uint8_t)(data & 0xff);
		cpu->registers[register_pair + 1] = (uint8_t)((data >> 8) & 0xff);
	}
}

bool get_flag(Cpu* state, uint8_t flag_bit) {
	return (state->registers[REGISTER_F] >> flag_bit) & 0x1;
}

void set_flag(Cpu* state, uint8_t flag_bit, bool is_set) {
	if (is_set) {
		state->registers[REGISTER_F] |= (0x1 << flag_bit);
	}
	else {
		state->registers[REGISTER_F] &= ~(0x1 << flag_bit);
	}
}

bool condition_matches(Cpu* cpu, Condition cc) {
	return
		(cc == CONDITION_NZ && get_flag(cpu, ZERO_FLAG_BIT) == 0x0) ||
		(cc == CONDITION_Z && get_flag(cpu, ZERO_FLAG_BIT) == 0x1) ||
		(cc == CONDITION_NC && get_flag(cpu, CARRY_FLAG_BIT) == 0x0) ||
		(cc == CONDITION_C && get_flag(cpu, CARRY_FLAG_BIT) == 0x1);
}

int cpu_tick(Cpu* cpu) {
	log_cpu_state(cpu);

	int cycles = 0;

	//TODO - set ime if next_ime is set? before or after interupts?

	if (handle_interupts(cpu)) {
		cycles += 20;
	}

	uint8_t opcode = fetch8(cpu);

	if (opcode == 0xcb) {
		opcode = fetch8(cpu);
		cycles += decode_execute_extended_set(cpu, opcode);
	}
	else {
		cycles += decode_execute(cpu, opcode);
	}

	return cycles;
}