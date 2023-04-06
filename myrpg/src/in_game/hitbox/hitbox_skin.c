/*
** EPITECH PROJECT, 2020
** MUL_my_rpg_2019
** File description:
** hitbox_skin
*/

#include "rpg.h"

int hitbox_select_skin(game_t *ga)
{
    int return_value = 0;
    switch (ga->player.type) {
        case BLOND_BOY:
            return_value = init_box(ga, &ga->hit.player, (sfVector2f)
            {868, 528}, "media/player/layer/walking_blond_boy_layer.png");
            break;
        case BROWN_BOY:
            return_value = init_box(ga, &ga->hit.player, (sfVector2f)
            {868, 528}, "media/player/layer/walking_brown_boy_layer.png");
            break;
        case BLOND_GIRL:
            return_value = init_box(ga, &ga->hit.player, (sfVector2f)
            {868, 528}, "media/player/layer/walking_blond_girl_layer.png");
            break;
        case BROWN_GIRL:
            return_value = init_box(ga, &ga->hit.player,  (sfVector2f)
            {868, 528}, "media/player/layer/walking_brown_girl_layer.png");
            break;
    }
    return (return_value);
}