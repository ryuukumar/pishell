

#include <string.h>
#include <stdint.h>

#include <registers.h>
#include <stoi64.h>

bool parsecmp(const char* buffer, int& error) {
	error = 0;

	buffer += 3;
	while (*buffer == ' ') buffer++;

	char numbuf [20] = {0}; int ptr = 0;
	const char* nb = numbuf;

	while (*buffer != ' ' && *buffer != ' ' && *buffer != '\n' && *buffer != '\t' && *buffer != 0) {
		numbuf[ptr++] = *buffer;
		buffer++;
	}

	int64_t regA = stoi64(nb, &error);
	if (error) return false;

	// while (*buffer && *buffer != ' ') buffer++;
	while (*buffer == ' ') buffer++;

	const char* opStart = buffer;
	while (*buffer && *buffer != ' ' && *buffer != '\n' && *buffer != '\t' && *buffer != 0) buffer++;
	int opLength = buffer - opStart;
	if (opLength < 1 || opLength > 2) {
		error = 5;
		return false;
	}

	while (*buffer == ' ') buffer++;
	for (int x=0; x<20; x++) numbuf[x] = 0;
	ptr = 0;

	while (*buffer != ' ' && *buffer != '\n' && *buffer != '\t' && *buffer != 0) {
		numbuf[ptr++] = *buffer;
		buffer++;
	}

	int64_t regB = stoi64(nb, &error);
	if (error) return false;

	int64_t valueA = get(regA);
	int64_t valueB = get(regB);

	if (opLength == 1) {
		switch (opStart[0]) {
			case '=': return valueA == valueB;
			case '>': return valueA > valueB;
			case '<': return valueA < valueB;
			default: error = 4; return false;
		}
	} else {
		if (strncmp(opStart, "<=", 2) == 0) return valueA <= valueB;
		if (strncmp(opStart, ">=", 2) == 0) return valueA >= valueB;
		if (strncmp(opStart, "!=", 2) == 0) return valueA != valueB;
		error = 4;
		return false;
	}
}