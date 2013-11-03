#ifndef ATOC_SIM
#define ATOC_SIM

#include "atoc.h"

// Display settings
void set_log(int val);
void set_quiet(int val);


// Simulates an atoc machine
void simulate(addr entry, int delay);

#endif
