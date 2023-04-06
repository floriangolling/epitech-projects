/*
** EPITECH PROJECT, 2020
** CPE_corewar_2019
** File description:
** execute_operators
*/

#include "corewar.h"

int execute_and(core_t *core, warrior_t *w, process_t **pcs, it_t *it)
{
    int a = 0;
    int b = 0;

    if (param_type_control(*it))
        return (0);
    a = param_type(core, pcs, 0, 7);
    b = param_type(core, pcs, 1, 7);
    (*pcs)->registre[it->param[2]] = a & b;
    (*pcs)->carry = CARRY((*pcs)->registre[it->param[2]]);
    return (0);
}

int execute_or(core_t *core, warrior_t *w, process_t **pcs, it_t *it)
{
    int a = 0;
    int b = 0;

    if (param_type_control(*it))
        return (0);
    a = param_type(core, pcs, 0, 7);
    b = param_type(core, pcs, 1, 7);
    (*pcs)->registre[it->param[2]] = a | b;
    (*pcs)->carry = CARRY((*pcs)->registre[it->param[2]]);
    return (0);
}

int execute_xor(core_t *core, warrior_t *w, process_t **pcs, it_t *it)
{
    int a = 0;
    int b = 0;

    if (param_type_control(*it))
        return (0);
    a = param_type(core, pcs, 0, 7);
    b = param_type(core, pcs, 1, 7);
    (*pcs)->registre[it->param[2]] = a ^ b;
    (*pcs)->carry = CARRY((*pcs)->registre[it->param[2]]);
    return (0);
}