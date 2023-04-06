/*
** EPITECH PROJECT, 2020
** MUL_my_rpg_2019
** File description:
** scene_handling
*/

#include "rpg.h"

int (*scene[])(game_t *game) = {
    NULL,
    scene_outside,
    scene_tavern,
    scene_seller,
    scene_cave,
    scene_dungeon,
    scene_arena_one,
    scene_arena_two,
    hitbox_pnj
};

void scene_handling(game_t *ga, cut_t *cut)
{
    if (cut->transition) {
        (*scene[cut->ic_scene])(ga);
        shield_movement(ga, 2);
        cut->transition = 0;
    }
}