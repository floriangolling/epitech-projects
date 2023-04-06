/*
** EPITECH PROJECT, 2020
** bonus
** File description:
** cycle_verification
*/

#include "corewar_bonus.h"

void verified_living_process(core_t *core, cycle_t *cycle)
{
    process_t *tmp;

    for (int e = 0; e < core->nb_w; ++e) {
        if (!core->warrior[e].alive)
            continue;
        tmp = core->warrior[e].process;
        for (int i = 0; tmp; tmp = tmp->next, ++i) {
            if (!tmp->alive) {
                --core->warrior[e].nb_p;
                sfText_setString(core->reveal.info[e].nb_p.text,
                nm_itoa(core->reveal.info[e].nb, core->warrior[e].nb_p));
                sfText_setOutlineColor(core->reveal.cell[tmp->it.pc].text,
                sfBlack);
                remove_process_index(&core->warrior[e].process, i);
            }
        }
    }
}

void display_winner(core_t *core, int winner)
{
    my_putstr("The player ");
    my_putnbr(core->warrior[winner].warrior_n);
    my_putstr("(");
    my_putstr(core->warrior[winner].header.prog_name);
    my_putstr(") has won.\n");
}

static int cycle_conclusion(core_t *core, cycle_t *cycle, int winner,
int still_live)
{
    if (still_live == 1) {
        display_winner(core, winner);
            return (1);
    } else if (!still_live) {
        display_winner(core, cycle->last_live - 1);
        return (1);
    }
    return (0);
}

static void restore_dead(core_t *core, cycle_t *cycle, warrior_t *w)
{
    process_t *save;

    cycle->cycle = 0;
    save = w->process;
    for (; w->process; w->process = w->process->next) {
        w->process->alive = 0;
        sfText_setOutlineColor(core->reveal.cell[w->process->it.pc].text,
        sfBlack);
        sfText_setString(core->reveal.info[w->n - 1].nb_p.text,
        nm_itoa(core->reveal.info[w->n - 1].nb, 0));
    }
    w->process = save;
}

int verified_living_warrior(core_t *core, cycle_t *cycle)
{
    process_t *tmp;
    int i = 0;
    int still_live = 0;
    int winner = 0;

    for (int e = 0; e < core->nb_w; ++e) {
        if (!core->warrior[e].alive) continue;
        tmp = core->warrior[e].process;
        for (i = 0; tmp; tmp = tmp->next, ++i);
        if (!i || core->warrior[e].alive != 2) {
            core->warrior[e].alive = 0;
            sfRectangleShape_setFillColor(core->reveal.info[e].rect.shape,
            sfRed);
            restore_dead(core, cycle, &core->warrior[e]);
        } else {
            ++still_live;
            winner = e;
        }
    }
    if (cycle_conclusion(core, cycle, winner, still_live)) return (1);
    return (0);
}