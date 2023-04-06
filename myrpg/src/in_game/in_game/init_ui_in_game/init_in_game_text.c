/*
** EPITECH PROJECT, 2020
** rpg Project
** File description:
** init_in_game_text
*/

#include "rpg.h"

int init_in_game_text(game_t *game)
{
    sfVector2f position;

    position.x = 320;
    position.y = 837;

    for (int i = 0; i < 5; ++i) {
        game->game_scenes[i].texts.string = sfText_create();
        game->game_scenes[i].texts.font = sfFont_createFromFile(
            "media/font/DimboRegular.ttf");
        sfText_setFont(game->game_scenes[i].texts.string,
            game->game_scenes[i].texts.font);
        game->game_scenes[i].texts.color =
            sfColor_fromRGB(255, 255, 255);
        sfText_setColor(game->game_scenes[i].texts.string,
            game->game_scenes[i].texts.color);
        sfText_setCharacterSize(game->game_scenes[i].texts.string, 40);
        sfText_setPosition(game->game_scenes[i].texts.string, position);
        game->game_scenes[i].pos_in_dial = 0;
    }
    return (0);
}