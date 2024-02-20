#ifndef PARSE_H
#define PARSE_H

#include <stdio.h>

#include <registers.h>
#include <stoi64.h>
#include <version.h>

#define BUFFER_SIZE		100

extern int parse (char*, bool&, bool&, bool&);

#endif