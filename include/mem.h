#ifndef _MEMORY_H
#define _MEMORY_H

#include <emu-err.h>

#include <sizes.h>


enum _memory_type
{
    MEMORY_RAM,
    MEMORY_ROM,
};


struct memory_region
{
    unsigned int present;
    unsigned long base;
    unsigned long size;

    unsigned int type;

    struct memops *ops;
};
struct memops
{
    udword_t (*_read_dword)(struct memory_region *reg, udword_t addr);
    uword_t (*_read_word)(struct memory_region *reg, udword_t addr);
    uhword_t (*_read_hword)(struct memory_region *reg, udword_t addr);
    ubyte_t (*_read_byte)(struct memory_region *reg, udword_t addr);
    void (*_write_dword)(struct memory_region *reg, udword_t addr, udword_t value);
    void (*_write_word)(struct memory_region *reg, udword_t addr, uword_t value);
    void (*_write_hword)(struct memory_region *reg, udword_t addr, uhword_t value);
    void (*_write_byte)(struct memory_region *reg, udword_t addr, ubyte_t value);
};

struct memory_region *_get_region(udword_t addr);
void add_region(struct memory_region region);

inline udword_t read_memdw(udword_t addr)
{
    struct memory_region *region = _get_region(addr);
    if (region == NULL) 
    {
        emu_err(E_MEMOOB, "Address not covered by region\n");
    }
    return region->ops->_read_dword(region, addr - region->base);
}
inline uword_t read_memw(udword_t addr)
{
    struct memory_region *region = _get_region(addr);
    if (region == NULL) 
    {
        emu_err(E_MEMOOB, "Address not covered by region\n");
    }
    return region->ops->_read_word(region, addr - region->base);
}
inline uhword_t read_memhw(udword_t addr)
{
    struct memory_region *region = _get_region(addr);
    if (region == NULL) 
    {
        emu_err(E_MEMOOB, "Address not covered by region\n");
    }
    return region->ops->_read_hword(region, addr - region->base);
}
inline ubyte_t read_memb(udword_t addr)
{
    struct memory_region *region = _get_region(addr);
    if (region == NULL) 
    {
        emu_err(E_MEMOOB, "Address not covered by region\n");
    }
    return region->ops->_read_byte(region, addr - region->base);
}
inline void write_memdw(udword_t addr, udword_t value)
{
    struct memory_region *region = _get_region(addr);
    if (region == NULL) 
    {
        emu_err(E_MEMOOB, "Address not covered by region\n");
    }
    region->ops->_write_dword(region, addr - region->base, value);
}
inline void write_memw(udword_t addr, uword_t value)
{
    struct memory_region *region = _get_region(addr);
    if (region == NULL) 
    {
        emu_err(E_MEMOOB, "Address not covered by region\n");
    }
    return region->ops->_read_word(region, addr - region->base);
}
inline void write_memhw(udword_t addr, uhword_t value)
{
    struct memory_region *region = _get_region(addr);
    if (region == NULL) 
    {
        emu_err(E_MEMOOB, "Address not covered by region\n");
    }
    region->ops->_write_hword(region, addr - region->base, value);
}
inline void write_memb(udword_t addr, ubyte_t value)
{
    struct memory_region *region = _get_region(addr);
    if (region == NULL) 
    {
        emu_err(E_MEMOOB, "Address not covered by region\n");
    }
    region->ops->_write_byte(region, addr - region->base, value);
}
#endif