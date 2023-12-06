#include <mem.h>
#include <stdlib.h>

#define MAX_REGION_N 0x10

struct memory_region regions[MAX_REGION_N] = {};
unsigned int current_max_regions = 0;

struct memory_region *_get_region(udword_t addr)
{
    for (unsigned int reg_i = 0; reg_i < current_max_regions && regions[reg_i].present == 1; reg_i++)
    {
        if (regions[reg_i].base <= addr && regions[reg_i].base+regions[reg_i].size >= addr)
        {
            return &(regions[reg_i]);
        }
    }
    return NULL;
};

void add_region(struct memory_region region)
{
    regions[current_max_regions] = region;
    current_max_regions++;
    return;
}