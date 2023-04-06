/*
** EPITECH PROJECT, 2020
** MUL_my_rpg_2019
** File description:
** arrow_send
*/

#include "rpg.h"

static void arrow_offset(arrow_t *arrow, sfVector2i mouse, sfVector2f p)
{
    double h_x = mouse.x - p.x;
    double h_y = mouse.y - p.y;
    double length = sqrt((h_x * h_x) + (h_y * h_y));
    double time_arrive = length / arrow->speed;

    arrow->offset.x = h_x / (time_arrive * 60);
    arrow->offset.y = h_y / (time_arrive * 60);
    return;
}

static double arrow_angle(sfVector2i mouse, sfVector2f p)
{
    double h_x = mouse.x - p.x;
    double h_y = mouse.y - p.y;
    double hyp = sqrt((h_x * h_x) + (h_y * h_y));
    double prj = sqrt((h_x * h_x));
    double cos = prj / hyp;
    double angle = acos(cos) * (180 / PI);

    if (mouse.x <= p.x && mouse.y > p.y)
        angle = (90 - angle) + 90;
    else if (mouse.x < p.x && mouse.y <= p.y)
        angle += 180;
    if (mouse.x >= p.x && mouse.y < p.y)
        angle = (90 - angle) + 270;
    return (angle);
}

static void arrow_tip(arrow_t *arrow, double angle)
{
    arrow->tip.x = cos(angle * CONVERSION) * 20;
    arrow->tip.y = sin(angle * CONVERSION) * 20;
    return;
}

void arrow_send(game_t *ga, arrow_t *arrow)
{
    sfVector2i mouse = sfMouse_getPositionRenderWindow(ga->window->window);
    sfVector2f p = sfSprite_getPosition(ga->player.character.sprite);
    double angle = 0;

    arrow->send = 1;
    arrow->pos.x = p.x + 35;
    arrow->pos.y = p.y + 30;
    angle = arrow_angle(mouse, arrow->pos);
    sfSprite_setOrigin(arrow->sprite, (sfVector2f){20, 9});
    sfSprite_setRotation(arrow->sprite, angle);
    arrow_tip(arrow, angle);
    arrow_offset(arrow, mouse, arrow->pos);
    sfSprite_setPosition(arrow->sprite, arrow->pos);
    return;
}

void arrow_enemy_send(game_t *ga, enemy_t *enemy, arrow_t *arrow)
{
    sfVector2f p = sfSprite_getPosition(ga->player.character.sprite);
    sfVector2i target = {p.x, p.y};
    double angle = 0;

    arrow->send = 1;
    target.x += 35;
    target.y += 35;
    arrow->pos.x = enemy->pos.x + 60;
    arrow->pos.y = enemy->pos.y + 26;
    angle = arrow_angle(target, arrow->pos);
    sfSprite_setOrigin(arrow->sprite, (sfVector2f){20, 9});
    sfSprite_setRotation(arrow->sprite, angle);
    arrow_tip(arrow, angle);
    arrow_offset(arrow, target, arrow->pos);
    sfSprite_setPosition(arrow->sprite, arrow->pos);
    return;
}