/*
** EPITECH PROJECT, 2020
** rpg Project
** File description:
** pause menu
*/

#include "rpg.h"

int create_buttons_pm_hov(game_t *game)
{
    game->menu[PAUSE_MENU].buttons[PM_PLAY_HOV] = create_button(
        game->menu[PAUSE_MENU].buttons[PM_PLAY_HOV],
            "media/pause_menu/resume_hov.png", 801, 366);
    game->menu[PAUSE_MENU].buttons[PM_MM_HOV] = create_button(
        game->menu[PAUSE_MENU].buttons[PM_MM_HOV],
            "media/pause_menu/mm_hov.png", 801, 532);
    game->menu[PAUSE_MENU].buttons[PM_QUIT_HOV] = create_button(
        game->menu[PAUSE_MENU].buttons[PM_QUIT_HOV],
            "media/pause_menu/quit_hov.png", 801, 690);
    game->menu[PAUSE_MENU].buttons[PM_YES_HOV] = create_button(
        game->menu[PAUSE_MENU].buttons[PM_YES_HOV],
            "media/pause_menu/yes_hov.png", 974, 611);
    game->menu[PAUSE_MENU].buttons[PM_NO_HOV] = create_button(
        game->menu[PAUSE_MENU].buttons[PM_NO_HOV],
            "media/pause_menu/no_hov.png", 734, 611);
    return (0);
}

int create_buttons_pm(game_t *game)
{
    game->menu[PAUSE_MENU].buttons[PM_PLAY] = create_button(
        game->menu[PAUSE_MENU].buttons[PM_PLAY],
            "media/pause_menu/resume.png", 808, 366);
    game->menu[PAUSE_MENU].buttons[PM_MM] = create_button(
        game->menu[PAUSE_MENU].buttons[PM_MM],
            "media/pause_menu/mm.png", 808, 532);
    game->menu[PAUSE_MENU].buttons[PM_QUIT] = create_button(
        game->menu[PAUSE_MENU].buttons[PM_QUIT],
            "media/pause_menu/quit.png", 808, 690);
    game->menu[PAUSE_MENU].buttons[PM_YES] = create_button(
        game->menu[PAUSE_MENU].buttons[PM_YES],
            "media/pause_menu/yes.png", 974, 611);
    game->menu[PAUSE_MENU].buttons[PM_NO] = create_button(
        game->menu[PAUSE_MENU].buttons[PM_NO],
            "media/pause_menu/no.png", 734, 611);
    return (0);
}

int init_button_pause_menu(game_t *game)
{
    if (!(game->menu[PAUSE_MENU].buttons = malloc(sizeof(button_t) * 10)))
        return (1);
    create_buttons_pm(game);
    create_buttons_pm_hov(game);
    return (0);
}