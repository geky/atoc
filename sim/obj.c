#include "obj.h"

#include <string.h>
#include <stdio.h>

static const char *errors[] = {
    "Error opening file",
    "Invalid object file",
    "Exceeded address size",
    "Exceeded memory",
};


// Returns error string
const char *obj_error(int err) {
    return errors[(-err) - 1];
}


static int load_addr(FILE *file, byte addrlen, addr *dest) {
    int i;
    byte temp;
    addr res = 0;

    for (i = 0; i <= addrlen; i++) {
        if (res >> (ADDR_SIZE-8))
            return -3;

        if (fread(&temp, 1, 1, file) != 1)
            return -2;

        res <<= BYTE_SIZE;
        res |= temp;
    }

    *dest = res;
    return 0;
}
    

// returns less than zero on failure
int obj_load(char *filename) {
    byte temp;
    int err;
    byte addrlen;

    addr start;
    addr size;

    FILE *file = fopen(filename, "rb");


    // Get header info
    if (!file)
        return -1;

    if (fread(&temp, 1, 1, file) != 1) 
        return -2;

    if (temp != 'a')
        return -2;

    if (fread(&addrlen, 1, 1, file) != 1) 
        return -2;

    addrlen /= 8;


    while (1) {
        // Get bounds
        if ((err = load_addr(file, addrlen, &start))) {
            if (err == -2 && !ferror(file))
                return 0; // check for eof
            else
                return err;
        }

        if ((err = load_addr(file, addrlen, &size)))
            return err;


        // Check memory limits
        if (ADDR(start+size) < start)
            return -4;

        // Copy over memory
        if (fread(&mem[start], 1, size, file) != size)
            return -2;
    }
}   
