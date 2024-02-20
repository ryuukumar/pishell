
#include <parse.h>
#include <function.h>

char buffer_raw [BUFFER_SIZE] = {0};
char* buffer = buffer_raw;

bool cmpresult = false, fxn = false, skip = false;

void clrbuf() {
	for (int i=0; i<BUFFER_SIZE; i++) buffer[i] = 0;
}

int cmd() {
	clrbuf();

	if (!fxn) {
		printf (" > ");
		fgets (buffer, BUFFER_SIZE, stdin);
		return parse(buffer, cmpresult, fxn, skip);
	}

	else {
		do {
			printf (" + ");
			fgets (buffer, BUFFER_SIZE, stdin);
		} while (fxnadd (buffer));
		fxn = false;
		printf ("DEFINED FUNCTION WITH LENGTH %d\n", closefxn());
	}

	return 20;
	
}