/*
** EPITECH PROJECT, 2020
** rpg Project
** File description:
** pause menu
*/

#include "rpg.h"

void draw_are_you_sure_window(game_t *game)
{
    drawSprite(WINDOW, game->menu[PAUSE_MENU].ui_scene[PM_SURE_UI].sprite,
        NULL);
    for (int i = 3; i < 5; ++i) {
        if (game->menu[PAUSE_MENU].buttons[i].is_hover)
            drawSprite(WINDOW, game->menu[PAUSE_MENU].buttons[i + 5].sprite,
                NULL);
        else
            drawSprite(WINDOW, game->menu[PAUSE_MENU].buttons[i].sprite,
                NULL);
    }
    return;
}

void draw_pause_menu(game_t *game)
{
    drawSprite(WINDOW, game->menu[PAUSE_MENU].ui_scene[PM_BLACK_BG].sprite,
        NULL);
    drawSprite(WINDOW, game->menu[PAUSE_MENU].ui_scene[BACK].sprite, NULL);
    for (int i = 0; i < 3; ++i) {
        if (game->menu[PAUSE_MENU].buttons[i].is_hover)
            drawSprite(WINDOW, game->menu[PAUSE_MENU].buttons[i + 5].sprite,
                NULL);
        else
            drawSprite(WINDOW, game->menu[PAUSE_MENU].buttons[i].sprite, NULL);
    }
    if (game->menu[PAUSE_MENU].ui_scene[PM_SURE_UI].is_display)
        draw_are_you_sure_window(game);
    return;
}