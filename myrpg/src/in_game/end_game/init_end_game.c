/*
** EPITECH PROJECT, 2020
** rpg Project
** File description:
** init_end_game
*/

#include "rpg.h"

int init_end_game_text(game_t *game)
{
    sfVector2f position;

    position.x = 710;
    position.y = 1100;

    game->game_scenes[END_GAME_SCENE].texts.place_string.x = position.x;
    game->game_scenes[END_GAME_SCENE].texts.place_string.y = position.y;
    game->game_scenes[END_GAME_SCENE].texts.string = sfText_create();
    game->game_scenes[END_GAME_SCENE].texts.font = sfFont_createFromFile(
        "media/font/DimboRegular.ttf");
    sfText_setFont(game->game_scenes[END_GAME_SCENE].texts.string,
        game->game_scenes[END_GAME_SCENE].texts.font);
    game->game_scenes[END_GAME_SCENE].texts.color =
        sfColor_fromRGB(255, 255, 255);
    sfText_setColor(game->game_scenes[END_GAME_SCENE].texts.string,
        game->game_scenes[END_GAME_SCENE].texts.color);
    sfText_setCharacterSize(game->game_scenes[END_GAME_SCENE].texts.string, 40);
    sfText_setPosition(game->game_scenes[END_GAME_SCENE].texts.string,
        position);
    return (0);
}

int init_end_game_dialog(game_t *game)
{
    game->game_scenes[END_GAME_SCENE].dialog = read_file(
        "media/end_game/end_game");
    if (game->game_scenes[END_GAME_SCENE].dialog == NULL)
        return (1);
    init_end_game_text(game);
    sfText_setString(game->game_scenes[END_GAME_SCENE].texts.string,
        game->game_scenes[END_GAME_SCENE].dialog);
    return (0);
}