/*
** EPITECH PROJECT, 2020
** CPE_corewar_bonus_2019
** File description:
** execute_life
*/

#include "corewar_bonus.h"

static void live_alive(core_t *core, warrior_t *w, process_t **process,
it_t *it)
{
    ++core->cycle.nbr_live;
    if (it->param[0] == w->warrior_n) {
        w->alive = 2;
        core->cycle.last_live = w->n;
        sfText_setString(core->reveal.cy_info.nb_l.text,
        nm_itoa(core->reveal.cy_info.li, core->cycle.nbr_live));
        sfRectangleShape_setFillColor(core->reveal.info[w->n - 1].rect.shape,
        sfGreen);
    }
    (*process)->alive = 1;
}

static void live_display(warrior_t *w, it_t *it)
{
    my_putstr("The player ");
    my_putnbr(it->param[0]);
    my_putstr("(");
    my_putstr(w->header.prog_name);
    my_putstr(") is alive.\n");
}

int execute_live(core_t *core, warrior_t *w, process_t **process, it_t *it)
{
    live_alive(core, w, process, it);
    live_display(w, it);
    return (0);
}