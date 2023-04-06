/*
** EPITECH PROJECT, 2020
** MUL_my_rpg_2019
** File description:
** cut_wait
*/

#include "rpg.h"

void cut_wait_before(game_t *ga, cut_t *cut, u_int8_t idx)
{
    sfTime sleep = {1000};

    ga->fbf.cut.is_transition = true;
    ga->fbf.cut.past_transition = true;
    sfMutex_lock(cut->l_idx);
    cut->idx = idx;
    sfMutex_unlock(cut->l_idx);
    sfMutex_lock(cut->l_wait);
    cut->wait = 1;
    while (cut->wait) {
        sfMutex_unlock(cut->l_wait);
        sfSleep(sleep);
        draw_in_game(ga);
        sfRenderWindow_display(ga->window->window);
        sfMutex_lock(cut->l_wait);
    }
    sfMutex_unlock(cut->l_wait);
    return;
}

void cut_wait_after(game_t *ga, cut_t *cut)
{
    sfTime sleep = {10000};

    sfMutex_lock(cut->l_wait);
    cut->wait = 1;
    while (cut->wait) {
        sfMutex_unlock(cut->l_wait);
        sfSleep(sleep);
        draw_in_game(ga);
        sfRenderWindow_display(ga->window->window);
        sfMutex_lock(cut->l_wait);
    }
    sfMutex_unlock(cut->l_wait);
    ga->fbf.cut.is_transition = false;
    return;
}