/*
** EPITECH PROJECT, 2020
** rpg Project
** File description:
** destroy_in_game
*/

#include "rpg.h"

void destroy_ui_scenes(game_t *game)
{
    for (int i = 0; i < 6; ++i) {
        sfTexture_destroy(game->game_scenes[i].ui_scene[0].texture);
        sfSprite_destroy(game->game_scenes[i].ui_scene[0].sprite);
        if (i < 4) {
            sfTexture_destroy(game->game_scenes[i].pnj[0].texture);
            sfSprite_destroy(game->game_scenes[i].pnj[0].sprite);
            sfTexture_destroy(game->game_scenes[i].pnj[1].texture);
            sfSprite_destroy(game->game_scenes[i].pnj[1].sprite);
        }
    }
    sfTexture_destroy(game->game_scenes[OUTSIDE_MAP].ui_scene[1].texture);
    sfSprite_destroy(game->game_scenes[OUTSIDE_MAP].ui_scene[1].sprite);
    sfTexture_destroy(game->game_scenes[OUTSIDE_MAP].pnj[ENNEMY].texture);
    sfSprite_destroy(game->game_scenes[OUTSIDE_MAP].pnj[ENNEMY].sprite);
    return;
}

void destroy_inventory(game_t *game)
{
    for (int i = 0; i < 8; ++i) {
        if (i < 5)
            sfRectangleShape_destroy(game->common.inv_rectangle[i].rect);
        sfTexture_destroy(game->common.inventory_ui[i].texture);
        sfSprite_destroy(game->common.inventory_ui[i].sprite);
    }
    return;
}

void destroy_text(game_t *game)
{
    for (int i = 0; i < 4; ++i) {
        sfText_destroy(game->game_scenes[i].texts.string);
        sfFont_destroy(game->game_scenes[i].texts.font);
    }
    return;
}

void destroy_in_game(game_t *game)
{
    destroy_ui_scenes(game);
    destroy_inventory(game);
    destroy_text(game);
    return;
}