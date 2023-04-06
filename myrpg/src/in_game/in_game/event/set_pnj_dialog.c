/*
** EPITECH PROJECT, 2020
** rpg Project
** File description:
** set_pnj_dialog
*/

#include "rpg.h"

int outside_dialog(game_t *game)
{
    if (game->game_scenes[OUTSIDE_MAP].dialog_state == 0)
        return (0);
    if (game->game_scenes[TAVERN_MAP].dial_activated == true &&
        game->game_scenes[OUTSIDE_MAP].dialog_state == 2)
        game->game_scenes[OUTSIDE_MAP].dialog_state = 0;
    else {
        game->game_scenes[OUTSIDE_MAP].dialog_state = 2;
        game->game_scenes[TAVERN_MAP].dialog_state = 1;
    }
    return (0);
}

int tavern_dialog(game_t *game)
{
    if (game->game_scenes[TAVERN_MAP].dialog_state == 0)
        return (0);
    if (game->game_scenes[TAVERN_MAP].dialog_state == 2 &&
        game->game_scenes[TAVERN_MAP].dial_activated == true) {
        game->game_scenes[TAVERN_MAP].dialog_state = 0;
        game->game_scenes[SELLER_MAP].dialog_state = 1;
        game->player.level++;
    }
    return (0);
}

int seller_dialog(game_t *game)
{
    if (game->game_scenes[SELLER_MAP].dialog_state == 0)
        return (0);
    if (game->game_scenes[CAVE_MAP].dial_activated == true &&
        game->game_scenes[SELLER_MAP].dialog_state == 2)
        game->game_scenes[SELLER_MAP].dialog_state = 0;
    if (game->game_scenes[SELLER_MAP].dial_activated == true &&
        game->game_scenes[SELLER_MAP].dialog_state == 1) {
        game->game_scenes[OUTSIDE_MAP].ui_scene[1].is_display = true;
    }
    if (game->game_scenes[SELLER_MAP].dialog_state == 2 &&
        game->game_scenes[SELLER_MAP].dial_activated == true) {
        game->game_scenes[CAVE_MAP].dialog_state = 1;
        game->player.level++;
    }
    return (0);
}

int cave_dialog(game_t *game)
{
    if (game->game_scenes[SELLER_MAP].dialog_state == 2)
        game->game_scenes[CAVE_MAP].dialog_state = 1;
    if (game->game_scenes[CAVE_MAP].dialog_state == 1 &&
        game->game_scenes[CAVE_MAP].dial_activated == true) {
        game->game_scenes[CAVE_MAP].dialog_state = 2;
        game->player.level++;
        set_power(game);
    }
    return (0);
}

int choose_pnj_dialog(game_t *game)
{
    if (game->player.is_on_scene == DUNGEON_MAP ||
        game->player.is_on_scene == ARENA_MAP ||
        game->game_scenes[game->player.is_on_scene].dial_activated == false)
        return (0);
    outside_dialog(game);
    tavern_dialog(game);
    seller_dialog(game);
    cave_dialog(game);
    return (0);
}