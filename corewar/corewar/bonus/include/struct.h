/*
** EPITECH PROJECT, 2020
** CPE_corewar_bonus_2019
** File description:
** struct
*/

#ifndef STRUCT_H_
#define STRUCT_H_

#include "op.h"
#include <SFML/Graphics.h>

/***************\
*  INSTRUCTION  *
\***************/

typedef struct it_s
{
    u_int8_t mnemonic;
    u_int8_t type[MAX_ARGS_NUMBER];
    int param[MAX_ARGS_NUMBER];
    int pc;
}it_t;

/*************\
*   PROCESS   *
\*************/

typedef struct process_s
{
    int pc;
    it_t it;
    bool alive;
    bool carry;
    u_int8_t state;
    short cycle;
    int registre[REG_NUMBER];
    struct process_s *next;
}process_t;

/*************\
*   WARRIOR   *
\*************/

typedef struct warrior_s
{
    u_int8_t alive;
    u_int8_t n;
    int nb_p;
    int warrior_n;
    int ld_adress;
    char *program;
    header_t header;
    process_t *process;
}warrior_t;

/***********\
*   CYCLE   *
\***********/

typedef struct cycle_s
{
    long int total;
    int cycle;
    int cycle_to_die;
    int nbr_live;
    u_int8_t last_live;
}cycle_t;

/************\
*   WINDOW   *
\************/

typedef struct cw_s
{
    sfRenderWindow *window;
    sfClock *clock;
    sfClock *vclock;
    sfVideoMode video_mode;
    sfEvent event;
    sfTime time;
    double sec;
    double vm;
}cw_t;

/**********\
*   CELL   *
\**********/

typedef struct cell_s
{
    sfText *text;
    sfFont *font;
    sfVector2f pos;
    sfColor color;
    char value[3];
    bool read;
}cell_t;

/**********\
*   TEXT   *
\**********/

typedef struct text_s
{
    sfText *text;
    sfVector2f pos;
    sfColor color;
}text_t;

/**********\
*   RECT   *
\**********/

typedef struct rect_s
{
    sfRectangleShape *shape;
    sfVector2f pos;
}rect_t;

/**********\
*   INFO   *
\**********/

typedef struct arg_s
{
    text_t type;
    text_t argu;
    char nb[10];
}arg_t;

typedef struct cmd_s
{
    char nb_arg;
    text_t d;
    text_t nb_pc;
    char pc[10];
    text_t cmd;
    arg_t arg[4];
}cmd_t;

typedef struct info_s
{
    cmd_t cmd;
    text_t name;
    text_t live;
    rect_t rect;
    text_t nb_p;
    char nb[10];
}info_t;

typedef struct infc_s
{
    text_t desc;
    text_t nb_c;
    char cy[10];
    text_t nb_d;
    char di[10];
    text_t tota;
    text_t nb_t;
    char to[20];
    text_t live;
    text_t nb_l;
    char li[10];
}infc_t;

/************\
*   REVEAL   *
\************/

typedef struct reveal_s
{
    bool pause;
    u_int8_t frame;
    u_int8_t output;
    infc_t cy_info;
    info_t info[4];
    sfFont *font;
    cell_t cell[MEM_SIZE + 1];
    cw_t cw;
}reveal_t;

/**********\
*   CORE   *
\**********/

typedef struct core_s
{
    bool run;
    u_int8_t nb_w;
    cycle_t cycle;
    u_int32_t nb_cycle;
    unsigned char men[MEM_SIZE + 1];
    unsigned char belong[MEM_SIZE + 1];
    warrior_t warrior[4];
    reveal_t reveal;
}core_t;

#endif /* !STRUCT_H_ */