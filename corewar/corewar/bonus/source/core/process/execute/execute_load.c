/*
** EPITECH PROJECT, 2020
** CPE_corewar_bonus_2019
** File description:
** execute_load
*/

#include "corewar_bonus.h"

int execute_load(core_t *core, warrior_t *w, process_t **process, it_t *it)
{
    int pc = it->pc;

    if (param_type_control(*it))
        return (0);
    if (it->type[0] == INDIRECT) {
        merge_4bytes_pc(core, &(*process)->registre[it->param[1]],
        GO_PC(pc, it->param[0]));
    } else if (it->type[0] == DIRECT)
        (*process)->registre[it->param[1]] = it->param[0];
    (*process)->carry = CARRY((*process)->registre[it->param[1]]);
    return (0);
}

int execute_lload(core_t *core, warrior_t *w, process_t **process, it_t *it)
{
    int pc = it->pc;

    if (param_type_control(*it))
        return (0);
    if (it->type[0] == INDIRECT) {
        merge_4bytes_pc(core, &(*process)->registre[it->param[1]],
        GO_LPC(pc, it->param[0]));
    } else if (it->type[0] == DIRECT)
        (*process)->registre[it->param[1]] = it->param[0];
    (*process)->carry = CARRY((*process)->registre[it->param[1]]);
    return (0);
}

int execute_load_index(core_t *core, warrior_t *w, process_t **pcs, it_t *it)
{
    int s = 0;
    int a = 0;
    int b = 0;
    int pc = (*pcs)->pc;

    if (param_type_control(*it))
        return (0);
    a = param_type(core, pcs, 0, 7);
    b = param_type(core, pcs, 1, 6);
    s = a + b;
    merge_4bytes_pc(core, &(*pcs)->registre[it->param[2]], GO_PC(pc, s));
    (*pcs)->carry = CARRY((*pcs)->registre[it->param[2]]);
    return (0);
}

int execute_lload_index(core_t *core, warrior_t *w, process_t **pcs, it_t *it)
{
    int s = 0;
    int a = 0;
    int b = 0;
    int pc = (*pcs)->pc;

    if (param_type_control(*it))
        return (0);
    a = param_type(core, pcs, 0, 7);
    b = param_type(core, pcs, 1, 6);
    s = a + b;
    merge_4bytes_pc(core, &(*pcs)->registre[it->param[2]], GO_LPC(pc, s));
    (*pcs)->carry = CARRY((*pcs)->registre[it->param[2]]);
    return (0);
}
