/*
** EPITECH PROJECT, 2020
** defender project
** File description:
** seller pnj
*/

#include "rpg.h"

int init_seller_pnj(game_t *game)
{
    if (!(game->game_scenes[SELLER_MAP].pnj = malloc(sizeof(elem_t) * 2)))
        return (1);
    game->game_scenes[SELLER_MAP].pnj[PNJ_F] = create_element(
        game->game_scenes[SELLER_MAP].pnj[PNJ_F],
        "media/pnj/seller_pnj.png", 1520, 671);
    game->game_scenes[SELLER_MAP].pnj[PNJ_S] = create_element(
        game->game_scenes[SELLER_MAP].pnj[PNJ_S],
        "media/pnj/w_seller.png", 910, 370);
    game->game_scenes[SELLER_MAP].dialog_state = 0;
    game->game_scenes[SELLER_MAP].dial_activated = false;
    return (0);
}