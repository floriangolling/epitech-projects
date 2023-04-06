/*
** EPITECH PROJECT, 2020
** bonus
** File description:
** info_rectangle
*/

#include "corewar_bonus.h"

int init_rectangle(rect_t *rect, sfVector2f pos, sfVector2f size)
{
    rect->shape = sfRectangleShape_create();
    if (!rect->shape) return (1);
    sfRectangleShape_setFillColor(rect->shape, ORANGE);
    sfRectangleShape_setSize(rect->shape, size);
    sfRectangleShape_setPosition(rect->shape, pos);
    return (0);
}

void display_rectangle(cw_t *cw, rect_t *rect)
{
    sfRenderWindow_drawRectangleShape(cw->window, rect->shape, NULL);
}

void destroy_rectangle(rect_t *rect)
{
    sfRectangleShape_destroy(rect->shape);
}