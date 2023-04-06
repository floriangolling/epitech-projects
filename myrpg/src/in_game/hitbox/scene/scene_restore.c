/*
** EPITECH PROJECT, 2020
** MUL_my_rpg_2019
** File description:
** scene_restore
*/

#include "rpg.h"

void scene_restore(game_t *ga)
{
    sfMutex_lock(ga->fbf._s.l_activate);
    for (int e = 0; e < ga->fbf.nb_active; ++e)
        ga->fbf.active[e] = 0;
    ga->fbf.active[CUT] = 1;
    sfMutex_unlock(ga->fbf._s.l_activate);
    return;
}

void scene_restore_outside(game_t *ga)
{
    sfMutex_lock(ga->fbf._s.l_activate);
    ga->fbf.active[RAIN] = rand() % 100 / 70;
    ga->fbf.active[DARK] = rand() % 100 / 90;
    if (!ga->game_scenes[TAVERN_MAP].dialog_state
    && !ga->player.inventory.has_drop_shield) {
        ga->fbf.active[DARK] = 1;
        ga->fbf.active[RAIN] = 0;
    }
    ga->fbf.active[CUT] = 1;
    sfMutex_unlock(ga->fbf._s.l_activate);
    return;
}