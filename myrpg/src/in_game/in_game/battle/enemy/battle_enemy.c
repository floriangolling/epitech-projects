/*
** EPITECH PROJECT, 2020
** MUL_my_rpg_2019
** File description:
** battle_enemy
*/

#include "rpg.h"

int create_enemy_elf(enemy_t *enemy, sfVector2f pos)
{
    enemy->alive = 1;
    enemy->animate = 0;
    enemy->pos = pos;
    enemy->move = (sfVector2i){0, 0};
    enemy->sprite = sfSprite_create();
    enemy->rect = (sfIntRect){532, 0, 76, 52};
    enemy->saveleft = enemy->rect.left;
    enemy->texture = sfTexture_createFromFile
    ("media/enemy/elf/elf_enemy.png", NULL);
    if (create_arrow(&enemy->arrow, "media/battle/arrow_enemy.png", 170))
        return (1);
    if (!enemy->sprite || !enemy->texture) return (1);
    sfSprite_setTexture(enemy->sprite, enemy->texture, sfTrue);
    sfSprite_setTextureRect(enemy->sprite, enemy->rect);
    sfSprite_setPosition(enemy->sprite, enemy->pos);
    return (0);
}

int create_enemy_woman(enemy_t *enemy, sfVector2f pos)
{
    enemy->alive = 1;
    enemy->animate = 0;
    enemy->pos = pos;
    enemy->move = (sfVector2i){0, 0};
    enemy->sprite = sfSprite_create();
    enemy->rect = (sfIntRect){648, 0, 72, 55};
    enemy->saveleft = enemy->rect.left;
    enemy->texture = sfTexture_createFromFile
    ("media/enemy/woman/woman_enemy.png", NULL);
    if (create_arrow(&enemy->arrow, "media/battle/arrow_enemy2.png", 220))
        return (1);
    if (!enemy->sprite || !enemy->texture) return (1);
    sfSprite_setTexture(enemy->sprite, enemy->texture, sfTrue);
    sfSprite_setTextureRect(enemy->sprite, enemy->rect);
    sfSprite_setPosition(enemy->sprite, enemy->pos);
    return (0);
}

void enemy_display(game_t *ga, enemy_t *enemy)
{
    if (!enemy->alive) return;
    enemy_animate(enemy);
    enemy_extremity(ga, &ga->battle, enemy);
    enemy_dodge(ga, &ga->battle, enemy);
    enemy_move(ga, &ga->battle, enemy);
    sfRenderWindow_drawSprite(ga->window->window, enemy->sprite, NULL);
    arrow_display(ga, &enemy->arrow);
    return;
}

void enemy_destroy(enemy_t *enemy)
{
    sfTexture_destroy(enemy->texture);
    sfSprite_destroy(enemy->sprite);
    arrow_destroy(&enemy->arrow);
    return;
}