/*
** EPITECH PROJECT, 2020
** bonus
** File description:
** reveal_info
*/

#include "corewar_bonus.h"

int init_info(core_t *core, reveal_t *reveal)
{
    sfVector2f pos = {10, 30};

    for (int e = 0; e < core->nb_w; ++e, pos.x += (WIDTH / 4))
        if (init_data(core, &core->warrior[e], &reveal->info[e], pos))
            return (1);
    if (init_infc(core, &reveal->cy_info, (sfVector2f){220, 185}))
        return (1);
    return (0);
}

static void display_data(core_t *core, info_t *info)
{
    display_text(core, &core->reveal, &info->name);
    display_text(core, &core->reveal, &info->live);
    display_rectangle(&core->reveal.cw, &info->rect);
    display_text(core, &core->reveal, &info->nb_p);
    if (core->reveal.frame == 5)
        display_cmd(core, &core->reveal, &info->cmd);
}

static void display_infc(core_t *core, infc_t *infc)
{
    display_text(core, &core->reveal, &infc->desc);
    display_text(core, &core->reveal, &infc->nb_c);
    display_text(core, &core->reveal, &infc->nb_d);
    display_text(core, &core->reveal, &infc->tota);
    display_text(core, &core->reveal, &infc->nb_t);
    display_text(core, &core->reveal, &infc->live);
    display_text(core, &core->reveal, &infc->nb_l);
}

int info_run(core_t *core, reveal_t *reveal)
{
    for (int e = 0; e < core->nb_w; ++e)
        display_data(core, &reveal->info[e]);
    display_infc(core, &reveal->cy_info);
    return (0);
}

void destroy_info(core_t *core, reveal_t *reveal)
{
    for (int e = 0; e < core->nb_w; ++e) {
        destroy_text(&reveal->info[e].name);
        destroy_text(&reveal->info[e].live);
        destroy_text(&reveal->info[e].nb_p);
        destroy_rectangle(&reveal->info[e].rect);
        destroy_cmd(&reveal->info[e].cmd);
    }
    destroy_cycle(&reveal->cy_info);
}