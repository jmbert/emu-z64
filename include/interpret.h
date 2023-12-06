#ifndef _EMU_STATE_H
#define _EMU_STATE_H

#include <sizes.h>

struct greg_state
{
    uword_t a;
    uword_t flags;
    uword_t b;
    uword_t c;
    uword_t d;
    uword_t e;
};

struct cpu_state
{
    struct greg_state *current;
    struct greg_state *alternate;
    uword_t h;
    uword_t l;
    
    udword_t sp;
    udword_t ix;
    udword_t iy;
    udword_t pc;
};

void interpret(struct cpu_state initial_state);

#endif