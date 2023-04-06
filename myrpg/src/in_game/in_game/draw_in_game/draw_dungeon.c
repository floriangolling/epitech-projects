/*
** EPITECH PROJECT, 2020
** rpg Project
** File description:
** draw file
*/

#include "rpg.h"

void draw_dungeon(game_t *game)
{
    drawSprite(WINDOW,
        game->game_scenes[DUNGEON_MAP].ui_scene[MAP].sprite, NULL);
    return;
}