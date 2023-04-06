/*
** EPITECH PROJECT, 2020
** rpg Project
** File description:
** create buttons mm
*/

#include "rpg.h"

int create_buttons_main_menu(game_t *game)
{
    game->menu[MAIN_MENU].buttons[MM_PLAY_HOV] = create_button(
        game->menu[MAIN_MENU].buttons[MM_PLAY_HOV],
        "media/main_menu/start_hov.png", 805, 327);
    game->menu[MAIN_MENU].buttons[MM_SETTINGS_HOV] = create_button(
        game->menu[MAIN_MENU].buttons[MM_SETTINGS_HOV],
        "media/main_menu/options_hov.png", 805, 493);
    game->menu[MAIN_MENU].buttons[MM_QUIT_HOV] = create_button(
        game->menu[MAIN_MENU].buttons[MM_QUIT_HOV],
        "media/main_menu/quit_hov.png", 805, 651);
    return (0);
}

int create_rectangle_mm(game_t *game, int num, int x, int y)
{
    game->menu[MAIN_MENU].rectangle[num].rect_position.x = x;
    game->menu[MAIN_MENU].rectangle[num].rect_position.y = y;
    game->menu[MAIN_MENU].rectangle[num].color = sfTransparent;
    game->menu[MAIN_MENU].rectangle[num].rect_size.x = 300;
    game->menu[MAIN_MENU].rectangle[num].rect_size.y = 105.5;
    game->menu[MAIN_MENU].rectangle[num].rect = sfRectangleShape_create();
    sfRectangleShape_setSize(game->menu[MAIN_MENU].rectangle[num].rect,
        game->menu[MAIN_MENU].rectangle[num].rect_size);
    sfRectangleShape_setFillColor(game->menu[MAIN_MENU].rectangle[num].rect,
        game->menu[MAIN_MENU].rectangle[num].color);
    sfRectangleShape_setPosition(game->menu[MAIN_MENU].rectangle[num].rect,
        game->menu[MAIN_MENU].rectangle[num].rect_position);
    game->menu[MAIN_MENU].rectangle[num].is_hover = false;
    return (0);
}

int init_button_main_menu(game_t *game)
{
    if (!(game->menu[MAIN_MENU].buttons = malloc(sizeof(button_t) * 3)))
        return (1);
    if (!(game->menu[MAIN_MENU].rectangle = malloc(sizeof(rectangle_t) * 3)))
        return (1);
    create_rectangle_mm(game, MM_PLAY, 813, 332);
    create_rectangle_mm(game, MM_SETTINGS, 815, 498);
    create_rectangle_mm(game, MM_QUIT, 815, 656);
    create_buttons_main_menu(game);
    return (0);
}