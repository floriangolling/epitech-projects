/*
** EPITECH PROJECT, 2020
** MUL_my_rpg_2019
** File description:
** cut_seller
*/

#include "rpg.h"

static void create_cut(game_t *ga, cut_t *cut, shift_t *shift)
{
    shift->active = 2;
    shift->dim.x = 6;
    shift->dim.y = ga->fbf.w.y;
    shift->pos = (sfVector2f){0, 0};
    shift->color = (sfColor){0, 0, 0, 255};
    return;
}

static void put_band(game_t *ga, shift_t *shift, int e, int step)
{
    if ((e / step) % 2)
        for (int j = 0; j < shift->dim.x; j++)
            put_pixel(&ga->fbf.buffer, shift->pos.x + j, shift->pos.y + e,
            shift->color);
    else
        for (int j = 0; j < shift->dim.x; j++) {
            put_pixel(&ga->fbf.buffer, ga->fbf.w.x - shift->pos.x - j,
            shift->pos.y + e, shift->color);
        }
    return;
}

static void put_cut(game_t *ga, shift_t *shift)
{
    int step = ga->fbf.w.y / 8;

    for (int e = 0; e < shift->dim.y; e++)
        put_band(ga, shift, e, step);
    return;
}

static void inc_cut(game_t *ga, cut_t *cut, shift_t *shift)
{
    static int reach = 0;

    shift->pos.x += 6;
    if (shift->pos.x > ga->fbf.w.x + 20 && reach == 0) {
        sfMutex_lock(cut->l_wait);
        cut->wait = 0;
        sfMutex_unlock(cut->l_wait);
        shift->pos = (sfVector2f){0, 0};
        shift->color = (sfColor){0, 0, 0, 0};
        ++reach;
    } else if (shift->pos.x > ga->fbf.w.x && reach == 1) {
        sfMutex_lock(ga->fbf._s.l_activate);
        ga->fbf.active[CUT] = 0;
        sfMutex_unlock(ga->fbf._s.l_activate);
        sfMutex_lock(cut->l_wait);
        cut->wait = 0;
        sfMutex_unlock(cut->l_wait);
        reach = 0;
        shift->active = 0;
    }
}

void cut_enter(game_t *ga, cut_t *cut)
{
    if (!cut->shift.active)
        create_cut(ga, cut, &cut->shift);
    put_cut(ga, &cut->shift);
    inc_cut(ga, cut, &cut->shift);
    return;
}