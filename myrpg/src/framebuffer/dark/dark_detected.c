/*
** EPITECH PROJECT, 2020
** MUL_my_rpg_2019
** File description:
** dark_detected
*/

#include "rpg.h"

void dark_detected(game_t *ga, sfUint8 large, int x, int y)
{
    static int ic = 1;

    ga->fbf.dark.halo[ic].pos.x = x;
    ga->fbf.dark.halo[ic].pos.y = y;
    ga->fbf.dark.halo[ic].radius = large;
    ++ic;
    if (ic == ga->fbf.dark.nb_halo)
        ic = 1;
    return;
}