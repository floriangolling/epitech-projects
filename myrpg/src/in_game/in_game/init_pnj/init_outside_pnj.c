/*
** EPITECH PROJECT, 2020
** defender project
** File description:
** outside pnj
*/

#include "rpg.h"

int init_outside_pnj(game_t *game)
{
    if (!(game->game_scenes[OUTSIDE_MAP].pnj = malloc(sizeof(elem_t) * 3)))
        return (1);
    game->game_scenes[OUTSIDE_MAP].pnj[PNJ_F] = create_element(
        game->game_scenes[OUTSIDE_MAP].pnj[PNJ_F],
        "media/pnj/outside_pnj.png", 1520, 671);
    game->game_scenes[OUTSIDE_MAP].pnj[PNJ_S] = create_element(
        game->game_scenes[OUTSIDE_MAP].pnj[PNJ_S],
        "media/pnj/w_outside.png", 580, 480);
    game->game_scenes[OUTSIDE_MAP].dialog =
        read_file("media/pnj/outside_dialog");
    if (game->game_scenes[OUTSIDE_MAP].dialog == NULL)
        return (1);
    game->game_scenes[OUTSIDE_MAP].pnj[ENNEMY] = create_element(
        game->game_scenes[OUTSIDE_MAP].pnj[ENNEMY],
        "media/enemy/elf/elf_transparent.png", 2005, 1165);
    game->game_scenes[OUTSIDE_MAP].dialog_state = 1;
    game->game_scenes[OUTSIDE_MAP].dial_activated = false;
    return (0);
}