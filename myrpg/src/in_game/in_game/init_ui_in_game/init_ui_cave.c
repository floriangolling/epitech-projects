/*
** EPITECH PROJECT, 2020
** defender project
** File description:
** init cave
*/

#include "rpg.h"

int init_ui_cave(game_t *game)
{
    if (!(game->game_scenes[CAVE_MAP].ui_scene = malloc(sizeof(elem_t))))
        return (1);
    game->game_scenes[CAVE_MAP].ui_scene[MAP] = create_element(
    game->game_scenes[CAVE_MAP].ui_scene[MAP], "media/game/cave.png",
        435, -90);
    return (0);
}