/*
** EPITECH PROJECT, 2020
** bonus
** File description:
** info_text
*/

#include "corewar_bonus.h"

int init_texta(text_t *text, u_int32_t size, sfFont *font, char *fill)
{
    text->text = sfText_create();
    if (!text->text) return (error("CELL: failed to create\n"));
    sfText_setString(text->text, fill);
    sfText_setFont(text->text, font);
    sfText_setCharacterSize(text->text, size);
    return (0);
}

int init_textb(text_t *text, sfVector2f pos, sfColor color)
{
    text->pos = pos;
    sfText_setFillColor(text->text, color);
    sfText_setPosition(text->text, text->pos);
    return (0);
}

void display_text(core_t *core, reveal_t *reveal, text_t *text)
{
    sfRenderWindow_drawText(reveal->cw.window, text->text, NULL);
}

void destroy_text(text_t *text)
{
    sfText_destroy(text->text);
}