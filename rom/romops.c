#include <rom.h>

ubyte_t *rom = NULL;

struct memops rom_ops =
{
    ._read_dword = _rom_read_dword,
    ._read_word = _rom_read_word,
    ._read_hword = _rom_read_hword,
    ._read_byte = _rom_read_byte,
    ._write_dword = _rom_write_dword,
    ._write_word = _rom_write_word,
    ._write_hword = _rom_write_hword,
    ._write_byte = _rom_write_byte,
};

void rom_init(ubyte_t *rombuffer)
{
    rom = rombuffer;
    
}

udword_t _rom_read_dword(struct memory_region *reg, udword_t addr)
{
    return CONSTRUCT_DWORD(addr, rom);
}
uword_t _rom_read_word(struct memory_region *reg, udword_t addr)
{
    return CONSTRUCT_WORD(addr, rom);
}
uhword_t _rom_read_hword(struct memory_region *reg, udword_t addr)
{
    return CONSTRUCT_HWORD(addr, rom);
}
ubyte_t _rom_read_byte(struct memory_region *reg, udword_t addr)
{
    return rom[addr];
}
void _rom_write_dword(struct memory_region *reg, udword_t addr, udword_t value)
{
    return;
}
void _rom_write_word(struct memory_region *reg, udword_t addr, uword_t value)
{

    return;
}

void _rom_write_hword(struct memory_region *reg, udword_t addr, uhword_t value)
{
    return;
}
void _rom_write_byte(struct memory_region *reg, udword_t addr, ubyte_t value)
{
    return;
}