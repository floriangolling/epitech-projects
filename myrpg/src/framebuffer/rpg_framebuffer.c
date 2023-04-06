/*
** EPITECH PROJECT, 2019
** MUL_my_radar_2019
** File description:
** framebuffer
*/

#include "rpg.h"

int init_framebuffer(game_t *ga, fbf_t *fbf, int height, int width)
{
    srand(time(NULL));
    fbf->w = (sfVector2i){width, height};
    fbf->p = (sfVector2f){0, 0};
    fbf->m = (sfVector2f){0, 0};
    fbf->move = 1;
    fbf->nb_active = 3;
    fbf->active = malloc(sizeof(u_int8_t) * fbf->nb_active);
    if (!fbf->active) return (1);
    for (int e = 0; e < fbf->nb_active; ++e)
        fbf->active[e] = 0;
    if (init_buffer(fbf, height, width)) return (1);
    if (init_rain(ga, fbf, &fbf->rain)) return (1);
    if (init_dark(ga, &fbf->dark)) return (1);
    if (init_cut(ga, &fbf->cut)) return (1);
    return (0);
}

void framebuffer_display(game_t *ga)
{
    sfMutex_lock(ga->fbf.buffer.l_sprite);
    sfRenderWindow_drawSprite(ga->window->window, ga->fbf.buffer.sprite, NULL);
    sfMutex_unlock(ga->fbf.buffer.l_sprite);
    return;
}

void framebuffer_destroy(fbf_t *fbf)
{
    destroy_buffer(&fbf->buffer);
    destroy_rain(&fbf->rain);
    destroy_dark(&fbf->dark);
    destroy_cut(&fbf->cut);
    return;
}