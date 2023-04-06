/*
** EPITECH PROJECT, 2020
** CPE_corewar_2019
** File description:
** fill_memory
*/

#include "corewar.h"

void memory_fill(core_t *core, warrior_t *warrior)
{
    int idx = 0;

    for (int e = 0; e < warrior->header.prog_size; ++e) {
        idx = (e + warrior->ld_adress) % (MEM_SIZE);
        core->men[idx] = warrior->program[e];
    }
}