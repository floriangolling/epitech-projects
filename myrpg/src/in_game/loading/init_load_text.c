/*
** EPITECH PROJECT, 2020
** rpg Project
** File description:
** init_load_text
*/

#include "rpg.h"

int create_loading_text(game_t *game)
{
    sfVector2f position;

    position.x = 910;
    position.y = 500;
    game->loading.text.place_string.x = position.x;
    game->loading.text.place_string.y = position.y;
    game->loading.text.string = sfText_create();
    game->loading.text.font = sfFont_createFromFile(
        "media/font/DimboRegular.ttf");
    sfText_setFont(game->loading.text.string, game->loading.text.font);
    game->loading.text.color = sfColor_fromRGB(255, 255, 255);
    sfText_setColor(game->loading.text.string, game->loading.text.color);
    sfText_setCharacterSize(game->loading.text.string, 40);
    sfText_setPosition(game->loading.text.string, position);
    return (0);
}

int init_text_loading(game_t *game)
{
    game->loading.loading_tab = malloc(sizeof(char *) * 5);
    if (game->loading.loading_tab == NULL)
        return (1);
    game->loading.loading_tab[0] = "Loading";
    game->loading.loading_tab[1] = "Loading.";
    game->loading.loading_tab[2] = "Loading..";
    game->loading.loading_tab[3] = "Loading...";
    game->loading.loading_tab[4] = NULL;
    create_loading_text(game);
    return (0);
}