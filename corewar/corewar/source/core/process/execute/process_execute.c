/*
** EPITECH PROJECT, 2020
** CPE_corewar_2019
** File description:
** process_execute
*/

#include "corewar.h"

int execute_jumpifzero(core_t *core, warrior_t *w, process_t **pcs, it_t *it)
{
    if ((*pcs)->carry) {
        (*pcs)->pc = it->pc;
        GO_PC((*pcs)->pc, it->param[0]);
    }
    return (0);
}

int execute_aff(core_t *core, warrior_t *w, process_t **process, it_t *it)
{
    unsigned char character = 0;

    if (WRONG_REG(it->param[0]))
        return (0);
    character = (*process)->registre[it->param[0]] % 256;
    my_putchar(character);
    my_putchar('\n');
    return (0);
}

int process_execute(core_t *core, warrior_t *warrior, process_t **process)
{
    static int (*execute[])(core_t *core, warrior_t *w, process_t **process,
    it_t *it) = {NULL, execute_live, execute_load, execute_store,
    execute_addition, execute_subtraction, execute_and, execute_or,
    execute_xor, execute_jumpifzero, execute_load_index, execute_store_index,
    execute_fork, execute_lload, execute_lload_index, execute_long_fork,
    execute_aff};

    if ((execute[(*process)->it.mnemonic])
    (core, warrior, process, &(*process)->it))
        return (1);
    (*process)->state = FETCH;
    return (0);
}