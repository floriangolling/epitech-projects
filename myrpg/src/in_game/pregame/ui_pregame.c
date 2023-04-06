/*
** EPITECH PROJECT, 2020
** defender project
** File description:
** ui pregame
*/

#include "rpg.h"

int init_ui_pregame(game_t *game)
{
    if (!(game->menu[PREGAME].ui_scene = malloc(sizeof(elem_t) * 2)))
        return (1);
    game->menu[PREGAME].ui_scene[BACK] = create_element(
        game->menu[PREGAME].ui_scene[BACK], "media/pregame/back_pregame.jpg",
        0, 0);
    game->menu[PREGAME].ui_scene[PREGAME_UI] = create_element(
        game->menu[PREGAME].ui_scene[PREGAME_UI],
        "media/pregame/ui_pregame.png", 584, 232);
    return (0);
}