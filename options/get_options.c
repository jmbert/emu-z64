#include <get_options.h>
#include <getopt.h>
#include <emu-err.h>

unsigned int get_options(struct option_data *opt_buffer, int argc, char **argv)
{
    unsigned int opflags = 0;

    int opt;

    while ((opt = getopt(argc, argv, "r:h")) != -1) {
        switch (opt) {
        case 'r': 
            opflags |= OPTION_ROM_SPECIFIED; 
            opt_buffer->rom_file = fopen(optarg, "r");
            break;
        case 'h': 
            opflags |= OPTION_HELP; 
            break;
        }
    }

    return opflags;
}