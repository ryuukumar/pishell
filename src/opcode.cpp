#include <stdio.h>
#include <string.h>

#define OPS_SZ		25

const char* ops [25] = {
	"EXIT", "ECHO", "HELP", "INPUT",

	"MEM", "SET", "VAL", "DROP", "SHOW",

	"AND", "OR", "ADD", "SUB", "MUL", "DIV", "INV", "BLINV", "CMP", "STCMP",

	"DEFFXN", "ENDFXN", "JMPT", "JMP", "SNIT", "LFXN"
};

int opcode (const char* buffer) {
	char cmd [10] = {0};
	for (int i=0; i<10; i++) {
		if (buffer[i] >= 'A' && buffer[i] <= 'Z')
			cmd[i] = buffer[i];
		else if (buffer[i] >= 'a' && buffer[i] <= 'z')
			cmd[i] = buffer[i] - 'a' + 'A';
		else break;
	}
	const char* c = cmd;

	for (int i=0; i<OPS_SZ; i++) {
		if (strcmp(c, ops[i]) == 0) return i;
	}

	return -1;
}