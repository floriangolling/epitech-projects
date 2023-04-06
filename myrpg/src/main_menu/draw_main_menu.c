/*
** EPITECH PROJECT, 2020
** rpg Project
** File description:
** main menu
*/

#include "rpg.h"

void draw_main_menu(game_t *game)
{
    drawSprite(WINDOW, game->window->sprite, NULL);
    drawSprite(WINDOW, game->menu[MAIN_MENU].ui_scene[BACK].sprite, NULL);
    if (game->menu[MAIN_MENU].buttons[MM_PLAY_HOV].is_hover == true)
        drawSprite(WINDOW,
            game->menu[MAIN_MENU].buttons[MM_PLAY_HOV].sprite, NULL);
    if (game->menu[MAIN_MENU].rectangle[MM_SETTINGS].is_hover == true)
        drawSprite(WINDOW,
            game->menu[MAIN_MENU].buttons[MM_SETTINGS_HOV].sprite, NULL);
    if (game->menu[MAIN_MENU].rectangle[MM_QUIT].is_hover == true)
        drawSprite(WINDOW,
            game->menu[MAIN_MENU].buttons[MM_QUIT_HOV].sprite, NULL);
    return;
}