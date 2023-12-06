#ifndef _EMU_ERR_H
#define _EMU_ERR_H

#include <stdlib.h>
#include <stdio.h>

enum emu_errs
{
    E_MEMOOB,
    E_NOFILE,
    E_NOREG,
    E_NOOP,
    E_BADARG,
};

#define __errprint(_msg, ...) fprintf(stderr, _msg __VA_OPT__(,) __VA_ARGS__)

#define emu_err(_exit, _msg, ...) __errprint(_msg, __VA_ARGS__); exit(-_exit)


#endif