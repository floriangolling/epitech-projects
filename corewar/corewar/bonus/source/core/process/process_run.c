/*
** EPITECH PROJECT, 2020
** CPE_corewar_bonus_2019
** File description:
** process_run
*/

#include "corewar_bonus.h"

static int process_wait(core_t *core, warrior_t *warrior, process_t **process)
{
    --(*process)->cycle;
    if (!(*process)->cycle)
        (*process)->state = EXECUTE;
    return (0);
}

int process_run(core_t *core, warrior_t *warrior)
{
    process_t *list = warrior->process;
    static int (*state[])(core_t *core, warrior_t *warrior, process_t **process)
    = {process_fetch, process_wait, process_execute};

    for (; list;list = list->next)
        if ((*state[list->state])(core, warrior, &list))
            return (1);
    return (0);
}