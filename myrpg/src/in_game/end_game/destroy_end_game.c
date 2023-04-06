/*
** EPITECH PROJECT, 2020
** rpg Project
** File description:
** destroy_end_game
*/

#include "rpg.h"

void destroy_end_game(game_t *game)
{
    sfFont_destroy(game->game_scenes[END_GAME_SCENE].texts.font);
    sfText_destroy(game->game_scenes[END_GAME_SCENE].texts.string);
    return;
}