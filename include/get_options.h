#ifndef _GET_OPTIONS_H
#define _GET_OPTIONS_H

#include <stdio.h>

enum _options
{
    OPTION_HELP = 1 << 0,
    OPTION_ROM_SPECIFIED = 1 << 1,
};

struct option_data
{
    FILE *rom_file;
};

unsigned int get_options(struct option_data *opt_buffer, int argc, char **argv);

#endif