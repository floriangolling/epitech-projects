/*
** EPITECH PROJECT, 2020
** CPE_corewar_bonus_2019
** File description:
** fetch_particular
*/

#include "corewar_bonus.h"

static void fetch_live(core_t *core, warrior_t *warrior, process_t **process)
{
    restore_it(process);
    merge_4bytes(core, process, &(*process)->it.param[0]);
    INC_PC((*process)->pc);
}

static void fetch_zjmp(core_t *core, warrior_t *warrior, process_t **process)
{
    restore_it(process);
    merge_2bytes(core, process, &(*process)->it.param[0]);
    INC_PC((*process)->pc);
}

static void fetch_fork(core_t *core, warrior_t *warrior, process_t **process)
{
    restore_it(process);
    merge_2bytes(core, process, &(*process)->it.param[0]);
    INC_PC((*process)->pc);
}

int fetch_particular(core_t *core, warrior_t *warrior, process_t **process)
{
    int yes = 0;

    if ((*process)->it.mnemonic == LIVE) {
        fetch_live(core, warrior, process);
        yes = 1;
    }
    if ((*process)->it.mnemonic == ZJMP) {
        fetch_zjmp(core, warrior, process);
        yes = 1;
    }
    if ((*process)->it.mnemonic == FORK || (*process)->it.mnemonic == LFORK) {
        fetch_fork(core, warrior, process);
        yes = 1;
    }
    if (yes) {
        fill_cmd(core, warrior, process,
        &core->reveal.info[warrior->n - 1].cmd);
        return (1);
    }
    return (0);
}