/*
** EPITECH PROJECT, 2020
** CPE_corewar_2019
** File description:
** execute_arithmetic
*/

#include "corewar.h"

int execute_addition(core_t *core, warrior_t *w, process_t **pcs, it_t *it)
{
    int sum = 0;

    if (param_type_control(*it))
        return (0);
    sum = (*pcs)->registre[it->param[0]] + (*pcs)->registre[it->param[1]];
    (*pcs)->registre[it->param[2]] = sum;
    (*pcs)->carry = CARRY((*pcs)->registre[it->param[2]]);
    return (0);
}

int execute_subtraction(core_t *core, warrior_t *w, process_t **pcs, it_t *it)
{
    int sum = 0;

    if (param_type_control(*it))
        return (0);
    sum = (*pcs)->registre[it->param[0]] - (*pcs)->registre[it->param[1]];
    (*pcs)->registre[it->param[2]] = sum;
    (*pcs)->carry = CARRY((*pcs)->registre[it->param[2]]);
    return (0);
}