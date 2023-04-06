/*
** EPITECH PROJECT, 2020
** MUL_my_rpg_2019
** File description:
** game_event
*/

#include "rpg.h"

int tavern_events(game_t *game)
{
    if (game->game_scenes[TAVERN_MAP].dialog_state == 1) {
        game->game_scenes[TAVERN_MAP].dialog =
            read_file("media/pnj/tavern_dialog");
    } else if (game->game_scenes[TAVERN_MAP].dialog_state == 2) {
        game->game_scenes[TAVERN_MAP].dialog =
            read_file("media/pnj/tavern_dialog_next");
    } else {
        game->game_scenes[TAVERN_MAP].dialog =
            read_file("media/pnj/idle_dialog");
    }
    if (game->game_scenes[TAVERN_MAP].dialog == NULL)
        return (1);
    return (0);
}