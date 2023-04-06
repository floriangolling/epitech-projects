/*
** EPITECH PROJECT, 2020
** CPE_corewar_2019
** File description:
** prototype
*/

#ifndef PROTOTYPE_H_
#define PROTOTYPE_H_

#include "struct.h"

/**********\
*   ROOT   *
\**********/

int corewar_root(int argc, char **argv);

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

void divide_in_4bytes(core_t *core, void *param, int pc);

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

#endif /* !PROTOTYPE_H_ */