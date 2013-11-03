#include "atoc.h"
#include "obj.h"
#include "sim.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>


void usage(char *name) {
    printf("Usage: %s [options] <objfile.ao>\n", name);
    printf("\t-h\n");
    printf("\t\tPrint usage information\n");
    printf("\t-f freq\n");
    printf("\t\tRun at specified frequency\n");
    printf("\t-e entry\n");
    printf("\t\tUse specified entry point\n");
    printf("\t-l\n");
    printf("\t\tLog all states of the simulation\n");
    printf("\t-q\n");
    printf("\t\tHide output of the simulation states\n");
}


int main(int argc, char **argv) {
    int opt;
    int delay = 1000;
    addr entry = 0x100;

    while ((opt = getopt(argc, argv, "hf:e:lq")) > 0) {
        switch (opt) {
            case 'h':
                usage(argv[0]);
                return 0;

            case 'f':
                if (strcmp(optarg, "0"))
                    delay = (int)(1000000.0 / strtod(optarg, 0));
                else
                    delay = 0;

                break;

            case 'e':
                entry = strtol(optarg, 0, 0);
                break;

            case 'l':
                set_log(1);
                break;

            case 'q':
                set_quiet(1);
                break;
        }
    }

    for (; optind < argc; optind++) {     
        if ((opt = obj_load(argv[optind]))) {
            fprintf(stderr, "%s: %s\n", argv[0], obj_error(opt));
            return 2;
        }
    }

    simulate(entry, delay);

    exit(0);
}

