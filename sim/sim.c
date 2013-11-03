#include "sim.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>


static int log = 0;
static int quiet = 0;

void set_log(int val) {
    log = val;
}

void set_quiet(int val) {
    quiet = val;
}


void display(void) {
    if (quiet)
        return;

    printf("\rc[%1x] ir[%02x] r[%03x %03x %03x %03x]", 
           nz, ir, 
           reg[0], reg[1], reg[2], reg[3]);

    if (log)
        printf("\n");

    fflush(stdout);
}


void simulate(addr entry, int delay) {
    delay /= 2;

    reset(entry);
    display();
    usleep(delay);

    while (!halted()) {
        fetch();
        display();
        usleep(delay);

        exec();
        display();
        usleep(delay);
    }

    if (!quiet)
        printf("\nHalted\n");
}
