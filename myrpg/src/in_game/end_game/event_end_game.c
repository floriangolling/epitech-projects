/*
** EPITECH PROJECT, 2020
** rpg Project
** File description:
** event_end_game
*/

#include "rpg.h"

int moove_text(game_t *game)
{
    static double time;

    if (game->game_scenes[END_GAME_SCENE].texts.place_string.y <= -1580)
        return (0);
    game->time = sfClock_getElapsedTime(game->clock);
    time = time + game->time.microseconds / 1000000.0;
    if (time >= 0.03) {
        time -= 0.03;
        game->game_scenes[END_GAME_SCENE].texts.place_string.y -= 5;
        sfText_setPosition(game->game_scenes[END_GAME_SCENE].texts.string,
            game->game_scenes[END_GAME_SCENE].texts.place_string);
    }
    return (0);
}

int events_end_game(game_t *game)
{
    while (sfRenderWindow_pollEvent(game->window->window,
        &(game->window->event))) {
        if (game->window->event.type == sfEvtClosed) {
            sfRenderWindow_close(game->window->window);
            game->game_state[END_GAME] = 0;
            game->game_is_up = 0;
        }
        if (game->window->event.type == sfEvtKeyReleased &&
            game->window->event.key.code == sfKeyEnter &&
            game->game_scenes[END_GAME_SCENE].texts.place_string.y <= -1570) {
            game->game_state[END_GAME] = 0;
            game->game_is_up = 0;
        }
    }
    return (0);
}