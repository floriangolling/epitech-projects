/*
** EPITECH PROJECT, 2020
** defender project
** File description:
** destroy pregame
*/

#include "rpg.h"

void destroy_pregame(game_t *game)
{
    for (int i = 0; i < 2; ++i) {
        sfTexture_destroy(game->menu[PREGAME].ui_scene[i].texture);
        sfSprite_destroy(game->menu[PREGAME].ui_scene[i].sprite);
    }
    for (int i = 0; i < 8; ++i) {
        sfTexture_destroy(game->menu[PREGAME].buttons[i].texture);
        sfSprite_destroy(game->menu[PREGAME].buttons[i].sprite);
    }
    return;
}