/*
** EPITECH PROJECT, 2020
** MUL_my_world_bootstrap_2019
** File description:
** display_window
*/

#include "corewar_bonus.h"

int init_window(cw_t *cw)
{
    cw->clock = sfClock_create();
    cw->vclock = sfClock_create();
    if (!cw->vclock || !cw->clock) return (1);
    cw->video_mode = (sfVideoMode){WIDTH, HEIGHT, 32};
    cw->window = sfRenderWindow_create(cw->video_mode, "corewar_bonus",
    sfDefaultStyle, NULL);
    if (!cw->window) return (1);
    sfRenderWindow_setFramerateLimit(cw->window, 10);
    return (0);
}

void time_event_handling(core_t *core, reveal_t *reveal, cw_t *cw)
{
    cw->time = sfClock_getElapsedTime(cw->clock);
    cw->sec = cw->time.microseconds / 1000000.0;
    cw->time = sfClock_getElapsedTime(cw->vclock);
    cw->vm = cw->time.microseconds / 1000000.0;
    while (sfRenderWindow_pollEvent(cw->window, &cw->event))
        reveal_event(core, reveal);
}

void destroy_window(cw_t *cw)
{
    sfClock_destroy(cw->clock);
    sfClock_destroy(cw->vclock);
    sfRenderWindow_destroy(cw->window);
}