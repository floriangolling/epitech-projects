/*
** EPITECH PROJECT, 2020
** CPE_corewar_bonus_2019
** File description:
** process_it
*/

#include "corewar_bonus.h"

void init_it(it_t *it)
{
    it->pc = 0;
    it->mnemonic = 0;
    for (int e = 0; e < MAX_ARGS_NUMBER; ++e) {
        it->type[e] = 0;
        it->param[e] = 0;
    }
}

void restore_it(process_t **process)
{
    for (int e = 0; e < 4; ++e) {
        (*process)->it.type[e] = 0;
        (*process)->it.param[e] = 0;
    }
}