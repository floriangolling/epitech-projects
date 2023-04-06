/*
** EPITECH PROJECT, 2020
** framebuffer
** File description:
** rain_born
*/

#include "rpg.h"

drop_t drop_born(fbf_t *fbf, int x, int y)
{
    drop_t drop;
    int add = x % 40 - 20;
    float eighty = fbf->w.y * (8.0 / 10.0);
    float step = eighty / 38;

    drop.animation = 0;
    drop.pos = (sfVector2i){x % (fbf->w.x + 100), -20};
    drop.dim = (sfVector2i){x % 2 + 1, y % 15 + 8};
    drop.speed = drop.dim.y * drop.dim.x;
    drop.color = (sfColor){50, 100 + add, 235 + add, 255};
    drop.impact = (drop.speed - 8) * step + y % (int)step + (fbf->w.y - eighty);
    return (drop);
}

void drop_reborn(fbf_t *fbf, drop_t *drop, int x, int y)
{
    int add = x % 40 - 20;
    float eighty = fbf->w.y * (8.0 / 10.0);
    float step = eighty / 38;

    drop->animation = 0;
    drop->pos = (sfVector2i){x % (fbf->w.x + 100), -20};
    drop->dim = (sfVector2i){x % 2 + 1, y % 15 + 8};
    drop->speed = drop->dim.y * drop->dim.x;
    drop->color = (sfColor){3, 100 + add, 235 + add, 255};
    drop->impact = (drop->speed - 8) * step + y % (int)step +
    (fbf->w.y - eighty);
    return;
}