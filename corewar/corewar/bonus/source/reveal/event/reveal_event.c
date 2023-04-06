/*
** EPITECH PROJECT, 2020
** MUL_my_world_object_2019
** File description:
** window_event
*/

#include "corewar_bonus.h"

int quit(core_t *core, reveal_t *reveal)
{
    sfRenderWindow_close(reveal->cw.window);
    return (0);
}

int debug(core_t *core, reveal_t *reveal)
{
    static int v = 0;

    ++v;
    if (reveal->frame == 5 && !(v % 2)) {
        reveal->frame = 100;
        reveal->output = 10;
    }
    else if (reveal->frame == 100 && !(v % 2)) {
        reveal->frame = 5;
        reveal->output = 5;
    }
    return (0);
}

int pausevm(core_t *core, reveal_t *reveal)
{
    static int v = 0;

    ++v;
    if (!reveal->pause && !(v % 2))
        reveal->pause = 1;
    else if (reveal->pause && !(v % 2))
        reveal->pause = 0;
    return (0);
}

static int (*event[])(core_t *core, reveal_t *reveal) = {
    quit,
    debug,
    pausevm
};

static sfKeyCode key[] = {
    sfKeyQ,
    sfKeyD,
    sfKeySpace
};

int reveal_event(core_t *core, reveal_t *reveal)
{
    if (reveal->cw.event.type == sfEvtClosed)
        sfRenderWindow_close(reveal->cw.window);
    for (int ic = 0; ic < 3; ++ic) {
        if (sfKeyboard_isKeyPressed(key[ic]))
            (*event[ic])(core, reveal);
    }
    return (0);
}