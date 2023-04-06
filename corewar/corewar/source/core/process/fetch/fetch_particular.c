/*
** EPITECH PROJECT, 2020
** CPE_corewar_2019
** File description:
** fetch_particular
*/

#include "corewar.h"

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
    if ((*process)->it.mnemonic == LIVE) {
        fetch_live(core, warrior, process);
        return (1);
    }
    if ((*process)->it.mnemonic == ZJMP) {
        fetch_zjmp(core, warrior, process);
        return (1);
    }
    if ((*process)->it.mnemonic == FORK || (*process)->it.mnemonic == LFORK) {
        fetch_fork(core, warrior, process);
        return (1);
    }
    return (0);
}