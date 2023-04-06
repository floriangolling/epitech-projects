/*
** EPITECH PROJECT, 2020
** framebuffer
** File description:
** shape_drop
*/

#include "rpg.h"

void put_drop(bf_t *buffer, drop_t drop)
{
    if (drop.animation) return;
    for (int e = 0; e < drop.dim.y; e++)
        for (int j = 0; j < drop.dim.x; j++)
            put_pixel(buffer, drop.pos.x + j, drop.pos.y + e, drop.color);
    return;
}