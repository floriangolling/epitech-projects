/*
** EPITECH PROJECT, 2020
** CPE_corewar_bonus_2019
** File description:
** execute_store
*/

#include "corewar_bonus.h"

int execute_store(core_t *core, warrior_t *w, process_t **process, it_t *it)
{
    int pc = it->pc;

    if (param_type_control(*it))
        return (0);
    if (it->type[1] == INDIRECT) {
        divide_in_4bytes(core, &(*process)->registre[it->param[0]],
        GO_PC(pc, it->param[1]), w->n);
    } else if (it->type[1] == REGISTER) {
        (*process)->registre[it->param[1]] = (*process)->registre[it->param[0]];
    }
    return (0);
}

int execute_store_index(core_t *core, warrior_t *w, process_t **pcs, it_t *it)
{
    int pc = it->pc;
    int a = 0;
    int b = 0;

    if (param_type_control(*it))
        return (0);
    a = param_type(core, pcs, 1, 7);
    b = param_type(core, pcs, 2, 3);
    divide_in_4bytes(core, &(*pcs)->registre[it->param[0]], GO_PC(pc, (a + b)),
    w->n);
    return (0);
}