/*
** EPITECH PROJECT, 2020
** CPE_corewar_bonus_2019
** File description:
** core_cycle
*/

#include "corewar_bonus.h"

int init_cycle(core_t *core, cycle_t *cycle)
{
    cycle->cycle = 0;
    cycle->total = 0;
    cycle->cycle_to_die = CYCLE_TO_DIE;
    cycle->nbr_live = 0;
    cycle->last_live = 0;
    return (0);
}

static void restore_alive(core_t *core, cycle_t *cycle)
{
    process_t *save;

    cycle->cycle = 0;
    for (int e = 0; e < core->nb_w; ++e) {
        if (!core->warrior[e].alive) continue;
        save = core->warrior[e].process;
        for (; core->warrior[e].process;
        core->warrior[e].process = core->warrior[e].process->next)
            core->warrior[e].process->alive = 0;
        core->warrior[e].alive = 1;
        sfRectangleShape_setFillColor(core->reveal.info[e].rect.shape,
        ORANGE);
        core->warrior[e].process = save;
    }
}

static void cycle_continue(core_t *core, cycle_t *cycle)
{
    ++cycle->cycle;
    ++cycle->total;
    sfText_setString(core->reveal.cy_info.nb_c.text,
    nm_itoa(core->reveal.cy_info.cy, cycle->cycle));
    sfText_setString(core->reveal.cy_info.nb_t.text,
    nm_itoa(core->reveal.cy_info.to, cycle->total));
}

static void cycle_decrement(core_t *core, cycle_t *cycle)
{
    cycle->cycle_to_die -= CYCLE_DELTA;
    sfText_setString(core->reveal.cy_info.nb_d.text,
    nm_itoa(core->reveal.cy_info.di, cycle->cycle_to_die));
    cycle->nbr_live = 0;
    sfText_setString(core->reveal.cy_info.nb_l.text,
    nm_itoa(core->reveal.cy_info.li, cycle->nbr_live));
}

int core_cycle(core_t *core, cycle_t *cycle)
{
    cycle_continue(core, cycle);
    if (core->nb_cycle && core->nb_cycle < cycle->total) {
        display_winner(core, cycle->last_live - 1);
        return (1);
    }
    if (cycle->cycle >= cycle->cycle_to_die) {
        verified_living_process(core, cycle);
        if (verified_living_warrior(core, cycle))
            return (1);
        restore_alive(core, cycle);
    }
    if (cycle->nbr_live >= NBR_LIVE)
        cycle_decrement(core, cycle);
    return (0);
}