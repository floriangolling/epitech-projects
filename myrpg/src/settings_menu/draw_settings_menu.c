/*
** EPITECH PROJECT, 2020
** rpg Project
** File description:
** draw settings menu
*/

#include "rpg.h"

int draw_settings_menu(game_t *game)
{
    drawSprite(WINDOW, game->menu[SETTINGS].ui_scene[BACK].sprite, NULL);
    drawSprite(WINDOW, game->menu[SETTINGS].ui_scene[SM_MENU].sprite, NULL);
    if (game->settings.is_music_on == true)
        drawSprite(WINDOW,
            game->menu[SETTINGS].ui_scene[SM_NOTCH].sprite, NULL);
    drawSprite(WINDOW,
        game->menu[SETTINGS].ui_scene[SM_SELECTOR].sprite, NULL);
    if (game->menu[SETTINGS].buttons[SM_QUIT_HOV].is_hover == true)
        drawSprite(WINDOW,
            game->menu[SETTINGS].buttons[SM_QUIT_HOV].sprite, NULL);
    if (game->menu[SETTINGS].buttons[SM_CONFIRM_HOV].is_hover == true)
        drawSprite(WINDOW,
            game->menu[SETTINGS].buttons[SM_CONFIRM_HOV].sprite, NULL);
    return (0);
}