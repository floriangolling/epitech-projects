/*
** EPITECH PROJECT, 2020
** CPE_corewar_bonus_2019
** File description:
** core_process
*/

#include "corewar_bonus.h"

process_t *create_process(int pc, int warrior_n)
{
    process_t *element = malloc(sizeof(process_t));

    if (!element) return (NULL);
    element->pc = pc;
    element->carry = 1;
    element->cycle = 0;
    element->state = FETCH;
    element->alive = 0;
    init_it(&element->it);
    for (int e = 0; e < REG_NUMBER; ++e)
        element->registre[e] = 0;
    element->registre[1] = warrior_n;
    return (element);
}

process_t *duplicate_process(int pc, process_t *process)
{
    process_t *element = malloc(sizeof(process_t));

    if (!element) return (NULL);
    element->pc = pc;
    element->carry = 1;
    element->cycle = 0;
    element->state = FETCH;
    element->alive = 0;
    init_it(&element->it);
    for (int e = 0; e < REG_NUMBER; ++e)
        element->registre[e] = process->registre[e];
    return (element);
}

int insert_process_end(process_t **list, process_t *element)
{
    process_t *save = *list;

    if (!element) return (1);
    if (save == NULL) {
        element->next = save;
        *list = element;
        return (0);
    }
    for (; save->next != NULL; save = save->next);
    element->next = NULL;
    save->next = element;
    return (0);
}

void remove_process_index(process_t **list, int index)
{
    process_t *save = *list;
    process_t *tmp;

    if (index < 0 || save == NULL)
        return;
    if (index == 0 && save->next == NULL) {
        *list = NULL;
        return;
    } else if (index == 0 && save->next != NULL) {
        *list = save->next;
        return ;
    }
    for (int i = 0; i < index - 1 && save->next != NULL; save = save->next)
        i++;
    if (save->next == NULL) return;
    tmp = save->next->next;
    save->next = tmp;
}

void destroy_process(process_t *node)
{
    process_t *tmp = node;

    while (node) {
        tmp = node->next;
        free(node);
        node = tmp;
    }
}