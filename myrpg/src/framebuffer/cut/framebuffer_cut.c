/*
** EPITECH PROJECT, 2020
** MUL_my_rpg_2019
** File description:
** framebuffer_cut
*/

#include "rpg.h"

int init_cut(game_t *ga, cut_t *cut)
{
    cut->transition = 0;
    cut->ic_scene = 0;
    cut->wait = 0;
    cut->idx = 0;
    cut->shift.active = 0;
    cut->l_wait = sfMutex_create();
    cut->l_idx = sfMutex_create();
    if (!cut->l_wait || !cut->l_idx) return (1);
    return (0);
}

void (*transition[])(game_t *ga, cut_t *cut) = {
    cut_enter,
    cut_out
};

void framebuffer_cut(game_t *ga, cut_t *cut)
{
    sfMutex_lock(cut->l_idx);
    (*transition[cut->idx])(ga, cut);
    sfMutex_unlock(cut->l_idx);
    return;
}

void destroy_cut(cut_t *cut)
{
    sfMutex_destroy(cut->l_idx);
    sfMutex_destroy(cut->l_wait);
}