/*
** EPITECH PROJECT, 2020
** CPE_corewar_bonus_2019
** File description:
** execute_divide_int
*/

#include "corewar_bonus.h"

void divide_in_4bytes(core_t *core, void *param, int pc, int n)
{
    int_4b *value = (int_4b *)param;

    for (int e = 3; e >= 0; --e, INC_PC(pc)) {
        core->men[pc] = (*value)[e];
        sfText_setFillColor(core->reveal.cell[pc].text, warrior_color[n]);
    }
}