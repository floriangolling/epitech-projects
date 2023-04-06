/*
** EPITECH PROJECT, 2020
** rpg Project
** File description:
** leave state cause of error
*/

#include "rpg.h"

int change_state_cause_of_error(game_t *game)
{
    int check_tab = 0;

    while (game->game_state[check_tab] != 1 && game->game_state[check_tab] != 2)
        ++check_tab;
    my_putstr("Issue was found, processing redirection to main menu...\n");
    game->game_state[check_tab] = 0;
    game->game_state[MAIN_MENU] = 1;
    return (0);
}