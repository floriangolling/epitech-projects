/*
** EPITECH PROJECT, 2020
** defender project
** File description:
** init arena
*/

#include "rpg.h"

int init_ui_arena(game_t *game)
{
    if (!(game->game_scenes[ARENA_MAP].ui_scene = malloc(sizeof(elem_t))))
        return (1);
    game->game_scenes[ARENA_MAP].ui_scene[MAP] = create_element(
        game->game_scenes[ARENA_MAP].ui_scene[MAP], "media/game/arena.png",
        0, 0);
    return (0);
}