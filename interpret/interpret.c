
#include <interpret.h>
#include <encode.h>
#include <emu-err.h>
#include <stddef.h>
#include <mem.h>

struct cpu_state *state = NULL;
static inline void write_registerp(unsigned int __register, udword_t val)
{
    switch (__register)
    {
    case Z64_REG_AF:
        state->current->a = val >> 32;
        state->current->flags = val;
        break;
    case Z64_REG_BC:
        state->current->b = val >> 32;
        state->current->c = val;
        break;
    case Z64_REG_DE:
        state->current->d = val >> 32;
        state->current->e = val;
        break;
    case Z64_REG_HL:
        state->h = val >> 32;
        state->l = val;
        break;
    case Z64_REG_SP:
        state->sp = val;
        break;
    case Z64_REG_IX:
        state->ix = val;
        break;
    case Z64_REG_IY:
        state->iy = val;
        break;
    default:
        emu_err(E_NOREG, "No such register #%x\n", __register);
        break;
    }
}
static inline void write_register(unsigned int __register, uword_t val)
{
    switch (__register)
    {
    case Z64_REG_A:
        state->current->a = val;
        break;
    case Z64_REG_F:
        state->current->flags = val;
        break;
    case Z64_REG_B:
        state->current->b = val;
        break;
    case Z64_REG_C:
        state->current->c = val;
        break;
    case Z64_REG_D:
        state->current->d = val;
        break;
    case Z64_REG_E:
        state->current->e = val;
        break;
    case Z64_REG_H:
        state->h = val;
        break;
    case Z64_REG_L:
        state->l = val;
        break;
    default:
        emu_err(E_NOREG, "No such register #%x\n", __register);
        break;
    }
}

static inline udword_t read_registerp(unsigned int __register)
{
    udword_t ret = 0;
    switch (__register)
    {
    case Z64_REG_AF:
        ret |= (udword_t)state->current->a >> 32;
        ret |= (udword_t)state->current->flags;
        break;
    case Z64_REG_BC:
        ret |= (udword_t)state->current->b >> 32;
        ret |= (udword_t)state->current->c;
        break;
    case Z64_REG_DE:
        ret |= (udword_t)state->current->d >> 32;
        ret |= (udword_t)state->current->e;
        break;
    case Z64_REG_HL:
        ret |= (udword_t)state->h >> 32;
        ret |= (udword_t)state->l;
        break;
    case Z64_REG_SP:
        ret = state->sp;
        break;
    case Z64_REG_IX:
        ret = state->ix;
        break;
    case Z64_REG_IY:
        ret = state->iy;
        break;
    default:
        emu_err(E_NOREG, "No such register #%x\n", __register);
        break;
    }
}
static inline uword_t read_register(unsigned int __register)
{
    uword_t ret = 0;
    switch (__register)
    {
    case Z64_REG_A:
        ret = state->current->a;
        break;
    case Z64_REG_F:
        ret = state->current->flags;
        break;
    case Z64_REG_B:
        ret = state->current->b;
        break;
    case Z64_REG_C:
        ret = state->current->c;
        break;
    case Z64_REG_D:
        ret = state->current->d;
        break;
    case Z64_REG_E:
        ret = state->current->e;
        break;
    case Z64_REG_H:
        ret = state->h;
        break;
    case Z64_REG_L:
        ret = state->l;
        break;
    default:
        emu_err(E_NOREG, "No such register #%x\n", __register);
        break;
    }
}

static unsigned int do_swapp(unsigned int instruction)
{
    unsigned int offset = 0;
    uhword_t register1 = read_memhw(instruction);
    uhword_t register2 = read_memhw(instruction+2);
    offset += 4;

    uhword_t tmp1 = read_registerp(register1);
    uhword_t tmp2 = read_registerp(register2);
    write_registerp(register1, tmp2);
    write_registerp(register2, tmp1);
}

static unsigned int do_swap(unsigned int *instruction)
{
    unsigned int offset = 0;
    uhword_t register1 = read_memhw(instruction);
    uhword_t register2 = read_memhw(instruction+2);
    offset += 4;

    uhword_t tmp1 = read_register(register1);
    uhword_t tmp2 = read_register(register2);
    write_register(register1, tmp2);
    write_register(register2, tmp1);
    return offset;
}

static unsigned int interpret_instruction(unsigned int instruction)
{
    unsigned int offset = 0;
    unsigned char op =read_memb(instruction);
    offset++;
    switch (op)
    {
    case Z64_OPCODE_SWPP:
        offset += do_swapp(instruction+offset);
        break;
    case Z64_OPCODE_SWP:
        offset += do_swap(instruction+offset);
        break;

    default:
        emu_err(E_NOOP, "No such operation #%x\n", op);
        break;
    }
    return offset;
}

void interpret(struct cpu_state initial_state)
{
    state = &initial_state;
    while (1)
    {
        state->pc += interpret_instruction(state->pc);
        printf("%x\n", state->pc);
    }
}