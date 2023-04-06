/*
** EPITECH PROJECT, 2020
** CPE_corewar_bonus_2019
** File description:
** core_memory
*/

#include "corewar_bonus.h"

static int init_header(warrior_t *warrior, int fd)
{
    if (!fd)
        return (error("INIT: arg aren't a warrior or unknow arg\n"));
    if (read(fd, &warrior->header, sizeof(header_t)) == -1)
        return (error("INIT: header error\n"));
    BIT(warrior->header.prog_size);
    return (0);
}

static int init_program(warrior_t *warrior, int fd)
{
    int a = 0;

    warrior->program = malloc(warrior->header.prog_size + 1);
    if (!warrior->program) return (1);
    if ((a = read(fd, warrior->program, warrior->header.prog_size)) == -1)
        return (error("INIT: failed to read the program\n"));
    warrior->program[warrior->header.prog_size] = '\0';
    close(fd);
    return (0);
}

int init_menory(core_t *core, warrior_t *warrior, char **argv, int *e)
{
    int fd = open(argv[*e], O_RDONLY);

    if (init_header(warrior, fd)) return (1);
    if (init_program(warrior, fd)) return (1);
    if (insert_process_end(&warrior->process,
    create_process(warrior->ld_adress, warrior->warrior_n))) return (1);
    memory_fill(core, warrior);
    return (0);
}