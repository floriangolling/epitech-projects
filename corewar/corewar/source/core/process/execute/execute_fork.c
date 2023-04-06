/*
** EPITECH PROJECT, 2020
** CPE_corewar_2019
** File description:
** execute_fork
*/

#include "corewar.h"

int execute_fork(core_t *core, warrior_t *w, process_t **process, it_t *it)
{
    int pc = it->pc;

    if (insert_process_end(process,
    duplicate_process(GO_PC(pc, it->param[0]), (*process))))
        return (error("FORK: failed to create a new process\n"));
    return (0);
}

int execute_long_fork(core_t *core, warrior_t *w, process_t **pcs, it_t *it)
{
    int pc = (*pcs)->pc;

    if (insert_process_end(pcs,
    create_process(GO_LPC(pc, it->param[0]), w->warrior_n)))
        return (error("FORK: failed to create a new process\n"));
    return (0);
}