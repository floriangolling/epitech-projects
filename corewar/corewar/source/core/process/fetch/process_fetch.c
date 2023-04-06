/*
** EPITECH PROJECT, 2020
** CPE_corewar_2019
** File description:
** process_fetch
*/

#include "corewar.h"

static void fetch_type(core_t *core, warrior_t *warrior, process_t **process)
{
    u_int8_t cd_b = core->men[(*process)->pc];

    for (int e = 0; e < 4; ++e, cd_b = cd_b << 2) {
        (*process)->it.type[e] = NO_PARAM;
        if (!(cd_b & 128) && cd_b & 64)
            (*process)->it.type[e] = REGISTER;
        if (cd_b & 128 && !(cd_b & 64))
            (*process)->it.type[e] = DIRECT;
        if (cd_b & 128 && cd_b & 64)
            (*process)->it.type[e] = INDIRECT;
    }
}

static void param_direct(core_t *core, warrior_t *warrior, process_t **process,
int e)
{
    u_int8_t it = (*process)->it.mnemonic;

    if (it == LDI || it == STI || it == LLDI)
        merge_2bytes(core, process, &(*process)->it.param[e]);
    else
        merge_4bytes(core, process, &(*process)->it.param[e]);
}

static void fetch_param(core_t *core, warrior_t *warrior, process_t **process)
{
    for (int e = 0; e < 4; ++e) {
        (*process)->it.param[e] = 0;
        if ((*process)->it.type[e] == REGISTER) {
            (*process)->it.param[e] = core->men[(*process)->pc];
            INC_PC((*process)->pc);
        }
        if ((*process)->it.type[e] == DIRECT) {
            param_direct(core, warrior, process, e);
            INC_PC((*process)->pc);
        }
        if ((*process)->it.type[e] == INDIRECT) {
            merge_2bytes(core, process, &(*process)->it.param[e]);
            INC_PC((*process)->pc);
        }
    }
}

int process_fetch(core_t *core, warrior_t *warrior, process_t **process)
{
    u_int8_t it;

    (*process)->state = WAIT;
    (*process)->it.pc = (*process)->pc;
    (*process)->it.mnemonic = core->men[(*process)->pc];
    it = core->men[(*process)->pc];
    if (WRONG_IT(it)) {
        INC_PC((*process)->pc);
        (*process)->state = FETCH;
        return (0);
    }
    (*process)->cycle = ref[it].nbr_cycles;
    INC_PC((*process)->pc);
    if (fetch_particular(core, warrior, process))
        return (0);
    fetch_type(core, warrior, process);
    INC_PC((*process)->pc);
    fetch_param(core, warrior, process);
    return (0);
}