/*
** EPITECH PROJECT, 2020
** rpg Project
** File description:
** destroy settings menu
*/

#include "rpg.h"

void destroy_settings_menu(game_t *game)
{
    for (int i = 0; i < 4; ++i) {
    sfTexture_destroy(game->menu[SETTINGS].ui_scene[i].texture);
    sfSprite_destroy(game->menu[SETTINGS].ui_scene[i].sprite);
    }
    for (int i = 0; i < 2; ++i) {
    sfTexture_destroy(game->menu[SETTINGS].buttons[i].texture);
    sfSprite_destroy(game->menu[SETTINGS].buttons[i].sprite);
    sfRectangleShape_destroy(game->menu[SETTINGS].rectangle[i].rect);
    }
    return;
}