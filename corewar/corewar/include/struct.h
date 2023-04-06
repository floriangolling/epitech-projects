/*
** EPITECH PROJECT, 2020
** CPE_corewar_2019
** File description:
** struct
*/

#ifndef STRUCT_H_
#define STRUCT_H_

#include "op.h"
#include <sys/types.h>

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
    warrior_t warrior[4];
}core_t;

/**********\
*   ROOT   *
\**********/

typedef struct corewar_s
{
    core_t core;
}corewar_t;

#endif /* !STRUCT_H_ */