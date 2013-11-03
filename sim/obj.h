#ifndef ATOC_OBJ
#define ATOC_OBJ

#include "atoc.h"

// Returns error string
const char *obj_error(int err);

// Loads an obj file and returns <0 on failure
int obj_load(char *filename);

#endif
