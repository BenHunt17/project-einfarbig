#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "cpu/cpu.h"
#include "bus.h"
#include "debug/logger.h"

int main() {
	Bus bus = { 0 };
	initialise_bus(&bus);

	Cpu cpu = { 0 };
	initialise_cpu(&cpu, &bus);
	
	//TODO - come back to 02

	FILE* file;
	fopen_s(&file,  "src/test/roms/blargg_cpu_instructions/01.gb", "rb");
	if (file == NULL) {
		printf("File was not succesfully opened\n");
		return 1;
	}

	fseek(file, 0, SEEK_END);
	int fileSize = ftell(file);
	fseek(file, 0, SEEK_SET);

	if (cpu.bus == NULL) {
		printf("Bus was not succesfully initialised\n");
		return 1;
	}

	fread(cpu.bus->mock_memory_mapper, fileSize, 1, file);

	fclose(file);

	FILE* f;
	fopen_s(&f, "src/debug/logs/state.txt", "a+");
	if (file == NULL) {
		printf("File was not succesfully opened\n");
		return 1;
	}

	for (int i = 0; i < 2210640; i++) {
		log_cpu_state(&cpu, file);

		cpu_tick(&cpu);

		if (read_byte(cpu.bus, 0xff02) == 0x81) {
			printf("%c", read_byte(cpu.bus, 0xff01));
			write_byte(cpu.bus, 0xff02, 0x0);
		}
	}

	fclose(file);

	free_bus(&bus);
	free_cpu(&cpu);

	return 0;
}