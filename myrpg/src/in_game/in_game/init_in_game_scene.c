/*
** EPITECH PROJECT, 2020
** defender project
** File description:
** in game
*/

#include "rpg.h"

int init_ui_in_game(game_t *game)
{
    if (init_ui_outside(game))
        return (1);
    if (init_ui_tavern(game))
        return (1);
    if (init_ui_seller(game))
        return (1);
    if (init_ui_cave(game))
        return (1);
    if (init_ui_dungeon(game))
        return (1);
    if (init_ui_arena(game))
        return (1);
    return (0);
}

int init_pnj_in_game(game_t *game)
{
    if (init_outside_pnj(game))
        return (1);
    if (init_tavern_pnj(game))
        return (1);
    if (init_seller_pnj(game))
        return (1);
    if (init_cave_pnj(game))
        return (1);
    if (init_arena_pnj(game))
        return (1);
    for (int i = 0; i < 5; ++i)
        game->game_scenes[i].dial_activated = false;
    return (0);
}

int init_in_game_scene(game_t *game)
{
    if (!(game->game_scenes = malloc(sizeof(scene_t) * 7)))
        return (1);
    game->fbf.cut.is_transition = false;
    game->fbf.cut.past_transition = false;
    if (init_common_to_scenes(game))
        return (1);
    if (init_ui_in_game(game))
        return (1);
    if (init_pnj_in_game(game))
        return (1);
    return (0);
}