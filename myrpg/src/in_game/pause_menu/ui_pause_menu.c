/*
** EPITECH PROJECT, 2020
** rpg Project
** File description:
** pause menu
*/

#include "rpg.h"

int blk_pm(game_t *game)
{
    sfColor color;

    game->menu[PAUSE_MENU].ui_scene[PM_BLACK_BG] = create_element(
        game->menu[PAUSE_MENU].ui_scene[PM_BLACK_BG],
        "media/pause_menu/seventy_op.png", 0, 0);
    color = sfColor_fromRGBA(0, 0, 0, 20);
    sfSprite_setColor(game->menu[PAUSE_MENU].ui_scene[PM_BLACK_BG].sprite,
        color);
    return (0);
}

int init_ui_pause_menu(game_t *game)
{
    if (!(game->menu[PAUSE_MENU].ui_scene = malloc(sizeof(elem_t) * 3)))
        return (1);
    game->menu[PAUSE_MENU].ui_scene[BACK] = create_element(
        game->menu[PAUSE_MENU].ui_scene[BACK],
        "media/pause_menu/pause_menu_ui.png", 660, 225);
    game->menu[PAUSE_MENU].ui_scene[PM_SURE_UI] = create_element(
        game->menu[PAUSE_MENU].ui_scene[PM_SURE_UI],
        "media/pause_menu/sure_ui.png", 707, 419);
    blk_pm(game);
    return (0);
}