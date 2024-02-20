#ifndef REGISTERS_H
#define REGISTERS_H

#include <stdint.h>

extern int get_numregisters (void);
extern void init_registers (void);
extern void set (int, int64_t);
extern int64_t get (int);

#endif