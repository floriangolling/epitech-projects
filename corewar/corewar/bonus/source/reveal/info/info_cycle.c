/*
** EPITECH PROJECT, 2020
** bonus
** File description:
** info_cycle
*/

#include "corewar_bonus.h"

static int init_cycle_to_die(core_t *core, infc_t *infc, sfVector2f pos)
{
    if (init_texta(&infc->desc, 25, core->reveal.font, "cycle to die:\t\t\t  \
    /")) return (1);
    if (init_textb(&infc->desc, pos, warrior_color[0]))
        return (1);
    pos.x += 100;
    if (init_texta(&infc->nb_c, 25, core->reveal.font,
    nm_itoa(infc->cy, core->cycle.cycle)))
        return (1);
    if (init_textb(&infc->nb_c, pos, warrior_color[0]))
        return (1);
    pos.x += 100;
    if (init_texta(&infc->nb_d, 25, core->reveal.font,
    nm_itoa(infc->di, core->cycle.cycle_to_die)))
        return (1);
    if (init_textb(&infc->nb_d, pos, warrior_color[0]))
        return (1);
    return (0);
}

static int init_total_cycle(core_t *core, infc_t *infc, sfVector2f pos)
{
    if (init_texta(&infc->tota, 25, core->reveal.font, "Total cycle:\t\t\t\t"))
        return (1);
    if (init_textb(&infc->tota, pos, warrior_color[0]))
        return (1);
    pos.x += 100;
    if (init_texta(&infc->nb_t, 25, core->reveal.font,
    nm_itoa(infc->to, core->cycle.total)))
        return (1);
    if (init_textb(&infc->nb_t, pos, warrior_color[0]))
        return (1);
    return (0);
}

static int init_cycle_live(core_t *core, infc_t *infc, sfVector2f pos)
{
    if (init_texta(&infc->live, 25, core->reveal.font, "Nb live:\t\t\t\t/  40"))
        return (1);
    if (init_textb(&infc->live, pos, warrior_color[0]))
        return (1);
    pos.x += 70;
    if (init_texta(&infc->nb_l, 25, core->reveal.font,
    nm_itoa(infc->li, core->cycle.nbr_live)))
        return (1);
    if (init_textb(&infc->nb_l, pos, warrior_color[0]))
        return (1);
    return (0);
}

int init_infc(core_t *core, infc_t *infc, sfVector2f pos)
{
    if (init_cycle_to_die(core, infc, pos)) return (1);
    pos.x += 600;
    if (init_total_cycle(core, infc, pos)) return (1);
    pos.x += 500;
    if (init_cycle_live(core, infc, pos)) return (1);
    return (0);
}

void destroy_cycle(infc_t *infc)
{
    sfText_destroy(infc->nb_c.text);
    sfText_destroy(infc->nb_d.text);
    sfText_destroy(infc->nb_l.text);
    sfText_destroy(infc->nb_t.text);
    sfText_destroy(infc->desc.text);
    sfText_destroy(infc->tota.text);
    sfText_destroy(infc->live.text);
}