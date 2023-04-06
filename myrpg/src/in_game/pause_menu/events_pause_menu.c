/*
** EPITECH PROJECT, 2020
** rpg Project
** File description:
** pause menu
*/

#include "rpg.h"

int do_pm_actions(game_t *game, int i, int wich_one)
{
    switch (i) {
        case 0:
            game->game_state[PAUSE_MENU] = 0;
            break;
        case 1:
            game->menu[PAUSE_MENU].ui_scene[PM_SURE_UI].is_display = true;
            wich_one = 1;
            break;
        case 2:
            game->menu[PAUSE_MENU].ui_scene[PM_SURE_UI].is_display = true;
            wich_one = 2;
            break;
    }
    return (wich_one);
}

int analyse_mouse_actions_pause_menu(game_t *game, int wich_one)
{
    sfFloatRect rect_rect;

    for (int i = 0; i < 3; ++i) {
        rect_rect = sfSprite_getGlobalBounds(
            game->menu[PAUSE_MENU].buttons[i].sprite);
        game->menu[PAUSE_MENU].buttons[i].is_hover =
            sfFloatRect_contains(&(rect_rect), MOUSEX, MOUSEY);
        if (game->menu[PAUSE_MENU].buttons[i].is_hover && MOUSE_CLICK)
            wich_one = do_pm_actions(game, i, wich_one);
    }
    return (wich_one);
}

int do_ays_actions(game_t *game, int i, int wich_one)
{
    switch (i) {
        case 3:
            break;
        case 4:
            game->menu[PAUSE_MENU].ui_scene[PM_SURE_UI].is_display = false;
            return (0);
    }
    if (wich_one == 1) {
        game->game_state[PAUSE_MENU] = 0;
        game->game_state[GAME] = 0;
        game->game_state[MAIN_MENU] = 1;
        return (0);
    }
    if (wich_one == 2) {
        game->game_state[PAUSE_MENU] = 0;
        game->game_state[GAME] = 0;
        game->game_is_up = 0;
    }
    return (0);
}

int are_you_sure_pm(game_t *game, int wich_one)
{
    sfFloatRect rect_rect;

    for (int i = 3; i < 5; ++i) {
        rect_rect = sfSprite_getGlobalBounds(
            game->menu[PAUSE_MENU].buttons[i].sprite);
        game->menu[PAUSE_MENU].buttons[i].is_hover =
            sfFloatRect_contains(&(rect_rect), MOUSEX, MOUSEY);
        if (game->menu[PAUSE_MENU].buttons[i].is_hover && MOUSE_CLICK)
            do_ays_actions(game, i, wich_one);
    }
    return (0);
}

int events_pause_menu(game_t *game)
{
    static int wich_one = 0;
    while (sfRenderWindow_pollEvent(game->window->window,
        &(game->window->event))) {
        if (game->window->event.type == sfEvtClosed) {
            sfRenderWindow_close(game->window->window);
            game->game_state[PAUSE_MENU] = 0;
            game->game_state[GAME] = 0;
            game->game_is_up = 0;
        }
        if (game->window->event.type == sfEvtKeyReleased &&
            game->window->event.key.code == sfKeyEscape)
            game->game_state[PAUSE_MENU] = 0;
        game->mouse_position =
            sfMouse_getPositionRenderWindow(game->window->window);
        if (!game->menu[PAUSE_MENU].ui_scene[PM_SURE_UI].is_display)
            wich_one = analyse_mouse_actions_pause_menu(game, wich_one);
        else
            are_you_sure_pm(game, wich_one);
    }
    return (0);
}