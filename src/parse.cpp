

#include <parse.h>
#include <function.h>

#define INPBUF_SZ	25

char inputbuffer_raw [INPBUF_SZ] = {0};
char* inputbuffer = &inputbuffer_raw[0];


extern void clrbuf();
extern int opcode (const char*);
extern void helpmsg (int, int);
extern bool parsecmp (const char*, int&);

const char* parse_next (const char* buf, int& i) {
	char stor [BUFFER_SIZE] = {0};
	int ptr = 0;

	for (; i<BUFFER_SIZE; i++) {
		if (buf[i] == 0 || !(buf[i] == ' ' || buf[i] == '\n' || buf[i] == '\t')) break;
	}

	for (; i<BUFFER_SIZE; i++) {
		if (buf[i] == 0 || buf[i] == ' ' || buf[i] == '\n' || buf[i] == '\t') break;
		stor[ptr++] = buf[i];
	}

	const char* ret = stor;
	return ret;
}

bool p2v (const char* buffer, int& a, int& b, int& i, int& error) {
	error = 0;
	a = stoi64(parse_next(buffer, i), &error);
	if (error || a >= get_numregisters() || a < 0) {
		printf ("INVALID REGISTER, ERROR CODE %d\n", error);
		return false;
	}
	b = stoi64(parse_next(buffer, i), &error);
	if (error || b >= get_numregisters() || b < 0) {
		printf ("INVALID REGISTER, ERROR CODE %d\n", error);
		return false;
	}
	return true;
}

bool p3v (const char* buffer, int& a, int& b, int& c, int& i, int& error) {
	error = 0;
	if (!p2v(buffer, a, b, i, error)) return false;
	c = stoi64(parse_next(buffer, i), &error);
	if (error || c >= get_numregisters() || c < 0) {
		printf ("INVALID REGISTER, ERROR CODE %d\n", error);
		return false;
	}
	return true;
}

void printfxns (void) {
	int nf = num_fxns();
	if (nf == 0) printf("NO FUNCTIONS DECLARED.\n");
	for (int i=0; i<nf; i++) {
		printf("%s:\n", fname(i));
		printf("%s", ftext(i));
		printf("\n");
	}
}

bool runfxn (char* buffer, const char* fn) {
	int fidx = fid(fn), fctr = 0, bufctr = 0;
	bool cmpresult = false, fxn = false, skip = false;
	if (fidx == -1) {
		printf ("COULD NOT FIND FUNCTION BY NAME \"%s\".\n", fn);
		return false;
	}

	const char* text = ftext(fidx);
	// printf ("Found function %s with text:\n%s\n", fn, text);

	do {
		clrbuf(); bufctr = 0;
		while (text[fctr] != 0 && text[fctr] != '\n')
			buffer[bufctr++] = text[fctr++];
		buffer[bufctr++] = '\n';
		// printf (" + %s\n", buffer);
		parse (buffer, cmpresult, fxn, skip);
		while (text[fctr] != 0 && text[fctr] == '\n') fctr++;
	} while (text[fctr] != 0);

	return true;
}

