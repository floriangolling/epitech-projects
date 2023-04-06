/*
** EPITECH PROJECT, 2020
** MUL_my_rpg_2019
** File description:
** game_event
*/

#include "rpg.h"

int event_keyboard(game_t *game)
{
    static double time = 0;

    if (game->window->event.type != sfEvtKeyPressed) {
        game->player.is_walking = 0;
        time = 0;
        return (0);
    }
    sfTime seconds = sfClock_getElapsedTime(game->clock);
    time = time + seconds.microseconds / 1000000.0;
    game->player.is_walking = 1;
    movement_activations(game, time);
    time = 0;
    return (0);
}

void movement_activations(game_t *game, double time)
{
    static sfKeyCode key[] = {sfKeyLeft, sfKeyRight, sfKeyUp, sfKeyDown};
    static void (*event[])(game_t *, double) = {
        move_left,
        move_right,
        move_up,
        move_down
        };
    for (int ic = 0; ic < 4; ++ic) {
        if (sfKeyboard_isKeyPressed(key[ic])) {
            (*event[ic])(game, time);
            shield_activation(game, ic);
        }
    }
    return;
}

void shield_activation(game_t *game, int ic)
{
    if (game->player.inventory.is_equip_shield == 1)
        shield_movement(game, ic);
    return;
}

void move_rect_player(game_t *ga)
{
    static int reverse = 1;
    if (reverse == 0)
        ga->player.character.rect.left -= 47;
    else if (reverse == 1)
        ga->player.character.rect.left += 47;
    sfSprite_setTextureRect(ga->player.character.sprite,
    ga->player.character.rect);
    if (ga->player.character.rect.left > 94) {
        reverse = 0;
        ga->player.character.rect.left -= 94;
    } else if (ga->player.character.rect.left < 0) {
        ga->player.character.rect.left = 47;
        reverse = 1;
    }
    sfSprite_setTextureRect(ga->player.character.sprite,
    ga->player.character.rect);
    sfSprite_setTextureRect(ga->player.pl_not_op.sprite,
    ga->player.character.rect);
    return;
}