/*
** EPITECH PROJECT, 2020
** defender project
** File description:
** init seller
*/

#include "rpg.h"

int init_ui_seller(game_t *game)
{
    if (!(game->game_scenes[SELLER_MAP].ui_scene = malloc(sizeof(elem_t))))
        return (1);
    game->game_scenes[SELLER_MAP].ui_scene[MAP] = create_element(
        game->game_scenes[SELLER_MAP].ui_scene[MAP], "media/game/seller.png",
        472, 0);
    return (0);
}