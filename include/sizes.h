#ifndef _SIZES_H
#define _SIZES_H

#define CONSTRUCT_HWORD(__addr, __buffer) *(uhword_t*)(__buffer+__addr)

#define CONSTRUCT_WORD(__addr, __buffer) *(uword_t*)(__buffer+__addr)

#define CONSTRUCT_DWORD(__addr, __buffer) *(udword_t*)(__buffer+__addr)

typedef unsigned char ubyte_t;
typedef unsigned short uhword_t;
typedef unsigned int uword_t;
typedef unsigned long udword_t;

#endif