/*
** EPITECH PROJECT, 2020
** CPE_corewar_bonus_2019
** File description:
** prototype
*/

#ifndef PROTOTYPE_H_
#define PROTOTYPE_H_

#include "struct.h"
#include <SFML/Graphics.h>

/**********\
*   CORE   *
\**********/

int init_core(core_t *core, int argc, char **argv);
int core_run(core_t *core);
void destroy_core(core_t *core);

/*************\
*   WARRIOR   *
\*************/

int init_warrior(core_t *core, int argc, char **argv, int *e);
void destroy_warrior(warrior_t *warrior);

/************\
*   MEMORY   *
\************/

int init_menory(core_t *core, warrior_t *warrior, char **argv, int *e);
void memory_fill(core_t *core, warrior_t *warrior);

/*************\
*   PROCESS   *
\*************/

process_t *create_process(int pc, int warrior_n);
process_t *duplicate_process(int pc, process_t *process);
int insert_process_end(process_t **list, process_t *element);
void remove_process_index(process_t **list, int index);
void destroy_process(process_t *node);

int process_run(core_t *core, warrior_t *warrior);

/***********\
*   FETCH   *
\***********/

int process_fetch(core_t *core, warrior_t *warrior, process_t **process);

void merge_4bytes(core_t *core, process_t **process, void *param);
void merge_4bytes_pc(core_t *core, void *param, int pc);

void merge_2bytes(core_t *core, process_t **process, int *param);
void merge_2bytes_pc(core_t *core, int *param, int pc);

int fetch_particular(core_t *core, warrior_t *warrior, process_t **process);

/***********\
*   CYCLE   *
\***********/

int init_cycle(core_t *core, cycle_t *cycle);
int core_cycle(core_t *core, cycle_t *cycle);

void verified_living_process(core_t *core, cycle_t *cycle);
int verified_living_warrior(core_t *core, cycle_t *cycle);
void display_winner(core_t *core, int winner);

/*************\
*   EXECUTE   *
\*************/

int process_execute(core_t *core, warrior_t *warrior, process_t **process);

void divide_in_4bytes(core_t *core, void *param, int pc, int n);

int param_type(core_t *core, process_t **pcs, u_int8_t ic, u_int8_t ref);
int param_type_control(it_t it);

int execute_live(core_t *core, warrior_t *w, process_t **process, it_t *it);

int execute_load(core_t *core, warrior_t *w, process_t **process, it_t *it);
int execute_lload(core_t *core, warrior_t *w, process_t **process, it_t *it);
int execute_load_index(core_t *core, warrior_t *w, process_t **pcs, it_t *it);
int execute_lload_index(core_t *core, warrior_t *w, process_t **pcs, it_t *it);

int execute_store(core_t *core, warrior_t *w, process_t **process, it_t *it);
int execute_store_index(core_t *core, warrior_t *w, process_t **pcs, it_t *it);

int execute_addition(core_t *core, warrior_t *w, process_t **pcs, it_t *it);
int execute_subtraction(core_t *core, warrior_t *w, process_t **pcs, it_t *it);

int execute_and(core_t *core, warrior_t *w, process_t **pcs, it_t *it);
int execute_or(core_t *core, warrior_t *w, process_t **pcs, it_t *it);
int execute_xor(core_t *core, warrior_t *w, process_t **pcs, it_t *it);

int execute_jumpifzero(core_t *core, warrior_t *w, process_t **pcs, it_t *it);

int execute_fork(core_t *core, warrior_t *w, process_t **process, it_t *it);
int execute_long_fork(core_t *core, warrior_t *w, process_t **pcs, it_t *it);

int execute_aff(core_t *core, warrior_t *w, process_t **process, it_t *it);

/********\
*   IT   *
\********/

void init_it(it_t *it);
void restore_it(process_t **process);

/********************\
*   BONUS : ORIGIN   *
\********************/

int bonus_origin(int argc, char **argv);

/************\
*   REVEAL   *
\************/

int init_reveal(core_t *core, reveal_t *reveal);
int reveal_run(core_t *core, reveal_t *reveal);
void destroy_reveal(core_t *core, reveal_t *reveal);
int init_board(core_t *core, reveal_t *reveal);
void board_display(core_t *core, reveal_t *rv);

/************\
*   WINDOW   *
\************/

int init_window(cw_t *cw);
void time_event_handling(core_t *core, reveal_t *reveal, cw_t *cw);
void destroy_window(cw_t *cw);

/***********\
*   EVENT   *
\***********/

int reveal_event(core_t *core, reveal_t *reveal);

/**********\
*   CELL   *
\**********/

int init_cell(cell_t *cell, sfVector2f pos, u_int8_t value,  u_int8_t warrior);
void cell_display(reveal_t *rv, cell_t *cell, u_int8_t value);
void destroy_cell(cell_t *cell);

/**********\
*   INFO   *
\**********/

int init_info(core_t *core, reveal_t *reveal);
int info_run(core_t *core, reveal_t *reveal);
void destroy_info(core_t *core, reveal_t *reveal);

int init_data(core_t *core, warrior_t *w, info_t *info, sfVector2f pos);

int init_infc(core_t *core, infc_t *infc, sfVector2f pos);
void destroy_cycle(infc_t *infc);

/**********\
*   TEXT   *
\**********/

int init_texta(text_t *text, u_int32_t size, sfFont *font, char *fill);
int init_textb(text_t *text, sfVector2f pos, sfColor color);
void display_text(core_t *core, reveal_t *reveal, text_t *text);
void destroy_text(text_t *text);

/**********\
*   RECT   *
\**********/

int init_rectangle(rect_t *rect, sfVector2f pos, sfVector2f size);
void display_rectangle(cw_t *cw, rect_t *rect);
void destroy_rectangle(rect_t *rect);

/*********\
*   CMD   *
\*********/

int init_cmd(core_t *core, warrior_t *w, cmd_t *cmd, sfVector2f pos);
void display_cmd(core_t *core, reveal_t *reveal, cmd_t *cmd);
void fill_cmd(core_t *core, warrior_t *w, process_t **pcs, cmd_t *cmd);
void destroy_cmd(cmd_t *cmd);

/*********\
*   ARG   *
\*********/

int init_arg(core_t *core, warrior_t *w, arg_t *arg, sfVector2f pos);
void display_arg(core_t *core, reveal_t *reveal, arg_t *arg);
void fill_arg(core_t *core, u_int8_t type, int param, arg_t *arg);
void destroy_arg(arg_t *arg);

#endif /* !PROTOTYPE_H_ */