/*
** EPITECH PROJECT, 2020
** bonus
** File description:
** bonus_reveal
*/

#include "corewar_bonus.h"

int init_reveal(core_t *core, reveal_t *reveal)
{
    reveal->pause = 0;
    reveal->frame = 100.0;
    reveal->output = 10;
    reveal->font = sfFont_createFromFile("media/font/Teko-Regular.ttf");
    if (!reveal->font) return (error("CELL: failed to load font\n"));
    if (init_window(&reveal->cw)) return (1);
    if (init_board(core, reveal)) return (1);
    if (init_info(core, reveal)) return (1);
    return (0);
}

static int calcul_run(core_t *core, reveal_t *rv)
{
    if (rv->cw.vm > (1.0 / rv->frame) && !rv->pause) {
        if (core_run(core))
            return (1);
        sfClock_restart(rv->cw.vclock);
    }
    return (0);
}

int reveal_run(core_t *core, reveal_t *rv)
{
    while (sfRenderWindow_isOpen(rv->cw.window)) {
        time_event_handling(core, rv, &rv->cw);
        if (calcul_run(core, rv))
            break;
        if (rv->cw.sec > (1.0 / rv->output) && !rv->pause) {
            sfRenderWindow_clear(rv->cw.window, sfBlack);
            info_run(core, rv);
            board_display(core, rv);
            sfRenderWindow_display(rv->cw.window);
            sfClock_restart(rv->cw.clock);
        }
    }
    return (0);
}

void destroy_reveal(core_t *core, reveal_t *reveal)
{
    sfFont_destroy(reveal->font);
    for (int e = 0; e < MEM_SIZE; ++e)
        destroy_cell(&reveal->cell[e]);
    destroy_window(&reveal->cw);
    destroy_info(core, reveal);
}