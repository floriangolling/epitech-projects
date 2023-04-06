/*
** EPITECH PROJECT, 2020
** bonus
** File description:
** info_cmd
*/

#include "corewar_bonus.h"

int init_cmd(core_t *core, warrior_t *w, cmd_t *cmd, sfVector2f pos)
{
    cmd->nb_arg = 0;
    if (init_texta(&cmd->d, 23, core->reveal.font,
    "Execution of:\nAt PC:")) return (1);
    if (init_textb(&cmd->d, pos, warrior_color[0])) return (1);
    pos.x += 100;
    if (init_texta(&cmd->cmd, 23, core->reveal.font, "start")) return (1);
    if (init_textb(&cmd->cmd, pos, warrior_color[0])) return (1);
    pos.x += 50;
    for (int e = 0; e < MAX_ARGS_NUMBER; ++e, pos.x += 60)
        if (init_arg(core, w, &cmd->arg[e], pos)) return (1);
    pos.x -= 330;
    pos.y += 33;
    if (init_texta(&cmd->nb_pc, 23, core->reveal.font,
        nm_itoa(cmd->pc, w->process->it.pc))) return (1);
    if (init_textb(&cmd->nb_pc, pos, warrior_color[0])) return (1);
    return (0);
}

void display_cmd(core_t *core, reveal_t *reveal, cmd_t *cmd)
{
    display_text(core, reveal, &cmd->d);
    display_text(core, reveal, &cmd->nb_pc);
    display_text(core, reveal, &cmd->cmd);
    for (int e = 0; e < MAX_ARGS_NUMBER && e < cmd->nb_arg; ++e)
        display_arg(core, reveal, &cmd->arg[e]);
}

void fill_cmd(core_t *core, warrior_t *w, process_t **pcs, cmd_t *cmd)
{
    sfText_setString(cmd->nb_pc.text, nm_itoa(cmd->pc, (*pcs)->it.pc));
    sfText_setString(cmd->cmd.text, ref[(*pcs)->it.mnemonic].mnemonique);
    cmd->nb_arg = ref[(*pcs)->it.mnemonic].nbr_args;
    for (int e = 0; e < MAX_ARGS_NUMBER && e < cmd->nb_arg; ++e)
        fill_arg(core, (*pcs)->it.type[e], (*pcs)->it.param[e], &cmd->arg[e]);
}

void destroy_cmd(cmd_t *cmd)
{
    destroy_text(&cmd->d);
    destroy_text(&cmd->nb_pc);
    destroy_text(&cmd->cmd);
    for (int e = 0; e < MAX_ARGS_NUMBER; ++e)
        destroy_arg(&cmd->arg[e]);
}