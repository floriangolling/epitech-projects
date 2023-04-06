/*
** EPITECH PROJECT, 2020
** MUL_my_rpg_2019
** File description:
** init_intro
*/

#include "rpg.h"

bool init_intro(intro_t *intro)
{
    if (!(intro->tilesheet = sfSprite_create())) return (false);
    if (!(intro->texture = malloc(sizeof(sfTexture *) * 8))) return (false);
    intro->time = (sfTime){0};
    intro->seconds = 0;
    intro->rect = (sfIntRect){0, 0, 960, 540};
    intro->inc = (sfVector2i){0, 0};
    return (true);
}

void init_sprite(intro_t *intro)
{
    char *file_texture[] = {P1, P2, P3, P4, P5, P6, P7, P8};

    for (int i = 0; i != 8; i++)
        intro->texture[i] = sfTexture_createFromFile(file_texture[i], false);
    sfSprite_setTexture(intro->tilesheet, intro->texture[0], false);
    sfSprite_setTextureRect(intro->tilesheet, intro->rect);
    sfSprite_setScale(intro->tilesheet, (sfVector2f){2, 2});
}