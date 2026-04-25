
#include <registers.h>

#define NUM_REGISTERS	32

int64_t registers[NUM_REGISTERS] = {0};

int get_numregisters (void) {
	return NUM_REGISTERS;
}

void init_registers (void) {
	for (int i=0; i<NUM_REGISTERS; i++) {
		registers[i] = 0;
	}
}

void set (int reg, int64_t num) {
	registers[reg] = num;
}

int64_t get (int reg) {
	return registers[reg];
}