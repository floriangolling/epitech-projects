/*
** EPITECH PROJECT, 2020
** rpg Project
** File description:
** draw_inventory
*/

#include "rpg.h"

void day_clock(game_t *game)
{
    static double time = 0;
    sfTime seconds = sfClock_getElapsedTime(game->clock);

    if (game->trans->state == NIGHT)
        return (night_clock(game));
    else if (game->trans->state == REAL_NIGHT)
        return (night(game));
    time = time + seconds.microseconds / 1000000.0;
    while (time > 1) {
        game->trans->color.a += 2;
        time -= 1;
        sfSprite_setColor(game->trans->sprite, game->trans->color);
    }
    if (game->trans->color.a >= 80)
        game->trans->state = NIGHT;
    return;
}

void night_clock(game_t *game)
{
    static double time = 0;
    sfTime seconds = sfClock_getElapsedTime(game->clock);
    time = time + seconds.microseconds / 1000000.0;

    while (time > 0.5) {
        if (game->trans->color.r > 4)
            game->trans->color.r -= 4;
        else if (game->trans->color.g > 2)
            game->trans->color.g -= 2;
        time -= 0.5;
        game->trans->color.a += 1;
        sfSprite_setColor(game->trans->sprite, game->trans->color);
        if (game->trans->color.r <= 4)
            game->trans->state = REAL_NIGHT;
    }
    return;
}

void night(game_t *game)
{
    static double time = 0;
    sfTime seconds = sfClock_getElapsedTime(game->clock);

    time = time + seconds.microseconds / 1000000.0;
    if (time > 30) {
        game->trans->state = MORNING;
        time = 0;
    }
    return;
}