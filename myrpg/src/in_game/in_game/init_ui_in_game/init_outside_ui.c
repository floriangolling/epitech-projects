/*
** EPITECH PROJECT, 2020
** defender project
** File description:
** init outside
*/

#include "rpg.h"

int init_ui_outside(game_t *game)
{
    if (!(game->game_scenes[OUTSIDE_MAP].ui_scene = malloc(sizeof(elem_t) * 3)))
        return (1);
    game->game_scenes[OUTSIDE_MAP].ui_scene[MAP] = create_element(
        game->game_scenes[OUTSIDE_MAP].ui_scene[MAP], "media/game/outside.png",
        -48, -48);
    game->game_scenes[OUTSIDE_MAP].ui_scene[2] = create_element(
        game->game_scenes[OUTSIDE_MAP].ui_scene[2],
        "media/game/outside_event.png", -48, -48);
    if (init_day_night(game) == 1)
        return (1);
    game->game_scenes[OUTSIDE_MAP].ui_scene[1] = create_element(
        game->game_scenes[OUTSIDE_MAP].ui_scene[1],
        "media/inventory/seller_shield.png", 1231, 1300);
    game->game_scenes[OUTSIDE_MAP].ui_scene[1].is_display = false;
    return (0);
}