#ifndef FUNCTION_H
#define FUNCTION_H

#include <string.h>

#include <parse.h>

#define FXN_NAME_SZ	32
#define FXN_TEXT_SZ 1024
#define NUM_FXNS	16

extern bool newfxn (const char*);
extern bool fxnadd (const char*);
extern int closefxn (void);

extern int num_fxns (void);
extern const char* fname (int);
extern const char* ftext (int);

extern int fid (const char*);

#endif
