/*
** EPITECH PROJECT, 2020
** MUL_my_rpg_2019
** File description:
** framebuffer_calculate
*/

#include "rpg.h"

void run_rain(game_t *ga)
{
    ga->fbf._s.sleep.microseconds = 20000.0;
    framebuffer_rain(ga, &ga->fbf);
    buffer_display(&ga->fbf.buffer, ga->window->window);
    buffer_gloomy_restore(&ga->fbf.buffer, 100);
    return;
}

void run_dark(game_t *ga)
{
    ga->fbf._s.sleep.microseconds = 10000.0;
    framebuffer_update(ga, &ga->fbf, ga->fbf.dark.gradually);
    framebuffer_dark(ga, &ga->fbf, &ga->fbf.dark);
    buffer_display(&ga->fbf.buffer, ga->window->window);
    return;
}

void run_cut(game_t *ga)
{
    ga->fbf._s.sleep.microseconds = 1000.0;
    framebuffer_cut(ga, &ga->fbf.cut);
    buffer_display(&ga->fbf.buffer, ga->window->window);
    return;
}

void (*run[])(game_t *ga) = {
    run_cut,
    run_rain,
    run_dark
};

int framebuffer_calculate(game_t *ga)
{
    sfMutex_lock(ga->fbf._s.l_activate);
    for (int e = 0; e < ga->fbf.nb_active; ++e)
        if (ga->fbf.active[e]) {
            (*run[e])(ga);
            break;
        }
    sfMutex_unlock(ga->fbf._s.l_activate);
    return (0);
}