/*
** EPITECH PROJECT, 2020
** MUL_my_rpg_2019
** File description:
** framebuffer_thread
*/

#include "rpg.h"

int framebuffer_run(game_t *ga)
{
    sfMutex_lock(ga->fbf._s.l_run);
    while (ga->fbf._s.run) {
        sfMutex_unlock(ga->fbf._s.l_run);
        sfSleep(ga->fbf._s.sleep);
        framebuffer_calculate(ga);
        sfMutex_lock(ga->fbf._s.l_run);
    }
    return (0);
}

int framebuffer_thread(game_t *ga)
{
    ga->fbf._s.thread = sfThread_create((void *)&framebuffer_run, ga);
    ga->fbf._s.l_run = sfMutex_create();
    ga->fbf._s.l_activate = sfMutex_create();
    ga->fbf._s.sleep.microseconds = 20000.0;
    ga->fbf._s.run = 1;
    if (!ga->fbf._s.thread || !ga->fbf._s.l_run || !ga->fbf._s.l_activate)
        return (change_state_cause_of_error(ga));
    sfThread_launch(ga->fbf._s.thread);
    return (0);
}

void framebuffer_end(fbf_t *fbf)
{
    sfMutex_lock(fbf->_s.l_run);
    fbf->_s.run = 0;
    sfMutex_unlock(fbf->_s.l_run);
    sfThread_destroy(fbf->_s.thread);
    return;
}