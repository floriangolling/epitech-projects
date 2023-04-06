/*
** EPITECH PROJECT, 2020
** MUL_my_rpg_2019
** File description:
** cut_out_second
*/

#include "rpg.h"

void cut_out_second(game_t *ga, cut_t *cut, shift_t *shift)
{
    sfMutex_lock(cut->l_wait);
    cut->wait = 0;
    sfMutex_unlock(cut->l_wait);
    shift->pos = (sfVector2f){0, 0};
    if (ga->fbf.active[RAIN])
        shift->color = (sfColor){0, 0, 0, 100};
    else
        shift->color = (sfColor){0, 0, 0, 0};
    sfMutex_lock(cut->l_wait);
    while (!cut->wait) {
        sfMutex_unlock(cut->l_wait);
        sfSleep((sfTime){1000});
        sfMutex_lock(cut->l_wait);
    }
    sfMutex_unlock(cut->l_wait);
    return;
}