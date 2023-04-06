/*
** EPITECH PROJECT, 2020
** CPE_corewar_bonus_2019
** File description:
** execute_param
*/

#include "corewar_bonus.h"

int param_type_control(it_t it)
{
    if (WRONG_IT(it.mnemonic)) return (1);
    for (int e = 0; e < ref[it.mnemonic].nbr_args; ++e) {
        if (!(it.type[e] & ref[it.mnemonic].type[e]))
            return (1);
        if (it.type[e] == REGISTER && (WRONG_REG(it.param[e])))
            return (1);
    }
    return (0);
}

int param_type(core_t *core, process_t **pcs, u_int8_t ic, u_int8_t ref)
{
    int pc = (*pcs)->it.pc;
    int merge = 0;

    if (ref & 1 && (*pcs)->it.type[ic] == REGISTER)
        return ((*pcs)->registre[(*pcs)->it.param[ic]]);
    if (ref & 2 && (*pcs)->it.type[ic] == DIRECT)
        return ((*pcs)->it.param[ic]);
    if (ref & 4 && (*pcs)->it.type[ic] == INDIRECT) {
        merge_2bytes_pc(core, &merge, GO_PC(pc, (*pcs)->it.param[ic]));
        return (merge);
    }
    return (0);
}