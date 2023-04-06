/*
** EPITECH PROJECT, 2020
** CPE_corewar_2019
** File description:
** reveal_board
*/

#include "corewar_bonus.h"

int init_board(core_t *core, reveal_t *reveal)
{
    sfVector2f pos = {1, 216};
    sfVector2f gap = {15, 18};

    for (int e = 0; e < MEM_SIZE; ++e, pos.x += gap.x) {
        reveal->cell[e].font = reveal->font;
        if (init_cell(&reveal->cell[e], pos, core->men[e], core->belong[e]))
            return (1);
        if (pos.x > WIDTH - (1 + gap.x)) {
            pos.x = 1 - gap.x;
            pos.y += gap.y;
        }
    }
    return (0);
}

void board_display(core_t *core, reveal_t *rv)
{
    for (int e = 0; e < MEM_SIZE; ++e)
        cell_display(rv, &rv->cell[e], core->men[e]);
}