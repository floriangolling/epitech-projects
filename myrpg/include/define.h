/*
** EPITECH PROJECT, 2020
** MUL_my_rpg_2019
** File description:
** define
*/

#ifndef DEFINE_H_
#define DEFINE_H_

/************************\
*   RECURRENT ELEMENTS   *
\************************/

#define WINDOW game->window->window

/************\
*   EVENTS   *
\************/

#define MOUSE_CLICK game->window->event.type == sfEvtMouseButtonPressed
#define MOUSE_RELEASED game->window->event.type == sfEvtMouseButtonReleased
#define GET_MOUSE_POS game->mouse_position = \
                        sfMouse_getPositionRenderWindow(game->window->window)

/*******************************\
*   REWRITE TOO LONG FUNCTION   *
\*******************************/

#define sfSprite_getPos sfSprite_getPosition
#define drawSprite sfRenderWindow_drawSprite

/************\
*    INTRO   *
\************/
#define P1 "media/intro/part1.jpg"
#define P2 "media/intro/part2.jpg"
#define P3 "media/intro/part3.jpg"
#define P4 "media/intro/part4.jpg"
#define P5 "media/intro/part5.jpg"
#define P6 "media/intro/part6.jpg"
#define P7 "media/intro/part7.jpg"
#define P8 "media/intro/part8.jpg"


/************\
*    MOUSE   *
\************/

#define MOUSEX game->mouse_position.x
#define MOUSEY game->mouse_position.y

/************\
*   HITBOX   *
\************/

#define RED_MATCH (map & 128 && player & 128)

#define GREEN_MATCH (map & 64 && player & 64)

#define BLUE_MATCH (map & 32 && player & 32)

#define LOW_BLUE_MATCH (map == 1 && player & 128)

#define SCENE_MATCH map == i && player & 32

#define INTERACTION_MATCH map == 9 && player & 128

#define GATE_MATCH (map == 10 && player & 128 && \
    ga->game_scenes[TAVERN_MAP].dialog_state && \
    !ga->game_scenes[SELLER_MAP].dialog_state)

#define PLAYER_PIXEL h->player.box[y + c->rect.top][x + c->rect.left]
#define MAP_PIXEL h->map.box[p.y + y][p.x + x]

#define OUT_OF_RANGE p.y + y < 0 || p.y + y >= h->map.dim.y || p.x + x < 0 || \
    p.x + x >= h->map.dim.x || y + c->rect.top >= h->player.dim.y || \
    x + c->rect.left >= h->player.dim.x

/***************\
*  FRAMEBUFFER  *
\***************/

#define UPDATE_NECESSARY m.x != ga->fbf.m.x || m.y != ga->fbf.m.y || \
    p.x != ga->fbf.p.x || p.y != ga->fbf.p.y || alpha < 230

/**********\
*   RAIN   *
\**********/

#define DROP_CAN_SPLASH y > 0 && x > 0 && y < ga->hit.map.dim.y && \
    x < ga->hit.map.dim.x && (!ga->hit.map.box[y][x] || \
    ga->hit.map.box[y][x] == 32)

/**********\
*   RAIN   *
\**********/

#define HALO_INSIDE dark->halo[e].light_on && dark->halo[e].pos.x + fbf->m.x + \
    dark->halo[e].radius > 0 && dark->halo[e].pos.x + fbf->m.x - \
    dark->halo[e].radius < fbf->w.x && dark->halo[e].pos.y + fbf->m.y + \
    dark->halo[e].radius > 0 && dark->halo[e].pos.y + fbf->m.y - \
    dark->halo[e].radius < fbf->w.y

/************\
*   BUFFER   *
\************/

#define IN_BUFFER x < buffer->size.x && x >= 0 && y < buffer->size.y && y >= 0

/************\
*   BATTLE   *
\************/

#define ENEMY_IS_HIT sfFloatRect_contains(&enemy, ba->arrows[e].pos.x + \
    ba->arrows[e].tip.x, ba->arrows[e].pos.y + ba->arrows[e].tip.y)

#define PLAYER_IS_HIT ba->enemy[e].arrow.send && sfFloatRect_contains(&player, \
    ba->enemy[e].arrow.pos.x + ba->enemy[e].arrow.tip.x, \
    ba->enemy[e].arrow.pos.y + ba->enemy[e].arrow.tip.y)

#define ENEMY_BOUNCE ba->enemy[i].alive && ba->enemy[e].alive && \
    sfFloatRect_intersects(&enemy1, &enemy2, NULL)

#endif /* !DEFINE_H_ */