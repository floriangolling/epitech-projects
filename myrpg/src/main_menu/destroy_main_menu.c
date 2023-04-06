/*
** EPITECH PROJECT, 2020
** rpg Project
** File description:
** destroy mm
*/

#include "rpg.h"

void destroy_main_menu_elements(game_t *game)
{
    sfTexture_destroy(game->menu[MAIN_MENU].ui_scene[BACK].texture);
    sfSprite_destroy(game->menu[MAIN_MENU].ui_scene[BACK].sprite);
    for (int i = 0; i < 3; ++i) {
        sfTexture_destroy(game->menu[MAIN_MENU].buttons[i].texture);
        sfSprite_destroy(game->menu[MAIN_MENU].buttons[i].sprite);
        sfRectangleShape_destroy(game->menu[MAIN_MENU].rectangle[i].rect);
    }
    return;
}