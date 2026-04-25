
#include <function.h>


extern int opcode (const char*);

typedef struct {
	char name_raw [FXN_NAME_SZ] = {0};
	char code_raw [FXN_TEXT_SZ] = {0};
	char* name = name_raw;
	char* code = code_raw;
	int insert = 0;
} Function;

// static function definitions
Function fxns [NUM_FXNS];
int fptr = 0;

bool fxnopen = false;

bool newfxn (const char* n) {
	if (strlen(n) == 0) return false;
	if (fptr == NUM_FXNS) return false;
	strncpy(fxns[fptr].name, n, FXN_NAME_SZ);
	for (int i=0; i<FXN_NAME_SZ; i++) {
		if (fxns[fptr].name_raw[i] == '\n') fxns[fptr].name_raw[i] = 0;
	}
	return true;
}

bool fxnadd (const char* n) {
	int opc = opcode(n);
	if (opc == 20) return false;
	if (opc == -1) {
		printf ("INVALID COMMAND\n");
		return true;
	}

	strncpy(fxns[fptr].code+fxns[fptr].insert, n, FXN_TEXT_SZ-fxns[fptr].insert);
	fxns[fptr].insert += strlen(n);
	return true;
}

int closefxn (void) {
	fptr++;
	return strlen(fxns[fptr-1].code);
}


int num_fxns (void) {
	return fptr;
}

const char* fname (int n) {
	return fxns[n].name;
}

const char* ftext (int n) {
	return fxns[n].code;
}

int fid (const char* fn) {
	for (int i=0; i<fptr; i++) {
		if (strcmp(fn, fxns[i].name) == 0) return i;
	}
	return -1;
}