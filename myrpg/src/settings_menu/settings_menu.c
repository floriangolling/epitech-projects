/*
** EPITECH PROJECT, 2020
** rpg Project
** File description:
** settings menu
*/

#include "rpg.h"

int init_settings_menu(game_t *game)
{
    if (init_ui_settings_menu(game))
        return (1);
    if (init_button_settings_menu(game))
        return (1);
    return (0);
}

int settings_menu(game_t *game)
{
    if (init_settings_menu(game))
        change_state_cause_of_error(game);
    while (game->game_state[SETTINGS] == 1) {
        draw_settings_menu(game);
        events_settings_menu(game);
        sfRenderWindow_display(game->window->window);
    }
    destroy_settings_menu(game);
    return (0);
}