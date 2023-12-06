#ifndef _ROM_H
#define _ROM_H

#include <mem.h>

#define ROM_START 0x0
#define ROM_SIZE 0x100

udword_t _rom_read_dword(struct memory_region *reg, udword_t addr);
uword_t _rom_read_word(struct memory_region *reg, udword_t addr);
uhword_t _rom_read_hword(struct memory_region *reg, udword_t addr);
ubyte_t _rom_read_byte(struct memory_region *reg, udword_t addr);
void _rom_write_dword(struct memory_region *reg, udword_t addr, udword_t value);
void _rom_write_word(struct memory_region *reg, udword_t addr, uword_t value);
void _rom_write_hword(struct memory_region *reg, udword_t addr, uhword_t value);
void _rom_write_byte(struct memory_region *reg, udword_t addr, ubyte_t value);

void rom_init(ubyte_t *rombuffer);

extern struct memops rom_ops;

#endif