/*
** EPITECH PROJECT, 2020
** rpg Project
** File description:
** draw_end_game
*/

#include "rpg.h"

void draw_end_game(game_t *game)
{
    sfRenderWindow_drawText(WINDOW,
        game->game_scenes[END_GAME_SCENE].texts.string, NULL);
    return;
}