/*
** EPITECH PROJECT, 2020
** MUL_my_rpg_2019
** File description:
** battle_end
*/

#include "rpg.h"

static void end_one(game_t *ga, battle_t *ba)
{
    if (!ba->life.nb_life) {
        ba->end = 1;
        scene_outside(ga);
        battle_destroy(ba);
        return;
    }
    for (int e = 0; e < ba->nb_enemy; ++e) {
        if (ba->enemy[e].alive)
            return;
    }
    ba->end = 1;
    ga->game_scenes[TAVERN_MAP].dialog_state = 2;
    scene_outside(ga);
    battle_destroy(ba);
    return;
}

static void end_two(game_t *ga, battle_t *ba)
{
    if (!ba->life.nb_life) {
        ba->end = 1;
        scene_dungeon(ga);
        battle_destroy(ba);
        return;
    }
    for (int e = 0; e < ba->nb_enemy; ++e) {
        if (ba->enemy[e].alive)
            return;
    }
    ba->end = 1;
    ++ba->battle;
    scene_dungeon(ga);
    battle_destroy(ba);
    return;
}

void battle_end(game_t *ga, battle_t *ba)
{
    if (ba->end) return;
    if (ba->battle == 1)
        end_one(ga, ba);
    else
        end_two(ga, ba);
    return;
}