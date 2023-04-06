/*
** EPITECH PROJECT, 2020
** defender project
** File description:
** init dungeon
*/

#include "rpg.h"

int init_ui_dungeon(game_t *game)
{
    if (!(game->game_scenes[DUNGEON_MAP].ui_scene = malloc(sizeof(elem_t))))
        return (1);
    game->game_scenes[DUNGEON_MAP].ui_scene[MAP] = create_element(
        game->game_scenes[DUNGEON_MAP].ui_scene[MAP], "media/game/dungeon.png",
        200, -825);
    return (0);
}