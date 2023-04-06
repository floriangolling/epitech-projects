/*
** EPITECH PROJECT, 2020
** rpg Project
** File description:
** end_game
*/

#include "rpg.h"

int init_end_game(game_t *game)
{
    if (init_end_game_dialog(game))
        return (1);
    return (0);
}

int end_game(game_t *game)
{
    if (init_end_game(game))
        return (change_state_cause_of_error(game));
    sfClock_restart(game->clock);
    while (game->game_state[END_GAME] == 1) {
        sfRenderWindow_clear(WINDOW, sfBlack);
        moove_text(game);
        events_end_game(game);
        draw_end_game(game);
        sfClock_restart(game->clock);
        sfRenderWindow_display(game->window->window);
    }
    destroy_end_game(game);
    return (0);
}