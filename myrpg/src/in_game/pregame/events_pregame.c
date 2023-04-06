/*
** EPITECH PROJECT, 2020
** defender project
** File description:
** events pregame
*/

#include "rpg.h"

int analyse_mouse_actions_pregame(game_t *game)
{
    sfFloatRect rect_rect;

    for (int i = 0; i < 4; ++i) {
        rect_rect = sfSprite_getGlobalBounds(
            game->menu[PREGAME].buttons[i].sprite);
        game->menu[PREGAME].buttons[i].is_hover =
            sfFloatRect_contains(&(rect_rect), MOUSEX, MOUSEY);
    }
    return (0);
}

int events_pregame(game_t *game)
{
    while (sfRenderWindow_pollEvent(game->window->window,
        &(game->window->event))) {
        if (game->window->event.type == sfEvtClosed) {
            sfRenderWindow_close(game->window->window);
            game->game_state[PREGAME] = 0;
            game->game_is_up = 0;
        }
        game->mouse_position =
            sfMouse_getPositionRenderWindow(game->window->window);
        analyse_mouse_actions_pregame(game);
    }
    return (0);
}