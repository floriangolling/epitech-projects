/*
** EPITECH PROJECT, 2020
** CPE_corewar_2019
** File description:
** fetch_merge_4b
*/

#include "corewar.h"

void merge_4bytes(core_t *core, process_t **process, void *param)
{
    int_4b *value = (int_4b *)param;
    int ic = 3;

    for (; ic >= 0; --ic) {
        (*value)[ic] = core->men[(*process)->pc];
        if (ic)
            INC_PC((*process)->pc);
    }
}

void merge_4bytes_pc(core_t *core, void *param, int pc)
{
    int_4b *value = (int_4b *)param;
    int ic = 3;

    for (; ic >= 0; --ic) {
        (*value)[ic] = core->men[pc];
        if (ic)
            INC_PC(pc);
    }
}