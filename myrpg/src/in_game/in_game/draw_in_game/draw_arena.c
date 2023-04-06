/*
** EPITECH PROJECT, 2020
** rpg Project
** File description:
** draw_battle_scene
*/

#include "rpg.h"

void draw_arena(game_t *game)
{
    drawSprite(WINDOW, game->game_scenes[ARENA_MAP].ui_scene[MAP].sprite, NULL);
    battle_display(game, &game->battle);
    return;
}