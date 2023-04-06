/*
** EPITECH PROJECT, 2020
** MUL_my_rpg_2019
** File description:
** battle_arrow
*/

#include "rpg.h"

int create_arrow(arrow_t *arrow, char *path, float speed)
{
    arrow->send = 0;
    arrow->speed = speed;
    arrow->pos = (sfVector2f){0, 0};
    arrow->offset = (sfVector2f){0, 0};
    arrow->tip = (sfVector2f){0, 0};
    arrow->sprite = sfSprite_create();
    arrow->texture = sfTexture_createFromFile(path, NULL);
    if (!arrow->sprite || !arrow->texture) return (1);
    sfSprite_setTexture(arrow->sprite, arrow->texture, sfFalse);
    return (0);
}

void arrow_display(game_t *ga, arrow_t *arrow)
{
    if (!arrow->send) return;
    arrow->pos.x += arrow->offset.x;
    arrow->pos.y += arrow->offset.y;
    arrow_hit(ga, arrow);
    sfSprite_move(arrow->sprite, arrow->offset);
    sfRenderWindow_drawSprite(ga->window->window, arrow->sprite, NULL);
    return;
}

void arrow_destroy(arrow_t *arrow)
{
    sfSprite_destroy(arrow->sprite);
    sfTexture_destroy(arrow->texture);
    return;
}