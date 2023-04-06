/*
** EPITECH PROJECT, 2020
** MUL_my_rpg_2019
** File description:
** cut_out
*/

#include "rpg.h"

static void create_cut(game_t *ga, cut_t *cut, shift_t *shift)
{
    shift->active = 2;
    shift->dim.x = ga->fbf.w.x;
    shift->dim.y = 6;
    shift->pos = (sfVector2f){0, 0};
    shift->color = (sfColor){0, 0, 0, 255};
    return;
}

static void put_band(game_t *ga, shift_t *shift, int e, int step)
{
    if ((e / step) % 2)
        for (int j = 0; j < shift->dim.y; ++j)
            put_pixel(&ga->fbf.buffer, shift->pos.x + e, shift->pos.y + j,
            shift->color);
    else
        for (int j = 0; j < shift->dim.y; ++j) {
            put_pixel(&ga->fbf.buffer, shift->pos.x + e,
            ga->fbf.w.y - shift->pos.y - j, shift->color);
        }
    return;
}

static void put_cut(game_t *ga, shift_t *shift)
{
    int step = ga->fbf.w.x / 12;

    for (int e = 0; e < shift->dim.x; ++e)
        put_band(ga, shift, e, step);
    return;
}

static void inc_cut(game_t *ga, cut_t *cut, shift_t *shift)
{
    static int reach = 0;

    shift->pos.y += 6;
    if (shift->pos.y > ga->fbf.w.y + 20 && reach == 0) {
        cut_out_second(ga, cut, shift);
        ++reach;
    } else if (shift->pos.y > ga->fbf.w.y && reach == 1) {
        sfMutex_lock(ga->fbf._s.l_activate);
        ga->fbf.active[CUT] = 0;
        sfMutex_unlock(ga->fbf._s.l_activate);
        sfMutex_lock(cut->l_wait);
        cut->wait = 0;
        sfMutex_unlock(cut->l_wait);
        reach = 0;
        shift->active = 0;
    }
    return;
}

void cut_out(game_t *ga, cut_t *cut)
{
    if (!cut->shift.active)
        create_cut(ga, cut, &cut->shift);
    put_cut(ga, &cut->shift);
    inc_cut(ga, cut, &cut->shift);
    return;
}

