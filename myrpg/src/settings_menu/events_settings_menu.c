/*
** EPITECH PROJECT, 2020
** rpg Project
** File description:
** events settings menu
*/

#include "rpg.h"

int modify_volume(game_t *game)
{
    float gap = 27.3;
    float volume = game->settings.music_volume;

    float x = (MOUSEX - 827);
    volume = x / gap * 10;
    if (volume <= 2)
        volume = 0;
    if (volume >= 98)
        volume = 100;
    sfMusic_setVolume(game->music, volume);
    return (0);
}

int move_volume_selector(game_t *game)
{
    if (MOUSEX < 1100 && MOUSEX > 827) {
        game->menu[SETTINGS].ui_scene[SM_SELECTOR].set_position.x =
            MOUSEX - 18;
        sfSprite_setPosition(game->menu[SETTINGS].ui_scene[SM_SELECTOR].sprite,
            game->menu[SETTINGS].ui_scene[SM_SELECTOR].set_position);
            modify_volume(game);
    }
    return (0);
}

int volume_selector(game_t *game)
{
    static bool is_hover = false;
    static bool is_changing = false;
    sfFloatRect rect;

    rect = sfSprite_getGlobalBounds(
        game->menu[SETTINGS].ui_scene[SM_SELECTOR].sprite);
    is_hover =
        sfFloatRect_contains(&(rect), MOUSEX, MOUSEY);
    if ((is_hover && MOUSE_CLICK)) {
        is_changing = true;
        sfRenderWindow_setMouseCursorVisible(game->window->window, sfFalse);
    }
    if (is_changing)
        move_volume_selector(game);
    if (MOUSE_RELEASED) {
        sfRenderWindow_setMouseCursorVisible(game->window->window, sfTrue);
        is_changing = false;
    }
    return (0);
}

int analyse_mouse_actions_settings(game_t *game)
{
    if (is_on_quit_button_settings(game) && MOUSE_CLICK) {
        game->game_state[SETTINGS] = 0;
        game->game_state[MAIN_MENU] = 1;
    }
    if (is_on_confirm_button_settings(game) && MOUSE_CLICK) {
        game->game_state[SETTINGS] = 0;
        game->game_state[MAIN_MENU] = 1;
    }
    is_on_off_music(game);
    volume_selector(game);
    return (0);
}

int events_settings_menu(game_t *game)
{
    while (sfRenderWindow_pollEvent(game->window->window,
        &(game->window->event))) {
        if (game->window->event.type == sfEvtClosed) {
            sfRenderWindow_close(game->window->window);
            game->game_state[SETTINGS] = 0;
            game->game_is_up = 0;
        }
        game->mouse_position =
            sfMouse_getPositionRenderWindow(game->window->window);
        analyse_mouse_actions_settings(game);
    }
    return (0);
}