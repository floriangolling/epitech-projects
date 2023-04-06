/*
** EPITECH PROJECT, 2020
** rpg Project
** File description:
** mouse position settings menu
*/

#include "rpg.h"

int is_on_quit_button_settings(game_t *game)
{
    sfFloatRect rect_rect;

    rect_rect = sfRectangleShape_getGlobalBounds(
        game->menu[SETTINGS].rectangle[SM_QUIT].rect);
    game->menu[SETTINGS].rectangle[SM_QUIT].is_hover =
        sfFloatRect_contains(&(rect_rect),
        game->mouse_position.x, game->mouse_position.y);
    if (game->menu[SETTINGS].rectangle[SM_QUIT].is_hover) {
        game->menu[SETTINGS].buttons[SM_QUIT_HOV].is_hover = true;
        return (1);
    } else
        game->menu[SETTINGS].buttons[SM_QUIT_HOV].is_hover = false;
    return (0);
}

int is_on_confirm_button_settings(game_t *game)
{
    sfFloatRect rect_rect;

    rect_rect = sfRectangleShape_getGlobalBounds(
        game->menu[SETTINGS].rectangle[SM_CONFIRM].rect);
    game->menu[SETTINGS].rectangle[SM_CONFIRM].is_hover =
        sfFloatRect_contains(&(rect_rect),
        game->mouse_position.x, game->mouse_position.y);
    if (game->menu[SETTINGS].rectangle[SM_CONFIRM].is_hover) {
        game->menu[SETTINGS].buttons[SM_CONFIRM_HOV].is_hover = true;
        return (1);
    } else
        game->menu[SETTINGS].buttons[SM_CONFIRM_HOV].is_hover = false;
    return (0);
}

int is_on_off_music(game_t *game)
{
    bool is_hover = false;
    sfFloatRect rect;

    rect = sfSprite_getGlobalBounds(
        game->menu[SETTINGS].ui_scene[SM_NOTCH].sprite);
    is_hover =
        sfFloatRect_contains(
            &(rect), game->mouse_position.x, game->mouse_position.y);
    if (is_hover && MOUSE_CLICK) {
        if (game->settings.is_music_on == false) {
            game->settings.is_music_on = true;
            sfMusic_play(game->music);
        } else {
            game->settings.is_music_on = false;
            sfMusic_stop(game->music);
        }
    }
    return (0);
}