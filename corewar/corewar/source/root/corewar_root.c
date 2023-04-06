/*
** EPITECH PROJECT, 2020
** CPE_corewar_2019
** File description:
** corewar_root
*/

#include "corewar.h"

static int init_all(corewar_t *corewar, int argc, char **argv)
{
    if (init_core(&corewar->core, argc, argv)) return (1);
    return (0);
}

static void destroy_all(corewar_t *corewar)
{
    destroy_core(&corewar->core);
    free(corewar);
}

int corewar_root(int argc, char **argv)
{
    corewar_t *corewar = malloc(sizeof(corewar_t));
    int value = 0;

    if (!corewar) return (1);
    if (init_all(corewar, argc, argv)) return (1);
    value = core_run(&corewar->core);
    destroy_all(corewar);
    if (value)
        return (1);
    return (0);
}