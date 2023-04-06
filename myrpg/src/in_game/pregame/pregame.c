/*
** EPITECH PROJECT, 2020
** defender project
** File description:
** pregame
*/

#include "rpg.h"

int init_pregame(game_t *game)
{
    if (init_ui_pregame(game))
        return (1);
    if (init_button_pregame(game))
        return (1);
    return (0);
}

int pregame(game_t *game)
{
    if (init_pregame(game))
        change_state_cause_of_error(game);
    while (game->game_state[PREGAME] == 1) {
        draw_pregame(game);
        events_pregame(game);
        sfRenderWindow_display(game->window->window);
    }
    destroy_pregame(game);
    return (0);
}