/*
** EPITECH PROJECT, 2020
** rpg Project
** File description:
** arena_events
*/

#include "rpg.h"

int arena_events(game_t *game)
{
    battle_shot(game, &game->battle);
    return (0);
}