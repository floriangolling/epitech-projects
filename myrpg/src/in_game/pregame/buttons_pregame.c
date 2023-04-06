/*
** EPITECH PROJECT, 2020
** defender project
** File description:
** buttons pregame
*/

#include "rpg.h"

int create_pregame_buttons(game_t *game)
{
    game->menu[PREGAME].buttons[BLOND_BOY] = create_button(
        game->menu[PREGAME].buttons[BLOND_BOY],
        "media/pregame/blond_boy.png", 715, 337);
    game->menu[PREGAME].buttons[BROWN_BOY] = create_button(
        game->menu[PREGAME].buttons[BROWN_BOY],
        "media/pregame/brown_boy.png", 1115, 590);
    game->menu[PREGAME].buttons[BLOND_GIRL] = create_button(
        game->menu[PREGAME].buttons[BLOND_GIRL],
        "media/pregame/blond_girl.png", 715, 590);
    game->menu[PREGAME].buttons[BROWN_GIRL] = create_button(
        game->menu[PREGAME].buttons[BROWN_GIRL],
        "media/pregame/red_girl.png", 1115, 337);
    return (0);
}

int create_pregame_buttons_hover(game_t *game)
{
    game->menu[PREGAME].buttons[BLBOY_HOV] = create_button(
        game->menu[PREGAME].buttons[BLBOY_HOV],
        "media/pregame/blond_boy_smiling.png", 715, 337);
    game->menu[PREGAME].buttons[BRBOY_HOV] = create_button(
        game->menu[PREGAME].buttons[BRBOY_HOV],
        "media/pregame/brown_boy_smiling.png", 1115, 590);
    game->menu[PREGAME].buttons[BLGIRL_HOV] = create_button(
        game->menu[PREGAME].buttons[BLGIRL_HOV],
        "media/pregame/blond_girl_smiling.png", 715, 590);
    game->menu[PREGAME].buttons[BRGIRL_HOV] = create_button(
        game->menu[PREGAME].buttons[BRGIRL_HOV],
        "media/pregame/red_girl_smiling.png", 1115, 337);
    return (0);
}

int init_button_pregame(game_t *game)
{
    if (!(game->menu[PREGAME].buttons = malloc(sizeof(button_t) * 8)))
        return (1);
    create_pregame_buttons(game);
    create_pregame_buttons_hover(game);
    return (0);
}