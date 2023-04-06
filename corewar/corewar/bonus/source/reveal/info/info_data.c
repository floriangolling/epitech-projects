/*
** EPITECH PROJECT, 2020
** bonus
** File description:
** info_data
*/

#include "corewar_bonus.h"

static int init_name(core_t *core, warrior_t *w, info_t *info, sfVector2f pos)
{
    if (init_texta(&info->name, 30, core->reveal.font, w->header.prog_name))
        return (1);
    if (init_textb(&info->name, pos, warrior_color[w->n])) return (1);
    return (0);
}

static int init_state(core_t *core, warrior_t *w, info_t *info, sfVector2f pos)
{
    if (init_texta(&info->live, 23, core->reveal.font,
        "live state:\nnb of process:"))
        return (1);
    if (init_textb(&info->live, pos, warrior_color[0]))
        return (1);
    if (init_rectangle(&info->rect, (sfVector2f){pos.x + 80, pos.y + 2},
        (sfVector2f){27, 27}))
        return (1);
    if (init_texta(&info->nb_p, 25, core->reveal.font,
        nm_itoa(info->nb, w->nb_p)))
        return (1);
    pos.y += 33;
    if (init_textb(&info->nb_p, (sfVector2f){pos.x + 105, pos.y},
        warrior_color[0]))
        return (1);
    return (0);
}

int init_data(core_t *core, warrior_t *w, info_t *info, sfVector2f pos)
{
    if (init_name(core, w, info, pos)) return (1);
    pos.y += 40;
    if (init_state(core, w, info, pos)) return (1);
    pos.y += 63;
    if (init_cmd(core, w, &info->cmd, pos)) return (1);
    return (0);
}