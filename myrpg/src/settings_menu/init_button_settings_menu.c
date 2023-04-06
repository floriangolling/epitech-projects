/*
** EPITECH PROJECT, 2020
** rpg Project
** File description:
** init button
*/

#include "rpg.h"

int create_rectangle_gen_settings(game_t *game, int num, sfVector2i position,
    sfVector2i size)
{
    game->menu[SETTINGS].rectangle[num].rect_position.x = position.x;
    game->menu[SETTINGS].rectangle[num].rect_position.y = position.y;
    game->menu[SETTINGS].rectangle[num].color = sfTransparent;
    game->menu[SETTINGS].rectangle[num].rect_size.x = size.x;
    game->menu[SETTINGS].rectangle[num].rect_size.y = size.y;
    game->menu[SETTINGS].rectangle[num].rect = sfRectangleShape_create();
    sfRectangleShape_setSize(game->menu[SETTINGS].rectangle[num].rect,
        game->menu[SETTINGS].rectangle[num].rect_size);
    sfRectangleShape_setFillColor(game->menu[SETTINGS].rectangle[num].rect,
        game->menu[SETTINGS].rectangle[num].color);
    sfRectangleShape_setPosition(game->menu[SETTINGS].rectangle[num].rect,
        game->menu[SETTINGS].rectangle[num].rect_position);
    game->menu[SETTINGS].rectangle[num].is_hover = false;
    return (0);
}

int create_rectangle_settings_menu(game_t *game)
{
    sfVector2i position;
    sfVector2i size;

    position.y = 230;
    position.x = 1170;
    size.y = 85;
    size.x = 85;
    create_rectangle_gen_settings(game, SM_QUIT, position, size);
    position.y = 710;
    position.x = 815;
    size.y = 95;
    size.x = 300;
    create_rectangle_gen_settings(game, SM_CONFIRM, position, size);
    return (0);
}

int init_button_settings_menu(game_t *game)
{
    if (!(game->menu[SETTINGS].buttons = malloc(sizeof(button_t) * 2)))
        return (1);
    if (!(game->menu[SETTINGS].rectangle = malloc(sizeof(rectangle_t) * 2)))
        return (1);
    create_rectangle_settings_menu(game);
    game->menu[SETTINGS].buttons[SM_QUIT_HOV] = create_button(
        game->menu[SETTINGS].buttons[SM_QUIT_HOV],
        "media/settings_menu/quit_button.png", 1171, 233);
        game->menu[SETTINGS].buttons[SM_CONFIRM_HOV] = create_button(
    game->menu[SETTINGS].buttons[SM_CONFIRM_HOV],
        "media/settings_menu/confirm_hover.png", 810, 699);
    return (0);
}