/*
** EPITECH PROJECT, 2021
** nodeuse
** File description:
** nodeuse
*/

#include "../include/prototype.h"

void remove_node_ghettobyfd(user_t *user, server_t *srv)
{
    user_t *tmp = srv->user_list;

    if (tmp == user) {
        srv->user_list = srv->user_list->next;
        return;
    }
    for (; tmp; tmp = tmp->next) {
        if (tmp->next == user && tmp->next->next == NULL)
            tmp->next = NULL;
        else if (tmp->next == user && tmp->next->next != NULL) {
            tmp->next = tmp->next->next;
        }
    }
    return;
}