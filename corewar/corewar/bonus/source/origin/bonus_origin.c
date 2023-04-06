/*
** EPITECH PROJECT, 2020
** CPE_corewar_bonus_2019
** File description:
** bonus_origin
*/

#include "corewar_bonus.h"

static int init_all(core_t *core, int argc, char **argv)
{
    if (init_core(core, argc, argv)) return (1);
    if (init_reveal(core, &core->reveal)) return (1);
    return (0);
}

static void destroy_all(core_t *core)
{
    destroy_core(core);
    destroy_reveal(core, &core->reveal);
    free(core);
}

int bonus_origin(int argc, char **argv)
{
    core_t *core = malloc(sizeof(core_t));
    int value = 0;

    if (!core) return (1);
    if (init_all(core, argc, argv)) return (1);
    value = reveal_run(core, &core->reveal);
    destroy_all(core);
    if (value)
        return (1);
    return (0);
}