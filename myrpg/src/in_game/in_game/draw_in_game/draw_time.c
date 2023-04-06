/*
** EPITECH PROJECT, 2020
** rpg Project
** File description:
** draw_inventory
*/

#include "rpg.h"

int init_day_night(game_t *game)
{
    game->trans = malloc(sizeof(transparent_t));
    if (game->trans == NULL)
        return (1);
    sfVector2f pos;
    pos.x = 0;
    pos.y = 0;
    game->trans->pos = pos;
    game->trans->sprite = sfSprite_create();
    game->trans->texture =
        sfTexture_createFromFile("media/white2.jpg", NULL);
    sfSprite_setTexture(game->trans->sprite, game->trans->texture, sfTrue);
    sfSprite_setPosition(game->trans->sprite, game->trans->pos);
    game->trans->state = REAL_MORNING;
    game->trans->color.r = 204;
    game->trans->color.g = 51;
    game->trans->color.b = 0;
    game->trans->color.a = 0;
    sfSprite_setColor(game->trans->sprite, game->trans->color);
    return (0);
}

void reset_color(game_t *game)
{
    game->trans->color.r = 204;
    game->trans->color.g = 51;
    game->trans->color.b = 0;
    game->trans->color.a = 0;
    sfSprite_setColor(game->trans->sprite, game->trans->color);
    return;
}

void morning(game_t *game)
{
    static double time = 0;
    sfTime seconds = sfClock_getElapsedTime(game->clock);
    time = time + seconds.microseconds / 1000000.0;
    while (time > 0.5) {
        if (game->trans->color.r < 204) {
            game->trans->color.r += 2;
            game->trans->color.g += 1;
        }
        if (game->trans->color.a > 2.5)
            game->trans->color.a -= 2.5;
        sfSprite_setColor(game->trans->sprite, game->trans->color);
        if (game->trans->color.r >= 204) {
            game->trans->state = REAL_MORNING;
            reset_color(game);
        }
        time -= 0.5;
    }
    return;
}

void real_morning(game_t *game)
{
    if (game->trans->state == DAY ||
        game->trans->state == NIGHT || game->trans->state == REAL_NIGHT)
        return (day_clock(game));
    else if (game->trans->state == MORNING)
        return (morning(game));
    static double time = 0;
    sfTime seconds = sfClock_getElapsedTime(game->clock);
    time = time + seconds.microseconds / 1000000.0;
    if (time > 30) {
        game->trans->state = DAY;
        time = 0;
    }
    return;
}