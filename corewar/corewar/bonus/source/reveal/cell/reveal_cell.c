/*
** EPITECH PROJECT, 2020
** bonus
** File description:
** reveal_cell
*/

#include "corewar_bonus.h"

sfColor warrior_color[] = {
    {220, 220, 220, 255},
    {237, 24, 107, 255},
    {133, 207, 180, 255},
    {255, 179, 18, 255},
    {246, 224, 174, 255}
};

char *cell_hex(cell_t *cell, u_int8_t nb)
{
    int mod = 0;
    int e = 0;

    for (e = 0; nb > 0; e++) {
        mod = nb % HEX_LEN;
        nb /= HEX_LEN;
        cell->value[e] = HEX[mod];
    }
    for (; e < 2; ++e)
        cell->value[e] = '0';
    cell->value[e] = '\0';
    my_revstr(cell->value);
    return (cell->value);
}

int init_cell(cell_t *cell, sfVector2f pos, u_int8_t value, u_int8_t warrior)
{
    cell->text = sfText_create();
    if (!cell->text) return (error("CELL: failed to create\n"));
    cell->pos = pos;
    sfText_setString(cell->text, cell_hex(cell, value));
    sfText_setFont(cell->text, cell->font);
    sfText_setCharacterSize(cell->text, 17);
    sfText_setFillColor(cell->text, warrior_color[warrior]);
    sfText_setOutlineThickness(cell->text, 1.5);
    sfText_setOutlineColor(cell->text, sfBlack);
    sfText_setPosition(cell->text, cell->pos);
    return (0);
}

void cell_display(reveal_t *rv, cell_t *cell, u_int8_t value)
{
    sfText_setString(cell->text, cell_hex(cell, value));
    sfRenderWindow_drawText(rv->cw.window, cell->text, NULL);
}

void destroy_cell(cell_t *cell)
{
    sfText_destroy(cell->text);
}