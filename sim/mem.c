#include "atoc.h"

#include <stdio.h>
#include <stdlib.h>


/* Accessable memory */

#define MAP_SIZE 0x20

byte mem[1 << ADDR_SIZE] = {0x00};


/* Memory mapped functions */

byte get_invalid(addr loc) {
    fprintf(stderr, "\nInvalid memory read at 0x%x\n", loc);
    exit(1);
}

void set_invalid(addr loc, byte val) {
    fprintf(stderr, "\nInvalid memory write at 0x%x\n", loc);
    exit(1);
}


byte get_stdin(addr loc) {
    return getc(stdin);
}

void set_stdout(addr loc, byte val) {
    putc(val, stdout);
}


/* Map of memory mapped functions */

byte (*getmap[MAP_SIZE])(addr) = {
/* 0x00 */  get_invalid, get_invalid, get_invalid, get_invalid,
/* 0x04 */  get_invalid, get_invalid, get_invalid, get_invalid,
/* 0x08 */  get_invalid, get_invalid, get_invalid, get_invalid,
/* 0x0c */  get_invalid, get_invalid, get_invalid, get_invalid,
/* 0x10 */  get_stdin,   get_invalid, get_invalid, get_invalid,
/* 0x14 */  get_invalid, get_invalid, get_invalid, get_invalid,
/* 0x18 */  get_invalid, get_invalid, get_invalid, get_invalid,
/* 0x1c */  get_invalid, get_invalid, get_invalid, get_invalid,
};

void (*setmap[MAP_SIZE])(addr, byte) = {
/* 0x00 */  set_invalid, set_invalid, set_invalid, set_invalid,
/* 0x04 */  set_invalid, set_invalid, set_invalid, set_invalid,
/* 0x08 */  set_invalid, set_invalid, set_invalid, set_invalid,
/* 0x0c */  set_invalid, set_invalid, set_invalid, set_invalid,
/* 0x10 */  set_invalid, set_invalid, set_stdout,  set_invalid,
/* 0x14 */  set_invalid, set_invalid, set_invalid, set_invalid,
/* 0x18 */  set_invalid, set_invalid, set_invalid, set_invalid,
/* 0x1c */  set_invalid, set_invalid, set_invalid, set_invalid,
};


/* Memeory setters and getters */

byte mem_get(addr loc) {
    if (loc < MAP_SIZE)
        return getmap[loc](loc);
    else
        return mem[loc];
}


void mem_set(addr loc, byte val) {
    if (loc < MAP_SIZE)
        setmap[loc](loc, val);
    else
        mem[loc] = val;
}
