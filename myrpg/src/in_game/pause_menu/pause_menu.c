/*
** EPITECH PROJECT, 2020
** rpg Project
** File description:
** pause menu
*/

#include "rpg.h"

bool clear_pause_menu(game_t *game, bool is_act)
{
    static double time = 0;

    game->time = sfClock_getElapsedTime(game->clock);
    time = game->time.microseconds / 1000000;
    if (time >= 1) {
        sfRenderWindow_clear(WINDOW, sfBlack);
        is_act = false;
    }
    return (is_act);
}

int init_pause_menu(game_t *game)
{
    if (init_ui_pause_menu(game))
        return (1);
    if (init_button_pause_menu(game))
        return (1);
    return (0);
}

int pause_menu(game_t *game)
{
    bool is_act = true;

    if (init_pause_menu(game))
        change_state_cause_of_error(game);
    while (game->game_state[PAUSE_MENU] == 1) {
        if (is_act == true)
            is_act = clear_pause_menu(game, is_act);
        draw_pause_menu(game);
        events_pause_menu(game);
        sfRenderWindow_display(game->window->window);
    }
    destroy_pause_menu(game);
    return (0);
}