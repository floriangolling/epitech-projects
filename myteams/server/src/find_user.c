/*
** EPITECH PROJECT, 2021
** find
** File description:
** find
*/

#include "../include/prototype.h"

user_t *find_user_name(char *str, server_t *srv)
{
    user_t *tmp = srv->user_list;

    for (; tmp; tmp = tmp->next) {
        if (tmp->user_name != NULL && strcmp(str, tmp->user_name) == 0) {
            return (tmp);
        }
    }
    return (NULL);
}

user_t *find_user_by_fd(int fd, server_t *srv)
{
    user_t *user = NULL;

    for (user_t *tmp = srv->user_list; tmp; tmp = tmp->next) {
        if (tmp->socket == fd)
            return (tmp);
    }
    return (user);
}

user_t *find_user_by_uuid(char *uuid, server_t *srv)
{
    user_t *user = NULL;

    for (user_t *tmp = srv->user_list; tmp; tmp = tmp->next) {
        if (strcmp(tmp->uuid, uuid) == 0)
            return (tmp);
    }
    return (user);
}