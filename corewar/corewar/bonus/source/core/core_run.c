/*
** EPITECH PROJECT, 2020
** CPE_corewar_bonus_2019
** File description:
** core_run
*/

#include "corewar_bonus.h"

int core_run(core_t *core)
{
    for (int i = 0; i < core->nb_w; ++i) {
        if (!core->warrior[i].alive)
            continue;
        if (process_run(core, &core->warrior[i]))
            return (1);
    }
    if (core_cycle(core, &core->cycle))
        return (1);
    return (0);
}