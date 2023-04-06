/*
** EPITECH PROJECT, 2020
** rpg Project
** File description:
** ui main menu
*/

#include "rpg.h"

int init_ui_main_menu(game_t *game)
{
    if (!(game->menu[MAIN_MENU].ui_scene = malloc(sizeof(elem_t))))
        return (1);
    game->menu[MAIN_MENU].ui_scene[BACK] = create_element(
        game->menu[MAIN_MENU].ui_scene[BACK], "media/main_menu/main_menu.png",
        660, 223);
    return (0);
}