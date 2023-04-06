/*
** EPITECH PROJECT, 2020
** rpg Project
** File description:
** main menu
*/

#include "rpg.h"

int init_main_menu(game_t *game)
{
    if (init_ui_main_menu(game))
        return (1);
    if (init_button_main_menu(game))
        return (1);
    return (0);
}

int main_menu(game_t *game)
{
    if (init_main_menu(game))
        change_state_cause_of_error(game);
    while (game->game_state[MAIN_MENU] == 1) {
        draw_main_menu(game);
        events_main_menu(game);
        sfRenderWindow_display(game->window->window);
    }
    destroy_main_menu_elements(game);
    return (0);
}