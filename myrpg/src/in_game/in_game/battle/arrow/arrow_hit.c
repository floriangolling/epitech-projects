/*
** EPITECH PROJECT, 2020
** MUL_my_rpg_2019
** File description:
** arrow_hit
*/

#include "rpg.h"

void arrow_hit(game_t *ga, arrow_t *arrow)
{
    int x = arrow->pos.x + arrow->tip.x;
    int y = arrow->pos.y + arrow->tip.y;

    if (ga->hit.map.box[y][x] & 128)
        arrow->send = 0;
    return;
}