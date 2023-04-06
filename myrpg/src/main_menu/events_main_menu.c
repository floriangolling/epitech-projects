/*
** EPITECH PROJECT, 2020
** rpg Project
** File description:
** events main menu
*/

#include "rpg.h"

int is_on_play_button_mm(game_t *game)
{
    sfFloatRect rect_rect;

    rect_rect = sfRectangleShape_getGlobalBounds(
        game->menu[MAIN_MENU].rectangle[MM_PLAY].rect);
    game->menu[MAIN_MENU].rectangle[MM_PLAY].is_hover =
        sfFloatRect_contains(&(rect_rect), MOUSEX, MOUSEY);
    if (game->menu[MAIN_MENU].rectangle[MM_PLAY].is_hover) {
        game->menu[MAIN_MENU].buttons[MM_PLAY_HOV].is_hover = true;
        return (1);
    } else
        game->menu[MAIN_MENU].buttons[MM_PLAY_HOV].is_hover = false;
    return (0);
}

int is_on_settings_button_mm(game_t *game)
{
    sfFloatRect rect_rect;

    rect_rect = sfRectangleShape_getGlobalBounds(
        game->menu[MAIN_MENU].rectangle[MM_SETTINGS].rect);
    game->menu[MAIN_MENU].rectangle[MM_SETTINGS].is_hover =
        sfFloatRect_contains(&(rect_rect), MOUSEX, MOUSEY);
    if (game->menu[MAIN_MENU].rectangle[MM_SETTINGS].is_hover) {
        game->menu[MAIN_MENU].buttons[MM_SETTINGS_HOV].is_hover = true;
        return (1);
    } else
        game->menu[MAIN_MENU].buttons[MM_SETTINGS_HOV].is_hover = false;
    return (0);
}

int is_on_quit_bouton_mm(game_t *game)
{
    sfFloatRect rect_rect;

    rect_rect = sfRectangleShape_getGlobalBounds(
        game->menu[MAIN_MENU].rectangle[MM_QUIT].rect);
    game->menu[MAIN_MENU].rectangle[MM_QUIT].is_hover =
        sfFloatRect_contains(&(rect_rect), MOUSEX, MOUSEY);
    if (game->menu[MAIN_MENU].rectangle[MM_QUIT].is_hover) {
        game->menu[MAIN_MENU].buttons[MM_QUIT_HOV].is_hover = true;
        return (1);
    }
    else
        game->menu[MAIN_MENU].buttons[MM_QUIT_HOV].is_hover = false;
    return (0);
}

int analyse_mouse_actions_mm(game_t *game)
{
    if (is_on_play_button_mm(game) && MOUSE_CLICK) {
        game->game_state[MAIN_MENU] = 0;
        game->game_state[PREGAME] = 1;
    }
    if (is_on_settings_button_mm(game) && MOUSE_CLICK) {
        game->game_state[MAIN_MENU] = 0;
        game->game_state[SETTINGS] = 1;
    }
    if (is_on_quit_bouton_mm(game) && MOUSE_CLICK) {
        game->game_state[MAIN_MENU] = 0;
        game->game_is_up = 0;
    }
    return (0);
}

int events_main_menu(game_t *game)
{
    while (sfRenderWindow_pollEvent(game->window->window,
        &(game->window->event))) {
        if (game->window->event.type == sfEvtClosed) {
            sfRenderWindow_close(game->window->window);
            game->game_state[MAIN_MENU] = 0;
            game->game_is_up = 0;
        }
        game->mouse_position =
            sfMouse_getPositionRenderWindow(game->window->window);
        analyse_mouse_actions_mm(game);
    }
    return (0);
}