#include <get_options.h>
#include <emu-err.h>
#include <interpret.h>
#include <stdio.h>
#include <errno.h>
#include <mem.h>
#include <rom.h>

void print_help(char *arg0)
{
    printf("Usage: %s [OPTIONS]\n", arg0);
    printf("Options:\n");
    printf("\t-r\tSelect Rom file (default rom.bin)\n");
    printf("\t-h\tDisplay this help message\n");
}

ssize_t *read_rom(FILE *rom, ubyte_t **buf)
{
    ssize_t size = 0;
    if (rom == NULL) 
    { 
        emu_err(E_NOFILE, "Rom file does not exist\n");
    } 
    fseek(rom, 0, SEEK_END);
    size = ftell(rom);
    fseek(rom, 0, SEEK_SET);
    *buf = malloc(size);
    if (size != fread(*buf, sizeof(ubyte_t), size, rom)) 
    { 
        free(*buf);
        emu_err(errno, "Failed to read rom file\n");
    } 

    fclose(rom);
    return size;
}

int main(int argc, char **argv)
{
    struct option_data *optbuffer = (typeof(optbuffer))malloc(sizeof(*optbuffer));
    unsigned int optionflags = get_options(optbuffer, argc, argv);

    FILE *romfile = NULL;

    if (optionflags & OPTION_HELP)
    {
        print_help(argv[0]);
        exit(0);
    }
    if (optionflags & OPTION_ROM_SPECIFIED)
    {
        romfile = optbuffer->rom_file;
    } else
    {
        romfile = fopen("rom.bin", "r");
    }

    struct greg_state primary = {};
    struct greg_state alternate = {};
    struct cpu_state state =
    {
        .current = &primary,
        .alternate = &alternate,
    };

    ubyte_t *rom = NULL;

    ssize_t romsize = read_rom(romfile, &rom);
    rom_init(rom);

    struct memory_region romreg = 
    {
        .present = 1,
        .base = ROM_START,
        .size = ROM_SIZE,
        .type = MEMORY_ROM,
        .ops = &rom_ops,
    };

    add_region(romreg);
    
    interpret(state);
    return 0;
}