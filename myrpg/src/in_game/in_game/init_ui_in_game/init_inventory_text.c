/*
** EPITECH PROJECT, 2020
** rpg Project
** File description:
** init_inventory_text
*/

#include "rpg.h"

int gen_text_inventory(game_t *game, int num, sfVector2f position, char *string)
{
    game->common.inventory_text[num].string = sfText_create();
    game->common.inventory_text[num].font = sfFont_createFromFile(
        "media/font/deli.ttf");
    sfText_setFont(game->common.inventory_text[num].string,
        game->common.inventory_text[num].font);
    game->common.inventory_text[num].color =
        sfColor_fromRGB(255, 255, 255);
    sfText_setColor(game->common.inventory_text[num].string,
        game->common.inventory_text[num].color);
    sfText_setCharacterSize(game->common.inventory_text[num].string, 25);
    sfText_setPosition(game->common.inventory_text[num].string,
        position);
    sfText_setString(game->common.inventory_text[num].string, string);
    return (0);
}

int init_inventory_text(game_t *game)
{
    sfVector2f position;
    game->player.power = 0;
    game->player.level = 0;

    game->common.inventory_text = malloc(sizeof(string_t) * 3);
    if (game->common.inventory_text == NULL)
        return (1);
    position.x = 815;
    position.y = 348;
    gen_text_inventory(game, LEVEL_NUM_TEXT, position,
        my_nbrtoarray(game->player.level));
    position.x = 720;
    position.y = 700;
    gen_text_inventory(game, POWER_WORD_TEXT, position, "Power");
    position.x = 800;
    position.y = 700;
    gen_text_inventory(game, POWER_NUM_TEXT, position,
        my_nbrtoarray(game->player.power));
    return (0);
}