/*
** EPITECH PROJECT, 2020
** rpg Project
** File description:
** init ui
*/

#include "rpg.h"

int init_ui_settings_menu(game_t *game)
{
    if (!(game->menu[SETTINGS].ui_scene = malloc(sizeof(elem_t) * 4)))
        return (1);
    game->menu[SETTINGS].ui_scene[BACK] = create_element(
        game->menu[SETTINGS].ui_scene[BACK], "media/settings_menu/rouage.jpg",
        0, 0);
    game->menu[SETTINGS].ui_scene[SM_MENU] = create_element(
        game->menu[SETTINGS].ui_scene[SM_MENU],
        "media/settings_menu/settings_menu.png", 660, 223);
    game->menu[SETTINGS].ui_scene[SM_NOTCH] = create_element(
        game->menu[SETTINGS].ui_scene[SM_NOTCH],
        "media/settings_menu/music_selection.png", 945, 540);
    game->menu[SETTINGS].ui_scene[SM_SELECTOR] = create_element(
        game->menu[SETTINGS].ui_scene[SM_SELECTOR],
        "media/settings_menu/sound_volume.png", 945, 426);
    return (0);
}