int parse (char* buffer, bool& cmpresult, bool& fxn, bool& skip) {
	if (skip) {
		skip = false;
		return 24;
	}

	int opc = opcode(buffer),
		i = 0, error = 0, r = 0,
		a = 0, b = 0, c = 0;
	int64_t v = 0;

	switch (opc) {
		case -1: printf("INVALID COMMAND: %s", buffer); break;
		case 0: break;
		case 1: printf("%s", &buffer[5]); break;
		case 2: helpmsg(VERSION_MAJOR, VERSION_MINOR); break;
		case 3:
			i = 5, error = 0;
			r = stoi64(parse_next(buffer, i), &error);
			if (error || r >= get_numregisters() || r < 0) {
				printf ("INVALID REGISTER, ERROR CODE %d\n", error); break;
			}
			i = 0;
			fgets (inputbuffer, BUFFER_SIZE, stdin);
			v = stoi64(parse_next(inputbuffer, i), &error);
			if (error) {
				printf ("INVALID VALUE, ERROR CODE %d\n", error); break;
			}
			set (r, v);
			break;
		case 4:
			printf("AVAILABLE REGISTERS: %d\nAVAILABLE FUNCTIONS: %d\nMAX FUNCTION NAME LENGTH: %d\nMAX FUNCTION TEXT LENGTH: %d\n",
				get_numregisters(), NUM_FXNS, FXN_NAME_SZ, FXN_TEXT_SZ);
			break;

		case 5:
			i = 4, error = 0;
			r = stoi64(parse_next(buffer, i), &error);
			if (error || r >= get_numregisters() || r < 0) {
				printf ("INVALID REGISTER, ERROR CODE %d\n", error); break;
			}
			v = stoi64(parse_next(buffer, i), &error);
			if (error) {
				printf ("INVALID VALUE, ERROR CODE %d\n", error); break;
			}
			set (r, v);
			break;

		case 6:
			i = 4, error = 0;
			r = stoi64(parse_next(buffer, i), &error);
			if (error || r >= get_numregisters() || r < 0) {
				printf ("INVALID REGISTER, ERROR CODE %d\n", error); break;
			}
			printf ("%ld\n", get(r));
			break;
		
		case 7: for (int j=0; j<get_numregisters(); j++) set (j, 0); break;
		case 8:
			for (int j=0; j<get_numregisters(); j++)
				printf("R%d\t%ld\n", j, get(j));
			break;
		
		case 9:
			i = 4;
			if (!p3v(buffer, a, b, c, i, error)) break;
			set(c, get(a) & get(b));
			break;
		
		case 10:
			i = 3;
			if (!p3v(buffer, a, b, c, i, error)) break;
			set(c, get(a) | get(b));
			break;
		
		case 11:
			i = 4;
			if (!p3v(buffer, a, b, c, i, error)) break;
			set(c, get(a) + get(b));
			break;
		
		case 12:
			i = 4;
			if (!p3v(buffer, a, b, c, i, error)) break;
			set(c, get(a) - get(b));
			break;
		
		case 13:
			i = 4;
			if (!p3v(buffer, a, b, c, i, error)) break;
			set(c, get(a) * get(b));
			break;
		
		case 14:
			i = 4;
			if (!p3v(buffer, a, b, c, i, error)) break;
			if (get(b) == 0) {
				printf ("DIVISION BY ZERO!\n");
				break;
			}
			set(c, get(a) / get(b));
			break;
		
		case 15:
			i = 4;
			if (!p2v(buffer, a, b, i, error)) break;
			set(b, ~get(a));
			break;
		
		case 16:
			i = 5;
			if (!p2v(buffer, a, b, i, error)) break;
			set(b, !get(a));
			break;
		
		case 17:
			r = parsecmp(buffer, error);
			if (error) {
				printf("ERROR CODE %d\n", error); break;
			} 
			if (r) printf("TRUE\n");
			else printf("FALSE\n");
			cmpresult = r;
			break;
		
		case 18:
			i = 5, error = 0;
			a = stoi64(parse_next(buffer, i), &error);
			if (error || a >= get_numregisters() || a < 0) {
				printf ("INVALID REGISTER, ERROR CODE %d\n", error); break;
			}
			set(a, cmpresult);
			break;

		case 19:
			error = 0, i = 6;
			if (newfxn (parse_next(buffer, i))) fxn = true;
			else printf("ERROR WHILE DEFINING FUNCTION.\n");
			break;
		
		case 20:
			printf ("REQUIRES A PRIOR DEFFXN INSTRUCTION.\n");
			break;

		case 21:
			i = 4;
			if (cmpresult) (void)runfxn(buffer, parse_next(buffer, i));
			break;

		case 22:
			i = 4;
			(void)runfxn(buffer, parse_next(buffer, i));
			break;
		
		case 23:
			if (cmpresult) skip = true;
			break;
		
		case 24:
			printfxns();
			break;


	}

	return opc;
}