/*
** EPITECH PROJECT, 2020
** lib element
** File description:
** check if FD is OK
*/

#include "my.h"
#include "include.h"
#include "struct.h"

void space_padding(info_t *globale)
{
    int i;
    node_t *tmp = globale->head;

    while (tmp != NULL) {
        if (tmp->line[0] != '\0') {
            i = my_strlen(tmp->line);
            for (; tmp->line[i] == ' ' || tmp->line[i] == '\t' ||
            tmp->line[i] == '\n'; i--)
                tmp->line[i] = '\0';
        }
        tmp = tmp->next;
    }
    return;
}

void remove_first_spaces(info_t *globale)
{
    node_t *tmp = globale->head;

    while (tmp != NULL) {
        while (*tmp->line == ' ' || *tmp->line == '\t')
            tmp->line++;
        tmp = tmp->next;
    }
    return;
}