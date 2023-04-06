/*
** EPITECH PROJECT, 2020
** bonus
** File description:
** info_arg
*/

#include "corewar_bonus.h"

int init_arg(core_t *core, warrior_t *w, arg_t *arg, sfVector2f pos)
{
    if (init_texta(&arg->type, 23, core->reveal.font, "arg")) return (1);
    if (init_textb(&arg->type, pos, warrior_color[0])) return (1);
    pos.x += 20;
    if (init_texta(&arg->argu, 23, core->reveal.font, "nb")) return (1);
    if (init_textb(&arg->argu, pos, warrior_color[0])) return (1);
    return (0);
}

void display_arg(core_t *core, reveal_t *reveal, arg_t *arg)
{
    display_text(core, reveal, &arg->argu);
    display_text(core, reveal, &arg->type);
}

void fill_arg(core_t *core, u_int8_t type, int param, arg_t *arg)
{
    if (type == REGISTER)
        sfText_setString(arg->type.text, REG_STR);
    else if (type == DIRECT)
        sfText_setString(arg->type.text, DIRECT_STR);
    if (type == NO_PARAM || type == INDIRECT)
        sfText_setString(arg->type.text, INDIRECT_STR);
    sfText_setString(arg->argu.text, nm_itoa(arg->nb, param));
}

void destroy_arg(arg_t *arg)
{
    destroy_text(&arg->argu);
    destroy_text(&arg->type);
}