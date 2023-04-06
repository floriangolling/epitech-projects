/*
** EPITECH PROJECT, 2020
** CPE_corewar_bonus_2019
** File description:
** fetch_merge_2b
*/

#include "corewar_bonus.h"

static void merge_bytes(core_t *core, process_t **process, void *param)
{
    short_2b *value = (short_2b *)param;
    int ic = 1;

    for (; ic >= 0; --ic) {
        (*value)[ic] = core->men[(*process)->pc];
        if (ic)
            INC_PC((*process)->pc);
    }
}

void merge_2bytes(core_t *core, process_t **process, int *param)
{
    merge_bytes(core, process, (void *)param);
    *param = (short)*param;
}


static void merge_bytes_pc(core_t *core, void *param, int pc)
{
    short_2b *value = (short_2b *)param;
    int ic = 1;

    for (; ic >= 0; --ic) {
        (*value)[ic] = core->men[pc];
        if (ic)
            INC_PC(pc);
    }
}

void merge_2bytes_pc(core_t *core, int *param, int pc)
{
    merge_bytes_pc(core, (void *)param, pc);
    *param = (short)*param;
}