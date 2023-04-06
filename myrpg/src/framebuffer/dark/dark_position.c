/*
** EPITECH PROJECT, 2020
** MUL_my_rpg_2019
** File description:
** dark_posistion
*/

#include "rpg.h"

void halo_position(halo_t *halo, sfVector2f p)
{
    halo->pos.x = p.x + 20;
    halo->pos.y = p.y + 30;
    return;
}
