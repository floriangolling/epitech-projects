/*
** EPITECH PROJECT, 2020
** rpg Project
** File description:
** pause menu
*/

#include "rpg.h"

void destroy_pause_menu(game_t *game)
{
    for (int i = 0; i < 2; ++i) {
        sfTexture_destroy(game->menu[PAUSE_MENU].ui_scene[i].texture);
        sfSprite_destroy(game->menu[PAUSE_MENU].ui_scene[i].sprite);
    }
    for (int i = 0; i < 10; ++i) {
        sfTexture_destroy(game->menu[PAUSE_MENU].buttons[i].texture);
        sfSprite_destroy(game->menu[PAUSE_MENU].buttons[i].sprite);
    }
    return;
}